
#include "config.h"
#include "cd-rom.h"
#include "atapi.h"

static ATA_info_type Atp[] =
{
  { 0x1F0, 14, TRUE  },
  { 0x1F0, 14, FALSE },
  { 0x170, 15, TRUE  },
  { 0x170, 15, FALSE },
  { 0x1E0, 10, TRUE  },
  { 0x1E0, 10, FALSE },
  { 0x168, 11, TRUE  },
  { 0x168, 11, FALSE },
};

static unsigned int number_of_ATA_info = sizeof(Atp) / sizeof(ATA_info_type);

ATA_info_type *cdrom_device;
unsigned int device_number;

Cmd5AInfo Buf5A2A;
Inf12Blk Info12Buf;
Inf3Blk  Info3Buf;
TOC10	TrkBuf;


u16 packet_close_tray[6]	= {0x1B, 0, 3, 0, 0, 0};
u16 packet_eject_tray[6]	= {0x1B, 0, 2, 0, 0, 0};
u16 packet_lock_tray[6]		= {0x1E, 0, 1, 0, 0, 0};
u16 packet_unlock_tray[6]	= {0x1E, 0, 0, 0, 0, 0};
u16 packet_read_sectors[6]	= {0xBE, 0, 0, 0, 0, 0};
u16 packet_read_max_sectors[6]	= {0xB9, 0, 0, 0, 0, 0};

word Info5A2A[6]	= {0x5A, 0xAA, 0, 0, 0x1C, 0};
word Info12[6]		= {0x12, 0, sizeof(Inf12Blk), 0, 0, 0};
word Info3[6]		= {0x3, 0, sizeof(Inf3Blk), 0, 0, 0};
word RdToc[6]		= {0x243, 0, 0, 1, sizeof(TOC10), 0};
word PlaySt[6]		= {0x47, 0, 0, -1, 255, 0};


static bool reset_drive (int port)
{
  int i;
  log_print_formatted (&log_structure, LOG_URGENCY_EMERGENCY,
                         "Reseting device...");
  system_port_out_u8 (port + 7, 8);
  system_port_out_u8 (port + 0x206, 0xE);
  system_sleep (10);
  system_port_out_u8 (port + 0x206, 8);
  system_sleep (10);
  for ( i = 0 ; i < 200 ; i++ )
  {
    if ((system_port_in_u8 (port + 7) & 0x88) == 0)
    {
      log_print_formatted (&log_structure, LOG_URGENCY_EMERGENCY,
                         "Reset Succesfull.");
      return TRUE;
    }
    else 
    {
      system_sleep (10);
    }
  }
  log_print_formatted (&log_structure, LOG_URGENCY_EMERGENCY,
                         "Reset Fail.");
  return FALSE;
}

static bool ATAPI_CD_probe (unsigned int devnum)
{
  int port = Atp[devnum].port;
  int i;

  /* select active drive */
  system_port_out_u8 (port + 6, Atp[devnum].ms ? 0xA0 : 0xB0);
  system_sleep (1);
    
  if (system_port_in_u8 (port + 7) == 0xFF)
  {
    return FALSE;
  }
    
  if (system_port_in_u8 (port + 7) & 0x80)
  {
    if (!reset_drive (port))
    {
      return FALSE;
    }
  }
  
  system_port_out_u8 (port + 4, 0);
  system_port_out_u8 (port + 5, 0);
  system_port_out_u8 (port + 7, 0xEC);
  for ( i = 0 ; i < 20 ; i++ )
  {
    system_sleep (1);
    if ((system_port_in_u8 (port + 4) == 0x14) &&
        (system_port_in_u8 (port + 5) == 0xEB))
    {
      u16 device_code;

      system_sleep (1);
      system_port_out_u8 (port + 7, 0xA1);
      for ( i = 0 ; i < 100 ; i++ )
      {
        if (system_port_in_u8 (port + 7) & 0x80)
        {
          system_sleep (1);
        }
        else 
        {
          break;
        }
      }
      
      if (i == 100)
      {
        return FALSE;
      }

      system_sleep (10);
      device_code = system_port_in_u16 (port);
      for ( i = 0 ; i < 255 ; i++ )
      {
        system_port_in_u16 (port);
      }
      if ((device_code & 0x1F00) != 0x500)
      {
        return FALSE;
      }
      if (device_code & 1)
      {
	return FALSE;
      }
      return TRUE;
    }
  }
  return FALSE;
}

