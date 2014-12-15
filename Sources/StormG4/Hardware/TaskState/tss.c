#include <enviroment.h>

#include "Include/tss.h"

#define DEBUG_MODULE_NAME "TSS"

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE1
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <debug/macros.h>

void tss_create (p_tss_t tss, p_page_directory_t page_directory,
    uint16_t selector_code, uint16_t selector_data,
    uint32_t instruction_pointer, uint32_t kernel_stack_pointer, 
    uint32_t user_stack_pointer UNUSED,
    uint32_t eflags)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
         "%s: %s (%p, %p, %p, %p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        tss, page_directory, (p_void_t) instruction_pointer, 
        (p_void_t) kernel_stack_pointer);

    memory_clear (tss, sizeof (tss_t));
    
    tss->cr3 = (uint32_t) page_directory;
    tss->eip = instruction_pointer;

    tss->eax = tss->ebx = tss->ecx = tss->edx = 0xC0CAC01A;

    /* Fill up the segment registers. */

    tss->cs = selector_code;//SELECTOR_KERNEL_CODE;
  
    tss->ds = selector_data;//SELECTOR_KERNEL_DATA;
    tss->es = selector_data;//SELECTOR_KERNEL_DATA;
    tss->fs = selector_data;//SELECTOR_KERNEL_DATA;
    tss->gs = selector_data;//SELECTOR_KERNEL_DATA;

    tss->eflags = eflags;

//selector_data;
    tss->ss = SELECTOR_KERNEL_DATA;
    tss->esp = kernel_stack_pointer;//user_stack_pointer;

//selector_data;
    tss->ss0 = SELECTOR_KERNEL_DATA;
    tss->esp0 = kernel_stack_pointer;

    tss->iomap_base = (uint8_t *) tss->iomap - (uint8_t *) tss;
    tss->iomap_size = 0;
}

/**
 *  @todo Must be one flag for each processor.
 */
static volatile unsigned int dispatch_flag = 0; 

uint32_t jump_data[2] = {0, 0};
 
void tss_switch_prepare (p_tss_t tss)
{
    dispatch_flag ^= 1;
            
    if (dispatch_flag == 0)
    {
        gdt_setup_tss_descriptor (DESCRIPTOR_INDEX_TSS1, tss, 
            sizeof (tss_t), PRIVILEGE_LEVEL_KERNEL);
            
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
            "%s: %s: Jump to TSS1 %4.4x:%p, esp: %p [%p].\n",
            DEBUG_MODULE_NAME, __FUNCTION__, 
            tss->cs, (void *) tss->eip, (void *) tss->esp, tss);

        jump_data[1] = SELECTOR_TSS1;
    }
    else
    {
        gdt_setup_tss_descriptor (DESCRIPTOR_INDEX_TSS2, tss,
            sizeof (tss_t), PRIVILEGE_LEVEL_KERNEL);
            
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
            "%s: %s: Jump to TSS2 %4.4x:%p, esp: %p [%p].\n",
            DEBUG_MODULE_NAME, __FUNCTION__, 
            tss->cs, (void *) tss->eip, (void *) tss->esp, tss);
                
        jump_data[1] = SELECTOR_TSS2;
    }
}

