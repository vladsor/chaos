#include <enviroment.h>

#include "Include/return_values.h"
#include "Include/fat.h"
#include "Include/structs.h"
#include "Include/entry.h"

#include "Include/types.h"
#include "Include/volume.h"
#include "Include/file.h"

#include "Include/common.h"
#include "Include/low_fat.h"
#include "Include/read_write.h"
#include "Include/directory_entry.h"

/*
 * FUNCTION: Converts the cluster number to a sector number for this physical
 *           device
 */
uint32_t cluster_to_sector (
    p_vfat_volume_t vfat_volume,
    uint32_t cluster)
{
    return vfat_volume->data_offset +
        ((cluster - 2) * vfat_volume->sectors_per_cluster);
}

void vfat_8_dot_3_to_wstring (
    const char *base_name,
    const char *extension,
    wchar_t *name)
{
    unsigned int from_index, to_index;
  
    from_index = to_index = 0; 

    while (from_index < 8 && base_name[from_index] != ' ')
    {
        name[to_index++] = (wchar_t) base_name[from_index++];
    }

    if (extension[0] != ' ')
    {
        name[to_index++] = L'.';

        from_index = 0;
        while (from_index < 3 && extension[from_index] != ' ')
        {
            name[to_index++] = (wchar_t) extension[from_index++];
        }
    }

    name[to_index] = L'\0';
}

void vfat_8_dot_3_to_volume_label (
    const char *base_name,
    const char *extension,
    char *name)
{
    unsigned int from_index, to_index;
  
    from_index = to_index = 0; 

    while (from_index < 8 && base_name[from_index] != ' ')
    {
        name[to_index++] = base_name[from_index++];
    }

    if (extension[0] != ' ')
    {
        name[to_index++] = '.';

        from_index = 0;
        while (from_index < 3 && extension[from_index] != ' ')
        {
            name[to_index++] = extension[from_index++];
        }
    }

    name[to_index] = '\0';
}

/*
 * FUNCTION: Compare two wide character strings, s2 with jokers (* or ?)
 * return TRUE if s1 like s2
 */
bool wstrcmpjoki (const wchar_t *s1, const wchar_t *s2)
{
   while ((*s2 == L'*') || (*s2 == L'?') || 
          (char_to_lower_case (*s1) == char_to_lower_case (*s2)))
   {
     if ((*s1)==0 && (*s2)==0)
     {
       return TRUE;
     }
     
     if (*s2 == L'*')
     {
       s2++;
       while (*s1)
        if (wstrcmpjoki (s1, s2)) return TRUE;
         else s1++;
      }
      else
      {
        s1++;
        s2++;
      }
   }
   if ((*s2) == L'.')
   {
   	for (; ((*s2) == L'.') || ((*s2) == L'*') || ((*s2) == L'?'); s2++);
   }

  if ((*s1)==0 && (*s2)==0)
  {
    return TRUE;
  }

  return FALSE;
}

wchar_t * vfat_get_next_path_element (wchar_t *file_name)
{
  if (file_name[0] == L'\0')
  {
    return  0;
  }

  while (file_name[0] != L'\0' && file_name[0] != L'/')
  {
    file_name++;
  }

  return file_name;
}

void vfat_sub_string (wchar_t *target, const wchar_t *source, uint32_t length)
{
    wstring_copy_max (target, source, length);
    target [length] = L'\0';
}
