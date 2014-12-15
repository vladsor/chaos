#include <enviroment.h>

#define DEBUG_MODULE_NAME "Cpu"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#include <debug/macros.h>

#include "Include/cpu_speed.h"

/* FIXME: This code should be much cleaner... */

/* The timer frequency. */
static unsigned int hz = 100;

/* Calibrate the TSC. */

#define PIT_BASE_FREQUENCY \
            (1193180UL)
            
/* Return 2^32 * (1 / (TSC clocks per usec)) for cpu_info HZ detection.
   Too much 64-bit arithmetic here to do this cleanly in C, and for
   accuracy's sake we want to keep the overhead on the CTC speaker
   (channel 2) output busy loop as low as possible. We avoid reading
   the CTC registers directly because of the awkward 8-bit access
   mechanism of the 82C54 device. */

/* For divider */

#define LATCH           ((PIT_BASE_FREQUENCY + hz / 2) / hz)
#define CALIBRATE_LATCH	(5 * LATCH)
#define CALIBRATE_TIME	(5 * 1000020 / hz)

static uint32_t calibrate_tsc (void)
{
  uint32_t startlow, starthigh;
  uint32_t endlow, endhigh;
  uint32_t count;

  /* Set the gate high, disable speaker. */

  port_uint8_out (0x61, (port_uint8_in (0x61) & ~0x02) | 0x01);
  
  /* Now let's take care of CTC channel 2. */
  
  /* Set the gate high, program CTC channel 2 for mode 0, (interrupt
     on terminal count mode), binary count, load 5 * LATCH count, (LSB
     and MSB) to begin countdown. */

  /* Binary, mode 0, LSB/MSB, Ch 2 */

  port_uint8_out (0x43, 0xB0);

  /* LSB of count */

  port_uint8_out (0x42, CALIBRATE_LATCH & 0xFF);

  /* MSB of count */

  port_uint8_out (0x42, CALIBRATE_LATCH >> 8);
  
  rdtsc (startlow, starthigh);
  count = 0;
  
  do
  {
    count++;
  } while ((port_uint8_in (0x61) & 0x20) == 0);

  rdtsc (endlow, endhigh);
  
  /* Error */
  
  if (count <= 1)
  {
    return 0;
  }
  
  /* 64-bit subtract - gcc just messes up with long longs. FIXME: test
     if this is really so. The code was borrowed from Linux which was
     designed for gcc 2.7, and we're targeting gcc 2.95... */
  
  asm ("subl %2, %0\n"
       "sbbl %3, %1"
       : "=a" (endlow), "=d" (endhigh)
       : "g" (startlow), "g" (starthigh), "0" (endlow), "1" (endhigh));
  
  /* cpu_info is too fast. */
  
    if (endhigh != 0)
    {
      return 0;
    }
  
  /* cpu_info is too slow. */
  
  if (endlow <= CALIBRATE_TIME)
  {
    return 0;
  }
  
  asm ("divl %2"
       : "=a" (endlow), "=d" (endhigh)
       : "r" (endlow), "0" (0), "1" (CALIBRATE_TIME));
  
  return endlow;
}

/* Get the cpu_info speed in MHz. This requires TSC support. */

uint64_t cpu_speed_get (void)
{
  uint32_t tsc_quotient = calibrate_tsc ();
  uint32_t cpu_hz;
  
  if (tsc_quotient != 0)
  {
    /* Report cpu_info clock rate in Hz. The formula is (10^6 * 2^32) /
       (2^32 * 1 / (clocks/us)) = clock/second. Our precision is about
       100 ppm. */

    {	
      uint32_t eax = 0, edx = 1000000;
      asm ("divl %2"
	   : "=a" (cpu_hz), "=d" (edx)
	   : "r" (tsc_quotient), "0" (eax), "1" (edx));
    }
  }
  else
  {
    return 0;
  }
    return cpu_hz;
}


