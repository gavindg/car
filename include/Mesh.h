#ifndef MESHHPP
#define MESHHPP

#include "Triangle.h"
#include <vector>

class Mesh {
private: 
    std::vector<Triangle> _tris;

public:
    // TODO: convert to just a set of vectors?
    Mesh(std::initializer_list<Triangle> tris) : _tris(tris) {}

    size_t numTriangles() { return _tris.size(); }
    bool insideTriangle(size_t ind, Vector2 pixel) { return _tris[ind].inside(pixel); }
};

#endif
