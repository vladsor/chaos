/* Abstract: String conversions functions. */
/* Author: Vladimir Sorokin */

/* Copyright 2000 chaos development. */

#include <enviroment.h>
#include "string.h"

return_t wstring_to_int32 (wchar_t *string, int32_t *number,
    unsigned int base, unsigned int *count)
{
    unsigned int value;
    bool overflow = FALSE;
    bool sign = FALSE;
    int32_t result = 0, oldresult;
    wchar_t *string_base = string;

    if (string == NULL || number == NULL)
    {
        return STRING_RETURN_INVALID_ARGUMENT;
    }
    
    /* Evaluate sign */
    if (*string == L'-')
    {
        sign = TRUE;
        string++;
    }
    else if (*string == L'+')
    {
        string++;
    }
  
    /* Skip trailing zeros */
    while (*string == L'0')
    {
        string++;
    }
  
    /* Convert number */
    while (char_is_number (*string, base))
    {
        value = char_to_int (*string++);
    
        if (value > base)
        {
            return STRING_RETURN_INVALID_ARGUMENT;
        }
    
        oldresult = result;
        result *= base;
        result += value;
    
        /* Detect overflow */
        if (oldresult > result)
        {
            overflow = TRUE;
        }
    }

    if (count != NULL)
    {
        *count = string - string_base;
    }
  
    if (overflow)
    {
        result = INT32_MAX;
    }

    if (sign)
    {  
        result *= -1;
    }
  
    *number = result;
  
    return STRING_RETURN_SUCCESS;
}

return_t wstring_to_uint32 (wchar_t *string, uint32_t *number,
  unsigned int base, unsigned int *count)
{
    unsigned int value;
    bool overflow = FALSE;
    uint32_t result = 0, oldresult;
    wchar_t *string_base = string;

    if (string == NULL || number == NULL)
    {
        return STRING_RETURN_INVALID_ARGUMENT;
    }
    
    /* Skip trailing zeros */
    while (*string == L'0')
    {
        string++;
    }
    
    if (*string == L'x' && base == 16)
    {
        string++;
        while (*string == '0')
        {
            string++;
        }
    }
  
    /* Convert number */
    while (char_is_number (*string, base))
    {
        value = char_to_int (*string++);
        
        if (value > base)
        {
            return STRING_RETURN_INVALID_ARGUMENT;
        }
    
        oldresult = result;
        result *= base;
        result += value;

        /* Detect overflow */
        if (oldresult > result) 
        {
            overflow = TRUE;
        }
    }
  
    if (count != NULL)
    {
        (*count) = string - string_base;
    }
  
    if (overflow)
    {
        result = UINT32_MAX;
    }

    (*number) = result;

    return STRING_RETURN_SUCCESS;
}

return_t wstring_to_double (wchar_t *string, double *number, unsigned int *count)
{
    int sign, i;
    double result = 0;
    double value;
    double mantissa = 0, divisor = 1;
    unsigned short power = 0;
    wchar_t *string_base = string;

    if (string == NULL || number == NULL)
    {
        return STRING_RETURN_INVALID_ARGUMENT;
    }

    /* Evaluate sign */
    if (*string == L'-')
    {
        sign = -1;
        string++;
    }
    else
    {
        sign = 1;
    }
  
    /* Skip trailing zeros */
    while (*string == L'0')
    {
        string++;
    }

    /* Convert integer part */
    while (*string <= L'9' && *string >= L'0')
    {
        value = *string++ - L'0';
        result *= 10.0;
        result += value;
    }
  
    /* Detect floating point & mantissa */
    if (*string == L'.')
    {
        string++;
        while (*string <= L'9' && *string >= L'0')
        {
            value = *string++ - '0';
            mantissa *= 10.0;
            mantissa += value;
            divisor *= 10.0;
        }
    }
    
    mantissa /= divisor;

    /* Adjust result */
    result += mantissa;
  
    /* Adjust sign */
    result *= sign;
  
    /* Detect exponent */
    if (*string == L'e' || *string == L'E')
    {
        string++;
        if (*string == L'-')
        {
            sign = -1;
            string++;
        } 
        else if (*string == L'+') 
        {
            sign = 1;
            string++;
        }
        else
        {
            sign = 1;
        }
    
        while (*string <= L'9' && *string >= L'0')
        {
            value = *string++ - L'0';
            power *= 10.0;
            power += value;
        }
    }
  
    /* Adjust result on exponent sign */
    if (sign > 0) 
    {
        for (i = 0; i < power; i++)
        {
            result *= 10.0;
        }
    }
    else
    {
        for (i = 0; i < power; i++)
        {
            result /= 10.0;
        }
    }
    
    if (count != NULL)
    {
        *count = string - string_base;
    }

    *number = result;

    return STRING_RETURN_SUCCESS;
}

/* Converts a string to a number. */

