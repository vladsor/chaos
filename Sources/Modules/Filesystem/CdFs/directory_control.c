#include <enviroment.h>

#include "cdfs.h"

#define DEBUG_MODULE_NAME L"CDFS"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#ifndef __STORM_KERNEL__
#   define DEBUG_SUPPLIER (cdfs_debug_supplier)
#endif

/*
 * FUNCTION: Retrieves the file name, be it in short or long file name format
 */
static return_t CdfsGetEntryName(PDEVICE_EXTENSION DeviceExt,
    p_void_t *Context,
    p_void_t *Block,
    PLARGE_INTEGER StreamOffset,
    uint32_t DirLength,
    p_void_t *Ptr,
    p_wchar_t Name,
    p_uint32_t pIndex,
    p_uint32_t CurrentOffset)
{
    p_directory_record_t Record = *Ptr;
    uint32_t Index;
  
  if (*CurrentOffset >= DirLength)
     return(STATUS_NO_MORE_ENTRIES);

  if (*CurrentOffset == 0)
  {
     Index = 0;
     Record = (p_directory_record_t)*Block;
     while (Index < *pIndex)
     {
       (*Ptr) += Record->RecordLength;
       (*CurrentOffset) += Record->RecordLength;
       Record = *Ptr;
       if (*Ptr - *Block >= BLOCKSIZE || Record->RecordLength == 0)
       {
	  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Map next sector\n");
	  CcUnpinData(*Context);
	  StreamOffset->QuadPart += BLOCKSIZE;
	  *CurrentOffset = ROUND_UP(*CurrentOffset, BLOCKSIZE);
	  if (!CcMapData(DeviceExt->StreamFileObject,
		         StreamOffset,
		         BLOCKSIZE, TRUE,
		         Context, Block))
	  {
	     DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "CcMapData() failed\n");
	     return(STATUS_UNSUCCESSFUL);
	  }
	  *Ptr = *Block;
	  Record = (PDIR_RECORD)*Ptr;
       }
       if (*CurrentOffset >= DirLength)
	 return(STATUS_NO_MORE_ENTRIES);

       Index++;
     }
  }

  if (*Ptr - *Block >= BLOCKSIZE || Record->RecordLength == 0)
  {
     DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Map next sector\n");
     CcUnpinData(*Context);
     StreamOffset->QuadPart += BLOCKSIZE;
     *CurrentOffset = ROUND_UP(*CurrentOffset, BLOCKSIZE);
     if (!CcMapData(DeviceExt->StreamFileObject,
		       StreamOffset,
		       BLOCKSIZE, TRUE,
		       Context, Block))
     {
       DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "CcMapData() failed\n");
       return(STATUS_UNSUCCESSFUL);
     }
     *Ptr = *Block;
     Record = (PDIR_RECORD)*Ptr;
  }
  if (*CurrentOffset >= DirLength)
     return(STATUS_NO_MORE_ENTRIES);

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Index %lu  RecordLength %lu  Offset %lu\n",
	 *pIndex, Record->RecordLength, *CurrentOffset);

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
	  CdfsSwapString(Name, Record->FileId, Record->FileIdLength);
	}
    }

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Name '%S'\n", Name);

  *Ptr = Record;

  return(STATUS_SUCCESS);
}

/*
 * FUNCTION: Find a file
 */
