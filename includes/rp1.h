#ifndef RP1_H
#define RP1_H

#include "standard.h"
#include "address.h"

//#define RP1_BASE	UADDR(0x1F00000000ull)
#define RP1_BASE	UADDR(0x1F02000000ull)

/* base addresses */
#define IO_BANK0    UADDR(RP1_BASE + 0x000d0000ull)
#define SYS_RIO0    UADDR(RP1_BASE + 0x000e0000ull)
#define PADS_BANK0  UADDR(RP1_BASE + 0x000f0000ull)

#include "rp1_rio.h"
#include "rp1_gpio.h"
#include "rp1_pads.h"

#endif
