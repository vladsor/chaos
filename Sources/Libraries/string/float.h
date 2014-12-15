/**
 * @file                float.h
 * @brief               Functions for working with float.
 * @author              Vladimir Sorokin
 * @version             1.0
 * @date                2000-2003
 */

#ifndef __LIBRARY_STRING_FLOAT_H__
#define __LIBRARY_STRING_FLOAT_H__

enum float_special
{
    FLOAT_NORMAL,
    FLOAT_NAN,
    FLOAT_PLUS_INFINITE,
    FLOAT_MINUS_INFINITE,
};

/**
 * @brief               Check if float number is special.       
 * @param float_number  Floating point number
 * @return              type of float number
 */
extern unsigned int float_is_special (double float_number);

#endif /* __LIBRARY_STRING_FLOAT_H__ */
