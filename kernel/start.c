#include "types.h"
#include "defs.h"
#include "log.c"

void skernel();
void ekernel();
void stext();
void etext();
void srodata();
void erodata();
void sdata();
void edata();
void sbss();
void ebss();

void clear_bss() {
    for (void *p = &sbss; p < (void *)(&ebss); p++) {
        *(byte *)p = 0;
    }
}

void print_memory_layout() {
    error("skernel: %p", &skernel);
    warn("stext: %p, etext: %p", &stext, &etext);
    info("srodata: %p, erodata: %p", &srodata, &erodata);
    debug("sdata: %p, edata: %p", &sdata, &edata);
    trace("sbss: %p, ebss: %p", &sbss, &ebss);
    info("ekernel: %p", &ekernel);
}

void _start() {
    consoleinit();
    printfinit();
    clear_bss();

    print_memory_layout();

    printf("Hello, world!");

    while (1) {
    }
}