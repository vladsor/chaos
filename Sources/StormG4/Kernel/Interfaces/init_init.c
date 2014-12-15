#include <enviroment.h>

#include "../interfaces.h"
#include "../classes.h"

#include <Classes/kernel.h>

#include <Classes/flat_namespace_object.h>
#include <Classes/storm_module.h>
#include <Classes/storm_program.h>

#include "init_interface.h"

#define DEBUG_MODULE_NAME L"Kernel{KernelControl}"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE1
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE2
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <debug/macros.h>
#include <exception/macros.h>
   
kernel_class_info_t kernel_classes_info[] = 
{
    [KERNEL_CLASS_FLAT_NAMESPACE_INDEX] = { 
        L"FlatNamespace", &flat_namespace_class_init, 
        REFERENCE_NULL, TRUE },

    [KERNEL_CLASS_STORM_MODULE_INDEX] = { 
        L"StormModule", &storm_module_class_init, 
        REFERENCE_NULL, TRUE },

    [KERNEL_CLASS_STORM_PROGRAM_INDEX] = { 
        L"StormProgram", &storm_program_class_init, 
        REFERENCE_NULL, TRUE },
};

#define NUMBER_OF_KERNEL_CLASSES (sizeof (kernel_classes_info) / \
    sizeof (kernel_class_info_t))
/*
typedef struct
{
    wchar_t *name;
    object_reference_t object;
    sequence_t parameters_in;
    sequence_t parameters_inout;
    sequence_t parameters_out;
    bool enabled;

} kernel_object_info_t;

static kernel_object_info_t kernel_objects_info[] = 
{
    flat_namespace
};        

#define NUMBER_OF_KERNEL_OBJECTS (sizeof (kernel_objects_info) / \
    sizeof (kernel_object_info_t))

static kernel_handle_info_t kernel_handles_info[] =
{
    flat_namespace,
    namespace,
    timer
};
*/

p_object_reference_t storm_module_objects;

object_reference_t kernel_object_root_flat_namespace = REFERENCE_NULL;
handle_reference_t kernel_handle_root_flat_namespace = REFERENCE_NULL;

handle_reference_t kernel_handle_namespace = REFERENCE_NULL;
handle_reference_t kernel_handle_timer = REFERENCE_NULL;

event_queue_reference_t kernel_debug_queue = REFERENCE_NULL;
event_supplier_reference_t kernel_supplier_debug = REFERENCE_NULL;
event_consumer_reference_t kernel_consumer_debug = REFERENCE_NULL;

extern description_reference_t debug_event_class;
extern description_reference_t irq_event_class;

#include "../static_modules.h"
static void init (context_t context UNUSED)
{
    uint32_t index;
    
    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
        L"%S: %s (%llX, %llX)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        context.object_data, context.handle_data);

    for (index = 0; index < NUMBER_OF_KERNEL_CLASSES; index++)
    {
        DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1, 
            L"%S: Registering class: \"%S\"\n",
            DEBUG_MODULE_NAME, 
            kernel_classes_info[index].name);
            
        kernel_classes_info[index].class = 
            kernel_classes_info[index].init ();
    }    
