#include "rp1.h"
#include "uart.h"
#include "bcm2712.h"

/*	to do :
	use enums etc to have a single variable replacing '23'
	PCIe BCM2712
	RP1
	read BAR1 or/and BAR2
*/

int kmain(void)
{
	uint32_t GPIO_PIN = 23u;

	uart_putstr("kmain alive\n", BCM2712_UART);

	uint64_t rp1_adr = rp1_get_bar1_base_from_dtb((const void *)0x2efec600ull);
	if (!rp1_adr)
		while(1) { }

	/* IO BANK0 */
	REG4B(rp1_adr + RP1_GPIO_CTRL(GPIO_PIN) + CLR_OFFSET) =
		/* clear */
		FUNCSEL_MASK
		| OUTOVER_MASK
		| OEOVER_MASK;
	REG4B(rp1_adr + RP1_GPIO_CTRL(GPIO_PIN) + SET_OFFSET) =
		/* new value */
		5u << FUNCSEL_SHIFT;

	/* RIO */
	/* output enable */
	REG4B(rp1_adr + SYS_RIO0 + OE_OFFSET + SET_OFFSET) = (1u << GPIO_PIN);
	/* output value */
	REG4B(rp1_adr + SYS_RIO0 + OUT_OFFSET + CLR_OFFSET) = (1u << GPIO_PIN);

	/* PADS */
	/* 3.3v */
	REG4B(rp1_adr + PADS_BANK0 + CLR_OFFSET) = 0x1u;
	/* select mA */
	REG4B(rp1_adr + RP1_PADS_GPIO(GPIO_PIN) + CLR_OFFSET) =
		/* clear */
		DRIVE_MASK
		/* output enable */
		| (1u << OD_SHIFT);
	REG4B(rp1_adr + RP1_PADS_GPIO(GPIO_PIN) + SET_OFFSET) =
		/* set to 4mA */
		1u << DRIVE_SHIFT;

	/* cpu hang */
	while (1) {
		REG4B(rp1_adr + SYS_RIO0 + OUT_OFFSET + XOR_OFFSET) = (1u << GPIO_PIN);
		for (volatile unsigned long long i = 0; i < 2000000ULL; i++) ;
	}
}
