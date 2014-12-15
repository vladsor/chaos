
typedef return_t (util_class_init_function_t) (p_class_id_t class_id);
typedef util_class_init_function_t *p_init_function_t;

typedef struct
{
    char *name;
    p_util_class_init_function_t init;
    bool enabled;

} util_class_info_t;

util_class_info_t util_classes_info[] =
{
    {"integer",             &object_debug_init,            TRUE },

    {"large_integer",               &object_cpu_init,              TRUE },

    {"event_channel",            &object_memory_init,           TRUE },
    
    {"stream_channel",           &object_io_port_init,          TRUE },
};

#define NUMBER_OF_UTIL_CLASSES (sizeof (util_classes_info) / \
    sizeof (util_class_info_t))
    
