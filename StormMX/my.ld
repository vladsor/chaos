OUTPUT_FORMAT("elf32-i386", "elf32-i386", "elf32-i386")
OUTPUT_ARCH(i386)
ENTRY(_start)

PHDRS
{
    headers PT_PHDR PHDRS;
    code PT_LOAD AT (0x00000000) FLAGS (1);
    data PT_LOAD AT (0x00000000) FLAGS (6);
/*    stack AT (0xFFFFFFFF - STACK_SIZE);*/
}

SECTIONS
{
    . = 0x100000 + SIZEOF_HEADERS;

    .init.pre :
    {
	*(.init.pre)
    }

    .init : 
    { 
	*(.text.init)
	*(.data.init)
    }
    
    _init_end = .;

    /* We want the GDT and IDT to be page aligned. */
    . = ALIGN (4K);
    .special :
    {
	*(.gdt)
	*(.idt)
    } :data

    . = ALIGN (4K);    
    .code_section : 
    { 
	*.(.text) 
    } :code
    
    . = ALIGN (4K);
    .data : 
    { 
	*.(.data) 
    }
    
    .bss : 
    { 
	*.(.bss) 
    }
    
    /DISCARD/ :
    {
	*.(.sbss)
    }
    
    _end = .;
}
