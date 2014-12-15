/* Abstract: String inlines declarations. */
/* Author: Vladimir Sorokin */

/* Copyright 2000 chaos development. */

#ifndef __LIBRARY_STRING_WSTRING_INLINES_H__
#define __LIBRARY_STRING_WSTRING_INLINES_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _WCHAR_T
#define _WCHAR_T

typedef uint16_t wchar_t;
#endif /* !_WCHAR_T */

/**
 * @brief Find the first occurrence in S of any character in REJECT.
 * @param string
 * @param reject
 * @return
 */
extern wchar_t * wstring_scn (wchar_t *string, wchar_t *reject);

static inline bool wstring_is_empty (wchar_t *string)
{
    return string[0] == L'\0';
}

#ifndef HAVE_ARCHITECTURE_WSTRING_COPY
extern wchar_t * wstring_copy (wchar_t *, const wchar_t *);
#endif

#ifndef HAVE_ARCHITECTURE_WSTRING_COPY_MAX
extern wchar_t * wstring_copy_max (wchar_t *, const wchar_t *, unsigned int);
#endif

#ifndef HAVE_ARCHITECTURE_WSTRING_APPEND
extern wchar_t * wstring_append (wchar_t *, const wchar_t *);
#endif

#ifndef HAVE_ARCHITECTURE_WSTRING_APPEND_MAX
extern wchar_t * wstring_append_max (wchar_t *, const wchar_t *, unsigned int);
#endif

#ifndef HAVE_ARCHITECTURE_WSTRING_COMPARE
extern wchar_t wstring_compare (const wchar_t *, const wchar_t *);
#endif

#ifndef HAVE_ARCHITECTURE_WSTRING_COMPARE_MAX
extern wchar_t wstring_compare_max (const wchar_t *, const wchar_t *, unsigned int);
#endif

#ifndef HAVE_ARCHITECTURE_WSTRING_LENGTH
extern unsigned int wstring_length (const wchar_t *);
#endif

#ifndef HAVE_ARCHITECTURE_WSTRING_LENGTH_MAX
extern unsigned int wstring_length_max (const wchar_t *, unsigned int);
#endif

#ifndef HAVE_ARCHITECTURE_WSTRING_COMPARE_TEMPLATE
extern bool wstring_compare_template (wchar_t *s1, wchar_t *s2);
#endif

#ifndef HAVE_ARCHITECTURE_WSTRING_FIND_FIRST_CHAR
extern wchar_t * wstring_find_first_char (const wchar_t *, wchar_t);
#endif

#ifndef HAVE_ARCHITECTURE_WSTRING_FIND_LAST_CHAR
extern wchar_t * wstring_find_last_char (const wchar_t *, wchar_t);
#endif

#ifndef HAVE_ARCHITECTURE_WSTRING_FIND_SUBSTRING
extern wchar_t * wstring_find_substring (const wchar_t *, const wchar_t *);
#endif

#ifdef __cplusplus
}
#endif

#endif /* __LIBRARY_STRING_WSTRING_INLINES_H__ */

