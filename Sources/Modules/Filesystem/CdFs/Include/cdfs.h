#ifndef CDFS_H
#define CDFS_H

#define CDFS_BASIC_SECTOR 2048
#define CDFS_PRIMARY_DESCRIPTOR_LOCATION 16
#define BLOCKSIZE CDFS_BASIC_SECTOR
#define CDFS_MAX_NAME_LEN 256


/* Volume descriptor types (VdType) */
#define BOOT_VOLUME_DESCRIPTOR_TYPE		0
#define PRIMARY_VOLUME_DESCRIPTOR_TYPE		1
#define SUPPLEMENTARY_VOLUME_DESCRIPTOR_TYPE	2
#define VOLUME_PARTITION_DESCRIPTOR_TYPE	3
#define VOLUME_DESCRIPTOR_SET_TERMINATOR	255

enum
{
    CDFS_RETURN_END_OF_FILE
};

struct directory_record_struct;
typedef struct directory_record_struct directory_record_t;
typedef directory_record_t * p_directory_record_t;

struct directory_record_struct
{
    uint8_t  RecordLength;			// 1
    uint8_t  ExtAttrRecordLength;		// 2
    uint32_t  ExtentLocationL;		// 3-6
    uint32_t  ExtentLocationM;		// 7-10
    uint32_t  DataLengthL;			// 11-14
    uint32_t  DataLengthM;			// 15-18
    uint8_t  Year;				// 19
    uint8_t  Month;				// 20
    uint8_t  Day;				// 21
    uint8_t  Hour;				// 22
    uint8_t  Minute;			// 23
    uint8_t  Second;			// 24
    uint8_t  TimeZone;			// 25
    uint8_t  FileFlags;			// 26
    uint8_t  FileUnitSize;			// 27
    uint8_t  InterleaveGapSize;		// 28
    uint32_t  VolumeSequenceNumber;		// 29-32
    uint8_t  FileIdLength;			// 33
    uint8_t  FileId[1];			// 34
  
} PACKED;

struct volume_descriptor_header_struct;
typedef struct volume_descriptor_header_struct volume_descriptor_header_t;
typedef volume_descriptor_header_t * p_volume_descriptor_header_t;

/* Volume Descriptor header*/
struct volume_descriptor_header_struct
{
    uint8_t  VdType;			// 1
    uint8_t  StandardId[5];			// 2-6
    uint8_t  VdVersion;			// 7
} PACKED;

struct primary_volume_descriptor_struct;
typedef struct primary_volume_descriptor_struct primary_volume_descriptor_t;
typedef primary_volume_descriptor_t * p_primary_volume_descriptor_t;

/* Primary Volume Descriptor */
struct primary_volume_descriptor_struct
{
    uint8_t  VdType;			// 1
    uint8_t  StandardId[5];			// 2-6
    uint8_t  VdVersion;			// 7
    uint8_t  unused0;			// 8
    uint8_t  SystemId[32];			// 9-40
    uint8_t  VolumeId[32];			// 41-72
    uint8_t  unused1[8];			// 73-80
    uint32_t  VolumeSpaceSizeL;		// 81-84
    uint32_t  VolumeSpaceSizeM;		// 85-88
    uint8_t  unused2[32];			// 89-120
    uint32_t  VolumeSetSize;			// 121-124
    uint32_t  VolumeSequenceNumber;		// 125-128
    uint32_t  LogicalBlockSize;		// 129-132
    uint32_t  PathTableSizeL;		// 133-136
    uint32_t  PathTableSizeM;		// 137-140
    uint32_t  LPathTablePos;			// 141-144
    uint32_t  LOptPathTablePos;		// 145-148
    uint32_t  MPathTablePos;			// 149-152
    uint32_t  MOptPathTablePos;		// 153-156
    directory_record_t RootDirRecord;		// 157-190
    uint8_t  VolumeSetIdentifier[128];	// 191-318
    uint8_t  PublisherIdentifier[128];	// 319-446

  /* more data ... */

} PACKED;

