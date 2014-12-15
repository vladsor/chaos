#define         IRQ14_VECTOR            118
#define         IRQ15_VECTOR            119

#define         CHAIN_INTS

//#define               BUFF_SIZE               49152u
#define         BUFF_SIZE               16384

drivecmd Cmd;
char Buffer[BUFF_SIZE];

/*****************************************************************************
        name:   atapiTOC
        action: reads table of contents of audio CD and prints starting
                time of each track
        returns:whatever atapiCmd2() returns
*****************************************************************************/
#define MAX_TRACKS              32

atapimsf Track[MAX_TRACKS];
unsigned NumTracks;

int atapi_TOC (unsigned WhichDrive)
{
    atapi_toc Contents;
    int Temp;

/* read just the header at first */
    Temp = sizeof (atapitocheader);
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "atapiTOC: calling atapiTOCEnt with Count=%u\n", 
        Temp);
    
    Temp = atapi_TOCEnt (&Contents, Temp, WhichDrive);
    
    if (Temp)
    {
        return (Temp);
    }
    
    NumTracks = Contents.Hdr.LastTrk - Contents.Hdr.FirstTrk + 1;
    
    if (NumTracks <= 0 || NumTracks > 99)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, 
            "atapiTOC: bad number of tracks %d\n", 
            NumTracks);
        
        return (-1);
    }
    
    if (NumTracks > MAX_TRACKS)
    {
        DEBUG_PRINT (DEBUG_LEVEL_WARNING, 
            "Too many tracks (%u); reducing to %u.\n",
            NumTracks, MAX_TRACKS);
            
        NumTracks = MAX_TRACKS; 
    }
    
    Temp = sizeof (atapitocheader) + (NumTracks + 1) * sizeof (atapitocentry);
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "atapiTOC: calling atapiTOCEnt with Count=%u\n", 
        Temp);
    
    Temp = atapi_TOCEnt (&Contents, Temp, WhichDrive);

    if (Temp)
    {
        return (Temp);
    }
    
    for (Temp = 0; Temp <= NumTracks; Temp++)
    {
        Track[Temp].Min = Contents.Ent[Temp].Where.Time.Min;
        Track[Temp].Sec = Contents.Ent[Temp].Where.Time.Sec;
        Track[Temp].Frame = Contents.Ent[Temp].Where.Time.Frame;
        
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
            "%02u:%02u:%02u  ",
            Contents.Ent[Temp].Where.Time.Min,
            Contents.Ent[Temp].Where.Time.Sec,
            Contents.Ent[Temp].Where.Time.Frame);
    }
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "\n");
    
    return (0); 
}

