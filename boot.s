.section .text
.global _start
_start:
	msr daifset, #0xf		// disable interrupts

	ldr x0, =__stack_top
	mov sp, x0				// temporary stack

	ldr x0, =__bss_start
	ldr x1, =__bss_end
bss_loop:
	cmp x0, x1
	b.hs bss_done
	strb wzr, [x0], #1		// write 0 then increase pointer by 1
	b bss_loop				// while in bss

bss_done:

	/*	to do :
		parse device tree
		use mmu
	*/

	bl kmain				// branch to kernel main

cpu_hang:
	wfi
	b cpu_hang				// error handler if kmain returns
