#include "Transformations.h"

// world space transformations

void transformations::translate(Mesh & m, const Vector4 & displacement) {
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