#if 0
/*////////////////////////////////////////////////////////////////////////////
                        GENERAL PARTITION STUFF
////////////////////////////////////////////////////////////////////////////*/
/*****************************************************************************
        name:   partProbe
        action: analyzes partitions on ATA drives
*****************************************************************************/
void partProbe(void)
{
    uint8_t Buffer[512], WhichDrive, WhichPart;
    unsigned HiHead, Scale, LHeads, Heads, Sects;
    long int Temp, Track;
    unsigned Offset, Cyls;
    drivecmd Cmd;

    printf("partProbe:\n");
    for(WhichDrive=0; WhichDrive < 4; WhichDrive++)
    {
        if(Drive[WhichDrive].IOAdr == 0)
        {
            continue;
        }
            
        if(Drive[WhichDrive].Flags & ATA_FLG_ATAPI)
        {
            continue;
        }
/* load sector 0 (the partition table) */
                Cmd.Blk=0;
                Cmd.Count=512;
                Cmd.Dev=WhichDrive;
                Cmd.Cmd=DRV_CMD_RD;
                Cmd.Data=Buffer;
                Temp=ataCmd(&Cmd);
                if(Temp < 0) continue;
/* see if it's valid */
                if(Buffer[0x1FE] != 0x55 || Buffer[0x1FF] != 0xAA)
                {       printf("  hd%1u: invalid partition table\n",
                                WhichDrive);
                        continue; }
/* check all four primary partitions for highest Heads value */
                HiHead=0;
                for(WhichPart=0; WhichPart < 4; WhichPart++)
                {       Offset=0x1BE + 16 * WhichPart;
                        if(Buffer[Offset + 1] > HiHead)
                                HiHead=Buffer[Offset + 1];
                        if(Buffer[Offset + 5] > HiHead)
                                HiHead=Buffer[Offset + 5]; }
/* compare highest head value with heads/cylinder value from 'identify'.
Check for LARGE mode and determine Scale. This test will fail unless
partitions end on a cylinder boundary (hopefully, they do). */
                HiHead++;
                LHeads=Drive[WhichDrive].Heads;
                if(HiHead > LHeads)
                {       Scale=HiHead / LHeads;
                        printf("  hd%1u: LARGE mode, N=", WhichDrive);
                        if(Scale * LHeads == HiHead)
                        {       LHeads *= Scale;
                                printf("%u, new CHS=%u:%u:%u\n", Scale,
                                        Drive[WhichDrive].Cyls / Scale,
                                        LHeads,
                                        Drive[WhichDrive].Sects);  }
/* HiHead / Drive[WhichDrive].Heads is not an integer. */
                        else printf("??? (UNKNOWN !!!)\n"); }
/* now print geometry info for all primary partitions. CHS values in each
partition record may be faked for the benefit of MS-DOS/Win, so we ignore
them and use the 32-bit size-of-partition and sectors-preceding-partition
fields to compute CHS */
                for(WhichPart=0; WhichPart < 4; WhichPart++)
                {       Offset=0x1BE + 16 * WhichPart;
/* get 32-bit sectors-preceding-partition; skip if undefined partition */
                        Temp=*(uint32_t *)(Buffer + Offset + 8);
                        if(Temp == 0) continue;
/* convert to CHS, using LARGE mode value of Heads if necessary */
                        Sects=Temp % Drive[WhichDrive].Sects + 1;
                        Track=Temp / Drive[WhichDrive].Sects;
                        Heads=Track % LHeads;
                        Cyls=Track / LHeads;
                        printf("  hd%1u%c: start LBA=%8lu, start CHS=%4u:"
                                "%2u:%2u, ", WhichDrive, 'a' + WhichPart,
                                Temp, Cyls, Heads, Sects);
/* get 32-bit partition size */
                        Temp=*(uint32_t *)(Buffer + Offset + 12);
                        printf("%lu sectors\n", Temp); 
        }
    }
}
#endif

#if 0
/*****************************************************************************
        name:   demo
        action: loads interesting sectors from ATA and ATAPI drives
                and dumps them in hex
*****************************************************************************/
void demo(void)
{
    unsigned Count, WhichDrive;

        for(WhichDrive=0; WhichDrive < 4; WhichDrive++)
        {       if(Drive[WhichDrive].IOAdr == 0) continue;
                Cmd.Dev=WhichDrive;
                Cmd.Cmd=DRV_CMD_RD;
                Cmd.Data=Buffer;
                if(Drive[WhichDrive].Flags & ATA_FLG_ATAPI)
/* CD-ROM has it's root directory at logical block #16. According to
ISO-9660, the first 16 blocks (2048 bytes each) are all zeroes. (These
blocks might now be used for El Torrito boot-from-CD.) */
                {       Count=17;
                        Cmd.Blk=17 - Count;
                        Cmd.Count=Count << ATAPI_LG_SECTSIZE;
                        printf("atapiCmd() returned %d\n", atapiCmd(&Cmd));
                        dump(Buffer + ATAPI_SECTSIZE * (Count - 1), 96); }
                else
/* load first sector of first partition, plus the MultSect sectors before it,
to demonstrate multisector read (if supported) */
                {       Count=Drive[WhichDrive].MultSect + 1;
                        Cmd.Blk=Drive[WhichDrive].Sects + 1 - Count;
                        Cmd.Count=Count << ATA_LG_SECTSIZE;
                        printf("ataCmd() returned %d\n", ataCmd(&Cmd));
                        dump(Buffer + ATA_SECTSIZE * (Count - 1), 96);
        }
    }
}

#ifdef MAIN_TEST

