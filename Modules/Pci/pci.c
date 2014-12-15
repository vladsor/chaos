/* $Id: pci.c,v 1.7 2000/10/15 21:15:32 plundis Exp $ */
/* Abstract: PCI server. (It should also support AGP sometime, but
   currently, it hardly does PCI right...) */
/* Author: Per Lundberg <plundis@chaosdev.org>. Heaviliy inspired by
 * the Linux source, but not by far as obnoxious... */

/* Copyright 1999-2000 chaos development. */

#include <enviroment.h>

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

#include <list.h>

#include "pci.h"
#include "types.h"
#include "pci_lowlevel.h"

static int ffs (int a)
{
  int res;

  asm (
    "bsfl %0, %%eax\n"
/* ZF is set if all bits are 0 */
    "jz 1\n"
/* clear result */
    "1: xorl %%eax, %%eax" 
    : "=a" (res)
    : "g" (a));
  
  /* bits numbered from 1, not 0 */

  return res + 1;

};

/* Linked list of all PCI devices. */

list_t pci_device_list = LIST_EMPTY;

/* Linked list of all buses. */

list_t pci_bus_list = LIST_EMPTY;

extern pci_device_id_t pci_device_id[];
extern unsigned int number_of_devices;

extern pci_vendor_id_t pci_vendor_id[];
extern unsigned int number_of_vendors;

extern pci_class_id_t pci_class_id[];
extern unsigned int number_of_classes;

/* The operations we should use to access the PCI host. */

static pci_operation_t *pci_operation = NULL;

/* Get the vendor name for the given ID. */

static const char *vendor_get_name (uint16_t vendor_id)
{
  unsigned int range_begin = 0;
  unsigned int range_end = number_of_vendors - 1;
  unsigned int range_median = (range_end - range_begin) >> 1;

  while (pci_vendor_id[range_median].vendor_id != vendor_id)
  {
    if (range_begin == range_end)
    {
      return NULL;
    }
    
    if (pci_vendor_id[range_median].vendor_id > vendor_id)
    {
      range_end = range_median - 1;
      range_median = (range_begin + range_end) >> 1;
      
      if (range_end < range_begin)
      {
        return NULL;
      }
    }
    else
    {
      range_begin = range_median + 1;
      range_median = (range_begin + range_end) >> 1;

      if (range_end < range_begin)
      {
        return NULL;
      }
    }
  }
  
  return pci_vendor_id[range_median].name;
}

/* Get the device name for the given ID. */

static const char *device_get_name (uint16_t vendor_id, uint16_t device_id)
{
  unsigned int range_begin = 0;
  unsigned int range_end = number_of_devices - 1;
  unsigned int range_median = (range_end - range_begin) >> 1;

  while (pci_device_id[range_median].vendor_id != vendor_id ||
         pci_device_id[range_median].device_id != device_id)
  {
    if (range_begin == range_end)
    {
      return NULL;
    }
    
    if (pci_device_id[range_median].vendor_id > vendor_id)
    {
      range_end = range_median - 1;
      range_median = (range_begin + range_end) >> 1;

      if (range_end < range_begin)
      {
        return NULL;
      }
    }
    else if (pci_device_id[range_median].vendor_id < vendor_id)
    {
      range_begin = range_median + 1;
      range_median = (range_begin + range_end) >> 1;

      if (range_end < range_begin)
      {
        return NULL;
      }
    }
    else
    {
      if (pci_device_id[range_median].device_id > device_id)
      {
        range_end = range_median - 1;
        range_median = (range_begin + range_end) >> 1;
  
        if (range_end < range_begin)
        {
          return NULL;
        }
      }
      else
      {
        range_begin = range_median + 1;
        range_median = (range_begin + range_end) >> 1;

        if (range_end < range_begin)
        {
          return NULL;
        }
      }
    }
  }

  return pci_device_id[range_median].name;
}

/* Get the class name for the given ID. */

