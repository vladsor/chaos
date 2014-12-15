/* Abstract: String inlines declarations. */
/* Author: Vladimir Sorokin */

/* Copyright 2000 chaos development. */

#ifndef __LIBRARY_STRING_INLINES_H__
#define __LIBRARY_STRING_INLINES_H__

#ifdef __cplusplus
extern "C" {
#endif

extern char * ___strtok;

/**
 * @brief Find the first occurrence in S of any character in ACCEPT.  
 * @param string
 * @param accept
 * @return
 */
extern char * string_pbrk (const char *string, const char *accept);

/**
 * @brief Divide S into tokens separated by characters in DELIM.  
 * @param string
 * @param delim
 * @return
 */
extern char * string_tok (char *string, const char *delim);

/**
 * @brief Return the next DELIM-delimited token from *STRINGP, terminating it 
 * with a '\0', and update *STRINGP to point past it.
 * @param stringp
 * @param delim
 * @return
 */
extern char * string_sep (char **stringp, const char *delim);

/**
 * @brief Return the length of the initial segment of S which consists entirely
 * of characters in ACCEPT.  
 * @param string
 * @param accept
 * @return
 */
extern unsigned int string_spn (const char *string, const char *accept);

/**
 * @brief Find the first occurrence in S of any character in REJECT.
 * @param string
 * @param reject
 * @return
 */
extern char *string_scn (char *string, char *reject);

static inline bool string_is_empty (char *string)
{
    return string[0] == '\0';
}

#ifndef HAVE_ARCHITECTURE_STRING_COPY
extern char * string_copy (char *, const char *);
#endif

#ifndef HAVE_ARCHITECTURE_STRING_COPY_MAX
extern char * string_copy_max (char *, const char *, unsigned int);
#endif

#ifndef HAVE_ARCHITECTURE_STRING_APPEND
extern char * string_append (char *, const char *);
#endif

#ifndef HAVE_ARCHITECTURE_STRING_APPEND_MAX
extern char * string_append_max (char *, const char *, unsigned int);
#endif

#ifndef HAVE_ARCHITECTURE_STRING_COMPARE
extern int string_compare (const char *, const char *);
#endif

#ifndef HAVE_ARCHITECTURE_STRING_COMPARE_MAX
extern int string_compare_max (const char *, const char *, unsigned int);
#endif

#ifndef HAVE_ARCHITECTURE_STRING_LENGTH
extern unsigned int string_length (const char *);
#endif

#ifndef HAVE_ARCHITECTURE_STRING_LENGTH_MAX
extern unsigned int string_length_max (const char *, unsigned int);
#endif

#ifndef HAVE_ARCHITECTURE_STRING_I_COMPARE_MAX
extern int string_i_compare_max (const char *, const char *, unsigned int);
#endif

#ifndef HAVE_ARCHITECTURE_STRING_FIND_FIRST_CHAR
extern char * string_find_first_char (const char *, int);
#endif

#ifndef HAVE_ARCHITECTURE_STRING_FIND_LAST_CHAR
extern char * string_find_last_char (const char *, int);
#endif

#ifndef HAVE_ARCHITECTURE_STRING_FIND_SUBSTRING
extern char * string_find_substring (const char *, const char *);
#endif

#ifdef __cplusplus
}
#endif

#endif /* __LIBRARY_STRING_INLINES_H__ */
