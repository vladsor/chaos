
#define IID_CONSOLE_CONTROL 0x00002000

typedef struct
{
    unsigned int width;
    unsigned int height;
    unsigned int depth;
    unsigned int mode_type;
} console_attribute_t;

typedef struct
{
    console_attribute_t attribute;
} console_create_parameters_t;

