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

#include "Matrix.h"
#include "Scene.h"
#include "Pipeline.h"
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include "Models.h"

int main() {
    struct winsize size;    // this should probably be my own struct
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    viewport vp{size.ws_col, size.ws_row};
    std::cout << "viewport width: " << vp.width << "; viewport height: " << vp.height << std::endl;
    std::cout << "width: "<< size.ws_col<<  "; height: " <<size.ws_row << std::endl;

    // Initialize "Scene"
    Scene scene{models::CANNONICAL_CUBE, Camera(Camera::CENTERED_16_9)};
    pipeline::run(scene, vp);

    return 0;
}
