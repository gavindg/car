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
        // when rasterized, triangle 0 should be rendered above
        // triangle 1 with depth buffer resolution
        {   // verts 
            Vector4(7, 23, 0, 1),
            Vector4(3, 3, 0, 1),
            Vector4(65, 6, -1, 1),
            Vector4(53, 27, -1, 1),
        },
        {   // tris
            0, 1, 2,
            3, 1, 2,
        }
    };

    const Mesh CANNONICAL_CUBE_FRONT {
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

    const Mesh CANNONICAL_CUBE {
        // verts
        {
            Vector4(-1,  1,  1, 1),  // 0
            Vector4(-1, -1,  1, 1),  // 1
            Vector4( 1,  1,  1, 1),  // 2
            Vector4( 1, -1,  1, 1),  // 3
            Vector4(-1,  1, -1, 1),  // 4
            Vector4(-1, -1, -1, 1),  // 5
            Vector4( 1,  1, -1, 1),  // 6
            Vector4( 1, -1, -1, 1),  // 7
        },

        // tris
        {
            // front
            0, 1, 2,
            2, 1, 3,
            // back
            6, 7, 4,
            4, 7, 5,
            // left
            4, 5, 0,
            0, 5, 1,
            // right
            2, 3, 6,
            6, 3, 7,
            // top
            0, 2, 4,
            4, 2, 6,
            // bottom
            1, 5, 3,
            3, 5, 7,
        },
    };


};

#endif
