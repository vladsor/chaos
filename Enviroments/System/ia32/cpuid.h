
#ifndef __SYSTEM_ENVIROMENT_IA32_CPUID_H__
#define __SYSTEM_ENVIROMENT_IA32_CPUID_H__

/** 
 * @defgroup group_cpuid_vendor_strings Hardcoded vendors strings
 *
 * @brief     
 *
 * @{
 */

#define CPU_VENDOR_STRING_LENGTH (12)

/**
 * @brief               Hardcoded string of unknown CPU's vendor.
 */
#define VENDOR_UNKNOWN_STRING       "------------"

/**
 * @brief               Hardcoded string of AMD.
 */
#define VENDOR_AMD_STRING           "AuthenticAMD"

/**
 * @brief               Hardcoded string of Intel.
 */
#define VENDOR_INTEL_STRING         "GenuineIntel"

/**
 * @brief               Hardcoded string of Cyrix.
 */
#define VENDOR_CYRIX_STRING         "CyrixInstead"

/**
 * @brief               Hardcoded string of Centaur.
 */
#define VENDOR_CENTAUR_STRING       "CentaurHauls"

/**
 * @brief               Hardcoded string of UMC.
 */
#define VENDOR_UMC_STRING               "UMC UMC UMC "

/**
 * @brief               Hardcoded string of NexGen.
 */
#define VENDOR_NEXGEN_STRING        "NexGenDriven"

/**
 * @brief               Hardcoded string of Rise Technology.
 */
#define VENDOR_RISETECHNOLOGY_STRING    "RiseRiseRise"

/**
 * @brief               Hardcoded string of Transmeta.
 */
#define VENDOR_TRANSMETA_STRING         "GenuineTMx86"

/**
 * @} // end of group_cpuid_vendor_strings
 */

enum cpu_id_command_t
{
    GET_CPU_VENDOR                              = 0,
    GET_CPU_INFO                                = 1,
    CHECK_AMD_FEATURES                          = 0x80000000,
    GET_AMD_FEATURES                            = 0x80000001,
    GET_AMD_CPU_STRING_1                        = 0x80000002,
    GET_AMD_CPU_STRING_2                        = 0x80000003,
    GET_AMD_CPU_STRING_3                        = 0x80000004,
    GET_AMD_CACHE_L1_INFO                       = 0x80000005,
    GET_AMD_CACHE_L2_INFO                       = 0x80000006,
    GET_AMD_ADVANCED_POWER_MENEGMENT_FEATURES   = 0x80000007,
    GET_AMD_ADDRESS_SIZES                       = 0x80000008,
};

#endif /* !__SYSTEM_ENVIROMENT_IA32_CPUID_H__ */

