#include <enviroment.h>

#include "cdfs.h"

#define DEBUG_MODULE_NAME L"CDFS"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#ifndef __STORM_KERNEL__
#   define DEBUG_SUPPLIER (cdfs_debug_supplier)
#endif


/* FUNCTIONS ****************************************************************/
bool wstrcmpjoki (p_wchar_t s1, p_wchar_t s2)
/*
 * FUNCTION: Compare two wide character strings, s2 with jokers (* or ?)
 * return TRUE if s1 like s2
 */
{
  while ((*s2=='*')||(*s2=='?')||(towlower(*s1)==towlower(*s2)))
    {
      if ((*s1)==0 && (*s2)==0)
        return(TRUE);

      if(*s2=='*')
	{
	  s2++;
	  while (*s1)
	    if (wstrcmpjoki(s1,s2))
	      return(TRUE);
	    else
	      s1++;
	}
      else
	{
	  s1++;
	  s2++;
	}
    }

  if ((*s2)=='.')
    {
      for (;((*s2)=='.')||((*s2)=='*')||((*s2)=='?');s2++)
	;
    }

  if ((*s1)==0 && (*s2)==0)
    return(TRUE);

  return(FALSE);
}

void CdfsSwapString(p_wchar_t Out, p_uint8_t In, uint32_t Count)
{
  p_uint8_t t = (p_uint8_t)Out;
  uint32_t i;

  for (i = 0; i < Count; i += 2)
    {
      t[i] = In[i+1];
      t[i+1] = In[i];
      if (t[i+1] == 0 && t[i] == ';')
	break;
    }
  t[i] = 0;
  t[i+1] = 0;
}

void CdfsDateTimeToFileTime (p_file_data_t Fcb, TIME *FileTime)
{
    TIME_FIELDS TimeFields;

    TimeFields.Milliseconds = 0;
    TimeFields.Second = Fcb->Entry.Second;
    TimeFields.Minute = Fcb->Entry.Minute;
    TimeFields.Hour = Fcb->Entry.Hour;

    TimeFields.Day = Fcb->Entry.Day;
    TimeFields.Month = Fcb->Entry.Month;
    TimeFields.Year = Fcb->Entry.Year + 1900;

//  RtlTimeFieldsToTime(&TimeFields,
//		      (PLARGE_INTEGER)FileTime);
}

void CdfsFileFlagsToAttributes (p_file_data_t Fcb, p_uint32_t FileAttributes)
{
  /* FIXME: Fix attributes */

  *FileAttributes = // FILE_ATTRIBUTE_READONLY |
		    (Fcb->Entry.FileFlags & 0x01) ? FILE_ATTRIBUTE_HIDDEN : 0 |
		    (Fcb->Entry.FileFlags & 0x02) ? FILE_ATTRIBUTE_DIRECTORY : 0 |
		    (Fcb->Entry.FileFlags & 0x04) ? FILE_ATTRIBUTE_SYSTEM : 0 |
		    (Fcb->Entry.FileFlags & 0x10) ? FILE_ATTRIBUTE_READONLY : 0;
}
