
#define IID_SEMAPHORE_CONTROL 0x00000004

typedef struct
{
    uint32_t value;
    uint32_t max;
} semaphore_create_parameters_t;

