#include "standard.h"
#include "address.h"
#include "uart.h"

static void uart_putc(char c, uintptr_t target)
{
	while (UART_GET_BIT(target, FR_OFFSET, FR_TXFF)) { }
    REG4B(target + DR_OFFSET) = (uint32_t)(unsigned char)c;
}

extern void uart_putstr(const char *s, uintptr_t target)
{
    while (*s) {
        char c = *s++;
        if (c == '\n')
            uart_putc('\r', target);
        uart_putc(c, target);
    }
}
