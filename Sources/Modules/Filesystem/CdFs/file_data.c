#include <enviroment.h>

#include "cdfs.h"

#define DEBUG_MODULE_NAME L"CDFS"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#ifndef __STORM_KERNEL__
#   define DEBUG_SUPPLIER (cdfs_debug_supplier)
#endif

static p_wchar_t CdfsGetNextPathElement (p_wchar_t FileName)
{
    if (*FileName == L'\0')
    {
        return(NULL);
    }

    while (*FileName != L'\0' && *FileName != L'\\')
    {
        FileName++;
    }

    return(FileName);
}


static void CdfsWSubString (p_wchar_t pTarget, const p_wchar_t pSource, 
    size_t pLength)
{
    wstring_copy_max (pTarget, pSource, pLength);
    pTarget [pLength] = L'\0';
}


p_file_data_t CdfsCreateFCB (p_wchar_t FileName)
{
    p_file_data_t Fcb;

    Fcb = ExAllocatePoolWithTag(NonPagedPool, sizeof(FCB), TAG_FCB);

    memory_clear (Fcb, sizeof (file_data_t));

    if (FileName)
    {
        wstring_copy (Fcb->PathName, FileName);
        
        if (wstring_rchr (Fcb->PathName, L'\\') != 0)
        {
            Fcb->ObjectName = wstring_chr(Fcb->PathName, L'\\');
        }
        else
        {
            Fcb->ObjectName = Fcb->PathName;
        }
    }

//  ExInitializeResourceLite(&Fcb->MainResource);

    return (Fcb);
}


void CdfsDestroyFCB (p_file_data_t Fcb)
{
//  ExDeleteResourceLite(&Fcb->MainResource);

    ExFreePool(Fcb);
}


bool CdfsFCBIsDirectory (p_file_data_t Fcb)
{
//  return(Fcb->entry.Attrib & FILE_ATTRIBUTE_DIRECTORY);
    return (Fcb->Entry.FileFlags & 0x02);
}


bool CdfsFCBIsRoot (p_file_data_t Fcb)
{
    return (wstring_compare (Fcb->PathName, L"\\") == 0);
}


void CdfsGrabFCB(PDEVICE_EXTENSION Vcb,
	    PFCB Fcb)
{
  KIRQL  oldIrql;

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "grabbing FCB at %x: %S, refCount:%d\n",
	 Fcb,
	 Fcb->PathName,
	 Fcb->RefCount);

  KeAcquireSpinLock(&Vcb->FcbListLock, &oldIrql);
  Fcb->RefCount++;
  KeReleaseSpinLock(&Vcb->FcbListLock, oldIrql);
}

void CdfsReleaseFCB(PDEVICE_EXTENSION Vcb,
	       PFCB Fcb)
{
  KIRQL  oldIrql;

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "releasing FCB at %x: %S, refCount:%d\n",
	 Fcb,
	 Fcb->PathName,
	 Fcb->RefCount);

  KeAcquireSpinLock(&Vcb->FcbListLock, &oldIrql);
  Fcb->RefCount--;
  if (Fcb->RefCount <= 0 && !CdfsFCBIsDirectory(Fcb))
    {
      RemoveEntryList(&Fcb->FcbListEntry);
      CdfsDestroyFCB(Fcb);
    }
  KeReleaseSpinLock(&Vcb->FcbListLock, oldIrql);
}


void CdfsAddFCBToTable(PDEVICE_EXTENSION Vcb,
		  PFCB Fcb)
{
  KIRQL  oldIrql;

  KeAcquireSpinLock(&Vcb->FcbListLock, &oldIrql);
  Fcb->DevExt = Vcb;
  InsertTailList(&Vcb->FcbListHead, &Fcb->FcbListEntry);
  KeReleaseSpinLock(&Vcb->FcbListLock, oldIrql);
}


