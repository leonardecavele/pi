#ifndef RP1_PADS_H
# define RP1_PADS_H

#define RP1_PADS_GPIO(a) \
	(PADS_BANK0 + 0x04u + (uint32_t)(a) * 4u)

typedef enum e_rp1_pads_shift {
    SLEWFAST_SHIFT = 0,
    SCHMITT_SHIFT = 1,
    PDE_SHIFT = 2,
    PUE_SHIFT = 3,
    DRIVE_SHIFT = 4,
    IE_SHIFT = 6,
    OD_SHIFT = 7
} t_rp1_pads_shift;

typedef enum e_rp1_pads_mask {
    SLEWFAST_MASK = 0x01u,
    SCHMITT_MASK = 0x02u,
    PDE_MASK = 0x04u,
    PUE_MASK = 0x08u,
    DRIVE_MASK = 0x30u,
    IE_MASK = 0x40u,
    OD_MASK = 0x80u
} t_rp1_pads_mask;

#endif
