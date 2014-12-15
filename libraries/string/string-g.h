#ifndef _STRING_H_
#define _STRING_H_

#ifdef __cplusplus
extern "C" {
#endif

extern char * ___strtok;
extern char * string_pbrk (const char *, const char *);
extern char * string_tok (char *, const char *);
extern char * string_sep (char **, const char *);
extern unsigned int string_spn (const char *, const char *);


/*
 * Include machine specific inline routines
 */
#include <asm/string.h>

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

#ifndef __HAVE_ARCH_STRNICMP
extern int string_ni_compare (const char *, const char *, unsigned int);
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

#endif /* _STRING_H_ */
