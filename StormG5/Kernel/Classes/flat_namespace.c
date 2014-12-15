#include <enviroment.h>

#include "../classes.h"
#include "../interfaces.h"

#include <Classes/flat_namespace_object.h>

#include "flat_namespace.h"

#define DEBUG_MODULE_NAME "FlatNamespaceClass"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>
#include <exception/macros.h>

static description_reference_t class_description;

/* Main function. */

class_reference_t flat_namespace_class_init (void)
{
    class_reference_t class;

    class_description = class_description_register (
        CLASS_FLAT_NAMESPACE_OBJECT_ID,
        L"FlatNamespace",
        CLASS_TYPE_STATIC);

    class = class_create (class_description, 
        kernel_interfaces_info[
            KERNEL_INTERFACE_FLAT_NAMESPACE_OBJECT_FACTORY_INDEX].interface, 0);

    flat_namespace_init (class);
    
    return class;
}

