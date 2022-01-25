//
// Created by Meevere on 22.01.2022.
//

#ifndef ARX_ARRAY_FUNCTIONS_H
#define ARX_ARRAY_FUNCTIONS_H

#include "ndArray.h"

template<typename T, size_t N>
Vector<T,N> get_gradient_at(const ndArray<T,N>& array, Vector<int,N> vec) {
    Vector<int,N> offset{}, out{};
    for (int i = 0; i < N; ++i) {
        offset[i] = 1;
        auto fx = array[vec];
        auto df = (array.at_def(vec + offset, fx) - array.at_def(vec - offset, fx))/2;
        offset[i] = 0;
        out[i] = df;
    }
    return out;
}

// Simple algorithm
template<typename T, size_t N>
ndArray<Vector<T,N>,N> get_gradient(ndArray<T,N> array) {
    ndArray<Vector<T,N>,N> out{array.get_size()};
    auto it_arr = array.begin();
    for (auto it = out.begin(); it != out.end(); ++it){
        auto pos = it.get_vector();
        out[pos] = get_gradient_at(array, pos);
    }
    return out;
}

// Simple algorithm
template<typename T, size_t N>
ndArray<T,N> get_gradient_module(ndArray<T,N> array) {
    ndArray<T,N> out{array.get_size()};
    auto grad = get_gradient(array);

    auto it_out = out.begin();
    auto it_proc = grad.begin();
    while (it_out != out.end()){
        *it_out = it_proc->square();
        ++it_out;
        ++it_proc;
    }
    return out;
}

#endif //ARX_ARRAY_FUNCTIONS_H
