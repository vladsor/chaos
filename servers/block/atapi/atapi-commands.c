
bool wait_flags (ata_probe_type *ata_probe, u8 flags)
{
  for (counter = WAIT_READY ; Temp>0 ; Temp-- )
  {
    if ((system_port_in_u8(ATA_STATUS_REGISTER(ata_probe->base_port)) & 
        flags) == 0)
    {
      return TRUE;
    }
    system_sleep(1); 
  }
  return FALSE;
}

bool select_device (ata_probe_type *ata_probe)
{
  if (((system_port_in_u8(ATA_DEVICE_HEAD_REGISTER(ata_probe->base_port)) 
        ^ Sel) & 0x10) == 0) 
  {
   /* already selected */
    return TRUE;
  }

  system_port_out_u8 (ATA_DEVICE_HEAD_REGISTER(ata_probe->base_port),
                      ata_device->master_slave ? 
                      ATA_MASTER_DRIVE_SELECT : ATA_SLAVE_DRIVE_SELECT);

//  system_sleep (400);
  return wait_ready (ata_probe, ATA_STATE_BUSY);
}

bool check_power_mode (ata_probe_type *ata_probe)
{
//  select_device (ata_probe);  
  system_port_out_u8 (ATA_COMMAND_REGISTER(ata_probe->base_port),
                      ATA_COMMAND_CHECK_POWER_MODE);

  return wait_ready (ata_probe, ATA_STATE_BUSY);
}

bool device_reset (ata_probe_type *ata_probe)
{
//  select_device (ata_probe);  
  system_port_out_u8 (ATA_COMMAND_REGISTER(ata_probe->base_port),
                      ATA_COMMAND_DEVICE_RESET);

  return wait_ready (ata_probe, ATA_STATE_BUSY);
}

bool flush_cache (ata_probe_type *ata_probe)
{
//  select_device (ata_probe);  
  system_port_out_u8 (ATA_COMMAND_REGISTER(ata_probe->base_port),
                      ATA_COMMAND_FLUSH_CACHE);
  return wait_ready (ata_probe, ATA_STATE_BUSY);
}

bool get_media_status (ata_probe_type *ata_probe)
{
//  select_device (ata_probe);  
  system_port_out_u8 (ATA_COMMAND_REGISTER(ata_probe->base_port),
                      ATA_COMMAND_GET_MEDIA_STATUS);

  return wait_ready (ata_probe, ATA_STATE_BUSY);
}
