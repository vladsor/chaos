#include <enviroment.h>

#include "Include/exception.h"

#define DEBUG_MODULE_NAME "Exception"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <debug/macros.h>

static bool output_enabled = TRUE;

static void exception_print_page_screen (
    exception_hardware_page_info_t *exception_info)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "    Error code: 0x%8.8X\n", 
        *((uint32_t *) &exception_info->page_error));

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "    Page error: ");

    if (exception_info->page_error.rsvd)
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "RSVD, ");
    }

    if (exception_info->page_error.u_s)
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Supervisor ");
    }
    else
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "User ");
    }
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Page, ");

    if (exception_info->page_error.w_r)
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Write ");
    }
    else
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Read ");
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Operation");

    if (exception_info->page_error.p)
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, ", Page Not Present");
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "\n");

    DEBUG_PRINT (DEBUG_LEVEL_ERROR, "  Page address: %p\n",
        (void *) exception_info->address);
}

static void exception_print_segment_screen (
    exception_hardware_segment_info_t *exception_info)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "    Segment Error: ");

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Selector Index: %u, ", 
        exception_info->segment_error.segment_selector_index);

    if (!exception_info->segment_error.idt)
    {               
        if (exception_info->segment_error.ti)
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "in LDT, ");
        }
        else
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "in GDT, ");
        }
    }
    else
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "in IDT, ");
    }
      
    if (exception_info->segment_error.ext)
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "External Event");
    }
    else
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Internal Event");
    }
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "\n");
}

static void dump_registers (exception_hardware_info_t *registers)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "  Registers:\n");
  
    DEBUG_PRINT (DEBUG_LEVEL_ERROR,
        "    CS: %04X EIP: %08X EFLAGS: %08X\n", 
        registers->cs, registers->header.pc, registers->eflags);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "  Segment registers:\n");

    DEBUG_PRINT (DEBUG_LEVEL_ERROR,
        "    CS: %04X DS: %04X SS: %04X ES: %04X FS: %04X GS: %04X\n",
        registers->cs, registers->ds, registers->ss, registers->es, 
        registers->fs, registers->gs);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "  General-purpose registers:\n");
  

    DEBUG_PRINT (DEBUG_LEVEL_ERROR,
        "    EAX: %08X EBX: %08X ECX: %08X EDX: %08X\n",
        registers->eax, registers->ebx, registers->ecx, registers->edx);

    DEBUG_PRINT (DEBUG_LEVEL_ERROR,
        "    ESI: %08X EDI: %08X EBP: %08X ESP: %08X\n",
        registers->esi, registers->edi, registers->ebp, registers->esp);
/*
{
    uint32_t cr2;
    cpu_cr2_save (cr2);

    DEBUG_PRINT (DEBUG_LEVEL_ERROR,
        "    CR2: %08X\n",
        cr2);
}
*/
}

/* Display a exception screen. */

void exception_print_screen (uint32_t class_id, const char *description, 
    const char *reason, uint32_t error_code_type, 
    exception_hardware_info_t *exception_info)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "  Exception class: ");
    
    switch (class_id)
    {
        case EXCEPTION_CLASS_FAULT:
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Fault\n");
            break;
        }
        
        case EXCEPTION_CLASS_ABORT:
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Abort.\n");
            break;
        }
        
        case EXCEPTION_CLASS_INTERRUPT:
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Interrupt.\n");
            break;
        }
        
        default:
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Unknown.\n");
        }
    }
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "    Description: %s\n", 
        description);
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "    Possible reason: %s\n", 
        reason);
  
    switch (error_code_type)
    {
        case EXCEPTION_CODE_PAGE:
        {
            exception_print_page_screen (
                (exception_hardware_page_info_t *) exception_info);
            break;
        }
        
        case EXCEPTION_CODE_SEGMENT:
        {
            exception_print_segment_screen (
                (exception_hardware_segment_info_t *) exception_info);
            break;
        }
    }

    dump_registers (exception_info);
}

/**
 * @todo register/unregister must be atomic
 */
p_exception_handler_t exception_handlers[NUMBER_OF_EXCEPTIONS];
p_void_t exception_handlers_data[NUMBER_OF_EXCEPTIONS];


return_t exception_register (unsigned int exception_number, 
    p_exception_handler_t function, p_void_t parameter)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1, 
        "%s: Trying to register %i for %p...",
        DEBUG_MODULE_NAME,
        exception_number, function);

    /* Make sure the input data is pure. */
    
    DEBUG_ASSERT (exception_number < NUMBER_OF_EXCEPTIONS, 
	"Invalid exception number.\n");

    DEBUG_ASSERT (function != NULL, "Invalid address of function.\n");

#if 0    
    if (exception_handlers[exception_number] != NULL)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "%s: Exception #%u already used.\n", 
            DEBUG_MODULE_NAME, exception_number);
        
        return STORM_RETURN_BUSY;
    }
#endif    
    exception_handlers_data[exception_number] = parameter;
    exception_handlers[exception_number] = function;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1, 
                 "done.\n");

    return STORM_RETURN_SUCCESS;
}

return_t exception_unregister (unsigned int exception_number)
{
    /* Make sure the input data is pure. */
    
    DEBUG_ASSERT (exception_number < NUMBER_OF_EXCEPTIONS, 
	"Invalid exception number.\n");

    exception_handlers[exception_number] = NULL;
    
    return STORM_RETURN_SUCCESS;
}

#ifndef GDB
static void dummy_handler (p_void_t data UNUSED, 
    exception_hardware_info_t exception_info)
{
    int index = ((p_exception_info_t) &exception_info)->id;

//    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "data=%p\n", data);

    exception_print_screen (
        exception_hardware_descriptions[index].class_id,
        exception_hardware_descriptions[index].description, 
        exception_hardware_descriptions[index].reason,
        exception_hardware_descriptions[index].error_code_type, 
        (exception_hardware_info_t *) &exception_info);
    
    asm (
        "1: hlt\n"
        "jmp 1b");
}
#endif

return_t exception_init (int argc, char *argv[], char **envp UNUSED) 
{
    int index;
    
    for (index = 1; index < argc; index++)
    {
        if (!string_compare (argv[index], "--output-disable"))
        {
            output_enabled = FALSE;
        }
    }

#ifndef GDB /* The GDB stuff provides its own exception handlers. */

    /* Setup exception handlers for all exceptions. */
    for (index = 0; index < NUMBER_OF_EXCEPTIONS; index++)
    {
        idt_setup_interrupt_gate (index, SELECTOR_KERNEL_CODE,
            (address_t) exception_hardware_descriptions[index].handler, 
            PRIVILEGE_LEVEL_USER);
    }
    
    for (index = 0; index < NUMBER_OF_EXCEPTIONS; index++)
    {
        exception_register (index, &dummy_handler, NULL);
    }    
#endif

    return 0;
}


