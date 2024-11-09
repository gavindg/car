#ifndef PIPELINEHPP
#define PIPELINEHPP

#include <iostream>

struct frag {
    char color;   // this is dumb
    size_t x,y;

    frag(size_t x, size_t y, char col) {
        frag(x, y);
        this->color = col;
    }

    frag(size_t x, size_t y) {
        this->x = x;
        this->y = y;
        color = '\0';
    }

    frag() {
        frag(0, 0, '\0');
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