static const char *class_get_name (uint8_t class_id)
{
  unsigned int range_begin = 0;
  unsigned int range_end = number_of_classes - 1;
  unsigned int range_median = (range_end - range_begin) >> 1;

  while (pci_class_id[range_median].class_id != class_id)
  {
    if (range_begin == range_end)
    {
      return NULL;
    }
    
    if (pci_class_id[range_median].class_id > class_id)
    {
      range_end = range_median - 1;
      range_median = (range_begin + range_end) >> 1;
      
      if (range_end < range_begin)
      {
        return NULL;
      }
    }
    else
    {
      range_begin = range_median + 1;
      range_median = (range_begin + range_end) >> 1;

      if (range_end < range_begin)
      {
        return NULL;
      }
    }
  }
  
  return pci_class_id[range_median].class_name;
}

/* Detect the presence of a PCI host, and if found, return a pointer
   to the functions that should be used when accessing it. Otherwise,
   return NULL. */

static pci_operation_t *pci_detect (void)
{
    pci_operation_t *operation = NULL;

    port_uint8_out (PCI_BASE, 0);
    port_uint8_out (PCI_BASE + 2, 0);

    if ((port_uint8_in (PCI_BASE) == 0) && (port_uint8_in (PCI_BASE + 2) == 0))
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "PCI Type 2.\n");

        operation = &pci_type2_operation;
    }
    else
    {
        uint32_t tmp = port_uint32_in (PCI_BASE);
        port_uint32_out (PCI_BASE, 0x80000000);

        if (port_uint32_in (PCI_BASE) == 0x80000000)
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "PCI Type 1.\n");
            operation = &pci_type1_operation;
        }
        else
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "PCI not present.\n");
        }

        port_uint32_out (PCI_BASE, tmp);
    }

    return operation;
}

static bool device_has_bist (pci_device_t *pci_device)
{
    return ((pci_read_config_u8 (pci_device, PCI_BIST) &
        PCI_BIST_CAPABLE) != 0);
}


uint8_t device_bist (pci_device_t *pci_device)
{
    uint32_t start_time, current_time;
  
    pci_write_config_u8 (pci_device, PCI_BIST, PCI_BIST_START);

    timer_system_read (&start_time);
  
    while ((pci_read_config_u8 (pci_device, PCI_BIST) & PCI_BIST_START) != 0)
    {
        timer_system_read (&current_time);
        if ((current_time - start_time) > 2000)
        {
            return 0xFF;
        }
    }
    
    return (pci_read_config_u8 (pci_device, PCI_BIST) & PCI_BIST_CODE_MASK);
}

/* Read interrupt line. */

static void pci_read_irq (pci_device_t *device)
{
    unsigned int irq;
  
    irq = pci_read_config_u8 (device, PCI_INTERRUPT_PIN);
  
    if (irq != 0)
    {
        /* The value 255 is defined as meaning "unknown" or "no connection" 
           to the interrupt controller (as sample: IDE controller say so).  */
        irq = pci_read_config_u8 (device, PCI_INTERRUPT_LINE);
    }

    device->irq = irq;
}

/* Translate the low bits of the PCI base to the resource type. */

static unsigned int pci_get_resource_type (unsigned int flags)
{
    if ((flags & PCI_BASE_ADDRESS_SPACE_IO) != 0)
    {
        return PCI_RESOURCE_IO;
    }
  
    if ((flags & PCI_BASE_ADDRESS_MEM_PREFETCH) != 0)
    {
        return PCI_RESOURCE_MEMORY | PCI_RESOURCE_PREFETCH;
    }
  
    return PCI_RESOURCE_MEMORY;
}

/* Read PCI base addresses. */

