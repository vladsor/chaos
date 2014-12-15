#include <enviroment.h>

//#include <Classes/kernel.h>
#include "interface.h"

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

handle_t handle_namespace = {HANDLE_HEADER_KERNEL, NULL};
handle_t handle_cpu = {HANDLE_HEADER_KERNEL, NULL};;
handle_t handle_debug = {HANDLE_HEADER_KERNEL, NULL};;
handle_t handle_dma = {HANDLE_HEADER_KERNEL, NULL};;
handle_t handle_io_port = {HANDLE_HEADER_KERNEL, NULL};;
handle_t handle_irq = {HANDLE_HEADER_KERNEL, NULL};;
handle_t handle_memory = {HANDLE_HEADER_KERNEL, NULL};;
handle_t handle_timer = {HANDLE_HEADER_KERNEL, NULL};;
handle_t handle_thread = {HANDLE_HEADER_KERNEL, NULL};;

return_t module_start (int argc, char *argv[])
{
    return_t return_value;

    register_object_open (&handle_namespace, IID_NAMESPACE);
    register_object_open (&handle_cpu, IID_CPU);
    register_object_open (&handle_debug, IID_DEBUG);
    register_object_open (&handle_dma, IID_DMA);
    register_object_open (&handle_io_port, IID_IO_PORT);
    register_object_open (&handle_irq, IID_IRQ);
    register_object_open (&handle_memory, IID_MEMORY);
    register_object_open (&handle_timer, IID_TIMER);
    register_object_open (&handle_thread, IID_THREAD);

    return_value = pcnet32_main (argc, argv);
    
    return return_value;
}

return_t module_stop (void)
{
    return 0;
}
