#include <enviroment.h>

#include "cdfs.h"

#define DEBUG_MODULE_NAME L"CDFS"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#ifndef __STORM_KERNEL__
#   define DEBUG_SUPPLIER (cdfs_debug_supplier)
#endif

/* FUNCTIONS ****************************************************************/

static inline int msf_to_lba (uint8_t m, uint8_t s, uint8_t f)
{
   return (((m * 60) + s) * 75 + f) - 150;
}

static void CdfsGetPVDData (p_uint8_t Buffer, p_cd_info_t CdInfo)
{
    p_primary_volume_descriptor_t Pvd;
    uint32_t i;
    p_uint8_t pc;
    p_wchar_t pw;

    union
    {
        uint32_t Value;
        uint8_t Part[4];
    } Serial;

  Pvd = (p_primary_volume_descriptor_t) Buffer;

  /* Calculate the volume serial number */
  Serial.Value = 0;
  for (i = 0; i < 2048; i += 4)
    {
      /* DON'T optimize this to uint32_t!!! (breaks overflow) */
      Serial.Part[0] += Buffer[i+3];
      Serial.Part[1] += Buffer[i+2];
      Serial.Part[2] += Buffer[i+1];
      Serial.Part[3] += Buffer[i+0];
    }
  CdInfo->SerialNumber = Serial.Value;

  /* Extract the volume label */
  pc = Pvd->VolumeId;
  pw = CdInfo->VolumeLabel;
  for (i = 0; i < MAXIMUM_VOLUME_LABEL_LENGTH && *pc != ' '; i++)
    {
      *pw++ = (WCHAR)*pc++;
    }
  *pw = 0;
  CdInfo->VolumeLabelLength = i;

  CdInfo->VolumeSpaceSize = Pvd->VolumeSpaceSizeL;
  CdInfo->RootStart = Pvd->RootDirRecord.ExtentLocationL;
  CdInfo->RootSize = Pvd->RootDirRecord.DataLengthL;

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
      "VolumeSerial: %08lx\n", CdInfo->SerialNumber);
  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
      "VolumeLabel: '%S'\n", CdInfo->VolumeLabel);
  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
      "VolumeLabelLength: %lu\n", CdInfo->VolumeLabelLength);
  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
      "VolumeSize: %lu\n", Pvd->VolumeSpaceSizeL);
  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
      "RootStart: %lu\n", Pvd->RootDirRecord.ExtentLocationL);
  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
      "RootSize: %lu\n", Pvd->RootDirRecord.DataLengthL);

#if 0
  DbgPrint("******** PVD **********\n");
  DbgPrint("VdType:               %d\n", Pvd->VdType);
  DbgPrint("StandardId:           '%.*s'\n", 5, Pvd->StandardId);
  DbgPrint("VdVersion:            %d\n", Pvd->VdVersion);
  DbgPrint("SystemId:             '%.*s'\n", 32, Pvd->SystemId);
  DbgPrint("VolumeId:             '%.*s'\n", 32, Pvd->VolumeId);
  DbgPrint("VolumeSpaceSizeL:     %d (%x)\n", Pvd->VolumeSpaceSizeL, Pvd->VolumeSpaceSizeL);
  DbgPrint("VolumeSpaceSizeM:     %d (%x)\n", Pvd->VolumeSpaceSizeM, Pvd->VolumeSpaceSizeM);
  DbgPrint("VolumeSetSize:        %d (%x)\n", Pvd->VolumeSequenceNumber, Pvd->VolumeSequenceNumber);
  DbgPrint("VolumeSequenceNumber: %d (%x)\n", Pvd->VolumeSequenceNumber, Pvd->VolumeSequenceNumber);
  DbgPrint("LogicalBlockSize:     %d (%x)\n", Pvd->LogicalBlockSize, Pvd->LogicalBlockSize);
  DbgPrint("PathTableSizeL:       %d (%x)\n", Pvd->PathTableSizeL, Pvd->PathTableSizeL);
  DbgPrint("PathTableSizeM:       %d (%x)\n", Pvd->PathTableSizeM, Pvd->PathTableSizeM);
  DbgPrint("LPathTablePos:        %d (%x)\n", Pvd->LPathTablePos, Pvd->LPathTablePos);
  DbgPrint("LOptPathTablePos:     %d (%x)\n", Pvd->LOptPathTablePos, Pvd->LOptPathTablePos);
  DbgPrint("MPathTablePos:        %d (%x)\n", Pvd->MPathTablePos, Pvd->MPathTablePos);
  DbgPrint("MOptPathTablePos:     %d (%x)\n", Pvd->MOptPathTablePos, Pvd->MOptPathTablePos);
  DbgPrint("VolumeSetIdentifier:  '%.*s'\n", 128, Pvd->VolumeSetIdentifier);
  DbgPrint("PublisherIdentifier:  '%.*s'\n", 128, Pvd->PublisherIdentifier);
  DbgPrint("******** Root *********\n");
  DbgPrint("RecordLength:         %d\n", Pvd->RootDirRecord.RecordLength);
  DbgPrint("ExtAttrRecordLength:  %d\n", Pvd->RootDirRecord.ExtAttrRecordLength);
  DbgPrint("ExtentLocationL:      %d\n", Pvd->RootDirRecord.ExtentLocationL);
  DbgPrint("DataLengthL:          %d\n", Pvd->RootDirRecord.DataLengthL);
  DbgPrint("Year:                 %d\n", Pvd->RootDirRecord.Year);
  DbgPrint("Month:                %d\n", Pvd->RootDirRecord.Month);
  DbgPrint("Day:                  %d\n", Pvd->RootDirRecord.Day);
  DbgPrint("Hour:                 %d\n", Pvd->RootDirRecord.Hour);
  DbgPrint("Minute:               %d\n", Pvd->RootDirRecord.Minute);
  DbgPrint("Second:               %d\n", Pvd->RootDirRecord.Second);
  DbgPrint("TimeZone:             %d\n", Pvd->RootDirRecord.TimeZone);
  DbgPrint("FileFlags:            %d\n", Pvd->RootDirRecord.FileFlags);
  DbgPrint("FileUnitSize:         %d\n", Pvd->RootDirRecord.FileUnitSize);
  DbgPrint("InterleaveGapSize:    %d\n", Pvd->RootDirRecord.InterleaveGapSize);
  DbgPrint("VolumeSequenceNumber: %d\n", Pvd->RootDirRecord.VolumeSequenceNumber);
  DbgPrint("FileIdLength:         %d\n", Pvd->RootDirRecord.FileIdLength);
  DbgPrint("FileId:               '%.*s'\n", Pvd->RootDirRecord.FileId);
  DbgPrint("***********************\n");
