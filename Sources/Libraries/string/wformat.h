/* $Id: functions.h,v 1.2 2001/02/10 21:23:13 jojo Exp $ */

/* Copyright 2000 chaos development. */
/**
 * @file                functions.h
 * @brief               Format string functions.
 * @author              Per Lundberg <plundis@chaosdev.org>,
 *                      Vladimir Sorokin
 * @version             1.0
 * @date                2001-2003
 */

#ifndef __LIBRARY_STRING_WFORMAT_H__
#define __LIBRARY_STRING_WFORMAT_H__

/**
 * @brief               Formatted print to string.
 * @param output        String for output
 * @param format_string Formating string
 * @param ...           Outputed parameters
 * @return
 */
extern return_t wstring_print (wchar_t *output, const wchar_t *format_string, 
    ...);

/**
 * @brief               Internal formatted print to string.
 * @param output        String for output
 * @param format_string
 * @param arguments
 * @return
 */
extern return_t wstring_print_va (wchar_t *output, const wchar_t *format_string, 
    va_list arguments);

/**
 * @brief               Scan string for getting parameters.
 * @param input         Scanned string
 * @param format_string
 * @param ...
 * @return
 */
extern int wstring_scan (wchar_t *input, wchar_t *format_string, ...);

/**
 * @brief               Internal scan string for getting parameters.
 * @param input         Scanned string
 * @param format_string
 * @param arguments
 * @return
 */
extern int wstring_scan_va (wchar_t *input, wchar_t *format_string, va_list arguments);

/**
 * @brief               Split one string in several.
 * @param string        
 * @param pointers
 * @return
 */
//extern unsigned int wstring_split (wchar_t *string, wchar_t **pointers);

#endif /* !__LIBRARY_STRING_FORMAT_H__ */
