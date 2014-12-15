/* $Id: cpuid.c,v 1.1.1.1 2000/09/26 19:08:16 plundis Exp $ */
/* Abstract: CPU identification. Parts borrowed from the Linux
   kernel. */
/* Author: Per Lundberg <plundis@chaosdev.org>
           Parts borrowed from Linux kernel. */
/* Mostly rewriten by Sorokin Vladimir */

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
#include <storm/ia32/cpuid_ad.h>
#include <storm/ia32/cpuid-asm.h>

#include <storm/ia32/cpu.h>
#include <storm/ia32/flags.h>
#include <storm/ia32/memory.h>
#include <storm/ia32/port.h>
#include <storm/ia32/timer.h>
#include <storm/ia32/string.h>

#define DEBUG FALSE

/* CPUID functions. */

enum
{
  GET_CPU_VENDOR 	= 0,
  GET_CPU_INFO 		= 1,
  CHECK_AMD_FEATURES 	= 0x80000000,
  GET_AMD_FEATURES 	= 0x80000001,
  GET_AMD_CPU_STRING_1	= 0x80000002,
  GET_AMD_CPU_STRING_2	= 0x80000003,
  GET_AMD_CPU_STRING_3	= 0x80000004,
  GET_AMD_CACHE_L1_INFO	= 0x80000005,
  GET_AMD_CACHE_L2_INFO	= 0x80000006
};


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

