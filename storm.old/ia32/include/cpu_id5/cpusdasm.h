/*
*******************************************************************************
 * Source File		: cpusdasm.h
 * Archive File	: /General Utilities/CPU Speed Check/cpusdasm.h  $
 *	$Date				: 10/08/98
 *	Description		: This header files contains all the proto types and defines
 *						  for cpusdasm.c file
 *
 * Original engineer:     AFan  $
 *
 *
 * Copyright 1998 ADVANCED MICRO DEVICES, INC. All Rights Reserved.
 *	This software is unpublished and contains the trade secrets and
 * confidential proprietary information of AMD. Unless otherwise provided
 *	in the software Agreement associated herewith, it is licensed in
 *	confidence "AS IS" and is not to be reproduced in whole or part by
 *	any means except for backup. Use, duplication, or disclosure by
 *	the Government is subject to the restrictions in paragraph (b) (3) (B)
 *	of the Rights in Technical Data and Computer Software clause in
 *	DFAR 52.277-7013 (a) (Oct 1988).
 *	Software owned by Advanced Micro Devices, Inc., #1 AMD Place,
 *	Sunnyvale, CA 94088
*******************************************************************************
*/

#define htuA                    0x68747541            // hex value for htuA
#define itne                    0x69746e65            // hex value for itne
#define DMAc                    0x444d4163            // hex value for DMAc

#define family_offset           8                               // the bits of family number in EAX register
#define model_offset            4            // the bits of model number in EAX register

#define REF_TICK                100                     // # of timer interrupts
#define TICK_SEC                1098510               // Tick value for 1 sec
#define TIMER_TICK_LOW          0x46C                 // BIOS date are 40:6ch
#define TIMER_TICK_HIGH         0x46E                 // BIOS date are 40:6eh


void check_cache(void);
void restore_cache(void);
//unsigned long check_timer_procedure(void);
//unsigned long read_cpu_state(void);
//void test_id(unsigned long *family, unsigned long *model_no, unsigned long *stepping);
//void test_writability(unsigned long *ID_x, unsigned long *ID_y);