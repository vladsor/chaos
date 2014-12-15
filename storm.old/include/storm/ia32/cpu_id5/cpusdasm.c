/*
*******************************************************************************
 * Source File		: cpuspasm.c
 * Archive File	: /General Utilities/CPU Speed Check/cpuspeed.c  $
 *	$Date				: 10/08/98
 *	Description		: This program conatins all the inline Assembly code for
 *						  cpuspeed.c file and will determine the speed and model
 *						  number of the CPU. It uses the timer tick
 *						  (18.2064796812/sec) and TSC to determine the speed
 *						  which the processor is running.
 *
 * Original engineer:     AFan  $
 *
 * $Header:     	/General Utilities/CPU Speed Check/cpuspeed.h
 *
 * $History: cpuspd3.asm
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

#include <string.h>
#include <ctype.h>
#include <dos.h>
#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "cpusdasm.h"


/*******************************************************************************
*	Name;				read_cpu_state()
*	Description:  	This function will find out the state for AMD K6 model 9
*						and model 8 (Chomper XT (CXT)).
*	Parameters:		None
*	returns:       state
******************************************************************************/
#pragma inline
unsigned long read_cpu_state()
{
		unsigned long state=0;

		asm{   .586P
					pusha
					mov ecx, 0C0000087h        // processor state observability
					rdmsr                      // read constant of PSOR MSR
					mov state, eax             // save constant of PSOR MSR in bus_state variable
					popa
		} // end of asm

		return state;
}



/******************************************************************************
*	Name:				test_writablity()
*	Description:	This function will test the writablity of the ID bit in the
*     				EFLAGS register
*	Parameters:		unsigned long *ID_x
*						unsigned long *ID_y
*	Returns:			None
******************************************************************************/
void test_writability(unsigned long *ID_x, unsigned long *ID_y)
{
		_asm {
			.586P

		 // test the writablity of the ID bit in the EFLAGS register

		pushfd                          // push eflags dword into stack
		pop     eax                     // load eflags dword into eax
		mov     ebx, eax                // save for later use
		xor     eax, 00200000h          // toggle bit 21
		push    eax                     // push the result into stack
		popfd                           // update eflags from stack

		pushfd                          // push eflags dword into stack
		pop     eax                     // load eflags dword into eax
		mov     si, ID_x
		mov     [si], eax                    // load the contents of eax to x
		mov     si, ID_y
		mov     [si], ebx                    // load the contents of ebx to y
	}  // end asm
}



/******************************************************************************
* 	Name:				test_id()
*	Description:	This function will test the CPU id for entire CPU, the
*               	result may be either AMD or Non-AMD CPU
*	Parameters:		unsigned long *family
*						unsigned long *model_no
*						unsigned long *stepping
*	Returns:       None
******************************************************************************/
void test_id(unsigned long *family, unsigned long *model_no, unsigned long *stepping)
{
	unsigned long mode1=0, mode2=0, mode3=0;
	unsigned long save_value;

	_asm{
			// cpu_oK - run CPUID instruction to get cpu vendor
			mov     eax, 0                          // function 0
			db      0fh, 0a2h                       // CPUID opcode
			mov     mode1, ebx              	// load to string variable
			mov     mode2, edx                      // load to string variable
			mov     mode3, ecx                      // load to string variable
		}

		if ((mode1 == htuA) && (mode2 == itne) && (mode3 == DMAc))    // AMD CPU
		{
			_asm {
					mov    eax, 1                          // function 1
					db     0fh, 0a2h                       // CPUID opcode
					mov    save_value, eax                 // reload the whole cpu family
			}

			*family = (save_value >> family_offset) & 0x0F;          // find out the familu number (8 - 11 bits in EAX register)

			*model_no = (save_value >> model_offset) & 0x0F;        // find out the model number  (4 - 7 bits in EAX register)

			*stepping = save_value & 0x0F;								  // find out the stepping number (0 - 3 bits in EAX register)
      	
		}
}



/*****************************************************************************
*	Name:				check_timer_procedure()
*	Description:	This function will use Assembly code to do the check timer,
* 					   wait for next tick, wait for ref tick, and to find out the
*     				right number for calculating the raw cpu speed
*	Parameters:		None
*	Returns;       timer_speed
*****************************************************************************/
unsigned long check_timer_procedure()
{
		unsigned long timer_speed = 0;
		_asm {

					pusha

			check_timer0:
					pushfd                           // save current interrupt flag

					sti                             // enable interrupts

					mov     ax, 0                   // to access BIOS data area
					mov     fs, ax                  // through segment 0
					mov     bx, TIMER_TICK_LOW      // and offset
					xor     ecx, ecx                // to initialize timer_tick_low & high
					mov     eax, fs:[bx]            // load current timer count dword

        }
		  wait_for_next_tick:
        _asm {
					jmp     $+2
					jmp     $+2
					cmp     eax, fs:[bx]            // check if timer intr. occurred
					jz      wait_for_next_tick      // not yet
        }
	_asm {
					//--- One timer period just passed. Start speed detection.
					//--- Initialize time stamp counter register to prevent overflow.
					push    ecx
					mov     ecx, 10h                // time stamp counter access via MSR
					mov     eax, 0                  // initialize the eax part of the counter
					mov     edx, 0                  // initialize the edx part of the counter
		 			wrmsr
					pop     ecx
					xchg    ecx, fs:[bx]            // save current timer_tick_low/high and
														  // initialize it with 0

        }
	wait_for_ref_tick:
        _asm {
					cmp     dword ptr fs:[bx], REF_TICK     // repeat until the number of timer
					jne     wait_for_ref_tick               // ticks are equal to TIMER_CNT
         }
	 _asm {
					db      0Fh, 031h                       // rdtsc: read time stamp counter again

					//--- Update BIOS data variable.

					add     ecx, REF_TICK           // update timer_tick_low/high with the
					mov     fs:[bx], ecx            // ticks occurred during this test

					pop     ecx
					mov     timer_speed, eax           // load the content of eax to number variable
					popa
			}
			return (timer_speed);
}




/*****************************************************************************
*	Name:				restore_cache()
*	Description:	This function will restore previous interrupt flags
*     				and L1 cache state
*	Parameter:		None
*	Returen:			None
*****************************************************************************/
void restore_cache()
{
		//--- Restore previous interrupt flag and L1 cache state.

		_asm {
			restore_cache:
			popf                            // restore interrupt flag state
			pop     eax                     // load previous l1 cache state
			test    eax, 060000000h         // cache was on?
			jz      exit                    // yes,

			wbinvd                          // flush l1 cache before disable it
			mov     cr0, eax                // disable l1 cache
			wbinvd
		}
		exit:
		_asm {
			mov     ah, 4ch                 // terminate the program
			int     21h
		}

} // end restore_cache()



/***************************************************************************
*	Name:				check_cache()
*	Description:	This function will save old L1 cache state and enable
*						L1 cache
*	Parameter:		None
*	Returns:			None
***************************************************************************/
void check_cache()
{
		unsigned long X;

		//--- Save old L1 cache state and enable L1 cache
		_asm {

				mov     eax, cr0                // load current l1 cache state
				push    eax
				mov     X, eax                  // load eax to X
		}

		if (!(X & 0x60000000) )
		{
			_asm {
				and     eax, 9fffffffh          // enable L1 cache
				mov     cr0, eax                // update cr0
			}   // end of asm
		}
}
