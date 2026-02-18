#ifndef DTB_H
#define DTB_H

#include "standard.h"

/* flattened device tree header */
typedef struct s_dtb_data {
	uintptr_t dtb;
    uint32_t magic;
    uint32_t totalsize;
    uint32_t off_dt_struct;
    uint32_t off_dt_strings;
    uint32_t off_mem_rsvmap;
    uint32_t version;
    uint32_t last_comp_version;
    uint32_t boot_cpuid_phys;
    uint32_t size_dt_strings;
    uint32_t size_dt_struct;
}	t_dtb_data;

enum e_structure_tokens {
	/* beginning of a node's representation */
	FDT_BEGIN_NODE = 0x00000001,
	/* end of a node's representation */
	FDT_END_NODE = 0x00000002,
	/* beginning of the representation of one property in the devicetree */
	FDT_PROP = 0x00000003,
	/* ignored */
	FDT_NOP = 0x00000004,
	/* end of the structure block */
	FDT_END = 0x00000009
};

/* FDT PROP */
typedef struct s_prop {
	/* zero if empty value */
	uint32_t len;
	uint32_t nameoff;
}	t_prop;

typedef struct s_dtb_reg { // change name
	uintptr_t reg;
	uintptr_t ranges;
	uint32_t ranges_len;
	uint32_t size;
	uint32_t n;
	bool found;
}	t_dtb_reg;

int dtb_check(uintptr_t dtb);
t_dtb_reg find_in_dtb(char *needle_node, char *needle_compatible);

#endif