/*
    for (index = 0; index < NUMBER_OF_KERNEL_OBJECTS; index++)
    {
        DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
            L"%s: Init object: %S\n",
            DEBUG_MODULE_NAME, 
            kernel_objects_info[index].name);
            
        kernel_objects_info[index].object = object_create (
            kernel_classes_info[index].class);
    }    
*/
    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE2, 
        L"%S: Create root flat namespace {%p}\n",
        DEBUG_MODULE_NAME,
        kernel_classes_info[KERNEL_CLASS_FLAT_NAMESPACE_INDEX].class);
        
    kernel_object_root_flat_namespace = flat_namespace$create (
        kernel_classes_info[KERNEL_CLASS_FLAT_NAMESPACE_INDEX].class);
    kernel_handle_root_flat_namespace = flat_namespace$handle$create (
        kernel_object_root_flat_namespace);
        
    kernel_handle_namespace = namespace$handle$create (OBJECT_CURRENT);
    
    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE2, 
        L"%S: Handle for kernel namespace: %p\n",
        DEBUG_MODULE_NAME,
        kernel_handle_namespace);
    
    namespace$bind (kernel_handle_namespace, L"/Kernel/object", OBJECT_CURRENT);
    
    kernel_handle_timer = timer$handle$create (OBJECT_CURRENT);

    kernel_debug_queue = event_queue_create (debug_event_class,
        EVENT_QUEUE_TYPE_SYNCHRONOUS, 0);
    kernel_supplier_debug = debug$supplier$create (OBJECT_CURRENT);
    kernel_consumer_debug = debug$consumer$create (OBJECT_CURRENT);

    event_supplier_set_queue (kernel_supplier_debug, kernel_debug_queue);
    event_consumer_set_queue (kernel_consumer_debug, kernel_debug_queue);

    namespace$bind (kernel_handle_namespace, L"/Kernel/EventQueue/debug",
        kernel_debug_queue);

#if defined (TEST_EXC)
    EXCEPTION_TRY
    {
//        reference_t test;
//        test = namespace$resolve (kernel_handle_namespace, L"/Kernel2");
        ((p_uint32_t) NULL)[0] = UINT32_MAX;
    }
    EXCEPTION_CATCH_ALL (e)
    {
        uint32_t eflags;
        
        cpu_flags_save (eflags);
        
        DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1, 
            L"%S: Exception, current flags: %X\n",
            DEBUG_MODULE_NAME, 
            eflags);
    }
    EXCEPTION_FINALLY
    {
    }
    EXCEPTION_END_TRY;    

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1, 
        L"%S: Exception block done.\n",
        DEBUG_MODULE_NAME);
#endif
}

extern unsigned int arguments_parse (
    char *source,
    char **array_of_pointers);

static_module_info_t static_modules_info[] =
{
#if defined (STATIC_MODULE_PCI)
    { L"PCI",           &pci_main,          TRUE },
#endif

#if defined (STATIC_MODULE_PCNET32)
    { L"PCNet32",       &pcnet32_main,      TRUE },
#endif

#if defined (STATIC_MODULE_ATA)
    { L"ATA",           &ata_main,          TRUE },
#endif

#if defined (STATIC_MODULE_PARTITION)
    { L"Partition",     &partition_main,    TRUE },
#endif

#if defined (STATIC_MODULE_VFAT)
    { L"VFAT",          &vfat_main,         TRUE },
#endif

#if defined (STATIC_MODULE_KEYBOARD)
    { L"Keyboard",      &keyboard_main,     TRUE },
#endif

#if defined (STATIC_MODULE_MOUSE)
    { L"Mouse",         &mouse_main,        TRUE },
#endif

#if defined (STATIC_MODULE_VGA)
    { L"VGA",           &vga_main,          TRUE },
#endif

#if defined (STATIC_MODULE_CONSOLE)
    { L"Console",       &console_main,      TRUE },
#endif
};

#define NUMBER_OF_STATIC_MODULES (sizeof (static_modules_info) / \
    sizeof (static_module_info_t))

