/* $chaos: elf.c,v 1.10 2002/11/21 21:46:55 per Exp $ */
/* Abstract: ELF module, implementing the exec service. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <enviroment.h>
#include <string.h>

#include "../Include/elf.h"

#define DEBUG_MODULE_NAME "Elf"

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

enum storm_elf_t
{
    STORM_ELF_NONE,
    STORM_ELF_UNKNOWN,
    STORM_ELF_MODULE,
    STORM_ELF_PROGRAM,
};

/* Make sure this is a valid ELF for our platform. */
enum storm_elf_t elf_identify (elf_header_t *elf_header)
{
    /* First of all, make sure this is an ELF image... */
    if (!(elf_header->identification[0] == 0x7F &&
          elf_header->identification[1] == 'E' && 
          elf_header->identification[2] == 'L' &&
          elf_header->identification[3] == 'F'))
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, "No ELF header found.\n");
        
        return STORM_ELF_NONE;
    }

    /* ...and a 32-bit one, little-endian, relocatable... */
    if (elf_header->class != ELF_CLASS_32BIT ||
        elf_header->endian != ELF_ENDIAN_LITTLE ||
        elf_header->version != ELF_VERSION_CURRENT ||
        elf_header->machine != ELF_MACHINE_386)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, "Invalid type of ELF detected.\n");
        
        return STORM_ELF_UNKNOWN;
    }

    if (elf_header->type == ELF_TYPE_EXECUTABLE)
    {
        return STORM_ELF_PROGRAM;
    }
    else if (elf_header->type == ELF_TYPE_DYNAMIC)
    {
        return STORM_ELF_MODULE;
    }

    return STORM_ELF_UNKNOWN;
}

/* Parse the given ELF header. */
return_t elf_parse (elf_header_t *elf_header, elf_parsed_t *elf_parsed)
{
    int index;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s::%s (%p, %p)\n",
        __FILE__, __FUNCTION__,
        elf_header, elf_parsed);
    
    /* Make sure the ELF is valid. */
    if (elf_identify (elf_header) != STORM_ELF_MODULE)
    {
        return -1;
    }

    elf_parsed->elf_header = elf_header;

    /* Find the string table and symbol table. */
    for (index = 0; index < elf_header->section_header_entries; index++)
    {
        elf_section_header_t *section_header = 
            (elf_section_header_t *) (((uint32_t) elf_header) + 
            elf_header->section_header_offset + (index * 
                elf_header->section_header_entry_size));
                
        if (section_header->type == ELF_SECTION_TYPE_STRING_TABLE &&
            section_header->flags & ELF_SECTION_FLAG_ALLOCATE)
        {
            elf_parsed->string_header = section_header;
        }
        else if (section_header->type == ELF_SECTION_TYPE_DYNAMIC_SYMBOL_TABLE)
        {
            elf_parsed->symbol_header = section_header;
        }
        else if (section_header->type == ELF_SECTION_TYPE_RELOCATION)
        {
            elf_parsed->relocation_header = section_header;
        }
    }

    /* If we don't have a string table and symbol table, we won't be
       able to link this module into the kernel. */
    if (elf_parsed->string_header == NULL ||
        elf_parsed->symbol_header == NULL)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "Elf image don't have a string table and symbol table\n");
	    
        return STORM_RETURN_MODULE_INVALID;
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s::%s String table: %p, Symbol table: %p.\n",
        __FILE__, __FUNCTION__, 
        elf_parsed->string_header, elf_parsed->symbol_header);

    return STORM_RETURN_SUCCESS;
}

