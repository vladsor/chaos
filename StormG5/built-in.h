static char **kernel_environment = (char *[])
{
    NULL,
};

kernel_info_t kernel_info =
{
    version: STORM_VERSION_STRING,
    compiler: COMPILER,
    compiler_version: __VERSION__,
    maintainer: CREATOR,
    build_date: __DATE__,
    build_time: __TIME__,
    command_line: "",
    memory_size: 0,
    number_of_memory_maps: 0,
    memory_map:
    {
        {
            size: 0,
            base_address: NULL,
            length: 0,
            type: 0,
        },
    },
    number_of_modules: 0,
    module_info:
    {
        {
            start: 0,
            end: 0,
            name: "",
        },
    }

    subsystem_built_in:
    {
#ifdef SUBSYSTEM_SYSTEM_DEBUG
        {"system_debug",      &system_debug_init,     TRUE,  ""},
#endif

#ifdef SUBSYSTEM_CPU
        {"cpu",               &cpu_init,              TRUE,  ""},
#endif

#ifdef SUBSYSTEM_EXCEPTION    
        {"exception",         &exception_init,        TRUE,  ""},
#endif

#ifdef SUBSYSTEM_PHYSICAL_MEMORY    
        {"physical_memory",   &physical_memory_init,  TRUE,  ""},
#endif    

#ifdef SUBSYSTEM_VIRTUAL_MEMORY    
        {"virtual_memory",    &virtual_memory_init,   TRUE,  ""},
#endif

#ifdef SUBSYSTEM_PORT
        {"port",              &port_init,             TRUE,  ""},
#endif

#ifdef SUBSYSTEM_DMA
        {"dma",               &dma_init,              TRUE,  ""},
#endif

#ifdef SUBSYSTEM_IRQ
        {"irq",               &irq_init,              TRUE,  ""},
#endif

#ifdef SUBSYSTEM_CLOCK
        {"clock",             &clock_init,            TRUE,  ""},
#endif

#if defined (SUBSYSTEM_TIMER) 
        {"timer",             &timer_init,            TRUE,  ""},
#endif

#if defined (SUBSYSTEM_TASK_STATE) 
        {"task_state",        &task_state_init,       TRUE,  ""},
#endif

#if defined (SUBSYSTEM_SYSTEM_CALL)
        {"system_call",       &system_call_init,      TRUE,  ""},
#endif

#if defined (SUBSYSTEM_REPOSITORY)
        {"repository",        &repository_init,       TRUE,  ""},
#endif
    },
};