return_t wstring_to_int32_with_base_autodetect (const wchar_t *string, 
    int32_t *number, int *characters)
{
    unsigned int index = 0;
    unsigned int base = 10;
    bool negative = FALSE;

    /* Make sure we are not null. */

    if (string == NULL)
    {
        return STRING_RETURN_INVALID_ARGUMENT;
    }

    /* Is this a negative number? */

    if (string[index] == L'-')
    {
        negative = TRUE;
        index++;
    }

    /* Check which base this is. Hexadecimal, perhaps? */

    switch (string[index])
    {
        case L'0':
        {
            index++;

            switch (string[index])
            {
                /* Hexadecimal. */

                case L'X':
                case L'x':
                {
                    base = 16;
                    index++;
                    break;
                }

                case L'b':
                {
                    base = 2;
                    index++;
                    break;
                }
            }
            break;
        }
    }

    /* Null the number. */

    *number = 0;

    switch (base)
    {
        /* Binary. */

        case 2:
        {
            while ((string[index] == L'0' ||
                    string[index] == L'1') &&
                   string[index] != L'\0')
            {
                *number *= 2;
                *number += string[index] - '0';
                index++;
            }
            break;
        }
    
        /* Decimal. */

        case 10:
        {
            while (string[index] >= L'0' &&
                   string[index] <= L'9' &&
                   string[index] != L'\0')
            {
                *number *= 10;
                if (L'0' <= string[index] && string[index] <= L'9')
                {
                    *number += string[index] - L'0';
                }
                else
                {
                    return STRING_RETURN_INVALID_ARGUMENT;
                }
                index++;
            }
            break;
        }

        /* Hexadecimal. */

        case 16:
        {
            while (((string[index] >= L'0' &&
                     string[index] <= L'9') ||
                    (string[index] >= L'a' &&
                     string[index] <= L'f') ||
                    (string[index] >= L'A' &&
                     string[index] <= L'F')) &&
                   string[index] != L'\0')
            {
                *number *= 16;

                if (L'0' <= string[index] && string[index] <= L'9')
                {
                    *number += string[index] - L'0';
                }
                else if (string[index] >= L'a' && string[index] <= L'f')
                {
                    *number += string[index] - L'a' + 10;
                }
                else if (string[index] >= L'A' && string[index] <= L'F')
                {
                    *number += string[index] - L'A' + 10;
                }
                else
                {
                    return STRING_RETURN_INVALID_ARGUMENT;
                }
                index++;
            }

            break;
        }
    }   
    
    if (negative)
    {
        *number = 0 - *number;
    }

    /* If we're not interested in the number of characters slurped by
       this function, we might have set characters to NULL. */

    if (characters != NULL)
    {
        *characters = index;
    }

    return STRING_RETURN_SUCCESS;
}

/* Converts a number to a string. */

wchar_t * uint32_to_wstring (wchar_t *string, uint32_t number, int base,
    int size, int precision, int flags)
{
    wchar_t pad_character, sign = 0, tmp_string[66];
    const wchar_t *digits = L"0123456789abcdefghijklmnopqrstuvwxyz";
    int tmp_index = 0;
    int real_index = 0;

    /* Sometimes we prefer to print things with large hexadecimals. */

    if ((flags & STRING_LARGE) != 0)
    {
        digits = L"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    }

    /* Pad to left? */

    if ((flags & STRING_LEFT) != 0)
    {
        flags &= ~STRING_ZERO_PAD;
    }

    /* We only support base 2 to 36. */
    
    if (base < 2 || base > 36)
    {
        return 0;
    }

    pad_character = ((flags & STRING_ZERO_PAD) != 0) ? L'0' : L' ';

    /* Do we have a sign character? If so, add it. */

    if ((flags & STRING_SIGN) != 0) 
    {
        if ((long) number < 0) 
        {
            sign = L'-';
            number = -((long) number);
            size--;
        }
        else if ((flags & STRING_PLUS) != 0) 
        {
            sign = L'+';
            size--;
        }
        else if ((flags & STRING_SPACE) != 0) 
        {
            sign = L' ';
            size--;
        }
    }

    if ((flags & STRING_SPECIAL) != 0) 
    {
        if (base == 16)
        {
            size -= 2;
        }
        else if (base == 8)
        {
            size--;
        }
    }

    if (number == 0)
    {
        tmp_string[tmp_index] = L'0';
        tmp_index++;
    }
    else 
    {
        while (number != 0)
        {
            tmp_string[tmp_index] = digits[number % base];
            number /= base;
            tmp_index++;
        }
    }

    /* Okay, we have the string, but in reversed order. Lets do some
       more magic before we reverse it. */

    if (tmp_index > precision)
    {
        precision = tmp_index;
    }

    size -= precision;

    if (!((flags & (STRING_ZERO_PAD + STRING_LEFT)) != 0))
    {
        while (size > 0)
        {
            string[real_index] = L' ';
            real_index++;
            size--;
        }
    }

    /* If we have a sign character, prepend it. */

    if (sign != 0)
    {
        string[real_index] = sign;
        real_index++;
    }

    /* Do we want 0x or 0 before the number? */

    if ((flags & STRING_SPECIAL) != 0)
    {
        if (base == 8)
        {
            string[real_index] = L'0';
            real_index++;
        }
        else if (base == 16) 
        {
            string[real_index] = L'0';
            string[real_index + 1] = digits[33];
            real_index += 2;
        }
    }
  
    /* We might want to pad characters a little. */

    if (!((flags & STRING_LEFT) != 0))
    {
        while (size > 0)
        {
            string[real_index] = pad_character;
            real_index++;
            size--;
        }
    }

    while (tmp_index < precision)
    {
        string[real_index] = L'0';
        real_index++;
        precision--;
    }

    /* Copy the string. */

    while (tmp_index > 0)
    {
        tmp_index--;
        string[real_index] = tmp_string[tmp_index];
        real_index++;
    }

    while (size > 0)
    {
        string[real_index] = L' ';
        real_index++;
        size--;
    }

    string[real_index] = L'\0';

    return string;
}

