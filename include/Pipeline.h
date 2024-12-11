#ifndef PIPELINEDEF_HPP
#define PIPELINEDEF_HPP

#include <iostream>
#include "Mesh.h"
#include "Matrix.h"
#include "Scene.h"
#include "CPRDef.h"

namespace pipeline {
    void run(Scene & scene, const struct viewport & vp);
    // void rasterize(Mesh & m, const struct viewport & vp, std::vector<std::vector<frag>> & frags);
    void rasterize(Mesh & m, const struct viewport & vp, std::vector<frag> & frags);  // , std::vector<std::vector<frag>> & frags) {
    void transform(Scene & scene, double angleDelt);
    void shade(std::vector<frag> & frags);
    void project(Scene & scene, const struct viewport & vp);
}

#endif
