#include "../configuration.h"

typedef return_t (main_function_t) (int argc, char *argv[], char **envp);

typedef struct
{
    char name[STRING_MAX_LENGTH];
    main_function_t *init;
    bool enabled;
    char parameters[STRING_MAX_LENGTH];
} subsystem_built_in_t;


extern main_function_t keyboard_main;
extern main_function_t mouse_main;

extern main_function_t pci_main;
extern main_function_t riva_main;
extern main_function_t vga_main;
extern main_function_t console_main;

extern main_function_t ramdisk_init;
extern main_function_t floppy_init;
extern main_function_t ata_main;
extern main_function_t partition_main;

extern main_function_t vfat_main;

extern void posix_init (void);
extern int main (int argc, char *argv[], char **envp);


subsystem_built_in_t subsystem_built_in[] =
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

#ifdef SUBSYSTEM_GLOBAL_MEMORY        
    {"global_memory",     &global_memory_init,    TRUE,  ""},
#endif    

#ifdef SUBSYSTEM_USER_MEMORY        
    {"global_memory",     &user_memory_init,      TRUE,  ""},
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

#if defined (SUBSYSTEM_IRQ) && defined (SUBSYSTEM_TIMER) 
    {"timer",             &timer_init,            TRUE,  ""},
#endif

#if defined (SUBSYSTEM_TIMER) && defined (SUBSYSTEM_THREAD)
    {"thread",            &thread_init,           TRUE,  ""},
#endif

#if defined (SUBSYSTEM_PROCESS) && defined (SUBSYSTEM_THREAD)
    {"process",           &process_init,          TRUE,  ""},
#endif

#if defined (SUBSYSTEM_REPOSITORY)
    {"repository",        &repository_init,       TRUE,  ""},
#endif

#if defined (SUBSYSTEM_REGISTER)
    {"register",          &register_init,         TRUE,  ""},
#endif

//    {"ramdisk", &ramdisk_init, TRUE},

//    {"floppy",            &floppy_init,            TRUE,  ""},
//    {"keyboard",    keyboard_main,        TRUE,  ""},
//    {"mouse",         mouse_main,             TRUE,  ""},

//    {"ata", &ata_main, TRUE, ""},
//    {"partitition", &partition_main, TRUE, ""},
//    {"vfat", &vfat_main, TRUE},

//    {"system_call", system_call_init},
//    {"pci", &pci_main, TRUE, ""},
//    {"riva", &riva_main, TRUE, ""},
//    {"vga", &vga_main, TRUE, ""},
//    {"console", &console_main, TRUE, ""},
#if defined (SUBSYSTEM_POSIX)
    {"posix",             &posix_init,            TRUE,  ""},
#endif

#if defined (SUBSYSTEM_PROGRAM)
    {PROGRAM_NAME,        &main,                  TRUE,  ""},
#endif
};

#define NUMBER_OF_BUILT_IN (sizeof (subsystem_built_in) / \
    sizeof (subsystem_built_in_t))


