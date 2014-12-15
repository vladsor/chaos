
#define IID_INTEGER_CONTROL 0x00000D00

typedef struct
{
    uint32_t value;
} integer_create_parameters_t;

#define integer$create(handle,integer_value) \
do { \
    integer_create_parameters_t parameters; \
    parameters.value = (integer_value); \
    register_object_create ((handle), (INTEGER_CLASS_ID), &parameters); \
} while (0)
