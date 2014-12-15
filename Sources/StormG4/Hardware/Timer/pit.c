/* $chaos: timer.c,v 1.3 2002/10/04 19:01:21 per Exp $ */
/* Abstract: Timer support. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <enviroment.h>

#include "Include/pit.h"
#include "Include/timer.h"

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

uint8_t pit_mode[NUMBER_OF_PIT_CHANNELS];
uint16_t pit_divisor[NUMBER_OF_PIT_CHANNELS];

/* Initialise PIT channels 0 and 2. */
void pit_init (void)
{
//    pit_mode_set (0, 16, 0);
//    pit_frequency_set (0, /*PIT_0_DEFAULT_FREQUENCY*/hz);

//    pit_mode_set (2, 16, 0);
//    pit_frequency_set (2, PIT_2_DEFAULT_FREQUENCY);
} 

void pit_mode_set (int channel, unsigned int digits UNUSED, unsigned int mode)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Channel=%u, Digits=%u, Mode=%u\n", 
        channel, digits, mode);

    DEBUG_ASSERT ((channel < NUMBER_OF_PIT_CHANNELS), "Invalid channel.");

    DEBUG_ASSERT ((digits == 8 || digits == 16), "");

    pit_mode[channel] = mode;
 
    port_uint8_out (PIT_MODE_REGISTER, (channel | ACCESS_LOW_COUNTER_UINT8 |
        ACCESS_HIGH_COUNTER_UINT8 | PIT_MODE_3 | PIT_COUNTER_MODE_BINARY));
}

void pit_frequency_set (int channel, unsigned int frequency)
{
    uint32_t divisor;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Channel=%u, Frequency=%u\n", 
        channel, frequency);

    DEBUG_ASSERT ((channel < NUMBER_OF_PIT_CHANNELS), "Invalid channel.");

    DEBUG_ASSERT ((channel != PIT_CHANNEL_MEMORY_REFRESH), 
        "This channel is reserved.");
    
    DEBUG_ASSERT ((frequency != 0), 
        "This channel is reserved.");

    DEBUG_ASSERT (((uint32_t) frequency <= (uint32_t) PIT_BASE_FREQUENCY), 
        "Too high frequency.");

    divisor = FREQUENCY_TO_COUNTER_DIVISOR (frequency);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Divisor=%u\n", divisor);

//    DEBUG_ASSERT (DEBUG_LEVEL_ERROR, (divisor < 4), "");
    DEBUG_ASSERT ((divisor <= UINT16_MAX), "Too low frequency");

    if (divisor > UINT16_MAX)
    {
        divisor = UINT16_MAX;
    }

    pit_divisor[channel] = (uint16_t) divisor;

    port_uint8_out (PIT_COUNTER_REGISTER (channel), 
        UINT16_LOW_UINT8 ((uint16_t) divisor));

    port_uint8_out (PIT_COUNTER_REGISTER (channel), 
        UINT16_HIGH_UINT8 ((uint16_t) divisor));   
}

void pit_counter_read (int channel, uint16_t *counter)
{
    uint16_t temp_counter = 0;

    DEBUG_ASSERT ((channel < NUMBER_OF_PIT_CHANNELS), "Invalid channel.");

    port_uint8_out (PIT_MODE_REGISTER, 0);

    temp_counter = port_uint8_in (PIT_COUNTER_REGISTER (channel));
    temp_counter |= port_uint8_in (PIT_COUNTER_REGISTER (channel)) << 8;

    (*counter) = temp_counter;
}