static void pci_read_bases (pci_device_t *device, unsigned int amount,
    int rom)
{
    unsigned int position, register_number, next;

    /* FIXME: Find a better name for the 'l' variable. */

    uint32_t l, size;
    pci_resource_t *resource;
  
    for (position = 0; position < amount; position = next) 
    {
        next = position + 1;
        resource = &device->resource[position];
        resource->name = device->device_name;
        register_number = PCI_BASE_ADDRESS_0 + (position << 2);

        l = pci_read_config_u32 (device, register_number);
        pci_write_config_u32 (device, register_number, UINT32_MAX);
        size = pci_read_config_u32 (device, register_number);
        pci_write_config_u32 (device, register_number, l);

        if (size == 0 || size == 0xFFFFFFFF)
        {
          continue;
        }

        if (l == 0xFFFFFFFF)
        {
            l = 0;
        }

        if ((l & PCI_BASE_ADDRESS_SPACE) == PCI_BASE_ADDRESS_SPACE_MEMORY) 
        {
            resource->start = l & PCI_BASE_ADDRESS_MEM_MASK;
            size = ~(size & PCI_BASE_ADDRESS_MEM_MASK);
        }
        else 
        {
            resource->start = l & PCI_BASE_ADDRESS_IO_MASK;
            size = ~(size & PCI_BASE_ADDRESS_IO_MASK) & 0xFFFF;
        }

        resource->end = resource->start + (unsigned long) size;
        resource->flags |= (l & 0xF) | pci_get_resource_type (l);

        if ((l & (PCI_BASE_ADDRESS_SPACE | PCI_BASE_ADDRESS_MEM_TYPE_MASK)) ==
            (PCI_BASE_ADDRESS_SPACE_MEMORY | PCI_BASE_ADDRESS_MEM_TYPE_64)) 
        {
            l = pci_read_config_u32 (device, register_number + 4);
            next++;
      
            if (l != 0) 
            {
                resource->start = 0;
                resource->flags = 0;

                continue;
            }
        }
    }

    if (rom != 0)
    {
        device->rom_base_reg = rom;
        resource = &device->resource[PCI_ROM_RESOURCE];
        l = pci_read_config_u32 (device, rom);
        pci_write_config_u32 (device, rom, ~PCI_ROM_ADDRESS_ENABLE);
        size = pci_read_config_u32 (device, rom);
        pci_write_config_u32 (device, rom, l);

        if (l == 0xFFFFFFFF)
        {
            l = 0;
        }

        if (size != 0 && size != 0xFFFFFFFF) 
        {
            resource->flags = ((l & PCI_ROM_ADDRESS_ENABLE) |
                PCI_RESOURCE_MEMORY | PCI_RESOURCE_PREFETCH | 
                PCI_RESOURCE_READONLY | PCI_RESOURCE_CACHEABLE);
            resource->start = l & PCI_ROM_ADDRESS_MASK;
            size = ~(size & PCI_ROM_ADDRESS_MASK);
            resource->end = resource->start + (unsigned long) size;
        }
    
        resource->name = device->device_name;
    }
}

/* Fill in class and map information of a device. */

static bool pci_setup_device (pci_device_t *device)
{
    uint32_t class;
    char *p;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "%s:\n", __FUNCTION__);

    /* Set the name. */

    string_print (device->slot_name, "%02x:%02x.%d", device->bus->number, 
        PCI_SLOT (device->device_function), PCI_FUNC (device->device_function));

    p = (char *) device_get_name (device->vendor_id, device->device_id);

    if( p != NULL)
    {
        string_copy (device->device_name, p);
    }
    else
    {
        string_copy (device->device_name, "<UNKNOWN>");
    }

    p = (char *)vendor_get_name(device->vendor_id);

    if( p != NULL)
    {
        string_copy (device->vendor_name, p);
    }
    else
    {
        string_copy (device->device_name, "<UNKNOWN>");
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "Slot name=\"%s\", Vendor=\"%s\", Device=\"%s\"", 
        device->slot_name, device->vendor_name, device->device_name);

    device->has_bist = device_has_bist (device);

    /* Read the 3-byte class. (?) */
  
    class = pci_read_config_u32 (device, PCI_CLASS_REVISION);

    device->revision_id = class & 0xFF;
    class >>= 8;
    device->class = class;

