#ifndef RP1_PCIE_H
#define RP1_PCIE_H

#include "rp1.h"

/* base address (MMIO) */
#define BCM2712_PCIE_BASE	UADDR(0x1000120000ull)

/* config space access */
typedef enum e_rp1_pcie_cfg_access_off {
	PCIE_EXT_CFG_DATA = 0x8000u,
	PCIE_EXT_CFG_INDEX = 0x9000u
}	t_rp1_pcie_cfg_access_off;

typedef enum e_rp1_pcie_cfg_access_shift {
	PCIE_EXT_BUSNUM_SHIFT = 20u,
	PCIE_EXT_SLOT_SHIFT = 15u,
	PCIE_EXT_FUNC_SHIFT = 12u
}	t_rp1_pcie_cfg_access_shift;

//#define PCIE_EXT_CFG_INDEX_VAL(bus, slot, func) \
//	(((uint32_t)(bus)  << PCIE_EXT_BUSNUM_SHIFT) | \
//	 ((uint32_t)(slot) << PCIE_EXT_SLOT_SHIFT)   | \
//	 ((uint32_t)(func) << PCIE_EXT_FUNC_SHIFT))

/* PCIe link */
typedef enum e_rp1_pcie_link_off {
	PCIE_MISC_PCIE_CTRL = 0x4064u,
	PCIE_MISC_PCIE_STATUS = 0x4068u
}	t_rp1_pcie_link_off;

typedef enum e_rp1_pcie_link_mask {
	PCIE_PERSTB_MASK = 0x00000004u,
	PCIE_PHYLINKUP_MASK = 0x00000010u,
	PCIE_DL_ACTIVE_MASK = 0x00000020u
}	t_rp1_pcie_link_mask;

/* physical power */
typedef enum e_rp1_pcie_phy_off {
	PCIE_MISC_HARD_PCIE_HARD_DEBUG = 0x4304u
}	t_rp1_pcie_phy_off;

typedef enum e_rp1_pcie_phy_mask {
	PCIE_SERDES_IDDQ_MASK = 0x08000000u
}	t_rp1_pcie_phy_mask;

/* cpu window */
typedef enum e_rp1_pcie_out_win0_off {
	PCIE_MISC_CPU_2_PCIE_MEM_WIN0_LO = 0x400cu,
	PCIE_MISC_CPU_2_PCIE_MEM_WIN0_HI = 0x4010u,
	PCIE_MISC_CPU_2_PCIE_MEM_WIN0_BASE_LIMIT = 0x4070u,
	PCIE_MISC_CPU_2_PCIE_MEM_WIN0_BASE_HI = 0x4080u,
	PCIE_MISC_CPU_2_PCIE_MEM_WIN0_LIMIT_HI = 0x4084u
}	t_rp1_pcie_out_win0_off;

/* standard pcie config */
typedef enum e_pci_cfg_off {
	PCI_CFG_VENDOR_DEVICE = 0x00u,
	PCI_CFG_COMMAND = 0x04u,

	PCI_CFG_STATUS = 0x06u,
	PCI_CFG_REV_CLASS = 0x08u,
	PCI_CFG_HEADER_TYPE = 0x0eu,

	PCI_CFG_BAR0 = 0x10u,
	PCI_CFG_BAR1 = 0x14u,
	PCI_CFG_BAR2 = 0x18u,
	PCI_CFG_BAR3 = 0x1cu,
	PCI_CFG_BAR4 = 0x20u,
	PCI_CFG_BAR5 = 0x24u,

	PCI_CFG_PRIMARY_BUS = 0x18u,
	PCI_CFG_SECONDARY_BUS = 0x19u,
	PCI_CFG_SUBORDINATE_BUS = 0x1au,

	PCI_CFG_MEMORY_BASE = 0x20u,
	PCI_CFG_MEMORY_LIMIT = 0x22u
}	t_pci_cfg_off;

typedef enum e_pci_command_bits {
	PCI_COMMAND_IO = 0x0001u,
	PCI_COMMAND_MEMORY = 0x0002u,
	PCI_COMMAND_MASTER = 0x0004u
}	t_pci_command_bits;

/* rp1 BDF (bus/device/function) */
typedef enum e_rp1_pcie_bdf {
	RP1_PCI_BUS = 1u,
	RP1_PCI_SLOT = 0u,
	RP1_PCI_FUNC = 0u
}	t_rp1_pcie_bdf;

bool turn_on_pcie(void);
void pcie_setup(void);

#endif
