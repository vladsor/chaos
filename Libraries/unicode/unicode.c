/* $chaos: unicode.c,v 1.2 2002/10/04 19:00:57 per Exp $ */
/* Abstract: Unicode library. */
/* Authors: Anders Ohrt <doa@chaosdev.org>
            Per Lundberg <per@chaosdev.org> */

/* Copyright 2000-2002 chaos development */
/* Use freely under the terms listed in the file LICENSE. */

/* See the specification (RFC 2279) for more information about
   UTF-8. If you are looking for general Unicode information, try out
   http://www.unicode.org/ */

#include "unicode.h"

#define B00000000 0x00
#define B10000000 0x80
#define B11000000 0xC0
#define B11100000 0xE0
#define B11110000 0xF0
#define B11111000 0xF8
#define B11111100 0xFC
#define B11111110 0xFE

#define B00111111 0x3F
#define B00011111 0x1F
#define B00001111 0x0F
#define B00000111 0x07
#define B00000011 0x03
#define B00000001 0x01

/* Convert a UCS-2 character to UTF-8. */
return_t unicode_ucs2_to_utf8 (uint8_t *utf8_char, ucs2_t ucs2_char, unsigned int *bytes)
{
    int utf8_bytes;

    if (ucs2_char <= 0x0000007F)
    {
        /* 0xxxxxxx */
        utf8_bytes = 1;
        utf8_char[0] = (uint8_t) ucs2_char;
    }
    else if (ucs2_char <= 0x000007FF)
    {
        /* 110xxxxx 10xxxxxx */
        utf8_bytes = 2;
        utf8_char[0] = (uint8_t) ((ucs2_char >> 6) | B11000000);
        utf8_char[1] = (uint8_t) ((ucs2_char & B00111111) | B10000000);
    }
    else if (ucs2_char <= 0x0000FFFF)
    {
        /* 1110xxxx 10xxxxxx 10xxxxxx */
        utf8_bytes = 3;
        utf8_char[0] = (uint8_t) ((ucs2_char >> 12) | B11100000);
        utf8_char[1] = (uint8_t) (((ucs2_char >> 6) & B00111111) | B10000000);
        utf8_char[2] = (uint8_t) ((ucs2_char & B00111111) | B10000000);
    }
    else
    {
        return UNICODE_RETURN_UCS2_INVALID;
    }

    utf8_char[utf8_bytes] = '\0';
    
    if (bytes != NULL)
    {
	(*bytes) = utf8_bytes;
    }

    return UNICODE_RETURN_SUCCESS;
}

/* Convert a UCS-4 character to UTF-8. */
return_t unicode_ucs4_to_utf8 (uint8_t *utf8_char, ucs4_t ucs4_char)
{
    int utf8_bytes;

    if (ucs4_char <= 0x0000007F)
    {
        /* 0xxxxxxx */
        utf8_bytes = 1;
        utf8_char[0] = (uint8_t) ucs4_char;
    }
    else if (ucs4_char <= 0x000007FF)
    {
        /* 110xxxxx 10xxxxxx */
        utf8_bytes = 2;
        utf8_char[0] = (uint8_t) ((ucs4_char >> 6) | B11000000);
        utf8_char[1] = (uint8_t) ((ucs4_char & B00111111) | B10000000);
    }
    else if (ucs4_char <= 0x0000FFFF)
    {
        /* 1110xxxx 10xxxxxx 10xxxxxx */
        utf8_bytes = 3;
        utf8_char[0] = (uint8_t) ((ucs4_char >> 12) | B11100000);
        utf8_char[1] = (uint8_t) (((ucs4_char >> 6) & B00111111) | B10000000);
        utf8_char[2] = (uint8_t) ((ucs4_char & B00111111) | B10000000);
    }
    else if (ucs4_char <= 0x001FFFFF)
    {
        /* 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx */
        utf8_bytes = 4;
        utf8_char[0] = (uint8_t) ((ucs4_char >> 18) | B11110000);
        utf8_char[1] = (uint8_t) (((ucs4_char >> 12) & B00111111) | B10000000);
        utf8_char[2] = (uint8_t) (((ucs4_char >> 6) & B00111111) | B10000000);
        utf8_char[3] = (uint8_t) ((ucs4_char & B00111111) | B10000000);
    }
    else if (ucs4_char <= 0x03FFFFFF)
    {
        /* 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx */
        utf8_bytes = 5;
        utf8_char[0] = (uint8_t) ((ucs4_char >> 24) | B11111000);
        utf8_char[1] = (uint8_t) (((ucs4_char >> 18) & B00111111) | B10000000);
        utf8_char[2] = (uint8_t) (((ucs4_char >> 12) & B00111111) | B10000000);
        utf8_char[3] = (uint8_t) (((ucs4_char >> 6) & B00111111) | B10000000);
        utf8_char[4] = (uint8_t) ((ucs4_char & B00111111) | B10000000);
    }
    else if (ucs4_char <= 0x7FFFFFFF)
    {
        /* 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx */
        utf8_bytes = 6;
        utf8_char[0] = (uint8_t) ((ucs4_char >> 30) | B11111100);
        utf8_char[1] = (uint8_t) (((ucs4_char >> 24) & B00111111) | B10000000);
        utf8_char[2] = (uint8_t) (((ucs4_char >> 18) & B00111111) | B10000000);
        utf8_char[3] = (uint8_t) (((ucs4_char >> 12) & B00111111) | B10000000);
        utf8_char[4] = (uint8_t) (((ucs4_char >> 6) & B00111111) | B10000000);
        utf8_char[5] = (uint8_t) ((ucs4_char & B00111111) | B10000000);
    }
    else
    {
        return UNICODE_RETURN_UCS4_INVALID;
    }

    utf8_char[utf8_bytes] = '\0';

    return UNICODE_RETURN_SUCCESS;
}

