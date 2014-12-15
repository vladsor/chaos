object_create_method_t integer_create_method =
{
    &integer_create,
    MID_OBJECT_CREATE,
    sizeof (void *),
    1,
    {
        {sizeof (void *)}
    }
};

object_destroy_method_t integer_destroy_method =
{
    &integer_destroy,
    MID_OBJECT_DESTROY,
    0,
    0,
};

static method_t *control_methods[] = 
{
    (method_t *) &integer_create_method,
    (method_t *) &integer_destroy_method,
};

#define number_of_control_methods 2

interface_t integer_value_repository_interface_register ()
{
    return_value = register_interface_register (&integer_control_id, 
        IID_INTEGER_CONTROL, INTERFACE_TYPE_CONTROL, number_of_control_methods, 
        control_methods, NULL);
}