#include <vector>
#include <iostream>
#include "Mesh.h"
#include "Matrix.h"
#include "Pipeline.h"
#include "Transformations.h"

void pipeline::run(Scene & scene, Screen & screen) {
    std::vector<std::vector<frag>> frags;
    scene.mesh.printVerts();
    rasterize(screen, scene.mesh, frags);
    screen.draw(std::cout);
    screen.clear();

    /*
    std::cout << "ready to translate?" << std::endl;
    std::cin.ignore();
    
    transformations::translate(scene.mesh, {20, 0, 0});
    rasterize(screen, scene.mesh, frags);
    screen.draw(std::cout);
    */

    std::cout << "ready to scale?" << std::endl;
    std::cin.ignore();
    
    transformations::scale(scene.mesh, {2, 1, 1});
    rasterize(screen, scene.mesh, frags);
    scene.mesh.printVerts();
    screen.draw(std::cout);
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


