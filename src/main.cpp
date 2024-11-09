/*
 * CPR (C Plus plus Renderer)
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

    rasterize(screen, {myTriangle});
    screen.draw(std::cout);

    return 0;
    // std::cout << "-----" << std::endl;

    // Triangle myTri{Vector2(0, 0), Vector2(1, 0), Vector2(0, 1)};

    // std::cout << Vector2(0.3, 0.3) << " in tri: " << (myTri.inside({0.3, 0.3}) ? "pass" : "fail") << std::endl;
    // std::cout << Vector2(1, 1) << " in tri: " << (!myTri.inside({1, 1}) ? "pass" : "fail") << std::endl;
    
    // Vector2 v1 = {0, 1};
    // Vector2 v2 = {1, 1};
    // Vector2 v3 = {1, 0};

    // Matrix matt{4, 4};
    // matt.set({
    //     0, 1, 2, 3,
    //     4, 5, 6, 7, 
    //     8, 9, 10, 11,
    //     12, 13, 14, 15,
    // });

    // std::cout << "Vector v1: " << v1 << std::endl;
    // std::cout << "Vector v2: " << v2 << std::endl;
    // std::cout << "Vector v3: " << v3 << std::endl;

    // std::cout << "Matrix matt: " << matt << std::endl;

    // double dist = VMath::distance(v1, v2);
    // double dist2 = VMath::distance(v1, v3);
    // double dist3 = VMath::distance(v2, v3);

    // std::cout << "Distance from v1 to v2: " << dist << std::endl;
    // std::cout << "Distance from v1 to v3: " << dist2 << std::endl;
    // std::cout << "Distance from v2 to v3: " << dist3 << std::endl;

}

void rasterize(Screen & screen, std::vector<Triangle> tris) {
    for (const auto & tri : tris) {
        // get list of frags in the triangle
        std::vector<frag> frags;
        for (size_t y{0}; y < screen.height(); ++y) {
            for (size_t x{0}; x < screen.width(); ++x) {
                // test if this point is inside
                bool success{tri.inside({static_cast<double>(x), static_cast<double>(y)})};
                if (success) {
                    // i think usually, you'd want to get a list of the fragments you want to change,
                    // then do some logic on them later. this is fine for now:
                    screen.getFrag(y, x).color = 'O';
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
