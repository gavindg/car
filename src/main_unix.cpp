/*
 * CAR (C++ ASCII Renderer)
 *
 * written by Gavin Gee
 */

#include "Scene.h"
#include "Pipeline.h"
#include <sys/ioctl.h>
#include <unistd.h>
#include "Models.h"
#include "CARDef.h"
#include <string>

int main(int argc, char* argv[]) {
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    viewport vp{size.ws_col, size.ws_row};


    int sceneNumber{0};
    if (argc > 3) {
        std::cerr << "Expected 2 arguments and got " << argc-1 << std::endl;
        std::cerr << "Format:\n\t./car SCENE_NUMBER MATERIAL_TYPE" << 
            "\tSCENE_NUMBER is an integer. scene 0 is the rotating cube scene, scene 1 is the depth resolution example." << std::endl <<
            "\tMATERIAL_TYPE is a string, either 'tris' or 'depth'." << std::endl <<
            "\tdefault (no arguments) is the same as running ./car 0 tris" << std::endl;
        exit(1);
    }
    if (argc > 1) {
        try {
            sceneNumber = std::stoi(argv[1]);
        }
        catch (std::invalid_argument e) {
            std::cerr << "Please input an integer, either 0 or 1 (default 0)" << std::endl;
            exit(1);
        }
    }
    uniform::materialtype mat = uniform::materialtype::TRIANGLE_INDS;
    if (argc > 2) {
        if (std::string(argv[2]) == "tris")
            mat = uniform::materialtype::TRIANGLE_INDS;
        else if (std::string(argv[2]) == "depth") 
            mat = uniform::materialtype::DEPTH_BUF;
        else {
            std::cerr << "Please input a valid material type ('tris' or 'depth', default is 'tris')." << std::endl;
            exit(1);
        }
    }

    switch (sceneNumber) {
        case 0:
            {
                Scene scene{models::CANONICAL_CUBE, Camera(Camera::CENTERED_16_9)};
                scene.mesh.mat = mat;
                pipeline::run_rotationSample(scene, vp);
            }
            break;
        case 1:
            {
                Scene scene{models::DEPTH_ORDER_TEST, Camera(Camera::CENTERED_16_9)};
                scene.mesh.mat = mat;
                pipeline::run_oneshot(scene, vp);
            }
            break;
    }

    return 0;
}
