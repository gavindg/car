// TS IS NOT REAL
#include "CPRDef.h"
#include "Shade.h"

void shade::fragment(frag & f) {
    f.color = '0' + f.triangleInd;
}
