
#include <ddk/ntddk.h>
#include <ntos/minmax.h>

#define NDEBUG
#include <debug.h>

#include "cdfs.h"


/* GLOBALS *******************************************************************/

#define ROUND_UP(N, S) ((((N) + (S) - 1) / (S)) * (S))
#define ROUND_DOWN(N, S) ((N) - ((N) % (S)))


/* FUNCTIONS ****************************************************************/

/*
 * FUNCTION: Reads data from a file
 */
return_t CdfsReadFile (PDEVICE_EXTENSION DeviceExt,
    PFILE_OBJECT FileObject,
    PUCHAR Buffer,
    ULONG Length,
    ULONG ReadOffset,
    ULONG IrpFlags,
    PULONG LengthRead)
{
  NTSTATUS Status = STATUS_SUCCESS;
  PUCHAR TempBuffer;
  ULONG TempLength;
  PCCB Ccb;
  PFCB Fcb;

  DPRINT("CdfsReadFile(ReadOffset %lu  Length %lu)\n", ReadOffset, Length);

  *LengthRead = 0;

  if (Length == 0)
    return(STATUS_SUCCESS);

  Ccb = (PCCB)FileObject->FsContext2;
  Fcb = (PFCB)FileObject->FsContext;

  if (ReadOffset >= Fcb->Entry.DataLengthL)
    return(STATUS_END_OF_FILE);

  DPRINT("Reading %d bytes at %d\n", Length, ReadOffset);

  if (!(IrpFlags & (IRP_NOCACHE|IRP_PAGING_IO)))
    {
      LARGE_INTEGER FileOffset;
      IO_STATUS_BLOCK IoStatus;

      if (ReadOffset + Length > Fcb->Entry.DataLengthL)
         Length = Fcb->Entry.DataLengthL - ReadOffset;
      if (FileObject->PrivateCacheMap == NULL)
      {
	  CcRosInitializeFileCache(FileObject, PAGE_SIZE);
      }

      FileOffset.QuadPart = (LONGLONG)ReadOffset;
      CcCopyRead(FileObject,
		 &FileOffset,
		 Length,
		 TRUE,
		 Buffer,
		 &IoStatus);
      *LengthRead = IoStatus.Information;

      return(IoStatus.Status);
    }

  if ((ReadOffset % BLOCKSIZE) != 0 || (Length % BLOCKSIZE) != 0)
    {
      return STATUS_INVALID_PARAMETER;
    }
  if (ReadOffset + Length > ROUND_UP(Fcb->Entry.DataLengthL, BLOCKSIZE))
    Length = ROUND_UP(Fcb->Entry.DataLengthL, BLOCKSIZE) - ReadOffset;

  Status = CdfsReadSectors(DeviceExt->StorageDevice,
			   Fcb->Entry.ExtentLocationL + (ReadOffset / BLOCKSIZE),
			   Length / BLOCKSIZE,
			   Buffer);
  if (NT_SUCCESS(Status))
    {
      *LengthRead = Length;
      if (Length + ReadOffset > Fcb->Entry.DataLengthL)
      {
	memset(Buffer + Fcb->Entry.DataLengthL - ReadOffset, 
	       0, Length + ReadOffset - Fcb->Entry.DataLengthL);
      }
    }

    return (Status);
}

return_t CdfsWriteFile(PDEVICE_OBJECT DeviceObject,
	  PIRP Irp)
{
    DPRINT("CdfsWrite(DeviceObject %x Irp %x)\n",DeviceObject,Irp);

    return -1;
}

/* EOF */
