.section .text
.global _start
_start:
	/* disable interrupts */
	msr daifset, #0xf

	ldr x0, =__stack_top
	/* temporary stack */
	mov sp, x0

	ldr x0, =__bss_start
	ldr x1, =__bss_end
bss_loop:
	cmp x0, x1
	b.hs bss_done
	/* write 0 then increase pointer by 1 while in bss */
	strb wzr, [x0], #1
	b bss_loop

bss_done:

	/*	to do :
		parse device tree
		use mmu
	*/

	/* branch to kernel main */
	bl kmain

cpu_hang:
	wfi
	b cpu_hang
