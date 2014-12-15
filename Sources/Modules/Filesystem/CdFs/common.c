#include <enviroment.h>

#include "cdfs.h"

#define DEBUG_MODULE_NAME L"CDFS"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#ifndef __STORM_KERNEL__
#   define DEBUG_SUPPLIER (cdfs_debug_supplier)
#endif

return_t
CdfsReadSectors(IN PDEVICE_OBJECT DeviceObject,
		IN uint32_t DiskSector,
		IN uint32_t SectorCount,
		IN OUT p_uint8_t Buffer)
{
  IO_STATUS_BLOCK IoStatus;
  LARGE_INTEGER Offset;
  uint32_t BlockSize;
  KEVENT Event;
  PIRP Irp;
  return_t Status;

  KeInitializeEvent(&Event,
		    NotificationEvent,
		    FALSE);

  Offset.u.LowPart = DiskSector << 11;
  Offset.u.HighPart = DiskSector >> 21;

  BlockSize = BLOCKSIZE * SectorCount;

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "CdfsReadSectors(DeviceObject %x, DiskSector %d, Buffer %x)\n",
	 DeviceObject, DiskSector, Buffer);
  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Offset %I64x BlockSize %ld\n",
	 Offset.QuadPart,
	 BlockSize);

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Building synchronous FSD Request...\n");
  Irp = IoBuildSynchronousFsdRequest(IRP_MJ_READ,
				     DeviceObject,
				     Buffer,
				     BlockSize,
				     &Offset,
				     &Event,
				     &IoStatus);
  if (Irp == NULL)
    {
      DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "IoBuildSynchronousFsdRequest failed\n");
      return(STATUS_INSUFFICIENT_RESOURCES);
    }

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Calling IO Driver... with irp %x\n", Irp);
  Status = IoCallDriver(DeviceObject, Irp);

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Waiting for IO Operation for %x\n", Irp);
  if (Status == STATUS_PENDING)
    {
      DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Operation pending\n");
      KeWaitForSingleObject(&Event, Suspended, KernelMode, FALSE, NULL);
      DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Getting IO Status... for %x\n", Irp);
      Status = IoStatus.Status;
    }

  if (!NT_SUCCESS(Status))
    {
      if (Status == STATUS_VERIFY_REQUIRED)
        {
	  PDEVICE_OBJECT DeviceToVerify;
	  return_t NewStatus;

	  DPRINT1("STATUS_VERIFY_REQUIRED\n");
	  DeviceToVerify = IoGetDeviceToVerify(PsGetCurrentThread());
	  IoSetDeviceToVerify(PsGetCurrentThread(), NULL);

	  NewStatus = IoVerifyVolume(DeviceToVerify, FALSE);
	  DPRINT1("IoVerifyVolume() retuned (Status %lx)\n", NewStatus);
        }

      DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "CdfsReadSectors() failed (Status %x)\n", Status);
      DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "(DeviceObject %x, DiskSector %x, Buffer %x, Offset 0x%I64x)\n",
	     DeviceObject, DiskSector, Buffer,
	     Offset.QuadPart);
      return(Status);
    }

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Block request succeeded for %x\n", Irp);

  return(STATUS_SUCCESS);
}


return_t
CdfsReadRawSectors(IN PDEVICE_OBJECT DeviceObject,
		   IN uint32_t DiskSector,
		   IN uint32_t SectorCount,
		   IN OUT p_uint8_t Buffer)
{
  PIO_STACK_LOCATION Stack;
  IO_STATUS_BLOCK IoStatus;
  LARGE_INTEGER Offset;
  uint32_t BlockSize;
  KEVENT Event;
  PIRP Irp;
  return_t Status;

  KeInitializeEvent(&Event,
		    NotificationEvent,
		    FALSE);

  Offset.u.LowPart = DiskSector << 11;
  Offset.u.HighPart = DiskSector >> 21;

  BlockSize = BLOCKSIZE * SectorCount;

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "CdfsReadSectors(DeviceObject %x, DiskSector %d, Buffer %x)\n",
	 DeviceObject, DiskSector, Buffer);
  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Offset %I64x BlockSize %ld\n",
	 Offset.QuadPart,
	 BlockSize);

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Building synchronous FSD Request...\n");
  Irp = IoBuildSynchronousFsdRequest(IRP_MJ_READ,
				     DeviceObject,
				     Buffer,
				     BlockSize,
				     &Offset,
				     &Event,
				     &IoStatus);
  if (Irp == NULL)
    {
      DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "IoBuildSynchronousFsdRequest failed\n");
      return(STATUS_INSUFFICIENT_RESOURCES);
    }

