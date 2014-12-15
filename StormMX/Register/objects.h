//#include "configuration.h"

extern return_t namespace_init (interface_id_t *interface_id);

extern return_t object_cpu_init (interface_id_t *interface_id);
extern return_t object_debug_init (interface_id_t *interface_id);
extern return_t object_dma_init (interface_id_t *interface_id);
extern return_t object_io_port_init (interface_id_t *interface_id);
extern return_t object_irq_init (interface_id_t *interface_id);
extern return_t object_memory_init (interface_id_t *interface_id);
extern return_t object_timer_init (interface_id_t *interface_id);
extern return_t object_thread_init (interface_id_t *interface_id);


extern class_id_t integer_class_id;
#define INTEGER_CLASS_ID integer_class_id

extern return_t integer_init (void);
extern return_t mutex_init (int argc, char *argv[]);
extern return_t semaphore_init (int argc, char *argv[]);
extern return_t event_channel_init (int argc, char *argv[]);
extern return_t stream_channel_init (int argc, char *argv[]);
extern return_t storm_module_init (int argc, char *argv[]);
