
#define CLASS_PARTITION_ID 0x0007

#include <Interfaces/block.h>

static inline object_reference_t partition$create (
    class_reference_t class)
{
    sequence_t seq_empty = {data: NULL, count: 0};
    
    return object_create (class, SECURITY_CURRENT, seq_empty, 0);
}