/* Supplementary Volume Descriptor */
typedef struct
{
    uint8_t  VdType;			// 1
    uint8_t  StandardId[5];			// 2-6
    uint8_t  VdVersion;			// 7
    uint8_t  VolumeFlags;			// 8
    uint8_t  SystemId[32];			// 9-40
    uint8_t  VolumeId[32];			// 41-72
    uint8_t  unused1[8];			// 73-80
    uint32_t  VolumeSpaceSizeL;		// 81-84
    uint32_t  VolumeSpaceSizeM;		// 85-88
    uint8_t  EscapeSequences[32];		// 89-120
    uint32_t  VolumeSetSize;			// 121-124
    uint32_t  VolumeSequenceNumber;		// 125-128
    uint32_t  LogicalBlockSize;		// 129-132
    uint32_t  PathTableSizeL;		// 133-136
    uint32_t  PathTableSizeM;		// 137-140
    uint32_t  LPathTablePos;			// 141-144
    uint32_t  LOptPathTablePos;		// 145-148
    uint32_t  MPathTablePos;			// 149-152
    uint32_t  MOptPathTablePos;		// 153-156
    directory_record_t RootDirRecord;		// 157-190
    uint8_t  VolumeSetIdentifier[128];	// 191-318
    uint8_t  PublisherIdentifier[128];	// 319-446

 // more data ...
} supplementary_volume_descriptor_t PACKED;

typedef supplementary_volume_descriptor_t * p_supplementary_volume_descriptor_t;

typedef struct
{
    uint32_t VolumeOffset;
    uint32_t VolumeSpaceSize;
    uint32_t JolietLevel;
    uint32_t RootStart;
    uint32_t RootSize;
    wchar_t VolumeLabel[MAXIMUM_VOLUME_LABEL_LENGTH];
    uint32_t VolumeLabelLength;
    uint32_t SerialNumber;
} cd_info_t;

typedef cd_info_t * p_cd_info_t;

typedef struct
{
//  ERESOURCE DirResource;
//  ERESOURCE FatResource;

//  KSPIN_LOCK FcbListLock;
//  LIST_ENTRY FcbListHead;


  PVPB Vpb;
  handle_reference_t StorageDevice;
//  PFILE_OBJECT StreamFileObject;

  cd_info_t CdInfo;


} device_data_t;


#define FCB_CACHE_INITIALIZED   0x0001
#define FCB_IS_VOLUME_STREAM    0x0002
#define FCB_IS_VOLUME           0x0004

typedef struct _FCB
{
//  FSRTL_COMMON_FCB_HEADER RFCB;
//  SECTION_OBJECT_POINTERS SectionObjectPointers;

//  PFILE_OBJECT FileObject;
//  PDEVICE_EXTENSION DevExt;
    p_device_data_t DevExt;
    
/* point on filename (250 chars max) in PathName */
    wchar_t *ObjectName;		
    
    /* path+filename 260 max */
    wchar_t PathName[MAX_PATH];	
    wchar_t ShortName[13];
    uint16_t ShortNameLength;

//  ERESOURCE PagingIoResource;
//  ERESOURCE MainResource;

//  LIST_ENTRY FcbListEntry;
//  struct _FCB* ParentFcb;
    p_file_data_t ParentFcb;

    uint32_t DirIndex;

    uint32_t RefCount;
    uint32_t Flags;

    directory_record_t Entry;


} file_data_t;

#if 0
typedef struct _CCB
{
  LIST_ENTRY     NextCCB;
  PFILE_OBJECT   PtrFileObject;
  LARGE_INTEGER  CurrentByteOffset;

  /* for DirectoryControl */
  uint32_t Entry;
  uint32_t Offset;

  /* for DirectoryControl */
  PWCHAR DirectorySearchPattern;
  uint32_t LastCluster;
  uint32_t LastOffset;

} CCB, *PCCB;
#endif

//#define TAG(A, B, C, D) (uint32_t)(((A)<<0) + ((B)<<8) + ((C)<<16) + ((D)<<24))

//#define TAG_CCB TAG('I', 'C', 'C', 'B')


/*
typedef struct
{
  PDRIVER_OBJECT DriverObject;
  PDEVICE_OBJECT DeviceObject;
  uint32_t Flags;
} CDFS_GLOBAL_DATA, *PCDFS_GLOBAL_DATA;

extern PCDFS_GLOBAL_DATA CdfsGlobalData;
*/

return_t
CdfsReadSectors(IN PDEVICE_OBJECT DeviceObject,
		IN uint32_t DiskSector,
		IN uint32_t SectorCount,
		IN OUT Puint8_t Buffer);

int CdfsStrcmpi( wchar_t *str1, wchar_t *str2 );
void CdfsWstrcpy( wchar_t *str1, wchar_t *str2, int max );

