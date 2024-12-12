#ifndef PIPELINEDEF_HPP
#define PIPELINEDEF_HPP

#include <iostream>
#include "Mesh.h"
#include "Matrix.h"
#include "Scene.h"
#include "CARDef.h"

namespace pipeline {
    void run_rotationSample(const Scene & scene, const struct viewport & vp);
    void run_oneshot(const Scene & scene, const struct viewport & vp);
    void render(const Scene & scene, const struct viewport & vp, Screen & screen);
    void render(const Scene & scene, const struct viewport & vp, Screen & screen, std::ofstream * file);
    void rasterize(Mesh & m, const struct viewport & vp, std::vector<frag> & frags);
    void transform(Scene & scene, double angleDelt);
    void shade(std::vector<frag> & frags, uniform & uni);
    void project(Scene & scene, const struct viewport & vp);
    void draw(Screen & screen, const std::vector<frag> & frags);
    void draw(Screen & screen, const std::vector<frag> & frags, std::ofstream * file);
}

#endif
