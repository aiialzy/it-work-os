#include "math.h"

long pow_l(long x, long y) {
    long r = 1;
    while (y --) {
        r *= x;
    }

    return r;
}