#ifndef SCENE_HPP
#define SCENE_HPP

#include "Mesh.h"
#include "Camera.h"

class Scene {
public:
    Scene() {}
    Scene(const Mesh & mesh, bool validate=true) : mesh(mesh) {
        if (validate) this->mesh.validate();
    }
    Scene(const Mesh & mesh, Camera cam, bool validate=true) : mesh(mesh), camera(cam) {
        if (validate) this->mesh.validate();
    }

    Mesh mesh;
    Camera camera;
};

#endif
