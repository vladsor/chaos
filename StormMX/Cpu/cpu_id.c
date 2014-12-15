#include <enviroment.h>

#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#include <debug/macros.h>

#include "Include/cpu_id.h"
#include "Include/cpuid-internal.h"

void cpu_id_detect (cpu_info_t *cpu_info)
{ 
  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Detecting cpu...");
  
  cpu_info->platform = PLATFORM_80x86;

  /* Intel386 processor check:
     The AC bit(FLAG_ALIGNMENT_CHECK), bit #18, is a new bit introduced in the 
     EFLAGS register on the Intel486 processor to generate alignment faults.
     This bit cannot be set on the Intel386 processor. */
  
  if (!cpu_flags_test (CPU_FLAG_ALIGNMENT_CHECK))
  {
    cpu_info->family = 3;
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "is 386.\n");
  }
  
  /* Check if the CPUID instruction is available on this system.  This is 
     distinguished by checking if FLAG_ID in eflags can be toggled. If that's 
     true, the cpu_info has the CPUID instruction. See Intel's documentation 
     for more information about how the CPUID instruction works. */
  else if (!cpu_flags_test (CPU_FLAG_ID))
  {
    cpu_info->family = 4;
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "is 486.\n");
  }
  else
  {
    feature_set (cpu_info, CPU_FEATURE_CPUID, TRUE);
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "has CPUID.\n");
    process_cpu_id (cpu_info);
  }

  if (feature_get (cpu_info, CPU_FEATURE_FPU))
  {
    cpu_info->fpu_type_id = FPU_TYPE_BUILT_IN;
  }
  else
  {
    cpu_info->fpu_type_id = FPU_TYPE_NONE;
  }

#ifdef CPU_BASE_FAMILY
  if (cpu_info->family < CPU_BASE_FAMILY)
  {
    DEBUG_HALT ("This kernel request more advanced processor.");
  }    
#endif
#ifdef MMX_BASE 
  if (!get_cpu_feature (cpu_info, CPU_FEATURE_MMX))
  {
    DEBUG_HALT ("This kernel request MMX support.");
  }
#endif
#ifdef _3DNOW_BASE 
  if (!get_cpu_feature (cpu_info, CPU_FEATURE_3DNOW))
  {
    DEBUG_HALT ("This kernel request 3D-NOW support.");
  }
#endif
#ifdef FPU_BASE
  if (!get_cpu_feature (cpu_info, CPU_FEATURE_FPU))
  {
    DEBUG_HALT ("This kernel request co-processor present.");
  }
#endif  

}


void process_cpu_id (cpu_info_t *cpu_info)
{
  uint32_t signature;
  uint32_t features_ebx = 0;
  uint32_t features_ecx = 0;
  uint32_t features_edx = 0;

  cpuid (GET_CPU_VENDOR, signature, 
         *((uint32_t *)cpu_info->vendor_string),
         *((uint32_t *)(cpu_info->vendor_string + 8)), 
	 *((uint32_t *)(cpu_info->vendor_string + 4)));
  cpu_info->vendor_string[12] = 0;

  process_vendor (cpu_info, cpu_info->vendor_string);

  switch(signature) 
  { 
    case 2:
    case 1:
      cpuid (GET_CPU_INFO, signature, features_ebx, features_ecx,
             features_edx);
  }

  response_cpu (cpu_info, signature);
  cpu_info->generation = cpu_info->family;

  response_cpu_sub_type (cpu_info);
  
  process_features (cpu_info, features_edx);

  switch (cpu_info->vendor_id)
  {
    case VENDOR_AMD:
    {
      process_amd_features (cpu_info, features_edx);
      break;
    }
    case VENDOR_Intel:
    {
      break;
    }
//    default:
  }

  if (feature_get (cpu_info, CPU_FEATURE_TSC))
  {
    cpu_info->frequency = (uint64_t) cpuid_get_cpu_speed ();
  }
  
  return;
}

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

uint32_t cpuid_get_cpu_speed (void)
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

bool process_vendor (cpu_info_t *cpu_info, char* vendor)
{
  int num = sizeof (Vendor_records) / sizeof (vendor_record);
  int i;
  
  for (i = 0 ; i < num ; i++)
  {
    if (!string_compare_max (Vendor_records[i].vendor_string, vendor, 12))
    {
      cpu_info->vendor_id = Vendor_records[i].vendor_id;
      
      return TRUE;
    }
  }
  
  cpu_info->vendor_id = VENDOR_UNKNOWN;
  
  return FALSE;
}

