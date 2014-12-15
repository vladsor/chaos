typedef return_t (init_function_t) (interface_id_t *interface_id);

typedef struct
{
    char *name;
    init_function_t *init;
    bool enabled;

} object_built_in_t;


object_built_in_t objects_built_in[] =
{
    {"debug",             &object_debug_init, TRUE },

#ifdef SUBSYSTEM_CPU
    {"cpu",               &object_cpu_init,              TRUE },
#endif

//#ifdef SUBSYSTEM_EXCEPTION    
//    {"exception",         &exception_init,        TRUE },
//#endif

#ifdef SUBSYSTEM_MEMORY    
    {"memory",            &object_memory_init,  TRUE },
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

#define NUMBER_OF_BUILT_IN (sizeof (objects_built_in) / \
    sizeof (object_built_in_t))
