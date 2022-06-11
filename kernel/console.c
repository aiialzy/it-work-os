#include "console.h"
#include "uart.h"

void consoleputc(char c) {
    uartputc_sync(c);
}

void consoleinit() {
    uartinit();
}