#define MaxSect 16U

u8 Buffer[2352U*MaxSect];

static u8 Last1X7 = 0;

static void store_lba_to_msf(u32 lba, void *msf)
{
  u8 *msfb = msf;
  lba += 150;
  *msfb++ = lba / (60L * 75L);
  lba %= (60L * 75l);
  *msfb++ = lba / 75L;
  *msfb++ = lba % 75L;
}

static inline u16 GetMSBWord (u16 cd)
{
  return ( (cd >> 8) | (cd << 8));
}

static inline u32 GetMSBDword (u32 cd)
{
  return ( ((cd >> 24)&0x000000FFL) |
           ((cd >>  8)&0x0000FF00L) |
           ((cd <<  8)&0x00FF0000L) |
           ((cd << 24)&0xFF000000L) );
}

bool init (void)
{
  unsigned int devnum;

  for( devnum = 0 ; (devnum < number_of_ATA_info) ; devnum++ )
  {
    log_print_formatted (&log_structure, LOG_URGENCY_EMERGENCY,
                         "Searching CD-ROM...");

    if (system_call_port_range_register (Atp[devnum].port, 8, "ATAPI") !=
        STORM_RETURN_SUCCESS)
    {
      log_print_formatted (&log_structure, LOG_URGENCY_EMERGENCY,
                           "Could not allocate port range %x-%x.",
                           Atp[devnum].port, Atp[devnum].port + 8);
      continue;
    }
    if (system_call_port_range_register (Atp[devnum].port + 0x206, 1, "ATAPI") !=
        STORM_RETURN_SUCCESS)
    {
      log_print_formatted (&log_structure, LOG_URGENCY_EMERGENCY,
                           "Could not allocate port range %x-%x.",
                           Atp[devnum].port + 0x206, Atp[devnum].port + 0x20D);
      continue;
    }

    if (!ATAPI_CD_probe(devnum))
    {
      system_call_port_range_unregister (Atp[devnum].port);
      system_call_port_range_unregister (Atp[devnum].port + 0x206);
      log_print_formatted (&log_structure, LOG_URGENCY_EMERGENCY,
                           "not found.");
    }
    else
    {
      log_print_formatted (&log_structure, LOG_URGENCY_EMERGENCY,
                           "found CD-ROM.");
      cdrom_device = &Atp[devnum];
      device_number = devnum;
      return TRUE;
    }
  }
  return FALSE;
}

/* wait of bits set */
static bool bit_mask_wait (int port, int mask, int bits, int seconds)
{
  u32 counter;
  log_print_formatted (&log_structure, LOG_URGENCY_EMERGENCY,
                         "Waiting device...");
  for ( counter = seconds * 1000L ; counter > 0 ; counter-- )
  {
    int i;
    i = system_port_in_u8(port);
    if ((port & 7) == 7)
    {
      Last1X7 = i;
    }
    if ((i & mask) == bits)
    {
      log_print_formatted (&log_structure, LOG_URGENCY_EMERGENCY,
                           "Waiting OK.");
      return TRUE;
    }
    system_sleep (1);
  }
  log_print_formatted (&log_structure, LOG_URGENCY_EMERGENCY,
                       "Waiting Fail.");
  return FALSE;
}

static word PrefIOBlock = 0x8000;
static bool DontResetFlg = FALSE;

