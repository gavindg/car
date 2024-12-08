/*
 * CPR (C Plus plus Renderer)
 *
 * TODO LIST
 *
 *
 * TODO move rasterize to Pipeline.h
 *
 * TODO write ZBuffer algorithm
 *
 * TODO perspective projection
 */

#include "Vector.h"
#include "Matrix.h"
#include "Scene.h"
#include "Pipeline.h"
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include "Models.h"
#include "Transformations.h"

int main() {
    struct winsize size;    // this should probably be my own struct
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    viewport vp{size.ws_col, size.ws_row};
    std::cout << "viewport width: " << vp.width << "; viewport height: " << vp.height << std::endl;
    std::cout << "width: "<< size.ws_col<<  "; height: " <<size.ws_row << std::endl;

    // Initialize "Scene"
    Scene scene{models::CANNONICAL_CUBE, Camera(Camera::CENTERED_16_9)};
    transformations::scale(scene.mesh, {2, 2, 1});
    transformations::translate(scene.mesh, {0, 0, -5});
    // Scene scene{models::DEFAULT_CUBE, Camera(Camera::CENTERED_16_9)};
    pipeline::run(scene, vp);

    // transformations::scale(scene.mesh, {20, -20, 1});
    

    /*
    scene.mesh.setVerts({       // points need imaginary elem w=1.
        Vector4(3, 3, -5, 1),
        Vector4(7, 23, -5, 1),
        Vector4(65, 6, -5, 1),
        Vector4(53, 27, -5, 1),
    });

    scene.mesh.setTris({
        0, 1, 2,
        3, 2, 1,
    });
    */

    return 0;
}

    /*
    scene.mesh.setVerts({
        Vector4(6, 6, -5, 0),
        Vector4(6, 26, -5, 0),
        Vector4(26, 6, -5, 0),
        Vector4(26, 26, -5, 0),
    });
    */
