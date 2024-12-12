#ifndef TRIANGLEHPP
#define TRIANGLEHPP

#include "Vector.h"

// used for point-in-triangle test
class Triangle2D {
private:
    Vector2 p1, p2, p3;

    // check if point q is in half plane defined by p1, p2 
    // based on pseudocode from CS112 Lecture 6, slide 27 by Shuang Zhao
    bool inHalfPlane(const Vector2 & a, const Vector2 & b, const Vector2 & q) const {
        return ((a.y() - b.y()) * (q.x() - a.x()))
         + ((b.x() - a.x()) * (q.y() - a.y())) >= 0;
    }

public: 
    Triangle2D(Vector2 point1, Vector2 point2, Vector2 point3) : p1(point1), p2(point2), p3(point3) {};
    Triangle2D(Vector4 point1, Vector4 point2, Vector4 point3) : 
        p1(point1.x(), point1.y()), p2(point2.x(), point2.y()), p3(point3.x(), point3.y()) {};

    double area() const {
        return 0.5 * std::abs(
            p1.x() * (p2.y() - p3.y()) + 
            p2.x() * (p3.y() - p1.y()) +
            p3.x() * (p1.y() - p2.y())
        );
    }

    // based on pseudocode from CS112 lecture 6, slide 33 by Shuang Zhao
    bool inside(const Vector2 & q) const {
        return inHalfPlane(p1, p2, q) &&
            inHalfPlane(p2, p3, q) &&
            inHalfPlane(p3, p1, q);
    }
    
    Vector2 getBarycentric(Vector2 point) const {
        // sub triangles from partitioning
        Triangle2D s0{point, p2, p3};
        Triangle2D s1{point, p3, p1};
        Triangle2D s2{point, p1, p2};

        double greater_area{area()};
        double w1{s1.area() / greater_area};
        double w2{s2.area() / greater_area};

        return {w1, w2};
    }

    // based on the equation from Lecture 8, Slide 41 by Shuang Zhao
    template <typename T>
    T barycentricInterp(Vector2 point, T w0, T w1, T w2) {
        Vector2 bary{getBarycentric(point)};

        return (1 - bary[0] - bary[1]) * w0 +
            bary[0] * w1 +
            bary[1] * w2;
    }

    // based on the equation from lecture 8, slide 48 by Shuang Zhao
    double perspectiveCorrectInterp(Vector2 point, double w0, double w1, double w2) {
        Vector2 bary{getBarycentric(point)};

        return 1 / ((1 - bary[0] - bary[1]) * (1 / w0) +
            bary[0] * (1 / w1) +
            bary[1] * (1 / w2));
    }
};    


#endif