/* Resolve unresolved symbols in the given symbol table. */
return_t elf_resolve (elf_parsed_t *elf_parsed, function_info_t *function)
{
    int symbol_index;
    elf_symbol_t *symbol;
    elf_section_header_t *symbol_header = elf_parsed->symbol_header;
    char *string_table = (char *) (((address_t) elf_parsed->image) + 
        elf_parsed->string_header->offset);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s::%s\n",
        __FILE__, __FUNCTION__);

    /* Work out all unresolved symbols. Symbol index 0 is not used. */
    for (symbol_index = 1; symbol_index * sizeof (elf_symbol_t) < 
        symbol_header->size; symbol_index++)
    {
        symbol = (elf_symbol_t *) (((address_t) elf_parsed->image) + 
            symbol_header->offset + symbol_index * sizeof (elf_symbol_t));

        /* Non-empty value and a section header means we should just
           do simple address translation to our new offset. */
        if (symbol->value != 0 && symbol->section_header != 0)
        {
            symbol->value += (address_t) elf_parsed->image;
        }
        /* Empty value and no section header means unresolved
           symbol. */
        else if (symbol->value == 0 && symbol->section_header == 0)
        {
            int function_index;
            char *name = string_table + symbol->name;
            volatile bool match = FALSE;

            for (function_index = 0; 
                 function[function_index].name != NULL;
                 function_index++)
            {
                if (string_compare (function[function_index].name, name) == 0)
                {
                    /* We have a match. Modify the symbol table. */
                    symbol->value = (uint32_t) function[function_index].function;
                    
                    match = TRUE;
                    break;
                }
            }

            if (match == FALSE)
            {
                DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
                    "Unresolved symbol in module: %s\n", name);

                return STORM_RETURN_MODULE_INVALID;
            }
        }
    }
    
    return STORM_RETURN_SUCCESS;
}

/* Relocate relocatable symbols. */
return_t elf_relocate (elf_parsed_t *elf_parsed)
{
    elf_relocation_t *relocation;
    elf_section_header_t *relocation_header = elf_parsed->relocation_header;
    elf_header_t *elf_header = elf_parsed->elf_header;
    int index;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s::%s\n",
        __FILE__, __FUNCTION__);

    /* Perform relocation. */
    if (elf_parsed->relocation_header == NULL)
    {
        return STORM_RETURN_SUCCESS;
    }
   
    relocation = (elf_relocation_t *) (((uint32_t) elf_header) + 
        elf_parsed->relocation_header->offset);

    for (index = 0; index * sizeof (elf_relocation_t) <
             relocation_header->size; index++)
    {
        address_t symbol_address;
        address_t *relocation_address;
        
        return_t return_value = elf_symbol_find_by_index (elf_parsed, 
            relocation[index].symbol_index, &symbol_address);
            
        if (return_value != STORM_RETURN_SUCCESS)
        {
            return return_value;
        }

        /* Perform this relocation. */
        relocation_address = (address_t *) (((address_t) elf_parsed->image) + 
            relocation[index].offset);
        
        // FIXME: Use defines for these types.
        if (relocation[index].symbol_type == 1)
        {
            (*relocation_address) = (*relocation_address) + symbol_address;
        }
        else if (relocation[index].symbol_type == 2)
        {
            /* Are you confused yet? :-) */
            (*relocation_address) =  (*relocation_address) + 
                (address_t) (symbol_address - (address_t) relocation_address);
        }
        else if (relocation[index].symbol_type == ELF_RELOCATION_RELATIVE)
        {
            (*relocation_address) = (*relocation_address) + 
                (address_t) elf_parsed->image;
        }
        else
        {
            DEBUG_PRINT (DEBUG_LEVEL_ERROR,
                "%x %u %u\n",
                relocation[index].offset,
                relocation[index].symbol_type,
                relocation[index].symbol_index);
                
            DEBUG_PRINT (DEBUG_LEVEL_ERROR,
                "Unknown relocation type: %u == %u\n", 
                relocation[index].symbol_type,
                relocation[index].symbol_type);
                
            DEBUG_PRINT (DEBUG_LEVEL_ERROR,
                "%x %u %u\n",
                relocation[index].offset,
                relocation[index].symbol_type,
                relocation[index].symbol_index);
                         
            return STORM_RETURN_MODULE_INVALID;
        }
    }

    return STORM_RETURN_SUCCESS;
}

