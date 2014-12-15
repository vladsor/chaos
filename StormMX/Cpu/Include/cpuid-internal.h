/* Abstract: Function prototypes and structure definitions for CPU
   identification routines. */
/* Author: Vladimir Sorokin. */

/* Copyright 2000-2001 chaos development. */

#ifndef __STORM_IA32_CPUID_INTERNAL_H__
#define __STORM_IA32_CPUID_INTERNAL_H__

int process_vendor (cpu_info_t *cpu_info, char vendor[12]);
int response_cpu (cpu_info_t *cpu_info, uint32_t signature);
int response_cpu_sub_type (cpu_info_t *cpu_info);
void bugs_search (cpu_info_t *cpu_info);

static inline void feature_set (
    cpu_info_t *current_cpu_info, unsigned int feature, bool value)
{
  current_cpu_info->features[feature] = value;
}

static inline bool feature_get (
    cpu_info_t *current_cpu_info, unsigned int feature)
{
    return current_cpu_info->features[feature];
}

void process_features (cpu_info_t *cpu_info, uint32_t features);
void process_amd_features (cpu_info_t *cpu_info, uint32_t features);
//void detect_cpu (cpu_info_t *cpu_info);
void process_cpu_id (cpu_info_t *cpu_info);

uint32_t cpuid_get_cpu_speed (void);
void scaled_frequency(void);

enum
{
    GET_CPU_VENDOR 				= 0,
    GET_CPU_INFO 				= 1,
    CHECK_AMD_FEATURES 				= 0x80000000,
    GET_AMD_FEATURES 				= 0x80000001,
    GET_AMD_CPU_STRING_1			= 0x80000002,
    GET_AMD_CPU_STRING_2			= 0x80000003,
    GET_AMD_CPU_STRING_3			= 0x80000004,
    GET_AMD_CACHE_L1_INFO			= 0x80000005,
    GET_AMD_CACHE_L2_INFO			= 0x80000006,
    GET_AMD_ADVANCED_POWER_MENEGMENT_FEATURES	= 0x80000007,
    GET_AMD_ADDRESS_SIZES			= 0x80000008,
};


typedef struct
{
    uint8_t vendor_id;
  
    char* vendor_string;
  
} vendor_record;

vendor_record Vendor_records[] =
{
  { VENDOR_UNKNOWN,		VENDOR_UNKNOWN_STRING },
  { VENDOR_AMD,			VENDOR_AMD_STRING },
  { VENDOR_Intel,		VENDOR_Intel_STRING },
  { VENDOR_Cyrix,		VENDOR_Cyrix_STRING },
  { VENDOR_Centaur,		VENDOR_Centaur_STRING },
  { VENDOR_UMC,			VENDOR_UMC_STRING },
  { VENDOR_NexGen,		VENDOR_NexGen_STRING },
  { VENDOR_RiseTechnology, 	VENDOR_RiseTechnology_STRING },
  { VENDOR_Transmeta,		VENDOR_Transmeta_STRING }
};

typedef struct
{
    uint16_t type_id;
    char* name;
} cpu_type_record;

typedef struct
{
    uint16_t sub_type_id;
    char* name;
} cpu_sub_type_record;

typedef struct
{
    uint8_t type_id;
    char* name;
} fpu_type_record;

typedef struct
{
    uint8_t family;
    uint8_t from_model;
    uint8_t to_model;
    uint8_t vendor_id;
    uint16_t cpu_type_id;
} cpu_record;


#define NONE -1
#define LAST -1

typedef struct
{
    uint8_t from_model;
    uint8_t to_model;
    uint8_t vendor_id;
    uint16_t cpu_type_id;
    
} cpu_family_record;

cpu_family_record family0[] =
{
  { 0,LAST, VENDOR_UNKNOWN,	CPU_TYPE_UNKNOWN_8086 },
};

cpu_family_record family1[] =
{
  { 0,LAST, VENDOR_UNKNOWN,	CPU_TYPE_UNKNOWN_80186 },
};

cpu_family_record family2[] =
{
  { 0,LAST, VENDOR_UNKNOWN,	CPU_TYPE_UNKNOWN_80286 },
};

cpu_family_record family3[] =
{
  { 0,LAST, VENDOR_UNKNOWN,	CPU_TYPE_UNKNOWN_80386 },
};

