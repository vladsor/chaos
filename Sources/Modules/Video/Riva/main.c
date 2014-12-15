/* $Id: vga.c,v 1.2 2001/02/10 21:25:42 jojo Exp $ */
/* Abstract: VGA server for chaos. */
/* Authors: Per Lundberg <plundis@chaosdev.org>
            Henrik Hallin <hal@chaosdev.org> */

#include <enviroment.h>

#include <Classes/pci_bus.h>
#include <Classes/pci_device.h>

#include "video.h"

#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL 11
//define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

uint8_t *graphic_video_memory = (uint8_t *) NULL;
#define PCI_RESOURCE_IO                 0x00000100
#define PCI_RESOURCE_MEMORY             0x00000200
#define PCI_RESOURCE_IRQ                0x00000400
#define PCI_RESOURCE_DMA                0x00000800

#define NVIDIA_VENDOR_ID               0x10DE

enum 
{
    VIDEO_Riva128,
    VIDEO_RivaTnT,
    VIDEO_RivaTnT2,
    VIDEO_Geforce,
    VIDEO_Geforce2,
};

uint16_t riva_devices[] =
{
    0x0020, /*  Riva TnT 128 [NV04] */
    0x0028, /*  Riva TnT2 [NV5] */
    0x0029, /*  Riva TnT2 Ultra [NV5] */
    0x002A, /*  Riva TnT2 [NV5] */
    0x002B, /*  Riva TnT2 [NV5] */
    0x00A0, /*  Riva TNT2 */
};

#define number_of_probe (sizeof (riva_devices) / \
                        sizeof (uint16_t))


typedef struct
{
  unsigned long memory_io_dma;
  uint8_t *memory_io;

  unsigned long linear_dma;
  uint8_t *linear;

  unsigned long memory_size;
  unsigned long linear_size;
} adapter_info_type;

void *io_address = NULL;
void *linear_address = NULL;
static riva_info_type riva;

static void handle_video (pci_device_info_t *device_info)
{
  unsigned int counter;
  adapter_info_type adapter_info;
  void *base0, *base1;

  for (counter = 0; counter < PCI_NUMBER_OF_RESOURCES; counter++)
  {
    if ((device_info->resource[counter].flags & PCI_RESOURCE_MEMORY) != 0)
    {
      DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
          "Memory resource %lX, %lX\n",
      device_info->resource[counter].start,
      device_info->resource[counter].end);
    }
  }

  base0 = (void*) (device_info->resource[0].start & 0xFF800000);
  base1 = (void*) (device_info->resource[1].start & 0xFF800000);

  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
      "base0 = %p, base1 = %p\n", base0, base1);

  riva.PRAMIN = (char *) base0 + 0x00710000;

  riva.PCRTC = (char *) base0 + 0x00600000;
  
  adapter_info.memory_io_dma = device_info->resource[0].start;
  adapter_info.memory_size = device_info->resource[0].end - 
                             device_info->resource[0].start + 1;
  adapter_info.linear_dma = device_info->resource[1].start;
  adapter_info.linear_size = device_info->resource[1].end - 
                             device_info->resource[1].start + 1;

  MapNvRegs ((void *) adapter_info.memory_io_dma);
  NV1DisplayPowerManagementSet (DPMSModeOff);

/*
  system_call_memory_reserve (adapter_info.memory_io_dma, 
                              0x00080000,
                              (void **) &adapter_info.memory_io);
*/
  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
                       "MM IO %lX, %lu, [%lX]\n",
		       adapter_info.memory_io_dma, adapter_info.memory_size,
		       (uint32_t) adapter_info.memory_io);
/*
  system_call_memory_reserve (adapter_info.linear_dma, 
                              0x00001000,
                              &linear_address);
*/
  DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
                       "LINEAR %lX, %lu\n",
		       adapter_info.linear_dma, adapter_info.linear_size);
/*
  system_call_memory_reserve (base0 + 0x00710000, 0x00010000, &riva.PRAMIN);
  system_call_memory_reserve (base0 + 0x00600000, 0x00001000, &riva.PCRTC);
*/
//  memory_set_u8 (adapter_info.memory_io, 0x0, 1*KB);

}    


static bool riva_init (void)
{
    pci_device_info_t device_info;
    uint32_t number_of_devices;
    unsigned int probe_counter;
    handle_t pci;
    handle_t riva_device;
    
    namespace_resolve ("/devices/pci", &pci);
    register_object_open (&pci, IID_PCI_BUS);

    for (probe_counter = 0; probe_counter < number_of_probe; probe_counter++)
    {
        uint32_t device = 0;
        number_of_devices = 1;
        
        pci_bus$find_devices (&pci, NVIDIA_VENDOR_ID, 
            riva_devices[probe_counter], 0xFF, 0xFF, 0xFF, device, 
            &number_of_devices, &riva_device);

        if (number_of_devices == 1)
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Found RIVA adapter.\n");
            
            register_object_open (&riva_device, IID_PCI_DEVICE);
            pci_device$get_info (&riva_device, &device_info);
            handle_video (&device_info);
        }
    }
  
    return TRUE;
}

