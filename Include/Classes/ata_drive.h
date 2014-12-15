
#define CLASS_ATA_DRIVE_ID 0x0006

#include <Interfaces/block.h>

static inline object_reference_t ata$create (class_reference_t class)
{
    sequence_t pars_seq = {data: NULL, count: 0};
    
    return object_create (class, SECURITY_CURRENT, pars_seq, 0);
}