bool response_cpu (cpu_info_t *cpu_info, uint32_t signature)
{
  int num_of_families = sizeof(CPU_families) / sizeof(families_type);
  int j = 0;

  uint8_t family   = (signature >> 8) & 0xF;
  uint8_t model    = (signature >> 4) & 0xF;
  uint8_t stepping = (signature     ) & 0xF;

  if (family == 0xF)
  {
    family += (signature >> 20) & 0xFF;
  }

  if (model == 0xF)
  {
    model |= ((signature >> 16) & 0xF) << 4;
  }
  

  if (family > num_of_families)
  {
    cpu_info->cpu_type_id = CPU_TYPE_UNKNOWN_PROCESSOR;
    cpu_info->family = family;
    cpu_info->model = model;
    cpu_info->stepping = stepping;

    return FALSE;
  }

  for(j = 0 ; j < CPU_families[family].size_of_family ; j++)
  { 
    if((CPU_families[family].family[j].from_model<= model ) &&
       (CPU_families[family].family[j].to_model  >= model ) &&
       (CPU_families[family].family[j].vendor_id == cpu_info->vendor_id))
    {
	 cpu_info->cpu_type_id = CPU_families[family].family[j].cpu_type_id;
	 cpu_info->family = family;
	 cpu_info->model  = model;
	 cpu_info->stepping = stepping;
	 return TRUE;
    }
  }

  cpu_info->cpu_type_id = CPU_TYPE_UNKNOWN_PROCESSOR;
  cpu_info->family = family;
  cpu_info->model = model;
  cpu_info->stepping = stepping;

  return FALSE;
}

bool response_cpu_sub_type (cpu_info_t *cpu_info)
{
  int num = sizeof (CPU_sub_records) / sizeof (cpu_sub_record);
  int i = 0;

  for (i = 0 ; i < num ; i++)
  {
    if((CPU_sub_records[i].cpu_type_id	 == cpu_info->cpu_type_id ) &&
       (CPU_sub_records[i].model	 == cpu_info->model       ) &&
      ((CPU_sub_records[i].stepping	 == cpu_info->stepping    ) ||
       (CPU_sub_records[i].stepping	 == (uint8_t) NONE        )))
    {
      cpu_info->cpu_sub_type_id = CPU_sub_records[i].cpu_sub_type_id;
      return TRUE;
    }
  }    

  cpu_info->cpu_sub_type_id = CPU_SUB_TYPE_Standart;

  return FALSE;
}

/* Feature Bit Test Capabilities */

void process_features (cpu_info_t *cpu_info, uint32_t features)
{

  /* bit  0 = FPU */
  feature_set (cpu_info, CPU_FEATURE_FPU, (features >>  0) & 1);
    
  /* bit  1 = Virtual Mode Extensions */    
  feature_set (cpu_info, CPU_FEATURE_VME, (features >>  1) & 1);
    
  /* bit  2 = Debug extensions */
  feature_set (cpu_info, CPU_FEATURE_DEBUG, (features >>  2) & 1);
    
  /* bit  3 = Page Size Extensions */
  feature_set (cpu_info, CPU_FEATURE_PSE, (features >>  3) & 1);

  /* bit  4 = Time Stamp Counter */
  feature_set (cpu_info, CPU_FEATURE_TSC, (features >>  4) & 1);

  /* bit  5 = Model Specific Registers */
  feature_set (cpu_info, CPU_FEATURE_MSR, (features >>  5) & 1);
    
  /* bit  6 = Page Size Extensions */
  feature_set (cpu_info, CPU_FEATURE_PAE, (features >>  6) & 1);

  /* bit  7 = Machine Check Extensions */
  feature_set (cpu_info, CPU_FEATURE_MCE, (features >>  7) & 1);

  /* bit  8 = CMPXCHG8 instruction */
  feature_set (cpu_info, CPU_FEATURE_CMPXCHG8, (features >>  8) & 1);

  /* bit  9 = APIC (Advanced Programmable Intrrupt Controller) */
  feature_set (cpu_info, CPU_FEATURE_APIC, (features >>  9) & 1);

  /* bit 10 = Reserved */

  /* bit 11 = Fast System Call */
  feature_set (cpu_info, CPU_FEATURE_SEP, (features >> 11) & 1);

  /* bit 12 = Memory Type Range Registers */
  feature_set (cpu_info, CPU_FEATURE_MTRR, (features >> 12) & 1);

  /* bit 13 = Page Global Enable */
  feature_set (cpu_info, CPU_FEATURE_PGE, (features >> 13) & 1);
    
  /* bit 14 = Machine Check Architecture */
  feature_set (cpu_info, CPU_FEATURE_MCA, (features >> 14) & 1);

  /* bit 15 = CMOV instruction */
  feature_set (cpu_info, CPU_FEATURE_CMOV, (features >> 15) & 1);
    
  /* bit 16 = Page Attribue Table */
  feature_set (cpu_info, CPU_FEATURE_PAT, (features >> 16) & 1);

  /* bit 17 = PSE36 (Page Size Extensions) */
  feature_set (cpu_info, CPU_FEATURE_PSE36, (features >> 17) & 1);

  /* bit 18 = Product Serial Number */
  feature_set (cpu_info, CPU_FEATURE_PSN, (features >> 18) & 1);
    
  /* bit 19 = cache line flush instruction */
  feature_set (cpu_info, CPU_FEATURE_CLFLSH, (features >> 19) & 1);

  /* bit 20 = Reserved */

  /* bit 21 = Debug Store */
  feature_set (cpu_info, CPU_FEATURE_DS, (features >> 21) & 1);
    
  /* bit 22 = processor duty cycle control */
  feature_set (cpu_info, CPU_FEATURE_ACPI, (features >> 22) & 1);

  /* bit 23 = MMX	*/
  feature_set (cpu_info, CPU_FEATURE_MMX, (features >> 23) & 1);

  /* bit 24 = FXSAVE/FXRSTOR instruction */
  feature_set (cpu_info, CPU_FEATURE_FXSR, (features >> 24) & 1);

  /* bit 25 = SSE	*/
  feature_set (cpu_info, CPU_FEATURE_SSE, (features >> 25) & 1);

  /* bit 26 = SSE 2 */
  feature_set (cpu_info, CPU_FEATURE_SSE2, (features >> 26) & 1);

  /* bit 27 = Self Snoop */
  feature_set (cpu_info, CPU_FEATURE_SS, (features >> 27) & 1);

  /* bit 28 = Reserved	*/

  /* bit 29 = Thermal Monitor supported */
  feature_set (cpu_info, CPU_FEATURE_TM, (features >> 29) & 1);

  /* bit 30 = IA-64 */
  feature_set (cpu_info, CPU_FEATURE_IA_64, (features >> 30) & 1);

  /* bit 31 = Reserved */

}