//    device->class_id = (class >> 16) & 0xFF;
    device->subclass_id = (class >> 8) & 0xFF;
    device->interface_id = class & 0xFF;

    class >>= 8;

    /* Handle erroneous cases first. (In Linux, they use evil gotos for
       this...) */

    if ((device->header_type == PCI_HEADER_TYPE_BRIDGE && 
         class != PCI_CLASS_BRIDGE_PCI) ||
        (device->header_type == PCI_HEADER_TYPE_CARDBUS &&
         class != PCI_CLASS_BRIDGE_CARDBUS))
    {
        device->class = PCI_CLASS_NOT_DEFINED;

        return TRUE;
    }       
  
    switch (device->header_type)
    {
        /* Standard header. */

        case PCI_HEADER_TYPE_NORMAL:
        {
            pci_read_irq (device);
            pci_read_bases (device, 6, PCI_ROM_ADDRESS);
        
            device->subsystem_vendor_id = pci_read_config_u16 (device, 
                PCI_SUBSYSTEM_VENDOR_ID);
        
            device->subsystem_device_id = pci_read_config_u16 (device, 
                PCI_SUBSYSTEM_ID);
        
            break;
        }

        /* Bridge header. */

        case PCI_HEADER_TYPE_BRIDGE:
        {
            pci_read_bases (device, 2, PCI_ROM_ADDRESS1);
            break;
        }
         
        /* CardBus bridge header. */

        case PCI_HEADER_TYPE_CARDBUS:
        {
            pci_read_irq (device);
            pci_read_bases (device, 1, 0);
        
            device->subsystem_vendor_id = pci_read_config_u16 (device, 
                PCI_CARDBUS_SUBSYSTEM_VENDOR_ID);
        
            device->subsystem_device_id = pci_read_config_u16 (device, 
                PCI_CARDBUS_SUBSYSTEM_ID);
        
            break;
        }

        /* Unknown header. */
        default:
        {
            return FALSE;
        }
    }

    device->class_id = (device->class >> 16) & 0xFF;
    p = (char *) class_get_name (device->class_id);
  
    if( p != NULL)
    {
        string_copy (device->class_name, p);
    }
    else
    {
        string_copy (device->class_name, "<UNKNOWN>");
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "Device class=\"%s\"\n", 
        device->class_name);

    /* We found a fine healthy device, go go go... */

    return TRUE;
}

/* Read the config data for a PCI device, sanity-check it and fill in
   the device structure... */

static pci_device_t *pci_scan_device (pci_device_t *input_device)
{
    pci_device_t *device;
    uint32_t vendor_id;

    vendor_id = pci_read_config_u32 (input_device, PCI_VENDOR_ID);
  
    /* Some broken boards return 0 or ~0 if a slot is empty. */

    if (vendor_id == 0xFFFFFFFF || vendor_id == 0x00000000 || 
        vendor_id == 0x0000FFFF || vendor_id == 0xFFFF0000)
    {
        return NULL;
    }
  
    memory_allocate ((void **) &device, sizeof (pci_device_t));

    if (device == NULL)
    {
        return NULL;
    }
  
    memory_copy (device, input_device, sizeof (pci_device_t));

    device->vendor_id = vendor_id & 0xFFFF;
    device->device_id = (vendor_id >> 16) & 0xFFFF;
  
    /* Assume 32-bit PCI; let 64-bit PCI cards (which are far rarer)
       set this higher, assuming the system even supports it.  */

    if (!pci_setup_device (device)) 
    {
        memory_deallocate ((void **) &device);
    }

    return device;
}

/* Scan the given PCI slot. */

static pci_device_t *pci_scan_slot (pci_device_t *input_device)
{
    pci_device_t *device;
    pci_device_t *first_device = NULL;
    int function = 0;
    bool is_multi = FALSE;
    uint8_t header_type;
    
    for (function = 0; function < 8; function++,
        input_device->device_function++) 
    {
        if (function != 0 && !is_multi)
        {
            continue;
        }

        header_type = pci_read_config_u8 (input_device, PCI_HEADER_TYPE);
        input_device->header_type = header_type & 0x7F;
        device = pci_scan_device (input_device);
    
        if (device == NULL)
        {
            continue;
        }

        if (function == 0)
        {
            is_multi = (header_type & 0x80) == 0x80;
            first_device = device;
        }
    
        /* Add this device to the linked list. */

        list_node_insert ((list_t *) &pci_device_list,
            (list_node_t *) device, LIST_OPTION_LAST);
    }
    
    return first_device;
}

