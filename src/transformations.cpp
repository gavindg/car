#include "Transformations.h"

// world space transformations

void transformations::translate(Mesh & m, const Vector4 & displacement) {
    // std::cout << " guess who just got called >:] " << std::endl;
    Matrix4 translation;
    translation.set({
        1.0, 0.0, 0.0, displacement.x(),
        0.0, 1.0, 0.0, displacement.y(),
        0.0, 0.0, 1.0, displacement.z(),
        0.0, 0.0, 0.0, 1.0
    });

    for (size_t vertInd{0}; vertInd < m.numVerts(); ++vertInd) {
        m.applyTransformation(vertInd, translation);
    }
}

void transformations::scale(Mesh & m, const Vector4 & amount) {
    Matrix4 scaleMatrix{transformations::scaleFromVector(amount)};

    for (size_t vertInd{0}; vertInd < m.numVerts(); ++vertInd) {
        m.applyTransformation(vertInd, scaleMatrix);
    }
}

void transformations::rotate(Mesh & m, const Vector4 & axis, double degree) {
    Matrix4 rotationMatrix{transformations::rotateFromVector(axis, degree)};

    for (size_t vertInd{0}; vertInd < m.numVerts(); ++vertInd) {
        m.applyTransformation(vertInd, rotationMatrix);
    }
}


// camera transformations

// squish the vertices of mesh into the cannonical cube.
void transformations::orthographic(Mesh & mesh, const Camera & cam) {
    // for scaling
    double two_div_rl{2.0 / (cam.r - cam.l)};
    double two_div_tb{2.0 / (cam.t - cam.b)};
    double two_div_nf{2.0 / (cam.n - cam.f)};
    
    // for translation
    double rl_div_2{(cam.r + cam.l) / -2.0};
    double tb_div_2{(cam.t + cam.b) / -2.0};
    double nf_div_2{(cam.n + cam.f) / -2.0};

    Matrix4 scaleElement{
        scaleFromVector({two_div_rl, two_div_tb, two_div_nf})
    };
    Matrix4 translateElement {
        translationFromVector({rl_div_2, tb_div_2, nf_div_2})
    };

    // in orthographic projection, translate and then scale
    for (size_t vertInd{0}; vertInd < mesh.numVerts(); ++vertInd) {
        mesh.applyTransformation(vertInd, translateElement);
        mesh.applyTransformation(vertInd, scaleElement);
    }
}

// unsquish the vertices of the mesh from the cannonical cube to viewport space
// TODO: change this to properly work with y positive going down!
void transformations::viewport(Mesh & m, const struct viewport & vp) {
    double width_div2{vp.width / 2.0};
    double height_div2{vp.height / 2.0};   // - because in viewport space 

    Matrix4 scaleElement{
        scaleFromVector({width_div2, height_div2, 1, 1})
    };
    Matrix4 translateElement{
        translationFromVector({width_div2, height_div2, 0, 1})
    };

    for (size_t vertInd{0}; vertInd < m.numVerts(); ++vertInd) {
        m.applyTransformation(vertInd, scaleElement);
        m.applyTransformation(vertInd, translateElement);
    }
}


Matrix4 transformations::scaleFromVector(const Vector4 & amount) {
    return {
        amount.x(), 0.0, 0.0, 0.0,
        0.0, amount.y(), 0.0, 0.0,
        0.0, 0.0, amount.z(), 0.0,
        0.0, 0.0, 0.0, 1.0,
    };
}

Matrix4 transformations::translationFromVector(const Vector4 & displacement) {
    return {
        1.0, 0.0, 0.0, displacement.x(),
        0.0, 1.0, 0.0, displacement.y(),
        0.0, 0.0, 1.0, displacement.z(),
        0.0, 0.0, 0.0, 1.0
    };
}

Matrix4 transformations::rotateFromVector(const Vector4 & axis, double degree) {
    // degrees are IN RADIANS
    // this formula for a rotation matrix around an arbitrary axis
    // is based on the one found in the OpenGL documentation: https://learnopengl.com/Getting-started/Transformations
    
    const double cos{std::cos(degree)};
    const double cos1min{1 - std::cos(degree)};
    const double sin{std::sin(degree)};
    const double rx{axis[0]};
    const double ry{axis[1]};
    const double rz{axis[2]};

    return {
        cos + rx*rx*cos1min,    rx*ry*cos1min - rz*sin, rx*rz*cos1min + ry*sin, 0,
        ry*rx*cos1min + rz*sin, cos + ry*ry*cos1min,    ry*rz*cos1min - rx*sin, 0,
        rz*rx*cos1min - ry*sin, rz*ry*cos1min + rx*sin, cos + rz*rz*cos1min,    0,
        0, 0, 0, 1,
    };
}


