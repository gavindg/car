#ifndef MATRIXHPP
#define MATRIXHPP

#include <stddef.h>
#include "Vector.h"
#include "CARDef.h"

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
        if (i < 0 || i > _m - 1 || j < 0 || j > _n - 1) {
            std::cerr << "Matrix indexed out of bounds. No index (" << i << ", " << j << ") in a " << _m << " by " << _n << " matrix." << std::endl;
            throw std::out_of_range("");
        }
        return _matr[i * _n + j];
    }
    virtual T & get(size_t i, size_t j) {
        if (i < 0 || i > _m - 1 || j < 0 || j > _n - 1) {
            std::cerr << "Matrix indexed out of bounds. No index (" << i << ", " << j << ") in a " << _m << " by " << _n << " matrix." << std::endl;
            throw std::out_of_range("");
        }
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

template <typename T>
class ScreenSizeBuffer : protected Matrix<T> {
public:
    ScreenSizeBuffer (const struct viewport & sizeInfo, T initialValue) : Matrix<T>(sizeInfo.height-1, sizeInfo.width) {
        for (size_t i{0}; i < Matrix<T>::_m; ++i) {
            for (size_t j{0}; j < Matrix<T>::_n; ++j) {
                Matrix<T>::get(i, j) = initialValue;
            }
        }
    }

    ScreenSizeBuffer(const struct viewport & sizeInfo) : Matrix<T>(sizeInfo.height-1, sizeInfo.width) {
        for (size_t i{0}; i < Matrix<T>::_m; ++i) {
            for (size_t j{0}; j < Matrix<T>::_n; ++j) {
                Matrix<T>::get(i, j) = {};
            }
        }
    }
};

class Screen : private ScreenSizeBuffer<char> {
private:
    void guideMarks() {
        // top left
        get(0, 0) =  'O';
        get(1, 0) = 'O';
        get(0, 1) = 'O';

        // top right
        get(0, _n-1) = 'O';
        get(0, _n-2) = 'O';
        get(1, _n-1) = 'O';

        // bottom left
        get(_m-1, 0) = 'O';
        get(_m-2, 0) = 'O';
        get(_m-1, 1) = 'O'; 

        // bottom right
        get(_m-1, _n-1) = 'O';
        get(_m-2, _n-1) = 'O';
        get(_m-1, _n-2) = 'O';
    }

public:
    Screen(const struct viewport & sizeInfo, bool enableGuideMarks=false) : ScreenSizeBuffer<char>(sizeInfo) {
        for (size_t i{0}; i < _m; ++i) {
            for (size_t j{0}; j < _n; ++j) {
                get(i, j) = '\0'; // frag(j, i, ' ', -1);
            }
        }
        if (enableGuideMarks)
            guideMarks();
    }

    void draw(const std::vector<std::ostream *> & streams, std::vector<frag> frags) {
        for (const struct frag & f : frags) {
            _matr[f.y * _n + f.x] = f.color;
        }

        for (size_t row{_m}; row > 0; --row) {
            for (size_t col{0}; col < _n; ++col) {
                size_t pos{(row - 1) * _n + col};
                if (_matr[pos] != '\0') {
                    for (auto & where : streams)
                        *where << _matr[pos];
                }
                else 
                    for (auto & where : streams)
                        *where << ' ';
            }
            for (auto & where : streams)
                *where << '\n';
        }
    }

    size_t width() const {
        return Matrix::numCols();
    }

    size_t height() const {
        return Matrix::numRows();
    }

    const char & getFrag(size_t i, size_t j) const {
        return get(i, j);
    }
    char & getFrag(size_t i, size_t j) {
        return get(i, j);
    }

    void clearBuffer() {
        for (size_t i{0}; i < _m; ++i) {
            for (size_t j{0}; j < _n; ++j) {
                get(i, j) = '\0';
            }
        }
        guideMarks();
    }
};

class ZBuffer : private ScreenSizeBuffer<double> {
public:
    ZBuffer(const struct viewport & sizeInfo, double initialValue) : ScreenSizeBuffer<double>(sizeInfo, initialValue) {}
    ZBuffer(const struct viewport & sizeInfo) : ScreenSizeBuffer<double>(sizeInfo, 2.0) {}

    void about() {
        std::cout << "hello. I am " << Matrix::_m << " by " << Matrix::_n << std::endl;
    }

    const double & get(size_t i, size_t j) const {
        return Matrix::get(i, j);
    }
    double & get(size_t i, size_t j) {
        return Matrix::get(i, j);
    }

};

#endif
