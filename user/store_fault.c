#include "printf.h"

int main() {
    printf("Into Test store_fault, we will insert an invalid store operation...\n");
    printf("Kernel should kill this application!\n");

    int *x;
    *x = 0;

    return 0;
}