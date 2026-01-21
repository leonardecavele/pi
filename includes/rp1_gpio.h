#ifndef RP1_GPIO_H
# define RP1_GPIO_H

#  include "rp1.h"

   /* get status address of gpio 'a' */
#  define RP1_GPIO_STATUS(a)	(IO_BANK0 + 0x0b8u + (uint32_t)(a) * 8)
   /* get control address of gpio 'a' */
#  define RP1_GPIO_CTRL(a)		(IO_BANK0 + 0x0bcu + (uint32_t)(a) * 8)

   /* get status bit 'b' of gpio 'a' */
#  define RP1_GPIO_STATUS_BIT(a, b) \
    ((REG4B(RP1_GPIO_STATUS((a))) >> (uint32_t)(b)) & 1u)

typedef enum e_rp1_a_status {
    OUTFROMPERI = 8,
    OUTTOPAD = 9,
    OEFROMPERI = 12,
    OETOPAD = 13,
    INISDIRECT = 16,
    INFROMPAD = 17,
    INFILTERED = 18,
    INTOPERI = 19,
    EVENT_EDGE_LOW = 20,
    EVENT_EDGE_HIGH = 21,
    EVENT_LEVEL_LOW = 22,
    EVENT_LEVEL_HIGH = 23,
    EVENT_F_EDGE_LOW = 24,
    EVENT_F_EDGE_HIGH = 25,
    EVENT_DB_LEVEL_LOW = 26,
    EVENT_DB_LEVEL_HIGH = 27,
    IRQCOMBINED = 28,
    IRQTOPROC = 29
} t_rp1_a_status;

typedef enum e_rp1_a_ctrl_shift {
    FUNCSEL_SHIFT = 0,
    F_M_SHIFT = 5,
    OUTOVER_SHIFT = 12,
    OEOVER_SHIFT = 14,
    INOVER_SHIFT = 16,
    IRQMASK_EDGE_LOW_SHIFT = 20,
    IRQMASK_EDGE_HIGH_SHIFT = 21,
    IRQMASK_LEVEL_LOW_SHIFT = 22,
    IRQMASK_LEVEL_HIGH_SHIFT = 23,
    IRQMASK_F_EDGE_LOW_SHIFT = 24,
    IRQMASK_F_EDGE_HIGH_SHIFT = 25,
    IRQMASK_DB_LEVEL_LOW_SHIFT = 26,
    IRQMASK_DB_LEVEL_HIGH_SHIFT = 27,
    IRQRESET_SHIFT = 28,
    IRQOVER_SHIFT = 30
} t_rp1_a_ctrl_shift;

typedef enum e_rp1_a_ctrl_mask {
    FUNCSEL_MASK = 0x0000001fu,
    F_M_MASK = 0x000007e0u,
    OUTOVER_MASK = 0x00003000u,
    OEOVER_MASK = 0x0000c000u,
    INOVER_MASK = 0x00030000u,
    IRQMASK_EDGE_LOW_MASK = 0x00100000u,
    IRQMASK_EDGE_HIGH_MASK = 0x00200000u,
    IRQMASK_LEVEL_LOW_MASK = 0x00400000u,
    IRQMASK_LEVEL_HIGH_MASK = 0x00800000u,
    IRQMASK_F_EDGE_LOW_MASK = 0x01000000u,
    IRQMASK_F_EDGE_HIGH_MASK = 0x02000000u,
    IRQMASK_DB_LEVEL_LOW_MASK = 0x04000000u,
    IRQMASK_DB_LEVEL_HIGH_MASK = 0x08000000u,
    IRQRESET_MASK = 0x10000000u,
    IRQOVER_MASK = 0xc0000000u
} t_rp1_a_ctrl_mask;

#endif
