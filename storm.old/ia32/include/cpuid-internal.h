
int process_vendor(char vendor[12]);
int response_cpu(u32 signature);
int response_cpu_sub_type(void);
int get_cpu_name(void);
int get_cpu_sub_name(void);
int get_fpu_name(void);
void bugs_search (void);
static inline void feature_set (unsigned int feature,bool value)
{
  CPU.features[feature] = value;
}

static inline bool feature_get (unsigned int feature)
{
  return CPU.features[feature];
}

void process_features(u32 features);
void process_amd_features(u32 features);
void detect_cpu(void);
void process_cpu_id(void);

u32 INIT_CODE cpuid_get_cpu_speed (void);
void scaled_frequency(void);

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

typedef struct
{
  u8 vendor_id;
  char* vendor_name;
  char* vendor_string;
} vendor_record;

vendor_record Vendor_records[] =
 {
  { VENDOR_UNKNOWN	,"Unknown"	,VENDOR_UNKNOWN_STRING },
  { VENDOR_AMD		,"AMD"		,VENDOR_AMD_STRING },
  { VENDOR_Intel	,"Intel"	,VENDOR_Intel_STRING },
  { VENDOR_Cyrix	,"Cyrix"	,VENDOR_Cyrix_STRING },
  { VENDOR_Centaur	,"Centaur"	,VENDOR_Centaur_STRING },
  { VENDOR_UMC		,"UMC"		,VENDOR_UMC_STRING },
  { VENDOR_NexGen	,"NexGen"	,VENDOR_NexGen_STRING },
  { VENDOR_RiseTechnology,"RiseTechnology",VENDOR_RiseTechnology_STRING },
  { VENDOR_Transmeta	,"Transmeta"	,VENDOR_Transmeta_STRING }
};

typedef struct
{
  u16 type_id;
  char* name;
} cpu_type_record;

cpu_type_record CPU_type_records[] =
{
  { CPU_TYPE_UNKNOWN_PROCESSOR	,"Unknown" },

  { CPU_TYPE_UNKNOWN_8086	,"8086" },
  { CPU_TYPE_UNKNOWN_80286	,"80286" },
  { CPU_TYPE_UNKNOWN_80386	,"80386" },
  { CPU_TYPE_UNKNOWN_80486	,"80486" },
  { CPU_TYPE_UNKNOWN_80586	,"80586" },
  { CPU_TYPE_UNKNOWN_80686	,"80686" },

  { CPU_TYPE_AMD_486		,"Am486" },

  { CPU_TYPE_AMD_486DX2		,"Am486DX2" },
  { CPU_TYPE_AMD_486DX4		,"Am486DX4" },
  { CPU_TYPE_AMD_5x86		,"Am5x86" },

  { CPU_TYPE_AMD_K5		,"AMD K5" },
  { CPU_TYPE_AMD_K6		,"AMD K6" },
  { CPU_TYPE_AMD_K6_2		,"AMD K6-II" },
  { CPU_TYPE_AMD_K6_3		,"AMD K6-III" },
  { CPU_TYPE_AMD_Athlon		,"AMD Athlon" },

  { CPU_TYPE_INTEL_486DX	,"Genuine IntelDX" },
  { CPU_TYPE_INTEL_486SX	,"Genuine IntelSX" },
  { CPU_TYPE_INTEL_486SL	,"Genuine IntelSL" },
  { CPU_TYPE_INTEL_486SX2	,"Genuine IntelSX2" },
  { CPU_TYPE_INTEL_486DX2	,"Genuine IntelDX2" },
  { CPU_TYPE_INTEL_486DX4	,"Genuine IntelDX4" },

  { CPU_TYPE_UNKNOWN_INTEL_Pentium,"Unknown Genuine Intel Pentium" },
  { CPU_TYPE_INTEL_Pentium	,"Genuine Intel Pentium" },

  { CPU_TYPE_UNKNOWN_INTEL_P6	,"Unknown Genuine Intel P6" },
  { CPU_TYPE_INTEL_Pentium_Pro	,"Genuine Intel Pentium Pro" },
  { CPU_TYPE_INTEL_Pentium_II	,"Genuine Intel Pentium II" },
  { CPU_TYPE_INTEL_Pentium_III	,"Genuine Intel Pentium III" },

  { CPU_TYPE_Cyrix_5x86		,"5x86" },
  { CPU_TYPE_Cyrix_MediaGX	,"MediaGX" },
  { CPU_TYPE_Cyrix_MediaGXm	,"MediaGX MMX Enhanced" },
  { CPU_TYPE_Cyrix_6x86		,"6x86(L)" },
  { CPU_TYPE_Cyrix_6x86MX	,"6x86MX" },
/*    
    Cyrix_M1,
    Cyrix_M2,
    Cyrix_III,
*/
  { CPU_TYPE_Centaur_C6		,"C6" },
  { CPU_TYPE_Centaur_C2		,"C2" },
  { CPU_TYPE_Centaur_C3		,"C3" },

  { CPU_TYPE_Rise_mP6		,"mP6" },

  { CPU_TYPE_UMC_U5D		,"U5D" },
  { CPU_TYPE_UMC_U5S		,"U5S" },
};

