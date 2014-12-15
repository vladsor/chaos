#include <enviroment.h>

#include "cdfs.h"

#define DEBUG_MODULE_NAME L"CDFS"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#ifndef __STORM_KERNEL__
#   define DEBUG_SUPPLIER (cdfs_debug_supplier)
#endif


/* FUNCTIONS ****************************************************************/

/*
 * FUNCTION: Reads data from a file
 */
return_t CdfsReadFile (
    p_file_data_t Fcb,
    p_uint8_t Buffer,
    uint32_t Length,
    uint32_t ReadOffset,
    uint32_t IrpFlags,
    p_uint32_t LengthRead)
{
  return_t Status = STATUS_SUCCESS;
  p_uint8_t TempBuffer;
  uint32_t TempLength;
//  PCCB Ccb;
  

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
      "CdfsReadFile(ReadOffset %lu  Length %lu)\n", 
      ReadOffset, Length);

  *LengthRead = 0;

    if (Length == 0)
    {
        return STORM_RETURN_SUCCESS;
    }

//  Ccb = (PCCB)FileObject->FsContext2;
//  Fcb = (PFCB)FileObject->FsContext;

    if (ReadOffset >= Fcb->Entry.DataLengthL)
    {
        return CDFS_RETURN_END_OF_FILE;
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "Reading %d bytes at %d\n", 
        Length, ReadOffset);
/*
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
*/
    if ((ReadOffset % BLOCKSIZE) != 0 || (Length % BLOCKSIZE) != 0)
    {
        return STORM_RETURN_INVALID_PARAMETER;
    }
    
    if (ReadOffset + Length > ROUND_UP(Fcb->Entry.DataLengthL, BLOCKSIZE))
    {
        Length = ROUND_UP(Fcb->Entry.DataLengthL, BLOCKSIZE) - ReadOffset;
    }
    
    Status = CdfsReadSectors (Fcb->StorageDevice,
        Fcb->Entry.ExtentLocationL + (ReadOffset / BLOCKSIZE),
        Length / BLOCKSIZE,
        Buffer);
                           
    if (Status == STORM_RETURN_SUCCESS)
    {
        (*LengthRead) = Length;
        
        if (Length + ReadOffset > Fcb->Entry.DataLengthL)
        {
            memory_clear (Buffer + Fcb->Entry.DataLengthL - ReadOffset, 
            Length + ReadOffset - Fcb->Entry.DataLengthL);
        }
    }

    return (Status);
}
/*
return_t CdfsWriteFile (p_file_data_t Fcb)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "CdfsWrite(DeviceObject %x Irp %x)\n",DeviceObject,Irp);

    return -1;
}
*/

