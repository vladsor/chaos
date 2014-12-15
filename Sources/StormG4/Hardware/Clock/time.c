/* $Id: time.c,v 1.1.1.1 2000/09/26 19:08:16 plundis Exp $ */
/* Abstract: Architecture dependent time management. */
/* Author: Per Lundberg <plundis@chaosdev.org> */

/* Copyright 2000 chaos development. */

#include <enviroment.h>

#include "Include/mc146818.h"
#include "Include/time.h"

#define DEBUG_MODULE_NAME "Clock"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#include <debug/macros.h>

#define CMOS_BASE       0x70

static void rtc_read (rtc_time_t *rtc_time)
{
    rtc_time->seconds      = convert_bcd_to_bin (cmos_read (RTC_SECONDS));
    rtc_time->minutes      = convert_bcd_to_bin (cmos_read (RTC_MINUTES));
    rtc_time->hours        = convert_bcd_to_bin (cmos_read (RTC_HOURS));
    rtc_time->day_of_week  = convert_bcd_to_bin (cmos_read (RTC_DAY_OF_WEEK));
    rtc_time->day_of_month = convert_bcd_to_bin (cmos_read (RTC_DAY_OF_MONTH));
    rtc_time->month        = convert_bcd_to_bin (cmos_read (RTC_MONTH));
    rtc_time->year         = convert_bcd_to_bin (cmos_read (RTC_YEAR));
}
/*
static void rtc_write (rtc_time_t *rtc_time)
{
    cmos_write (RTC_SECONDS,      BIN_TO_BCD (rtc_time->seconds));
    cmos_write (RTC_MINUTES,      BIN_TO_BCD (rtc_time->minutes));
    cmos_write (RTC_HOURS,        BIN_TO_BCD (rtc_time->hours));
    cmos_write (RTC_DAY_OF_WEEK,  BIN_TO_BCD (rtc_time->day_of_week));
    cmos_write (RTC_DAY_OF_MONTH, BIN_TO_BCD (rtc_time->day_of_month));
    cmos_write (RTC_MONTH,        BIN_TO_BCD (rtc_time->month));
    cmos_write (RTC_YEAR,         BIN_TO_BCD (rtc_time->year));
}
*/
typedef uint64_t time_t;
static time_t system_time;

/* Convert a date/time in Gregorian time to the standard chaos
   format. */

static time_t gregorian_to_chaos (unsigned int year, unsigned int month, 
    unsigned int day, unsigned int hours, unsigned int minutes, 
    unsigned int seconds)
{
  unsigned int leap_years = (year / 4) - (year / 100) + (year / 400);
  unsigned int month_start[] =
  {
    /* January. */   0,
    /* February. */  31,  
    /* March. */     31 + 28,
    /* April. */     31 + 28 + 31,
    /* May. */       31 + 28 + 31 + 30,
    /* June. */      31 + 28 + 31 + 30 + 31,
    /* July. */      31 + 28 + 31 + 30 + 31 + 31,
    /* August. */    31 + 28 + 31 + 30 + 31 + 31 + 30,
    /* September. */ 31 + 28 + 31 + 30 + 31 + 31 + 30 + 31,
    /* October. */   31 + 28 + 31 + 30 + 31 + 31 + 30 + 31 + 30,
    /* November. */  31 + 28 + 31 + 30 + 31 + 31 + 30 + 31 + 30 + 31,
    /* December. */  31 + 28 + 31 + 30 + 31 + 31 + 30 + 31 + 30 + 31 + 30
  };
  time_t work;

  work = leap_years * 366 + (year - leap_years) * 365;
  work += month_start[month] + day;
  if ((year % 400 == 0 ||
      (year % 100 != 0 && year % 4 == 0)) && month >= 2)
  {
    work++;
  }

  work = ((work * 24 + hours) * 60 + minutes) * 60 + seconds;

  return work;
}

/* Initialise the time (by reading from the CMOS). */

return_t clock_init (int argc UNUSED, char *argv[] UNUSED, char **envp UNUSED)
{
    rtc_time_t rtc_time;
    
    rtc_read (&rtc_time);
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %2.2u/%2.2u/%2.2u %2.2u:%2.2u:%2.2u\n",
        DEBUG_MODULE_NAME, 
        rtc_time.day_of_month, rtc_time.month, rtc_time.year, rtc_time.hours, 
        rtc_time.minutes, rtc_time.seconds);
    
    /* Convert this time to the chaos format. */

    system_time = gregorian_to_chaos (rtc_time.year, rtc_time.month,
        rtc_time.day_of_month, rtc_time.hours, rtc_time.minutes, 
        rtc_time.seconds);

    return 0;
}