typedef struct
{
  u16 sub_type_id;
  char* name;
} cpu_sub_type_record;

cpu_sub_type_record CPU_sub_type_records[] =
{
  { CPU_SUB_TYPE_A_step		,"A-step" },
  { CPU_SUB_TYPE_Standart	,"" },
  { CPU_SUB_TYPE_Overdrive	,"Overdrive" },
  { CPU_SUB_TYPE_Mobile		,"Mobile" },
    
  { CPU_SUB_TYPE_Celeron	,"MMX" },
  { CPU_SUB_TYPE_Celeron	,"Celeron" },
  { CPU_SUB_TYPE_Celeron	,"CeleronII" },
  { CPU_SUB_TYPE_Xeon		,"Xeon" },
  { CPU_SUB_TYPE_Coppermine	,"Coppermine" },
    
  { CPU_SUB_TYPE_Duron		,"Duron" },
  { CPU_SUB_TYPE_Thinderbird	,"Thinderbird" }
};

typedef struct
{
  u8 type_id;
  char* name;
} fpu_type_record;

fpu_type_record FPU_type_records[] = 
{
  { FPU_TYPE_NONE		,"none"},
  { FPU_TYPE_8087		,"8087"},
  { FPU_TYPE_80287		,"80287"},
  { FPU_TYPE_80387		,"80387"},
  { FPU_TYPE_BUILT_IN		,"built-in"}, 
}
;

typedef struct
{
  u8 family;
  u8 from_model;
  u8 to_model;
  u8 vendor_id;
  u16 cpu_type_id;
} cpu_record;


#define NONE -1
#define LAST -1

typedef struct
{
  u8 from_model;
  u8 to_model;
  u8 vendor_id;
  u16 cpu_type_id;
} cpu_family_record;

cpu_family_record family0[] =
{
  { 0,LAST,VENDOR_UNKNOWN	,CPU_TYPE_UNKNOWN_8086 },
};

cpu_family_record family1[] =
{
  { 0,LAST,VENDOR_UNKNOWN	,CPU_TYPE_UNKNOWN_80186 },
};

cpu_family_record family2[] =
{
  { 0,LAST,VENDOR_UNKNOWN	,CPU_TYPE_UNKNOWN_80286 },
};

cpu_family_record family3[] =
{
  { 0,LAST,VENDOR_UNKNOWN	,CPU_TYPE_UNKNOWN_80386 },
};

cpu_family_record family4[] =
{
  { 2,   2,VENDOR_Intel		,CPU_TYPE_INTEL_486SX },
  { 3,   3,VENDOR_Intel		,CPU_TYPE_INTEL_486DX2 },
  { 4,   4,VENDOR_Intel		,CPU_TYPE_INTEL_486SL },
  { 5,   5,VENDOR_Intel		,CPU_TYPE_INTEL_486SX2 },
  { 7,   7,VENDOR_Intel		,CPU_TYPE_INTEL_486DX2 },
  { 8,   9,VENDOR_Intel		,CPU_TYPE_INTEL_486DX4 },
  { 0,LAST,VENDOR_Intel		,CPU_TYPE_INTEL_486 },

  { 3,   7,VENDOR_AMD		,CPU_TYPE_AMD_486DX2 },
  { 8,   9,VENDOR_AMD		,CPU_TYPE_AMD_486DX4 },
  {0xE,0xF,VENDOR_AMD		,CPU_TYPE_AMD_5x86 },

  { 0,LAST,VENDOR_AMD		,CPU_TYPE_AMD_486 },

  { 4,   4,VENDOR_Cyrix		,CPU_TYPE_Cyrix_MediaGX },
  { 0,LAST,VENDOR_Cyrix		,CPU_TYPE_Cyrix_5x86 },

  { 1,   1,VENDOR_UMC		,CPU_TYPE_UMC_U5D },
  { 2,   2,VENDOR_UMC		,CPU_TYPE_UMC_U5S },

  { 0,LAST,VENDOR_UNKNOWN	,CPU_TYPE_UNKNOWN_80486 },
};

