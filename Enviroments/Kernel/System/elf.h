/* $chaos: elf.h,v 1.14 2002/10/15 16:11:14 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file        elf.h 
 * @brief       Structures and functions used for decoding ELF images.
 *
 * More information about the ELF format can be found in the ELF
 * specification, as published by the Tool Interface Standards (TIS):
 * http://x86.ddj.com/ftp/manuals/tools/elf.pdf 
 */

#ifndef __STORM_IA32_ELF_H__
#define __STORM_IA32_ELF_H__

/* Type definitions. */

/**
 * @brief               A function provided to the kernel modules. 
 */
typedef struct
{
    /**
     * @brief           Name of function.
     */
    const char *name;

    /**
     * @brief           Pointer to function.
     */
    p_function_t function;
    
} function_info_t;

/* Enumerations. */

/**
 * @brief               ELF classes. 
 */
enum elf_class_t
{
    /**
     * @brief           No class. Bad ELF. 
     */
    ELF_CLASS_NONE,
    
    /**
     * @brief           32-bit ELF. 
     */
    ELF_CLASS_32BIT,

    /**
     * @brief           64-bit ELF. 
     */
    ELF_CLASS_64BIT,
};

/**
 * @brief               ELF types. 
 */
enum elf_type_t
{
    /**
     * @brief           No type. 
     */
    ELF_TYPE_NONE, 
  
    /**
     * @brief           Relocatable ELF (i.e. position independant code, or PIC) 
     */
    ELF_TYPE_RELOCATABLE,
  
    /**
     * @brief           Executable ELF. 
     */
    ELF_TYPE_EXECUTABLE,

    /**
     * @brief           Shared object ELF. 
     */
    ELF_TYPE_DYNAMIC,
  
    /** 
     * @brief           Core dump. 
     */
    ELF_TYPE_CORE,
};

/**
 * @brief               Machine types. 
 */
enum elf_machine_t
{
    /**
     * @brief           No machne. 
     */
    ELF_MACHINE_NONE = 0,

    /**
     * @brief           AT&T WE 32100 
     */
    ELF_MACHINE_M32 = 1,

    /**
     * @brief           Sun Sparc. 
     */
    ELF_MACHINE_SPARC = 2,

    /**
     * @brief           Intel IA32. 
     */
    ELF_MACHINE_386 = 3,

    /**
     * @brief           Motorola 68000. 
     */
    ELF_MACHINE_68000 = 4,
  
    /**
     * @brief           Motorola 88000. 
     */
    ELF_MACHINE_88000 = 5,

    /**
     * @brief           Intel 80860. 
     */
    ELF_MACHINE_860 = 7,

    /**
     * @brief           MIPS RS3000. 
     */
    ELF_MACHINE_RS3000 = 8,

    /**
     * @brief           MIPS RS4000. 
     */
    ELF_MACHINE_RS4000 = 10,

    /**
     * @brief           HPPA 
     */
    ELF_MACHINE_PARISC = 15,

    /**
     * @brief           Sun's "v8plus" 
     */
    ELF_MACHINE_SPARC32PLUS = 18,

    /**
     * @brief           PowerPC 
     */
    ELF_MACHINE_PPC = 20,

    /**
     * @brief           PowerPC64 
     */
    ELF_MACHINE_PPC64 = 21,

    /**
     * @brief           IBM S/390 
     */
    ELF_MACHINE_S390 = 22,

    /**
     * @brief           ARM
     */
    ELF_MACHINE_ARM = 40,
  
    /**
     * @brief           SuperH 
     */
    ELF_MACHINE_SH = 42,

    /**
     * @brief           SPARC v9 64-bit 
     */
    ELF_MACHINE_SPARCV9 = 43,

    /**
     * @brief           HP/Intel IA-64 
     */
    ELF_MACHINE_IA_64 = 50,

    /**
     * @brief           AMD x86-64 
     */
    ELF_MACHINE_X8664 = 62,

    /**
     * @brief           Axis Communications 32-bit embedded processor 
     */
    ELF_MACHINE_CRIS = 76,

    /**
     * @brief           This is the old value for S/390 architecture
     */
    ELF_MACHINE_S390_OLD = 0xA390,
};

/**
 * @brief               ELF versions. 
 */
enum elf_version_t
{
    /**
     * @brief           Invalid version. 
     */
    ELF_VERSION_NONE,

    /**
     * @brief           Current version. 
     */
    ELF_VERSION_CURRENT,
};

/**
 * @brief               Endianess. 
 */
