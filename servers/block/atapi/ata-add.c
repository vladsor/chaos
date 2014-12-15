
static inline u8 lba_to_sector_number (device_type *device, u32 linear_sector)
{
  return (linear_sector %
          device->sectors_per_track) + 1;
}

static inline u8 lba_to_cylinder_low (device_type *device, u32 linear_sector)
{
  return (linear_sector /
          (device->number_of_heads *
           device->sectors_per_track)) & 0xFF;
}

static inline u8 lba_to_cylinder_high (device_type *device, u32 linear_sector)
{
  return ((linear_sector /
           (device->number_of_heads *
            device->sectors_per_track)) >> 8) & 0xFF;
}

static inline u8 lba_to_head (device_type *device, u32 linear_sector)
{
  return ((linear_sector /
           device->sectors_per_track) %
          device->number_of_heads);
}



ata_drive_type *ata_probe (ata_probe_type *ata_probe_drive)
{
  unsigned int temp, temp1, temp2;
 
  ata_drive_type *ata_drive;
  ata_identify_drive_type drive_info;
  
  if (!ata_select_device (ata_probe_drive))
  {
    return NULL;
  }

  temp1 = system_port_in_u8 (
          ATA_SECTOR_COUNT_REGISTER(ata_probe_drive->base_port));

  temp2 = system_port_in_u8 (
          ATA_SECTOR_NUMBER_REGISTER(ata_probe_drive->base_port));

  if (temp1 != 0x01 || temp2 != 0x01)
  {
    log_print (&log_structure, LOG_URGENCY_DEBUG,
               "nothing there");
    return NULL;
  }

  memory_allocate ( (void **)&ata_drive, sizeof(ata_drive_type));

  ata_drive->base_port    = ata_probe_drive->base_port;
  ata_drive->base_irq     = ata_probe_drive->irq;
  ata_drive->master_slave = ata_probe_drive->master_slave;

  temp1 = system_port_in_u8 (
          ATA_CYLINDER_LOW_REGISTER(ata_probe_drive->base_port));

  temp2 = system_port_in_u8 (
          ATA_CYLINDER_HIGH_REGISTER(ata_probe_drive->base_port));

  temp  = system_port_in_u8 (
          ATA_STATUS_REGISTER(ata_probe_drive->base_port));

  interrupt_occured = FALSE;

  if (temp1 == 0x14 && temp2 == 0xEB)
  {
    log_print (&log_structure, LOG_URGENCY_DEBUG,
               "ATAPI CD-ROM");
    ata_device->device_type = ATA_CDROM;

    /* issue ATAPI 'identify drive' command */
    system_port_out_u8 (ATA_COMMAND_REGISTER(ata_probe->base_port), 
                        ATA_COMMAND_IDENTIFY_PACKET_DEVICE);
  }
  else if(Temp1 == 0 && Temp2 == 0 && Temp)
  {
    log_print (&log_structure, LOG_URGENCY_DEBUG,
               "ATA hard drive");
    ata_device->device_type = ATA_HARD_DRIVE;

    /* issue ATA 'identify drive' command */
    system_port_u8 (ATA_COMMAND_REGISTER(ata_device->base_port), 
                    ATA_COMMAND_IDENTIFY_DEVICE);
  }
  else
  {
    log_print (&log_structure, LOG_URGENCY_DEBUG,
               "unknown drive type");
    ata_device->device_type = ATA_UNKNOWN;
    
    return ata_device;
  }

  /* ATA or ATAPI: get results of of identify */

//  system_sleep(400);
/*
  if (awaitInterrupt(0xC000, Temp) == 0)
  {
    printf("'identify' failed\n");
    return FALSE;
  }
*/

  /* grab info returned by 'identify' */
  system_port_in_u8 (ATA_STATUS_REGISTER(ata_probe->base_port));

  system_port_in_u8_string (ATA_DATA_REGISTER(ata_probe->base_port), 
                            (u16 *)&drive_info, sizeof(drive_info) >> 1);

  temp2 = 1;

  for ( temp = 0 ; temp < 40 ; temp += 2 )
  {
    printf ("%c", drive_info.model[Temp ^ Temp2]);
    printf ("%c", drive_info.model[Temp ^ Temp2 ^ 1]); 
  }
/*
  printf("\n	CHS=%u:%u:%u, ",
          drive_info.PhysCyls, drive_info.PhysHeads,  drive_info.PhysSects);

  ata_device->number_of_sectors = drive_info.PhysSects;
  ata_device->number_of_heads = drive_info.PhysHeads;
  ata_device->number_of_cylinders = drive_info.PhysCyls;
*/
  if (drive_info.capabilities[0] & 1)
  {
    log_print (&log_structure, LOG_URGENCY_DEBUG,
               "DMA");
    ata_device->dma = TRUE; 
  }
  if (drive_info.Capabilities & 2)
  {
    log_print (&log_structure, LOG_URGENCY_DEBUG,
               "LBA");
    ata_device->lba = TRUE; 
  }
/*
  if ((DriveInfo.MultSectValid & 1) && DriveInfo.MultSect)
  {
    Temp = DriveInfo.MaxMult;
    printf("MaxMult=%u, ", Temp); 
  }
  else Temp=1;
  Drive[WhichDrive].MultSect = Temp;
  ata_device->cache_size = (DriveInfo.BufSize >> 1);
*/
  return ata_drive;
}


