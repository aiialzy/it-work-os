#include "printf.h"

#define SSTATUS_SPP (1L << 8)  // Previous mode, 1=Supervisor, 0=User

int main() {
    printf("Try to access privileged CSR in U Mode\n");
    printf("Kernel should kill this application!\n");

    unsigned long x;
    asm volatile("csrr %0, sstatus" : "=r" (x) );
    x &= ~SSTATUS_SPP;
    asm volatile("csrw sstatus, %0" : : "r" (x));
    return 0;
}