PFCB CdfsGrabFCBFromTable(PDEVICE_EXTENSION Vcb,
		     PWSTR FileName)
{
  KIRQL  oldIrql;
  PFCB Fcb;
  PLIST_ENTRY  current_entry;

  KeAcquireSpinLock(&Vcb->FcbListLock, &oldIrql);

  if (FileName == NULL || *FileName == 0)
    {
      DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Return FCB for stream file object\n");
      Fcb = Vcb->StreamFileObject->FsContext;
      Fcb->RefCount++;
      KeReleaseSpinLock(&Vcb->FcbListLock, oldIrql);
      return(Fcb);
    }

  current_entry = Vcb->FcbListHead.Flink;
  while (current_entry != &Vcb->FcbListHead)
    {
      Fcb = CONTAINING_RECORD(current_entry, FCB, FcbListEntry);

      DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Comparing '%S' and '%S'\n", FileName, Fcb->PathName);
      if (_wcsicmp(FileName, Fcb->PathName) == 0)
	{
	  Fcb->RefCount++;
	  KeReleaseSpinLock(&Vcb->FcbListLock, oldIrql);
	  return(Fcb);
	}

      //FIXME: need to compare against short name in FCB here

      current_entry = current_entry->Flink;
    }
  KeReleaseSpinLock(&Vcb->FcbListLock, oldIrql);

  return(NULL);
}


return_t
CdfsFCBInitializeCache(PVCB Vcb,
		       PFCB Fcb)
{
  PFILE_OBJECT FileObject;
  return_t Status;
//  PCCB  newCCB;

  FileObject = IoCreateStreamFileObject(NULL, Vcb->StorageDevice);
/*
  newCCB = ExAllocatePoolWithTag(NonPagedPool, sizeof(CCB), TAG_CCB);
  if (newCCB == NULL)
    {
      return(STATUS_INSUFFICIENT_RESOURCES);
    }
  RtlZeroMemory(newCCB,
		sizeof(CCB));
*/
  FileObject->Flags = FileObject->Flags | FO_FCB_IS_VALID |
      FO_DIRECT_CACHE_PAGING_READ;
  FileObject->SectionObjectPointer = &Fcb->SectionObjectPointers;
  FileObject->FsContext = Fcb;
//  FileObject->FsContext2 = newCCB;
//  newCCB->PtrFileObject = FileObject;
  Fcb->FileObject = FileObject;
  Fcb->DevExt = Vcb;

  Status = CcRosInitializeFileCache(FileObject,
				    PAGE_SIZE);
  if (!NT_SUCCESS(Status))
    {
      DbgPrint("CcRosInitializeFileCache failed\n");
      KEBUGCHECK(0);
    }

  ObDereferenceObject(FileObject);
  Fcb->Flags |= FCB_CACHE_INITIALIZED;

  return(Status);
}


p_file_data_t CdfsMakeRootFCB (PDEVICE_EXTENSION Vcb)
{
  p_file_data_t Fcb;

  Fcb = CdfsCreateFCB(L"\\");

  Fcb->Entry.DataLengthL = Vcb->CdInfo.RootSize;
  Fcb->Entry.ExtentLocationL = Vcb->CdInfo.RootStart;
  Fcb->Entry.FileFlags = 0x02; // FILE_ATTRIBUTE_DIRECTORY;
  Fcb->RefCount = 1;
  Fcb->DirIndex = 0;
  Fcb->RFCB.FileSize.QuadPart = Vcb->CdInfo.RootSize;
  Fcb->RFCB.ValidDataLength.QuadPart = Vcb->CdInfo.RootSize;
  Fcb->RFCB.AllocationSize.QuadPart = Vcb->CdInfo.RootSize;

  CdfsFCBInitializeCache(Vcb, Fcb);
  CdfsAddFCBToTable(Vcb, Fcb);
  CdfsGrabFCB(Vcb, Fcb);

  return(Fcb);
}


p_file_data_t CdfsOpenRootFCB (PDEVICE_EXTENSION Vcb)
{
  p_file_data_t Fcb;

  Fcb = CdfsGrabFCBFromTable(Vcb, L"\\");
  if (Fcb == NULL)
    {
      Fcb = CdfsMakeRootFCB(Vcb);
    }

  return(Fcb);
}


/*
 * FUNCTION: Retrieves the file name from a directory record.
 */
