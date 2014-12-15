/* $chaos: init.c,v 1.13 2002/10/14 21:29:10 per Exp $ */
/* Abstract: storm initialization. */

/*
 * @author  Per Lundberg <per@chaosdev.org> 
 * @author  Henrik Hallin <hal@chaosdev.org>
 * @author  Vladimir Sorokin 
 */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE.
   reference documentation. */

#include <enviroment.h>

#include "Include/parse.h"
#include "Include/multiboot.h"
#include "Include/main.h"

static char *array_of_pointers[COMMAND_LINE_SIZE];
static unsigned int number_of_arguments;

descriptor_t gdt[GDT_ENTRIES] __attribute__ ((section (".gdt")));
descriptor_t idt[IDT_ENTRIES] __attribute__ ((section (".idt")));

/* The kernel stack. */
uint8_t kernel_stack[KERNEL_STACK_SIZE];

/**
 * @brief                A temporary GDT that we copy into the real one. 
 */
static uint64_t temporary_gdt[] = 
{
    /**
     * @brief            Null descriptor. Generates GPF on access. 
     */
    DESCRIPTOR_NULL,

    /**
     * @brief            Kernel code segment (executable). 
     */
    DESCRIPTOR_CODE (0x0, SEGMENT_SIZE_MAX, SEGMENT_GRANULARITY_PAGE,
        PRIVILEGE_LEVEL_KERNEL, SEGMENT_PRESENT, SEGMENT_DIGIT_32),

    /**
     * @brief            Kernel data segment (read/write).
     */
    DESCRIPTOR_DATA (0x0, SEGMENT_SIZE_MAX, SEGMENT_GRANULARITY_PAGE,
        PRIVILEGE_LEVEL_KERNEL, SEGMENT_PRESENT, SEGMENT_DIGIT_32),
    
    /**
     * @brief            Process code segment (exec). 
     */
    DESCRIPTOR_CODE (0x0, SEGMENT_SIZE_MAX, SEGMENT_GRANULARITY_PAGE,
        PRIVILEGE_LEVEL_USER, SEGMENT_PRESENT, SEGMENT_DIGIT_32),

    /**
     * @brief            Process data segment (read/write). 
     */
    DESCRIPTOR_DATA (0, SEGMENT_SIZE_MAX, SEGMENT_GRANULARITY_PAGE,
        PRIVILEGE_LEVEL_USER, SEGMENT_PRESENT, SEGMENT_DIGIT_32),
};

typedef struct
{
    uint16_t size;
    descriptor_t *base;
} descriptors_table_register_t PACKED;

static descriptors_table_register_t idtr = 
{
    size: IDT_SIZE - 1,
    base: NULL,
};

static descriptors_table_register_t gdtr = 
{
    size: GDT_SIZE - 1,
    base: NULL,
};

/**
 * This is the first code of the kernel that gets executed. (well,
 *   almost. _start () sets up some stuff first...) 
 */
static void kernel_entry (void)
{
    multiboot_init ();

    number_of_arguments = arguments_parse (storm_info.command_line, 
        array_of_pointers);
    
    main_bootup (number_of_arguments, array_of_pointers);

    asm 
    (
        "1: hlt\n"
        "jmp 1b"
    );
}

/**
 * @brief                This is the kernel entry point. 
 */
void _start (void)
{
    /* EBX contains the address to the multiboot table. Save this in
       the kernel data table. We can NOT use memory_copy here, since
       that will need a stack. */
    asm 
    (
        "movl    %0, %%edi\n"
        "movl    %%ebx, %%esi\n"
        "movl    %1, %%ecx\n"
        "rep     movsl\n"
        :
        :
            "g" ((uint32_t) &multiboot_info),
            "g" (sizeof (multiboot_info_t) / 4)
    );
  
    /* Move the GDT to the right location in memory. */
    asm 
    (
        "cld\n"
        "movl    %0, %%edi\n"
        "movl    %1, %%esi\n"
        "movl    %2, %%ecx\n"
        "rep     movsl\n"
        "movl    %3, %%ecx\n"
        "movl    $0, %%eax\n"
        "rep     stosl"
        :
        : 
            "g" ((uint32_t) gdt),
            "g" ((uint32_t) temporary_gdt),
            "g" (sizeof (temporary_gdt) / 4),
            "g" ((GDT_SIZE - sizeof (temporary_gdt)) / 4)
    );

    /* Clear the IDT. */
    asm 
    (
        "movl    %0, %%edi\n"
        "movl    $0, %%eax\n"
        "movl    %1, %%ecx\n"
        "rep     stosl"
        :
        : 
            "g" (idt),
            "g" (IDT_SIZE / 4)
    );

    /* IDT base. Couldn't do this in the declaration above since the
       compiler claimed it could not compute the address of idt. */
    idtr.base = idt;

    /* GDT base. */
    gdtr.base = gdt;

    /* Set up the GDTR and IDTR. */
    asm volatile ("lgdt    %0" : : "m" (gdtr));
    asm volatile ("lidt    %0" : : "m" (idtr));

    /* Initialize the segment registers so they are loaded with our new
       selectors. */
    asm 
    (
        "movl    %0, %%eax\n"
        "movw    %%ax, %%ss\n"
        "movl    %1, %%esp\n"
        "movw    %%ax, %%es\n"
        "movw    %%ax, %%fs\n"
        "movw    %%ax, %%gs\n"
        "movw    %%ax, %%ds"
        :
        :
        "g" (SELECTOR_KERNEL_DATA),
        "g" ((uint32_t) &kernel_stack + KERNEL_STACK_SIZE)
    );

    /* Pass control to the kernel. */
    asm ("ljmp   %0, %1"
         :
         :
         "n" (SELECTOR_KERNEL_CODE),
         "p" (&kernel_entry));
}

