#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include "Scene.h"
#include "Mesh.h"
#include "Matrix.h"
#include "Pipeline.h"
#include "Transformations.h"
#include "math.h"
#include "Shade.h"

double degToRad(double degrees);

void pipeline::render(const Scene & scene, const struct viewport & vp, Screen & screen) { 
    Scene modifiedScene{scene};
    std::vector<frag> frags;
    uniform uni;
    uni.material = modifiedScene.mesh.mat;

    project(modifiedScene, vp);
    rasterize(modifiedScene.mesh, vp, frags);
    shade(frags, uni);
    draw(screen, frags);
}

void pipeline::render(const Scene & scene, const struct viewport & vp, Screen & screen, std::ofstream * file) { 
    Scene modifiedScene{scene};
    std::vector<frag> frags;
    uniform uni;
    uni.material = modifiedScene.mesh.mat;

    project(modifiedScene, vp);
    rasterize(modifiedScene.mesh, vp, frags);
    shade(frags, uni);
    draw(screen, frags, file);
}

void pipeline::draw(Screen & screen, const std::vector<frag> & frags) {
    screen.draw({&std::cout}, frags);
    screen.clearBuffer();
}

void pipeline::draw(Screen & screen, const std::vector<frag> & frags, std::ofstream * file) {
    if (file->is_open()) 
        screen.draw({&std::cout, file}, frags);
    else
        screen.draw({&std::cout}, frags);
    screen.clearBuffer();
}


void pipeline::run_rotationSample(const Scene & scene, const struct viewport & vp) {
    Screen screen(vp, true);
    double angleDelt{20};
    std::ofstream file;
    file.open("output.txt");
    
    // rotate the mesh 360 degrees, twice.
    for (int i{0}; i < 37; ++i) {
        Scene working{scene};
        transform(working, angleDelt * i);
        render(working, vp, screen, &file);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    file.close();
}

void pipeline::run_oneshot(const Scene & scene, const struct viewport & vp) {
    Screen screen(vp, true);
    Scene working{scene};
    transformations::scale(working.mesh, {2, 2, 2});
    transformations::translate(working.mesh, {0, 0, -5});
    render(working, vp, screen);
}

void pipeline::shade(std::vector<frag> & frags, uniform & uni) {
    double minDepth = 3;
    double maxDepth = -1;

    for (const auto & f : frags) {
        minDepth = std::min(minDepth, f.depth);
        maxDepth = std::max(maxDepth, f.depth);
    }

    uni.maxDepth = 1;
    uni.minDepth = 0;

    for (auto & f : frags) {
        shade::fragment(f, uni);
    }
}

void pipeline::transform(Scene & scene, double angleDelt) {
    Vector4 axis{1, 1, 0};
    axis.normalize();
    transformations::rotate(scene.mesh, axis, degToRad(angleDelt));
    transformations::scale(scene.mesh, {2.5, 2.5, 2.5});
    transformations::translate(scene.mesh, {0, 0, -5});
}

void pipeline::project(Scene & scene, const struct viewport & vp) {
    transformations::orthographic(scene.mesh, scene.camera);
    transformations::viewport(scene.mesh, vp);
}


// based on pseudocode from CS112 Lecture 7, slide 11 by Shaung Zhao
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
                    static_cast<double>(y) - 0.5
                };
                bool inside{m.insideTriangle(triangleInd, fragPos)};
                if (inside) {
                    // find the depth of this frag
                    double depth = std::abs(m.interpolateDepth(triangleInd, fragPos));
                    {
                        if (depth < zbuf.get(y, x)) {
                            // only push a frag if its closer than another frag
                            zbuf.get(y, x) = depth;
                            frags.push_back({x, y, 0, depth, triangleInd});
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
