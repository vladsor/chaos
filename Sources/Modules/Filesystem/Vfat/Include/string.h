//extern void vfat_initstr (u8 *wstr, u32 wsize);//extern u8 * vfat_wcsncat (u8 *dest, u8 *src, u32 wstart, u32 wcount);//extern u8 * vfat_wcsncpy (u8 *dest, u8 *src, u32 wcount);//extern u8 * vfat_movstr (u8 *src, u32 dpos, u32 spos, u32 len);
extern bool wstrcmpi (uint8_t *s1, uint8_t *s2);
extern bool wstrcmpjoki (uint8_t *s1, uint8_t *s2);
extern uint8_t * vfat_get_next_path_element (uint8_t *file_name);
extern bool vfat_is_file_name_valid (uint8_t *file_name);
extern int wcscmp (const uint8_t *cs, const uint8_t *ct);
extern uint8_t *wcschr (const uint8_t *str, uint8_t ch);
extern uint8_t * wcsrchr (const uint8_t *str, uint8_t ch);
extern uint8_t* wcscpy (uint8_t* str1, const uint8_t* str2);
extern uint8_t* wcsncpy (uint8_t *dest, const uint8_t *src, uint32_t count);
extern uint32_t wcslen (const uint8_t *s);
extern uint8_t *wcscat (uint8_t *dest, const uint8_t *src);
extern void vfat_sub_string (uint8_t *target, const uint8_t *source, uint32_t length);