enum elf_endian_t
{
    /**
     * @brief           No endian (invalid). 
     */
    ELF_ENDIAN_NONE,

    /**
     * @brief           Little endian (LSB). 
     */
    ELF_ENDIAN_LITTLE,

    /**
     * @brief           Big endian (MSB). 
     */
    ELF_ENDIAN_BIG,
};

/**
 * @brief               Section types. 
 */
enum elf_section_type_t
{
    /**
     * @brief           This section is inactive. 
     */
    ELF_SECTION_TYPE_NULL,

    /**
     * @brief           This section is used for something defined by the 
     *                  program itself. 
     */
    ELF_SECTION_TYPE_UNDEFINED,

    /**
     * @brief           This section holds the symbol table. May only exist
     *                  once in the file. 
     */
    ELF_SECTION_TYPE_SYMBOL_TABLE,

    /**
     * @brief           This section holds the string table. May only exist
     *                  once in the file. 
     */
    ELF_SECTION_TYPE_STRING_TABLE,

    /**
     * @brief           This section holds relocation entries with explicit 
     *                  addends (?). 
     */
    ELF_SECTION_TYPE_RELOCATION_ADDENDS,

    /**
     * @brief           This section holds a symbol hash table. 
     */
    ELF_SECTION_TYPE_SYMBOL_HASH_TABLE,
  
    /**
     * @brief           This section holds information for dynamic linking. 
     */
    ELF_SECTION_TYPE_DYNAMIC,

    /**
     * @brief           This section holds information that marks the file in 
     *                  some way. 
     */
    ELF_SECTION_TYPE_NOTE,

    /**
     * @brief           This section does not take up any space in the ELF file.
     *                  Most often used for BSS sections. 
     */
    ELF_SECTION_TYPE_NO_SPACE,

    /**
     * @brief           This section holds relocation entries without explicit
     *                  addends. 
     */
    ELF_SECTION_TYPE_RELOCATION,
  
    /**
     * @brief           This section type is reserved by has unspecified 
     *                  semantics. Programs that contain a section of this type
     *                  does not conform to the ABI. 
     */
    ELF_SECTION_TYPE_SHARED_LIBRARY,
    
    /**
     * @brief           This section holds a symbol table used for dynamic
     *                  linking. 
     */
    ELF_SECTION_TYPE_DYNAMIC_SYMBOL_TABLE,
};

/**
 * @brief               Program types. 
 */
enum elf_program_type_t
{
    /**
     * @brief           A NULL program header means that this segment is unused. 
     */
    ELF_PROGRAM_TYPE_NULL,

    /**
     * @brief           A loadable segment. 
     */
    ELF_PROGRAM_TYPE_LOAD,

    /**
     * @brief           A segment containing dynamic linking information. 
     */
    ELF_PROGRAM_TYPE_DYNAMIC,

    /**
     * @brief           A segment containing a NULL-terminated path to the 
     *                  interpreter needed to run this segment. 
     */
    ELF_PROGRAM_TYPE_INTERPRETER,

    /**
     * @brief           A segment containig auxiliary information. 
     */
    ELF_PROGRAM_TYPE_NOTE,

    /**
     * @brief           A segment with "unspecified semantics". 
     */
    ELF_PROGRAM_TYPE_SHARED_LIBRARY,

    /**
     * @brief           A segment containing the program header. 
     */
    ELF_PROGRAM_TYPE_PROGRAM_HEADER,
};

/**
 * @brief               Program flags. 
 */
enum elf_program_flag_t
{
    /**
     * @brief           Allow execute segment
     */
    PF_EXECUTE = BIT_VALUE (0),
    
    /**
     * @brief           Allow write segment
     */
    PF_WRITE = BIT_VALUE (1),
    
    /**
     * @brief           Allow read segment
     */
    PF_READ = BIT_VALUE (2),

//    PF_MASKPROC 0xf0000000 Unspecified
};

/**
 * @brief               Section flags. 
 */
enum elf_section_flag_t
{
    /**
     * @brief           This section contains data that should be writable 
     *                  during process execution. 
     */
    ELF_SECTION_FLAG_WRITE = BIT_VALUE (0),

    /**
     * @brief           This section occupies memory during process execution. 
     */
    ELF_SECTION_FLAG_ALLOCATE = BIT_VALUE (1),

    /**
     * @brief           This section contains code that should be executable. 
     */
    ELF_SECTION_FLAG_EXECUTE = BIT_VALUE (2),
};

/**
 * @brief               Symbol bindings. 
 */