cpu_family_record family4[] =
{
  { 2,   2, VENDOR_Intel,	CPU_TYPE_INTEL_486SX },
  { 3,   3, VENDOR_Intel,	CPU_TYPE_INTEL_486DX2 },
  { 4,   4, VENDOR_Intel,	CPU_TYPE_INTEL_486SL },
  { 5,   5, VENDOR_Intel,	CPU_TYPE_INTEL_486SX2 },
  { 7,   7, VENDOR_Intel,	CPU_TYPE_INTEL_486DX2 },
  { 8,   9, VENDOR_Intel,	CPU_TYPE_INTEL_486DX4 },
  { 0,LAST, VENDOR_Intel,	CPU_TYPE_INTEL_486 },

  { 3,   7, VENDOR_AMD,		CPU_TYPE_AMD_486DX2 },
  { 8,   9, VENDOR_AMD,		CPU_TYPE_AMD_486DX4 },
  {0xE,0xF, VENDOR_AMD,		CPU_TYPE_AMD_5x86 },

  { 0,LAST, VENDOR_AMD,		CPU_TYPE_AMD_486 },

  { 4,   4, VENDOR_Cyrix,	CPU_TYPE_Cyrix_MediaGX },
  { 0,LAST, VENDOR_Cyrix,	CPU_TYPE_Cyrix_5x86 },

  { 1,   1, VENDOR_UMC,		CPU_TYPE_UMC_U5D },
  { 2,   2, VENDOR_UMC,		CPU_TYPE_UMC_U5S },

  { 0,LAST,VENDOR_UNKNOWN,	CPU_TYPE_UNKNOWN_80486 },
};

cpu_family_record family5[] =
{
  { 0,   3, VENDOR_AMD,		CPU_TYPE_AMD_K5 },
  { 7,   7, VENDOR_AMD,		CPU_TYPE_AMD_K6 },
  { 8,   8, VENDOR_AMD,		CPU_TYPE_AMD_K6_2 },
  { 9,   9, VENDOR_AMD,		CPU_TYPE_AMD_K6_3 },
  { 0,LAST, VENDOR_AMD,		CPU_TYPE_UNKNOWN_AMD },

  { 0,   8, VENDOR_Intel,	CPU_TYPE_INTEL_Pentium },
  { 0,LAST, VENDOR_Intel,	CPU_TYPE_UNKNOWN_INTEL_Pentium },

  { 4,   4, VENDOR_Cyrix,	CPU_TYPE_Cyrix_MediaGXm },
  { 0,LAST, VENDOR_Cyrix,	CPU_TYPE_Cyrix_6x86 },

  { 4,   4, VENDOR_Centaur,	CPU_TYPE_Centaur_C6 },
  { 8,   8, VENDOR_Centaur,	CPU_TYPE_Centaur_C2 },
  { 9,   9, VENDOR_Centaur,	CPU_TYPE_Centaur_C3 },

  { 0,   2, VENDOR_RiseTechnology, CPU_TYPE_Rise_mP6 },

  { 0,LAST, VENDOR_UNKNOWN,	CPU_TYPE_UNKNOWN_80586 },
};

cpu_family_record family6[] =
{
  { 0,   2, VENDOR_Intel,	CPU_TYPE_INTEL_Pentium_Pro },
  { 3,   6, VENDOR_Intel,	CPU_TYPE_INTEL_Pentium_II },
  { 7,   9, VENDOR_Intel,	CPU_TYPE_INTEL_Pentium_III },
  { 0,LAST, VENDOR_Intel,	CPU_TYPE_UNKNOWN_INTEL_P6 },

  { 0,LAST, VENDOR_AMD,		CPU_TYPE_AMD_Athlon },

  { 0,   0, VENDOR_Cyrix,	CPU_TYPE_Cyrix_6x86MX },

  { 0,LAST, VENDOR_UNKNOWN,	CPU_TYPE_UNKNOWN_80686 },
};

cpu_family_record family7[] =
{
  { 0,LAST, VENDOR_Intel,	CPU_TYPE_INTEL_Pentium_4 },
}
;

typedef struct
{
  cpu_family_record* family;
  int size_of_family;
} families_type;

families_type CPU_families[] =
{
  { family0,	sizeof (family0) / sizeof (cpu_family_record) },
  { family1,	sizeof (family1) / sizeof (cpu_family_record) },
  { family2,	sizeof (family2) / sizeof (cpu_family_record) },
  { family3,	sizeof (family3) / sizeof (cpu_family_record) },
  { family4,	sizeof (family4) / sizeof (cpu_family_record) },
  { family5,	sizeof (family5) / sizeof (cpu_family_record) },
  { family6,	sizeof (family6) / sizeof (cpu_family_record) },
  { family7,	sizeof (family7) / sizeof (cpu_family_record) },
};

typedef struct
{
    uint16_t cpu_type_id;
    uint8_t model;
    uint8_t stepping;
    uint16_t cpu_sub_type_id;
} cpu_sub_record;

