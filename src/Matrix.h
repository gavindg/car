#ifndef MATRIXHPP
#define MATRIXHPP

#include <stddef.h>
#include "Vector.h"
#include "Pipeline.h"

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

public:
    Matrix(size_t m, size_t n) :  _matr(new T [m * n]), _m(m), _n(n) {}

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

    friend std::ostream & operator<<(std::ostream & os, const Matrix & mat) {
        mat.print(os);
        return os;
    }
};


// TODO: put this in a different file...
class Screen : private Matrix<frag> {
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
    Screen(const struct winsize & sizeInfo) : Matrix<frag>(sizeInfo.ws_row, sizeInfo.ws_col) {
        for (size_t i{0}; i < _m; ++i) {
            for (size_t j{0}; j < _n; ++j) {
                get(i, j) = frag(j, i, ' ');
            }
        }
        guideMarks();
    }

    void draw(std::ostream & where) {
        for (size_t i{0}; i < _m * _n; ++i) {
            if (i != 0 && i % _n == 0) where << '\n';
            if (_matr[i].color != '\0') {
                where << _matr[i].color;
            }
            else where << ' ';
        }
    }

    // TODO make an out-of-bound function

    size_t width() const {
        return Matrix::numCols();
    }

    size_t height() const {
        return Matrix::numRows();
    }

    bool updateFrag(const frag & fragment) {
        // TODO: this should return false if out of bounds
        std::cout << "fragx: " << fragment.x << "; fragy: " << fragment.y << std::endl;
        get(fragment.x, fragment.y).x = fragment.x;
        std::cout << " set y ";
        get(fragment.x, fragment.y).y = fragment.y;
        std::cout << " set color ";
        get(fragment.x, fragment.y).color = fragment.color;
        std::cout << " done ." << std::endl;
        return true;
    }

    const frag & getFrag(size_t i, size_t j) const {
        return get(i, j);
    }
    frag & getFrag(size_t i, size_t j) {
        return get(i, j);
    }
};

#endif
