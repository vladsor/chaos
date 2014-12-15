
#include <Classes/kernel.h>
extern handle_reference_t kernel_handle_namespace;
extern event_queue_reference_t kernel_debug_queue;

#include <Classes/ata_manager.h>
#include <Classes/ata_drive.h>

extern class_reference_t ata_drive_class;
extern event_consumer_reference_t irq14_consumer;
extern event_consumer_reference_t irq15_consumer;
extern event_supplier_reference_t ata_debug_supplier;

extern return_t ata_main (int argc, char *argv[], char **envp);