/* Find the given symbol in the symbol table. */
return_t elf_symbol_find_by_index (elf_parsed_t *elf_parsed,
    unsigned int index, uint32_t *address)
{
    elf_section_header_t *symbol_header = elf_parsed->symbol_header;
    elf_symbol_t *symbol;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s::%s\n",
        __FILE__, __FUNCTION__);

    /* Make sure this symbol exists in the symbol table. */
    if (symbol_header->size / sizeof (elf_symbol_t) < index)
    {
        return STORM_RETURN_MODULE_INVALID;
    }

    symbol = (elf_symbol_t *) (((address_t) elf_parsed->image) + 
        symbol_header->offset + index * sizeof (elf_symbol_t));
        
    (*address) = symbol->value;
    
    return STORM_RETURN_SUCCESS;
}

/* Find the given symbol in the symbol table. */
return_t elf_symbol_find_by_name (elf_parsed_t *elf_parsed,
    char *name, address_t *address)
{
    elf_section_header_t *symbol_header = elf_parsed->symbol_header;
    char *string_table = (char *) (((address_t) elf_parsed->image) + 
        elf_parsed->string_header->offset);
    int symbol_index;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s::%s\n",
        __FILE__, __FUNCTION__);

    for (symbol_index = 1; 
        symbol_index * sizeof (elf_symbol_t) < symbol_header->size; 
        symbol_index++)
    {
        elf_symbol_t *symbol = (elf_symbol_t *) 
            (((address_t) elf_parsed->image) + symbol_header->offset + 
            symbol_index * sizeof (elf_symbol_t));
		
        char *symbol_name = string_table + symbol->name;

        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
    	    "%s::%s Test: %s\n",
            __FILE__, __FUNCTION__, symbol_name);

        if (string_compare (symbol_name, name) == 0)
        {
            (*address) = symbol->value;
            
            return STORM_RETURN_SUCCESS;
        }
    }

    return STORM_RETURN_MODULE_INVALID;
}

/* Load an ELF. Allocate memory for it, and copy the data from the
   different sections there. */
return_t elf_load_module (elf_parsed_t *elf_parsed)
{
    elf_header_t *elf_header = elf_parsed->elf_header;
    address_t highest_address = 0;
    return_t return_value;
    void *image;
    int index;
    page_number_t pages;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s::%s\n",
        __FILE__, __FUNCTION__);

    /* Find the highest end address of a section. This presumes that
       the sections come right after each other, which is a reasonable
       presumption since we control ELF generation for our OS. */
    for (index = 0; index < elf_header->section_header_entries; index++)
    {
        elf_section_header_t *section_header = (elf_section_header_t *) 
            (((uint32_t) elf_header) + elf_header->section_header_offset + 
            (index * elf_header->section_header_entry_size));
        
        if (section_header->flags & ELF_SECTION_FLAG_ALLOCATE &&
            section_header->address + section_header->size > highest_address)
        {
            highest_address = section_header->address + section_header->size;
        }
    }
  
    return_value = physical_memory_allocate (&pages, 
        SIZE_IN_PAGES (highest_address));
    
    image = (void *) (pages * PAGE_SIZE);
    
    if (return_value != STORM_RETURN_SUCCESS)
    {
        return return_value;
    }

    /* Now, go through all the sections again, but this time copying
       off all the sections into our new pointer. */
    for (index = 0; index < elf_header->section_header_entries; index++)
    {
        elf_section_header_t *section_header = (elf_section_header_t *) 
            (((uint32_t) elf_header) + elf_header->section_header_offset + 
            (index * elf_header->section_header_entry_size));
            
        if (section_header->flags & ELF_SECTION_FLAG_ALLOCATE)
        {
            memory_copy (
                (void *) (((address_t) image) + section_header->address),
                (void *) (((address_t) elf_header) + section_header->offset),
                section_header->size);
        }
    }

    elf_parsed->image = image;

    return STORM_RETURN_SUCCESS;
}

#if defined (SUBSYSTEM_PROCESS)

