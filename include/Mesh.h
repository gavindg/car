#ifndef MESHHPP
#define MESHHPP

#include "Triangle.h"
#include "Matrix.h"
#include <vector>

class Mesh {
private: 
    std::vector<Vector4> _verts;
    std::vector<size_t> _tris;
    size_t _triCount;

public:
    Mesh() {}       // default constructor
    Mesh(std::initializer_list<Vector4> verts, std::initializer_list<size_t> tris) {
        setVerts(verts);
        setTris(tris);
    }

    Mesh(const Mesh & other) {
        for (Vector4 vert : other._verts) {
            _verts.push_back(vert);
        }
        for (size_t triInd : other._tris) {
            _tris.push_back(triInd);
        }
        _triCount = other._triCount;
    }

    void setVerts(std::initializer_list<Vector4> verts) {
        for (auto it{std::begin(verts)}; it != std::end(verts); ++it) {
            _verts.push_back({*it});     // TODO double check if this is weird
        }
    }

    void setTris(std::initializer_list<size_t> tris) {
        if (tris.size() % 3 != 0) {
            std::cerr << "WRONG SIZED TRIANGLE LIST" << std::endl;
            exit(-1);
        }

        for (auto it{std::begin(tris)}; it != std::end(tris); ++it) {
            _tris.push_back({*it});     // TODO double check if this is weird
        }

        _triCount = tris.size() / 3;
    }

    size_t numTriangles() { return _triCount; }
    size_t numVerts() { return _verts.size(); }

    double interpolateDepth(size_t ind, Vector2 point) {
        size_t startInd{3 * ind};

        Triangle2D toInterp{
            _verts[_tris[startInd]],
            _verts[_tris[startInd+1]],
            _verts[_tris[startInd+2]]
        };

        return toInterp.barycentricInterp(
                point,
                {_verts[_tris[startInd]].z(),
                _verts[_tris[startInd+1]].z(),
                _verts[_tris[startInd+2]].z()
        });
    }

    bool insideTriangle(size_t ind, Vector2 pixel) { 
        size_t startInd{3 * ind};

        // maybe convert to just doin the math here ?
        Triangle2D toCheck{
            {_verts[_tris[startInd]].x(), _verts[_tris[startInd]].y()}, 
            {_verts[_tris[startInd + 1]].x(), _verts[_tris[startInd + 1]].y()}, 
            {_verts[_tris[startInd + 2]].x(), _verts[_tris[startInd + 2]].y()}
        };  // actually get barycentric coords here FIXME !!!!

        /*
        std::cout << "testing Triangle((" << _verts[startInd].x << ',' << _verts[startInd] <<
            '(' << _verts[startInd+1].x << ',' << _verts[startInd+1].y <<')' <<
            '(' << _verts[startInd+2].x << ',' << _verts[startInd+2].y << ")) vs" << pixel << std::endl;
            */
        
        return toCheck.inside({pixel.x() + 0.5, pixel.y() + 0.5}); 
    }

    void applyTransformation(size_t vert, const Matrix4 & transformationMatrix) {
        _verts[vert] = transformationMatrix * _verts[vert];
    }

    void printStatus() {
        std::cout << "hi. I have " << _verts.size() << " vertices and " << _triCount << " tris." << std::endl;
    }

    void printVerts() {
        std::cout << "[";
        for (auto vert : _verts) {
            std::cout << vert << ", ";
        }
        std::cout << std::endl;
    }
};

#endif