static return_t CdfsFindFile(PDEVICE_EXTENSION DeviceExt,
    p_file_data_t Fcb,
    p_file_data_t Parent,
    p_wchar_t FileToFind,
    p_uint32_t pDirIndex,
    p_uint32_t pOffset)
{
  wchar_t name[256];
  wchar_t TempStr[2];
  wchar_t ShortNameBuffer[13];
  UNICODE_STRING ShortName;
  UNICODE_STRING LongName;
  p_void_t Block;
  return_t Status;
  uint32_t len;
  uint32_t DirIndex;
  uint32_t Offset = 0;
  uint32_t Read;
  bool IsRoot;
  p_void_t Context = NULL;
  uint32_t DirSize;
  PDIR_RECORD Record;
  LARGE_INTEGER StreamOffset;
  bool HasSpaces;
//  GENERATE_NAME_CONTEXT NameContext;

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
      "FindFile(Parent %x, FileToFind '%S', DirIndex: %d)\n",
	 Parent, FileToFind, pDirIndex ? *pDirIndex : 0);
         
  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
      "FindFile: old Pathname %x, old Objectname %x)\n",
	 Fcb->PathName, Fcb->ObjectName);

  IsRoot = FALSE;
  DirIndex = 0;
  if (wcslen (FileToFind) == 0)
    {
      TempStr[0] = (wchar_t) '.';
      TempStr[1] = 0;
      FileToFind = (PWSTR)&TempStr;
    }

  if (Parent)
    {
      if (Parent->Entry.ExtentLocationL == DeviceExt->CdInfo.RootStart)
	{
	  IsRoot = TRUE;
	}
    }
  else
    {
      IsRoot = TRUE;
    }

  if (IsRoot == TRUE)
    {
      StreamOffset.QuadPart = (LONGLONG)DeviceExt->CdInfo.RootStart * (LONGLONG)BLOCKSIZE;
      DirSize = DeviceExt->CdInfo.RootSize;


      if (FileToFind[0] == 0 || (FileToFind[0] == '\\' && FileToFind[1] == 0)
	  || (FileToFind[0] == '.' && FileToFind[1] == 0))
	{
	  /* it's root : complete essentials fields then return ok */
	  RtlZeroMemory(Fcb, sizeof(FCB));

	  Fcb->PathName[0]='\\';
	  Fcb->ObjectName = &Fcb->PathName[1];
	  Fcb->Entry.ExtentLocationL = DeviceExt->CdInfo.RootStart;
	  Fcb->Entry.DataLengthL = DeviceExt->CdInfo.RootSize;
	  Fcb->Entry.FileFlags = 0x02; //FILE_ATTRIBUTE_DIRECTORY;

	  if (pDirIndex)
	    *pDirIndex = 0;
	  if (pOffset)
	    *pOffset = 0;
	  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
              "CdfsFindFile: new Pathname %S, new Objectname %S)\n",
              Fcb->PathName, Fcb->ObjectName);
	  return (STATUS_SUCCESS);
	}
    }
  else
    {
      StreamOffset.QuadPart = (LONGLONG)Parent->Entry.ExtentLocationL * (LONGLONG)BLOCKSIZE;
      DirSize = Parent->Entry.DataLengthL;
    }

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
      "StreamOffset %I64u  DirSize %lu\n", StreamOffset.QuadPart, DirSize);

  if (pDirIndex && (*pDirIndex))
    DirIndex = *pDirIndex;

  if (pOffset && (*pOffset))
  {
     Offset = *pOffset;
     StreamOffset.QuadPart += ROUND_DOWN(Offset, BLOCKSIZE);
  }

  if(!CcMapData(DeviceExt->StreamFileObject, &StreamOffset,
		BLOCKSIZE, TRUE, &Context, &Block))
  {
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "CcMapData() failed\n");
    return(STATUS_UNSUCCESSFUL);
  }

  Record = (PDIR_RECORD) (Block + Offset % BLOCKSIZE);
  if (Offset)
  {  
     Offset += Record->RecordLength;
     Record = (PVOID)Record + Record->RecordLength;
  }
  while(TRUE)
    {
      DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
          "RecordLength %u  ExtAttrRecordLength %u  NameLength %u\n",
	     Record->RecordLength, Record->ExtAttrRecordLength, Record->FileIdLength);

      Status = CdfsGetEntryName(DeviceExt, &Context, &Block, &StreamOffset,
	                        DirSize, (PVOID*)&Record, name, &DirIndex, &Offset);

      if (Status == STATUS_NO_MORE_ENTRIES)
	{
	  break;
	}
      else if (Status == STATUS_UNSUCCESSFUL)
	{
	  /* Note: the directory cache has already been unpinned */
	  return(Status);
	}

      DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Name '%S'\n", name);

      RtlInitUnicodeString(&LongName, name);
      ShortName.Length = 0;
      ShortName.MaximumLength = 26;
      ShortName.Buffer = ShortNameBuffer;

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

      if (wstrcmpjoki(name, FileToFind) ||
	  wstrcmpjoki(ShortNameBuffer, FileToFind))
	{
	  if (Parent && Parent->PathName)
	    {
	      len = wcslen(Parent->PathName);
	      memcpy(Fcb->PathName, Parent->PathName, len*sizeof(WCHAR));
	      Fcb->ObjectName=&Fcb->PathName[len];
	      if (len != 1 || Fcb->PathName[0] != '\\')
		{
		  Fcb->ObjectName[0] = '\\';
		  Fcb->ObjectName = &Fcb->ObjectName[1];
		}
	    }
	  else
	    {
	      Fcb->ObjectName=Fcb->PathName;
	      Fcb->ObjectName[0]='\\';
	      Fcb->ObjectName=&Fcb->ObjectName[1];
	    }

	  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "PathName '%S'  ObjectName '%S'\n", Fcb->PathName, Fcb->ObjectName);

	  memory_copy (&Fcb->Entry, Record, sizeof(DIR_RECORD));
	  wcsncpy(Fcb->ObjectName, name, MAX_PATH);

	  /* Copy short name */
	  Fcb->ShortNameLength = ShortName.Length;
	  memory_copy (Fcb->ShortName, ShortName.Buffer, ShortName.Length);

	  if (pDirIndex)
	    *pDirIndex = DirIndex;
	  if (pOffset)
	    *pOffset = Offset;

	  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "FindFile: new Pathname %S, new Objectname %S, DirIndex %d\n",
		 Fcb->PathName, Fcb->ObjectName, DirIndex);

	  CcUnpinData(Context);

	  return(STATUS_SUCCESS);
	}


      Offset += Record->RecordLength;
      Record = (PVOID)Record + Record->RecordLength;
      DirIndex++;

    }

  CcUnpinData(Context);

  if (pDirIndex)
    *pDirIndex = DirIndex;

  if (pOffset)
    *pOffset = Offset;

  return(STATUS_UNSUCCESSFUL);
}


