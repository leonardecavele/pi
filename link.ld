ENTRY(_start)

SECTIONS
{
  . = 0x200000;			// kernel_address

  .text : {
	. = ALIGN(16)
    *(.text*)
  }

  .rodata : {
    *(.rodata*)
  }

  .data : {
    *(.data*)
  }

  .bss (NOLOAD) : {
    . = ALIGN(16);
    __bss_start = .;
    *(.bss*)
    *(COMMON)
    __bss_end = .;
  }

  .stack (NOLOAD) : {
    . = ALIGN(16);
    __stack_bottom = .;
    . = . + 0x10000;
    __stack_top = .;
  }
}
