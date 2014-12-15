/* $Id: cpuid.h,v 1.1.1.1 2000/09/26 19:08:18 plundis Exp $ */
/* Abstract: Function prototypes and structure definitions for CPU
   identification routines. */

/* Copyright 1999 chaos development. */

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
   USA */

#ifndef __STORM_IA32_CPUID_H__
#define __STORM_IA32_CPUID_H__

#include <storm/ia32/defines.h>
#include <storm/ia32/types.h>
 
/* External functions. */

extern void cpuid_init (void) INIT_CODE;

#define VENDOR_UNKNOWN_STRING		"------------"
#define VENDOR_AMD_STRING    		"AuthenticAMD"
#define VENDOR_Intel_STRING  		"GenuineIntel"
#define VENDOR_Cyrix_STRING  		"CyrixInstead"
#define VENDOR_Centaur_STRING		"CentaurHauls"
#define VENDOR_UMC_STRING		"UMC UMC UMC "
#define VENDOR_NexGen_STRING		"NexGenDriven"
#define VENDOR_RiseTechnology_STRING	"RiseRiseRise"
#define VENDOR_Transmeta_STRING         "GenuineTMx86"

enum
{
  PLATFORM_80x86,
};

enum
{
    VENDOR_UNKNOWN,
    VENDOR_AMD,
    VENDOR_Intel,
    VENDOR_Cyrix,
    VENDOR_Centaur,
    VENDOR_UMC,
    VENDOR_NexGen,
    VENDOR_RiseTechnology,
    VENDOR_Transmeta,
};

enum
{
    CPU_TYPE_UNKNOWN_PROCESSOR,
    CPU_TYPE_UNKNOWN_INTEL,
    CPU_TYPE_UNKNOWN_AMD,
    CPU_TYPE_UNKNOWN_CYRIX,
    CPU_TYPE_UNKNOWN_CENTAUR,

    CPU_TYPE_UNKNOWN_8086,
    CPU_TYPE_UNKNOWN_80186,
    CPU_TYPE_UNKNOWN_80286,
    CPU_TYPE_UNKNOWN_80386,
    CPU_TYPE_UNKNOWN_80486,
    CPU_TYPE_UNKNOWN_80586,
    CPU_TYPE_UNKNOWN_80686,

    CPU_TYPE_UNKNOWN_INTEL_Pentium,
    CPU_TYPE_UNKNOWN_INTEL_P6,
    CPU_TYPE_UNKNOWN_AMD_Athlon,

    CPU_TYPE_AMD_486,
    CPU_TYPE_AMD_486DX2,
    CPU_TYPE_AMD_486DX4,
    CPU_TYPE_AMD_5x86,
    CPU_TYPE_AMD_K5,
    CPU_TYPE_AMD_K6,
    CPU_TYPE_AMD_K6_2,
    CPU_TYPE_AMD_K6_3,
    CPU_TYPE_AMD_Athlon,

    CPU_TYPE_Cyrix_5x86,
    CPU_TYPE_Cyrix_MediaGX,
    CPU_TYPE_Cyrix_MediaGXm,
    CPU_TYPE_Cyrix_M1,
    CPU_TYPE_Cyrix_M2,
    CPU_TYPE_Cyrix_III,
    CPU_TYPE_Cyrix_6x86,
    CPU_TYPE_Cyrix_6x86MX,

    CPU_TYPE_Centaur_C6,
    CPU_TYPE_Centaur_C2,
    CPU_TYPE_Centaur_C3,

    CPU_TYPE_Rise_mP6,

    CPU_TYPE_UMC_U5D,
    CPU_TYPE_UMC_U5S,
    
    CPU_TYPE_INTEL_486,
    CPU_TYPE_INTEL_486DX,
    CPU_TYPE_INTEL_486SX,
    CPU_TYPE_INTEL_486SL,
    CPU_TYPE_INTEL_486DX2,
    CPU_TYPE_INTEL_486SX2,
    CPU_TYPE_INTEL_486DX4,

    CPU_TYPE_INTEL_Pentium,
    
    CPU_TYPE_INTEL_Pentium_Pro,
    CPU_TYPE_INTEL_Pentium_II,
    CPU_TYPE_INTEL_Pentium_III,
    CPU_TYPE_INTEL_Pentium_IV,
    
};

enum
{
    CPU_SUB_TYPE_A_step,
    CPU_SUB_TYPE_Standart,
    CPU_SUB_TYPE_Mobile,
    CPU_SUB_TYPE_Overdrive,
    CPU_SUB_TYPE_WriteBackEnhanced,    
    CPU_SUB_TYPE_MMX,
    
    CPU_SUB_TYPE_Celeron,
    CPU_SUB_TYPE_CeleronII,
    CPU_SUB_TYPE_Xeon,
    CPU_SUB_TYPE_Coppermine,
    
    CPU_SUB_TYPE_Duron,
    CPU_SUB_TYPE_Thinderbird
};