/* Read one or more sectors from a device. */
/* FIXME: Do rangechecking in all neccessary ways. */

bool sectors_read (ata_drive_type *ata_drive,
                   u32 sector_number, unsigned int number_of_sectors,
                   void *buffer)
{
  u8 status, error;

  /* Range check number of sectors to read, and convert to ATA way. */

  if (number_of_sectors == 0 || number_of_sectors > 256)
  {
    return FALSE;
  }
  if (number_of_sectors == 256)
  {
    number_of_sectors = 0;
  }

  log_print_formatted (&log_structure, LOG_URGENCY_DEBUG,
                       "Reading %u sectors...", number_of_sectors);

  /* Wait for BSY to clear. */

  while ((system_port_in_u8 (interface->io_base + REGISTER_ALTERNATE_STATUS) & BIT_BSY) != 0);

  /* FIXME: Investigate this!!! */

#if FALSE
  if (interface->device[device]->lba)
  {
    /* This device supports LBA addressing mode. */

    log_print (&log_structure, LOG_URGENCY_DEBUG, "LBA");
    
    system_port_out_u8 (interface->io_base + REGISTER_DEVICE_HEAD,
                        ((sector_number >> 24) & 0x0F) | BIT_LBA |
                        (device == 0) ? DEVICE_MASTER : DEVICE_SLAVE);

    /* Wait for controller. */

    while ((system_port_in_u8 (interface->io_base + REGISTER_ALTERNATE_STATUS) & BIT_BSY) != 0 ||
           (system_port_in_u8 (interface->io_base + REGISTER_ALTERNATE_STATUS) & BIT_DRDY) == 0);

    system_port_out_u8 (interface->io_base + REGISTER_SECTOR_NUMBER,
                        sector_number & 0xFF);
    system_port_out_u8 (interface->io_base + REGISTER_CYLINDER_LOW,
                        (sector_number >> 8) & 0xFF);
    system_port_out_u8 (interface->io_base + REGISTER_CYLINDER_HIGH,
                        (sector_number >> 16) & 0xFF);
  }
  else
#endif

  {
    /* CHS addressing mode. */

    log_print (&log_structure, LOG_URGENCY_DEBUG, "CHS");

    system_port_out_u8 (interface->io_base + REGISTER_DEVICE_HEAD,
                        lba_to_head (interface->device[device],
                                     sector_number) |
                        (device == 0) ? DEVICE_MASTER : DEVICE_SLAVE);

    /* Wait for controller. */

    while ((system_port_in_u8 (interface->io_base + REGISTER_ALTERNATE_STATUS) & BIT_BSY) != 0 ||
           (system_port_in_u8 (interface->io_base + REGISTER_ALTERNATE_STATUS) & BIT_DRDY) == 0);

    system_port_out_u8 (interface->io_base + REGISTER_SECTOR_NUMBER,
                        lba_to_sector_number (interface->device[device],
                                              sector_number));
    system_port_out_u8 (interface->io_base + REGISTER_CYLINDER_LOW,
                        lba_to_cylinder_low (interface->device[device],
                                             sector_number));
    system_port_out_u8 (interface->io_base + REGISTER_CYLINDER_HIGH,
                        lba_to_cylinder_high (interface->device[device],
                                              sector_number));
  }

  /* How many sectors to read? */

  system_port_out_u8 (interface->io_base + REGISTER_SECTOR_COUNT,
                      number_of_sectors);

  /* Send the command. */

  send_command (interface, COMMAND_READ_SECTORS_RETRY);

  /* Read status and ACK controller. */

  status = system_port_in_u8 (interface->io_base + REGISTER_STATUS);
  error = system_port_in_u8 (interface->io_base + REGISTER_ERROR);

  if ((error & BIT_ABRT) == 0 &&
      (status & BIT_ERR) == 0)
  {
    /* Read the sector(s). */

    log_print_formatted (&log_structure, LOG_URGENCY_DEBUG,
                         "Status OK, reading %d bytes from device...",
                         512 * number_of_sectors);

    system_port_in_u16_string (interface->io_base + REGISTER_DATA,
                               (u16 *) buffer, 256 * number_of_sectors);
    return TRUE;
  }
  else
  {
    log_print_formatted (&log_structure, LOG_URGENCY_DEBUG,
                         "An error occured while reading sector(s). status = 0x%X, error = 0x%X.",
                         status, error);

    return FALSE;
  }
}