/* Parse the given ELF header. */
return_t elf_parse_program (elf_header_t *elf_header, 
    elf_parsed_program_t *elf_parsed)
{
    int index;
    return_t return_value;
    unsigned int elf_type;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p, %p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        elf_header, elf_parsed);

    /* Make sure the ELF is valid. */
    if (elf_identify (elf_header) != STORM_ELF_PROGRAM)
    {
        return -1;
    }

    elf_parsed->elf_header = elf_header;
    return 0;

    /* Find the string table and symbol table. */
    for (index = 0; index < elf_header->section_header_entries; index++)
    {
        elf_section_header_t *section_header = 
            (elf_section_header_t *) (((uint32_t) elf_header) + 
            elf_header->section_header_offset + (index * 
                elf_header->section_header_entry_size));
                
        if (section_header->type == ELF_SECTION_TYPE_STRING_TABLE &&
            section_header->flags & ELF_SECTION_FLAG_ALLOCATE)
        {
            elf_parsed->string_header = section_header;
        }
        else if (section_header->type == ELF_SECTION_TYPE_DYNAMIC_SYMBOL_TABLE)
        {
            elf_parsed->symbol_header = section_header;
        }
    }

    /* If we don't have a string table and symbol table, we won't be
       able to link this module into the kernel. */
    if (elf_parsed->string_header == NULL ||
        elf_parsed->symbol_header == NULL)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "Elf image don't have a string table and symbol table\n");
	    
        return STORM_RETURN_MODULE_INVALID;
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s String table: %p, Symbol table: %p.\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        elf_parsed->string_header, elf_parsed->symbol_header);

    return STORM_RETURN_SUCCESS;
}

#define ELF_SECTION_TYPE_PROGRAM ELF_SECTION_TYPE_UNDEFINED

/* Load an ELF. Allocate memory for it, and copy the data from the
   different sections there. */