static return_t CdfsGetNameInformation(
    p_file_data_t Fcb,
		       PDEVICE_EXTENSION DeviceExt,
		       PFILE_NAMES_INFORMATION Info,
		       uint32_t BufferLength)
{
  uint32_t Length;

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "CdfsGetNameInformation() called\n");

  Length = wcslen(Fcb->ObjectName) * sizeof (wchar_t);
  if ((sizeof (FILE_BOTH_DIRECTORY_INFORMATION) + Length) > BufferLength)
    return(STATUS_BUFFER_OVERFLOW);

  Info->FileNameLength = Length;
  Info->NextEntryOffset =
    ROUND_UP(sizeof(FILE_BOTH_DIRECTORY_INFORMATION) + Length, 4);
  memory_copy (Info->FileName, Fcb->ObjectName, Length);

  return(STATUS_SUCCESS);
}


static return_t CdfsGetDirectoryInformation (
    p_file_data_t Fcb,
			    PDEVICE_EXTENSION DeviceExt,
			    PFILE_DIRECTORY_INFORMATION Info,
			    uint32_t BufferLength)
{
  uint32_t Length;

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "CdfsGetDirectoryInformation() called\n");

  Length = wcslen(Fcb->ObjectName) * sizeof (wchar_t);
  if ((sizeof (FILE_BOTH_DIRECTORY_INFORMATION) + Length) > BufferLength)
    return(STATUS_BUFFER_OVERFLOW);

  Info->FileNameLength = Length;
  Info->NextEntryOffset =
    ROUND_UP(sizeof(FILE_BOTH_DIRECTORY_INFORMATION) + Length, 4);
  memory_copy (Info->FileName, Fcb->ObjectName, Length);

  /* Convert file times */
  CdfsDateTimeToFileTime(Fcb,
			 &Info->CreationTime);
  CdfsDateTimeToFileTime(Fcb,
			 &Info->LastAccessTime);
  CdfsDateTimeToFileTime(Fcb,
			 &Info->LastWriteTime);
  CdfsDateTimeToFileTime(Fcb,
			 &Info->ChangeTime);

  /* Convert file flags */
  CdfsFileFlagsToAttributes(Fcb,
			    &Info->FileAttributes);

  Info->EndOfFile.QuadPart = Fcb->Entry.DataLengthL;

  /* Make AllocSize a rounded up multiple of the sector size */
  Info->AllocationSize.QuadPart = ROUND_UP(Fcb->Entry.DataLengthL, BLOCKSIZE);

//  Info->FileIndex=;

  return(STATUS_SUCCESS);
}


static return_t CdfsGetFullDirectoryInformation (
    p_file_data Fcb,
    PDEVICE_EXTENSION DeviceExt,
    PFILE_FULL_DIRECTORY_INFORMATION Info,
    uint32_t BufferLength)
{
  uint32_t Length;

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
      "CdfsGetFullDirectoryInformation() called\n");

  Length = wcslen(Fcb->ObjectName) * sizeof (wchar_t);
  
  if ((sizeof (FILE_BOTH_DIRECTORY_INFORMATION) + Length) > BufferLength)
    return(STATUS_BUFFER_OVERFLOW);

  Info->FileNameLength = Length;
  Info->NextEntryOffset =
    ROUND_UP(sizeof(FILE_BOTH_DIRECTORY_INFORMATION) + Length, 4);
  memory_copy (Info->FileName, Fcb->ObjectName, Length);

  /* Convert file times */
  CdfsDateTimeToFileTime(Fcb,
			 &Info->CreationTime);
  CdfsDateTimeToFileTime(Fcb,
			 &Info->LastAccessTime);
  CdfsDateTimeToFileTime(Fcb,
			 &Info->LastWriteTime);
  CdfsDateTimeToFileTime(Fcb,
			 &Info->ChangeTime);

  /* Convert file flags */
  CdfsFileFlagsToAttributes(Fcb,
			    &Info->FileAttributes);

  Info->EndOfFile.QuadPart = Fcb->Entry.DataLengthL;

  /* Make AllocSize a rounded up multiple of the sector size */
  Info->AllocationSize.QuadPart = ROUND_UP(Fcb->Entry.DataLengthL, BLOCKSIZE);

