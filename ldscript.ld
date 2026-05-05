ENTRY(_reset);

MEMORY {
  flash(rx)  : ORIGIN = 0x08000000, LENGTH = 32k
  sram(rwx) : ORIGIN = 0x20000000, LENGTH = 12k
}


_estack     = ORIGIN(sram) + LENGTH(sram);

SECTIONS {
    .vectors  : { KEEP(*(.vectors)) }   > flash
    .text     : { *(.text*) }           > flash

    .rodata : {
        . = ALIGN(4);
        *(.rodata)
        *(.rodata*)
        . = ALIGN(4);
    } > flash

    .data : {
        _sdata = .;
        *(.first_data)
        *(.data SORT(.data.*))
        _edata = .;  /* .data section end */
    } > sram AT > flash
    _sidata = LOADADDR(.data);
    .bss : {
        _sbss = .;              /* .bss section start */
        *(.bss SORT(.bss.*) COMMON)
        _ebss = .;              /* .bss section end */
    } > sram
}
