
typedef struct
{
    uint32_t max;
    uint32_t average;
    uint32_t min;
    
    uint32_t max_burst;
} resource_usage_t;

typedef struct
{
    uint32_t lost_probability;
    uint32_t time_delay;
    uint32_t latency;
} quality_t;
