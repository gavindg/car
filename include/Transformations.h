#ifndef TRANSFORMATIONS_HPP
#define TRANSFORMATIONS_HPP

#include "Mesh.h"
#include "Vector.h"
#include "Camera.h"

namespace transformations {
    // world-space transformations
    void translate(Mesh & m, const Vector4 & displacement);
    void scale(Mesh & m, const Vector4 & amount);
    void rotate(Mesh & m, const Vector4 & axis, double degree);

    Matrix4 translationFromVector(const Vector4 & displacement);
    Matrix4 scaleFromVector(const Vector4 & amount);
    Matrix4 rotateFromVector(const Vector4 & axis, double degree);

    // camera transformations
    void orthographic(Mesh & mesh, const Camera & cam);
    void viewport(Mesh & m, const struct viewport & vp);

};

#endif
