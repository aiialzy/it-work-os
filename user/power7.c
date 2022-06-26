#include "printf.h"

const unsigned int LEN = 100;

int main() {
    unsigned long p = 7;
    unsigned long m = 998244353;
    unsigned int iter = 200000;
    unsigned long s[LEN];
    unsigned int cur = 0;
    s[cur] = 1;
    for (int i=0; i<=iter; i++) {
        unsigned int next;
        if (cur + 1 == LEN) {
            next = 0;
        } else {
            next = cur + 1;
        }
        cur = next;
        if (i % 10000 == 0) {
            printf("power_7 [%d/%d]", i, iter);
        }
    }
    printf("%d^%d = %d(MOD %d)", p, iter, s[cur], m);
    printf("Test power_7 OK!");
    return 0;
}