/* Convert a UTF-8 encoded character to UCS-2. */
return_t unicode_utf8_to_ucs2 (ucs2_t *ucs2, uint8_t *utf8_string,
                               size_t *length)
{
    uint8_t utf8_character = utf8_string[0];
  
    /* Is the character in the ASCII range? If so, just copy it to the
       output. */
    if (utf8_character <= 0x7F)
    {
        *ucs2 = utf8_character;
        *length = 1;
    }
    else if ((utf8_character & B11100000) == B11000000)
    {
        /* A two-byte UTF-8 sequence. Make sure the other byte is good. */
        if ((utf8_string[1] != '\0') &&
            (utf8_string[1] & B11000000) != B10000000)
        {
            return UNICODE_RETURN_UTF8_INVALID;
        }
    
        *ucs2 =
            ((utf8_string[1] & B00111111) << 0) +
            ((utf8_character & B00011111) << 6);
        *length = 2;
    }
    else if ((utf8_character & B11110000) == B11100000)
    {
        /* A three-byte UTF-8 sequence. Make sure the other bytes are
           good. */
        if ((utf8_string[1] != '\0') &&
            (utf8_string[1] & B11000000) != B10000000 &&
            (utf8_string[2] != '\0') &&
            (utf8_string[2] & B11000000) != B10000000)
        {
            return UNICODE_RETURN_UTF8_INVALID;
        }
    
        *ucs2 = 
            ((utf8_string[2] & B00111111) << 0) +
            ((utf8_string[1] & B00111111) << 6) +
            ((utf8_character & B00001111) << 12);
        *length = 3;
    }
    else
    {
        return UNICODE_RETURN_UTF8_INVALID;
    }

    return UNICODE_RETURN_SUCCESS;
}

