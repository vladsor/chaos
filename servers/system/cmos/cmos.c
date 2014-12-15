/* $Id: serial.c,v 2.7 2000/07/01 18:26:37 plundis Exp $ */
/* Abstract: RTC server for chaos. */
/* Authors: Vladimir Sorokin */

/* Copyright 1999-2000 chaos development */

/* This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
   USA. */

#include <ipc/ipc.h>
#include <log/log.h>
#include <memory/memory.h>
#include <string/string.h>
#include <system/system.h>

#include "config.h"
#include "mc146818.h"

static log_structure_type log_structure;

tag_type empty_tag =
{
  0, 0, ""
};

static rtc_time_type start_time;

/* FIXME: Real mutexing. */

//static volatile bool lock = FALSE;

static void handle_connection (mailbox_id_type reply_mailbox_id);
static bool init (void);

static void rtc_read(rtc_time_type *rtc_time)
{
  rtc_time->seconds      = convert_bcd_to_bin( cmos_read(RTC_SECONDS) );
  rtc_time->minutes      = convert_bcd_to_bin( cmos_read(RTC_MINUTES) );
  rtc_time->hours        = convert_bcd_to_bin( cmos_read(RTC_HOURS) );
  rtc_time->day_of_week  = convert_bcd_to_bin( cmos_read(RTC_DAY_OF_WEEK) );
  rtc_time->day_of_month = convert_bcd_to_bin( cmos_read(RTC_DAY_OF_MONTH) );
  rtc_time->month        = convert_bcd_to_bin( cmos_read(RTC_MONTH) );
  rtc_time->year         = convert_bcd_to_bin( cmos_read(RTC_YEAR) );

}

static void rtc_write(rtc_time_type *rtc_time)
{
  cmos_write( RTC_SECONDS,      BIN_TO_BCD(rtc_time->seconds) );
  cmos_write( RTC_MINUTES,      BIN_TO_BCD(rtc_time->minutes) );
  cmos_write( RTC_HOURS,        BIN_TO_BCD(rtc_time->hours) );
  cmos_write( RTC_DAY_OF_WEEK,  BIN_TO_BCD(rtc_time->day_of_week) );
  cmos_write( RTC_DAY_OF_MONTH, BIN_TO_BCD(rtc_time->day_of_month) );
  cmos_write( RTC_MONTH,        BIN_TO_BCD(rtc_time->month) );
  cmos_write( RTC_YEAR,         BIN_TO_BCD(rtc_time->year) );
}


/* Init server. */

static bool init (void)
{
  return_type return_value;

  /* Register ports. */
  if ((return_value = system_call_port_range_register (0x70, 2, "CMOS Controller")) 
    != STORM_RETURN_SUCCESS)
  {
    log_print_formatted (&log_structure, LOG_URGENCY_EMERGENCY,
                           "Could not allocate port range %x-%x.(%u)",
                           0x70, 0x71, return_value);
    return FALSE;
  }

  rtc_read(&start_time);

  log_print_formatted (&log_structure, LOG_URGENCY_EMERGENCY,
    "Date %02u.%02u.%02u",start_time.day_of_month,start_time.month,start_time.year);

  log_print_formatted (&log_structure, LOG_URGENCY_EMERGENCY,
    "Time %02u:%02u:%02u",start_time.hours,start_time.minutes,start_time.seconds);
  
  return TRUE;
}

/* Handle a connection request. */

static void handle_connection (mailbox_id_type reply_mailbox_id)
{
  bool done = FALSE;
  message_parameter_type message_parameter;
  ipc_structure_type ipc_structure;
  rtc_time_type data;

  /* Accept the connection. */ 

  ipc_structure.output_mailbox_id = reply_mailbox_id;
  ipc_connection_establish (&ipc_structure);

  log_print (&log_structure, LOG_URGENCY_DEBUG,
             "RTC established connection.");

  /* Main loop. The connection is up, so we just handle the packets we
     get in the way we should. */

  while (!done)
  {
    message_parameter.protocol = IPC_PROTOCOL_RTC;
    message_parameter.message_class = IPC_CLASS_NONE;
    message_parameter.length = sizeof (rtc_time_type);
    message_parameter.data = (void *) &data;
    message_parameter.block = TRUE;

    if (system_call_mailbox_receive
        (ipc_structure.input_mailbox_id, &message_parameter) !=
        STORM_RETURN_SUCCESS)
    {
      log_print (&log_structure, LOG_URGENCY_ERROR,
                 "RTC mailbox_receive failed.");
      continue;
    }
    switch (message_parameter.message_class)
    {
      case IPC_RTC_READ:
      {
        rtc_read(&data);      
	  
	system_call_mailbox_send(reply_mailbox_id, &message_parameter);

        break;
      } 
      case IPC_RTC_WRITE:
      {

        rtc_write(&data);

        break;
      }
      default:
      {
      }
    }

  }
}


/* Server entry point. */

int main (void)
{
  ipc_structure_type ipc_structure;

  
  /* FIXME command-line options. */
  system_call_process_name_set("rtc");
  system_call_thread_name_set("initialising");

  log_init (&log_structure, PACKAGE_NAME, &empty_tag);
  
  if (init () == FALSE)
  {
    log_print (&log_structure, LOG_URGENCY_EMERGENCY,
               "Failed initialisation.");
    return -1;
  }
  
  /* Create service. */

  if (ipc_service_create ("ipc", &ipc_structure, &empty_tag) 
    != IPC_RETURN_SUCCESS)
  {
    log_print (&log_structure, LOG_URGENCY_EMERGENCY, "Couldn't create service.");
    return -1;
  }
  
  /* Main loop.	*/

  system_call_thread_name_set ("Service handler");

  /* Unblock any servers that may be waiting after us. */

  system_call_process_parent_unblock ();
  
  while (TRUE)
  {
    mailbox_id_type reply_mailbox_id;
    
    ipc_service_connection_wait (&ipc_structure);
    reply_mailbox_id = ipc_structure.output_mailbox_id;

    
    if (system_call_thread_create () == STORM_RETURN_THREAD_NEW)
    {
      system_call_thread_name_set ("Handling connection");

      handle_connection (reply_mailbox_id);
    }
  }
}
