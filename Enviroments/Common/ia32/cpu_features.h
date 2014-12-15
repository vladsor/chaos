/**
 * @file                cpu_features.h 
 * @brief               Definitions of cpu features and bugs.
 * @author              Vladimir Sorokin
 * @version             1.2
 * @date                2000-2002
 */

/* Copyright: chaos development. */

#ifndef __ENVIROMENT_IA32_CPU_FEATURES_H_
#define __ENVIROMENT_IA32_CPU_FEATURES_H_

/**
 * @brief               Hardcoded string of unknown CPU's vendor.
 */
#define VENDOR_UNKNOWN_STRING		"------------"

/**
 * @brief               Hardcoded string of AMD.
 */
#define VENDOR_AMD_STRING    		"AuthenticAMD"

/**
 * @brief               Hardcoded string of Intel.
 */
#define VENDOR_Intel_STRING  		"GenuineIntel"

/**
 * @brief               Hardcoded string of Cyrix.
 */
#define VENDOR_Cyrix_STRING  		"CyrixInstead"

/**
 * @brief               Hardcoded string of Centaur.
 */
#define VENDOR_Centaur_STRING		"CentaurHauls"

/**
 * @brief               Hardcoded string of UMC.
 */
#define VENDOR_UMC_STRING               "UMC UMC UMC " 

/**
 * @brief               Hardcoded string of NexGen.
 */
#define VENDOR_NexGen_STRING		"NexGenDriven"

/**
 * @brief               Hardcoded string of Rise Technology.
 */
#define VENDOR_RiseTechnology_STRING	"RiseRiseRise"

/**
 * @brief               Hardcoded string of Transmeta.
 */
#define VENDOR_Transmeta_STRING         "GenuineTMx86"

//FIXME: move elsewhere
/**
 * @brief              Type of platform.
 */
enum platform_t
{
  PLATFORM_80x86,
};

/**
 * @brief               CPU vendor type.
 */
enum vendor_t
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

/**
 * @brief               Major CPU type.
 */
enum cpu_t
{
  CPU_TYPE_UNKNOWN_PROCESSOR,
  CPU_TYPE_UNKNOWN_Intel,
  CPU_TYPE_UNKNOWN_AMD,
  CPU_TYPE_UNKNOWN_Cyrix,
  CPU_TYPE_UNKNOWN_Centaur,
  CPU_TYPE_UNKNOWN_Transmeta,

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
  CPU_TYPE_INTEL_Pentium_4,

  CPU_TYPE_Transmeta_TM3200,
  CPU_TYPE_Transmeta_TM5400,
  CPU_TYPE_Transmeta_TM5600,
        
};

/**
 * @brief               Minor CPU type.
 */
enum cpu_sub_t
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

/**
 * @brief               FPU type.
 */
enum fpu_t
{
    FPU_TYPE_NONE,
    FPU_TYPE_8087,
    FPU_TYPE_80287,
    FPU_TYPE_80387,
    FPU_TYPE_BUILT_IN, 
};

/**
 * @brief               Features supported by CPU.
 */
enum cpu_feature_t
{
  /* Processor Features - returned as boolean values */

  /**
   * @brief Supports CPUID instruction 
   */
  CPU_FEATURE_CPUID,

  /**
   * @brief Supports get cpu name 
   */
  CPU_FEATURE_CPU_NAME,	
    
  /**
   * @brief FPU present 
   *
   * The processor contains an FPU that supports the Intel387 floating-point 
   * instruction set.
   */
  CPU_FEATURE_FPU,

  /**
   * @brief Supports cache L1 info 
   */
  CPU_FEATURE_CACHE_L1_INFO,

  /**
   * @brief Supports cache L2 info 
   */
  CPU_FEATURE_CACHE_L2_INFO,

  /**
   * @brief Supports hardware get cpu name 
   */
  CPU_FEATURE_HARD_NAME,

  /**
   * @brief Virtual Mode Extensions 
   *
   * The processor supports extensions to virtual-8086 mode.
   */
  CPU_FEATURE_VME,

  /**
   * @brief Debug extensions 
   *
   * The processor supports I/O breakpoints, including the CR4.DE bit for 
   * enabling debug extensions and optional trapping of access to the DR4 and 
   * DR5 registers.
   */
  CPU_FEATURE_DEBUG,

  /**
   * @brief Page Size Extensions
   *
   * The processor supports 4-Mbyte pages.
   */
  CPU_FEATURE_PSE,

  /**
   * @brief Time Stamp Counter 
   *
   * The RDTSC instruction is supported including the CR4.TSD bit for 
   * access/privilege control.
   */
  CPU_FEATURE_TSC,

  /**
   * @brief Model Specific Registers 
   *
   * Model Specific Registers are implemented with the RDMSR, WRMSR 
   * instructions.
   */
  CPU_FEATURE_MSR,

  /**
   * @brief Physical Address Extensions 
   *
   * Physical addresses greater than 32 bits are supported.
   */
  CPU_FEATURE_PAE,

  /**
   * @brief Machine Check Exception
   *
   * Machine Check Exception, Exception 18, and the CR4.MCE enable bit are 
   * supported.
   */
  CPU_FEATURE_MCE,

  /**
   * @	brief CMPXCHG8 instruction Supported
   *
   * The compare and exchange 8 bytes instruction is supported.
   */
  CPU_FEATURE_CMPXCHG8,

  /**
   * @brief On-chip APIC Hardware Supported
   *
   * The processor contains a software-accessible Local APIC.
   */
  CPU_FEATURE_APIC,

