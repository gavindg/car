#ifndef TRANSFORMATIONS_HPP
#define TRANSFORMATIONS_HPP

#include "Mesh.h"
#include "Vector.h"
#include "Camera.h"

namespace transformations {
    void translate(Mesh & m, const Vector4 & displacement);
    void scale(Mesh & m, const Vector4 & amount);
    void orthographic(Mesh & mesh, const Camera & cam);
    void viewport(Mesh & m, const viewport & vp);

    Matrix4 translationFromVector(const Vector4 & displacement);
    Matrix4 scaleFromVector(const Vector4 & amount);
};

#endif
