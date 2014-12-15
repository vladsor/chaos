typedef uint32_t exception_id_t;
typedef exception_id_t * p_exception_id_t;

typedef struct
{
    HASH_ELEMENT_PART;

    exception_id_t id;

    char name[STRING_MAX_LENGTH];

} exception_description_t;

typedef exception_description_t * p_exception_description_t;

extern void exception_register (
    p_exception_description_t exception_description);

extern void exception_unregister (
    p_exception_description_t exception_description);
