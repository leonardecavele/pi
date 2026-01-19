#include "address.h"
#include "gpio.h"
#include "rio.h"
#include "pads.h"

/*	to do :
	use enums etc to have a single variable replacing '23'
	PCIe BCM2712
	RP1
	read BAR1 or/and BAR2
*/

int kmain(void)
{
	/* IO BANK0 */
	REG4B(IO_BANK0 + GPIO23_CONTROL + CLR_OFFSET) = 
		/* clear */
		GPIO_CONTROL_FUNCSEL_MASK
		| GPIO_CONTROL_OUTOVER_MASK
		| GPIO_CONTROL_OEOVER_MASK;
	REG4B(IO_BANK0 + GPIO23_CONTROL + SET_OFFSET) = 
		/* new value */
		5u << GPIO_CONTROL_FUNCSEL_OFFSET;

	/* RIO */
	/* output enable */
	REG4B(SYS_RIO0 + RIO_OE + SET_OFFSET) = (1u << 23u);
	/* output value */
	REG4B(SYS_RIO0 + RIO_OUT + CLR_OFFSET) = (1u << 23u);

	/* PADS */
	/* 3.3v */
	REG4B(PADS_BANK0 + CLR_OFFSET) = 0x1u;
	/* select mA */
	REG4B(PADS_BANK0 + PADS_GPIO23_OFFSET + CLR_OFFSET) = 
		/* clear */
		PADS_DRIVE_MASK
		/* output enable */
		| 1u << PADS_OD_OFFSET;
	REG4B(PADS_BANK0 + PADS_GPIO23_OFFSET + SET_OFFSET) =
		/* set to 4mA */
		1u << PADS_DRIVE_OFFSET;

	/* cpu hang */
	while (1) { }
}
