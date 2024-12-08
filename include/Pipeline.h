#ifndef PIPELINEDEF_HPP
#define PIPELINEDEF_HPP

#include <iostream>
#include "Mesh.h"
#include "Matrix.h"
#include "Scene.h"
#include "CPRDef.h"

namespace pipeline {
    void run(Scene & scene, const struct viewport & vp);
    void rasterize(Screen & screen, Mesh & m, std::vector<std::vector<frag>> frags);
    void transform(Scene & scene);
    void project(Scene & scene, const struct viewport & vp);
}

#endif