/**
 * pci_find_capability - query for devices' capabilities 
 * @dev: PCI device to query
 * @cap: capability code
 *
 * Tell if a device supports a given PCI capability.
 * Returns the address of the requested capability structure within the
 * device's PCI configuration space or 0 in case the device does not
 * support it.  Possible values for @cap:
 *
 *  %PCI_CAP_ID_PM           Power Management 
 *
 *  %PCI_CAP_ID_AGP          Accelerated Graphics Port 
 *
 *  %PCI_CAP_ID_VPD          Vital Product Data 
 *
 *  %PCI_CAP_ID_SLOTID       Slot Identification 
 *
 *  %PCI_CAP_ID_MSI          Message Signalled Interrupts
 *
 *  %PCI_CAP_ID_CHSWP        CompactPCI HotSwap 
 */
static return_t pci_find_capability (pci_device_t *device, int capability)
{
    uint16_t status;
    uint8_t pos, id;
    int ttl = 48;

    status = pci_read_config_u16 (device, PCI_STATUS);
	
	if (!(status & PCI_STATUS_CAPABILITY_LIST))
	{
        return 0;
    }
    
    switch (device->header_type) 
    {
    case PCI_HEADER_TYPE_NORMAL:
    case PCI_HEADER_TYPE_BRIDGE:
        pos = pci_read_config_u8 (device, PCI_CAPABILITY_LIST);
		break;
    case PCI_HEADER_TYPE_CARDBUS:
		pos = pci_read_config_u8 (device, PCI_CARDBUS_CAPABILITY_LIST);
		break;
    default:
        return 0;
	}
	
	while (ttl-- && pos >= 0x40)
    {
        pos &= ~3;
        id = pci_read_config_u8 (device, pos + PCI_CAPABILITY_LIST_ID);
        
        if (id == 0xff)
        {
            break;
        }
        
        if (id == capability)
        {
            return pos;
        }
        
        pos = pci_read_config_u8 (device, pos + PCI_CAPABILITY_LIST_NEXT);
    }
    
    return 0;
}

/**
 * pci_set_power_state - Set the power state of a PCI device
 * @dev: PCI device to be suspended
 * @state: Power state we're entering
 *
 * Transition a device to a new power state, using the Power Management 
 * Capabilities in the device's config space.
 *
 * RETURN VALUE: 
 * -EINVAL if trying to enter a lower state than we're already in.
 * 0 if we're already in the requested state.
 * -EIO if device does not support PCI PM.
 * 0 if we can successfully change the power state.
 */

return_t pci_set_power_state (pci_device_t *device, int state)
{
    int pm;
    uint16_t pmcsr;

    /* bound the state we're entering */
    if (state > 3) state = 3;

    /* Validate current state:
     * Can enter D0 from any state, but if we can only go deeper 
     * to sleep if we're already in a low power state
     */
    if (state > 0 && device->current_state > state)
    {
        return -1;
    }
    else if (device->current_state == state) 
    {
        return 0;        /* we're already there */
    }

    /* find PCI PM capability in list */
    pm = pci_find_capability (device, PCI_CAPABILITY_ID_PM);
	
    /* abort if the device doesn't support PM capabilities */
    if (!pm)
    {
        return -1; 
    }

    /* check if this device supports the desired state */
    if (state == 1 || state == 2)
    {
        uint16_t pmc;
        
        pmc = pci_read_config_u16 (device, pm + PCI_PM_PMC);
        
        if (state == 1 && !(pmc & PCI_PM_CAPABILITY_D1))
        {
            return -1;
        }
        else if (state == 2 && !(pmc & PCI_PM_CAPABILITY_D2))
        {
            return -1;
        }
    }

    /* If we're in D3, force entire word to 0.
     * This doesn't affect PME_Status, disables PME_En, and
     * sets PowerState to 0.
     */
    if (device->current_state >= 3)
    {
        pmcsr = 0;
    }
    else 
    {
        pmcsr = pci_read_config_u16 (device, pm + PCI_PM_CONTROL);
        pmcsr &= ~PCI_PM_CONTROL_STATE_MASK;
        pmcsr |= state;
    }

    /* enter specified state */
    pci_write_config_u16 (device, pm + PCI_PM_CONTROL, pmcsr);

    /* Mandatory power management transition delays */
    /* see PCI PM 1.1 5.6.1 table 18 */
    if (state == 3 || device->current_state == 3)
    {
//        set_current_state (TASK_UNINTERRUPTIBLE);
//        schedule_timeout(HZ/100);
    }
    else if (state == 2 || device->current_state == 2)
    {
//        udelay(200);
        timer_sleep_milli (200);
    }
    
    device->current_state = state;

    return 0;
}