#endif
}


static void CdfsGetSVDData (p_uint8_t Buffer, p_cd_info_t CdInfo)
{
    p_supplementary_volume_descriptor_t Svd;
    uint32_t JolietLevel = 0;

    Svd = (p_supplementary_volume_descriptor_t) Buffer;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "EscapeSequences: '%.32s'\n", Svd->EscapeSequences);

    if (string_compare_max (Svd->EscapeSequences, "%/@", 3) == 0)
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
            "Joliet extension found (UCS-2 Level 1)\n");
            
        JolietLevel = 1;
    }
    else if (string_compare_max (Svd->EscapeSequences, "%/C", 3) == 0)
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
            "Joliet extension found (UCS-2 Level 2)\n");
            
        JolietLevel = 2;
    }
    else if (string_compare_max (Svd->EscapeSequences, "%/E", 3) == 0)
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
            "Joliet extension found (UCS-2 Level 3)\n");
            
        JolietLevel = 3;
    }

    CdInfo->JolietLevel = JolietLevel;

    if (JolietLevel != 0)
    {
        CdInfo->RootStart = Svd->RootDirRecord.ExtentLocationL;
        CdInfo->RootSize = Svd->RootDirRecord.DataLengthL;

        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
            "RootStart: %lu\n", Svd->RootDirRecord.ExtentLocationL);
            
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
            "RootSize: %lu\n", Svd->RootDirRecord.DataLengthL);
    }
}


