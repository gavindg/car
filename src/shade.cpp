// TS IS NOT REAL
#include "CPRDef.h"
#include "Shade.h"

void shade::fragment(frag & f) {
    f.color = f.depth == 1 ? '1' : '0';
}