enum
{
    FPU_TYPE_NONE,
    FPU_TYPE_8087,
    FPU_TYPE_80287,
    FPU_TYPE_80387,
    FPU_TYPE_BUILT_IN, 
};

/* Detected CPU features */
enum
{
  /* Processor Features - returned as boolean values */

  /* Supports CPUID instruction */
  CPU_FEATURE_CPUID,

  /* Supports get cpu name */
  CPU_FEATURE_CPU_NAME,	
    
  /* FPU present */
  CPU_FEATURE_FPU,

  /* Supports cache L1 info */
  CPU_FEATURE_CACHE_L1_INFO,

  /* Supports cache L2 info */
  CPU_FEATURE_CACHE_L2_INFO,

  /* Supports hardware get cpu name */
  CPU_FEATURE_HARD_NAME,

  /* Product Serial Number */
  CPU_FEATURE_PSN,

  /* Virtual Mode Extensions */
  CPU_FEATURE_VME,

  /* Debug extensions */
  CPU_FEATURE_DEBUG,

  /* Page Size Extensions	*/
  CPU_FEATURE_PSE,

  /* Time Stamp Counter */
  CPU_FEATURE_TSC,

  /* Model Specific Registers */
  CPU_FEATURE_MSR,

  /* Physical Address Extensions */
  CPU_FEATURE_PAE,

  /* Machine Check Extensions */
  CPU_FEATURE_MCE,

  /* CMPXCHG8 instruction */
  CPU_FEATURE_CMPXCHG8,

  /* APIC */
  CPU_FEATURE_APIC,

  /* SYSENTER/SYSEXIT instruction */
  CPU_FEATURE_SYSENTER,

  /* Memory Type Range Registers */
  CPU_FEATURE_MTRR,

  /* Global Paging Extensions */
  CPU_FEATURE_GPE,
  CPU_FEATURE_PGE = CPU_FEATURE_GPE,	

  /* Machine Check Architecture */
  CPU_FEATURE_MCA,

  /* CMOV instruction */
  CPU_FEATURE_CMOV,

  /* Page Attribue Table */
  CPU_FEATURE_PAT,

  /* PSE36 (Page Size Extensions) */
  CPU_FEATURE_PSE36,

  /* MMX support */
  CPU_FEATURE_MMX,

  /* MMX Extensions */
  CPU_FEATURE_MMX_EXT,

  /* FXSAVE/FXRSTOR instruction */
  CPU_FEATURE_FXSAVE,

  /* 3DNow! support */
  CPU_FEATURE_3DNOW,

  /* Extended 3DNow! support */
  CPU_FEATURE_3DNOW_EXT,

  /* SSE */
  CPU_FEATURE_SSE,

  /* SSE FP support */
  CPU_FEATURE_SSE_FP,

  /* SSE MMX support (same as FEATURE_MMXEXT) */
  CPU_FEATURE_SSE_MMX,

  /* Undocumented features or not released */
  /* Self Snoop */
  CPU_FEATURE_SELF_SNOOP,

  /* Automatic Clock Control */
  CPU_FEATURE_ACC,

  /* Intel Architecture - 64 */
  CPU_FEATURE_IA_64,

  /* Cache line flush instruction CLFLSH */
  CPU_FEATURE_CLFLSH,

  /* Debug Trace and EMON Store */
  CPU_FEATURE_DTES,

  /* processor duty cycle control (ACPI) */
  CPU_FEATURE_ACPI,

  /* SSE2 instructions */
  CPU_FEATURE_SSE_2,

  /* AMD Architecture - 64 */
  CPU_FEATURE_AA_64,

  /* Voltage ID Control Suport */
  CPU_FEATURE_VIDC,

  /* Bus Multiplier Control */
  CPU_FEATURE_BMC,  
};

enum
{
  CPU_BUG_F0_0F,
};

#define NAME_LENGTH 49
#define NUMBER_OF_FEATURES 50
#define NUMBER_OF_BUGS 1

typedef struct
{
  u8 platform;
  
  u16 cpu_type_id;
  u16 cpu_sub_type_id;
  u8 fpu_type_id;
  u8 vendor_id;

  char cpu_name[NAME_LENGTH];
  char hardware_cpu_name[49];
  char fpu_name[NAME_LENGTH];

  u32 frequency;
  u16 scaled_frequency;
  char frequency_scale;

  char vendor_string[13];
  char vendor_name[NAME_LENGTH];

  char family;
  char model;
  char stepping;
  char generation;

  u32 data_cache_l1_size;
  u32 instructions_cache_l1_size;  
  u32 cache_l2_size;
  bool features[NUMBER_OF_FEATURES];
  bool bugs[NUMBER_OF_BUGS];
} full_cpu_info;

extern unsigned int cpus;
extern full_cpu_info CPU;
										
static inline bool cpu_feature_get (full_cpu_info cpu, unsigned int feature)
{
  return cpu.features[feature];
}

#endif /* !__STORM_IA32_CPUID_H__ */
