
#include <storm/ia32/types.h>
#include <storm/ia32/defines.h>
#include <storm/ia32/cpuid.h>
#include <storm/ia32/cpu.h>
#include <storm/ia32/flags.h>
#include <storm/ia32/memory.h>
#include <storm/ia32/port.h>
#include <storm/ia32/timer.h>
#include <storm/ia32/string.h>

#define FLAG_AC 0x40000
#define FLAG_ID 0x200000

/* Generic CPUID function */
/*
static inline void cpuid (u32 command, u32 *eax, u32 *ebx, u32 *ecx, u32 *edx)
{
  asm volatile ("cpuid"
       : "=a" (*eax), "=b" (*ebx), "=c" (*ecx), "=d" (*edx)
       : "a" (command)
       : "cc");
}
*/

static u16 INIT_CODE is_8086 (void) 
{
  int return_value;

  debug_print("8086 Testing...\n");

  asm volatile ("\
	push %%cx
	push %%dx

        pushf			/* push original FLAGS			*/
        pop %%ax		/* get original FLAGS 			*/
        mov %%ax, %%cx		/* save original FLAGS			*/
        and $0x0FFF, %%ax	/* clear bits 12-15 in FLAGS		*/
        push %%ax		/* save new FLAGS value on stack	*/
        popf			/* replace current FLAGS value		*/
        pushf			/* get new FLAGS			*/
        pop %%ax		/* store new FLAGS in AX		*/
        and $0x0F000, %%ax	/* if bits 12-15 are set, then		*/
        cmp $0x0F000, %%ax	/* processor is an 8086/8088		*/

        jne 3f			/* go check for 80286			*/
        push %%sp		/* double check with push sp		*/
        pop %%dx		/* if value pushed was different	*/
        cmp %%sp, %%dx		/* means it's really not an 8086	*/
        jne 2f			/* jump if processor is 8086/8088	*/
1:
        mov $-1, %%ax
	jmp 4f
2:
        mov $1, %%ax
	jmp 4f
3:
        xor %%ax,%%ax
4:
	push %%cx
	popf
	
	pop %%dx
	pop %%cx
  "
   : "=&a" (return_value));

  debug_print("end 8086 testing.\n");
  
  return return_value;
}

//--------------------------------------------------------------------
// Intel 286 processor check
// Bits 12-15 of the FLAGS register are always clear on the
// Intel 286 processor in real-address mode.
static u16 INIT_CODE is_80286 (void)
{
  int return_value;

  debug_print("80286 Testing\n");

  asm volatile ("\
	push %%cx
  
	pushf			/* push original FLAGS			*/
        pop %%ax		/* get original FLAGS			*/
        mov %%ax, %%cx		/* save original FLAGS			*/

        or $0x0F000, %%cx	/* try to set bits 12-15		*/
        push %%cx		/* save new FLAGS value on stack	*/
        popf			/* replace current FLAGS value		*/
        pushf			/* get new FLAGS			*/
        pop %%ax		/* store new FLAGS in AX		*/
        and $0x0F000, %%ax	/* if bits 12-15 are clear		*/
        jnz 2f			/* jump if processor is 80286		*/
1:
        mov $1,%%ax
        jmp 3f
2:
        xor %%ax,%%ax
3:
	push %%cx
	popf

	pop %%cx
  "
   : "=&a" (return_value));

  debug_print("end 80286 testing.\n");

  return return_value;
}

//--------------------------------------------------------------------
// Intel386 processor check
// The AC bit, bit #18, is a new bit introduced in the EFLAGS
// register on the Intel486 processor to generate alignment
// faults.
// This bit cannot be set on the Intel386 processor.
static int INIT_CODE is_80386 (void)
{
  int return_value;

  debug_print("80386 Testing...\n");

  asm volatile ("\
	pushl %%ecx

	pushfl			/* push original EFLAGS			*/
        popl %%eax		/* get original EFLAGS			*/

        movl %%eax, %%ecx	/* save original EFLAGS			*/
        xorl $0x40000, %%eax	/* flip AC bit in EFLAGS		*/
        pushl %%eax		/* save new EFLAGS value on stack	*/
        popfl			/* replace current EFLAGS value		*/

        pushfl			/* get new EFLAGS			*/
        popl %%eax		/* store new EFLAGS in EAX		*/

        xorl %%ecx, %%eax 	/* can't toggle AC bit, processor=80386	*/

        jnz is386		/* jump if 80386 processor		*/

not386:
        xor %%eax,%%eax
        jmp end386
is386:
        mov $1,%%eax
end386:
        pushl %%ecx	
        popfl			/* restore AC bit in EFLAGS first	*/

	popl %%ecx
  "
   : "=&a" (return_value));

  debug_print("end 80386 testing.\n");
  
  return return_value;
}

//--------------------------------------------------------------------
// Intel486 processor check
// Checking for ability to set/clear ID flag (Bit 21) in EFLAGS
// which indicates the presence of a processor with the CPUID
// instruction.