enum elf_symbol_binding_t
{
    /**
     * @brief           A local symbol. 
     */
    ELF_SYMBOL_BINDING_LOCAL,

    /**
     * @brief           A global symbol. 
     */
    ELF_SYMBOL_BINDING_GLOBAL,
    
    /**
     * @brief           A "weak" symbol. Similar to a global symbol but with
     *                  less precedence. 
     */
    ELF_SYMBOL_BINDING_WEAK
};

/**
 * @brief               Symbol types. 
 */
enum elf_symbol_type_t
{
    /**
     * @brief           Unspecified symbol type. 
     */
    ELF_SYMBOL_TYPE_NONE,

    /**
     * @brief           A data object. (variable, array, etc). 
     */
    ELF_SYMBOL_TYPE_OBJECT,

    /**
     * @brief           A function or other executable code. 
     */
    ELF_SYMBOL_TYPE_FUNCTION,

    /**
     * @brief           A section symbol (used for relocation). 
     */
    ELF_SYMBOL_TYPE_SECTION,

    /**
     * @brief           A file symbol. 
     */
    ELF_SYMBOL_TYPE_FILE
};
/*
A This means the addend used to compute the value of the relocatable field.

B This means the base address at which a shared object has been loaded into memory
during execution. Generally, a shared object file is built with a 0 base virtual address,
but the execution address will be different.

G This means the offset into the global offset table at which the address of the
relocation entry's symbol will reside during execution. See "Global Offset Table''
below for more information.

GOT This means the address of the global offset table. See "Global Offset Table'' below
for more information.

L This means the place (section offset or address) of the procedure linkage table entry
for a symbol. A procedure linkage table entry redirects a function call to the proper
destination. The link editor builds the initial procedure linkage table, and the
dynamic linker modifies the entries during execution. See "Procedure Linkage
Table'' below for more information.

P This means the place (section offset or address) of the storage unit being relocated
(computed using r_offset.

S This means the value of the symbol whose index resides in the relocation entry.
*/

/**
 * @brief               Relocation types. 
 */
enum elf_relocation_type_t
{
    /**
     * @brief           No relocation needs to be performed. 
     */
    ELF_RELOCATION_NONE = 0,

    // S+A
    ELF_RELOCATION_386_32 = 1,
    
    // S+A-P
    ELF_RELOCATION_386_PC32 = 2,

    // G + A           
    ELF_RELOCATION_GOT_32 = 3,
    
    // L + A - P
    ELF_RELOCATION_PLT_32 = 4,
    
    // none
    ELF_RELOCATION_COPY = 5,
    
    /**
     * This relocation type is used to set a global offset table entry to the address of the 
     * specified symbol. The special relocation type allows one to determine the 
     * correspondence between symbols and global offset table entries.     
     */
     // S
    ELF_RELOCATION_GLOB_DAT = 6,
    
    /**
     * The link editor creates this relocation type for dynamic linking. Its offset member 
     * gives the location of a procedure linkage table entry. The dynamic linker modifies the 
     * procedure linkage table entry to transfer control to the designated symbol's address 
     * [see "Procedure Linkage Table'' below].    
     */
    // S  
    ELF_RELOCATION_JMP_SLOT = 7,

    /* The contents of the relocated place plus the address of the
       symbol. */
    
    /* The contents of the relocated place plus the base of the image
       in memory. */
    /**
     * The link editor creates this relocation type for dynamic linking. Its offset member
     * gives a location within a shared object that contains a value representing a relative
     * address. The dynamic linker computes the corresponding virtual address by adding the
     * virtual address at which the shared object was loaded to the relative address. 
     * Relocation entries for this type must specify 0 for the symbol table index.
     */
    // B + A 
    ELF_RELOCATION_RELATIVE = 8,
    
    /**
     * This relocation type computes the difference between a symbol's value and the address
     * of the global offset table. It additionally instructs the link editor to build the
     * global offset table.    
     */
    // S + A - GOT 
    ELF_RELOCATION_GOTOFF = 9,
    
    /**
     * This relocation type resembles ELF_RELATION_386_PC32, except it uses the address of the global
     * offset table in its calculation. The symbol referenced in this relocation normally
     * is _GLOBAL_OFFSET_TABLE_, which additionally instructs the link editor to build the
     * global offset table.    
     */
    // GOT + A - P 
    ELF_RELOCATION_GOTPC = 10,
    /*    ELF_RELOCATION_ = 32, */
};

/**
 * @brief               An ELF (Executable and linkable format) header. 
 */