return_t pci_enable_resources (pci_device_t *device)
{
    uint16_t cmd, old_cmd;
    int idx;
    pci_resource_t *r;

    cmd = pci_read_config_u16 (device, PCI_COMMAND);
    
    old_cmd = cmd;
    
    for (idx = 0; idx < 6; idx++)
    {
        r = &device->resource[idx];
        
        if (!r->start && r->end) 
        {
            DEBUG_PRINT (DEBUG_LEVEL_ERROR,
                "PCI: Device %s not available because of resource collisions\n", 
                device->slot_name);
                
            return -1;
        }
        
        if (r->flags & PCI_RESOURCE_IO)
        {
            cmd |= PCI_COMMAND_IO;
        }
        
        if (r->flags & PCI_RESOURCE_MEMORY)
        {
            cmd |= PCI_COMMAND_MEMORY;
        }
    }
    
    if (device->resource[PCI_ROM_RESOURCE].start)
    {
        cmd |= PCI_COMMAND_MEMORY;
    }
    
    if (cmd != old_cmd) 
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
            "PCI: Enabling device %s (%04x -> %04x)\n", 
            device->slot_name, old_cmd, cmd);
        
        pci_write_config_u16 (device, PCI_COMMAND, cmd);
    }
    
    return 0;
}

/**
 * pci_enable_device - Initialize device before it's used by a driver.
 * @dev: PCI device to be initialized
 *
 *  Initialize device before it's used by a driver. Ask low-level code
 *  to enable I/O and memory. Wake up the device if it was suspended.
 *  Beware, this function can fail.
 */
return_t pci_enable_device (pci_device_t *device)
{
//	int err;

	pci_set_power_state (device, 0);
	
//    if ((err = pcibios_enable_resources(dev)) < 0)
//        return err;
//    pcibios_enable_irq(dev);

	return 0;
}

/**
 * pci_disable_device - Disable PCI device after use
 * @dev: PCI device to be disabled
 *
 * Signal to the system that the PCI device is not in use by the system
 * anymore.  This only involves disabling PCI bus-mastering, if active.
 */
void pci_disable_device (pci_device_t *device)
{
    uint16_t pci_command;

    pci_command = pci_read_config_u16 (device, PCI_COMMAND);
    
    if (pci_command & PCI_COMMAND_MASTER) 
    {
        pci_command &= ~PCI_COMMAND_MASTER;
        pci_write_config_u16 (device, PCI_COMMAND, pci_command);
    }
}

/**
 * pci_enable_wake - enable device to generate PME# when suspended
 * @dev: - PCI device to operate on
 * @state: - Current state of device.
 * @enable: - Flag to enable or disable generation
 * 
 * Set the bits in the device's PM Capabilities to generate PME# when
 * the system is suspended. 
 *
 * -EIO is returned if device doesn't have PM Capabilities. 
 * -EINVAL is returned if device supports it, but can't generate wake events.
 * 0 if operation is successful.
 * 
 */
