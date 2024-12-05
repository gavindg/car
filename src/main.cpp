/*
 * CPR (C Plus plus Renderer)
 *
 * TODO LIST
 *
 * TODO TRIANGLES SHOULD BE COUNTERCLOCKWISE
 */

#include "Vector.h"
#include "Matrix.h"
#include "Triangle.h"

#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>


void rasterize(Screen & screen, std::vector<Triangle> tris);

int main() {
    struct winsize size;    // this should probably be my own struct
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    std::cout << "width: "<< size.ws_col<<  "; height: " <<size.ws_row << std::endl;
    Screen screen{size};

    Triangle myTriangle{Vector2(3, 3), Vector2(65, 6), Vector2(7, 23)};
    Triangle myTriangle2{Vector2(20, 8), Vector2(30, 8), Vector2(25, 20)};

    rasterize(screen, {myTriangle, myTriangle2});
    //rasterize(screen, {myTriangle, });
    screen.draw(std::cout);

    return 0;
}

void rasterize(Screen & screen, std::vector<Triangle> tris) {
    // todo: make color an element of the mesh...
    int colorDecider = 0;
    for (const auto & tri : tris) {
        ++colorDecider;
        // get list of frags in the triangle
        std::vector<frag> frags;
        for (size_t y{0}; y < screen.height(); ++y) {
            for (size_t x{0}; x < screen.width(); ++x) {
                // test if this point is inside
                bool success{tri.inside({static_cast<double>(x), static_cast<double>(y)})};
                if (success) {
                    // i think usually, you'd want to get a list of the fragments you want to change,
                    // then do some logic on them later. this is fine for now:
                    screen.getFrag(y, x).color = colorDecider == 1 ? '1' : '2';
                    frags.push_back(screen.getFrag(y, x));
                }
            }
        }

        std::cout << "sizeof frags: " << std::size(frags) << std::endl;
        // for (auto fragment : frags) {
        //     std::cout << "fragx: " << fragment.x << "; fragy: " << fragment.y << std::endl;
        //     screen.updateFrag(fragment);
        // }
    }
}
