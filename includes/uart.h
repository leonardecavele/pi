#ifndef UART_H
# define UART_H

#  include "standard.h"
#  include "address.h"
#  include "bcm2712.h"

   /* get bit 'c' from uart register 'a' + offset 'b' */
#  define UART_GET_BIT(a, b, c) \
    ((REG4B((a) + (b)) >> (uint32_t)(c)) & 1u)

typedef enum e_uart_offset {
    DR_OFFSET = 0x00u,
    FR_OFFSET = 0x18u
} t_a_offset;

typedef enum e_uart_fr_bit {
    FR_TXFF = 5
} t_a_fr_bit;

void uart_putstr(const char *s, uintptr_t target);

#endif
