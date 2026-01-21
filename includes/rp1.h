#ifndef RP1_H
# define RP1_H

#  include "standard.h"
#  include "address.h"

#  define IO_BANK0		UADDR(0x400d0000ull)
#  define SYS_RIO0		UADDR(0x400e0000ull)
#  define PADS_BANK0	UADDR(0x400f0000ull)

#  include "rp1_rio.h"
#  include "rp1_gpio.h"
#  include "rp1_pads.h"

uint64_t rp1_get_bar1_base_from_dtb(const void *dtb);

#endif
