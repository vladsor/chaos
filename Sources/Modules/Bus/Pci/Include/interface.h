
extern return_t pci_main (int argc, char *argv[], char **envp);

#include <Classes/kernel.h>
extern handle_reference_t kernel_handle_namespace;
extern handle_reference_t kernel_handle_timer;
extern event_queue_reference_t kernel_debug_queue;

extern event_supplier_reference_t pci_debug_supplier;


