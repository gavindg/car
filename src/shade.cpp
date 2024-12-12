#include "CARDef.h"
#include "Shade.h"

// fragment shader declarations
void index_frag(frag & f);
void depth_buf(frag & f, const uniform & uni);

void shade::fragment(frag & f, const uniform & uni) {
    switch (uni.material) {
        case uniform::materialtype::DEPTH_BUF:
            depth_buf(f, uni);
            break;
        case uniform::materialtype::TRIANGLE_INDS:
            index_frag(f);
            break;
    }
}

// fragment shader definitions

void index_frag(frag & f) {
    // this shader assigns a unique character to each triangle,
    // starting at 0, then 1, etc.
    // of course, once you go past '9', it starts to display
    // them as other ascii characters, such as ';' and ':'.
    // this is okay, as the point isn't really to label the 
    // triangles as much as it is to differentiate them from one another.
    f.color = '0' + f.triangleInd;
}

void depth_buf(frag & f, const uniform & uni) {
    if (f.depth < (uni.maxDepth - uni.minDepth) / 4 + uni.minDepth - 0.01) f.color = '.';
    else if (f.depth < (uni.maxDepth - uni.minDepth) / 2 + uni.minDepth - 0.01) f.color = ':';
    else if (f.depth < 3 * (uni.maxDepth - uni.minDepth) / 4 + uni.minDepth - 0.01) f.color = '+';
    else f.color = 'O';
}
