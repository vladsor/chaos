/*
 *  ReactOS kernel
 *  Copyright (C) 2002,2003 ReactOS Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
/* $Id: attrib.c,v 1.6 2003/09/15 16:01:16 ea Exp $
 *
 * COPYRIGHT:        See COPYING in the top level directory
 * PROJECT:          ReactOS kernel
 * FILE:             drivers/fs/ntfs/attrib.c
 * PURPOSE:          NTFS filesystem driver
 * PROGRAMMER:       Eric Kohl
 * Updated	by       Valentin Verkhovsky  2003/09/12 
 */

/* INCLUDES *****************************************************************/

#include <ddk/ntddk.h>

#include <ntos.h>

//#define NDEBUG
#include <debug.h>

#include "ntfs.h"


/* FUNCTIONS ****************************************************************/



ULONG RunLength(PUCHAR run)
{
  return(*run & 0x0f) + ((*run >> 4) & 0x0f) + 1;
}


LONGLONG RunLCN(PUCHAR run)
{
	UCHAR n1 = *run & 0x0f;
	UCHAR n2 = (*run >> 4) & 0x0f;
	LONGLONG lcn = n2 == 0 ? 0 : (CHAR)(run[n1 + n2]);
	LONG i = 0;
	
	for (i = n1 +n2 - 1; i > n1; i--)
		lcn = (lcn << 8) + run[i];
	return lcn;
}



ULONGLONG RunCount(PUCHAR run)
{
	UCHAR n =  *run & 0xf;
	ULONGLONG count = 0;
	ULONG i = 0;

	for (i = n; i > 0; i--)
		count = (count << 8) + run[i];
	return count;
}


VOID
NtfsDumpFileNameAttribute(PATTRIBUTE Attribute)
{
  PRESIDENT_ATTRIBUTE ResAttr;
  PFILENAME_ATTRIBUTE FileNameAttr;

  DbgPrint("  FILE_NAME ");

  ResAttr = (PRESIDENT_ATTRIBUTE)Attribute;
//  DbgPrint(" Length %lu  Offset %hu ", ResAttr->ValueLength, ResAttr->ValueOffset);

  FileNameAttr = (PFILENAME_ATTRIBUTE)((PVOID)ResAttr + ResAttr->ValueOffset);
  DbgPrint(" '%.*S' ", FileNameAttr->NameLength, FileNameAttr->Name);
}


VOID
NtfsDumpVolumeNameAttribute(PATTRIBUTE Attribute)
{
  PRESIDENT_ATTRIBUTE ResAttr;
  PWCHAR VolumeName;

  DbgPrint("  $VOLUME_NAME ");

  ResAttr = (PRESIDENT_ATTRIBUTE)Attribute;
//  DbgPrint(" Length %lu  Offset %hu ", ResAttr->ValueLength, ResAttr->ValueOffset);

  VolumeName = (PWCHAR)((PVOID)ResAttr + ResAttr->ValueOffset);
  DbgPrint(" '%.*S' ", ResAttr->ValueLength/2, VolumeName);
}


VOID
NtfsDumpVolumeInformationAttribute(PATTRIBUTE Attribute)
{
  PRESIDENT_ATTRIBUTE ResAttr;
  PVOLINFO_ATTRIBUTE VolInfoAttr;

  DbgPrint("  $VOLUME_INFORMATION ");

  ResAttr = (PRESIDENT_ATTRIBUTE)Attribute;
//  DbgPrint(" Length %lu  Offset %hu ", ResAttr->ValueLength, ResAttr->ValueOffset);

  VolInfoAttr = (PVOLINFO_ATTRIBUTE)((PVOID)ResAttr + ResAttr->ValueOffset);
  DbgPrint(" NTFS Version %u.%u  Flags 0x%04hx ",
	   VolInfoAttr->MajorVersion,
	   VolInfoAttr->MinorVersion,
	   VolInfoAttr->Flags);
}


BOOL
NtfsDumpAttribute(PATTRIBUTE Attribute)
{
  PNONRESIDENT_ATTRIBUTE NresAttr;
  PRESIDENT_ATTRIBUTE ResAttr;
  UNICODE_STRING Name;
  PUCHAR Ptr;
  UCHAR RunHeader;
  ULONG RunLength;
  ULONG RunStart;
  

  switch (Attribute->AttributeType)
    {
     
       case AttributeFileName:
	NtfsDumpFileNameAttribute(Attribute);
	break;
  
  
      case AttributeStandardInformation:
	DbgPrint("  $STANDARD_INFORMATION ");
	break;

      case AttributeAttributeList:
	DbgPrint("  $ATTRIBUTE_LIST ");
	break;

   

      case AttributeObjectId:
	DbgPrint("  $OBJECT_ID ");
	break;

      case AttributeSecurityDescriptor:
	DbgPrint("  $SECURITY_DESCRIPTOR ");
	break;

      case AttributeVolumeName:
	NtfsDumpVolumeNameAttribute(Attribute);
	break;

      case AttributeVolumeInformation:
	NtfsDumpVolumeInformationAttribute(Attribute);
	break;

      case AttributeData:
	DbgPrint("  $DATA ");
	//DataBuf = ExAllocatePool(NonPagedPool,AttributeLengthAllocated(Attribute));
	break;

      case AttributeIndexRoot:
	DbgPrint("  $INDEX_ROOT ");
	break;

      case AttributeIndexAllocation:
	DbgPrint("  $INDEX_ALLOCATION ");
	break;

      case AttributeBitmap:
	DbgPrint("  $BITMAP ");
	break;

      case AttributeReparsePoint:
	DbgPrint("  $REPARSE_POINT ");
	break;

      case AttributeEAInformation:
	DbgPrint("  $EA_INFORMATION ");
	break;

      case AttributeEA:
	DbgPrint("  $EA ");
	break;

      case AttributePropertySet:
	DbgPrint("  $PROPERTY_SET ");
	break;

      case AttributeLoggedUtilityStream:
	DbgPrint("  $LOGGED_UTILITY_STREAM ");
	break;

      default:
	DbgPrint("  Attribute %lx ",
		 Attribute->AttributeType);
	break;
    }

  if (Attribute->NameLength != 0)
    {
      Name.Length = Attribute->NameLength * sizeof(WCHAR);
      Name.MaximumLength = Name.Length;
      Name.Buffer = (PWCHAR)((ULONG)Attribute + Attribute->NameOffset);

      DbgPrint("'%wZ' ", &Name);
    }

  DbgPrint("(%s)\n",
	   Attribute->Nonresident ? "non-resident" : "resident");
    
     


    if (Attribute->Nonresident != 0)
    {

       return TRUE;
	}

    return FALSE;

  
	


	

}


/* EOF */