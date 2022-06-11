#include "uart.h"

#define UART0 0x10000000L

#define Reg(reg) ((volatile unsigned char*)(UART0 + reg))

#define RHR 0
#define THR 0
#define IER 1
#define IER_RX_ENABLE (1 << 0)
#define IER_TX_ENABLE (1 << 1)
#define FCR 2
#define FCR_FIFO_ENABLE (1 << 0)
#define FCR_FIFO_CLEAR (3 << 1)
#define ISR 2
#define LCR 3
#define LCR_EIGHT_BITS (3 << 0)
#define LCR_BAUD_LATCH (1 << 7)
#define LSR 5
#define LSR_RX_READY (1 << 0)
#define LSR_TX_IDLE (1 << 5)

#define ReadReg(reg) (*(Reg(reg)))
#define WriteReg(reg, v) (*(Reg(reg)) = (v))

#define UART_TX_BUF_SIZE 32
char uart_tx_buf[UART_TX_BUF_SIZE];
unsigned long uart_tx_w;
unsigned long uart_tx_r;


void uartinit() {
    WriteReg(IER, 0x00);
    WriteReg(LCR, LCR_BAUD_LATCH);
    WriteReg(0, 0x03);
    WriteReg(1, 0x00);
    WriteReg(LCR, LCR_EIGHT_BITS);
    WriteReg(FCR, FCR_FIFO_ENABLE | FCR_FIFO_CLEAR);
    WriteReg(IER, IER_TX_ENABLE | IER_RX_ENABLE);
}

void uartputc_sync(char c) {
    while ((ReadReg(LSR) & LSR_TX_IDLE) == 0) {
    }
    WriteReg(THR, c);
}

void uartstart() {
    while (1) {
        if (uart_tx_w == uart_tx_r) {
            return;
        }

        if ((ReadReg(LSR) & LSR_TX_IDLE) == 0) {
            return;
        }

        int c = uart_tx_buf[uart_tx_r % UART_TX_BUF_SIZE];
        uart_tx_r += 1;

        WriteReg(THR, c);
    }
}