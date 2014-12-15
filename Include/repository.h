
typedef uint32_t handle_id_t;
typedef handle_id_t * p_handle_id_t;

typedef uint32_t object_id_t;
typedef object_id_t * p_object_id_t;

typedef uint32_t class_id_t;
typedef class_id_t * p_class_id_t;

typedef uint32_t interface_id_t;
typedef interface_id_t * p_interface_id_t;

typedef uint32_t method_id_t;
typedef method_id_t * p_method_id_t;

typedef uint32_t exception_id_t;
typedef exception_id_t * p_exception_id_t;

typedef uint32_t security_id_t;
typedef security_id_t * p_security_id_t;

#if defined (__STORM_KERNEL__) || defined (__STORM_KERNEL_MODULE__)
typedef struct handle_t * handle_reference_t;
typedef struct object_t * object_reference_t;
typedef struct class_t * class_reference_t;
typedef struct interface_t * interface_reference_t;
typedef struct exception_t * exception_reference_t;
typedef struct security_t * security_reference_t;

#elif defined (__STORM_PROGRAM__)
typedef object_id_t object_reference_t;
typedef class_id_t class_reference_t;
typedef interface_id_t interface_reference_t;
typedef security_id_t security_reference_t;

#else
#error "Unknown target of object file"
#endif

typedef handle_reference_t * p_handle_reference_t;
typedef object_reference_t * p_object_reference_t;
typedef class_reference_t * p_class_reference_t;
typedef interface_reference_t * p_interface_reference_t;
typedef exception_reference_t * p_exception_reference_t;
typedef security_reference_t * p_security_reference_t;


#include "Repository/exception.h"
#include "Repository/method.h"
#include "Repository/interface.h"
#include "Repository/class.h"
#include "Repository/object.h"
#include "Repository/handle.h"
#include "Repository/security.h"

extern return_t repository_init (int argc, char *argv[], char **envp);

