#ifndef __INTERFACE_BLOCK_H__
#define __INTERFACE_BLOCK_H__

#define INTERFACE_BLOCK_ID 0x000B

enum
{
    METHOD_BLOCK_READ_ID,
    METHOD_BLOCK_WRITE_ID,

    METHOD_BLOCK_NUMBER
};

typedef uint32_t (block_read_t) (context_t context, 
    sequence_t blocks, uint32_t start);
typedef block_read_t * p_block_read_t;
    
typedef uint32_t (block_write_t) (context_t context, 
    sequence_t blocks, uint32_t start);
typedef block_write_t * p_block_write_t;
    

typedef struct
{
    p_block_read_t read;
    p_block_write_t write;
    
} block_interface_table_t;

typedef block_interface_table_t * p_block_interface_table_t;


static inline handle_reference_t block$handle$create (object_reference_t object)
{
    sequence_t seq_empty = {data: NULL, count: 0};

    return handle_create (object, INTERFACE_BLOCK_ID, seq_empty, 0);
}    


static inline uint32_t block$read (handle_reference_t handle, 
    sequence_t block, uint32_t start)
{
    uint32_t pars_in[] = {start};
    sequence_t pars_in_seq = {data: pars_in, count: 1};

    sequence_t empty_seq = {data: NULL, count: 0};

    uint32_t pars_out[] = {0, (uint32_t) block.data, block.count};
    sequence_t pars_out_seq = {data: pars_out, count: 2};

    handle_invoke_method (handle, METHOD_BLOCK_READ_ID, REFERENCE_NULL, 
        pars_in_seq, empty_seq, pars_out_seq, 0);

    return pars_out[0];
}    

static inline uint32_t block$write (handle_reference_t handle, 
    sequence_t block, uint32_t start)
{
    uint32_t pars_in[] = {(uint32_t) block.data, block.count, start};
    sequence_t pars_in_seq = {data: pars_in, count: 2};

    sequence_t empty_seq = {data: NULL, count: 0};

    uint32_t pars_out[] = {0};
    sequence_t pars_out_seq = {data: pars_out, count: 1};
    
    handle_invoke_method (handle, METHOD_BLOCK_WRITE_ID, REFERENCE_NULL,
        pars_in_seq, empty_seq, pars_out_seq, 0);

    return pars_out[0];
}    

#endif /* !__INTERFACE_BLOCK_H__ */
