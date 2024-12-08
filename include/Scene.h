#ifndef SCENE_HPP
#define SCENE_HPP

#include "Mesh.h"
#include "Camera.h"

class Scene {
public:
    Scene() {}
    Scene(const Mesh & mesh) : mesh(mesh) {}
    Scene(const Mesh & mesh, Camera cam) : mesh(mesh), camera(cam) {}

    Mesh mesh;
    Camera camera;
};

#endif
