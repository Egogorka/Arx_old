//
// Created by Meevere on 29.12.2021.
//

#ifndef ARX_NDARRAY_H
#define ARX_NDARRAY_H

#include <array>
#include "utility/Vector.h"

using std::array;

template<typename T, size_t N>
class ndArray {
    std::array<int, N> size;

    long num_el;

    T *data;


    /**
     * The flag for ownership of data
     */
    bool is_owner;

protected:
    static long num_elements(const std::array<int, N>& size){
        long num_el = 1;
        for (const auto &el : size) {
            num_el *= el;
        }
        return num_el;
    }

    static std::array<int, N> from_initializer(std::initializer_list<int> list){
        std::array<int, N> temp;
        auto it = list.begin();
        for (int i = 0; i < N; ++i) {
            if( it == list.end() ) break;
            temp[i] = *it;
            ++it;
        }
        return temp;
    }

public:
    long index(const Vector<int, N> &vector) const{
        long index = 0;
        long multiplier = num_el;
        for (int i = 0; i < N; ++i) {
            multiplier /= size[i];
            index += vector[i] * multiplier;
        }
        return index;
    }

    Vector<int, N> from_index(long index) const{
        Vector<int, N> output;
        long multiplier = 1;
        long previous = 0;
        for (int i = N-1; i >= 0; --i) {
            auto temp = index % (multiplier * size[i]);
            output[i] = (temp - previous) / multiplier;
            previous = temp;
            multiplier *= size[i];
        }
        return output;
    }

    explicit ndArray(const std::array<int, N> &size)
    : size(size), num_el(num_elements(size)), is_owner(true) {
        data = new T[num_el]{};
    }

    explicit ndArray(std::initializer_list<int> size)
            : ndArray(from_initializer(size)) {}

    static ndArray with_size(std::initializer_list<int> size){
        return ndArray{from_initializer(size)};
    }

    /**
     * @param array - must at least support the size of dimensions
     * @param dimensions
     * @return ndArray constructed with needed dimesionality and from data
     */
    static ndArray from_data(T* array, std::array<int,N> dimensions){
        ndArray out{dimensions};
        for(auto& item : out){
            item = *array;
            ++array;
        }
        return out;
    }

    static ndArray from_data(T* array, std::initializer_list<int> dimensions){
        return from_data(array, from_initializer(dimensions));
    }

    static ndArray from_data(std::initializer_list<T> array, std::initializer_list<int> dimensions){
        T arr[array.size()];
        auto it = array.begin();
        for (int i = 0; i < array.size(); ++i) {
            arr[i] = *it;
            it++;
        }
        return from_data(arr, from_initializer(dimensions));
    }

    ndArray(ndArray&& other): size(other.size), data(other.data), num_el(other.num_el), is_owner(true){
        other.is_owner = false;
        other.data = nullptr;
    }

    ndArray& operator=(ndArray&& other){
        ndArray temp{std::move(other)};
        std::swap(temp.is_owner, is_owner);
        std::swap(temp.data, data);
        std::swap(temp.size, size);
        std::swap(temp.num_el, num_el);
        return *this;
    }

    // deep-copy
    ndArray(const ndArray &other) : size(other.size), data(new T[other.num_el]), num_el(other.num_el), is_owner(true) {
        for (int i = 0; i < other.num_el; ++i) {
            data[i] = other.data[i];
        }
    }

    ndArray &operator=(const ndArray &other) {
        ndArray temp{other};
        *this = std::move(temp);
    }

    T& operator()(const Vector<int, N> &vector) {
        return data[index(vector)];
    }

    T& operator[](const Vector<int, N> &vector) {
        return data[index(vector)];
    }

    const T& operator[](const Vector<int, N> &vector) const {
        return data[index(vector)];
    }

    T at_def(const Vector<int, N> &vector, T def) const{
        for (int i = 0; i < N; ++i) {
            if(vector[i] < 0 || vector[i] >= size[i])
                return def;
        }
        return (*this)[vector];
    }

    ndArray<T,N-1> get_section(int index_section){
        // get_section the index
        Vector<int,N> temp{};
        temp[0] = index_section;
        auto j = index(temp);

        //get_section the subarray from size array (O(dim))
        std::array<int,N-1> subsize;
        int i = 0;
        int index = 0;
        for(auto& item : subsize){
            if(i == index) ++i;
            item = size[i];
            ++i;
        }

        return ndArray<T,N-1>::from_data(data+j,subsize);
    }

    std::array<int, N> get_size(){
        return size;
    }

    ~ndArray() {
        if (is_owner)
            delete[] data;
    }

    class Iterator {
        T *index;
        ndArray *array;
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using pointer = T *;
        using reference = T &;

        Iterator(T *index, ndArray *array) : index(index), array(array) {};

        Iterator(const Iterator &it) = default;

        Iterator &operator=(const Iterator &it) = default;

        reference operator*() const { return *index; };

        pointer operator->() { return index; };

        Iterator operator++() { ++index; return *this;};

        const Iterator operator++(int) {
            Iterator temp(*this);
            ++(*this);
            return temp;
        };

        Vector<int,N> get_vector() {return array->from_index(index - array->data);}

        friend bool operator==(const Iterator &a, const Iterator &b) { return a.index == b.index; };

        friend bool operator!=(const Iterator &a, const Iterator &b) { return a.index != b.index; };
    };

    class ConstIterator {
        T *index;
        ndArray *array;
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = const T;
        using pointer = const T *;
        using reference = const T &;

        ConstIterator(T *index) : index(index), array(array) {};

        ConstIterator(const ConstIterator &it) = default;

        ConstIterator &operator=(const ConstIterator &it) = default;

        reference operator*() const { return *index; };

        pointer operator->() { return index; };

        ConstIterator operator++() { return ++index; };

        const ConstIterator operator++(int) {
            ConstIterator temp(*this);
            ++(*this);
            return temp;
        };

        friend bool operator==(const ConstIterator &a, const ConstIterator &b) { return a.index == b.index; };

        friend bool operator!=(const ConstIterator &a, const ConstIterator &b) { return a.index != b.index; };
    };

    Iterator begin(){
        return Iterator(data, this);
    }

    Iterator end(){
        return Iterator(data + num_el, this);
    }

    ConstIterator cbegin(){
        return ConstIterator(data, this);
    }

    ConstIterator cend(){
        return ConstIterator(data + num_el, this);
    }
};

#endif //ARX_NDARRAY_H