static void start (context_t context UNUSED)
{
    uint32_t index;

#ifndef NO_STATIC_MODULES
    return_t return_value;

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1,
        L"%S: Starting static modules. Number of modules: %u.\n", 
        DEBUG_MODULE_NAME,
        NUMBER_OF_STATIC_MODULES);

    for (index = 0; index < NUMBER_OF_STATIC_MODULES; index++)
    {
        if (static_modules_info[index].enabled)
        {
            DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1, 
                L"%S: Starting module \'%S\'.\n",
                DEBUG_MODULE_NAME, 
                static_modules_info[index].name);
/*
            string_copy (temp_buffer, subsystem_built_in[index].name);
            
            if (!string_is_empty (subsystem_built_in[index].parameters))
            {
                string_append (temp_buffer, " ");
                string_append (temp_buffer, 
                    subsystem_built_in[index].parameters);
            }
            
            number_of_arguments = arguments_parse (temp_buffer, 
                array_of_arguments);
                            
            return_value = subsystem_built_in[index].init (number_of_arguments, 
                array_of_arguments, storm_environ);
*/
            return_value = static_modules_info[index].main (0, NULL, NULL);
            
            if (return_value != 0)
            {
                static_modules_info[index].enabled = FALSE;
            }
        }
    }
#endif

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1, 
        L"%S: Starting dynamic modules. Number of modules: %u.\n", 
        DEBUG_MODULE_NAME,
        storm_info.number_of_modules);
      
    if (storm_info.number_of_modules > 0)
    {
#ifdef MODULE_TYPE_MODULE
        char temp_buffer[STRING_MAX_LENGTH];
        uint32_t number_of_arguments;
        char *array_of_arguments[STRING_MAX_LENGTH / 2];
        wchar_t module_name[WSTRING_MAX_LENGTH];
        handle_reference_t handle;

        memory_allocate ((p_p_void_t) &storm_module_objects,
            sizeof (object_reference_t) * storm_info.number_of_modules);
        memory_clear (storm_module_objects, 
            sizeof (object_reference_t) * storm_info.number_of_modules);
	
        /* Check what modules GRUB has provided for us. */
        for (index = 0; index < storm_info.number_of_modules; index++)
        {
            DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1, 
                L"%S: Starting module \"%s\".\n", 
                DEBUG_MODULE_NAME,
                storm_info.module_info[index].name);
            
            storm_module_objects[index] = storm_module_factory$create (
                kernel_classes_info[KERNEL_CLASS_STORM_MODULE_INDEX].class, 
                (elf_header_t *) storm_info.module_info[index].start);

            string_copy (temp_buffer, storm_info.module_info[index].name);                

            number_of_arguments = arguments_parse (temp_buffer, 
                array_of_arguments);
       
            wstring_print (module_name, L"/Kernel/Modules%s", 
                string_find_last_char (array_of_arguments[0], '/'));
            namespace$bind (kernel_handle_namespace, module_name, 
                storm_module_objects[index]);
            
            handle = storm_module_control$handle$create (
                storm_module_objects[index]);
            
            storm_module_control$start (handle, number_of_arguments, 
                array_of_arguments, NULL);

        	DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1, 
            	 L"%S: Module %s started successfull.\n", 
            	 DEBUG_MODULE_NAME,
                 storm_info.module_info[index].name);
             
            handle_destroy (handle);
		
            physical_memory_deallocate (&physical_memory_global,
                PAGE_NUMBER (storm_info.module_info[index].start),
                SIZE_IN_PAGES (storm_info.module_info[index].end - 
                    storm_info.module_info[index].start));
        }
#else
        object_reference_t object;
        handle_reference_t handle;

        for (index = 0; index < storm_info.number_of_modules; index++)
        {
            DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1,
                L"%S: Starting program \"%s\".\n",
                DEBUG_MODULE_NAME,
                storm_info.module_info[index].name);

            object = storm_program_factory$create (
                kernel_classes_info[KERNEL_CLASS_STORM_PROGRAM_INDEX].class,
                (elf_header_t *) storm_info.module_info[index].start);

            handle = storm_program_control$handle$create (object);

            storm_program_control$main (handle, 0, NULL, NULL);
        }
#endif
    }
}

static void stop (context_t context UNUSED)
{
}

static kernel_control_interface_table_t table =
{
    init: &init,
    start: &start,
    stop: &stop,
};

/* Main function. */

interface_reference_t kernel_control_init (void)
{
    return kernel_control_interface_register (&table);
}