cpu_family_record family5[] =
{
  { 0,   3,VENDOR_AMD		,CPU_TYPE_AMD_K5 },
  { 7,   7,VENDOR_AMD		,CPU_TYPE_AMD_K6 },
  { 8,   8,VENDOR_AMD		,CPU_TYPE_AMD_K6_2 },
  { 9,   9,VENDOR_AMD		,CPU_TYPE_AMD_K6_3 },
  { 0,LAST,VENDOR_AMD		,CPU_TYPE_UNKNOWN_AMD },

  { 0,   8,VENDOR_Intel		,CPU_TYPE_INTEL_Pentium },
  { 0,LAST,VENDOR_Intel		,CPU_TYPE_UNKNOWN_INTEL_Pentium },

  { 4,   4,VENDOR_Cyrix		,CPU_TYPE_Cyrix_MediaGXm },
  { 0,LAST,VENDOR_Cyrix		,CPU_TYPE_Cyrix_6x86 },

  { 4,   4,VENDOR_Centaur	,CPU_TYPE_Centaur_C6 },
  { 8,   8,VENDOR_Centaur	,CPU_TYPE_Centaur_C2 },
  { 9,   9,VENDOR_Centaur	,CPU_TYPE_Centaur_C3 },

  { 0,   2,VENDOR_RiseTechnology,CPU_TYPE_Rise_mP6 },

  { 0,LAST,VENDOR_UNKNOWN	,CPU_TYPE_UNKNOWN_80586 },
};

cpu_family_record family6[] =
{
  { 0,   2,VENDOR_Intel		,CPU_TYPE_INTEL_Pentium_Pro },
  { 3,   6,VENDOR_Intel		,CPU_TYPE_INTEL_Pentium_II },
  { 7,   9,VENDOR_Intel		,CPU_TYPE_INTEL_Pentium_III },
  { 0,LAST,VENDOR_Intel		,CPU_TYPE_UNKNOWN_INTEL_P6 },

  { 0,LAST,VENDOR_AMD		,CPU_TYPE_AMD_Athlon },

  { 0,   0,VENDOR_Cyrix		,CPU_TYPE_Cyrix_6x86MX },

  { 0,LAST,VENDOR_UNKNOWN	,CPU_TYPE_UNKNOWN_80686 },
};

typedef struct
{
  cpu_family_record* family;
  int size_of_family;
} families_type;

families_type CPU_families[] =
{
  { family0	,sizeof(family0) / sizeof(cpu_family_record) },
  { family1	,sizeof(family1) / sizeof(cpu_family_record) },
  { family2	,sizeof(family2) / sizeof(cpu_family_record) },
  { family3	,sizeof(family3) / sizeof(cpu_family_record) },
  { family4	,sizeof(family4) / sizeof(cpu_family_record) },
  { family5	,sizeof(family5) / sizeof(cpu_family_record) },
  { family6	,sizeof(family6) / sizeof(cpu_family_record) },
};

typedef struct
{
  u16 cpu_type_id;
  u8 model;
  u8 stepping;
  u16 cpu_sub_type_id;
} cpu_sub_record;

