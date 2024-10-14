#ifndef MATRIXHPP
#define MATRIXHPP

#include <stddef.h>
#include "Vector.h"

class Matrix {
private:
    Vector ** matr;
    size_t _m;   // size of each vector
    size_t _n;   // size of array

public:
    Matrix(size_t m, size_t n) : _m(m), _n(n), matr(new Vector*[n]) {}

    ~Matrix() {
        delete [] matr;
    }
};


#endif
