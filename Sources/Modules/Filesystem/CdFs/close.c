#include <enviroment.h>

#include "cdfs.h"

#define DEBUG_MODULE_NAME L"CDFS"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#ifndef __STORM_KERNEL__
#   define DEBUG_SUPPLIER (cdfs_debug_supplier)
#endif

return_t CdfsCloseFile(PDEVICE_EXTENSION DeviceExt,
	      PFILE_OBJECT FileObject)
/*
 * FUNCTION: Closes a file
 */
{
//  PCCB Ccb;
  
  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "CdfsCloseFile(DeviceExt %x, FileObject %x)\n",
	 DeviceExt,
	 FileObject);
/*
  Ccb = (PCCB)(FileObject->FsContext2);

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Ccb %x\n", Ccb);
  if (Ccb == NULL)
    {
      return(STATUS_SUCCESS);
    }
*/
  FileObject->FsContext2 = NULL;

  if (FileObject->FileName.Buffer)
    {
      // This a FO, that was created outside from FSD.
      // Some FO's are created with IoCreateStreamFileObject() insid from FSD.
      // This FO's don't have a FileName.
      CdfsReleaseFCB(DeviceExt, FileObject->FsContext);
    }

  if (Ccb->DirectorySearchPattern)
    {
      ExFreePool(Ccb->DirectorySearchPattern);
    }
  ExFreePool(Ccb);

  return(STATUS_SUCCESS);
}


return_t CdfsClose(PDEVICE_OBJECT DeviceObject,
	  PIRP Irp)
{
  PDEVICE_EXTENSION DeviceExtension;
  PIO_STACK_LOCATION Stack;
  PFILE_OBJECT FileObject;
  return_t Status;

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "CdfsClose() called\n");

  if (DeviceObject == CdfsGlobalData->DeviceObject)
    {
      DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Closing file system\n");
      Status = STATUS_SUCCESS;
      goto ByeBye;
    }

  Stack = IoGetCurrentIrpStackLocation(Irp);
  FileObject = Stack->FileObject;
  DeviceExtension = DeviceObject->DeviceExtension;

  Status = CdfsCloseFile(DeviceExtension,FileObject);

ByeBye:
  Irp->IoStatus.Status = Status;
  Irp->IoStatus.Information = 0;

  IoCompleteRequest(Irp, IO_NO_INCREMENT);
  return(Status);
}

/* EOF */

