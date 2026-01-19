#ifndef PADS_H
# define PADS_H

#  define PADS_BANK0			0x400f0000u

#  define PADS_GPIO23_OFFSET	0x60u

#  define PADS_SLEWFAST_OFFSET	0x0u
#  define PADS_SLEWFAST_MASK	0x00000001u

#  define PADS_SCHMITT_OFFSET	0x1u
#  define PADS_SCHMITT_MASK		0x00000002u

#  define PADS_PDE_OFFSET		0x2u
#  define PADS_PDE_MASK			0x00000004u

#  define PADS_PUE_OFFSET		0x3u
#  define PADS_PUE_MASK			0x00000008u

#  define PADS_DRIVE_OFFSET		0x4u
#  define PADS_DRIVE_MASK		0x00000030u

#  define PADS_IE_OFFSET		0x6u
#  define PADS_IE_MASK			0x00000040u

#  define PADS_OD_OFFSET		0x7u
#  define PADS_OD_MASK			0x00000080u

#endif
