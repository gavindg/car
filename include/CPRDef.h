#ifndef CPR_DEF_H
#define CPR_DEF_H

#include <stddef.h>
#include <iostream>

struct viewport {
    size_t width;
    size_t height;
};

struct frag {
    char color;
    size_t x,y;
    double depth;

    frag(size_t x, size_t y, char col, double depth) {
        frag(x, y);
        this->color = col;
        this->depth = depth;
    }

    frag(size_t x, size_t y) {
        this->x = x;
        this->y = y;
        color = '\0';
        depth = -1;
    }

    // should this b illegal ?
    frag() {
        frag(0, 0);
    }

    frag(const frag & other) {
        this->x = other.x;
        this->y = other.y;
        this->color = other.color;
    }

    frag & operator=(const frag & other) {
        if (this == &other) return *this;

        this->x = other.x;
        this->y = other.y;
        this->color = other.color;
        
        return *this;
    }

    // for printing
    friend std::ostream & operator<<(std::ostream & os, const frag & f) {
        os << f.color;
        return os;
    }
};


#endif