static return_t CdfsGetVolumeData (PDEVICE_OBJECT DeviceObject,
    p_cd_info_t CdInfo)
{
    p_uint8_t Buffer;
    return_t Status;
    uint32_t Sector;
    p_volume_descriptor_header_t VdHeader;
    uint32_t Size;
    uint32_t Offset;
    uint32_t i;
  
    struct
    {
        uint8_t  Length[2];
        uint8_t  FirstSession;
        uint8_t  LastSession;
        TRACK_DATA  TrackData;
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "CdfsGetVolumeData\n");
  
    Buffer = ExAllocatePool(NonPagedPool,

    if (Buffer == NULL)
    {
        return STORM_RETURN_INSUFFICIENT_RESOURCES;
    }
    
    Size = sizeof(Toc);
    
    Status = CdfsDeviceIoControl(DeviceObject,
			       IOCTL_CDROM_GET_LAST_SESSION,
			       NULL,
			       0,
			       &Toc,
			       &Size);
                               
    if (Status != STORM_RETURN_SUCCESS)
    {
        ExFreePool(Buffer);
        return Status;
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "FirstSession %d, LastSession %d, FirstTrack %d\n", 
        Toc.FirstSession, Toc.LastSession, Toc.TrackData.TrackNumber);

    Offset = 0;
    for (i = 0; i < 4; i++)
    {
        Offset = (Offset << 8) + Toc.TrackData.Address[i];
    }
    
    CdInfo->VolumeOffset = Offset;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "Offset of first track in last session %d\n", Offset);
  
    CdInfo->JolietLevel = 0;
    VdHeader = (p_volume_descriptor_header_t) Buffer;
    Buffer[0] = 0;

    for (Sector = CDFS_PRIMARY_DESCRIPTOR_LOCATION; 
        Sector < 100 && Buffer[0] != 255; Sector++)
    {
        /* Read the Primary Volume Descriptor (PVD) */
        Status = CdfsReadRawSectors (DeviceObject,
				    Sector + Offset,
				    1,
				    Buffer);
        if (Status != STORM_RETURN_SUCCESS)
	{
	    ExFreePool(Buffer);
	    return(Status);
	}

	if (Sector == CDFS_PRIMARY_DESCRIPTOR_LOCATION)
	{  
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
                "CD-identifier: [%.5s]\n", Buffer + 1);

            if (Buffer[0] != 1 || Buffer[1] != 'C' || Buffer[2] != 'D' ||
	        Buffer[3] != '0' || Buffer[4] != '0' || Buffer[5] != '1')
	    {
		ExFreePool(Buffer);
		return STATUS_UNRECOGNIZED_VOLUME;
	    }
	}

        switch (VdHeader->VdType)
	{
	   case 0:
	      DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
                  "BootVolumeDescriptor found!\n");
	      break;

	   case 1:
	      DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
                  "PrimaryVolumeDescriptor found!\n");
	      CdfsGetPVDData(Buffer, CdInfo);
	      break;

	   case 2:
	      DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
                  "SupplementaryVolumeDescriptor found!\n");
	      CdfsGetSVDData(Buffer, CdInfo);
	      break;

	   case 3:
	      DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
                  "VolumePartitionDescriptor found!\n");
	      break;

	   case 255:
	      DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
                  "VolumeDescriptorSetTerminator found!\n");
	      break;

	   default:
	      DEBUG_PRINT (DEBUG_LEVEL_WARNING,
                  "Unknown volume descriptor type %u found!\n", 
                  VdHeader->VdType);
	      break;
	}

     }

    ExFreePool(Buffer);

    return STORM_RETURN_SUCCESS;
}

static return_t CdfsMountVolume(PDEVICE_OBJECT DeviceObject,
		PIRP Irp)
{
  PDEVICE_EXTENSION DeviceExt = NULL;
  PDEVICE_OBJECT NewDeviceObject = NULL;
  PDEVICE_OBJECT DeviceToMount;
//  PIO_STACK_LOCATION Stack;
  p_file_data_t Fcb = NULL;
//  PCCB Ccb = NULL;
  PVPB Vpb;
  return_t Status;
  cd_info_t CdInfo;

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "CdfsMountVolume() called\n");

  if (DeviceObject != CdfsGlobalData->DeviceObject)
    {
      Status = STATUS_INVALID_DEVICE_REQUEST;
      goto ByeBye;
    }

//  Stack = IoGetCurrentIrpStackLocation(Irp);
  DeviceToMount = Stack->Parameters.MountVolume.DeviceObject;
  Vpb = Stack->Parameters.MountVolume.Vpb;

  Status = CdfsGetVolumeData(DeviceToMount, &CdInfo);
  if (!NT_SUCCESS(Status))
    {
      goto ByeBye;
    }

  Status = IoCreateDevice(CdfsGlobalData->DriverObject,
			  sizeof(DEVICE_EXTENSION),
			  NULL,
			  FILE_DEVICE_FILE_SYSTEM,
//			  FILE_DEVICE_DISK_FILE_SYSTEM,
			  0,
			  FALSE,
			  &NewDeviceObject);
  if (!NT_SUCCESS(Status))
    goto ByeBye;

  NewDeviceObject->Flags = NewDeviceObject->Flags | DO_DIRECT_IO;
  DeviceExt = (PVOID)NewDeviceObject->DeviceExtension;
  RtlZeroMemory(DeviceExt,
		sizeof(DEVICE_EXTENSION));

  Vpb->SerialNumber = CdInfo.SerialNumber;
  Vpb->VolumeLabelLength = CdInfo.VolumeLabelLength;
  RtlCopyMemory(Vpb->VolumeLabel, CdInfo.VolumeLabel, CdInfo.VolumeLabelLength * sizeof(WCHAR));
  RtlCopyMemory(&DeviceExt->CdInfo, &CdInfo, sizeof(CDINFO));
  
  NewDeviceObject->Vpb = DeviceToMount->Vpb;

  DeviceExt->StorageDevice = DeviceToMount;
  DeviceExt->StorageDevice->Vpb->DeviceObject = NewDeviceObject;
  DeviceExt->StorageDevice->Vpb->RealDevice = DeviceExt->StorageDevice;
  DeviceExt->StorageDevice->Vpb->Flags |= VPB_MOUNTED;
  DeviceObject->StackSize = DeviceExt->StorageDevice->StackSize + 1;
  DeviceObject->Flags &= ~DO_DEVICE_INITIALIZING;

  DeviceExt->StreamFileObject = IoCreateStreamFileObject(NULL,
	 DeviceExt->StorageDevice);

  Fcb = CdfsCreateFCB(NULL);
  if (Fcb == NULL)
    {
      Status = STATUS_INSUFFICIENT_RESOURCES;
      goto ByeBye;
    }
