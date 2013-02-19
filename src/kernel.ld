ENTRY(_start)
OUTPUT_ARCH("i386")

SECTIONS
{
    .__mbHeader 0x100000 :
    {
        * (.__mbHeader)
    }
    
    .text :
    {
        code = .;
        * (.text)
        . = ALIGN(4096);
    }
    
    .data :
    {
        data = .;
        * (.data)
        . = ALIGN(4096);
        * (.rodata)
        . = ALIGN(4096);
    }
    
    .bss :
    {
        bss = .;
        * (.bss)
        . = ALIGN(4096);
    }

    end = .;
}
