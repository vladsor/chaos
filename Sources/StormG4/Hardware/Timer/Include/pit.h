/* $chaos: timer.h,v 1.3 2002/10/08 20:16:14 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file timer.h
 * @brief Timer support.
 */

#ifndef __STORM_TIMER_PIT_H__
#define __STORM_TIMER_PIT_H__

#define NUMBER_OF_PIT_CHANNELS (3)

#define PIT_0_DEFAULT_FREQUENCY  (100)
#define PIT_2_DEFAULT_FREQUENCY  (50)

#define PIT_BASE                (0x40)

#define PIT_COUNTER_REGISTER(channel) (PIT_BASE + (channel))

#define PIT_MODE_REGISTER    (PIT_BASE + 3)

#define COUNTER_LATCH_COMMAND   (0)

#define ACCESS_LOW_COUNTER_UINT8   (BIT_VALUE (4))

#define ACCESS_HIGH_COUNTER_UINT8  (BIT_VALUE (5))

enum pit_mode
{
    PIT_MODE_ZERO_DETECTION_INTERRUPT,
    PIT_MODE_PROGRAMMABLE_ONE_SHORT,
    PIT_MODE_RATE_GENERATOR,
    PIT_MODE_SQUARE_WAVE_GENERATOR,
    PIT_MODE_SOFTWARE_TRIGGERED_STROBE,
    PIT_MODE_HARDWARE_TRIGGERED_STROBE,
};

enum pit_channel
{
    PIT_CHANNEL_0,
    PIT_CHANNEL_1,
    PIT_CHANNEL_2,
    
    PIT_CHANNEL_MEMORY_REFRESH = PIT_CHANNEL_1,
};

/**
 * @brief              Zero detection interrupt. 
 */
#define PIT_MODE_0     (0)

/**
 * @brief              Programmable one shot. 
 */
#define PIT_MODE_1     (BIT_VALUE (1))

/**
 * @brief              Rate generator. 
 */
#define PIT_MODE_2     (BIT_VALUE (2))

/**
 * @brief              Square wave generator. 
 */
#define PIT_MODE_3     (BIT_VALUE (2) | BIT_VALUE (1))

/**
 * @brief              Software triggered strobe. 
 */
#define PIT_MODE_4     (BIT_VALUE (3))

/**
 * @brief              Hardware triggered strobe. 
 */
#define PIT_MODE_5     (BIT_VALUE (3) | BIT_VALUE (1))


/**
 * @brief       Binary counter mode. 
 */
#define PIT_COUNTER_MODE_BINARY \
            (0)

/**
 * @brief       BCD counter mode 
 */
#define PIT_COUNTER_MODE_BCD \
            (1)

/**
 * @brief       The clock speed of the timer chip. 
 */
#define PIT_BASE_FREQUENCY \
            (1193180UL)

/* Used for setting counter divisors. The 8254 chip has a fixed
   frequency of 1193180 Hz, one fourth of the original 8088 speed. So,
   when we want a given speed, we divide this frequency with the
   desired frequency. */
#define FREQUENCY_TO_COUNTER_DIVISOR(hz) \
               (PIT_BASE_FREQUENCY / (uint32_t)hz)

extern void pit_init (void);
extern void pit_mode_set (int channel, unsigned int digits, unsigned int mode);

extern void pit_counter_read (int channel, uint16_t *counter);
extern void pit_frequency_set (int channel, unsigned int frequency);
extern void pit_wait_for_count (int channel, uint16_t wait_count);

#endif /* !__STORM_TIMER_PIT_H__ */
