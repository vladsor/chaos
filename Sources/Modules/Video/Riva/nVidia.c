#include <enviroment.h>

#include "video.h"
#include "nvreg.h"
#include "nv1ref.h"

bool xf86VTSema = TRUE;

static unsigned long currentGreen0=0;

static void * MapVideoMemory (void *address, unsigned int size)
{
    return address;
}

#define MapDevice(device,base) \
  nv##device##Port = (unsigned*) MapVideoMemory( \
                                 ((char*)(base))+DEVICE_BASE(device),\
                                 DEVICE_SIZE(device))

#define DefineDevice(device,base) \
  volatile unsigned int *nv##device##Port = NULL

#define NV_CHAN0 0x0080ffff:0x00800000

#define NV_FRAME_BUFFER 0x01000000

DefineDevice (PDAC, base);
DefineDevice (PFB, base);
DefineDevice (PRM, base);
DefineDevice (PGRAPH, base);
DefineDevice (PDMA, base);
DefineDevice (PFIFO, base);
DefineDevice (PRAM, base);
DefineDevice (PRAMFC, base);
DefineDevice (PRAMHT, base);
DefineDevice (PMC, base);
DefineDevice (CHAN0, base);

void MapNvRegs(void *base)
{
  MapDevice (PDAC, base);
  MapDevice (PFB, base);
  MapDevice (PRM, base);
  MapDevice (PGRAPH, base);
  MapDevice (PDMA, base);
  MapDevice (PFIFO, base);
  MapDevice (PRAM, base);
  MapDevice (PRAMFC, base);
  MapDevice (PRAMHT, base);
  MapDevice (PMC, base);
  MapDevice (CHAN0, base);
}

void NV1DisplayPowerManagementSet (int mode)
{
  int level;
  int hsyncOn = 0, vsyncOn = 0;
  unsigned long green = 0;

  if (!xf86VTSema)
  {
    return;
  }
  
  switch(mode) 
  {
    case DPMSModeOn:
    {
      /* Screen: On; HSync: On, VSync: On */
      level = 0; hsyncOn = 1; vsyncOn = 1;
      break;
    }
    
    case DPMSModeStandby:
    {
      /* Screen: Off; HSync: Off, VSync: On */
      level = 1; hsyncOn = 0; vsyncOn = 1;
      break;
    }
    
    case DPMSModeSuspend:
    {
      /* Screen: Off; HSync: On, VSync: Off */
      level = 1; hsyncOn = 1; vsyncOn = 0;
      break;
    }
    
    case DPMSModeOff:
    {
      /* Screen: Off; HSync: Off, VSync: Off */
      level = 2; hsyncOn = 0; vsyncOn = 0;
      break;
    }
    
    default:
    {
      return;
    }
  }

  if(hsyncOn) 
  {
    green |= (currentGreen0 & PFB_Mask (GREEN_0_POLAR_HSYNC));
  }
  else 
  { 
    green |= PFB_Def (GREEN_0_POLAR_HSYNC, LOW);
  }

  if(vsyncOn) 
  {
    green |= (currentGreen0 & PFB_Mask (GREEN_0_POLAR_VSYNC));
  }
  else 
  { 
    green |= PFB_Def (GREEN_0_POLAR_VSYNC, LOW);
  }
  
  green |= PFB_Val (GREEN_0_LEVEL, level);
  PFB_Write (GREEN_0, green);

}
