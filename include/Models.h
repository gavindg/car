#ifndef MODELS_HPP
#define MODELS_HPP

#include "Mesh.h"

namespace models {
    const Mesh TEST_PLANE {
        {   // verts 
            Vector4(7, 23, -5, 1),
            Vector4(3, 3, -5, 1),
            Vector4(65, 6, -5, 1),
            Vector4(53, 27, -5, 1),
        },
        {   // tris
            0, 1, 2,
            0, 2, 3,
        }
    };

    const Mesh TEST_OVERLAPPING_TRIS {
        {   // verts 
            Vector4(7, 23, -5, 1),
            Vector4(3, 3, -5, 1),
            Vector4(65, 6, -5, 1),
            Vector4(53, 27, -5, 1),
        },
        {   // tris
            0, 1, 2,
            3, 1, 2,
        }
    };

    const Mesh CANNONICAL_CUBE {
        // verts
        {
            Vector4(-1, 1, 1, 1),
            Vector4(-1, -1, 1, 1),
            Vector4(1, 1, 1, 1),
            Vector4(1, -1, 1, 1),
        },
        // tris
        {
            0, 1, 2,
            2, 1, 3,
        },
    };
};

#endif
