#include "rp1.h"
#include "uart.h"
#include "bcm2712.h"

/*	to do :
	proper sleep
*/

// to do
static void delay_loops(volatile uint64_t loops)
{
    while (loops--) {
        __asm__ volatile ("nop");
    }
}

// to do
static void sleep_approx_1s(void)
{
    delay_loops(6000000ULL);
}

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
	/* output enable */
	REG4B(SYS_RIO0 + OE_OFFSET + SET_OFFSET) = (1u << GPIO);
	/* output value */
	REG4B(SYS_RIO0 + OUT_OFFSET + SET_OFFSET) = (1u << GPIO);

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

	uart_printf(BCM2712_UART, "led set\r\n");
}

static void	turn_off(uint32_t GPIO)
{
	/* drive low first */
	REG4B(SYS_RIO0 + OUT_OFFSET + CLR_OFFSET) = (1u << GPIO);
	/* then disable output */
	REG4B(SYS_RIO0 + OE_OFFSET  + CLR_OFFSET) = (1u << GPIO);

	uart_printf(BCM2712_UART, "led off\r\n");
}

int pcie_rp1_x4_init(void);

int kmain(uintptr_t dtb)
{
	uart_printf(BCM2712_UART, "hello %s\r\n", "world");

	if (turn_on_pcie() == false) {
		uart_printf(BCM2712_UART, "error while turning on pcie\r\n");
		while (1) {}
	}
	pcie_setup();
	uart_printf(BCM2712_UART, "pcie setup\r\n");

	/* cpu hang */
	while (1) {
		turn_on(23);
		sleep_approx_1s();
		turn_off(23);
		turn_on(24);
		sleep_approx_1s();
		turn_off(24);
		turn_on(25);
		sleep_approx_1s();
		turn_off(25);
		turn_on(23);
		turn_on(24);
		sleep_approx_1s();
		turn_off(23);
		turn_off(24);
		turn_on(23);
		turn_on(25);
		sleep_approx_1s();
		turn_off(23);
		turn_off(25);
		turn_on(24);
		turn_on(25);
		sleep_approx_1s();
		turn_off(24);
		turn_off(25);
		turn_on(23);
		turn_on(24);
		turn_on(25);
		sleep_approx_1s();
		turn_off(25);
		turn_off(24);
		turn_off(23);
	}
}
