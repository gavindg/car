#ifndef MESHHPP
#define MESHHPP

#include "Triangle.h"
#include "Matrix.h"
#include "CARDef.h"
#include <vector>
#include <cassert>

class Mesh {
private: 
    std::vector<Vector4> _verts;
    std::vector<size_t> _tris;
    size_t _triCount;

public:
    uniform::materialtype mat;

    Mesh() {}       // default constructor
    Mesh(std::initializer_list<Vector4> verts, std::initializer_list<size_t> tris, uniform::materialtype material) : mat(material) {
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
        mat = other.mat;
    }

    void setVerts(std::initializer_list<Vector4> verts) {
        for (auto it{std::begin(verts)}; it != std::end(verts); ++it) {
            _verts.push_back({*it});
        }
    }

    void setTris(std::initializer_list<size_t> tris) {
        if (tris.size() % 3 != 0) {
            std::cerr << "WRONG SIZED TRIANGLE LIST" << std::endl;
            exit(-1);
        }

        for (auto it{std::begin(tris)}; it != std::end(tris); ++it) {
            _tris.push_back({*it});
        }

        _triCount = tris.size() / 3;
    }

    void validate() {
        // this function can be used to check if a mesh is valid.
        // it is called automatically when a scene is constructed 
        // unless you set the "validate" flag to false when constructing.
        //
        // this function does not check thing such as whether a triangle's
        // vertices are defined in clockwise order or other similar user errors
        // that are sometimes erroneous, but otherwise desired.
        
        assert(_tris.size() % 3 == 0);
        assert(_triCount == _tris.size() / 3);
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

        // return toInterp.barycentricInterp(
        return toInterp.perspectiveCorrectInterp(
            point,
            _verts[_tris[startInd]].z(),
            _verts[_tris[startInd+1]].z(),
            _verts[_tris[startInd+2]].z()
        );
    }

    Vector4 & getVert(size_t ind) {
        return _verts[ind];
    }

    bool insideTriangle(size_t ind, Vector2 pixel) { 
        size_t startInd{3 * ind};

        // maybe convert to just doin the math here ?
        Triangle2D toCheck{
            {_verts[_tris[startInd]].x(), _verts[_tris[startInd]].y()}, 
            {_verts[_tris[startInd + 1]].x(), _verts[_tris[startInd + 1]].y()}, 
            {_verts[_tris[startInd + 2]].x(), _verts[_tris[startInd + 2]].y()}
        };

        return toCheck.inside({pixel.x() + 0.5, pixel.y() + 0.5}); 
    }

    void applyVertexTransformation(size_t vert, const Matrix4 & transformationMatrix) {
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
        std::cout << ']' << std::endl;
    }
};

#endif
