//
// Created by Meevere on 23.10.2021.
//

#ifndef DEFANTCE_VECTOR_H
#define DEFANTCE_VECTOR_H

#include <array>
#include <iostream>

using std::array;

/**
 * Vector from linear algebra, as we know it
 *
 * @tparam T, type that Vector holds, for example Vector of floats
 *      this type must have overloaded += and other addition operations for proper function
 * @tparam N, a size of a Vector
 */
template<typename T, size_t N>
class Vector: public array<T,N>{
    typedef const Vector& cvecr;
    typedef Vector& vecr;
public:
    vecr operator+=(cvecr other){
        for(unsigned i=0; i<N; i++)
            this->at(i) += other[i];
        return *this;
    }

    vecr operator-=(cvecr other){
        for(unsigned i=0; i<N; i++)
            this->at(i) -= other[i];
        return *this;
    }

    vecr operator*=(T other){
        for(unsigned i=0; i<N; i++)
            this->at(i) *= other;
        return *this;
    }

    vecr operator/=(T other){
        for(unsigned i=0; i<N; i++)
            this->at(i) /= other;
        return *this;
    }

    friend Vector operator+(cvecr first, cvecr second){
        Vector out(first);
        out += second;
        return out;
    }

    friend Vector operator-(cvecr first, cvecr second){
        Vector out(first);
        out -= second;
        return out;
    }

    friend Vector operator*(cvecr first, T second){
        Vector out(first);
        out *= second;
        return out;
    }

    friend Vector operator*(T second, cvecr first){return first*second;}

    friend Vector operator/(cvecr first, T second){
        Vector out(first);
        out /= second;
        return out;
    }

    friend Vector operator-(cvecr vec){
        Vector out(vec);
        for(unsigned i = 0; i < N; ++i)
            out[i] = -vec[i];
        return out;
    }

    friend std::ostream& operator<<(std::ostream& out, cvecr vec){
        for(unsigned i = 0; i < N-1; ++i)
            out << vec[i] << ' ';
        out << vec.back();
        return out;
    }
};


typedef Vector<float,2> Vector2f;
typedef Vector<double,2> Vector3f;
typedef Vector<int,2> Vector2i;
typedef Vector<int,3> Vector3i;

#endif //DEFANTCE_VECTOR_H