/* cleanup.c */

return_t STDCALL
CdfsCleanup(PDEVICE_OBJECT DeviceObject,
	    PIRP Irp);

/* close.c */

return_t STDCALL
CdfsClose(PDEVICE_OBJECT DeviceObject,
	  PIRP Irp);

return_t
CdfsCloseFile(PDEVICE_EXTENSION DeviceExt,
	      PFILE_OBJECT FileObject);

/* common.c */

return_t
CdfsReadSectors(IN PDEVICE_OBJECT DeviceObject,
		IN uint32_t DiskSector,
		IN uint32_t SectorCount,
		IN OUT Puint8_t Buffer);

return_t
CdfsReadRawSectors(IN PDEVICE_OBJECT DeviceObject,
		   IN uint32_t DiskSector,
		   IN uint32_t SectorCount,
		   IN OUT Puint8_t Buffer);

return_t
CdfsDeviceIoControl (IN PDEVICE_OBJECT DeviceObject,
		     IN uint32_t CtlCode,
		     IN PVOID InputBuffer,
		     IN uint32_t InputBufferSize,
		     IN OUT PVOID OutputBuffer, 
		     IN OUT Puint32_t pOutputBufferSize);

/* create.c */

return_t STDCALL
CdfsCreate(PDEVICE_OBJECT DeviceObject,
	   PIRP Irp);


/* dirctl.c */

return_t STDCALL
CdfsDirectoryControl(PDEVICE_OBJECT DeviceObject,
		     PIRP Irp);


/* fcb.c */

PFCB
CdfsCreateFCB(PWCHAR FileName);

VOID
CdfsDestroyFCB(PFCB Fcb);

BOOLEAN
CdfsFCBIsDirectory(PFCB Fcb);

BOOLEAN
CdfsFCBIsRoot(PFCB Fcb);

VOID
CdfsGrabFCB(PDEVICE_EXTENSION Vcb,
	    PFCB Fcb);

VOID
CdfsReleaseFCB(PDEVICE_EXTENSION Vcb,
	       PFCB Fcb);

VOID
CdfsAddFCBToTable(PDEVICE_EXTENSION Vcb,
		  PFCB Fcb);

PFCB
CdfsGrabFCBFromTable(PDEVICE_EXTENSION Vcb,
		     PWSTR FileName);

return_t
CdfsFCBInitializeCache(PVCB Vcb,
		       PFCB Fcb);

PFCB
CdfsMakeRootFCB(PDEVICE_EXTENSION Vcb);

PFCB
CdfsOpenRootFCB(PDEVICE_EXTENSION Vcb);



return_t
CdfsAttachFCBToFileObject(PDEVICE_EXTENSION Vcb,
			  PFCB Fcb,
			  PFILE_OBJECT FileObject);




return_t
CdfsGetFCBForFile(PDEVICE_EXTENSION Vcb,
		  PFCB *pParentFCB,
		  PFCB *pFCB,
		  const PWSTR pFileName);


/* finfo.c */

return_t STDCALL
CdfsQueryInformation(PDEVICE_OBJECT DeviceObject,
		     PIRP Irp);

return_t STDCALL
CdfsSetInformation(PDEVICE_OBJECT DeviceObject,
		   PIRP Irp);

/* fsctl.c */

return_t STDCALL
CdfsFileSystemControl(PDEVICE_OBJECT DeviceObject,
		      PIRP Irp);

/* misc.c */

BOOLEAN
wstrcmpjoki(PWSTR s1, PWSTR s2);

VOID
CdfsSwapString(PWCHAR Out,
	       Puint8_t In,
	       uint32_t Count);

VOID
CdfsDateTimeToFileTime(PFCB Fcb,
		       TIME *FileTime);

VOID
CdfsFileFlagsToAttributes(PFCB Fcb,
			  Puint32_t FileAttributes);

/* rw.c */

return_t CdfsRead(PDEVICE_OBJECT DeviceObject,
	PIRP Irp);

return_t CdfsWrite(PDEVICE_OBJECT DeviceObject,
	  PIRP Irp);


/* volinfo.c */

return_t CdfsQueryVolumeInformation(PDEVICE_OBJECT DeviceObject,
			   PIRP Irp);

return_t CdfsSetVolumeInformation(PDEVICE_OBJECT DeviceObject,
			 PIRP Irp);

#endif //CDFS_H
