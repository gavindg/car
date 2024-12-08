#include <vector>
#include <iostream>
#include "Mesh.h"
#include "Matrix.h"
#include "Pipeline.h"
#include "Transformations.h"
#include "math.h"

double degToRad(double degrees);    // TODO move this declaraion to a header file somewhere

void pipeline::run(Scene & scene, const struct viewport & vp) {
    // FIXME should scene be const ?
    Screen screen(vp);
    std::vector<std::vector<frag>> frags;
    
    // pipeline !!
    transform(scene);
    project(scene, vp);
    rasterize(screen, scene.mesh, frags);
    screen.draw(std::cout);
    screen.clear();
}

void pipeline::transform(Scene & scene) {
    transformations::rotate(scene.mesh, {0, 0, 1}, degToRad(45.0));
    transformations::scale(scene.mesh, {2, 2, 1});
    transformations::translate(scene.mesh, {0, 0, -5});
}

void pipeline::project(Scene & scene, const struct viewport & vp) {
    transformations::orthographic(scene.mesh, scene.camera);
    transformations::viewport(scene.mesh, vp);
}


void pipeline::rasterize(Screen & screen, Mesh & m, std::vector<std::vector<frag>> frags) {
    // "rasterize" and create a vec of fragments per triangle
    std::vector<std::vector<frag>> fragLists;
    for (size_t triangleInd{0}; triangleInd < m.numTriangles(); ++triangleInd) {
        // get list of frags in the triangle
        std::vector<frag> frags;
        for (size_t y{0}; y < screen.height(); ++y) {
            for (size_t x{0}; x < screen.width(); ++x) {
                // test if this point is inside a triangle in this squashed mesh
                bool success{m.insideTriangle(triangleInd, {static_cast<double>(x), static_cast<double>(y)})};
                if (success) {
                    // TODO: move out of rasterize :flush:
                    screen.getFrag(y, x).color = triangleInd == 0 ? '0' : '1';  // TODO: shade me eventually..
                    frags.push_back(screen.getFrag(y, x));
                }
            }
        }
        fragLists.push_back({frags});
    }
    frags = fragLists;
}

// helper

double degToRad(double degrees) {
    return degrees * M_PI / 180.0;
}

// old
//
/*

void pipeline::run(Scene & scene, Screen & screen) {
    std::vector<std::vector<frag>> frags;
    scene.mesh.printVerts();
    rasterize(screen, scene.mesh, frags);
    screen.draw(std::cout);
    screen.clear();
}

 */
