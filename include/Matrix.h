#ifndef MATRIXHPP
#define MATRIXHPP

#include <stddef.h>
#include "Vector.h"
#include "CPRDef.h"

// for screen size stuff
#include <sys/ioctl.h>

template <typename T>
class Matrix {
protected:
    T * _matr;
    size_t _m;   // number of rows
    size_t _n;   // number of cols

    virtual void print(std::ostream & where) const {
        where << '[';
        for (size_t i{0}; i < _m; ++i) {
            for (size_t j{0}; j < _n; ++j) {
                where << this->get(i, j);
                if (i * _m + j != _m * _n - 1) where << ", ";
            }
            if (i != _m - 1) where << std::endl;
        }
        where << ']';
    }

    void printStraight(std::ostream & where) const {
        where << '[';
        for (size_t i{0}; i < _n * _m; ++i) {
            where << _matr[i];
            if (i < _n * _m - 1) where << ", ";
        }
        where << ']';
    }


public:
    Matrix(size_t m, size_t n) :  _matr(new T [m * n]), _m(m), _n(n) {}

    Matrix(size_t m, size_t n, std::initializer_list<T> l) :  _matr(new T [m * n]), _m(m), _n(n) {
        if (l.size() != _m * _n) throw; // sorry...

        size_t ind{0};
        for (auto it{l.begin()}; it < l.end(); ++it) {
            _matr[ind] = *it;
            ++ind;
        }
    }


    Matrix(Matrix & other) : _matr(new T [other._m * other._n]), _m(other._m), _n(other._n) {
        for (size_t i{0}; i < other._m * other._n; ++i) {
            _matr[i] = other._matr[i];
        }
    }

    ~Matrix() {
        delete [] _matr;
    }

    // ith row, jth column
    virtual const T & get(size_t i, size_t j) const {
        if (i < 0 || i > _m - 1 || j < 0 || j > _n - 1) throw std::out_of_range("Matrix indexed out of bounds.");
        return _matr[i * _n + j];
    }
    virtual T & get(size_t i, size_t j) {
        return _matr[i * _n + j];
    }
    virtual size_t numRows() const {
        return _m;
    }

    virtual size_t numCols() const {
        return _n;
    }

    virtual bool set(std::initializer_list<T> l) {
        if (l.size() != _m * _n) return false;

        size_t ind{0};
        for (auto it{l.begin()}; it < l.end(); ++it) {
            _matr[ind] = *it;
            ++ind;
        }
        return true;
    }

    // TODO: test me !
    Matrix operator=(const Matrix & other) {
        if (&other == this)
            return *this;
    
        delete [] _matr;
        _matr = new T[_m * _n];
        for (size_t i{0}; i < other._m * other._n; ++i) {
            _matr[i] = other._matr[i];
        }

        return *this;
    }

    friend std::ostream & operator<<(std::ostream & os, const Matrix & mat) {
        // mat.print(os);
        mat.printStraight(os);
        return os;
    }
};

class Matrix4 : public Matrix<double> {
public:
    Matrix4() : Matrix<double>(4, 4) {}
    Matrix4(std::initializer_list<double> init) : Matrix(4, 4, init) {}

    // Multiply a matrix into a vector
    // TODO make this work with arbitrarily sized vectors ? 
    Vector4 operator*(const Vector4 & vec) const {
        Vector4 out;
        for (size_t row{0}; row < Matrix::_m; ++row) {
            for (size_t col{0}; col < Matrix::_n; ++col) {
                out[row] += vec[col] * get(row, col);
            }
        }
        return out;
    }
};


// TODO: put this in a different file...
// TODO: and rename it to "Frame"

template <typename T>
class ScreenSizeBuffer : protected Matrix<T> {
public:
    ScreenSizeBuffer (const struct winsize & sizeInfo, T initialValue) : Matrix<T>(sizeInfo.ws_row-1, sizeInfo.ws_col) {
        for (size_t i{0}; i < Matrix<T>::_m; ++i) {
            for (size_t j{0}; j < Matrix<T>::_n; ++j) {
                Matrix<T>::get(i, j) = initialValue;
            }
        }
    }

    ScreenSizeBuffer(const struct winsize & sizeInfo) : Matrix<T>(sizeInfo.ws_row-1, sizeInfo.ws_col) {
        for (size_t i{0}; i < Matrix<T>::_m; ++i) {
            for (size_t j{0}; j < Matrix<T>::_n; ++j) {
                Matrix<T>::get(i, j) = {};
            }
        }
    }
};

class Screen : private ScreenSizeBuffer<frag> {
private:
    void guideMarks() {
        // top left
        get(0, 0).color = 'O';
        get(1, 0).color = 'O';
        get(0, 1).color = 'O';

        // top right
        get(0, _n-1).color = 'O';
        get(0, _n-2).color = 'O';
        get(1, _n-1).color = 'O';

        // bottom left
        get(_m-1, 0).color = 'O';
        get(_m-2, 0).color = 'O';
        get(_m-1, 1).color = 'O'; 

        // bottom right
        get(_m-1, _n-1).color = 'O';
        get(_m-2, _n-1).color = 'O';
        get(_m-1, _n-2).color = 'O';
    }

public:
    Screen(const struct winsize & sizeInfo, bool enableGuideMarks=false) : ScreenSizeBuffer<frag>(sizeInfo) {
        for (size_t i{0}; i < _m; ++i) {
            for (size_t j{0}; j < _n; ++j) {
                get(i, j) = frag(j, i, ' ', -1);
            }
        }
        if (enableGuideMarks)
            guideMarks();
    }

    // draw this screenframe 
    void draw(std::ostream & where) {
        for (size_t i{0}; i < _m * _n; ++i) {
            if (i != 0 && i % _n == 0) where << '\n';
            if (_matr[i].color != '\0') {
                where << _matr[i].color;
            }
            else where << ' ';
        }
    }

    // TODO make an out-of-bounds function

    size_t width() const {
        return Matrix::numCols();
    }

    size_t height() const {
        return Matrix::numRows();
    }

    const frag & getFrag(size_t i, size_t j) const {
        return get(i, j);
    }
    frag & getFrag(size_t i, size_t j) {
        return get(i, j);
    }

    void clear() {
        for (size_t i{0}; i < _m; ++i) {
            for (size_t j{0}; j < _n; ++j) {
                get(i, j) = frag(j, i, ' ', -1);
            }
        }
        guideMarks();
    }
};

class ZBuffer : private ScreenSizeBuffer<double> {
public:
    ZBuffer(const struct winsize & sizeInfo) : ScreenSizeBuffer<double>(sizeInfo, std::numeric_limits<double>::infinity()) {}
    const double & get(size_t i, size_t j) const {
        return Matrix::get(i, j);
    }
    double & get(size_t i, size_t j) {
        return Matrix::get(i, j);
    }
};

#endif
