#include "printf.h"

int main() {
    printf("Try to execute privileged instruction in U Mode\n");
    printf("Kernel should kill this application!\n");

    asm("sret");

    return 0;
}