cpu_sub_record CPU_sub_records[] =
{
  { CPU_TYPE_AMD_486DX2	,  3,NONE,CPU_SUB_TYPE_Standart	},
  { CPU_TYPE_AMD_486DX2	,  7,NONE,CPU_SUB_TYPE_WriteBackEnhanced },
  { CPU_TYPE_AMD_486DX4	,  8,NONE,CPU_SUB_TYPE_Standart	},
  { CPU_TYPE_AMD_486DX4	,  9,NONE,CPU_SUB_TYPE_WriteBackEnhanced },
  { CPU_TYPE_AMD_5x86	,0xE,NONE,CPU_SUB_TYPE_Standart	},
  { CPU_TYPE_AMD_5x86	,0xF,NONE,CPU_SUB_TYPE_WriteBackEnhanced },

  { CPU_TYPE_INTEL_Pentium	,   0,NONE,CPU_SUB_TYPE_A_step },
  { CPU_TYPE_INTEL_Pentium	,   1,NONE,CPU_SUB_TYPE_Standart },
  { CPU_TYPE_INTEL_Pentium	,   2,NONE,CPU_SUB_TYPE_Standart },
  { CPU_TYPE_INTEL_Pentium	,   3,NONE,CPU_SUB_TYPE_Overdrive },
  { CPU_TYPE_INTEL_Pentium	,   4,NONE,CPU_SUB_TYPE_MMX },
  { CPU_TYPE_INTEL_Pentium	,   7,NONE,CPU_SUB_TYPE_Standart },
  { CPU_TYPE_INTEL_Pentium	,   8,NONE,CPU_SUB_TYPE_MMX },

  { CPU_TYPE_AMD_K5		,   0,NONE,CPU_SUB_TYPE_Standart },
  { CPU_TYPE_AMD_K5		,   1,NONE,CPU_SUB_TYPE_Standart },
  { CPU_TYPE_AMD_K5		,   2,NONE,CPU_SUB_TYPE_Standart },
  { CPU_TYPE_AMD_K5		,   3,NONE,CPU_SUB_TYPE_Standart },
 
  { CPU_TYPE_INTEL_Pentium_Pro	,   0,NONE,CPU_SUB_TYPE_A_step },
  { CPU_TYPE_INTEL_Pentium_Pro	,   1,NONE,CPU_SUB_TYPE_Standart },

  { CPU_TYPE_INTEL_Pentium_II	,   3,   0,CPU_SUB_TYPE_Standart },
  { CPU_TYPE_INTEL_Pentium_II	,   5,   1,CPU_SUB_TYPE_Celeron },
  { CPU_TYPE_INTEL_Pentium_II	,   5,   2,CPU_SUB_TYPE_Standart },
  { CPU_TYPE_INTEL_Pentium_II	,   5,   3,CPU_SUB_TYPE_Xeon },
  { CPU_TYPE_INTEL_Pentium_II	,   6,   1,CPU_SUB_TYPE_Celeron },
  { CPU_TYPE_INTEL_Pentium_III	,   7,   1,CPU_SUB_TYPE_CeleronII },
  { CPU_TYPE_INTEL_Pentium_III	,   7,   2,CPU_SUB_TYPE_Standart },
  { CPU_TYPE_INTEL_Pentium_III	,   7,   3,CPU_SUB_TYPE_Xeon },
  { CPU_TYPE_INTEL_Pentium_III	,   8,   1,CPU_SUB_TYPE_CeleronII },
  { CPU_TYPE_INTEL_Pentium_III	,   8,   2,CPU_SUB_TYPE_Standart },
  { CPU_TYPE_INTEL_Pentium_III	,   8,   3,CPU_SUB_TYPE_Xeon },

  { CPU_TYPE_AMD_K6	,   6,NONE,CPU_SUB_TYPE_Standart },
  { CPU_TYPE_AMD_K6	,   7,NONE,CPU_SUB_TYPE_Standart },
  { CPU_TYPE_AMD_K6_2	,   8,NONE,CPU_SUB_TYPE_Standart },
  { CPU_TYPE_AMD_K6_3	,   9,NONE,CPU_SUB_TYPE_Standart },

  { CPU_TYPE_AMD_Athlon	,   1,NONE,CPU_SUB_TYPE_Standart },
  { CPU_TYPE_AMD_Athlon	,   2,NONE,CPU_SUB_TYPE_Standart },
  { CPU_TYPE_AMD_Athlon	,   3,NONE,CPU_SUB_TYPE_Duron },
  { CPU_TYPE_AMD_Athlon	,   4,NONE,CPU_SUB_TYPE_Thinderbird },
};