//  Info->FileIndex=;
  Info->EaSize = 0;

  return(STATUS_SUCCESS);
}


static return_t CdfsGetBothDirectoryInformation (
    p_file_data_t Fcb,
    PDEVICE_EXTENSION DeviceExt,
    PFILE_BOTH_DIRECTORY_INFORMATION Info,
    uint32_t BufferLength)
{
  uint32_t Length;

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "CdfsGetBothDirectoryInformation() called\n");

  Length = wcslen(Fcb->ObjectName) * sizeof(WCHAR);
  if ((sizeof (FILE_BOTH_DIRECTORY_INFORMATION) + Length) > BufferLength)
    return(STATUS_BUFFER_OVERFLOW);

  Info->FileNameLength = Length;
  Info->NextEntryOffset =
    ROUND_UP (sizeof(FILE_BOTH_DIRECTORY_INFORMATION) + Length, 4);
    
  memory_copy (Info->FileName, Fcb->ObjectName, Length);

  /* Convert file times */
  CdfsDateTimeToFileTime(Fcb,
			 &Info->CreationTime);
  CdfsDateTimeToFileTime(Fcb,
			 &Info->LastAccessTime);
  CdfsDateTimeToFileTime(Fcb,
			 &Info->LastWriteTime);
  CdfsDateTimeToFileTime(Fcb,
			 &Info->ChangeTime);

  /* Convert file flags */
  CdfsFileFlagsToAttributes(Fcb,
			    &Info->FileAttributes);

  Info->EndOfFile.QuadPart = Fcb->Entry.DataLengthL;

  /* Make AllocSize a rounded up multiple of the sector size */
  Info->AllocationSize.QuadPart = ROUND_UP(Fcb->Entry.DataLengthL, BLOCKSIZE);

//  Info->FileIndex=;
  Info->EaSize = 0;

  /* Copy short name */
  Info->ShortNameLength = Fcb->ShortNameLength;
  memory_copy (Info->ShortName, Fcb->ShortName, Fcb->ShortNameLength);

  return(STATUS_SUCCESS);
}


static return_t CdfsQueryDirectory (
    PDEVICE_OBJECT DeviceObject,
		   PIRP Irp)
{
  PDEVICE_EXTENSION DeviceExtension;
  LONG BufferLength = 0;
  PUNICODE_STRING SearchPattern = NULL;
  FILE_INFORMATION_CLASS FileInformationClass;
  uint32_t FileIndex = 0;
  p_uint8_t Buffer = NULL;
  PFILE_NAMES_INFORMATION Buffer0 = NULL;
  PFCB Fcb;
//  PCCB Ccb;
  FCB TempFcb;
  bool First = FALSE;
  PEXTENDED_IO_STACK_LOCATION Stack;
  PFILE_OBJECT FileObject;
  return_t Status = STATUS_SUCCESS;

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "CdfsQueryDirectory() called\n");

  DeviceExtension = DeviceObject->DeviceExtension;
  Stack = (PEXTENDED_IO_STACK_LOCATION) IoGetCurrentIrpStackLocation(Irp);
  FileObject = Stack->FileObject;