cpu_sub_record CPU_sub_records[] =
{
  { CPU_TYPE_AMD_486DX2,		3, NONE, CPU_SUB_TYPE_Standart	},
  { CPU_TYPE_AMD_486DX2,		7, NONE, CPU_SUB_TYPE_WriteBackEnhanced },
  { CPU_TYPE_AMD_486DX4,		8, NONE, CPU_SUB_TYPE_Standart	},
  { CPU_TYPE_AMD_486DX4,		9, NONE, CPU_SUB_TYPE_WriteBackEnhanced },
  { CPU_TYPE_AMD_5x86,		      0xE, NONE, CPU_SUB_TYPE_Standart	},
  { CPU_TYPE_AMD_5x86,		      0xF, NONE, CPU_SUB_TYPE_WriteBackEnhanced },

  { CPU_TYPE_INTEL_Pentium,		0, NONE, CPU_SUB_TYPE_A_step },
  { CPU_TYPE_INTEL_Pentium,		1, NONE, CPU_SUB_TYPE_Standart },
  { CPU_TYPE_INTEL_Pentium,		2, NONE, CPU_SUB_TYPE_Standart },
  { CPU_TYPE_INTEL_Pentium,		3, NONE, CPU_SUB_TYPE_Overdrive },
  { CPU_TYPE_INTEL_Pentium,		4, NONE, CPU_SUB_TYPE_MMX },
  { CPU_TYPE_INTEL_Pentium,		7, NONE, CPU_SUB_TYPE_Standart },
  { CPU_TYPE_INTEL_Pentium,		8, NONE, CPU_SUB_TYPE_MMX },

  { CPU_TYPE_AMD_K5,			0, NONE, CPU_SUB_TYPE_Standart },
  { CPU_TYPE_AMD_K5,			1, NONE, CPU_SUB_TYPE_Standart },
  { CPU_TYPE_AMD_K5,			2, NONE, CPU_SUB_TYPE_Standart },
  { CPU_TYPE_AMD_K5,			3, NONE, CPU_SUB_TYPE_Standart },
 
  { CPU_TYPE_INTEL_Pentium_Pro,		0, NONE, CPU_SUB_TYPE_A_step },
  { CPU_TYPE_INTEL_Pentium_Pro,		1, NONE, CPU_SUB_TYPE_Standart },

  { CPU_TYPE_INTEL_Pentium_II,		3,    0, CPU_SUB_TYPE_Standart },
  { CPU_TYPE_INTEL_Pentium_II,		5,    1, CPU_SUB_TYPE_Celeron },
  { CPU_TYPE_INTEL_Pentium_II,		5,    2, CPU_SUB_TYPE_Standart },
  { CPU_TYPE_INTEL_Pentium_II,		5,    3, CPU_SUB_TYPE_Xeon },
  { CPU_TYPE_INTEL_Pentium_II,		6,    1, CPU_SUB_TYPE_Celeron },
  { CPU_TYPE_INTEL_Pentium_III,		7,    1, CPU_SUB_TYPE_CeleronII },
  { CPU_TYPE_INTEL_Pentium_III,		7,    2, CPU_SUB_TYPE_Standart },
  { CPU_TYPE_INTEL_Pentium_III,		7,    3, CPU_SUB_TYPE_Xeon },
  { CPU_TYPE_INTEL_Pentium_III,		8,    1, CPU_SUB_TYPE_CeleronII },
  { CPU_TYPE_INTEL_Pentium_III,		8,    2, CPU_SUB_TYPE_Standart },
  { CPU_TYPE_INTEL_Pentium_III,		8,    3, CPU_SUB_TYPE_Xeon },

  { CPU_TYPE_AMD_K6,   			6, NONE, CPU_SUB_TYPE_Standart },
  { CPU_TYPE_AMD_K6,			7, NONE, CPU_SUB_TYPE_Standart },
  { CPU_TYPE_AMD_K6_2,			8, NONE, CPU_SUB_TYPE_Standart },
  { CPU_TYPE_AMD_K6_3,			9, NONE, CPU_SUB_TYPE_Standart },

  { CPU_TYPE_AMD_Athlon,		1, NONE, CPU_SUB_TYPE_Standart },
  { CPU_TYPE_AMD_Athlon,		2, NONE, CPU_SUB_TYPE_Standart },
  { CPU_TYPE_AMD_Athlon,		3, NONE, CPU_SUB_TYPE_Duron },
  { CPU_TYPE_AMD_Athlon,		4, NONE, CPU_SUB_TYPE_Thinderbird },
};

#endif /* __STORM_IA32_CPUID_INTERNAL_H__ */
