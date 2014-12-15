/* $Id: cpuid.c,v 1.1.1.1 2000/09/26 19:08:16 plundis Exp $ */
/* Abstract: CPU identification. Parts borrowed from the Linux
   kernel. */
/* Author: Per Lundberg <plundis@chaosdev.org>
           Parts borrowed from Linux kernel. */
/* Mostly rewriten by Vladimir Sorokin */

/* Copyright 1999-2000 chaos development. */

/* This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
   USA. */

#include <storm/ia32/types.h>
#include <storm/ia32/defines.h>
#include <storm/generic/debug.h>

#include <storm/ia32/cpuid.h>
#include <storm/ia32/cpuid-internal.h>

#include <storm/ia32/cpu.h>
#include <storm/ia32/flags.h>
#include <storm/ia32/memory.h>
#include <storm/ia32/port.h>
#include <storm/ia32/timer.h>
#include <storm/ia32/string.h>

#define DEBUG FALSE

/* CPUID functions. */

full_cpu_info CPU;

/* The number of CPUs in the system. When we write SMP support, this
   variable might be something else. */
unsigned int cpus = 1;

/* Initialise the CPU detection functionality. */

void cpuid_init (void)
{
  /* Make sure we clear this structure. */
  
  memory_set_u8 ((u8 *) &CPU, 0, sizeof (full_cpu_info));
  detect_cpu();
}

static bool INIT_CODE test_flag (u32 tested_flag)
{
  bool return_value;
  u32 eflags;
  u32 test_eflags;

  eflags = cpu_get_eflags ();
  
  debug_print ("Original EFLAGS: %X\n\n", eflags);
  
  cpu_set_eflags (eflags ^ tested_flag);
  
  test_eflags = cpu_get_eflags ();

  debug_print ("Test EFLAGS: %X\n\n", test_eflags);
  
  return_value = (test_eflags & ~tested_flag) != (eflags & ~tested_flag);
  
  cpu_set_eflags (eflags);
  
  return return_value;
}

void detect_cpu(void)
{ 
  debug_print("detecting cpu...\n");
  
  CPU.platform = PLATFORM_80x86;

  /* Intel386 processor check :
     The AC bit(FLAG_ALIGNMENT_CHECK), bit #18, is a new bit introduced in the 
     EFLAGS register on the Intel486 processor to generate alignment faults.
     This bit cannot be set on the Intel386 processor. */
  if (!test_flag (FLAG_ALIGNMENT_CHECK))
  {
    CPU.family = 3;
    debug_print("is 386.\n");
  }
  
  /* Check if the CPUID instruction is available on this system.  This is 
     distinguished by checking if FLAG_ID in eflags can be toggled. If that's 
     true, the CPU has the CPUID instruction. See Intel's documentation for more 
     information about how the CPUID instruction works. */
  else if (!test_flag (FLAG_ID))
  {
    CPU.family = 4;
    debug_print("is 486.\n");
  }
  else
  {
    feature_set(CPU_FEATURE_CPUID, TRUE);
    debug_print("has CPUID.\n");
    process_cpu_id();
  }

  bugs_search ();
  
  if(cpu_feature_get(CPU, CPU_FEATURE_FPU))
  {
    CPU.fpu_type_id = FPU_TYPE_BUILT_IN;
  }
  else
  {
    CPU.fpu_type_id = FPU_TYPE_NONE;
  }
  get_fpu_name ();

#ifdef CPU_BASE_FAMILY
  if(CPU.family < CPU_BASE_FAMILY)
  {
    DEBUG_HALT("This kernel request more advanced processor.");
  }    
#endif
#ifdef MMX_BASE 
  if(!get_cpu_feature(CPU,CPU_FEATURE_MMX))
  {
    DEBUG_HALT("This kernel request MMX support.");
  }
#endif
#ifdef _3DNOW_BASE 
  if(!get_cpu_feature(CPU,CPU_FEATURE_3DNOW))
  {
    DEBUG_HALT("This kernel request 3D-NOW support.");
  }
#endif
#ifdef FPU_BASE
  if(!get_cpu_feature(CPU,CPU_FEATURE_FPU))
  {
    DEBUG_HALT("This kernel request co-processor present.");
  }
#endif  
}