//  Ccb = (PCCB)FileObject->FsContext2;
  Fcb = (PFCB)FileObject->FsContext;

  /* Obtain the callers parameters */
  BufferLength = Stack->Parameters.QueryDirectory.Length;
  SearchPattern = Stack->Parameters.QueryDirectory.FileName;
  FileInformationClass =
    Stack->Parameters.QueryDirectory.FileInformationClass;
  FileIndex = Stack->Parameters.QueryDirectory.FileIndex;


  if (SearchPattern != NULL)
    {
      if (!Ccb->DirectorySearchPattern)
	{
	  First = TRUE;
	  Ccb->DirectorySearchPattern =
	    ExAllocatePool(NonPagedPool, SearchPattern->Length + sizeof(WCHAR));
	  if (!Ccb->DirectorySearchPattern)
	    {
	      return(STATUS_INSUFFICIENT_RESOURCES);
	    }

	  memcpy(Ccb->DirectorySearchPattern,
		 SearchPattern->Buffer,
		 SearchPattern->Length);
	  Ccb->DirectorySearchPattern[SearchPattern->Length / sizeof(WCHAR)] = 0;
	}
    }
  else if (!Ccb->DirectorySearchPattern)
    {
      First = TRUE;
      Ccb->DirectorySearchPattern = ExAllocatePool(NonPagedPool, 2 * sizeof(WCHAR));
      if (!Ccb->DirectorySearchPattern)
	{
	  return(STATUS_INSUFFICIENT_RESOURCES);
	}
      Ccb->DirectorySearchPattern[0] = L'*';
      Ccb->DirectorySearchPattern[1] = 0;
    }
  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Search pattern '%S'\n", Ccb->DirectorySearchPattern);

  /* Determine directory index */
  if (Stack->Flags & SL_INDEX_SPECIFIED)
    {
      Ccb->Entry = Ccb->CurrentByteOffset.u.LowPart;
      Ccb->Offset = 0;
    }
  else if (First || (Stack->Flags & SL_RESTART_SCAN))
    {
      Ccb->Entry = 0;
      Ccb->Offset = 0;
    }

  /* Determine Buffer for result */
  if (Irp->MdlAddress)
    {
      Buffer = MmGetSystemAddressForMdl(Irp->MdlAddress);
    }
  else
    {
      Buffer = Irp->UserBuffer;
    }
  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Buffer=%x tofind=%S\n", Buffer, Ccb->DirectorySearchPattern);

  TempFcb.ObjectName = TempFcb.PathName;
  while (Status == STATUS_SUCCESS && BufferLength > 0)
    {
      Status = CdfsFindFile(DeviceExtension,
			    &TempFcb,
			    Fcb,
			    Ccb->DirectorySearchPattern,
			    &Ccb->Entry,
			    &Ccb->Offset);
      DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Found %S, Status=%x, entry %x\n", TempFcb.ObjectName, Status, Ccb->Entry);

      if (NT_SUCCESS(Status))
	{
	  switch (FileInformationClass)
	    {
	      case FileNameInformation:
		Status = CdfsGetNameInformation(&TempFcb,
						DeviceExtension,
						(PFILE_NAMES_INFORMATION)Buffer,
						BufferLength);
		break;

	      case FileDirectoryInformation:
		Status = CdfsGetDirectoryInformation(&TempFcb,
						     DeviceExtension,
						     (PFILE_DIRECTORY_INFORMATION)Buffer,
						     BufferLength);
		break;

	      case FileFullDirectoryInformation:
		Status = CdfsGetFullDirectoryInformation(&TempFcb,
							 DeviceExtension,
							 (PFILE_FULL_DIRECTORY_INFORMATION)Buffer,
							 BufferLength);
		break;

	      case FileBothDirectoryInformation:
		Status = CdfsGetBothDirectoryInformation(&TempFcb,
							 DeviceExtension,
							 (PFILE_BOTH_DIRECTORY_INFORMATION)Buffer,
							 BufferLength);
		break;

	      default:
		Status = STATUS_INVALID_INFO_CLASS;
	    }

	  if (Status == STATUS_BUFFER_OVERFLOW)
	    {
	      if (Buffer0)
		{
		  Buffer0->NextEntryOffset = 0;
		}
	      break;
	    }
	}
      else
	{
	  if (Buffer0)
	    {
	      Buffer0->NextEntryOffset = 0;
	    }

	  if (First)
	    {
	      Status = STATUS_NO_SUCH_FILE;
	    }
	  else
	    {
	      Status = STATUS_NO_MORE_FILES;
	    }
	  break;
	}

      Buffer0 = (PFILE_NAMES_INFORMATION)Buffer;
      Buffer0->FileIndex = FileIndex++;
      Ccb->Entry++;

      if (Stack->Flags & SL_RETURN_SINGLE_ENTRY)
	{
	  break;
	}
      BufferLength -= Buffer0->NextEntryOffset;
      Buffer += Buffer0->NextEntryOffset;
    }

  if (Buffer0)
    {
      Buffer0->NextEntryOffset = 0;
    }

  if (FileIndex > 0)
    {
      Status = STATUS_SUCCESS;
    }

  return(Status);
}