  /**
   * @brief Fast System Call 
   *   
   * Indicates whether the processor supports the Fast System Call instructions,
   * SYSENTER and SYSEXIT. NOTE: Refer to "Intel Processor Identification and 
   * the CPUID Instruction" Section 3.4 for further information regarding 
   * SYSENTER/ SYSEXIT feature and SEP feature bit.
   */
  CPU_FEATURE_SEP,

  /**
   * @brief Memory Type Range Registers 
   *
   * The Processor supports the Memory Type Range Registers specifically the 
   * MTRR_CAP register.
   */
  CPU_FEATURE_MTRR,

  /**
   * @brief Page Global Enable
   *
   * The global bit in the page directory entries (PDEs) and page table entries
   * (PTEs) is supported, indicating TLB entries that are common to different 
   * processes and need not be flushed. The CR4.PGE bit controls this feature.
   */
  CPU_FEATURE_PGE,	

  /**
   * @brief Machine Check Architecture 
   *
   * The Machine Check Architecture is supported, specifically the MCG_CAP 
   * register.
   */
  CPU_FEATURE_MCA,

  /**
   * @brief Conditional Move Instruction Supported
   *
   * The processor supports CMOVcc, and if the FPU feature flag (bit 0) is also
   * set, supports the FCMOVCC and FCOMI instructions.
   */
  CPU_FEATURE_CMOV,

  /**
   * @brief Page Attribue Table 
   *
   * Indicates whether the processor supports the Page Attribute Table. This 
   * feature augments the Memory Type Range Registers (MTRRs), allowing an 
   * operating system to specify attributes of memory on 4K granularity through 
   * a linear address.
   */
  CPU_FEATURE_PAT,

  /**
   * @brief 36-bit Page Size Extension
   *
   * Indicates whether the processor supports 4-Mbyte pages that are capable of
   * addressing physical memory beyond 4GB. This feature indicates that the 
   * upper four bits of the physical address of the 4-Mbyte page is encoded by 
   * bits 13-16 of the page directory entry.
   */
  CPU_FEATURE_PSE36,

  /**
   * @brief Processor serial number is present and enabled
   *
   * The processor supports the 96-bit processor serial number feature, and the
   * feature is enabled.
   */
  CPU_FEATURE_PSN,

  /**
   * @brief CLFLUSH Instruction supported
   *
   * Indicates that the processor supports the CLFLUSH instruction.
   */
  CPU_FEATURE_CLFLSH,

  /**
   * @brief Debug Store 
   *
   * Indicates that the processor has the ability to write a history of the 
   * branch to and from addresses into a memory buffer.
   */
  CPU_FEATURE_DS,

  /**
   * @brief Thermal Monitor and Software Controlled Clock Facilities supported
   *
   * The processor implements internal MSRs that allow processor temperature to
   * be monitored and processor performance to be modulated in predefined duty 
   * cycles under software control.
   */
  CPU_FEATURE_ACPI,

  /**
   * @brief Intel Architecture MMX technology supported
   *
   * The processor supports the MMX technology instruction set extensions to 
   * Intel Architecture.
   */
  CPU_FEATURE_MMX,

  /**
   * @brief MMX Extensions 
   */
  CPU_FEATURE_MMX_EXT,

  /**
   * @brief Fast floating point save and restore
   *
   * Indicates whether the processor supports the FXSAVE and FXRSTOR 
   * instructions for fast save and restore of the floating point context. 
   * Presence of this bit also indicates that CR4.OSFXSR is available for an 
   * operating system to indicate that it uses the fast save/restore 
   * instructions.
   */
  CPU_FEATURE_FXSR,

  /**
   * @brief 3DNow! support 
   */
  CPU_FEATURE_3DNOW,

  /**
   * @brief Extended 3DNow! support 
   */
  CPU_FEATURE_3DNOW_EXT,

  /**
   * @brief Streaming SIMD Extensions supported
   *
   * The processor supports the Streaming SIMD Extensions to the Intel 
   * Architecture.
   */
  CPU_FEATURE_SSE,

  /**
   * @brief SSE FP support 
   */
  CPU_FEATURE_SSE_FP,

  /**
   * @brief SSE MMX support (same as FEATURE_MMX_EXT) 
   */
  CPU_FEATURE_SSE_MMX,

  /**
   * @brief Streaming SIMD Extensions 2
   *
   * Indicates the processor supports the Streaming SIMD Extensions - 2 
   * Instructions.
   */
  CPU_FEATURE_SSE2,

  /**
   * @brief Self-Snoop 
   *
   * The processor supports the management of conflicting memory types by 
   * performing a snoop of its own cache structure for transactions issued to 
   * the bus.
   */
  CPU_FEATURE_SS,

  /**
   * @brief Thermal Monitor supported
   *
   * The processor implements the Thermal Monitor automatic thermal control 
   * circuit (TCC).
   */
  CPU_FEATURE_TM,

  /* Undocumented or not released features */

  /* Intel Architecture - 64 */
  CPU_FEATURE_IA_64,

  /* AMD Architecture - 64 */
  CPU_FEATURE_AA_64,

  /* Voltage ID Control Suport */
  CPU_FEATURE_VIDC,

  /* Bus Multiplier Control */
  CPU_FEATURE_BMC,  

  CPU_FEATURE_LAST,
};

/**
 * @brief               Bugs founded in CPU.
 */
enum cpu_bug_t
{
  CPU_BUG_POPAD,
  CPU_BUG_F0_0F,

  CPU_BUG_LAST,
};

/**
 * @brief               Total number of features.
 */
#define NUMBER_OF_FEATURES	(CPU_FEATURE_LAST)

/**
 * @brief               Total number of bugs.
 */
#define NUMBER_OF_BUGS		(CPU_BUG_LAST)

#endif /* __ENVIROMENT_IA32_CPU_FEATURES_H */
