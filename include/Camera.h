#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Vector.h"

// TODO: implement me !
class Camera {
public:
    Camera() {} // default constructor TODO get rid of this...
    Camera(double left, double right, double top, double bottom, double far, double near)
        : l(left), r(right), t(top), b(bottom), f(far), n(near) {}

    const Vector4 UP{0, 1, 0};
    const Vector4 LOOK{0, 0, -1};

    // this is an orthographic camera
    // view frustrum bounds:
    double l, r;    // left and right
    double t, b;    // top and bottom
    double f, n;    // near and far: note that far < near < 0 b.c. camera faces -z
};

#endif
