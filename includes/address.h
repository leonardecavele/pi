#ifndef ADDRESS_H
# define ADDRESS_H

#  include <stdint.h>

#  define REG1B(adr)	(*(volatile uint8_t  *)(uintptr_t)(adr))
#  define REG2B(adr)	(*(volatile uint16_t *)(uintptr_t)(adr))
#  define REG4B(adr)	(*(volatile uint32_t *)(uintptr_t)(adr))
#  define REG8B(adr)	(*(volatile uint64_t *)(uintptr_t)(adr))

#  define IO_BANK0		0x400d0000u

#  define RW_OFFSET		0x0000u
#  define XOR_OFFSET	0x1000u
#  define SET_OFFSET	0x2000u
#  define CLR_OFFSET	0x3000u

void regset_rw32(uintptr_t adr, uint32_t mask, uint32_t v);

# endif
