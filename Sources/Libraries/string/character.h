/**
 * @file                character.h
 * @brief               Functions for working with character.
 * @author              Vladimir Sorokin
 * @version             1.0
 * @date                2000-2003
 */

#ifndef __LIBRARY_STRING_CHARACTER_H__
#define __LIBRARY_STRING_CHARACTER_H__

/**
 * @brief               Convert character to upper case.
 * @param character
 * @return
 */
extern char char_to_upper_case (char character);

/**
 * @brief               Convert character to lower case.
 * @param character
 * @return
 */
extern char char_to_lower_case (char character);

/**
 * @brief               Convert character to number.
 * @param character
 * @return
 */
extern unsigned int char_to_int (char character);

/**
 * @brief               Convert digit to string presentation.
 * @param character
 * @return
 */
extern char int_to_char (int character);

/**
 * @brief               Check if character is alpha or number.
 * @param character
 * @return
 */
extern bool char_is_alpha_or_number (char character);

/**
 * @brief               Check if character is alpha.
 * @param character
 * @return
 */
extern bool char_is_alpha (char character);

/**
 * @brief               Check if character is control symbol.
 * @param character
 * @return
 */
extern bool char_is_control (char character);

/**
 * @brief               Check if character is digit.
 * @param character
 * @return
 */
extern bool char_is_digit (char character);

/**
 * @brief               Check if character is in lower case.
 * @param character
 * @return
 */
extern bool char_is_lower (char character);

/**
 * @brief               Check if character is space.
 * @param character
 * @return
 */
extern bool char_is_space (char character);

/**
 * @brief               Check if character is in upper case.
 * @param character
 * @return
 */
extern bool char_is_upper (char character);

/**
 * @brief               Check if character is heximal digit.
 * @param character
 * @return
 */
extern bool char_is_heximal_digit (char character);

/**
 * @brief               Check if character is number.
 * @param character
 * @param base
 * @return
 */
extern bool char_is_number (char character, int base);

#endif /* __LIBRARY_STRING_CHARACTER_H__ */
