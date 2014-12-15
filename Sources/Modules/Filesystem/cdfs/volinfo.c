
#include "cdfs.h"


/* FUNCTIONS ****************************************************************/

return_t CdfsGetFsVolumeInformation (
    PDEVICE_OBJECT DeviceObject,
    PFILE_FS_VOLUME_INFORMATION FsVolumeInfo,
    PULONG BufferLength)
{
  ULONG LabelLength;

  DPRINT("CdfsGetFsVolumeInformation() called\n");
  DPRINT("FsVolumeInfo = %p\n", FsVolumeInfo);
  DPRINT("BufferLength %lu\n", *BufferLength);

  DPRINT("Vpb %p\n", DeviceObject->Vpb);
  LabelLength = DeviceObject->Vpb->VolumeLabelLength;

  DPRINT("Required length %lu\n", (sizeof(FILE_FS_VOLUME_INFORMATION) + LabelLength*sizeof(WCHAR)));
  DPRINT("LabelLength %lu\n", LabelLength);
  DPRINT("Label %S\n", DeviceObject->Vpb->VolumeLabel);

  if (*BufferLength < sizeof(FILE_FS_VOLUME_INFORMATION))
    return STATUS_INFO_LENGTH_MISMATCH;

  if (*BufferLength < (sizeof(FILE_FS_VOLUME_INFORMATION) + LabelLength*sizeof(WCHAR)))
    return STATUS_BUFFER_OVERFLOW;

  /* valid entries */
  FsVolumeInfo->VolumeSerialNumber = DeviceObject->Vpb->SerialNumber;
  FsVolumeInfo->VolumeLabelLength = LabelLength * sizeof (WCHAR);
  wcscpy(FsVolumeInfo->VolumeLabel, DeviceObject->Vpb->VolumeLabel);

  /* dummy entries */
  FsVolumeInfo->VolumeCreationTime.QuadPart = 0;
  FsVolumeInfo->SupportsObjects = FALSE;

  DPRINT("Finished FsdGetFsVolumeInformation()\n");

  *BufferLength -= (sizeof(FILE_FS_VOLUME_INFORMATION) + LabelLength * sizeof(WCHAR));

  DPRINT("BufferLength %lu\n", *BufferLength);

  return(STATUS_SUCCESS);
}


return_t CdfsGetFsAttributeInformation (
    PDEVICE_EXTENSION DeviceExt,
    PFILE_FS_ATTRIBUTE_INFORMATION FsAttributeInfo,
    PULONG BufferLength)
{
  DPRINT("CdfsGetFsAttributeInformation()\n");
  DPRINT("FsAttributeInfo = %p\n", FsAttributeInfo);
  DPRINT("BufferLength %lu\n", *BufferLength);
  DPRINT("Required length %lu\n", (sizeof(FILE_FS_ATTRIBUTE_INFORMATION) + 8));

  if (*BufferLength < sizeof (FILE_FS_ATTRIBUTE_INFORMATION))
    return STATUS_INFO_LENGTH_MISMATCH;

  if (*BufferLength < (sizeof(FILE_FS_ATTRIBUTE_INFORMATION) + 8))
    return STATUS_BUFFER_OVERFLOW;

  FsAttributeInfo->FileSystemAttributes =
    FILE_CASE_PRESERVED_NAMES | FILE_UNICODE_ON_DISK;
  FsAttributeInfo->MaximumComponentNameLength = 255;
  FsAttributeInfo->FileSystemNameLength = 8;

  memcpy(FsAttributeInfo->FileSystemName, L"CDFS", 8);

  DPRINT("Finished FsdGetFsAttributeInformation()\n");

  *BufferLength -= (sizeof(FILE_FS_ATTRIBUTE_INFORMATION) + 8);
  DPRINT("BufferLength %lu\n", *BufferLength);

  return(STATUS_SUCCESS);
}


return_t CdfsGetFsSizeInformation (
    PDEVICE_OBJECT DeviceObject,
    PFILE_FS_SIZE_INFORMATION FsSizeInfo,
    PULONG BufferLength)
{
  PDEVICE_EXTENSION DeviceExt;
  NTSTATUS Status = STATUS_SUCCESS;

  DPRINT("CdfsGetFsSizeInformation()\n");
  DPRINT("FsSizeInfo = %p\n", FsSizeInfo);

  if (*BufferLength < sizeof(FILE_FS_SIZE_INFORMATION))
    return(STATUS_BUFFER_OVERFLOW);

  DeviceExt = DeviceObject->DeviceExtension;

  FsSizeInfo->AvailableAllocationUnits.QuadPart = 0;
  FsSizeInfo->TotalAllocationUnits.QuadPart = DeviceExt->CdInfo.VolumeSpaceSize;
  FsSizeInfo->SectorsPerAllocationUnit = 1;
  FsSizeInfo->BytesPerSector = BLOCKSIZE;

  DPRINT("Finished FsdGetFsSizeInformation()\n");
  if (NT_SUCCESS(Status))
    *BufferLength -= sizeof(FILE_FS_SIZE_INFORMATION);

  return(Status);
}

return_t CdfsGetFsDeviceInformation (
    PFILE_FS_DEVICE_INFORMATION FsDeviceInfo,
    PULONG BufferLength)
{
  DPRINT("CdfsGetFsDeviceInformation()\n");
  DPRINT("FsDeviceInfo = %p\n", FsDeviceInfo);
  DPRINT("BufferLength %lu\n", *BufferLength);
  DPRINT("Required length %lu\n", sizeof(FILE_FS_DEVICE_INFORMATION));

  if (*BufferLength < sizeof(FILE_FS_DEVICE_INFORMATION))
    return(STATUS_BUFFER_OVERFLOW);

  FsDeviceInfo->DeviceType = FILE_DEVICE_CD_ROM;
  FsDeviceInfo->Characteristics = 0; /* FIXME: fix this !! */

  DPRINT("FsdGetFsDeviceInformation() finished.\n");

  *BufferLength -= sizeof(FILE_FS_DEVICE_INFORMATION);
  DPRINT("BufferLength %lu\n", *BufferLength);

  return(STATUS_SUCCESS);
}