/* Convert a UTF-8 encoded character to UCS-4. */
return_t unicode_utf8_to_ucs4 (ucs4_t *ucs4, uint8_t *utf8_string, 
                               size_t *length)
{
    uint8_t utf8_character = utf8_string[0];
  
    /* Is the character in the ASCII range? If so, just copy it to the
       output. */
    if (utf8_character <= 0x7F)
    {
        *ucs4 = utf8_character;
        *length = 1;
    }
    else if ((utf8_character & B11100000) == B11000000)
    {
        /* A two-byte UTF-8 sequence. Make sure the other byte is good. */
        if (utf8_string[1] != '\0' &&
            (utf8_string[1] & B11000000) != B10000000)
        {
            return UNICODE_RETURN_UTF8_INVALID;
        }
    
        *ucs4 =
            ((utf8_string[1] & B00111111) << 0) +
            ((utf8_character & B00011111) << 6);
        *length = 2;
    }
    else if ((utf8_character & B11110000) == B11100000)
    {
        /* A three-byte UTF-8 sequence. Make sure the other bytes are
           good. */
        if ((utf8_string[1] != '\0') &&
            (utf8_string[1] & B11000000) != B10000000 &&
            (utf8_string[2] != '\0') &&
            (utf8_string[2] & B11000000) != B10000000)
        {
            return UNICODE_RETURN_UTF8_INVALID;
        }
    
        *ucs4 = 
            ((utf8_string[2] & B00111111) << 0) +
            ((utf8_string[1] & B00111111) << 6) +
            ((utf8_character & B00001111) << 12);
        *length = 3;
    }
    else if ((utf8_character & B11111000) == B11110000)
    {
        /* A four-byte UTF-8 sequence. Make sure the other bytes are
           good. */
        if ((utf8_string[1] != '\0') &&
            (utf8_string[1] & B11000000) != B10000000 &&
            (utf8_string[2] != '\0') &&
            (utf8_string[2] & B11000000) != B10000000 &&
            (utf8_string[3] != '\0') &&
            (utf8_string[3] & B11000000) != B10000000)
        {
            return UNICODE_RETURN_UTF8_INVALID;
        }
    
        *ucs4 = 
            ((utf8_string[3] & B00111111) << 0) +
            ((utf8_string[2] & B00111111) << 6) +
            ((utf8_string[1] & B00111111) << 12) +
            ((utf8_character & B00000111) << 18);
        *length = 4;
    }
    else if ((utf8_character & B11111100) == B11111000)
    {
        /* A five-byte UTF-8 sequence. Make sure the other bytes are
           good. */
        if ((utf8_string[1] != '\0') &&
            (utf8_string[1] & B11000000) != B10000000 &&
            (utf8_string[2] != '\0') &&
            (utf8_string[2] & B11000000) != B10000000 &&
            (utf8_string[3] != '\0') &&
            (utf8_string[3] & B11000000) != B10000000 &&
            (utf8_string[4] != '\0') &&
            (utf8_string[4] & B11000000) != B10000000)
        {
            return UNICODE_RETURN_UTF8_INVALID;
        }
    
        *ucs4 = 
            ((utf8_string[4] & B00111111) << 0) +
            ((utf8_string[3] & B00111111) << 6) +
            ((utf8_string[2] & B00111111) << 12) +
            ((utf8_string[1] & B00111111) << 18) +
            ((utf8_character & B00000011) << 24);
        *length = 5;
    }
    else if ((utf8_character & B11111110) == B11111100)
    {
        /* A six-byte UTF-8 sequence. Make sure the other bytes are
           good. */
        if ((utf8_string[1] != '\0') &&
            (utf8_string[1] & B11000000) != B10000000 &&
            (utf8_string[2] != '\0') &&
            (utf8_string[2] & B11000000) != B10000000 &&
            (utf8_string[3] != '\0') &&
            (utf8_string[3] & B11000000) != B10000000 &&
            (utf8_string[4] != '\0') &&
            (utf8_string[4] & B11000000) != B10000000 &&
            (utf8_string[5] != '\0') &&
            (utf8_string[5] & B11000000) != B10000000)
        {
            return UNICODE_RETURN_UTF8_INVALID;
        }
    
        *ucs4 = 
            ((utf8_string[5] & B00111111) << 0) +
            ((utf8_string[4] & B00111111) << 6) +
            ((utf8_string[3] & B00111111) << 12) +
            ((utf8_string[2] & B00111111) << 18) +
            ((utf8_string[1] & B00111111) << 24) +
            ((utf8_character & B00000001) << 30);
        *length = 6;
    }
    else
    {
        return UNICODE_RETURN_UTF8_INVALID;
    }

    return UNICODE_RETURN_SUCCESS;
}

/* Convert a UCS-2 string to UTF-8 encoding. */
return_t unicode_ucs2_to_utf8_string (uint8_t *utf8_string,
                                      ucs2_t *ucs2_string,
                                      size_t max_utf8_bytes)
{
    size_t ucs2_index = 0;
    size_t utf8_index = 0;
    ucs2_t ucs2_char;
    uint8_t utf8_char[6];

    ucs2_char = ucs2_string[ucs2_index];

    while (ucs2_char != 0)
    {
        if (unicode_ucs2_to_utf8 (utf8_char, ucs2_char, NULL) != UNICODE_RETURN_SUCCESS)
        {
            return UNICODE_RETURN_UCS2_INVALID;
        }

        ucs2_index++;
        ucs2_char = ucs2_string[ucs2_index];

        if (utf8_index + string_length (utf8_char) >= max_utf8_bytes)
        {
            return UNICODE_RETURN_BUFFER_TOO_SHORT;
        }
        else
        {
            string_copy (utf8_string + utf8_index, utf8_char);
            utf8_index += string_length (utf8_char);
        }
    }

    return UNICODE_RETURN_SUCCESS;
}

