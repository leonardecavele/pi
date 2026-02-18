#include "standard.h"
#include "dtb.h"
#include "uart.h" //maybe temporary

static t_dtb_data dd = (t_dtb_data){0};

/*
   to do :
   check all alignments in checker
   check memory reservation block
   select print port or None
   error codes
   */

extern t_dtb_reg find_in_dtb(char *path, char *needle)
{
	t_dtb_reg r = (t_dtb_reg){0};

	if (!dd.dtb) {
		uart_printf(BCM2712_UART, "call 'dtb_check' first\r\n");
		return r;
	}

	char *node_names[256];
	char *compatibles[128];
	char current_path[1024];
	memset(node_names, 0, sizeof(node_names));
	current_path[0] = 0;

	uintptr_t sb = dd.dtb + dd.off_dt_struct;
	uint32_t token = 0;
	uint8_t depth = 0;

	uint8_t compatibles_count = 0;

	do {
		token = __builtin_bswap32(REG4B(sb));
		sb += 0x04;

		if (token == FDT_BEGIN_NODE) {
			node_names[depth++] = (char *)sb;

			while ((*(char *)sb) != 0)
				sb += 0x01;

			while (sb % 4 != 0)
				sb += 0x01;
		}

		if (token == FDT_PROP) {
			t_prop p = (t_prop){0};

			p.len = __builtin_bswap32(REG4B(sb + 0x00));
			p.nameoff = __builtin_bswap32(REG4B(sb + 0x04));
			sb += 0x08;

			char *name = (char *)(dd.dtb + dd.off_dt_strings + p.nameoff);

			if (!strcmp((uint8_t *)name, "compatible")) {
                uintptr_t start = sb;
                uintptr_t end = sb + p.len;

                while (start < end) {
					compatibles[compatibles_count++] = (char *)start;

                    while (start < end && (*(char *)start) != 0)
                        start += 0x01;

                    if (start < end && (*(char *)start) == 0)
                        start += 0x01;
                }
            } else if (!strcmp((uint8_t *)name, "#address-cells"))
                r.n = __builtin_bswap32(REG4B(sb));
            else if (!strcmp((uint8_t *)name, "#size-cells"))
                r.size = __builtin_bswap32(REG4B(sb));
            else if (!strcmp((uint8_t *)name, "reg"))
                r.reg = sb;
            else if (!strcmp((uint8_t *)name, "ranges")) {
                r.ranges = sb;
                r.ranges_len = p.len;
            }

            sb += p.len;

            while (sb % 4 != 0)
                sb += 0x01;
        }

        if (token == FDT_NOP)
            ;
        else if (token == FDT_END_NODE) {
            current_path[0] = 0;

            int i = 0;
            while (++i < depth) {
                cat(current_path, sizeof(current_path), "/");
                cat(current_path, sizeof(current_path), node_names[i]);
            }

			for (int k = 0; k < compatibles_count; k++) {
				uart_printf(BCM2712_UART, "%s/%s\r\n", current_path, compatibles[k]);
				if (!strcmp(current_path, path) && !strcmp(needle, compatibles[k])) {
					r.found = true;
					break;
				}
			}
			compatibles_count = 0;

            node_names[--depth] = 0;
	        r = (t_dtb_reg){0};
        }
    } while (token != FDT_END);

    if (r.found == true)
        uart_printf(BCM2712_UART, "found %s in %s\r\n", needle, path);
    else
        uart_printf(BCM2712_UART, "can't find %s in %s\r\n", needle, path);

    return r;
}

extern int dtb_check(uintptr_t dtb)
{
    /* check if dtb has a 8-byte aligned offset */
    if (dtb % 8 != 0) {
        uart_printf(BCM2712_UART, "invalid dtb offset\r\n");
        return 1;
    }

    /* convert big endian to little endian */
    dd.dtb = dtb;
    dd.magic = __builtin_bswap32(REG4B(dd.dtb + 0x00));
    dd.totalsize = __builtin_bswap32(REG4B(dd.dtb + 0x04));
    dd.off_dt_struct = __builtin_bswap32(REG4B(dd.dtb + 0x08));
    dd.off_dt_strings = __builtin_bswap32(REG4B(dd.dtb + 0x0C));
    dd.off_mem_rsvmap = __builtin_bswap32(REG4B(dd.dtb + 0x10));
    dd.version = __builtin_bswap32(REG4B(dd.dtb + 0x14));
    dd.last_comp_version = __builtin_bswap32(REG4B(dd.dtb + 0x18));
    dd.boot_cpuid_phys = __builtin_bswap32(REG4B(dd.dtb + 0x1C));
    dd.size_dt_strings = __builtin_bswap32(REG4B(dd.dtb + 0x20));
    dd.size_dt_struct = __builtin_bswap32(REG4B(dd.dtb + 0x24));

    uart_printf(BCM2712_UART, "\r\n[DTB HEADER]\r\n");
    uart_printf(BCM2712_UART, "magic: %x\r\n", dd.magic);
    uart_printf(BCM2712_UART, "totalsize: %x\r\n", dd.totalsize);
    uart_printf(BCM2712_UART, "off_dt_struct: %x\r\n", dd.off_dt_struct);
    uart_printf(BCM2712_UART, "off_dt_strings: %x\r\n", dd.off_dt_strings);
    uart_printf(BCM2712_UART, "off_mem_rsvmap: %x\r\n", dd.off_mem_rsvmap);
    uart_printf(BCM2712_UART, "version: %u\r\n", dd.version);
    uart_printf(BCM2712_UART, "last_comp_version: %u\r\n", dd.last_comp_version);
    uart_printf(BCM2712_UART, "boot_cpuid_phys: %x\r\n", dd.boot_cpuid_phys);
    uart_printf(BCM2712_UART, "size_dt_strings: %x\r\n", dd.size_dt_strings);
    uart_printf(BCM2712_UART, "size_dt_struct: %x\r\n", dd.size_dt_struct);
    uart_printf(BCM2712_UART, "\r\n");

    /* check if it is the valid magic */
    if (dd.magic != 0xd00dfeed) {
        uart_printf(BCM2712_UART, "invalid magic\r\n");
        return 1;
    }

    /* check if structure block has a 4-byte aligned offset */
    if (dd.off_dt_struct % 4 != 0) {
        uart_printf(BCM2712_UART, "invalid structure offset\r\n");
        return 1;
    }

    /* check if last structure block is END */
    if (__builtin_bswap32(REG4B(dtb + dd.off_dt_struct + dd.size_dt_struct - 0x04)) != FDT_END) {
        uart_printf(BCM2712_UART, "invalid structure end\r\n");
        return 1;
    }

    return 0;
}
