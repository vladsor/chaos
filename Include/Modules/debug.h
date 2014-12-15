extern handle_t handle_debug;

static inline return_t system_debug_print (uint8_t level, char *module_name, 
    char *function_name, uint32_t function_line, char *message)
{
    return debug$print (&handle_debug, level, module_name, function_name,
        function_line, message);
}


