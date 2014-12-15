enum
{
    EXCEPTION_INVALID_PARAMETERS,
    EXCEPTION_NOT_IMPLEMENTED,
    EXCEPTION_NOT_SUPPORTED,
    EXCEPTION_ACCESS_DENIED,
    EXCEPTION_IS_LOCKED,
    EXCEPTION_NOT_ENOUGH_RESOURCES,
    EXCEPTION_INTERNAL_FAULT,
};
/*
typedef struct
{
    description_reference_struct_t header;

    wchar_t name[WSTRING_MAX_LENGTH];

    uint32_t length;

} exception_description_t;

typedef exception_description_t * p_exception_description_t;


extern description_reference_t exception_description_register_static (
    p_exception_description_t exception_description);
    
extern void exception_description_unregister_static (
    description_reference_t description);

extern description_reference_t exception_description_register (
    p_exception_description_t exception_description);

extern void exception_description_unregister (
    description_reference_t description);
*/