static void CdfsGetDirEntryName(PDEVICE_EXTENSION DeviceExt,
		    PDIR_RECORD Record,
		    PWSTR Name)
{
  if (Record->FileIdLength == 1 && Record->FileId[0] == 0)
    {
      wcscpy(Name, L".");
    }
  else if (Record->FileIdLength == 1 && Record->FileId[0] == 1)
    {
      wcscpy(Name, L"..");
    }
  else
    {
      if (DeviceExt->CdInfo.JolietLevel == 0)
	{
	  uint32_t i;

	  for (i = 0; i < Record->FileIdLength && Record->FileId[i] != ';'; i++)
	    Name[i] = (WCHAR)Record->FileId[i];
	  Name[i] = 0;
	}
      else
	{
	  CdfsSwapString(Name,
			 Record->FileId,
			 Record->FileIdLength);
	}
    }

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Name '%S'\n", Name);
}


return_t CdfsMakeFCBFromDirEntry (
    PVCB Vcb,
    p_file_data_t DirectoryFCB,
    p_wchar_t LongName,
    p_wchar_t ShortName,
    p_directory_record_t Record,
    p_file_data_t * fileFCB)
{
  wchar_t pathName[MAX_PATH];
  PFCB rcFCB;
  uint32_t Size;

  if (LongName [0] != 0 && wcslen (DirectoryFCB->PathName) +
        sizeof(WCHAR) + wcslen (LongName) > MAX_PATH)
    {
      return(STATUS_OBJECT_NAME_INVALID);
    }

  wcscpy(pathName, DirectoryFCB->PathName);
  if (!CdfsFCBIsRoot(DirectoryFCB))
    {
      wcscat(pathName, L"\\");
    }

  if (LongName[0] != 0)
    {
      wcscat(pathName, LongName);
    }
  else
    {
      wchar_t entryName[MAX_PATH];

      CdfsGetDirEntryName(Vcb, Record, entryName);
      wcscat(pathName, entryName);
    }

  rcFCB = CdfsCreateFCB(pathName);
  memory_copy (&rcFCB->Entry, Record, sizeof(DIR_RECORD));

  /* Copy short name into FCB */
  rcFCB->ShortNameLength = wcslen(ShortName) * sizeof(WCHAR);
  wcscpy(rcFCB->ShortName, ShortName);

  Size = rcFCB->Entry.DataLengthL;

  rcFCB->RFCB.FileSize.QuadPart = Size;
  rcFCB->RFCB.ValidDataLength.QuadPart = Size;
  rcFCB->RFCB.AllocationSize.QuadPart = ROUND_UP(Size, BLOCKSIZE);
  if (CdfsFCBIsDirectory(rcFCB))
  {
     CdfsFCBInitializeCache(Vcb, rcFCB);
  }
  rcFCB->RefCount++;
  CdfsAddFCBToTable(Vcb, rcFCB);
  *fileFCB = rcFCB;

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "%S %d %I64d\n", LongName, Size, rcFCB->RFCB.AllocationSize.QuadPart);

  return(STATUS_SUCCESS);
}


return_t CdfsAttachFCBToFileObject (PDEVICE_EXTENSION Vcb, PFCB Fcb, 
    PFILE_OBJECT FileObject)
{
  return_t Status;
//  PCCB  newCCB;
/*
  newCCB = ExAllocatePoolWithTag(NonPagedPool, sizeof(CCB), TAG_CCB);
  if (newCCB == NULL)
    {
      return(STATUS_INSUFFICIENT_RESOURCES);
    }
  memset(newCCB, 0, sizeof(CCB));
*/
  FileObject->Flags = FileObject->Flags | FO_FCB_IS_VALID |
      FO_DIRECT_CACHE_PAGING_READ;
  FileObject->SectionObjectPointer = &Fcb->SectionObjectPointers;
  FileObject->FsContext = Fcb;
//  FileObject->FsContext2 = newCCB;
//  newCCB->PtrFileObject = FileObject;
  Fcb->DevExt = Vcb;

  if (CdfsFCBIsDirectory(Fcb))
    {
      Status = CcRosInitializeFileCache(FileObject,
					PAGE_SIZE);
      if (!NT_SUCCESS(Status))
	{
	  DbgPrint("CcRosInitializeFileCache failed\n");
	  KEBUGCHECK(0);
	}
      Fcb->Flags |= FCB_CACHE_INITIALIZED;
    }

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "file open: fcb:%x file size: %d\n", Fcb, Fcb->Entry.DataLengthL);

  return(STATUS_SUCCESS);
}