void process_amd_features (cpu_info_t *cpu_info, uint32_t features)
{
  uint32_t functions;
  uint32_t dummy;
  uint32_t ext_features = 0;
  uint32_t temp1, temp2, temp3, temp4;

  cpuid (CHECK_AMD_FEATURES, functions, dummy, dummy, dummy);

  if (functions > GET_AMD_CACHE_L2_INFO)
  {
    functions = GET_AMD_CACHE_L2_INFO;
  }
  
  switch (functions)
  {
    case GET_AMD_CACHE_L2_INFO:
    {
      cpuid (GET_AMD_CACHE_L2_INFO, temp1, temp2, temp3, temp4);        

      cpu_info->cache_l2_size = (temp3 >> 16) & 0xFFFF;
      feature_set (cpu_info, CPU_FEATURE_CACHE_L2_INFO, TRUE);
    }
    case GET_AMD_CACHE_L1_INFO:
    {

      cpuid (GET_AMD_CACHE_L1_INFO, temp1, temp2, temp3, temp4);        

      cpu_info->data_cache_l1_size = (temp3 >> 24) & 0xFF;
      cpu_info->instructions_cache_l1_size = (temp4 >> 24) & 0xFF;
      feature_set (cpu_info, CPU_FEATURE_CACHE_L1_INFO, TRUE);
    }	

    case GET_AMD_CPU_STRING_3:
    {
      feature_set (cpu_info, CPU_FEATURE_HARD_NAME, TRUE);

      cpuid (GET_AMD_CPU_STRING_3, 
             *((uint32_t *)(cpu_info->hard_cpu_name + 32)),
             *((uint32_t *)(cpu_info->hard_cpu_name + 36)),
	     *((uint32_t *)(cpu_info->hard_cpu_name + 40)),
             *((uint32_t *)(cpu_info->hard_cpu_name + 44)) );        
    }
    case GET_AMD_CPU_STRING_2:
    {
      cpuid (GET_AMD_CPU_STRING_2, 
             *((uint32_t *)(cpu_info->hard_cpu_name + 16)),
             *((uint32_t *)(cpu_info->hard_cpu_name + 20)),
	     *((uint32_t *)(cpu_info->hard_cpu_name + 24)),
             *((uint32_t *)(cpu_info->hard_cpu_name + 28)) );        
    }	
    case GET_AMD_CPU_STRING_1:
    {
      cpuid (GET_AMD_CPU_STRING_1,
             *((uint32_t *)(cpu_info->hard_cpu_name +  0)),
 
             *((uint32_t *)(cpu_info->hard_cpu_name +  4)),
	     *((uint32_t *)(cpu_info->hard_cpu_name +  8)),
             *((uint32_t *)(cpu_info->hard_cpu_name + 12)) );        
    }
    case GET_AMD_FEATURES:
    {
      cpuid (GET_AMD_FEATURES, dummy, dummy, dummy, ext_features);        
      /* bit 22 (ext) = SSE MMX Extensions */
      feature_set (cpu_info, CPU_FEATURE_SSE_MMX, (ext_features >> 22) & 1);

      /* bits 25|22(ext) = MMX Extensions */
      feature_set (cpu_info, CPU_FEATURE_MMX_EXT, ((features >> 25) & 1) | 
                   ((ext_features >> 22) & 1));

      /* AMD extended information */
    
      /* bit 29 (ext) = AA-64 */
      feature_set (cpu_info, CPU_FEATURE_AA_64, (ext_features >> 29) & 1);
    
      /* bit 30 (ext) = Extended 3DNow! */
      feature_set (cpu_info, CPU_FEATURE_3DNOW_EXT, (ext_features >> 30) & 1);
    
      /* bit 31 (ext) = 3DNow! */
      feature_set (cpu_info, CPU_FEATURE_3DNOW, (ext_features >> 31) & 1);
    }

  }
}