/*
  Ccb = ExAllocatePoolWithTag(NonPagedPool,
			      sizeof(CCB),
			      TAG_CCB);
  if (Ccb == NULL)
    {
      Status =  STATUS_INSUFFICIENT_RESOURCES;
      goto ByeBye;
    }
  RtlZeroMemory(Ccb,
		sizeof(CCB));

  DeviceExt->StreamFileObject->Flags = DeviceExt->StreamFileObject->Flags | FO_FCB_IS_VALID | FO_DIRECT_CACHE_PAGING_READ;
  DeviceExt->StreamFileObject->FsContext = Fcb;
//  DeviceExt->StreamFileObject->FsContext2 = Ccb;
  DeviceExt->StreamFileObject->SectionObjectPointer = &Fcb->SectionObjectPointers;
  DeviceExt->StreamFileObject->PrivateCacheMap = NULL;
  DeviceExt->StreamFileObject->Vpb = DeviceExt->Vpb;
//  Ccb->PtrFileObject = DeviceExt->StreamFileObject;
  Fcb->FileObject = DeviceExt->StreamFileObject;
  Fcb->DevExt = (PDEVICE_EXTENSION)DeviceExt->StorageDevice;

  Fcb->Flags = FCB_IS_VOLUME_STREAM;

  Fcb->RFCB.FileSize.QuadPart = (DeviceExt->CdInfo.VolumeSpaceSize + DeviceExt->CdInfo.VolumeOffset) * BLOCKSIZE;
  Fcb->RFCB.ValidDataLength = Fcb->RFCB.AllocationSize = Fcb->RFCB.FileSize;

  Fcb->Entry.ExtentLocationL = 0;
  Fcb->Entry.DataLengthL = (DeviceExt->CdInfo.VolumeSpaceSize + DeviceExt->CdInfo.VolumeOffset) * BLOCKSIZE;

  Status = CcRosInitializeFileCache(DeviceExt->StreamFileObject,
				    PAGE_SIZE);
  if (!NT_SUCCESS (Status))
    {
      DbgPrint("CcRosInitializeFileCache failed\n");
      goto ByeBye;
    }

//  ExInitializeResourceLite(&DeviceExt->DirResource);
//  ExInitializeResourceLite(&DeviceExt->FatResource);

//  KeInitializeSpinLock(&DeviceExt->FcbListLock);
//  InitializeListHead(&DeviceExt->FcbListHead);

  Status = STATUS_SUCCESS;

ByeBye:
  if (!NT_SUCCESS(Status))
    {
      /* Cleanup */
      if (DeviceExt && DeviceExt->StreamFileObject)
	ObDereferenceObject(DeviceExt->StreamFileObject);
      if (Fcb)
	ExFreePool(Fcb);
//      if (Ccb)
//	ExFreePool(Ccb);
      if (NewDeviceObject)
	IoDeleteDevice(NewDeviceObject);
    }

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "CdfsMountVolume() done (Status: %lx)\n", Status);

  return(Status);
}


static return_t
		 PIRP Irp)
{
    PDEVICE_OBJECT DeviceToVerify;
//  PIO_STACK_LOCATION Stack;
    return_t Status;
    cd_info_t CdInfo;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "CdfsVerifyVolume() called\n");

//  Stack = IoGetCurrentIrpStackLocation(Irp);
  DeviceToVerify = Stack->Parameters.VerifyVolume.DeviceObject;

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
      "Device object %p  Device to verify %p\n", DeviceObject, DeviceToVerify);

  CdInfo.SerialNumber = ~DeviceToVerify->Vpb->SerialNumber;

  Status = CdfsGetVolumeData(DeviceToVerify, &CdInfo);

  if (NT_SUCCESS(Status))
  {
     DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Current serial number %08lx  Vpb serial number %08lx\n",
	    CdInfo.SerialNumber, DeviceToVerify->Vpb->SerialNumber);

     if (CdInfo.SerialNumber != DeviceToVerify->Vpb->SerialNumber)
	 Status = STATUS_WRONG_VOLUME;
    }

    return(Status);
}
