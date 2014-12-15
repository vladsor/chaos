/* Sorokin Vladimir 21.10.2000 */

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

#define TRUE 1
#define FALSE 0
#include "types.h"

#define VENDOR_UNKNOWN_STRING		"------------"
#define VENDOR_AMD_STRING    		"AuthenticAMD"
#define VENDOR_Intel_STRING  		"GenuineIntel"
#define VENDOR_Cyrix_STRING  		"CyrixInstead"
#define VENDOR_Centaur_STRING		"CentaurHauls"
#define VENDOR_UMC_STRING		"UMC UMC UMC "
#define VENDOR_NexGen_STRING		"NexGenDriven"
#define VENDOR_RiseTechnology_STRING	"RiseRiseRise"

typedef enum CPU_TYPES
{
    UNKNOWN,
    UNKNOWN_INTEL,
    UNKNOWN_AMD,
    UNKNOWN_CYRIX,
    UNKNOWN_CENTAUR,

    UNKNOWN_8086,
    UNKNOWN_80186,
    UNKNOWN_80286,
    UNKNOWN_80386,
    UNKNOWN_80486,
    UNKNOWN_80586,
    UNKNOWN_80686,

    AMD_Am486,
    AMD_K5,
    AMD_K6,
    AMD_K6_2,
    AMD_K6_3,
    AMD_ATHLON,

    INTEL_486,
    INTEL_486DX,
    INTEL_486SX,
    INTEL_486DX2,
    INTEL_486SL,
    INTEL_486SX2,
    INTEL_486DX2E,
    INTEL_486DX4,
    INTEL_Pentium,
    INTEL_Pentium_MMX,
    INTEL_Pentium_Pro,
    INTEL_Pentium_II,
    INTEL_Celeron,
    INTEL_Pentium_III,
    INTEL_Pentium_Copermine
};

typedef enum FPU_TYPES
{
    FPU_NONE,
    FPU_8087,
    FPU_80287,
    FPU_80387,
    FPU_BUILT_IN
};

// Detected CPU Vendors - returned by GetCPUCaps (CPU_VENDOR_STRING);
typedef enum CPU_VENDORS
{
    VENDOR_UNKNOWN,
    VENDOR_AMD,
    VENDOR_Intel,
    VENDOR_Cyrix,
    VENDOR_Centaur,
    VENDOR_UMC,
    VENDOR_NexGen,
    VENDOR_RiseTechnology
};

struct vendor_info {
  CPU_VENDORS vendor_id;
  char* vendor_name;
};

struct vendor_info Vendor_Infos[] =
{
  VENDOR_UNKNOWN	,VENDOR_UNKNOWN_STRING,
  VENDOR_AMD		,VENDOR_AMD_STRING,
  VENDOR_Intel		,VENDOR_Intel_STRING,
  VENDOR_Cyrix		,VENDOR_Cyrix_STRING,
  VENDOR_Centaur	,VENDOR_Centaur_STRING,
  VENDOR_UMC		,VENDOR_UMC_STRING,
  VENDOR_NexGen		,VENDOR_NexGen_STRING,
  VENDOR_RiseTechnology	,VENDOR_RiseTechnology_STRING
};

