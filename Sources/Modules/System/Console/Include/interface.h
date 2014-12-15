
extern return_t console_main (int argc, char *argv[], char **envp);

#include <Classes/kernel.h>

extern handle_reference_t kernel_handle_namespace;
extern event_queue_reference_t kernel_debug_queue;

extern event_supplier_reference_t console_debug_supplier;

