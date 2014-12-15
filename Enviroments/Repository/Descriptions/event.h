
typedef uint32_t event_id_t;

typedef struct
{
    description_reference_struct_t header;

    wchar_t name[WSTRING_MAX_LENGTH];

    uint32_t data_length;
} event_description_t;

typedef event_description_t * p_event_description_t;

// Static
extern 
    description_reference_t 
        event_description_register_static 
        (
            p_event_description_t event_description
        );
    
extern 
    void 
        event_description_unregister_static 
        (
            description_reference_t description_reference
        );

// Dynamic
extern 
    description_reference_t 
        event_description_register 
        (
            id_t id,
            const wchar_t *name,
            uint32_t data_length
        );

extern 
    void 
        event_description_unregister 
        (
            description_reference_t description_reference
        );


