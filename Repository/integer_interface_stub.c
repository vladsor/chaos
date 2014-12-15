
static integer_get_method_t integer_get_method =
{
    INTEGER_GET_METHOD (integer_get)
};

static integer_set_method_t integer_set_method =
{
    INTEGER_SET_METHOD (integer_set)
};

static method_t *methods[] = 
{
    (method_t *) &integer_get_method,
    (method_t *) &integer_set_method,
};

interface_t integer_interface_register (integer_interface_t *integer_interface)
{
    return interface_register (IID_INTEGER, 
        INTERFACE_TYPE_DYNAMIC, number_of_methods, methods);
}
