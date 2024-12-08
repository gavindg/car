#ifndef CPR_DEF_H
#define CPR_DEF_H

#include <stddef.h>
#include <iostream>

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

    frag(size_t x, size_t y, char col, double depth) : x(x), y(y), color(col), depth(depth) {}

    frag(size_t x, size_t y) : x(x), y(y), color('\0'), depth(-1) {}

    frag() : x(0), y(0), color('\0'), depth(-1) {}

    frag(const frag & other) {
        this->x = other.x;
        this->y = other.y;
        this->color = other.color;
        this->depth = other.depth;
    }

    frag & operator=(const frag & other) {
        if (this == &other) return *this;

        this->x = other.x;
        this->y = other.y;
        this->color = other.color;
        this->depth = other.depth;
        
        return *this;
    }

    // for printing
    friend std::ostream & operator<<(std::ostream & os, const frag & f) {
        os << f.color;
        return os;
    }
};


#endif