void process_cpu_id(void)
{
  u32 signature;
  u32 features_ebx = 0;
  u32 features_ecx = 0;
  u32 features_edx = 0;

  cpuid (GET_CPU_VENDOR, signature, *((u32 *)CPU.vendor_string),
         *((u32 *)(CPU.vendor_string + 8)), *((u32 *)(CPU.vendor_string + 4)));
  CPU.vendor_string[12] = 0;

  process_vendor (CPU.vendor_string);

  switch(signature) 
  { 
    case 2:
    case 1:
      cpuid (GET_CPU_INFO, signature, features_ebx, features_ecx,
             features_edx);
  }

  response_cpu (signature);

  response_cpu_sub_type ();
  
  process_features (features_edx);

  switch (CPU.vendor_id)
  {
    case VENDOR_AMD:
    {
      process_amd_features (features_edx);
      break;
    }
    case VENDOR_Intel:
    {
      break;
    }
    default:
  }

  if (cpu_feature_get(CPU, CPU_FEATURE_TSC))
  {
    CPU.frequency = (u64)cpuid_get_cpu_speed ();
    scaled_frequency ();
  }    

  if (!cpu_feature_get(CPU, CPU_FEATURE_HARD_NAME))
  {
    get_cpu_name();
  }

  if (CPU.cpu_sub_type_id != CPU_SUB_TYPE_Standart)
  {
    get_cpu_sub_name();
  }
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

static u32 INIT_CODE calibrate_tsc (void)
{
  u32 startlow, starthigh;
  u32 endlow, endhigh;
  u32 count;

  /* Set the gate high, disable speaker. */

  port_out_u8 (0x61, (port_in_u8 (0x61) & ~0x02) | 0x01);
  
  /* Now let's take care of CTC channel 2. */
  
  /* Set the gate high, program CTC channel 2 for mode 0, (interrupt
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

u32 INIT_CODE cpuid_get_cpu_speed (void)
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

void scaled_frequency(void)
{
  unsigned int i;
  char scale[] = {' ','K','M','T','G','P' };
  u64 temp = CPU.frequency;
  for( i = 0 ; i < sizeof(scale) ; i++ )
  {
    if(temp <= 1000)
    {
      CPU.frequency_scale = scale[i];
      CPU.scaled_frequency = temp;
      break;
    }
    temp /= 1000;
  }
  if(temp > 1000)
  {
    CPU.frequency_scale = scale[sizeof(scale) - 1];
    CPU.scaled_frequency = temp;
  }
}

static const char unknown[] = "Unknown";

int process_vendor (char* vendor)
{
  int num = sizeof (Vendor_records) / sizeof (vendor_record);
  int i;
  for ( i = 0 ; i < num ; i++ )
  {
    if (!string_compare_max (Vendor_records[i].vendor_string, vendor, 12))
    {
      CPU.vendor_id = Vendor_records[i].vendor_id;
      string_copy (CPU.vendor_name, Vendor_records[i].vendor_name);
      
      return TRUE;
    }
  }
  CPU.vendor_id = VENDOR_UNKNOWN;
  string_copy (CPU.vendor_name, unknown);
  
  return FALSE;
}

int response_cpu (u32 signature)
{
  int num_of_families = sizeof(CPU_families) / sizeof(families_type);
  int j = 0;

  u8 family   = (signature >> 8) & 0xF;
  u8 model    = (signature >> 4) & 0xF;
  u8 stepping = (signature     ) & 0xF;

  if( family > num_of_families )
  {
    CPU.cpu_type_id = CPU_TYPE_UNKNOWN_PROCESSOR;
    CPU.family = family;
    CPU.model = model;
    CPU.stepping = stepping;
    CPU.generation = model;

    return FALSE;
  }
  for(j = 0 ; j < CPU_families[family].size_of_family ; j++)
  { 
    if((CPU_families[family].family[j].from_model<= model ) &&
       (CPU_families[family].family[j].to_model  >= model ) &&
       (CPU_families[family].family[j].vendor_id == CPU.vendor_id))
    {
	 CPU.cpu_type_id = CPU_families[family].family[j].cpu_type_id;
	 CPU.family = family;
	 CPU.model  = model;
	 CPU.stepping = stepping;
	 return TRUE;
    }
  }

  CPU.cpu_type_id = CPU_TYPE_UNKNOWN_PROCESSOR;
  CPU.family = family;
  CPU.model = model;
  CPU.stepping = stepping;

  return FALSE;
}

int response_cpu_sub_type(void)
{
  int num = sizeof(CPU_sub_records)/sizeof(cpu_sub_record);
  int i = 0;

  for(i = 0 ; i < num ; i++)
  {
    if((CPU_sub_records[i].cpu_type_id	 == CPU.cpu_type_id ) &&
       (CPU_sub_records[i].model	 == CPU.model       ) &&
      ((CPU_sub_records[i].stepping	 == CPU.stepping    ) ||
       (CPU_sub_records[i].stepping	 == (u8)NONE        )))
    {
      CPU.cpu_sub_type_id = CPU_sub_records[i].cpu_sub_type_id;
      return TRUE;
    }
  }    

  CPU.cpu_sub_type_id = CPU_SUB_TYPE_Standart;

  return FALSE;
}

int get_cpu_name(void)
{
  int num = sizeof(CPU_type_records)/sizeof(cpu_type_record);
  int i;

  for(i = 0 ; i < num ; i++)
  {
    if(CPU.cpu_type_id == CPU_type_records[i].type_id)
    {
      string_copy(CPU.cpu_name,CPU_type_records[i].name);
      return TRUE;
    }
  }

  string_copy(CPU.cpu_name,"UNKNOWN PROCESSOR");

  return FALSE;
}

int get_cpu_sub_name(void)
{
  int num = sizeof(CPU_sub_type_records)/sizeof(cpu_sub_type_record);
  int k;

  for(k = 0 ; k < num ; k++)
  {
    if(CPU.cpu_sub_type_id == CPU_sub_type_records[k].sub_type_id)
    {
      string_append(CPU.cpu_name," ");
      string_append(CPU.cpu_name,CPU_sub_type_records[k].name);
      return TRUE;
    }
  }

  return FALSE;
}

int get_fpu_name(void)
{
  int num = sizeof(FPU_type_records)/sizeof(fpu_type_record);
  int i;
  for(i = 0 ; i < num ; i++)
  {
    if(CPU.fpu_type_id == FPU_type_records[i].type_id)
    {
      string_copy(CPU.fpu_name,FPU_type_records[i].name);
      return TRUE;
    }
  }
  return FALSE;
}

/* Feature Bit Test Capabilities */

void process_features(u32 features)
{
  /* bit  0 = FPU */
  feature_set (CPU_FEATURE_FPU, (features >>  0) & 1);
    
  /* bit  1 = Virtual Mode Extensions */    
  feature_set (CPU_FEATURE_VME, (features >>  1) & 1);
    
  /* bit  2 = Debug extensions */
  feature_set (CPU_FEATURE_DEBUG, (features >>  2) & 1);
    
  /* bit  3 = Page Size Extensions */
  feature_set (CPU_FEATURE_PSE, (features >>  3) & 1);

  /* bit  4 = Time Stamp Counter */
  feature_set (CPU_FEATURE_TSC, (features >>  4) & 1);

  /* bit  5 = Model Specific Registers */
  feature_set (CPU_FEATURE_MSR, (features >>  5) & 1);
    
  /* bit  6 = Page Size Extensions */
  feature_set (CPU_FEATURE_PAE, (features >>  6) & 1);

  /* bit  7 = Machine Check Extensions */
  feature_set (CPU_FEATURE_MCE, (features >>  7) & 1);

  /* bit  8 = CMPXCHG8 instruction */
  feature_set (CPU_FEATURE_CMPXCHG8, (features >>  8) & 1);

  /* bit  9 = APIC (Advanced Programmable Intrrupt Controller) */
  feature_set (CPU_FEATURE_APIC, (features >>  9) & 1);

  /* bit 10 = Reserved */

  /* bit 11 = SYSENTER instruction */
  feature_set (CPU_FEATURE_SYSENTER, (features >> 11) & 1);

  /* bit 12 = Memory Type Range Registers */
  feature_set (CPU_FEATURE_MTRR, (features >> 12) & 1);

  /* bit 13 = Global Paging Extensions */
  feature_set (CPU_FEATURE_GPE, (features >> 13) & 1);
    
  /* bit 14 = Machine Check Architecture */
  feature_set (CPU_FEATURE_MCA, (features >> 14) & 1);

  /* bit 15 = CMOV instruction */
  feature_set (CPU_FEATURE_CMOV, (features >> 15) & 1);
    
  /* bit 16 = Page Attribue Table */
  feature_set (CPU_FEATURE_PAT, (features >> 16) & 1);

  /* bit 17 = PSE36 (Page Size Extensions) */
  feature_set (CPU_FEATURE_PSE36, (features >> 17) & 1);

  /* bit 18 = Product Serial Number */
  feature_set (CPU_FEATURE_PSN, (features >> 18) & 1);
    
  /* bit 19 = cache line flush instruction */
  feature_set (CPU_FEATURE_CLFLSH, (features >> 19) & 1);

  /* bit 20 = Reserved */

  /* bit 21 = Debug Trace and EMON Store */
  feature_set (CPU_FEATURE_DTES, (features >> 21) & 1);
    
  /* bit 22 = processor duty cycle control */
  feature_set (CPU_FEATURE_ACPI, (features >> 22) & 1);

  /* bit 23 = MMX	*/
  feature_set (CPU_FEATURE_MMX, (features >> 23) & 1);

  /* bit 24 = FXSAVE/FXRSTOR instruction */
  feature_set (CPU_FEATURE_FXSAVE, (features >> 24) & 1);

  /* bit 25 = SSE	*/
  feature_set (CPU_FEATURE_SSE, (features >> 25) & 1);

  /* bit 26 = SSE 2 */
  feature_set (CPU_FEATURE_SSE_2, (features >> 26) & 1);

  /* bit 27 = Self Snoop */
  feature_set (CPU_FEATURE_SELF_SNOOP, (features >> 27) & 1);

  /* bit 28 = Reserved	*/

  /* bit 29 = Automatic Clock Control */
  feature_set (CPU_FEATURE_ACC, (features >> 29) & 1);

  /* bit 30 = IA-64 */
  feature_set (CPU_FEATURE_IA_64, (features >> 30) & 1);

  /* bit 31 = Reserved */

}

void process_amd_features (u32 features)
{
  u32 functions;
  u32 dummy;
  u32 ext_features = 0;
  u32 temp1, temp2, temp3, temp4;

  cpuid (CHECK_AMD_FEATURES, functions, dummy, dummy, dummy);

  if (functions > GET_AMD_CACHE_L2_INFO)
  {
    functions = GET_AMD_CACHE_L2_INFO;
  }
  
  switch (functions)
  {
    case GET_AMD_CACHE_L2_INFO:
    {
      cpuid (GET_AMD_CACHE_L2_INFO, temp1, temp2, temp3, temp4);        

      CPU.cache_l2_size = (temp3 >> 16) & 0xFFFF;
      feature_set (CPU_FEATURE_CACHE_L2_INFO, TRUE);
    }
    case GET_AMD_CACHE_L1_INFO:
    {
      cpuid (GET_AMD_CACHE_L1_INFO, temp1, temp2, temp3, temp4);        

      CPU.data_cache_l1_size = (temp3 >> 24) & 0xFF;
      CPU.instructions_cache_l1_size = (temp4 >> 24) & 0xFF;
      feature_set (CPU_FEATURE_CACHE_L1_INFO, TRUE);
    }	
    case GET_AMD_CPU_STRING_3:
    {
      feature_set(CPU_FEATURE_HARD_NAME, TRUE);

      cpuid ( GET_AMD_CPU_STRING_3, *((u32 *)(CPU.cpu_name + 32)),
             *((u32 *)(CPU.cpu_name + 36)), *((u32 *)(CPU.cpu_name + 40)),
             *((u32 *)(CPU.cpu_name + 44)) );        
    }
    case GET_AMD_CPU_STRING_2:
    {
      cpuid ( GET_AMD_CPU_STRING_2, *((u32 *)(CPU.cpu_name + 16)),
             *((u32 *)(CPU.cpu_name + 20)), *((u32 *)(CPU.cpu_name + 24)),
             *((u32 *)(CPU.cpu_name + 28)) );        
    }	
    case GET_AMD_CPU_STRING_1:
    {
      cpuid ( GET_AMD_CPU_STRING_1, *((u32 *)(CPU.cpu_name + 0)), 
             *((u32 *)(CPU.cpu_name + 4)), *((u32 *)(CPU.cpu_name + 8)),
             *((u32 *)(CPU.cpu_name + 12)) );        
    }
    case GET_AMD_FEATURES:
    {
      cpuid (GET_AMD_FEATURES, dummy, dummy, dummy, ext_features);        

      /* bit 22 (ext) = SSE MMX Extensions */
      feature_set (CPU_FEATURE_SSE_MMX,(ext_features >> 22) & 1 );	

      /* bits 25|22(ext) = MMX Extensions */
      feature_set (CPU_FEATURE_MMX_EXT,((features >> 25) & 1) | 
                   ((ext_features >> 22) &1 ));

      /* AMD extended information */
    
      /* bit 29 (ext) = AA-64 */
      feature_set (CPU_FEATURE_AA_64, (ext_features >> 29) & 1 );
    
      /* bit 30 (ext) = Extended 3DNow! */
      feature_set (CPU_FEATURE_3DNOW_EXT, (ext_features >> 30) & 1 );
    
      /* bit 31 (ext) = 3DNow! */
      feature_set (CPU_FEATURE_3DNOW, (ext_features >> 31) & 1 );
    }
  }
}
void bugs_search (void)
{
}