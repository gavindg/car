#ifndef VECTORHPP
#define VECTORHPP

#include <cmath>
#include <iostream>

class Vector {
public:
    double x;
    double y;
    double z;
    double w;

    Vector(double x, double y, double z, double w=0) 
        : x(x), y(y), z(z), w(w) {}

    double magnitude() const {
        return std::sqrt((x * x) + (y * y) + (z * z));
    }

    bool operator==(const Vector & to) const {
        // todo: fix ts
        // note: i think this is more complicated than it seems...
        // because of the 'w' dimension
        return x == to.x &&
            y == to.y &&
            z == to.z;
    }

    Vector operator+(const Vector & that) const {
        return Vector(this->x + that.x,
                this->y + that.y,
                this->z + that.z);
    }

    Vector operator-(const Vector & that) const {
        return Vector(this->x - that.x,
                this->y - that.y,
                this->z - that.z);
    }

    /* this needs to be friend or else it cant view the members on vec !
     * though honestly why this doesn't just operate on 'this' is weird... */
    friend std::ostream & operator<<(std::ostream & os, const Vector & vec) {
        os << '(' << vec.x << ", " << vec.y << ", " << vec.z << ')';
        return os;
    }

};


class VMath {
public:
    static double distanceTo(const Vector & from, const Vector & to) {
        return std::sqrt(
            std::pow(to.x - from.x, 2) +
            std::pow(to.y - from.y, 2) +
            std::pow(to.z - from.z, 2)
        );
    }

    VMath() = delete;
};

#endif