return_t CdfsDirFindFile(PDEVICE_EXTENSION DeviceExt,
		PFCB DirectoryFcb,
		PWSTR FileToFind,
		PFCB *FoundFCB)
{
  wchar_t TempName[2];
  wchar_t Name[256];
  p_void_t Block;
  uint32_t FirstSector;
  uint32_t DirSize;
  PDIR_RECORD Record;
  uint32_t Offset;
  uint32_t BlockOffset;
  return_t Status;

  LARGE_INTEGER StreamOffset;
  p_void_t Context;

  wchar_t ShortNameBuffer[13];
  UNICODE_STRING ShortName;
  UNICODE_STRING LongName;
  bool HasSpaces;
//  GENERATE_NAME_CONTEXT NameContext;


  assert(DeviceExt);
  assert(DirectoryFcb);
  assert(FileToFind);

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "CdfsDirFindFile(VCB:%08x, dirFCB:%08x, File:%S)\n",
	 DeviceExt,
	 DirectoryFcb,
	 FileToFind);
  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Dir Path:%S\n", DirectoryFcb->PathName);

  /*  default to '.' if no filename specified */
  if (wcslen(FileToFind) == 0)
    {
      TempName[0] = L'.';
      TempName[1] = 0;
      FileToFind = TempName;
    }

  DirSize = DirectoryFcb->Entry.DataLengthL;
  StreamOffset.QuadPart = (LONGLONG)DirectoryFcb->Entry.ExtentLocationL * (LONGLONG)BLOCKSIZE;

  if(!CcMapData(DeviceExt->StreamFileObject, &StreamOffset,
		BLOCKSIZE, TRUE, &Context, &Block))
  {
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "CcMapData() failed\n");
    return(STATUS_UNSUCCESSFUL);
  }

  Offset = 0;
  BlockOffset = 0;
  Record = (PDIR_RECORD)Block;
  while(TRUE)
    {
      if (Record->RecordLength == 0)
	{
	  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "RecordLength == 0  Stopped!\n");
	  break;
	}
	
      DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "RecordLength %u  ExtAttrRecordLength %u  NameLength %u\n",
	     Record->RecordLength, Record->ExtAttrRecordLength, Record->FileIdLength);

      CdfsGetDirEntryName(DeviceExt, Record, Name);
      DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Name '%S'\n", Name);

      RtlInitUnicodeString(&LongName, Name);
      ShortName.Length = 0;
      ShortName.MaximumLength = 26;
      ShortName.Buffer = ShortNameBuffer;
      memset(ShortNameBuffer, 0, 26);

      if ((RtlIsNameLegalDOS8Dot3(&LongName, NULL, &HasSpaces) == FALSE) ||
	  (HasSpaces == TRUE))
	{
	  /* Build short name */
	  RtlGenerate8dot3Name(&LongName,
			       FALSE,
			       &NameContext,
			       &ShortName);
	}
      else
	{
	  /* copy short name */
	  RtlUpcaseUnicodeString(&ShortName,
				 &LongName,
				 FALSE);
	}

      DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "ShortName '%wZ'\n", &ShortName);

      if (wstrcmpjoki(Name, FileToFind) || wstrcmpjoki(ShortNameBuffer, FileToFind))
	{
	  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Match found, %S\n", Name);
	  Status = CdfsMakeFCBFromDirEntry(DeviceExt,
					   DirectoryFcb,
					   Name,
					   ShortNameBuffer,
					   Record,
					   FoundFCB);

	  CcUnpinData(Context);

	  return(Status);
	}

      Offset += Record->RecordLength;
      BlockOffset += Record->RecordLength;
      Record = (PDIR_RECORD)(Block + BlockOffset);
      if (BlockOffset >= BLOCKSIZE || Record->RecordLength == 0)
	{
	  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Map next sector\n");
	  CcUnpinData(Context);
	  StreamOffset.QuadPart += BLOCKSIZE;
	  Offset = ROUND_UP(Offset, BLOCKSIZE);
	  BlockOffset = 0;

	  if (!CcMapData(DeviceExt->StreamFileObject,
			 &StreamOffset,
			 BLOCKSIZE, TRUE,
			 &Context, &Block))
	    {
	      DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "CcMapData() failed\n");
	      return(STATUS_UNSUCCESSFUL);
	    }
	  Record = (PDIR_RECORD)(Block + BlockOffset);
	}

      if (Offset >= DirSize)
	break;
    }

  CcUnpinData(Context);

  return(STATUS_OBJECT_NAME_NOT_FOUND);
}