return_t elf_load_program (elf_parsed_program_t *elf_parsed,
    process_t *process)
{
    return_t return_value;
    elf_header_t *elf_header = elf_parsed->elf_header;
    int index;
    page_directory_t *page_directory = process->page_directory;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p, %p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        elf_parsed, process);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s Elf header: %p\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        elf_header);

    /* Find the highest end address of a section. This presumes that
       the sections come right after each other, which is a reasonable
       presumption since we control ELF generation for our OS. */
    for (index = 0; index < elf_header->section_header_entries; index++)
    {
        elf_section_header_t *section_header = (elf_section_header_t *) 
            (((uint32_t) elf_header) + elf_header->section_header_offset + 
            (index * elf_header->section_header_entry_size));

        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE2, 
            "%s: %s Section header: %p\n",
            DEBUG_MODULE_NAME, __FUNCTION__, section_header);


        if (section_header->flags & ELF_SECTION_FLAG_ALLOCATE &&
            section_header->type == ELF_SECTION_TYPE_PROGRAM)
        {
            void *buffer;
             
            unsigned int remaining_size = section_header->size;
            size_t file_offset = 0;
            unsigned int page_offset = 0;

            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
                "%s: %s Program section header: %p (%p, %X, %X)\n",
                DEBUG_MODULE_NAME, __FUNCTION__, 
                section_header, section_header->address, 
                section_header->offset, section_header->size);

            /* If the first page is not page aligned, handle it
               slightly differently. */
            if (section_header->address % PAGE_SIZE != 0)
            {
                unsigned int offset = section_header->address % PAGE_SIZE;
                
                size_t size = MIN (section_header->size, PAGE_SIZE - offset);
                
                DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
                    "%s: %s Section header size: %x\n",
                    DEBUG_MODULE_NAME, __FUNCTION__, section_header->size);

                /* If this section overlaps another section, find the
                   physical addres of the page that has already been
                   mapped at this place. */
                unsigned int flags;
                page_number_t page_number;
                
                return_value = virtual_memory_lookup (page_directory, 
                    PAGE_NUMBER (section_header->address), &page_number, &flags);

                /* Yes -- use this physical address instead. */
                // FIXME: Check that the flags are valid.
                if (return_value == STORM_RETURN_SUCCESS)
                {
                    buffer = (void *) PAGE_ADDRESS (page_number);
                }
                /* The page is not mapped, so map it please. */
                else 
                {
                    /* Allocate memory for this section and map it at
                       the right place. */
                    return_value = physical_memory_allocate (&page_number, 1);
                    
                    buffer = (void *) PAGE_ADDRESS (page_number);
                    
                    if (return_value != STORM_RETURN_SUCCESS)
                    {
                        DEBUG_PRINT (DEBUG_LEVEL_ERROR,
                            "Failed to allocate memory");
                        
                        return return_value;
                    }
                    
                    /* Map this memory at the right place. */
                    // FIXME: Get some of the flags from the section
                    // (like writable).
                    return_value = virtual_memory_map (page_directory, 
                         PAGE_NUMBER (section_header->address),
                         PAGE_NUMBER (buffer), 1, PAGE_USER);
                         
                    if (return_value != STORM_RETURN_SUCCESS)
                    {
                        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
                            "Failed to map memory");
                        
                        return return_value;
                    }
                }                    

                DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
                    "%s: %s Copying to %p frop %x (%d bytes)\n",
                    DEBUG_MODULE_NAME, __FUNCTION__, 
                    (void *) ((address_t) buffer + offset),
                    (void *) (((address_t) elf_header) + 
                        section_header->offset), size);                
                                       
                memory_copy ((void *) ((address_t) buffer + offset),
                             (void *) (((address_t) elf_header) +
                                       section_header->offset), size);
                
                remaining_size -= size;
                file_offset += size;
                page_offset++;
            }

            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
                "%s: %s Remaining size: %u (%X)\n",
                DEBUG_MODULE_NAME, __FUNCTION__, remaining_size, file_offset);
            
            /* We have to take it one page at a time. */
            while (remaining_size > 0)
            {
                /* If this section overlaps another section, find the
                   physical addres of the page that has already been
                   mapped at this place. */
                unsigned int flags;
                page_number_t page_number;
                
                return_value = virtual_memory_lookup (page_directory, 
                    PAGE_NUMBER (section_header->address), &page_number, &flags);

                /* If it was found, use it instead of overwriting it. */
                if (return_value == STORM_RETURN_SUCCESS)
                {
                    buffer = (void *) PAGE_ADDRESS (page_number);
                }
                else
                {
                    /* Allocate memory for this section and map it at the
                       right place. */
                    return_value = physical_memory_allocate (&page_number, 1);
                    
                    if (return_value != STORM_RETURN_SUCCESS)
                    {
                        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
                            "Failed to allocate memory");
                        return return_value;
                    }
                    
                    buffer = (void *) PAGE_ADDRESS (page_number);

                    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
                        "%s: %s Buffer: %p\n",
                        DEBUG_MODULE_NAME, __FUNCTION__, buffer);
                    
                    memory_set_uint8 ((uint8_t *) buffer, 0, PAGE_SIZE);
                    /* Map this memory at the right place. */
                    // FIXME: Get some of the flags from the section (like
                    // writable).
                    return_value = virtual_memory_map (page_directory, 
                         PAGE_NUMBER (section_header->address) + page_offset,
                         PAGE_NUMBER (buffer), 1, PAGE_USER);
                         
                    if (return_value != STORM_RETURN_SUCCESS)
                    {
                        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
                            "Failed to map memory");
                        
                        return return_value;
                    }
                }

                /* Copy this page from the image. Another way to do
                   this would be to copy all the section in one sweep,
                   but that would require us to change the CR3 to
                   page_directory or map it in the current
                   process. Either way is most certainly much slower
                   than this, since it needs to flush the cache... */

                size_t length;
                if (remaining_size < PAGE_SIZE)
                {
                    length = remaining_size;
                }
                else
                {
                    length = PAGE_SIZE;
                }

                DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
                    "Address: %X %X %X\n",
                    (uint32_t) elf_header, 
                    (uint32_t) section_header->offset,
                    (uint32_t) file_offset);

                DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
                    "Copying to %p from %p (%d bytes)\n", buffer, 
                    (void *) ((address_t) elf_header + section_header->offset + 
                    file_offset), length);
                    
                memory_copy (buffer, (void *) ((address_t) elf_header + 
                    section_header->offset + file_offset), length);
                    
                remaining_size -= length;
                file_offset += length;
                page_offset++;
            }
        }
    }

    process->entry_point = elf_header->entry_point;
  
    return STORM_RETURN_SUCCESS;
}
#endif
