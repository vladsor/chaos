enum
{
    CLASS_TYPE_STATIC,    
    CLASS_TYPE_DYNAMIC,
};

#define CID_NONE                (0)
#define CID_EMPTY               (1)

typedef uint32_t class_id_t;
typedef class_id_t * p_class_id_t;

typedef struct
{
    class_id_t id;
    uint32_t class_type;
    uint32_t number_of_interfaces;
} class_description_t;

typedef class_description_t * p_class_description_t;

typedef struct
{
    HASH_ELEMENT_PART;

    class_id_t id;
    
    char name[STRING_MAX_LENGTH];
    
    p_class_description_t description;
    sequence_t interfaces;
    object_reference_t repository;

    uint32_t number_of_references;
} class_t;

typedef class_t * p_class_t;

#if defined (__STORM_KERNEL__) || defined (__STORM_KERNEL_MODULE__)
typedef p_class_t class_reference_t;
#elif defined (__STORM_PROGRAM__)
typedef class_id_t class_reference_t;
#else
#error "Unknown target of object file"
#endif

typedef class_reference_t * p_class_reference_t;

extern void class_register (p_class_reference_t class_reference, 
    p_class_description_t class_description,
    sequence_t class_interfaces, handle_t class_repository);

extern void class_unregister (class_reference_t class_reference);
/*    
extern void class_set_interfaces (class_reference_t class_reference, 
    sequence_t class_interfaces);

extern sequence_t class_get_interfaces (class_reference_t class_reference);
*/
extern interface_reference_t class_get_interface (
    class_reference_t class_reference, interface_id_t interface_id);