bool exec_ATAPI_command (ATA_info_type *ata_device, int dir,
                         u16 *command_packet, u16 *buffer, unsigned int bufflen)
{
  int port;
  int i;
  int readed = 0;
  int size;
  u16 pl;

  log_print_formatted (&log_structure, LOG_URGENCY_EMERGENCY,
			 "Executing ATAPI command...");

  port = ata_device->port;
  /* select active drive */
  system_port_out_u8 (port + 6, ata_device->ms ? 0xA0 : 0xB0);

  while (TRUE)
  {
    Last1X7 = system_port_in_u8 (port + 7);
    if (!(Last1X7 & 0x88))
    {
      break;
    }
    if (DontResetFlg)
    {
      return FALSE;
    }
    reset_drive (port);
    
    /* Wait for end of reset command */
    if (!bit_mask_wait (port + 7, 0x80, 0x0, 10))
    {
      return FALSE;	/* Not ready */
    }
  }

  /* set size of block */
  if (PrefIOBlock > bufflen)
  {
    pl = bufflen;
  }
  else
  {
    pl = PrefIOBlock;
  }
  system_port_out_u8 (port + 4, pl);
  system_port_out_u8 (port + 5, pl >> 8);

  /* Disabling  */
  system_port_out_u8 (port + 1, 0);

  /* Begin */
  system_port_out_u8 (port + 7, 0xA0);

  /* Waiting for Ready */
  if (!bit_mask_wait (port + 7, 0x89, 8, 3))
  {
    return FALSE;
  }

//  disable();
  log_print_formatted (&log_structure, LOG_URGENCY_EMERGENCY,
			 "Sending command...");
  for ( i = 0 ; i < 6 ; i++ )
  {
    system_port_out_u16 (port, *command_packet);
    command_packet++;
  }
  log_print_formatted (&log_structure, LOG_URGENCY_EMERGENCY,
			 "Sending command...End");
//  enable();

  GetNextBlk:

  bit_mask_wait (port + 7, 0x80, 0x00, 30);
  size = system_port_in_u8 (port + 4) | (system_port_in_u8 (port + 5) << 8);
  Last1X7 = system_port_in_u8 (port + 7);

  if (Last1X7 & 1)
  {
    return FALSE;
  }

  if (Last1X7 & 8)
  {
    if (system_port_in_u8(port+2) & 2) 
    {
      if (dir == 1 && buffer != NULL )
      {
	while (size > 0)
        {
	  int k = system_port_in_u16 (port);
          size -= 2;
	  if (bufflen < 1)
	  {
	    break;
	  }
	  *buffer++ = k;
	  readed += 2;
	  bufflen -= 2;
	}
      }

      while ((size -= 2) > 0)
      {
	system_port_in_u16 (port);
      }
    }
    else
    {
      if (dir == 0 && buffer != NULL)
      {
	while (bufflen > 0 && size > 0)
	{
	  if (bufflen < 1)
	  {
	    break;
	  }
	  system_port_out_u16 (port, *buffer++);
	  bufflen -= 2;
	  readed += 2;
	  size -= 2;
	}
      }

      while ((size -= 2) > 0)
      {
	system_port_out_u16 (port,0);
      }
    }
    goto GetNextBlk;
  }

  Last1X7 = system_port_in_u8 (port + 7);
  if (Last1X7 & 1)
  {
    return FALSE;
  }

  return TRUE;
}

#if TRUE
bool read_block (ATA_info_type *ata_device, u32 start_block, 
                 u8 *buffer, unsigned int number_of_blocks)
{
  u32 length;
  u32 current_sector = start_block;

  {
    store_lba_to_msf (current_sector, ((u8 *)packet_read_max_sectors) + 3);
    store_lba_to_msf (current_sector + MaxSect,((u8 *)packet_read_max_sectors) + 6);
    ((u8 *)packet_read_max_sectors)[9] = 0x10;
    if (!exec_ATAPI_command (ata_device, 1, packet_read_max_sectors, 
        (u16 *) buffer, number_of_blocks))
    {
      log_print (&log_structure, LOG_URGENCY_ERROR,
                 "Error read from CD");
      return FALSE;
    }
    current_sector += MaxSect;
  }
  return TRUE;
}
#endif

