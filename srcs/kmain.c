#include "rp1.h"
#include "uart.h"
#include "bcm2712.h"
#include "dtb.h"

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





static void dump_hex(uintptr_t addr, uint32_t len)
{
	const uint8_t *p = (const uint8_t *)addr;

	for (uint32_t i = 0; i < len; i++) {
		if ((i % 16) == 0)
			uart_printf(BCM2712_UART, "\r\n%08x: ", (uint32_t)(addr + i));
		uart_printf(BCM2712_UART, "%02x ", p[i]);
	}
	uart_printf(BCM2712_UART, "\r\n");
}



static uint32_t be32(const void *ptr)
{
	const uint8_t *p = (const uint8_t *)ptr;
	return ((uint32_t)p[0] << 24) | ((uint32_t)p[1] << 16) | ((uint32_t)p[2] << 8) | (uint32_t)p[3];
}

static uint64_t be64(const void *ptr)
{
	return ((uint64_t)be32(ptr) << 32) | (uint64_t)be32((const uint8_t *)ptr + 4);
}

static void dump_cells32(uintptr_t addr, uint32_t n_cells)
{
	for (uint32_t i = 0; i < n_cells; i++) {
		uint32_t v = be32((const void *)(addr + i * 4));
		uart_printf(BCM2712_UART, "cell[%u]=%08x\r\n", i, v);
	}
}


int kmain(uintptr_t dtb)
{
	uart_printf(BCM2712_UART, "hello %s\r\n", "world");

	dtb_check(dtb);
	t_dtb_reg rp1 = find_in_dtb(
		"/axi/pcie@1000120000", "rp1"
	);

	uart_printf(BCM2712_UART, "reg ptr: %x\r\n", rp1.reg);
	uart_printf(BCM2712_UART, "ranges ptr: %x\r\n", rp1.ranges);
	uart_printf(BCM2712_UART, "found: %d\r\n", rp1.found);
	uart_printf(BCM2712_UART, "size: %u\r\n", rp1.size);
	uart_printf(BCM2712_UART, "n: %u\r\n", rp1.n);
	uart_printf(BCM2712_UART, "ranges_len: %u\r\n", rp1.ranges_len);

	uart_putstr(BCM2712_UART, "DTB reg bytes:");
	dump_hex((uintptr_t)rp1.reg, 64);              // 64 bytes pour commencer

	uart_putstr(BCM2712_UART, "DTB ranges bytes:");
	dump_hex((uintptr_t)rp1.ranges, rp1.ranges_len); // là tu as la longueur


	uart_putstr(BCM2712_UART, "reg cells:");
	dump_cells32((uintptr_t)rp1.reg, 16);

	uart_putstr(BCM2712_UART, "ranges cells:");
	dump_cells32((uintptr_t)rp1.ranges, rp1.ranges_len / 4);



	//uint64_t rp1 = // get rp1 base address
	//if (!rp1) {
	//	uart_putstr("skill issue\n", BCM2712_UART);
	//	while(1) {} 
	//}

	//turn_on(23, rp1);

	/* cpu hang */
	while (1) {}
}