#if FALSE

int NV4Probe(vgaVideoChipRec *nv, void *regBase, void *frameBase)
{
    OFLG_SET(OPTION_DAC_8_BIT, &(nv->ChipOptionFlags));
    OFLG_SET(OPTION_DAC_8_BIT, &vga256InfoRec.options);
    /*
     * Record chip architecture based in PCI probe.
     */
    riva.Architecture = NV_ARCH_04;
    /*
     * Map chip-specific memory-mapped registers. This MUST be done in the OS specific driver code.
     */
    riva.PRAMIN = (unsigned *)xf86MapVidMem(vga256InfoRec.scrnIndex, MMIO_REGION,((char *)regBase+0x00710000), 0x00010000);
    riva.PCRTC  = (unsigned *)xf86MapVidMem(vga256InfoRec.scrnIndex, MMIO_REGION,((char *)regBase+0x00600000), 0x00001000);
    /*
     * Call the common chip probe.
     */
    return (RivaProbe(nv, regBase, frameBase));
}

static NVChipType chipis = NV1;

NVChipType GetChipType(void)
{
  return chipis;
}

typedef Bool (*NVProbeFuncType)(vgaVideoChipRec *rec,void *base0,void *base1);

Bool NV1Probe(vgaVideoChipRec *rec,void *base0,void *base1);
Bool NV3Probe(vgaVideoChipRec *rec,void *base0,void *base1);
Bool NV4Probe(vgaVideoChipRec *rec,void *base0,void *base1);
Bool NV10Probe(vgaVideoChipRec *rec,void *base0,void *base1);

static NVProbeFuncType NVProbeFuncList[NumNVChips]= {
  NV1Probe,
  NV3Probe,
  NV4Probe,
  NV10Probe
};


typedef struct {
  char *name;
  NVChipType type;
  int vendor;
  int device;
} NVProbeInfo;

static NVProbeInfo probeList[] = {
  { "NV1", 		NV1,  PCI_VENDOR_NVIDIA,	PCI_CHIP_DAC64 },
  { "STG2000",		NV1,  PCI_VENDOR_SGS,		PCI_CHIP_STG1764 },
  { "RIVA 128",		NV3,  PCI_VENDOR_NVIDIA_SGS,	PCI_CHIP_RIVA128 },
  { "RIVA TNT",		NV4,  PCI_VENDOR_NVIDIA,	PCI_CHIP_TNT },
  { "RIVA TNT2",	NV4,  PCI_VENDOR_NVIDIA,	PCI_CHIP_TNT2 },
  { "RIVA ULTRA TNT2",	NV4,  PCI_VENDOR_NVIDIA,	PCI_CHIP_UTNT2 },
  { "RIVA VANTA",	NV4,  PCI_VENDOR_NVIDIA,	PCI_CHIP_VTNT2 },
  { "RIVA ULTRA VANTA",	NV4,  PCI_VENDOR_NVIDIA,	PCI_CHIP_UVTNT2 },
  { "RIVA INTEGRATED",	NV4,  PCI_VENDOR_NVIDIA,	PCI_CHIP_ITNT2 },
  { "GeForce 256",	NV10, PCI_VENDOR_NVIDIA,	PCI_CHIP_GEFORCE256 },
  { "GeForce DDR",	NV10, PCI_VENDOR_NVIDIA,	PCI_CHIP_GEFORCEDDR },
  { "Quadro",		NV10, PCI_VENDOR_NVIDIA,	PCI_CHIP_QUADRO }
};


#define NUM_PROBE_ENTRIES (sizeof(probeList)/sizeof(NVProbeInfo))



static Bool NVProbe(void)
{
  int i;
  void *base0=NULL,*base1=NULL;
  Bool ret;
  int idx=0,found=0;
  pciConfigPtr pcrp,*pciList;
  int noaccelSet;

  for (probe_counter = 0; probe_counter < number_of_probe ; probe_counter++)
  {
    pci_device_exists (&pci_structure, &pci_device_probe[probe_counter],
                       &device_info, &number_of_devices);
    if (number_of_devices != 0)
    {
      log_print (&log_structure, LOG_URGENCY_EMERGENCY, "Found RIVA adapter.");
      base0 = (void*) (device_info->resource[0]->start & 0xFF800000);
      base1 = (void*) (device_info->resource[1]->start & 0xFF800000);
      found = TRUE;
      break
    }
  }

  if(!found) 
  {
    return FALSE;
  }
  
  return NVProbeFuncList[GetChipType()](&NV, base0, base1);
}
#endif

/* Main function. */

return_t riva_main (int argc UNUSED, char *argv[] UNUSED)
{
    if (!riva_init ())
    {
        return -1;
    }


    return 0;
}
