#include "types.h"
#include "uart.c"

void consoleputc(char c) {
    uartputc_sync(c);
}

void consoleinit() {
    uartinit();
}