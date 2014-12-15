
typedef return_t (kernel_interface_init_function_t) (
    p_interface_id_t interface_id);
typedef kernel_interface_init_function_t *p_kernel_interface_init_function_t;

typedef struct
{
    char *name;
    p_kernel_interface_init_function_t init;
    bool enabled;

} kernel_interface_info_t;

kernel_interface_info_t kernel_interfaces_info[] =
{
#ifdef SUBSYSTEM_SYSTEM_DEBUG
    {"debug",             &object_debug_init,            TRUE },
#endif

#ifdef SUBSYSTEM_CPU
    {"cpu",               &object_cpu_init,              TRUE },
#endif

//#ifdef SUBSYSTEM_EXCEPTION    
//    {"exception",         &exception_init,        TRUE },
//#endif

#ifdef SUBSYSTEM_MEMORY    
    {"memory",            &object_memory_init,           TRUE },
#endif    
    
#ifdef SUBSYSTEM_IO_PORT
    {"io port",           &object_io_port_init,          TRUE },
#endif

#ifdef SUBSYSTEM_DMA
    {"dma",               &object_dma_init,              TRUE },
#endif

#ifdef SUBSYSTEM_IRQ
    {"irq",               &object_irq_init,              TRUE },
#endif

#if defined (SUBSYSTEM_IRQ) && defined (SUBSYSTEM_TIMER) 
    {"timer",             &object_timer_init,            TRUE },
#endif

#ifdef SUBSYSTEM_THREAD
    {"thread",            &object_thread_init,           TRUE },
#endif

    {"namespace",         &namespace_init,               TRUE },
};

#define NUMBER_OF_KERNEL_INTERFACES (sizeof (kernel_interfaces_info) / \
    sizeof (kernel_interface_info_t))
    