/* Convert a UCS-4 string to UTF-8 encoding. */
return_t unicode_ucs4_to_utf8_string (uint8_t *utf8_string,
                                      ucs4_t *ucs4_string,
                                      size_t max_utf8_bytes)
{
    int ucs4_index = 0;
    int utf8_index = 0;
    ucs4_t ucs4_char;
    uint8_t utf8_char[6];

    while (ucs4_string[ucs4_index] != 0)
    {
        ucs4_char = ucs4_string[ucs4_index];

        if (unicode_ucs4_to_utf8 (utf8_char, ucs4_char) != UNICODE_RETURN_SUCCESS)
        {
            return UNICODE_RETURN_UCS4_INVALID;
        }

        ucs4_index++;

        if (utf8_index + string_length (utf8_char) >= max_utf8_bytes)
        {
            return UNICODE_RETURN_BUFFER_TOO_SHORT;
        }
        else
        {
            string_copy (utf8_string + utf8_index, utf8_char);
            utf8_index += string_length (utf8_char);
        }
    }
    return UNICODE_RETURN_SUCCESS;
}

/* Convert a UTF-8 encoded string to UCS-2. */
return_t unicode_utf8_to_ucs2_string (ucs2_t *ucs2_string,
                                      uint8_t *utf8_string,
                                      size_t max_ucs2_characters)
{
    size_t input_index = 0;
    size_t output_index = 0;
    unsigned int length;

    while (utf8_string[input_index] != '\0' &&
           output_index < max_ucs2_characters)
    {
        if (unicode_utf8_to_ucs2 (ucs2_string + output_index,
                                  utf8_string + input_index,
                                  &length) != UNICODE_RETURN_SUCCESS)
        {
            return UNICODE_RETURN_UTF8_INVALID;
        }

        input_index += length;
        output_index++;
    }

    ucs2_string[output_index] = 0;

    return UNICODE_RETURN_SUCCESS;
}

/* Convert a UTF-8 encoded string to UCS-4. */
return_t unicode_utf8_to_ucs4_string (ucs4_t *ucs4_string,
                                      uint8_t *utf8_string,
                                      size_t max_ucs4_characters)
{
    size_t input_index = 0;
    size_t output_index = 0;
    unsigned int length;

    while (utf8_string[input_index] != '\0' &&
           output_index < max_ucs4_characters)
    {
        if (unicode_utf8_to_ucs4 (ucs4_string + output_index,
                                  utf8_string + input_index,
                                  &length) != UNICODE_RETURN_SUCCESS)
        {
            return UNICODE_RETURN_UTF8_INVALID;
        }

        input_index += length;
        output_index++;
    }

    ucs4_string[output_index] = 0;
  
    /* FIXME: Check if we ran out of output space. Likewise in the UCS2
       function. */
    return UNICODE_RETURN_SUCCESS;
}

/* Return the character prior to the character at the given position's
   length. */
size_t unicode_utf8_previous_character_length (char *utf8_string, unsigned int string_position)
{
    unsigned int character_length = 0;

    if ((utf8_string[string_position - 1] & 0x80) == 0x80)
    {
        while (string_position > 0 &&
               (utf8_string[string_position - 1] & 0xC0) == 0x80)
        {
            string_position--;
            character_length++;
        }
    
        if (string_position > 0 &&
            (utf8_string[string_position - 1] & 0xC0) == 0xC0)
        {
            character_length++;
        }
    }
    else
    {
        character_length = 1;
    }

    return character_length;
}

/* Return the character after the character at the given position's
   length. */
size_t unicode_utf8_next_character_length (char *utf8_string, unsigned int string_position)
{
    unsigned int character_length;

    if ((utf8_string[string_position] & 0x80) == 0x80)
    {
        character_length = 1;
        string_position++;

        while ((utf8_string[string_position] & 0xC0) == 0x80)
        {
            string_position++;
            character_length++;
        }
    }
    else
    {
        character_length = 1;
    }

    return character_length;
}

/* Return the number of characters in a UTF-8 encoded string. */
// FIXME: Add error handling. What if we find broken UTF-8 sequences
// for example?
size_t unicode_utf8_string_characters (uint8_t *utf8_string)
{
    unsigned int input_index = 0;
    unsigned int string_characters = 0;
    unsigned int length;

    while (utf8_string[input_index] != '\0')
    {
        length = unicode_utf8_next_character_length (utf8_string, input_index);

        input_index += length;
        string_characters++;
    }

    return string_characters;
}