//  Stack = IoGetCurrentIrpStackLocation(Irp);
//  Stack->Flags |= SL_OVERRIDE_VERIFY_VOLUME;

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Calling IO Driver... with irp %x\n", Irp);
  Status = IoCallDriver(DeviceObject, Irp);

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Waiting for IO Operation for %x\n", Irp);
  if (Status == STATUS_PENDING)
    {
      DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Operation pending\n");
      KeWaitForSingleObject(&Event, Suspended, KernelMode, FALSE, NULL);
      DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Getting IO Status... for %x\n", Irp);
      Status = IoStatus.Status;
    }

  if (!NT_SUCCESS(Status))
    {
      DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "CdfsReadSectors() failed (Status %x)\n", Status);
      DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "(DeviceObject %x, DiskSector %x, Buffer %x, Offset 0x%I64x)\n",
	     DeviceObject, DiskSector, Buffer,
	     Offset.QuadPart);
      return(Status);
    }

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Block request succeeded for %x\n", Irp);

  return(STATUS_SUCCESS);
}

return_t
CdfsDeviceIoControl (IN PDEVICE_OBJECT DeviceObject,
		     IN uint32_t CtlCode,
		     IN PVOID InputBuffer,
		     IN uint32_t InputBufferSize,
		     IN OUT PVOID OutputBuffer, 
		     IN OUT p_uint32_t pOutputBufferSize)
{
  uint32_t OutputBufferSize = 0;
  KEVENT Event;
  PIRP Irp;
  IO_STATUS_BLOCK IoStatus;
  return_t Status;

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "CdfsDeviceIoControl(DeviceObject %x, CtlCode %x, "
	 "InputBuffer %x, InputBufferSize %x, OutputBuffer %x, " 
	 "POutputBufferSize %x (%x)\n", DeviceObject, CtlCode, 
	 InputBuffer, InputBufferSize, OutputBuffer, pOutputBufferSize, 
	 pOutputBufferSize ? *pOutputBufferSize : 0);

  if (pOutputBufferSize)
  {
     OutputBufferSize = *pOutputBufferSize;
  }

  KeInitializeEvent (&Event, NotificationEvent, FALSE);

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Building device I/O control request ...\n");
  Irp = IoBuildDeviceIoControlRequest(CtlCode, 
				      DeviceObject, 
				      InputBuffer, 
				      InputBufferSize, 
				      OutputBuffer,
				      OutputBufferSize, 
				      FALSE, 
				      &Event, 
				      &IoStatus);
  if (Irp == NULL)
  {
     DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "IoBuildDeviceIoControlRequest failed\n");
     return STATUS_INSUFFICIENT_RESOURCES;
  }

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Calling IO Driver... with irp %x\n", Irp);
  Status = IoCallDriver(DeviceObject, Irp);

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Waiting for IO Operation for %x\n", Irp);
  if (Status == STATUS_PENDING)
  {
     DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Operation pending\n");
     KeWaitForSingleObject (&Event, Suspended, KernelMode, FALSE, NULL);
     DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Getting IO Status... for %x\n", Irp);

     Status = IoStatus.Status;
  }
  if (OutputBufferSize)
  {
     *pOutputBufferSize = OutputBufferSize;
  }
  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Returning Status %x\n", Status);
  return Status;
}

/* EOF */