// Detected CPU capabilities - used as input to the GetCPUCaps() function
typedef enum CPUCAPS
{
    // Synthesized values
    CPU_VENDOR,     // Manufacturer (returns enum CPU_VENDORS)
    CPU_TYPE,       // CPU type (return enum CPU_TYPES)
    CPU_VENDOR_STRING,  // CPU vendor name string (return const char *)
    CPU_NAME_STRING,// CPU Processor string (extended functions 0x80000002 - 0x80000004, return const char *)

    // Processor Features - returned as boolean values
    HAS_CPUID,      // Supports CPUID instruction
    HAS_FPU,        // FPU present
    HAS_VME,        // Virtual Mode Extensions
    HAS_DEBUG,      // Debug extensions
    HAS_PSE,        // Page Size Extensions
    HAS_TSC,        // Time Stamp Counter
    HAS_MSR,        // Model Specific Registers
    HAS_PAE,        // Physical Address Extensions
    HAS_MCE,        // Machine Check Extensions
    HAS_CMPXCHG8,   // CMPXCHG8 instruction
    HAS_APIC,       // APIC
    HAS_SYSENTER,   // SYSENTER/SYSEXIT instruction
    HAS_MTRR,       // Memory Type Range Registers
    HAS_GPE,        // Global Paging Extensions
    HAS_MCA,        // Machine Check Architecture
    HAS_CMOV,       // CMOV instruction
    HAS_PAT,        // Page Attribue Table
    HAS_PSE36,      // PSE36 (Page Size Extensions)

    HAS_MMX_EXT,    // MMX Extensions
    HAS_MMX,        // MMX support
    HAS_FXSAVE,     // FXSAVE/FXRSTOR instruction

    HAS_3DNOW_EXT,  // Extended 3DNow! support
    HAS_3DNOW,      // 3DNow! support

    HAS_SSE_MMX,    // SSE MMX support (same as HAS_MMXEXT)
    HAS_SSE,        // SSE
    HAS_SSE_FP,     // SSE FP support

    // Cache parameters (not all values apply to all processors)
    CPU_L1_DTLB_ASSOC,      // L1 Data Cache TLB Associativity
    CPU_L1_DTLB_ENTRIES,    // L1 Data Cache TLB Entries
    CPU_L1_ITLB_ASSOC,      // L1 Instruction Cache TLB Associativity (0xff = full associativity)
    CPU_L1_ITLB_ENTRIES,    // L1 Instruction Cache TLB Entries

    CPU_L1_EDTLB_ASSOC,     // Extended (2/4 Mbyte) L1 Data Cache TLB Associativity (0xff = full associativity)
    CPU_L1_EDTLB_ENTRIES,   // Extended (2/4 Mbyte) L1 Data Cache TLB Entries
    CPU_L1_EITLB_ASSOC,     // Extended (2/4 Mbyte) L1 Instruction Cache TLB Associativity
    CPU_L1_EITLB_ENTRIES,   // Extended (2/4 Mbyte) L1 Instruction Cache TLB Entries

    CPU_L1_DCACHE_SIZE,     // L1 Data Cache Size (kbytes)
    CPU_L1_DCACHE_ASSOC,    // L1 Data Cache Associativity (0xff = full associativity)
    CPU_L1_DCACHE_LINES,    // L1 Data Cache Lines
    CPU_L1_DCACHE_LSIZE,    // L1 Data Cache Line Size (bytes)

    CPU_L1_ICACHE_SIZE,     // L1 Instruction Cache Size (kbytes)
    CPU_L1_ICACHE_ASSOC,    // L1 Instruction Cache Associativity (0xff = full associativity)
    CPU_L1_ICACHE_LINES,    // L1 Instruction Cache Lines
    CPU_L1_ICACHE_LSIZE,    // L1 Instruction Cache Line Size (bytes)

    CPU_L2_CACHE_SIZE,      // L2 Unified Cache Size (Kbytes)
    CPU_L2_CACHE_ASSOC,     // L2 Unified Cache Associativity (0xf = full associativity)
    CPU_L2_CACHE_LINES,     // L2 Unified Cache Lines (lines per tag)
    CPU_L2_CACHE_LSIZE,     // L2 Unified Cache Line Size (bytes)

    CPU_L2_DTLB_ASSOC,      // L2 Data Cache TLB Associativity
    CPU_L2_DTLB_ENTRIES,    // L2 Data Cache TLB Entries
    CPU_L2_UTLB_ASSOC,      // L2 Instruction or Unified Cache TLB Associativity (0xf = full associativity)
    CPU_L2_UTLB_ENTRIES,    // L2 Instruction or Unified Cache TLB Entries

    CPU_L2_EDTLB_ASSOC,     // Extended (2/4 Mbyte) L2 Data Cache TLB Associativity (0xf = full associativity)
    CPU_L2_EDTLB_ENTRIES,   // Extended (2/4 Mbyte) L2 Data Cache TLB Entries
    CPU_L2_EUTLB_ASSOC,     // Extended (2/4 Mbyte) L2 Instruction or Unified Cache TLB Associativity
    CPU_L2_EUTLB_ENTRIES    // Extended (2/4 Mbyte) L2 Instruction or Unified Cache TLB Entries

};

struct cpu_info {
  unsigned char family;
  unsigned char model;
  CPU_VENDORS vendor_id;
  CPU_TYPES type_id;
};

#define NONE -1

struct cpu_info CPU_Infos[] =
{
 0,NONE,VENDOR_UNKNOWN,UNKNOWN_8086,
 1,NONE,VENDOR_UNKNOWN,UNKNOWN_80186,
 2,NONE,VENDOR_UNKNOWN,UNKNOWN_80286,
 3,NONE,VENDOR_UNKNOWN,UNKNOWN_80386,

 4,   2,VENDOR_INTEL,INTEL_486SX,
 4,   3,VENDOR_INTEL,INTEL_486DX2,
 4,   5,VENDOR_INTEL,INTEL_486SX2,
 4,   7,VENDOR_INTEL,INTEL_486DX2E,
 4,   8,VENDOR_INTEL,INTEL_486DX4,
 4,NONE,VENDOR_INTEL,INTEL_486,
 4,NONE,VENDOR_AMD,AMD_Am486,
 4,NONE,VENDOR_UNKNOWN,UNKNOWN_80486,

 5,3,VENDOR_AMD,AMD_K5,
 5,7,VENDOR_AMD,AMD_K6,
 5,8,VENDOR_AMD,AMD_K6_2,
 5,15,VENDOR_AMD,AMD_K5,

 5,3,VENDOR_INTEL,INTEL_Pentium,
 5,4,VENDOR_INTEL,INTEL_Pentium_MMX,
 5,NONE,VENDOR_INTEL,INTEL_Pentium,

 5,NONE,VENDOR_AMD,UNKNOWN_AMD,
 5,NONE,VENDOR_UNKNOWN,UNKNOWN_80586,

