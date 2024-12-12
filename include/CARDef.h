#ifndef CPR_DEF_H
#define CPR_DEF_H

#include <stddef.h>
#include <iostream>
#include "Vector.h"

struct uniform {
    enum materialtype {TRIANGLE_INDS, DEPTH_BUF};
    double maxDepth;
    double minDepth;
    materialtype material;
};

struct viewport {
    viewport() {}
    constexpr viewport(size_t width, size_t height) : width(width), height(height) {}

    size_t width;
    size_t height;
};

struct camerasize {
    camerasize() {}
    constexpr camerasize(double l, double r, double t, double b, double n, double f) 
    : l(l), r(r), t(t), b(b), n(n), f(f) {}

    double l, r;    // left and right
    double t, b;    // top and bottom
    double n, f;    // near and far: note that far < near < 0 b.c. camera faces -z
};

struct frag {
    size_t x,y;
    char color;
    double depth;
    size_t triangleInd;    // this is used for the debug triangle ind. shader

    frag(size_t x, size_t y, char col, double depth, size_t triangleInd) : x(x), y(y), color(col), depth(depth), triangleInd(triangleInd) {}

    frag(size_t x, size_t y, char col, double depth) : x(x), y(y), color(col), depth(depth), triangleInd(8) {}

    frag(size_t x, size_t y) : x(x), y(y), color('\0'), depth(-1), triangleInd(8) {}

    frag() : x(0), y(0), color('\0'), depth(-1), triangleInd(8) {}

    frag(const frag & other) {
        this->x = other.x;
        this->y = other.y;
        this->color = other.color;
        this->depth = other.depth;
        this->triangleInd = other.triangleInd;
    }

    frag & operator=(const frag & other) {
        if (this == &other) return *this;

        this->x = other.x;
        this->y = other.y;
        this->color = other.color;
        this->depth = other.depth;
        this->triangleInd = other.triangleInd;
        
        return *this;
    }

    // for printing
    friend std::ostream & operator<<(std::ostream & os, const frag & f) {
        os << f.color;
        return os;
    }
};


#endif
