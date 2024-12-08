#include <vector>
#include <iostream>
#include <chrono>
#include <thread>

#include "Mesh.h"
#include "Matrix.h"
#include "Pipeline.h"
#include "Transformations.h"
#include "math.h"

double degToRad(double degrees);    // TODO move this declaraion to a header file somewhere
void untransform(Scene & scene, double angleDelt);  // maybe useless ?

void pipeline::run(Scene & scene, const struct viewport & vp) {
    Screen screen(vp, true);
    double angleDelt{10};
    
    for (int i{0}; i < 19; ++i) {
        std::vector<frag> frags;
        Scene working{scene};

        // pipeline !!
        std::cout << std::endl;
        transform(working, angleDelt * i);
        project(working, vp);
        rasterize(working.mesh, vp, frags);
        system("clear");
        screen.draw(std::cout, frags);
        screen.clear();
        // untransform(working, angleDelt * i);

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void pipeline::transform(Scene & scene, double angleDelt) {
    transformations::rotate(scene.mesh, {0, 0, 1}, degToRad(angleDelt));
    transformations::scale(scene.mesh, {2, 2, 1});
    transformations::translate(scene.mesh, {0, 0, -5});
}

void pipeline::project(Scene & scene, const struct viewport & vp) {
    transformations::orthographic(scene.mesh, scene.camera);
    transformations::viewport(scene.mesh, vp);
}


void pipeline::rasterize(Mesh & m, const struct viewport & vp, std::vector<frag> & frags) {
    ZBuffer zbuf(vp);
    // "rasterize" and create a vec of fragments per triangle
    for (size_t triangleInd{0}; triangleInd < m.numTriangles(); ++triangleInd) {
        // get list of frags in the triangle
        for (size_t y{0}; y < vp.height-1; ++y) {
            for (size_t x{0}; x < vp.width; ++x) {
                // test if this point is inside a triangle in this squashed mesh
                bool inside{m.insideTriangle(triangleInd, {static_cast<double>(x), static_cast<double>(y)})};
                if (inside) {
                    // TODO: check depth buffer
                    
                    char color = triangleInd == 0 ? '0' : '1';
                    double depth = -1;  // FIXME
                    frags.push_back({x, y, color, depth});
                }
            }
        }
    }
}


// helper

double degToRad(double degrees) {
    return degrees * M_PI / 180.0;
}

void untransform(Scene & scene, double angleDelt) {
    transformations::translate(scene.mesh, {0, 0, 5});
    transformations::scale(scene.mesh, {0.5, 0.5, 1});
    transformations::rotate(scene.mesh, {0, 0, 1}, -degToRad(angleDelt));
}

