#include <vector>
#include <iostream>
#include <chrono>
#include <thread>
#include "Mesh.h"
#include "Matrix.h"
#include "Pipeline.h"
#include "Transformations.h"
#include "math.h"
#include "Shade.h"

double degToRad(double degrees);    // TODO move this declaraion to a header file somewhere
void untransform(Scene & scene, double angleDelt);  // maybe useless ?

void pipeline::run(Scene & scene, const struct viewport & vp) {
    Screen screen(vp, true);
    double angleDelt{20};
    
    for (int i{0}; i < 37; ++i) {
        std::vector<frag> frags;
        Scene working{scene};

        // pipeline !!
        std::cout << std::endl;
        transform(working, angleDelt * i);
        project(working, vp);
        rasterize(working.mesh, vp, frags);
        shade(frags);
        // system("clear");
        screen.draw(std::cout, frags);
        screen.clear();
        // untransform(working, angleDelt * i);

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void pipeline::shade(std::vector<frag> & frags) {
    for (auto & f : frags) {
        shade::fragment(f);
    }
}

void pipeline::transform(Scene & scene, double angleDelt) {
    // transformations::rotate(scene.mesh, {0, 0, 1}, degToRad(angleDelt));
    Vector4 axis{1, 1, 0};
    axis.normalize();
    transformations::rotate(scene.mesh, axis, degToRad(angleDelt));
    transformations::scale(scene.mesh, {2, 2, 1});
    transformations::translate(scene.mesh, {0, 0, -5});
}

void pipeline::project(Scene & scene, const struct viewport & vp) {
    transformations::orthographic(scene.mesh, scene.camera);
    transformations::viewport(scene.mesh, vp);
}


void pipeline::rasterize(Mesh & m, const struct viewport & vp, std::vector<frag> & frags) {
    ZBuffer zbuf(vp, 2.0);
    // "rasterize" and create a vec of fragments per triangle
    for (size_t triangleInd{0}; triangleInd < m.numTriangles(); ++triangleInd) {
        // get list of frags in the triangle
        for (size_t y{0}; y < vp.height-1; ++y) {
            for (size_t x{0}; x < vp.width; ++x) {
                // test if this point is inside a triangle in this squashed mesh
                Vector2 fragPos{
                    static_cast<double>(x) + 0.5,
                    static_cast<double>(y) + 0.5
                };
                bool inside{m.insideTriangle(triangleInd, fragPos)};
                if (inside) {
                    // find the depth of this frag
                    double depth = std::abs(m.interpolateDepth(triangleInd, fragPos));
                    {
                        if (depth < zbuf.get(y, x)) {
                            // only push a frag if its closer than another frag
                            zbuf.get(y, x) = depth;
                            char color = 0;
                            // if (triangleInd != 0) std::cout << "wow its " << triangleInd << "!!" << std::endl;
                            frags.push_back({x, y, color, depth, triangleInd});
                        }
                    }
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

