#include "integer_interface.h"

#define CLASS_INTEGER_VALUE_ID 0x0001

#define NUMBER_OF_INTEGER_VALUE_INTERFACES (1)

extern class_reference_t integer_value_class_register (
    object_reference_t class_repository, p_integer_interface_table_t table);