 6,   1,VENDOR_INTEL,INTEL_Pentium_Pro,
 6,   3,VENDOR_INTEL,INTEL_Pentium_II,
 6,   5,VENDOR_INTEL,INTEL_Pentium_II,
 6,   6,VENDOR_INTEL,INTEL_Celeron,
 6,   7,VENDOR_INTEL,INTEL_Pentium_III,

 6,NONE,VENDOR_INTEL,UNKNOWN_INTEL,
 6,NONE,VENDOR_AMD,AMD_ATHLON,
 6,NONE,VENDOR_UNKNOWN,UNKNOWN_80686,

 NONE,NONE,VENDOR_INTEL,UNKNOWN_INTEL,
 NONE,NONE,VENDOR_AMD,UNKNOWN_AMD,
 NONE,NONE,VENDOR_UNKNOWN,UNKNOWN
};

struct cpu_name {
  CPU_TYPES type_id;
  char* name;
};
struct cpu_name CPU_Names[] =
{
    UNKNOWN		,"Unknown",

    UNKNOWN_8086	,"8086",
    UNKNOWN_80286	,"80286",
    UNKNOWN_80386	,"80386",
    UNKNOWN_80486	,"80486",
    UNKNOWN_80586	,"80586",
    UNKNOWN_80686	,"80686",

    AMD_Am486		,"AMD 486",
    AMD_K5		,"AMD K5",
    AMD_K6		,"AMD K6",
    AMD_K6_2		,"AMD K6-II",
    AMD_K6_3		,"AMD K6-III",
    AMD_ATHLON		,"AMD Athlon",

    INTEL_486DX		,"Genuine IntelDX(TM)",
    INTEL_486SX		,"Genuine IntelSX(TM)",
    INTEL_486DX2	,"Genuine IntelDX2(TM)",
    INTEL_486SL		,"Genuine IntelSL(TM)",
    INTEL_486SX2	,"Genuine IntelSX2(TM)",
    INTEL_486DX2E	,"Genuine Write-Back Enhanced IntelDX2(TM)",
    INTEL_486DX4	,"Genuine IntelDX4(TM)",
    INTEL_Pentium	,"Genuine Intel Pentium(R) processor",
    INTEL_Pentium_MMX	,"Genuine Intel Pentium(R) MMX processor",
    INTEL_Pentium_Pro	,"Genuine Intel Pentium(R) Pro processor",
    INTEL_Pentium_II	,"Genuine Intel Pentium(R) II processor",
    INTEL_Celeron	,"Genuine Intel Pentium(R) Celeron processor",
    INTEL_Pentium_III	,"Genuine Intel Pentium(R) III processor",
    INTEL_Pentium_Copermine,"Genuine Intel Pentium(R) Copermine processor",
};

struct cpu_feature {
  long feature;
  char* info;
};
#define bool char

typedef struct cpu_flags {
  CPU_TYPES type_id;
  CPU_VENDORS vendor_id;
  char family;
  char model;
  char stepping;
  bool cpu_id_instruction;
  u32 features[100];
/*
  char cpu_type;
  char fpu_type;
  bool cpuid_flag;
  char vendor_id[12];
  long cpu_signature;
  long features_ecx;
  long features_edx;
  long features_ebx;
*/
};
cpu_flags CPU;
typedef struct cpu_cap {
  CPUCAPS cap;
  char* info;
};

unsigned long get_CPU_Caps (CPUCAPS);
void print_all_capabilities(void);

struct cpu_cap CPU_Caps []=
{
    HAS_CPUID	,"Supports CPUID instruction",
    HAS_FPU  	,"FPU present",
    HAS_VME  	,"Virtual Mode Extensions",
    HAS_DEBUG	,"Debug Extensions",
    HAS_PSE  	,"Page Size Extensions",
    HAS_TSC  	,"Time Stamp Counter",
    HAS_MSR  	,"Model Specific Registers",
    HAS_PAE  	,"Page Address Exceptions",
    HAS_MCE  	,"Machine Check Extensions",
    HAS_CMPXCHG8,"CMPXCHG8 instruction",
    HAS_APIC	,"APIC",
    HAS_SYSENTER,"SYSENTER/SYSEXIT instruction",
    HAS_MTRR	,"Memory Type Range Registers",
    HAS_GPE	,"Global Paging Extensions",
    HAS_MCA	,"Machine Check Architecture",
    HAS_CMOV	,"CMOV instruction",
    HAS_PAT	,"Page Attribue Table",
    HAS_PSE36	,"PSE36 (Page Size Extensions)",
    HAS_FXSAVE	,"FXSAVE/FXRSTOR instruction",

    HAS_MMX_EXT	,"MMX Extensions",
    HAS_MMX	,"MMX support",

    HAS_SSE	,"SSE",
    HAS_SSE_FP	,"SSE FP support",
    HAS_SSE_MMX	,"SSE MMX support (same as MMX extensions)",

    HAS_3DNOW	,"3DNow! support",
    HAS_3DNOW_EXT,"Extended 3DNow! support",

};

#endif /* !__STORM_IA32_CPUID_H__ */
