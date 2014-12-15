
enum policy_t
{
    POLICY_UNSPECIFIED,
    POLICY_CONSTANT,
    POLICY_REALTIME_VARIABLE,
    POLICY_NON_REALTIME_VARIABLE,
    POLICY_AVAILABLE,
};

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

#define QUALITY_CURRENT (NULL)

extern void quality_set (quality_reference_t quality_reference, uint32_t delay);
extern void quality_reset (quality_reference_t quality_reference);

