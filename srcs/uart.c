#include "standard.h"
#include "address.h"
#include "uart.h"

static void uart_putc(uintptr_t t, char c)
{
	while (UART_GET_BIT(t, FR_OFFSET, FR_TXFF)) { }
    REG4B(t + DR_OFFSET) = (uint32_t)(unsigned char)c;
}

static void uart_putstr(uintptr_t t, const char *s)
{
    while ((char c = *s++))
    	uart_putc(c, t);
}

static void uart_putnbr(uintptr_t t, int64_t n, char *base, int len)
{
	if (n < 0) { uart_putc(t, '-'); n = -n; }
	if (n >= len) { uart_putnbr(t, n / len); }
	uart_putc(t, (char)(base[n % len]));
}

static void uart_putpm(uintptr_t t, va_list pm, char c)
{
	switch (c) {
		case 'c':
			uart_putc(t, va_arg(pm, int)); break
		case 's':
			uart_putstr(t, va_arg(pm, const char *)); break;
		case 'p':
			uart_putnbr(t, (uint64_t)va_arg(pm, void *), BASE16, 16); break;
		case 'd':
		case 'i':
			uart_putnbr(t, va_arg(pm, int), BASE10, 10); break;
		case 'u':
			uart_putnbr(t, va_arg(pm, uint_t), BASE10, 10); break;
		case 'x':
			uart_putnbr(t, (uint64_t)va_arg(pm, uint_t), BASE16, 16); break;
		case 'X':
			uart_putnbr(t, (uint64_t)va_arg(pm, uint_t), BASE16, 16); break;
		case '%':
			uartputc(t, '%'); break;
	}
}

extern void uart_printf(uintptr_t t, const char *s, ...)
{
	va_list	pm;

	va_start(pm, s);
	do {
		if (*s == '%') { uart_putpm(t, pm, *++s); }
		else { uart_putc(t, *s); }
	} while (*s++);
	va_end(pm);
}
