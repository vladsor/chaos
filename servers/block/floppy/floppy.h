/*
GazOS Operating System
Copyright (C) 1999  Gareth Owen <gaz@athene.co.uk>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#ifndef FDC_H
#define FDC_H

typedef unsigned char BYTE;

/* datatypes */

/* drive geometry */
typedef struct {
   BYTE heads;
   BYTE tracks;
   BYTE spt;     /* sectors per track */
} drive_geometry_type;

/* drive geometries */
#define DG144_HEADS       2     /* heads per drive (1.44M) */
#define DG144_TRACKS     80     /* number of tracks (1.44M) */
#define DG144_SPT        18     /* sectors per track (1.44M) */
#define DG144_GAP3FMT  0x54     /* gap3 while formatting (1.44M) */
#define DG144_GAP3RW   0x1b     /* gap3 while reading/writing (1.44M) */

#define DG168_HEADS       2     /* heads per drive (1.68M) */
#define DG168_TRACKS     80     /* number of tracks (1.68M) */
#define DG168_SPT        21     /* sectors per track (1.68M) */
#define DG168_GAP3FMT  0x0c     /* gap3 while formatting (1.68M) */
#define DG168_GAP3RW   0x1c     /* gap3 while reading/writing (1.68M) */

/* IO ports */
#define FDC_DOR  (0x3f2)   /* Digital Output Register */
#define FDC_MSR  (0x3f4)   /* Main Status Register (input) */
#define FDC_DRS  (0x3f4)   /* Data Rate Select Register (output) */
#define FDC_DATA (0x3f5)   /* Data Register */
#define FDC_DIR  (0x3f7)   /* Digital Input Register (input) */
#define FDC_CCR  (0x3f7)   /* Configuration Control Register (output) */

/* command bytes (these are 765 commands + options such as MFM, etc) */
#define COMMAND_SPECIFY 	(0x03)  /* specify drive timings */
#define COMMAND_WRITE   	(0xc5)  /* write data (+ MT,MFM) */
#define COMMAND_READ    	(0xe6)  /* read data (+ MT,MFM,SK) */
#define COMMAND_RECALIBRATE	(0x07)  /* recalibrate */
#define COMMAND_SENSEI  	(0x08)  /* sense interrupt status */
#define COMMAND_FORMAT  	(0x4d)  /* format track (+ MFM) */
#define COMMAND_SEEK    	(0x0f)  /* seek track */
#define COMMAND_VERSION 	(0x10)  /* FDC version */

#define FLOPPY_DMA_CHANNEL	(0x02)

/* function prototypes */

bool init(void);
/*void deinit(void); */

void reset(void);

bool disk_change (void);
void motor_on(void);
void motor_off(void);
void recalibrate(void);
bool seek(int track);
bool log_disk(drive_geometry_type *g);
bool read_block(int block,BYTE *blockbuff,unsigned long nosectors);
bool write_block(int block,BYTE *blockbuff,unsigned long nosectors);
bool format_track(BYTE track,drive_geometry_type *g);

extern log_structure_type log_structure;

#endif /* FDC_H */
