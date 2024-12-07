#ifndef SCENE_HPP
#define SCENE_HPP

#include "Mesh.h"
#include "Camera.h"

class Scene {
public:
    Scene() {}
    Scene(const Mesh & mesh) : mesh(mesh) {}

    Mesh mesh;
    Camera camera;
};

#endif
