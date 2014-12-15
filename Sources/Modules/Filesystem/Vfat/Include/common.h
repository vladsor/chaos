
extern uint32_t cluster_to_sector (
    p_vfat_volume_t vfat_volume,
    uint32_t cluster);
  
void vfat_8_dot_3_to_wstring (
    const char *base_name,
    const char *extension,
    wchar_t *name);

void vfat_8_dot_3_to_volume_label (
    const char *base_name,
    const char *extension,
    char *name);
  
extern bool wstrcmpjoki (const wchar_t *string1, const wchar_t *string2);

extern wchar_t * vfat_get_next_path_element (wchar_t *file_name);
extern void vfat_sub_string (wchar_t *target, const wchar_t *source, 
    uint32_t length);