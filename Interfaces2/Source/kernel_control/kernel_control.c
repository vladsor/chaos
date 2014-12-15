#include <enviroment.h>

#include <Interfaces/kernel_control.h>
#include "kernel_control.h"

#define DEBUG_MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

interface_reference_t kernel_control_interface_register (
    p_kernel_control_interface_table_t table)
{
    description_reference_t interface_description;
    description_reference_t method_description_init;
    description_reference_t method_description_start;
    description_reference_t method_description_stop;
    
    sequence_t empty_seq = {data: NULL, count: 0};
    interface_reference_t interface;

    interface_description = interface_description_register (
        INTERFACE_KERNEL_CONTROL_ID,
        L"kernel_control",
        INTERFACE_TYPE_DYNAMIC,
        empty_seq);
    
    method_description_init = method_description_register (
        interface_description,
        METHOD_KERNEL_CONTROL_INIT_ID,
        L"init",
        METHOD_TYPE_DYNAMIC,
        NULL,
        empty_seq,
        empty_seq);

    method_description_start = method_description_register (
        interface_description,
        METHOD_KERNEL_CONTROL_START_ID,
        L"start",
        METHOD_TYPE_DYNAMIC,
        NULL,
        empty_seq,
        empty_seq);

    method_description_stop = method_description_register (
        interface_description,
        METHOD_KERNEL_CONTROL_STOP_ID,
        L"stop",
        METHOD_TYPE_DYNAMIC,
        NULL,
        empty_seq,
        empty_seq);

    interface = interface_create (class_reference, 
        interface_description, REFERENCE_NULL, 0);
    
    (void) method_create (interface,
        method_description_init, REFERENCE_NULL,
        (address_t) table->init, 0);


    (void) method_create (interface,
        method_description_start, REFERENCE_NULL,
        (address_t) table->start, 0);

    (void) method_create (interface,
        method_description_stop, REFERENCE_NULL,
        (address_t) table->stop, 0);
    
    return interface;
}

