/* Author: Vladimir Sorokin. */

/* Copyright 2004 chaos development. */

#ifndef __COMMON_CPU_H__
#define __COMMON_CPU_H__

typedef struct
{
    uint8_t platform;
  
    uint16_t cpu_type_id;
    uint16_t cpu_sub_type_id;
    uint8_t fpu_type_id;
    uint8_t vendor_id;

    char hard_cpu_name[49];
    char vendor_string[13];

    uint32_t frequency;

    char family;
    char model;
    char stepping;
    char generation;

    uint32_t data_cache_l1_size;
    uint32_t instructions_cache_l1_size;  
    uint32_t cache_l2_size;
    bool features[NUMBER_OF_FEATURES];
    bool bugs[NUMBER_OF_BUGS];
    
} cpu_info_t PACKED;

/**
 * @brief               Different ways of halting.
 */
enum halt_t 
{
    /**
     * @brief           Reboot the machine. 
     */
    HALT_REBOOT,

    /**
     * @brief           Shut it down (with possible power-down as well). 
     */
    HALT_SHUTDOWN
};

#endif /* !__COMMON_CPU_H__ */