#if FALSE
  case CDROM_PLAY_TRACK:
  {
    track = 0;
    PlaySt[1]=TrkBuf.Trk[track].Start[1]<<8;
    PlaySt[2]=TrkBuf.Trk[track].Start[2]|(TrkBuf.Trk[i].Start[3]<<0x8);

    PlaySt[3]=TrkBuf.Trk[i+1].Start[1]|(TrkBuf.Trk[i+1].Start[2]<<0x8);
    PlaySt[4]=TrkBuf.Trk[i+1].Start[3]<<8;

    if (exec_ATAPI_command(workdrv,0,PlaySt,NULL,0))
    {
      /* Ok */
    }
    else
    {
      /* Fail */
    }
    break;
  }

  case CDROM_EJECT:
  {
    if (ExecATAPICMD(workdrv,0,EjectPkt,NULL,0))
    {
      /* Ok */;
    }
    else
    {
      /* Fail */;
    }
    break;
  }

  case CDROM_CLOSE:
  {
    if(ExecATAPICMD(workdrv,0,ClosePkt,NULL,0))
    {
      cprintf("Ok");
    }
    else
    {
      printf("Fail");
    }
    break;
  }

  case CDROM_INFO:
  {
    if (ExecATAPICMD(workdrv,1,Info5A2A,(void*)&Buf5A2A,sizeof(Buf5A2A)))
    {
      cprintf("MaxSpd: %d, CurSpd: %d, Buff: %d Kb",
			GetMSBWord(Buf5A2A.maxspeed),
			GetMSBWord(Buf5A2A.curspeed),
			GetMSBWord(Buf5A2A.bufsize));
    }
    else cprintf("Fail");
	break;

case 'M':
case 'm':
	if(ExecATAPICMD(workdrv,1,Info12,(void*)&Info12Buf,sizeof(Info12Buf))>0){
	cprintf("Manuf: [%8.8s], Prod: [%16.16s], Rev: [%4.4s]",
			Info12Buf.Manuf,
			Info12Buf.Prod,
			Info12Buf.Rev);
	}
	else cprintf("Fail");
	break;

case 'l':
case 'L':cprintf("Lock tray....");
	if(ExecATAPICMD(workdrv,0,LockPkt,NULL,0)!=-1)cprintf("Ok");
	else printf("Fail");
	break;

case 'u':
case 'U':cprintf("Unlock tray....");
	if(ExecATAPICMD(workdrv,0,UnlockPkt,NULL,0)!=-1)cprintf("Ok");
	else printf("Fail");
	break;

case 'X':
case 'x':
	if(ExecATAPICMD(workdrv,1,Info3,(void*)&Info3Buf,sizeof(Info3Buf))>0){
	cprintf("Err0: %3.3Xh, Err1: %3.3Xh, Err2: %3.3Xh",
			Info3Buf.err0,
			Info3Buf.err1,
			Info3Buf.err2);
	}
	else cprintf("Fail");
	break;

case 'R':
case 'r':
	if(ExecATAPICMD(workdrv,1,RdToc,(void*)&TrkBuf,sizeof(TrkBuf))>0){
		gotoxy(1,1);
		cprintf("Num   Ctrl/Addr   TrNum    Start");
		{
		 for(i=0;i<10;i++){
		   cprintf("\n\r");
		   clreol();
		   if(i<TrkBuf.EndTrk){
		    cprintf("%2.2d    %3.3Xh        %2.2X     %2.2d:%2.2d:%2.2d",
			i,
			TrkBuf.Trk[i].CA,
			TrkBuf.Trk[i].number,
			TrkBuf.Trk[i].Start[1],
			TrkBuf.Trk[i].Start[2],
			TrkBuf.Trk[i].Start[3]);
		   }


		 }
		}
	}
	else cprintf("Fail");
	break;

case 'w':
case 'W':{FILE *img;
	  word len;
	  long CurSector=0;
	while(kbhit())getch();
	img=fopen("CDImage.bin","wb");
	if(img==NULL)cprintf("Can't open save file !");
	cprintf("Copying sectors. Press any key to abort [");
	do{
		cprintf("/");
		StoreLBAToMSF(CurSector,((byte*)ReadScM)+3);
		StoreLBAToMSF(CurSector+MaxSect,((byte*)ReadScM)+6);
		((byte*)ReadScM)[9]=0x10;
		len=ExecATAPICMD(workdrv,1,ReadScM,(void*)Buffer,sizeof(Buffer));
		if(len==0xFFFF){ cprintf("]CD read fail");goto ecpy;};
		if(len==0){ cprintf("]CD return zero bytes");goto ecpy;}
		cprintf("%u\\",len);
		if(fwrite(Buffer,len,1,img)!=1){
				cprintf("]Error write to disk");
				goto ecpy;
				}
		CurSector+=MaxSect;
	}while(!kbhit());
	while(kbhit())getch();
	cprintf("]Copy stopped");
	ecpy:
	cprintf("(%ld)",CurSector);
	fclose(img);
	break;
	}
#endif