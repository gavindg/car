#ifndef PIPELINEDEF_HPP
#define PIPELINEDEF_HPP

#include <iostream>
#include "Mesh.h"
#include "Matrix.h"
#include "Scene.h"

namespace pipeline {
    void run(Scene & scene, Screen & screenFrame);
    void rasterize(Screen & screen, Mesh & m, std::vector<std::vector<frag>> frags);
}

#endif
