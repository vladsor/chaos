#ifndef __INTERFACE_STORM_MODULE_H__
#define __INTERFACE_STORM_MODULE_H__

#define IID_STORM_MODULE 0x00000AFF

enum
{
    MID_STORM_MODULE_START,
    MID_STORM_MODULE_STOP,
};

typedef return_t (storm_module_start_function_t) (context_t *context, 
    uint32_t argc, char *argv[]);

typedef return_t (storm_module_stop_function_t) (context_t *context);

    
typedef struct
{
    storm_module_start_function_t *start;
    storm_module_stop_function_t *stop;
} storm_module_interface_t;

typedef struct
{
    storm_module_start_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[3];

} storm_module_start_method_t;

typedef struct
{
    uint8_t *block;
    uint64_t start_block;
    uint64_t number_of_blocks;
} block_read_parameters_t;

#define STORM_MODULE_START_METHOD(function) \
    (&(function)), \
    (MID_STORM_MODULE_START), \
    (sizeof (block_read_parameters_t)), \
    (3), \
    { \
        {sizeof (uint8_t *)}, \
        {sizeof (uint64_t)}, \
        {sizeof (uint64_t)} \
    }
    

typedef struct
{
    storm_module_stop_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[3];

} storm_module_stop_method_t;

typedef struct
{
    uint8_t *block;
    uint64_t start_block;
    uint64_t number_of_blocks;
} block_write_parameters_t;

#define STORM_MODULE_STOP_METHOD(function) \
    (&(function)), \
    (MID_STORM_MODULE_STOP), \
    (sizeof (block_write_parameters_t)), \
    (3), \
    { \
        {sizeof (uint8_t *)}, \
        {sizeof (uint64_t)}, \
        {sizeof (uint64_t)} \
    }
    

#define storm_module$start(handle,argc,argv) \
    ((storm_module_interface_t *) ((handle)->functions))->start ( \
        &((handle)->context), \
        (argc), (argv))

#define storm_module$stop(handle) \
    ((storm_module_interface_t *) ((handle)->functions))->stop ( \
        &((handle)->context))


#endif /* !__INTERFACE_STORM_MODULE_H__ */

