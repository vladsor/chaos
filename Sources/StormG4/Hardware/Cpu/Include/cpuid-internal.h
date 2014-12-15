/* Abstract: Function prototypes and structure definitions for CPU
   identification routines. */
/* Author: Vladimir Sorokin. */

/* Copyright 2000-2001 chaos development. */

#ifndef __STORM_IA32_CPUID_INTERNAL_H__
#define __STORM_IA32_CPUID_INTERNAL_H__

typedef struct
{
    uint8_t vendor_id;
  
    const char *vendor_string;
  
} vendor_record_t;

typedef struct
{
    uint16_t type_id;
    char *name;
} cpu_type_record_t;

typedef struct
{
    uint16_t sub_type_id;
    char* name;
} cpu_sub_type_record_t;

typedef struct
{
    uint8_t type_id;
    char* name;
} fpu_type_record_t;

typedef struct
{
    uint8_t family;
    uint8_t from_model;
    uint8_t to_model;
    uint8_t vendor_id;
    uint16_t cpu_type_id;
} cpu_record_t;


#define NONE -1
#define LAST -1

typedef struct
{
    uint8_t from_model;
    uint8_t to_model;
    uint8_t vendor_id;
    uint16_t cpu_type_id;
    
} cpu_family_record;

typedef struct
{
  cpu_family_record *family;
  int size_of_family;
} family_t;

typedef struct
{
    uint16_t cpu_type_id;
    uint8_t model;
    uint8_t stepping;
    uint16_t cpu_sub_type_id;
} cpu_sub_record_t;

#endif /* __STORM_IA32_CPUID_INTERNAL_H__ */
