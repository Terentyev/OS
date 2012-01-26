OUTPUT_FORMAT("binary")
ENTRY(start)
phys = 0x00100000
SECTIONS
{
    .text phys : AT(phys)
    {
        code = .; _code = .; __code = .;
        *(.text)
        *(.rodata)
        . = ALIGN(4096);
    }
    .data : AT(phys + (data - code))
    {
        data = .; _data = .; __data = .;
        *(.data)
        . = ALIGN(4096);
    }
    .bss : AT(phys + (bss - code))
    {
        bss = .; _bss = .; __bss = .;
        *(.bss)
        . = ALIGN(4096);
    }
    end = .; _end = .; __end = .;
}
