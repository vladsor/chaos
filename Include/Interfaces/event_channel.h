
#define IID_EVENT_CHANNEL 0x00000C00

typedef struct
{
    size_t event_data_size;
    uint32_t max_events;
} event_channel_create_parameters_t;

