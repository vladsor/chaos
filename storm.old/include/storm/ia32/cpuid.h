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


//extern cpu_info_type cpu_info;
//extern parsed_cpu_type parsed_cpu;
 
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

typedef enum
{
    VENDOR_UNKNOWN,
    VENDOR_AMD,
    VENDOR_Intel,
    VENDOR_Cyrix,
    VENDOR_Centaur,
    VENDOR_UMC,
    VENDOR_NexGen,
    VENDOR_RiseTechnology,
    VENDOR_Transmeta,
} CPU_vendor;

typedef enum
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
    
} CPU_type;

typedef enum
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
    
} CPU_sub_type;

typedef enum
{
    FPU_NONE,
    FPU_8087,
    FPU_80287,
    FPU_80387,
    FPU_BUILT_IN
} FPU_type;

// Detected CPU capabilities - used as input to the GetCPUCaps() function
typedef enum
{
    /* Processor Features - returned as boolean values			*/
    FEATURE_CPUID,     	/* Supports CPUID instruction			*/
    FEATURE_CPU_NAME,	/* Supports get cpu name			*/
    
    FEATURE_FPU,        /* FPU present					*/
    FEATURE_VME,        /* Virtual Mode Extensions			*/
    FEATURE_DEBUG,	/* Debug extensions				*/
    FEATURE_PSE,        /* Page Size Extensions				*/
    FEATURE_TSC,        /* Time Stamp Counter				*/
    FEATURE_MSR,	/* Model Specific Registers			*/
    FEATURE_PAE,        /* Physical Address Extensions			*/
    FEATURE_MCE,        /* Machine Check Extensions			*/
    FEATURE_CMPXCHG8,	/* CMPXCHG8 instruction				*/
    FEATURE_APIC,	/* APIC						*/
    FEATURE_SYSENTER,	/* SYSENTER/SYSEXIT instruction			*/
    FEATURE_MTRR,	/* Memory Type Range Registers			*/
    FEATURE_GPE,	/* Global Paging Extensions			*/
    FEATURE_PGE = FEATURE_GPE,	
    FEATURE_MCA,	/* Machine Check Architecture			*/
    FEATURE_CMOV,	/* CMOV instruction				*/
    FEATURE_PAT,	/* Page Attribue Table				*/
    FEATURE_PSE36,	/* PSE36 (Page Size Extensions)			*/

    FEATURE_MMX,	/* MMX support					*/
    FEATURE_MMX_EXT,	/* MMX Extensions				*/
    FEATURE_FXSAVE,	/* FXSAVE/FXRSTOR instruction			*/

    FEATURE_3DNOW,	/* 3DNow! support				*/
    FEATURE_3DNOW_EXT,	/* Extended 3DNow! support			*/

    FEATURE_SSE,	/* SSE						*/
    FEATURE_SSE_FP,	/* SSE FP support				*/
    FEATURE_SSE_MMX,	/* SSE MMX support (same as FEATURE_MMXEXT)	*/

    FEATURE_SELF_SNOOP,	/* Self Snoop					*/
    FEATURE_ACC,	/* Automatic Clock Control			*/
    FEATURE_IA_64,	/* Intel Architecture - 64			*/
    FEATURE_PSN,	/* Product Serial Number			*/
    FEATURE_CLFLSH,	/* Cache line flush instruction CLFLSH		*/
    FEATURE_DTES,	/* Debug Trace and EMON Store			*/
    FEATURE_ACPI,	/* processor duty cycle control (ACPI)		*/
    FEATURE_SSE_2,	/* SSE2 instructions				*/
    FEATURE_AA_64,	/* AMD Architecture - 64			*/
    FEATURE_VIDC,	/* Voltage ID Control Suport			*/
    FEATURE_BMC,	/* Bus Multiplier Control			*/

    FEATURE_CACHE_L1_INFO,
    FEATURE_CACHE_L2_INFO,
    FEATURE_HARD_NAME,
    
} CPU_Capability;

#define NAME_LENGTH 49
#define FEATURES_NUMBER 50
typedef struct
{
  CPU_type cpu_type_id;
  CPU_sub_type cpu_sub_type_id;
  FPU_type fpu_type_id;
  CPU_vendor vendor_id;
  char cpu_name[NAME_LENGTH];
  char hardware_cpu_name[49];
  char additional_info[NAME_LENGTH];
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
  bool features[FEATURES_NUMBER];
} full_cpu_info;

extern unsigned int cpus;
extern full_cpu_info CPU;
										
static inline bool cpu_feature_get(full_cpu_info cpu,CPU_Capability cap)
{
  return ((cpu.features[cap]));
}

#endif /* !__STORM_IA32_CPUID_H__ */