void detect_cpu(void)
{ 
  debug_print("detecting cpu...\n");

  if(is_8086())
  {
    CPU.family = 0;
    debug_print("is 86.\n");
    cpu_halt();
  }
  else if(is_80286())
  {
    CPU.family = 2;
    debug_print("is 286.\n");
    cpu_halt();
  }
/*
  else if(is_80386())
  {
    CPU.family = 3;
    debug_print("is 386.\n");
  }
*/
  else if(is_80486())
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

  if(cpu_feature_get(CPU, CPU_FEATURE_FPU))
  {
    CPU.fpu_type_id = FPU_TYPE_BUILT_IN;
  }
  else
  {
    CPU.fpu_type_id = FPU_TYPE_NONE;
  }
  get_fpu_name();

#ifdef CPU_BASE_FAMILY
  if(CPU.family < CPU_BASE_FAMILY)
  {
    DEBUG_HALT("This kernel request more advanced processor.");
  }    
#endif
#ifdef MMX_BASE 
  if(!get_cpu_feature(CPU,CPU_FEATURE_MMX))
  {
    DEBUG_HALT("This kernel compiled for processor with MMX support.");
  }
#endif
#ifdef _3DNOW_BASE 
  if(!get_cpu_feature(CPU,CPU_FEATURE_3DNOW))
  {
    DEBUG_HALT("This kernel compiled for processor with 3D-NOW support.");
  }
#endif
#ifdef FPU_BASE
  if(!get_cpu_feature(CPU,CPU_FEATURE_FPU))
  {
    DEBUG_HALT("This kernel compiled for co-processor support.");
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

    if (CPU.cpu_name[0] == 0)
      get_cpu_name();

    response_cpu_sub_type();
    if (CPU.cpu_sub_type_id != CPU_SUB_TYPE_Standart)
      get_cpu_sub_name();
    
    process_features (features_edx);

    switch (CPU.vendor_id)
    {
      case VENDOR_AMD:
        process_amd_features (features_edx);
	break;
      case VENDOR_Intel:
        break;
      default:
    }

    if (cpu_feature_get(CPU, CPU_FEATURE_TSC))
    {
       debug_print("detecting frequency...");
       CPU.frequency = (u64)cpuid_get_cpu_speed ();
       scaled_frequency();
    }    
    return;
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
      string_copy(CPU.additional_info,CPU_sub_records[i].additional_info);
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

void process_features(u32 features)
{
    /* Feature Bit Test Capabilities */

/* bit  0 = FPU	*/    
    feature_set(CPU_FEATURE_FPU  ,	(features >>  0) & 1 );
    
/* bit  1 = Virtual Mode Extensions */    
    feature_set(CPU_FEATURE_VME  ,	(features >>  1) & 1 );
    
/* bit  2 = Debug extensions */
    feature_set(CPU_FEATURE_DEBUG,	(features >>  2) & 1 );
    
/* bit  3 = Page Size Extensions */
    feature_set(CPU_FEATURE_PSE  ,	(features >>  3) & 1 );

/* bit  4 = Time Stamp Counter */
    feature_set(CPU_FEATURE_TSC  ,	(features >>  4) & 1 );

/* bit  5 = Model Specific Registers */
    feature_set(CPU_FEATURE_MSR  ,	(u32)((features >>  5) & 1) );
    
/* bit  6 = Page Size Extensions */
    feature_set(CPU_FEATURE_PAE  ,	(u32)((features >>  6) & 1) );

/* bit  7 = Machine Check Extensions */
    feature_set(CPU_FEATURE_MCE  ,	(u32)((features >>  7) & 1) );

/* bit  8 = CMPXCHG8 instruction */
    feature_set(CPU_FEATURE_CMPXCHG8,	(u32)((features >>  8) & 1) );

/* bit  9 = APIC (Advanced Programmable Intrrupt Controller) */
    feature_set(CPU_FEATURE_APIC ,	(u32)((features >>  9) & 1) );

/* bit 10 = Reserved */

/* bit 11 = SYSENTER instruction */
    feature_set(CPU_FEATURE_SYSENTER,	(u32)((features >> 11) & 1) );

/* bit 12 = Memory Type Range Registers */
    feature_set(CPU_FEATURE_MTRR,	(u32)((features >> 12) & 1) );

/* bit 13 = Global Paging Extensions */
    feature_set(CPU_FEATURE_GPE,	(u32)((features >> 13) & 1) );
    
/* bit 14 = Machine Check Architecture */
    feature_set(CPU_FEATURE_MCA,	(u32)((features >> 14) & 1) );

/* bit 15 = CMOV instruction */
    feature_set(CPU_FEATURE_CMOV,	(u32)((features >> 15) & 1) );
    
/* bit 16 = Page Attribue Table */
    feature_set(CPU_FEATURE_PAT,	(u32)((features >> 16) & 1) );

/* bit 17 = PSE36 (Page Size Extensions) */
    feature_set(CPU_FEATURE_PSE36,	(u32)((features >> 17) & 1) );

/* bit 18 = Product Serial Number */
    feature_set(CPU_FEATURE_PSN,	(u32)((features >> 18) & 1) );
    
/* bit 19 = cache line flush instruction */
    feature_set(CPU_FEATURE_CLFLSH,	(u32)((features >> 19) & 1) );

/* bit 20 = Reserved */

/* bit 21 = Debug Trace and EMON Store */
    feature_set(CPU_FEATURE_DTES,	(u32)((features >> 21) & 1) );
    
/* bit 22 = processor duty cycle control */
    feature_set(CPU_FEATURE_ACPI,	(u32)((features >> 22) & 1) );

/* bit 23 = MMX	*/
    feature_set(CPU_FEATURE_MMX,	(u32)((features >> 23) & 1) );

/* bit 24 = FXSAVE/FXRSTOR instruction */
    feature_set(CPU_FEATURE_FXSAVE,	(u32)((features >> 24) & 1) );

/* bit 25 = SSE	*/
    feature_set(CPU_FEATURE_SSE,	(u32)((features >> 25) & 1) );

/* bit 26 = SSE 2 */
    feature_set(CPU_FEATURE_SSE_2,	(u32)((features >> 26) & 1) );

/* bit 27 = Self Snoop */
    feature_set(CPU_FEATURE_SELF_SNOOP,	(u32)((features >> 27) & 1) );

/* bit 28 = Reserved	*/

/* bit 29 = Automatic Clock Control */
    feature_set(CPU_FEATURE_ACC,	(u32)((features >> 29) & 1) );

/* bit 30 = IA-64 */
    feature_set(CPU_FEATURE_IA_64,	(u32)((features >> 30) & 1) );

/* bit 31 = Reserved */

}

void process_amd_features (u32 features)
{
  u32 functions;
  u32 dummy;
  u32 ext_features = 0;
  u32 temp1, temp2, temp3, temp4;

  cpuid (CHECK_AMD_FEATURES, functions, dummy, dummy, dummy);

  debug_print("features:%x\n",functions);

  if(functions >= GET_AMD_CACHE_L2_INFO)
  {
    debug_print("getting AMD cache L2 features...\n");

    cpuid (GET_AMD_CACHE_L2_INFO, temp1, temp2, temp3, temp4);        

    CPU.cache_l2_size = (temp3 >> 16) & 0xFFFF;
    feature_set (CPU_FEATURE_CACHE_L2_INFO, TRUE);
  }
  if(functions >= GET_AMD_CACHE_L1_INFO)
  {
    debug_print("getting AMD cache L1 features...\n");

    cpuid (GET_AMD_CACHE_L1_INFO, temp1, temp2, temp3, temp4);        

    CPU.data_cache_l1_size = (temp3 >> 24) & 0xFF;
    CPU.instructions_cache_l1_size = (temp4 >> 24) & 0xFF;
    feature_set (CPU_FEATURE_CACHE_L1_INFO, TRUE);
  }	

  if (functions >= GET_AMD_CPU_STRING_3)
  {
    feature_set(CPU_FEATURE_HARD_NAME, TRUE);
    debug_print("getting AMD processor string...\n");
    cpuid ( GET_AMD_CPU_STRING_3, *((u32 *)(CPU.cpu_name + 32)),
           *((u32 *)(CPU.cpu_name + 36)), *((u32 *)(CPU.cpu_name + 40)),
	   *((u32 *)(CPU.cpu_name + 44)) );        
  }
  if (functions >= GET_AMD_CPU_STRING_2)
  {
    cpuid ( GET_AMD_CPU_STRING_2, *((u32 *)(CPU.cpu_name + 16)),
           *((u32 *)(CPU.cpu_name + 20)), *((u32 *)(CPU.cpu_name + 24)),
	   *((u32 *)(CPU.cpu_name + 28)) );        
  }	
  if (functions >= GET_AMD_CPU_STRING_1)
  {
    cpuid ( GET_AMD_CPU_STRING_1, *((u32 *)(CPU.cpu_name + 0)), 
           *((u32 *)(CPU.cpu_name + 4)), *((u32 *)(CPU.cpu_name + 8)),
	   *((u32 *)(CPU.cpu_name + 12)) );        
  }
  if (functions >= GET_AMD_FEATURES)
  {
    debug_print("getting AMD extended features...\n");
    cpuid (GET_AMD_FEATURES, dummy, dummy, dummy, ext_features);        
  }

  /* bit 22 (ext) = SSE MMX Extensions */
  feature_set (CPU_FEATURE_SSE_MMX,(ext_features >> 22) & 1 );	

  /* bits 25|22(ext) = MMX Extensions */
  feature_set (CPU_FEATURE_MMX_EXT,((features >> 25)&1) | 
               ((ext_features >> 22)&1) );

  /* AMD extended information */
    
  /* bit 29 (ext) = AA-64 */
  feature_set (CPU_FEATURE_AA_64, (ext_features >> 29) & 1 );
    
  /* bit 30 (ext) = Extended 3DNow! */
  feature_set (CPU_FEATURE_3DNOW_EXT, (ext_features >> 30) & 1 );
    
  /* bit 31 (ext) = 3DNow! */
  feature_set (CPU_FEATURE_3DNOW, (ext_features >> 31) & 1 );
}
