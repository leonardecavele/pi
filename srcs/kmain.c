#include "rp1.h"
#include "uart.h"
#include "bcm2712.h"
#include "dtb.h"

/*	to do :
	PCIe BCM2712
	RP1
	read BAR1
*/

static void	turn_on(uint32_t GPIO)
{
	/* IO BANK0 */
	REG4B(RP1_GPIO_CTRL(GPIO) + CLR_OFFSET) =
		/* clear */
		FUNCSEL_MASK
		| OUTOVER_MASK
		| OEOVER_MASK;
	REG4B(RP1_GPIO_CTRL(GPIO) + SET_OFFSET) =
		/* new value */
		5u << FUNCSEL_SHIFT;

	/* RIO */
	/* output value */
	REG4B(SYS_RIO0 + OUT_OFFSET + CLR_OFFSET) = (1u << GPIO);
	/* output enable */
	REG4B(SYS_RIO0 + OE_OFFSET + SET_OFFSET) = (1u << GPIO);

	/* PADS */
	/* 3.3v */
	REG4B(PADS_BANK0 + CLR_OFFSET) = 0x1u;
	/* select mA */
	REG4B(RP1_PADS_GPIO(GPIO) + CLR_OFFSET) =
		/* clear */
		DRIVE_MASK
		/* output enable */
		| (1u << OD_SHIFT);
	REG4B(RP1_PADS_GPIO(GPIO) + SET_OFFSET) =
		/* set to 4mA */
		1u << DRIVE_SHIFT;
}

int kmain(uintptr_t dtb)
{
	uart_printf(BCM2712_UART, "hello %s\r\n", "world");

	//dtb_check(dtb);

	turn_on(23, rp1);

	/* cpu hang */
	while (1) {}
}
