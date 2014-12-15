/* Filename: cpuid3.c version 0.5 */
/* Copyright 1994, 1995, 1996, 1997 by Intel Corp.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpuid.h"

#define QUARZ_FREQ 1193180L
#define CALIBRATE 1000000L

#define REF_TICK                100                   // # of timer interrupts
#define TICK_SEC                1098510               // Tick value for 1 sec
#define TIMER_TICK_LOW          0x46C                 // BIOS date are 40:6ch
#define TIMER_TICK_HIGH         0x46E                 // BIOS date are 40:6eh

extern char cpu_type;
extern char fpu_type;
extern char cpuid_flag;
extern char vendor_id[12];
extern char cpu_name_string[48];
extern char proc_cache_l1[16];
extern char proc_cache_l2[16];

extern long cpu_signature;
extern long ext_features;
extern long features_ecx;
extern long features_edx;
extern long features_ebx;

extern u32 timer_count[2];
extern u32 timer_scale;

extern "C" void get_fpu_type(void);
extern "C" int CPU_is_8086(void);
extern "C" int CPU_is_80286(void);
extern "C" int CPU_is_80386(void);
extern "C" int CPU_is_80486(void);
extern "C" int get_CPU_ID(void);
extern "C" void read_tsc(void);

void print(void);

char* CPU_name;
char* CPU_model = "   ";
char vendor_idc;
char* table = "0123456789ABCDEF";
char* default_string = "Some known processor(no name available)";

char hex_lower(char val);

void cpu_id_init(void);

int proccess_vendor(char vendor[12],char* vendor_id);
int proccess_features(long *features,char** message);
int response_cpu(char family,char signature,char vendor_id);
int get_cpu_name(char** name);
int proccess_capabilities(long features,long ext_features);

char* get_all_capabilities(void);

void print(void)
{
  char* str;

  if(proccess_vendor(vendor_id,&vendor_idc))
    printf("known vendor: %s\n",vendor_id);

  response_cpu(cpu_type,cpu_signature,vendor_idc);
  get_cpu_name(&CPU_name);
  printf("CPU: %s\n",CPU_name);
  printf("ext CPU: %s\n",cpu_name_string);
  printf("model %c,stepping %c\n",hex_lower(CPU.model),hex_lower(CPU.stepping));
  proccess_capabilities(features_edx,ext_features);
  str = get_all_capabilities();
  printf("This processor support:\n%s",str);

  read_tsc();

  printf("%lu:%lu c:%lu\n",timer_count[1],timer_count[0],timer_scale);
  printf("%lu MHz",(((t imer_count[0]/1000000)*182)/timer_scale)/10 );
  printf("\n");
}
char hex_lower(char val)
{
  return table[val & 0xF];
}

int proccess_vendor(char vendor[12],char* vendor_id)
{
  int num = sizeof(Vendor_Infos)/sizeof(Vendor_Infos[0]);
  int i;
  for(i=0;i<num;i++)
  {
    if(!strncmp(Vendor_Infos[i].vendor_name,vendor,12)){
      CPU.vendor_id = Vendor_Infos[i].vendor_id;
      *vendor_id = Vendor_Infos[i].vendor_id;
      return TRUE;
    }
  }
  *vendor_id = Vendor_Infos[0].vendor_id;
  return FALSE;
}
int response_cpu(char family,char signature,char vendor_id)
{
  int num = sizeof(CPU_Infos)/sizeof(cpu_info);
  int i=0;
  for(i=0;i<num;i++)
  {
    if((CPU_Infos[i].family == family) &&
       (CPU_Infos[i].model > ((signature>>4)& 0xf)) &&
       ((CPU_Infos[i].vendor_id == vendor_id) ||
       (vendor_id == VENDOR_UNKNOWN)))
    {
	 CPU.type_id = CPU_Infos[i].type_id;
	 CPU.family = family;
	 CPU.model = (signature>>4)&0xf;
	 CPU.stepping = signature&0xf;
	 return 0;
    }
  }

  CPU.type_id = UNKNOWN;
  CPU.family = 0;
  CPU.model = 0;
  CPU.stepping = 0;

  return 1;
}
int get_cpu_name(char** name)
{
  int num = sizeof(CPU_Names)/sizeof(CPU_Names[0]);
  int i;
  for(i=0;i<num;i++)
  {
    if(CPU.type_id == CPU_Names[i].type_id)
    {
      *name = CPU_Names[i].name;
      return 0;
    }
  }
  *name = default_string;
  return 1;
}

void add_feature(CPUCAPS cap,u32 value)
{
  CPU.features[cap] = value;
}

u32 get_feature(CPUCAPS cap)
{
  return ((CPU.features[cap]));
}

int proccess_capabilities(long features,long ext_features)
{
    // Feature Bit Test Capabilities

    add_feature(HAS_FPU  ,	(features >>  0) & 1);	// bit  0 = FPU
    add_feature(HAS_VME  ,	(features >>  1) & 1);	// bit  1 = VME
    add_feature(HAS_DEBUG,	(features >>  2) & 1);	// bit  2 = Debugger extensions
    add_feature(HAS_PSE  ,	(features >>  3) & 1);	// bit  3 = Page Size Extensions
    add_feature(HAS_TSC  ,	(features >>  4) & 1);	// bit  4 = Time Stamp Counter
    add_feature(HAS_MSR  ,	(features >>  5) & 1);	// bit  5 = Model Specific Registers
    add_feature(HAS_PAE  ,	(features >>  6) & 1);	// bit  6 = PAE
    add_feature(HAS_MCE  ,	(features >>  7) & 1); 	// bit  7 = Machine Check Extensions
    add_feature(HAS_CMPXCHG8,	(features >>  8) & 1);	// bit  8 = CMPXCHG8 instruction
    add_feature(HAS_APIC ,	(features >>  9) & 1);	// bit  9 = APIC
    add_feature(HAS_SYSENTER,	(features >> 11) & 1);	// bit 11 = SYSENTER instruction
    add_feature(HAS_MTRR,	(features >> 12) & 1);	// bit 12 = Memory Type Range Registers
    add_feature(HAS_GPE,	(features >> 13) & 1);	// bit 13 = Global Paging Extensions
    add_feature(HAS_MCA,	(features >> 14) & 1);	// bit 14 = Machine Check Architecture
    add_feature(HAS_CMOV,	(features >> 15) & 1);	// bit 15 = CMOV instruction
    add_feature(HAS_PAT,	(features >> 16) & 1);	// bit 16 = Page Attribue Table
    add_feature(HAS_PSE36,	(features >> 17) & 1);	// bit 17 = PSE36 (Page Size Extensions)
    add_feature(HAS_MMX,	(features >> 23) & 1);	// bit 23 = MMX
    add_feature(HAS_FXSAVE,	(features >> 24) & 1);  // bit 24 = FXSAVE/FXRSTOR instruction
    add_feature(HAS_SSE,	(features >> 25) & 1);	// bit 25 = SSE

    add_feature(HAS_SSE_MMX,(ext_features >> 22) & 1);	// bit 22 (ext) = SSE MMX Extensions
    add_feature(HAS_MMX_EXT,((features >> 25)&1) | ((ext_features >> 22)&1) );
    // bits 25|22(ext) = MMX Extensions

    // AMD extended information
    add_feature(HAS_3DNOW_EXT,(ext_features >> 30) & 1);	// bit 30 (ext) = Extended 3DNow!
    add_feature(HAS_3DNOW,    (ext_features >> 31) & 1);	// bit 31 (ext) = 3DNow!

    // These are CPU-specific, so guard their access
    if (CPU.vendor_id == VENDOR_AMD)
    {
       // K5/K6 supports a restricted range
       add_feature(CPU_L1_DTLB_ASSOC,	(proc_cache_l1[1] >> 24) & 0xff);
       add_feature(CPU_L1_DTLB_ENTRIES,	(proc_cache_l1[1] >> 16) & 0xff);
       add_feature(CPU_L1_ITLB_ASSOC,	(proc_cache_l1[1] >>  8) & 0xff);
       add_feature(CPU_L1_ITLB_ENTRIES,	(proc_cache_l1[1] >>  0) & 0xff);

       add_feature(CPU_L1_DCACHE_SIZE,	(proc_cache_l1[2] >> 24) & 0xff);
       add_feature(CPU_L1_DCACHE_ASSOC,	(proc_cache_l1[2] >> 16) & 0xff);
       add_feature(CPU_L1_DCACHE_LINES,	(proc_cache_l1[2] >>  8) & 0xff);
       add_feature(CPU_L1_DCACHE_LSIZE,	(proc_cache_l1[2] >>  0) & 0xff);

       add_feature(CPU_L1_ICACHE_SIZE,	(proc_cache_l1[3] >> 24) & 0xff);
       add_feature(CPU_L1_ICACHE_ASSOC,	(proc_cache_l1[3] >> 16) & 0xff);
       add_feature(CPU_L1_ICACHE_LINES,	(proc_cache_l1[3] >>  8) & 0xff);
       add_feature(CPU_L1_ICACHE_LSIZE,	(proc_cache_l1[3] >>  0) & 0xff);

       add_feature(CPU_L2_CACHE_SIZE,	(proc_cache_l2[2] >> 16) & 0xffff);
       add_feature(CPU_L2_CACHE_ASSOC,	(proc_cache_l2[2] >> 12) & 0x0f);
       add_feature(CPU_L2_CACHE_LINES,	(proc_cache_l2[2] >>  8) & 0x0f);
       add_feature(CPU_L2_CACHE_LSIZE,	(proc_cache_l2[2] >>  0) & 0xff);

       if (CPU.type_id == AMD_ATHLON)
       {
	  // Athlon supports these additional parameters
	  add_feature(CPU_L1_EDTLB_ASSOC,	(proc_cache_l1[0] >> 24) & 0xff);
	  add_feature(CPU_L1_EDTLB_ENTRIES,	(proc_cache_l1[0] >> 16) & 0xff);
	  add_feature(CPU_L1_EITLB_ASSOC,	(proc_cache_l1[0] >>  8) & 0xff);
	  add_feature(CPU_L1_EITLB_ENTRIES,	(proc_cache_l1[0] >>  0) & 0xff);

	  add_feature(CPU_L2_DTLB_ASSOC,	(proc_cache_l2[0] >> 28) & 0x0f);
	  add_feature(CPU_L2_DTLB_ENTRIES,	(proc_cache_l2[0] >> 16) & 0xfff);
	  add_feature(CPU_L2_UTLB_ASSOC,	(proc_cache_l2[0] >> 12) & 0x0f);
	  add_feature(CPU_L2_UTLB_ENTRIES,	(proc_cache_l2[0] >>  0) & 0xfff);

	  add_feature(CPU_L2_EDTLB_ASSOC,	(proc_cache_l2[1] >> 28) & 0x0f);
	  add_feature(CPU_L2_EDTLB_ENTRIES,	(proc_cache_l2[1] >> 16) & 0xfff);
	  add_feature(CPU_L2_EUTLB_ASSOC,	(proc_cache_l2[1] >> 12) &  0x0f);
	  add_feature(CPU_L2_EUTLB_ENTRIES,	(proc_cache_l2[1] >>  0) & 0xfff);
       }
    }

 return TRUE;
}

char* get_all_capabilities(void)
{
  int num = sizeof(CPU_Caps)/sizeof(CPU_Caps[0]);
  int i;
  static char temp[100];
  temp[0] = 0;
  u32 value;
  for(i=0;i<num;i++)
  {
    value = get_feature(CPU_Caps[i].cap);
    if(value)
    {
      strcat(temp,CPU_Caps[i].info);
      strcat(temp,"\n");
    }
  }
  return temp;
}

void main(void)
{
  cpu_id_init();
}
void cpu_id_init(void)
{
  if(CPU_is_8086())
  {
    printf("is 8086\n");
  }
  else if(CPU_is_80286())
  {
    printf("is 80286\n");
  }
  else if(CPU_is_80386())
  {
    printf("is 80386\n");
  }
  else if(CPU_is_80486())
  {
    printf("is 80486\n");
  }else
  {
    add_feature(HAS_CPUID,TRUE);
    get_CPU_ID();
    print();
  }
  get_fpu_type();
//  print_all_capabilities();
}
