#ifndef __CLASS_KERNEL_H__
#define __CLASS_KERNEL_H__

#define CLASS_KERNEL_ID 0x0001

#include <Interfaces/init.h>
#include <Interfaces/namespace.h>
#include <Interfaces/timer.h>

#include <Interfaces/irq.h>
#include <Interfaces/debug.h>


static inline object_reference_t kernel$create (
    class_reference_t class)
{
    sequence_t seq_empty = {data: NULL, count: 0};
    
    return object_create (class, SECURITY_ABSOLUTE, seq_empty, 0);
}


#endif /* !__CLASS_KERNEL_H__ */
