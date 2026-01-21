.section .text
.global _start
_start:
	/* disable interrupts */
	msr daifset, #0xf

	/* fetch CPU data */
	mrs x2, mpidr_el1
	/* keep 2 least significant bits */
	and x2, x2, #3
	cbz x2, cpu0
	/* branch to hang if not cpu 0 */
	b cpu_hang
cpu0:

	ldr x2, =__stack_top
	/* temporary stack */
	mov sp, x2

	ldr x2, =__bss_start
	ldr x1, =__bss_end
bss_loop:
	cmp x2, x1
	b.hs bss_done
	/* write 0 then increase pointer by 1 while in bss */
	strb wzr, [x2], #1
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
