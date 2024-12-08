#ifndef TRIANGLEHPP
#define TRIANGLEHPP

#include "Vector.h"

// used for point-in-triangle test
class Triangle2D {
private:
    Vector2 p1, p2, p3;

    // check if point q is in half plane defined by p1, p2
    bool inHalfPlane(const Vector2 & a, const Vector2 & b, const Vector2 & q) const {
        return ((a.y() - b.y()) * (q.x() - a.x()))
         + ((b.x() - a.x()) * (q.y() - a.y())) >= 0; // TODO double check if this should be >
    }

public: 
    Triangle2D(Vector2 point1, Vector2 point2, Vector2 point3) : p1(point1), p2(point2), p3(point3) {};

    bool inside(const Vector2 & q) const {
        return inHalfPlane(p1, p2, q) &&
            inHalfPlane(p2, p3, q) &&
            inHalfPlane(p3, p1, q);
    }
};

class Triangle3D {
private:
     Vector4 p1, p2, p3;

public:
    Triangle3D(Vector4 point1, Vector4 point2, Vector4 point3) : p1(point1), p2(point2), p3(point3) {};

    

};


#endif
