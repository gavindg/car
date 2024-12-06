/*
 * CPR (C Plus plus Renderer)
 *
 * TODO LIST
 *
 * TODO TRIANGLES SHOULD BE COUNTERCLOCKWISE
 *
 * TODO move rasterize to Pipeline.h
 *
 * TODO write ZBuffer algorithm
 *
 * TODO perspective projection
 */

#include "Vector.h"
#include "Matrix.h"
#include "Triangle.h"
#include "Mesh.h"

#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>


void rasterize(Screen & screen, Mesh & m);

int main() {
    struct winsize size;    // this should probably be my own struct
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    std::cout << "width: "<< size.ws_col<<  "; height: " <<size.ws_row << std::endl;
    Screen screen{size, true};
    ZBuffer zbuf{size};

    std::cout << "zbuf @ (1,1): " << zbuf.get(1, 1) <<std::endl;

    Triangle myTriangle{Vector2(3, 3), Vector2(65, 6), Vector2(7, 23)};
    Triangle myTriangle2{Vector2(20, 8), Vector2(30, 8), Vector2(25, 20)};

    Mesh m{myTriangle, myTriangle2};

    rasterize(screen, m);
    screen.draw(std::cout);

    return 0;
}

// TODO: move this function to Pipeline.h
void rasterize(Screen & screen, Mesh & m) {
    // todo: make color an element of the mesh...
    
    // "rasterize" and create a vec of fragments per triangle
    std::vector<std::vector<frag>> fragLists;
    for (size_t triangleInd{0}; triangleInd < m.numTriangles(); ++triangleInd) {
        // get list of frags in the triangle
        std::vector<frag> frags;
        for (size_t y{0}; y < screen.height(); ++y) {
            for (size_t x{0}; x < screen.width(); ++x) {
                // test if this point is inside
                // bool success{tri.inside({static_cast<double>(x), static_cast<double>(y)})};
                bool success{m.insideTriangle(triangleInd, {static_cast<double>(x), static_cast<double>(y)})};
                if (success) {
                    // i think usually, you'd want to get a list of the fragments you want to change,
                    // then do some logic on them later. this is fine for now:
                    screen.getFrag(y, x).color = triangleInd == 0 ? 'O' : 'X';
                    frags.push_back(screen.getFrag(y, x));
                }
            }
        }

        // std::cout << "sizeof frags: " << std::size(frags) << std::endl;
        fragLists.push_back(frags);
    }

    // TODO: make this a separate function ?
    // depth buffer algorithm
    
}