return_t pci_enable_wake (pci_device_t *device, uint32_t state, int enable)
{
    int pm;
    uint16_t value;

    /* find PCI PM capability in list */
    pm = pci_find_capability (device, PCI_CAPABILITY_ID_PM);

    /* If device doesn't support PM Capabilities, but request is to disable
     * wake events, it's a nop; otherwise fail */
    if (!pm)
    { 
        return enable ? -1 : 0;
    }

    /* Check device's ability to generate PME# */
    value = pci_read_config_u16 (device, pm + PCI_PM_PMC);

    value &= PCI_PM_CAPABILITY_PME_MASK;
    value >>= ffs (value);   /* First bit of mask */

    /* Check if it can generate PME# from requested state. */
    if (!value || !(value & (1 << state))) 
    {
        return enable ? -1 : 0;
    }

    value = pci_read_config_u16 (device, pm + PCI_PM_CONTROL);

    /* Clear PME_Status by writing 1 to it and enable PME# */
    value |= PCI_PM_CONTROL_PME_STATUS | PCI_PM_CONTROL_PME_ENABLE;

    if (!enable)
    {
        value &= ~PCI_PM_CONTROL_PME_ENABLE;
    }

    pci_write_config_u16 (device, pm + PCI_PM_CONTROL, value);
	
    return 0;
}

static unsigned int pci_max_latency = 255;

/**
 * pci_set_master - enables bus-mastering for device dev
 * @dev: the PCI device to enable
 *
 * Enables bus-mastering on the device and calls pcibios_set_master()
 * to do the needed arch specific settings.
 */
void pci_set_master (pci_device_t *device)
{
    uint16_t cmd;
    uint8_t latency;

    cmd = pci_read_config_u16 (device, PCI_COMMAND);
    
    if (!(cmd & PCI_COMMAND_MASTER))
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
            "PCI: Enabling bus mastering for device %s\n", 
            device->slot_name);
            
        cmd |= PCI_COMMAND_MASTER;
        pci_write_config_u16 (device, PCI_COMMAND, cmd);
	}

    latency = pci_read_config_u8 (device, PCI_LATENCY_TIMER);
    
    if (latency < 16)
    {
        latency = (64 <= pci_max_latency) ? 64 : pci_max_latency;
    }
    else if (latency > pci_max_latency)
    {
        latency = pci_max_latency;
    }
    else
    {
        return;
    }
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "PCI: Setting latency timer of device %s to %d\n", 
        device->slot_name, latency);

    pci_write_config_u8 (device, PCI_LATENCY_TIMER, latency);
}

/* Scan the given bus. */

static pci_bus_t *pci_scan_bus (int bus_number, pci_operation_t *operation)
{
    pci_bus_t *bus;
    unsigned int device_function;
    pci_device_t device;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Scaning bus: %u.\n", bus_number);

    memory_allocate ((void **) &bus, sizeof (pci_bus_t));
    
    bus->number = bus->secondary = bus_number;
    bus->operation = (struct pci_operation_t *) operation;

    device.bus = bus;
    
    /* Find all the devices on this bus. */

    for (device_function = 0; device_function < 0x100; device_function += 8) 
    {
        device.device_function = device_function;
        pci_scan_slot (&device);
    }

    return bus;
}

/* Initialisation code. */

bool pci_init (void)
{
    /* Register the ports we need. */

    io_port_register (PCI_BASE, PCI_PORTS, "PCI controller");

    pci_operation = pci_detect ();

    if (pci_operation == NULL)
    {
        return FALSE;
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "PCI Detected.\n");

    /* Scan this bus. */

    list_node_insert ((list_t *) &pci_bus_list, 
        (list_node_t *) pci_scan_bus (0, pci_operation), LIST_OPTION_LAST);

    pci_scan_bus (1, pci_operation);
/*  
    if (root_bus != NULL)
    {
//        (pci_bus_t *) root_bus->next = pci_scan_bus (1, pci_operation);
    }
*/
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "PCI init ends.\n");

    return TRUE;
}
