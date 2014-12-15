/* $Id: controller.c,v 1.2 2001/02/10 21:25:00 jojo Exp $ */
/* Abstract: Common code for the keyboard server. */
/* Author: Per Lundberg <plundis@chaosdev.org> */

/* Copyright 2000 chaos development. */

#include <enviroment.h>

#include "Include/controller.h"
#include "Include/keyboard.h"
#include "Include/mouse.h"
#include "Include/interface.h"

#define DEBUG_MODULE_NAME L"Keyboard"
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#ifndef __STORM_KERNEL__
#   define DEBUG_SUPPLIER (keyboard_debug_supplier)
#endif

#include <debug/macros.h>

/* This reads the controller status port, and does the appropriate
   action. */

uint8_t handle_event (void)
{
    uint8_t status = controller_read_status ();
    unsigned int work;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%S: %s ()\n",
        DEBUG_MODULE_NAME, __FUNCTION__);
  
    for (work = 0; (work < 10000) && 
        ((status & CONTROLLER_STATUS_OUTPUT_BUFFER_FULL) != 0); work++) 
    {
        uint8_t scancode;
    
        scancode = controller_read_input ();
 
#if FALSE
        /* Ignore error bytes. */

        if ((status & (CONTROLLER_STATUS_GENERAL_TIMEOUT | 
            CONTROLLER_STATUS_PARITY_ERROR)) == 0)
#endif
        {
            if ((status & CONTROLLER_STATUS_MOUSE_OUTPUT_BUFFER_FULL) != 0)
            {
                mouse_handle_event (scancode);
            }
            else
            {
                keyboard_handle_event (scancode);
            }
        }
    
        status = controller_read_status ();
    }

    if (work == 10000)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR, "Keyboard controller jammed.");
    }

//    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "End handling event. Status=%i\n", 
//      status);
  
    return status;
}

/* Wait for keyboard controller input buffer to drain.
 
   Quote from PS/2 System Reference Manual:
   
     "Address hex 0060 and address hex 0064 should be written only
     when the input-buffer-full bit and output-buffer-full bit in the
     Controller Status register are set 0."  */

void controller_wait (void)
{
    unsigned long timeout;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%S: %s ()\n",
        DEBUG_MODULE_NAME, __FUNCTION__);
  
    for (timeout = 0; timeout < CONTROLLER_TIMEOUT; timeout++)
    {
        /* handle_event () will handle any incoming events while we wait
           -- keypresses or mouse movement. */
    
        unsigned char status = handle_event ();
                
        if ((status & CONTROLLER_STATUS_INPUT_BUFFER_FULL) == 0)
        {
            return;
        }
    
        /* Sleep for one millisecond. */

//        timer_sleep_milli (1);
        cpu_sleep_milli (CPU_CURRENT, 1);
    }
  
    DEBUG_PRINT (DEBUG_LEVEL_ERROR, "Keyboard timed out[1]");
}

/* Wait for input from the keyboard controller. */

int controller_wait_for_input (void)
{
    int timeout;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%S: %s ()\n",
        DEBUG_MODULE_NAME, __FUNCTION__);

    for (timeout = 0; timeout < KEYBOARD_INIT_TIMEOUT; timeout++)
    {
        int return_value = controller_read_data ();

        if (return_value >= 0)
        {
            return return_value;
        }

//        timer_sleep_milli (1);
        cpu_sleep_milli (CPU_CURRENT, 1);
    }

    DEBUG_PRINT (DEBUG_LEVEL_ERROR, "Time out.\n");
  
    return -1;
}

/* Write a command word to the keyboard controller. */

void controller_write_command_word (uint8_t data)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%S: %s ()\n",
        DEBUG_MODULE_NAME, __FUNCTION__);

    controller_wait ();
    controller_write_command (data);
}

/* Write an output word to the keyboard controller. */

void controller_write_output_word (uint8_t data)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%S: %s ()\n",
        DEBUG_MODULE_NAME, __FUNCTION__);

    controller_wait ();
    controller_write_output (data);
}

/* Empty the keyboard input buffer. */

void keyboard_clear_input (void)
{
    int max_read;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%S: %s ()\n",
        DEBUG_MODULE_NAME, __FUNCTION__);

    for (max_read = 0; max_read < 100; max_read++)
    {
        if (controller_read_data () == KEYBOARD_NO_DATA)
        {
            break;
        }
    }
}

/* Read data from the keyboard controller. */

int controller_read_data (void)
{
    int return_value = KEYBOARD_NO_DATA;
    uint8_t status;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%S: %s ()\n",
        DEBUG_MODULE_NAME, __FUNCTION__);

    status = controller_read_status ();
    
    if ((status & CONTROLLER_STATUS_OUTPUT_BUFFER_FULL) == 
        CONTROLLER_STATUS_OUTPUT_BUFFER_FULL)
    {
        uint8_t data = controller_read_input ();

        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Input: %X.\n", data);
    
        return_value = data;
	
        if ((status & (CONTROLLER_STATUS_GENERAL_TIMEOUT | 
            CONTROLLER_STATUS_PARITY_ERROR)) != 0)
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "Bad data.\n");
            
            return_value = KEYBOARD_BAD_DATA;
        }
    }
  
    return return_value;
}

