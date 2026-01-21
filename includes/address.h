#ifndef ADDRESS_H
# define ADDRESS_H

#  include "standard.h"

/* cast a numeric value as an address */
#  define UADDR(a)		((uintptr_t)(a))

/* rw register at address */
#  define REG1B(a)		(*(volatile uint8_t  *)UADDR((a)))
#  define REG2B(a)		(*(volatile uint16_t *)UADDR((a)))
#  define REG4B(a)		(*(volatile uint32_t *)UADDR((a)))
#  define REG8B(a)		(*(volatile uint64_t *)UADDR((a)))

/* atomic registers */
#  define RW_OFFSET		UADDR(0x0000)
#  define XOR_OFFSET	UADDR(0x1000)
#  define SET_OFFSET	UADDR(0x2000)
#  define CLR_OFFSET	UADDR(0x3000)

# endif
