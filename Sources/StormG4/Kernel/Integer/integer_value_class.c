#include <enviroment.h>

#include "integer_value_class.h"

#define MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

static interface_reference_t interfaces[NUMBER_OF_INTEGER_VALUE_INTERFACES];

static class_description_t integer_value_class_description =
{
/*    class_id_t id; */
    CLASS_INTEGER_VALUE_ID,

/*    wchar_t name[WSTRING_MAX_LENGTH]; */
    L"integer_value",

/*    uint32_t type; */
    CLASS_TYPE_STATIC,
    
/*    uint32_t number_of_interfaces; */
    0
};

class_reference_t integer_value_class_register (
    object_reference_t class_repository, p_integer_interface_table_t table)
{
    sequence_t seqs = {(void **) interfaces, NUMBER_OF_INTEGER_VALUE_INTERFACES,
        sizeof (interface_reference_t) };

    interfaces[0] = integer_interface_register (table);

    return class_create (&integer_value_class_description, seqs, class_repository);
}