typedef struct 
{
    /**
     * @brief           Must be 0x7F, 'E, 'L', 'F' in this order. 
     */
    uint8_t identification[4]; 

    /**
     * @brief           The class of this executable.
     *
     * @sa elf_class_t. 
     */
    uint8_t class;

    /**
     * @brief           The endianess of the data in this file.
     *
     * @sa elf_endian_t.
     */
    uint8_t endian;

    /**
     * @brief           Current version is ELF_VERSION_CURRENT. 
     */
    uint8_t version;

    /**
     * @brief           Should be zero.
     *
     * FreeBSD uses those to put 'FreeBSD' in the ELF header. We could
     * do the same...
     */
    uint8_t pad[9];

    /**
     * @brief           The type of ELF.
     *
     * @sa elf_type_t. 
     */
    uint16_t type;   

    /**
     * @brief           The machine type this ELF is designed to run on.
     *
     * @sa elf_machine_t. 
     */
    uint16_t machine;

    /**
     * @brief           Current version is still ELF_VERSION_CURRENT.
     *
     * (Don't ask me why they put the version ID in two places...) 
     */
    uint32_t version2;

    /**
     * @brief           The location of the program entry point. 
     */
    uint32_t entry_point;

    /**
     * @brief           Offset of program header table. 
     */
    uint32_t program_header_offset;

    /**
     * @brief           Offset of section header table. 
     */
    uint32_t section_header_offset;

    /**
     * @brief           Processor-specific flags associated with the file.
     */
    uint32_t flags;   

    /**
     * @brief           The size of the ELF header. 
     */
    uint16_t elf_header_size;

    /**
     * @brief           The size of a program header table entry. 
     */
    uint16_t program_header_entry_size;

    /**
     * @brief           The number of program header entries. 
     */
    uint16_t program_header_entries;

    /**
     * @brief           The size of a section header table entry. 
     */
    uint16_t section_header_entry_size;

    /**
     * @brief           The number of section header entries. 
     */
    uint16_t section_header_entries;

    /**
     * @brief           The section header table index of the section name
     *                  string table. 
     */
    uint16_t section_string_index;
    
} elf_header_t PACKED;

/**
 * @brief               An ELF section header entry. 
 */
typedef struct
{
    /**
     * @brief           The name of the section (index of the string table). 
     */
    uint32_t name;
    
    uint32_t type;
    
    /**
     * @brief           The flags of section.
     *
     * @sa elf_section_flag_t
     */
    uint32_t flags;     

    /**
     * @brief           The start of the section in memory. 
     */
    uint32_t address;
  
    /**
     * @brief           The start of the section in the file. 
     */
    uint32_t offset;

    /**
     * @brief           The size of the section. 
     */
    uint32_t size;
    uint32_t link;     
    uint32_t info;
    uint32_t address_align;

    /**
     * @brief           The size of each section entry. 
     */
    uint32_t entry_size;
    
} elf_section_header_t PACKED;

/**
 * @brief               An ELF program header entry. 
 */
typedef struct
{    
    /**
     * @brief           The type of this program header.
     *
     * @sa elf_program_type_t. 
     */
    uint32_t type;
    
    /**
     * @brief           The offset of this segment, starting from the beginning
     *                  of the ELF image. 
     */
    uint32_t offset;

    /**
     * @brief           The virtual address of this segment in memory.
     */
    uint32_t virtual_address;
    
    /**
     * @brief           The physical address of this segment in memory.
     */
    uint32_t physical_address;

    /**
     * @brief           Size of this segment in the file. 
     */
    uint32_t file_size;

    /**
     * @brief           Size of this segment in memory. 
     */
    uint32_t memory_size;

    /**
     * @brief           Flags for this segment.
     *
     * @sa elf_program_flag_t. 
     */
    uint32_t flags;

    /** 
     * @brief           The number of bytes to which this segment is aligned in
     *                  memory and in file.
     *
     * Values of 0 and 1 means no specific alignment. 
     */
    uint32_t align;
    
} elf_program_header_t PACKED;

/** 
 * @brief               A symbol table entry. 
 */
typedef struct
{
    /**
     * @brief           An index into the symbol string table, containing the
     *                  name of this symbol. 
     */
    uint32_t name;

    /**
     * @brief           The value of this symbol. 
     */
    uint32_t value;

    /**
     * @brief           The size of this symbol. 0 if no size or size unknown. 
     */
    uint32_t size;

    /**
     * @brief           The symbol's type.
     *
     * @sa elf_symbol_type_t.
     */
    uint8_t type : 4;
    
    /**
     * @brief           The binding attributes. 
     *
     * @sa elf_symbol_binding_t.
     */
    uint8_t bind : 4;

    /**
     * @brief           This field is not used. Only for alignment. 
     */
    uint8_t other;

    /**
     * @brief           The index of the section header that this symbol is
     *                  defined in relation to. 
     */
    uint16_t section_header;
    
} elf_symbol_t PACKED;