return_t CdfsGetFCBForFile(PDEVICE_EXTENSION Vcb,
    p_file_data_t *pParentFCB,
    p_file_data_t *pFCB,
    const p_wchar_t pFileName)
{
  return_t Status;
  wchar_t  pathName [MAX_PATH];
  wchar_t  elementName [MAX_PATH];
  p_wchar_t  currentElement;
  p_file_data_t  FCB;
  p_file_data_t  parentFCB;

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "CdfsGetFCBForFile(%x, %x, %x, '%S')\n",
	 Vcb,
	 pParentFCB,
	 pFCB,
	 pFileName);

  /* Trivial case, open of the root directory on volume */
  if (pFileName [0] == L'\0' || wcscmp(pFileName, L"\\") == 0)
    {
      DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "returning root FCB\n");

      FCB = CdfsOpenRootFCB(Vcb);
      *pFCB = FCB;
      *pParentFCB = NULL;

      return((FCB != NULL) ? STATUS_SUCCESS : STATUS_OBJECT_PATH_NOT_FOUND);
    }
  else
    {
      currentElement = pFileName + 1;
      wcscpy (pathName, L"\\");
      FCB = CdfsOpenRootFCB (Vcb);
    }
  parentFCB = NULL;

  /* Parse filename and check each path element for existance and access */
  while (CdfsGetNextPathElement(currentElement) != 0)
    {
      /*  Skip blank directory levels */
      if ((CdfsGetNextPathElement(currentElement) - currentElement) == 0)
	{
	  currentElement++;
	  continue;
	}

      DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
          "Parsing, currentElement:%S\n", currentElement);
      DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
          "  parentFCB:%x FCB:%x\n", parentFCB, FCB);

      /* Descend to next directory level */
      if (parentFCB)
	{
	  CdfsReleaseFCB(Vcb, parentFCB);
	  parentFCB = NULL;
	}

      /* fail if element in FCB is not a directory */
      if (!CdfsFCBIsDirectory(FCB))
	{
	  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Element in requested path is not a directory\n");

	  CdfsReleaseFCB(Vcb, FCB);
	  FCB = 0;
	  *pParentFCB = NULL;
	  *pFCB = NULL;

	  return(STATUS_OBJECT_PATH_NOT_FOUND);
	}
      parentFCB = FCB;

      /* Extract next directory level into dirName */
      CdfsWSubString (pathName, pFileName, 
          CdfsGetNextPathElement (currentElement) - pFileName);
      DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "  pathName:%S\n", pathName);

      FCB = CdfsGrabFCBFromTable(Vcb, pathName);
      if (FCB == NULL)
	{
	  CdfsWSubString(elementName,
			 currentElement,
			 CdfsGetNextPathElement(currentElement) - currentElement);
	  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "  elementName:%S\n", elementName);

	  Status = CdfsDirFindFile(Vcb, parentFCB, elementName, &FCB);
	  if (Status == STATUS_OBJECT_NAME_NOT_FOUND)
	    {
	      *pParentFCB = parentFCB;
	      *pFCB = NULL;
	      currentElement = CdfsGetNextPathElement(currentElement);
	      if (*currentElement == L'\0' || CdfsGetNextPathElement(currentElement + 1) == 0)
		{
		  return(STATUS_OBJECT_NAME_NOT_FOUND);
		}
	      else
		{
		  return(STATUS_OBJECT_PATH_NOT_FOUND);
		}
	    }
	  else if (!NT_SUCCESS(Status))
	    {
	      CdfsReleaseFCB(Vcb, parentFCB);
	      *pParentFCB = NULL;
	      *pFCB = NULL;

	      return(Status);
	    }
	}
      currentElement = CdfsGetNextPathElement(currentElement);
    }

  *pParentFCB = parentFCB;
  *pFCB = FCB;

  return(STATUS_SUCCESS);
}
