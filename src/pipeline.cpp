#include <vector>
#include <iostream>
#include "Mesh.h"
#include "Matrix.h"
#include "Pipeline.h"
#include "Transformations.h"

void pipeline::run(Scene & scene, const struct viewport & vp) {
    std::cout << "running in a viewport with height " << vp.height << " and width " << vp.width << std::endl;
    Screen screen(vp);
    std::vector<std::vector<frag>> frags;
    
    // pipeline !!
    transformations::orthographic(scene.mesh, scene.camera);
    transformations::viewport(scene.mesh, vp);
    rasterize(screen, scene.mesh, frags);
    screen.draw(std::cout);
    screen.clear();
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
