#include "rp1.h"
#include "uart.h"
#include "bcm2712.h"

/*	to do :
	PCIe BCM2712
	RP1
	read BAR1
*/

static void	turn_on(uint32_t GPIO, uint64_t rp1)
{
	/* IO BANK0 */
	REG4B(rp1 + RP1_GPIO_CTRL(GPIO) + CLR_OFFSET) =
		/* clear */
		FUNCSEL_MASK
		| OUTOVER_MASK
		| OEOVER_MASK;
	REG4B(rp1 + RP1_GPIO_CTRL(GPIO) + SET_OFFSET) =
		/* new value */
		5u << FUNCSEL_SHIFT;

	/* RIO */
	/* output enable */
	REG4B(rp1 + SYS_RIO0 + OE_OFFSET + SET_OFFSET) = (1u << GPIO);
	/* output value */
	REG4B(rp1 + SYS_RIO0 + OUT_OFFSET + CLR_OFFSET) = (1u << GPIO);

	/* PADS */
	/* 3.3v */
	REG4B(rp1 + PADS_BANK0 + CLR_OFFSET) = 0x1u;
	/* select mA */
	REG4B(rp1 + RP1_PADS_GPIO(GPIO) + CLR_OFFSET) =
		/* clear */
		DRIVE_MASK
		/* output enable */
		| (1u << OD_SHIFT);
	REG4B(rp1 + RP1_PADS_GPIO(GPIO) + SET_OFFSET) =
		/* set to 4mA */
		1u << DRIVE_SHIFT;
}

int kmain(void)
{
	uart_putstr("hello world\n", BCM2712_UART);

	//uint64_t rp1 = // get rp1 base address
	//if (!rp1) {
	//	uart_putstr("skill issue\n", BCM2712_UART);
	//	while(1) {} 
	//}

	//turn_on(23, rp1);

	/* cpu hang */
	while (1) {}
}
