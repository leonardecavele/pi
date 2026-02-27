#include "address.h"
#include "uart.h"
#include "utils.h"
#include "rp1_pcie.h"

/* to do : proper sleep */
// todo
static void delay_loops(volatile uint64_t loops)
{
	while (loops--)
	{
		__asm__ volatile ("nop");
	}
}

// todo
static void sleep_approx_1s(void)
{
	delay_loops(600000ULL);
}

static void win_setup(void)
{
	const uint64_t cpu_base  = RP1_BASE;
	const uint64_t size      = 0x00800000ull;
	const uint64_t pcie_base = 0x10000000ull;

	REG4B(BCM2712_PCIE_BASE + PCIE_MISC_CPU_2_PCIE_MEM_WIN0_LO) =
		(uint32_t)(pcie_base & 0xffffffffu);
	dsb_sy();

	REG4B(BCM2712_PCIE_BASE + PCIE_MISC_CPU_2_PCIE_MEM_WIN0_HI) =
		(uint32_t)(pcie_base >> 32);
	dsb_sy();

	uint32_t cpu_base_mb  = (uint32_t)(cpu_base >> 20);
	uint32_t cpu_limit_mb = (uint32_t)((cpu_base + size - 1) >> 20);

	uint32_t base_low  = cpu_base_mb & 0xFFFu;
	uint32_t limit_low = cpu_limit_mb & 0xFFFu;
	uint32_t base_limit = (limit_low << 20) | (base_low << 4);

	REG4B(BCM2712_PCIE_BASE + PCIE_MISC_CPU_2_PCIE_MEM_WIN0_BASE_LIMIT) =
		base_limit;
	dsb_sy();

	uint32_t base_high  = cpu_base_mb >> 12;
	uint32_t limit_high = cpu_limit_mb >> 12;

	REG4B(BCM2712_PCIE_BASE + PCIE_MISC_CPU_2_PCIE_MEM_WIN0_BASE_HI) =
		base_high;
	dsb_sy();

	REG4B(BCM2712_PCIE_BASE + PCIE_MISC_CPU_2_PCIE_MEM_WIN0_LIMIT_HI) =
		limit_high;
	dsb_sy();
}

extern void pcie_setup(void)
{
	/* setup bus */
	REG4B(BCM2712_PCIE_BASE + (PCI_CFG_PRIMARY_BUS & 0xffc)) = 0x00010100u;

	/* setup bridge */
	const uint64_t pcie_base = 0x10000000ull;
	const uint64_t size      = 0x00800000ull;

	uint16_t mem_base  = (uint16_t)((pcie_base >> 16) & 0xfff0);
	uint16_t mem_limit = (uint16_t)(((pcie_base + size - 1) >> 16) & 0xfff0);

	REG4B(BCM2712_PCIE_BASE + (PCI_CFG_MEMORY_BASE & 0xffc)) =
		((uint32_t)mem_limit << 16) | (uint32_t)mem_base;
	dsb_sy();

	uint32_t cmdsts = REG4B(BCM2712_PCIE_BASE + (PCI_CFG_COMMAND & 0xffc));
	cmdsts = (cmdsts & 0xffff0000u)
		| ((cmdsts & 0x0000ffffu) | (PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER));

	REG4B(BCM2712_PCIE_BASE + (PCI_CFG_COMMAND & 0xffc)) = cmdsts;
	dsb_sy();

	/* setup bar1 */
	uint32_t idx =
		((uint32_t)RP1_PCI_BUS  << PCIE_EXT_BUSNUM_SHIFT)
		| ((uint32_t)RP1_PCI_SLOT << PCIE_EXT_SLOT_SHIFT)
		| ((uint32_t)RP1_PCI_FUNC << PCIE_EXT_FUNC_SHIFT);

	/* BAR1 */
	REG4B(BCM2712_PCIE_BASE + PCIE_EXT_CFG_INDEX) = idx;
	dsb_sy();

	REG4B(BCM2712_PCIE_BASE + PCIE_EXT_CFG_DATA + (PCI_CFG_BAR1 & 0xffc)) =
		0x10000000u;
	dsb_sy();

	REG4B(BCM2712_PCIE_BASE + PCIE_EXT_CFG_INDEX) = idx;
	dsb_sy();

	REG4B(BCM2712_PCIE_BASE + PCIE_EXT_CFG_DATA + (PCI_CFG_COMMAND & 0xffc)) =
		(uint32_t)(PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER);
	dsb_sy();

	win_setup();
}

extern bool turn_on_pcie(void)
{
	REG4B(BCM2712_PCIE_BASE + PCIE_MISC_HARD_PCIE_HARD_DEBUG) &=
		~PCIE_SERDES_IDDQ_MASK;
	dsb_sy();

	sleep_approx_1s();

	REG4B(BCM2712_PCIE_BASE + PCIE_MISC_PCIE_CTRL) &= ~PCIE_PERSTB_MASK;
	dsb_sy();

	sleep_approx_1s();

	REG4B(BCM2712_PCIE_BASE + PCIE_MISC_PCIE_CTRL) |= PCIE_PERSTB_MASK;
	dsb_sy();

	sleep_approx_1s();

	for (uint32_t timeout = 2000; timeout; timeout--)
	{
		uint32_t status = REG4B(BCM2712_PCIE_BASE + PCIE_MISC_PCIE_STATUS);
		dsb_sy();

		if ((status & PCIE_PHYLINKUP_MASK) && (status & PCIE_DL_ACTIVE_MASK))
			return true;

		sleep_approx_1s();
	}

	return false;
}