/** 
 * @brief               A relocation table entry.
 */
typedef struct
{
    /**
     * @brief           The offset in the file that is affected by this
     *                  relocation. 
     */
    uint32_t offset;

    /**
     * @brief           The type of the symbol. 
     *
     * @sa elf_relocation_type_t
     */
    uint32_t symbol_type : 8;

    /**
     * @brief           The index into the symbol table of this relocation.
     */
    uint32_t symbol_index : 24;
    
} elf_relocation_t PACKED;

/**
 * @brief Our parsed ELF, with some important sections picked out.
 */
typedef struct
{
    /**
     * @brief The ELF header itself. 
     */
    elf_header_t *elf_header;

    /**
     * @brief The section containing strings, used for dynamic linking. 
     */
    elf_section_header_t *string_header;

    /**
     * @brief The section containing the symbol table, used for
     * dynamic linking. 
     */
    elf_section_header_t *symbol_header;

    /**
     * @brief The section containing where in the ELF image the
     * unresolved symbols are so we can resolve them.
     */
    elf_section_header_t *relocation_header;

    /**
     * @brief The image, freshly allocated.
     */
    void *image;
    
} elf_parsed_t;

typedef elf_parsed_t * p_elf_parsed_t;


typedef struct
{
    /**
     * @brief The ELF header itself. 
     */
    elf_header_t *elf_header;

} elf_parsed_program_t;

typedef elf_parsed_program_t * p_elf_parsed_program_t;

/**
 * @brief               Make sure the given ELF is identified properly. 
 * @param elf_header    Pointer to the ELF header.
 */
extern enum storm_elf_t elf_identify (elf_header_t *elf_header);

/**
 * @brief               Parse the given ELF header. 
 * @param elf_header    Pointer to the ELF header. 
 * @param elf_parsed    Pointer to the parsed ELF structure.
 * @return              STORM_RETURN_SUCCESS if successful.
 */
extern return_t elf_parse (elf_header_t *elf_header, elf_parsed_t *elf_parsed);

/**
 * @brief               Resolve unresolved symbols in the given symbol table. 
 * @param elf_parsed    Pointer to the parsed ELF structure.
 * @param function      The list of functions to resolve.
 * @return              STORM_RETURN_SUCCESS if successful.
 */
extern return_t elf_resolve (elf_parsed_t *elf_parsed,
    function_info_t *function);

/** 
 * @brief               Relocate relocatable symbols. 
 * @param elf_parsed    Pointer to the parsed ELF structure.
 * @return              STORM_RETURN_SUCCESSFUL if successful.
 */
extern return_t elf_relocate (elf_parsed_t *elf_parsed);

/**
 * @brief               Find the given symbol by index. 
 * @param elf_parsed    Pointer to the parsed ELF structure.
 * @param index         The index of the symbol to find.
 * @param address       Pointer to an address where we store the result.
 * @return              STORM_RETURN_SUCCESS if successful.
 */
extern return_t elf_symbol_find_by_index (elf_parsed_t *elf_parsed,
    unsigned int index, address_t *address);

/** 
 * @brief               Find the given symbol by name. 
 * @param elf_parsed    Pointer to the parsed ELF structure.
 * @param name          Pointer to the name of the smbol to find.
 * @param address       Pointer to an address where we store the result.
 * @return              STORM_RETURN_SUCCESS if successful.
 */
extern return_t elf_symbol_find_by_name (elf_parsed_t *elf_parsed,
    const char *name, address_t *address);

/** 
 * @brief Load an ELF.
 * @param elf_parsed    Pointer to the parsed ELF structure.
 * @return              STORM_RETURN_SUCCESS if successful.
 *
 * Allocate memory for it, and copy the data from the different
 * sections there. 
 */
extern return_t elf_load_module (elf_parsed_t *elf_parsed);

extern return_t elf_parse_program (elf_header_t *elf_header, 
    elf_parsed_program_t *elf_parsed);

extern return_t elf_load_program (elf_parsed_program_t *elf_parsed,
    virtual_memory_t *memory);

extern return_t elf_get_entry_point (elf_parsed_program_t *elf_parsed, 
    address_t *address);

#endif /* !__STORM_IA32_ELF_H__ */

