
#define IID_BLOCK 0x00000A01

enum
{
    MID_BLOCK_READ,
    MID_BLOCK_WRITE,
};

typedef return_t (block_read_function_t) (context_t *context, uint8_t *block,
    uint64_t offset, uint64_t length);
typedef return_t (block_write_function_t) (context_t *context, uint8_t *block,
    uint64_t offset, uint64_t length);
    
typedef struct
{
    block_read_function_t *read;
    block_write_function_t *write;
} block_interface_t;

typedef struct
{
    block_read_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[3];

} block_read_method_t;

typedef struct
{
    uint8_t *block;
    uint64_t start_block;
    uint64_t number_of_blocks;
} block_read_parameters_t;

#define BLOCK_READ_METHOD(function) \
    (&(function)), \
    (MID_BLOCK_READ), \
    (sizeof (block_read_parameters_t)), \
    (3), \
    { \
        {sizeof (uint8_t *)}, \
        {sizeof (uint64_t)}, \
        {sizeof (uint64_t)} \
    }    

typedef struct
{
    block_write_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[3];

} block_write_method_t;

typedef struct
{
    uint8_t *block;
    uint64_t start_block;
    uint64_t number_of_blocks;
} block_write_parameters_t;

#define BLOCK_WRITE_METHOD(function) \
    (&(function)), \
    (MID_BLOCK_WRITE), \
    (sizeof (block_write_parameters_t)), \
    (3), \
    { \
        {sizeof (uint8_t *)}, \
        {sizeof (uint64_t)}, \
        {sizeof (uint64_t)} \
    }    

#define block$read(handle,block,offset,length) \
    if ((handle->interface == NULL)
    {
        THROW (EXCEPTION_INVALID_PARAMETERS);
    }
    else if ((handle->interface->id != IID_BLOCK)
    {
        THROW (EXCEPTION_INVALID_PARAMETERS);
    }

    ((block_interface_t *) ((handle)->interface))->read ( \
        &((handle)->context), \
        (block), (offset), (length))

#define block$write(handle,block,offset,length) \
    ((block_interface_t *) ((handle)->functions))->write ( \
        &((handle)->context), \
        (block), (offset), (length))