/*****************************************************************************
        name:   main
*****************************************************************************/
int ata_main(void)
{       unsigned Data, WhichDrive, Temp;
        long Blk, Count;

        irqStart();
/* enable IRQ14 and IRQ15 at the 2nd 8259 PIC chip */
//        port_uint8_out(0xA1, port_uint8_in(0xA1) & ~0xC0);

        ataProbe();
    goto BAIL;
    
        partProbe();
#if 0
/* atapiCmd demonstrates data CDs */
        demo();
//#else
/* atapiTOC and atapiPlay demonstrate audio CDs */
        for(WhichDrive=0; WhichDrive < 4; WhichDrive++)
        {       if(Drive[WhichDrive].IOAdr &&
                        (Drive[WhichDrive].Flags & ATA_FLG_ATAPI)) break; }
        if(WhichDrive == 4)
        {       printf("No ATAPI devices detected.\n");
                goto BAIL; }
        printf("\n");
        atapiTOC(WhichDrive);
        for(Count=3; Count; Count--)
/* play from 13:11:32 to 18:01:00 -- Zeppelin */
        {
            Temp=atapiPlay(WhichDrive, (13ul * 60 + 11) * 75 + 32, (18ul * 60 + 1) * 75 + 0);
            if(Temp)
            {
                printf("atapiPlay returned error %d, retrying...\n", Temp);
            }
            else
            {
                break;
            }
        }
#endif

#if 0
#define         START_BLK               2048ul
#define         NUM_BLKS                8192ul
        printf( "\n""********************************************************\n"
                "***                      DANGER!                     ***\n"
                "********************************************************\n"
                "THIS OPERATION WILL ERASE PORTIONS OF YOUR HARD DRIVE!!!\n" "\n"
                "Press 'y' to continue.\n""\x07\x07\x07");
        Temp=getch();
        if(Temp != 'y' && Temp !='Y') goto BAIL;
        printf( "\n""********************************************************\n"
                "***                 SECOND WARNING!                  ***\n"
                "********************************************************\n"
                "Are you sure you want to ERASE YOUR HARD DRIVE?\n" "\n"
                "Press 'p' to proceed.\n""\x07");
        Temp=getch();
        if(Temp != 'p' && Temp != 'P') goto BAIL;
        Cmd.Dev=0;
        srand(2);
        Cmd.Cmd=DRV_CMD_WR;
/* write NUM_BLKS of pseudorandom data to beginning of drive. Skips
START_BLK sectors, which may or may not leave the FAT, DOS kernel files,
and COMMAND.COM intact. THIS ERASES DATA ON THE DRIVE!!! */
        for(Blk=START_BLK; Blk < START_BLK + NUM_BLKS; )
        {       for(Temp=0; Temp < BUFF_SIZE; Temp++) Buffer[Temp]=rand();
                printf("writing Blk %lu\r", Blk);
                Cmd.Data=Buffer;
                Cmd.Blk=Blk;
                Count=min(BUFF_SIZE >> 9, START_BLK + NUM_BLKS - Blk);
                Cmd.Count=Count << 9;
                Temp=ataCmd(&Cmd);
                if(Temp)
                {       printf("\n""ataCmd(write) returned %d\n", Temp);
                        break; }
                Blk += Count; }
        printf("\n");
        srand(2);
        Cmd.Cmd=DRV_CMD_RD;
/* read NUM_BLKS of data from beginning of drive, verify against same
pseudorandom sequence that was written */
        for(Blk=START_BLK; Blk < START_BLK + NUM_BLKS; )
        {       printf("reading Blk %lu\r", Blk);
                Cmd.Data=Buffer;
                Cmd.Blk=Blk;
                Count=min(BUFF_SIZE >> 9, START_BLK + NUM_BLKS - Blk);
                Cmd.Count=Count << 9;
                Temp=ataCmd(&Cmd);
                if(Temp)
                {       printf("\n""ataCmd(read) returned %d\n", Temp);
                        break; }
                for(Temp=0; Temp < min(BUFF_SIZE,
                        (START_BLK + NUM_BLKS - Blk) << 9); Temp++)
                {       Data=rand();
                        if(Buffer[Temp] != Data)
                        {       printf("\n""verify failed, Blk %lu, offset "
                                        "%u (wanted %u, got %u)\n", Blk,
                                        Temp,   Data, Buffer[Temp]);
                                break; }}
                Blk += Count; }
#endif
BAIL:   printf("\n");
        irqEnd();
        return 0;
}

#endif
#endif
