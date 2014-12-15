
#define IID_INTEGER_CONTROL 0x00000D00

typedef struct
{
    uint32_t value;
} integer_create_parameters_t;

#define integer$create(handle,cid,value)
do {
    integer_create_parameters_t parameters = {(value)};
    repository_object_create ((handle), (cid), &parameters);
} while (0)
