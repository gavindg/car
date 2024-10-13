/*
 * CPR (C Plus plus Renderer)
 *
 */

#include "Vector.h"
#include <iostream>

int main() {
    Vector v1 = {0, 1, 0};
    Vector v2 = {0, 2, 0};
    Vector v3 = {7, 3, 8};

    std::cout << "Vector v1: " << v1 << std::endl;
    std::cout << "Vector v2: " << v2 << std::endl;
    std::cout << "Vector v3: " << v3 << std::endl;

    double dist = VMath::distanceTo(v1, v2);
    double dist2 = VMath::distanceTo(v1, v3);

    std::cout << "Distance from v1 to v2: " << dist << std::endl;
    std::cout << "Distance from v1 to v3: " << dist2 << std::endl;

    return 0;
}