static int INIT_CODE is_80486 (void)
{
  int return_value;

  debug_print("80486 Testing...\n");

  asm volatile ("\
	pushl %%ecx

	pushfl			/* push original EFLAGS			*/
        popl %%eax		/* get original EFLAGS			*/
        movl %%eax, %%ecx	/* save original EFLAGS			*/
        xorl $0x200000, %%eax	/* flip ID bit in EFLAGS		*/
        push %%eax		/* save new EFLAGS value on stack	*/
        popfl			/* replace current EFLAGS value		*/
        pushfl			/* get new EFLAGS			*/
        popl %%eax		/* store new EFLAGS in EAX		*/
        xorl %%ecx, %%eax	/* can't toggle ID bit,			*/
        jne 2f		        /* processor=80486			*/
1:
        mov $1,%%eax
        jmp end486
2:
        xor %%eax,%%eax
end486:
	pushl %%ecx
	popfl
	
	popl %%ecx
  "
   : "=&a" (return_value));

  debug_print("end 80486 testing.\n");
  
  return return_value;
}

static int INIT_CODE is_386 (void)
{
  int return_value;

  asm
  ("\
    pushl   %%ecx
    
    pushfl
    popl    %%eax
    movl    %%eax, %%ecx
    xorl    $0x40000, %%eax
    pushl   %%eax
    popf
                  
    pushf
    popl    %%eax
    xorl    %%ecx, %%eax
    and     $0x40000, %%eax
    je      1f
  

    movl   $0, %%eax
    jmp    2f
                
1:  
    movl   $1, %%eax     
2:  
    popl   %%ecx
   "
   : "=&a" (return_value));
  
  return return_value;
}


/* Check if the CPUID instruction is available on this system.  This
   is distinguished by checking if FLAG_ID in eflags can be toggled. If
   that's true, the CPU has the CPUID instruction. See Intel's
   documentation for more information about how the CPUID instruction
   works. */

static u32 INIT_CODE has_CPUID (void)
{
  u32 return_value;

  debug_print("CPUID Testing...\n");

  asm volatile ("\
    pushl       %%ebx

    /* Invert id bit. */

    pushfl
    xorl        %1, (%%esp)
    popfl

    /* Read eflags register and mask all bits but id bit. */

    pushfl
    movl        (%%esp), %%eax
    andl        %1, %%eax
    popfl

    /* Invert id bit. */

    pushfl
    xorl        %1, (%%esp)
    popfl

    /* Mask. */

    pushfl
    movl        (%%esp), %%ebx
    andl        %1, %%ebx
    popfl

    /* Is id bit the same? */
          
    cmpl        %%ebx, %%eax
    jne         sup
  
    /* CPUID not supported. */

    xorl        %%eax, %%eax
    jmp         endid
sup: 
    movl        $1, %%eax
endid: 
    popl        %%ebx
  "
       : "=&a" (return_value)
       : "g" (FLAG_ID));

  debug_print("end CPUID testing.\n");

  return return_value;
}

/* FIXME: This code should be much cleaner... */

/* Calibrate the TSC. */
/* Return 2^32 * (1 / (TSC clocks per usec)) for CPU HZ detection.
   Too much 64-bit arithmetic here to do this cleanly in C, and for
   accuracy's sake we want to keep the overhead on the CTC speaker
   (channel 2) output busy loop as low as possible. We avoid reading
   the CTC registers directly because of the awkward 8-bit access
   mechanism of the 82C54 device. */

/* For divider */

#define LATCH           ((CLOCK_TICK_RATE + hz / 2) / hz)
#define CALIBRATE_LATCH	(5 * LATCH)
#define CALIBRATE_TIME	(5 * 1000020 / hz)

//#define CALIBRATE_LATCH COUNTER_DIVISOR(hz)

static u32 INIT_CODE calibrate_tsc (void)
{
  u32 startlow, starthigh;
  u32 endlow, endhigh;
  u32 count;

  /* Set the gate high, disable speaker. */

  port_out_u8 (0x61, (port_in_u8 (0x61) & ~0x02) | 0x01);
  
  /* Now let's take care of CTC channel 2. */
  
  /* Set the gate high, program CTC channel 2 for mode 0, (interrupt
     on terminal count mode), binary count, load 5 * LATCH count, (LSB
     and MSB) to begin countdown. */

  /* Binary, mode 0, LSB/MSB, Ch 2 */

  port_out_u8 (0x43, 0xB0);

  /* LSB of count */

  port_out_u8 (0x42, CALIBRATE_LATCH & 0xFF);

  /* MSB of count */

  port_out_u8 (0x42, CALIBRATE_LATCH >> 8);
  
  rdtsc (startlow, starthigh);
  count = 0;
  
  do
  {
    count++;
  } while ((port_in_u8 (0x61) & 0x20) == 0);

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
  
  /* CPU is too fast. */
  
  if (endhigh != 0)
  {
    return 0;
  }
  
  /* CPU is too slow. */
  
  if (endlow <= CALIBRATE_TIME)
  {
    return 0;
  }
  
  asm ("divl %2"
       : "=a" (endlow), "=d" (endhigh)
       : "r" (endlow), "0" (0), "1" (CALIBRATE_TIME));
  
  return endlow;
}

/* Get the CPU speed in MHz. This requires TSC support. */

static u32 INIT_CODE cpuid_get_cpu_speed (void)
{
  u32 tsc_quotient = calibrate_tsc ();
  u32 cpu_hz;
  
  if (tsc_quotient != 0)
  {
    /* Report CPU clock rate in Hz. The formula is (10^6 * 2^32) /
       (2^32 * 1 / (clocks/us)) = clock/second. Our precision is about
       100 ppm. */

    {	
      u32 eax = 0, edx = 1000000;
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
