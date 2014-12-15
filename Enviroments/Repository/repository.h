#ifndef __ENVIROMENT_REPOSITORY__
#define __ENVIROMENT_REPOSITORY__

typedef uint32_t id_t;

#define ID_NONE ((id_t) 0)

#if defined (__STORM_KERNEL__) || defined (__STORM_KERNEL_MODULE__)

typedef void * reference_t;
#define REFERENCE_NULL (NULL)

#elif defined (__STORM_PROGRAM__)

typedef id_t reference_t;
#define REFERENCE_NULL (ID_NONE)
/*
#else
#error "Unknown target of object file"
*/
#endif

typedef reference_t * p_reference_t;
typedef reference_t description_reference_t;

typedef reference_t event_class_reference_t;
typedef event_class_reference_t * p_event_class_reference_t;

typedef reference_t event_supplier_interface_reference_t;
typedef event_supplier_interface_reference_t * 
    p_event_supplier_interface_reference_t;

typedef reference_t event_consumer_interface_reference_t;
typedef event_consumer_interface_reference_t * 
    p_event_consumer_interface_reference_t;

typedef reference_t class_reference_t;
typedef class_reference_t * p_class_reference_t;

typedef reference_t object_reference_t;
typedef object_reference_t * p_object_reference_t;

typedef reference_t handle_reference_t;
typedef handle_reference_t * p_handle_reference_t;

typedef reference_t event_supplier_reference_t;
typedef event_supplier_reference_t * p_event_supplier_reference_t;

typedef reference_t event_consumer_reference_t;
typedef event_consumer_reference_t * p_event_consumer_reference_t;

typedef reference_t event_queue_reference_t;
typedef event_queue_reference_t * p_event_queue_reference_t;

typedef reference_t quality_reference_t;

typedef reference_t exception_reference_t;
typedef reference_t method_reference_t;
typedef reference_t interface_reference_t;

typedef interface_reference_t * p_interface_reference_t;
typedef exception_reference_t * p_exception_reference_t;

typedef reference_t security_reference_t;
typedef security_reference_t * p_security_reference_t;

typedef reference_t cpu_reference_t;
typedef cpu_reference_t * p_cpu_reference_t;

typedef reference_t memory_reference_t;
typedef memory_reference_t * p_memory_reference_t;

typedef reference_t computer_reference_t;
typedef computer_reference_t * p_computer_reference_t;


//----------------------------------------------
#include "System/reference.h"
#include "reference.h"
//----------------------------------------------

#include "context.h"
#include "function.h"

#include "Descriptions/reference.h"
#include "Descriptions/data.h"
#include "System/Descriptions/exception.h"
#include "Descriptions/method.h"
#include "Descriptions/event.h"
#include "Descriptions/interface.h"
#include "Descriptions/class.h"


#include "System/security.h"

//----------------------------------------------
#include "System/method.h"
#include "method.h"
//----------------------------------------------
#include "System/interface.h"
#include "interface.h"
//----------------------------------------------
#include "System/class.h"
#include "class.h"
//----------------------------------------------
#include "System/object.h"
#include "System/Static/object.h"
#include "object.h"
//----------------------------------------------
#include "System/handle.h"
#include "handle.h"
//----------------------------------------------
#include "System/quality.h"
#include "System/cpu.h"
#include "System/memory.h"

//----------------------------------------------
#include "System/computer.h"
#include "computer.h"
//----------------------------------------------
#include "System/event_supplier_interface.h"
#include "event_supplier_interface.h"
//----------------------------------------------
#include "System/event_consumer_interface.h"
#include "event_consumer_interface.h"
//----------------------------------------------

#include "System/event_queue.h"
#include "event_queue.h"

//----------------------------------------------
#include "System/event_supplier.h"
#include "System/Static/event_supplier.h"
#include "event_supplier.h"
//----------------------------------------------
#include "System/event_consumer.h"
#include "event_consumer.h"
//----------------------------------------------

#include "Interfaces/object_factory.h"
#include "Interfaces/handle_factory.h"
#include "Interfaces/event_supplier_factory.h"
#include "Interfaces/event_consumer_factory.h"

extern return_t memory_allocate (void **pointer, unsigned int size);
extern return_t memory_deallocate (void *pointer);

extern return_t repository_init (int argc, char *argv[], char **envp);

#endif /* !__ENVIROMENT_REPOSITORY__ */

