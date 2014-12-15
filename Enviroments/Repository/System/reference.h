
#include <list.h>
#include <hash_table.h>

#define REFERENCE_MAGIC_NUMBER_NULL         (0x5AA5A55A)
#define REFERENCE_MAGIC_NUMBER_METHOD       (0xABCD0123)
#define REFERENCE_MAGIC_NUMBER_INTERFACE    (0xEF894567)
#define REFERENCE_MAGIC_NUMBER_CLASS        (0x03C00C30)
#define REFERENCE_MAGIC_NUMBER_SECURITY     (0x01234567)
#define REFERENCE_MAGIC_NUMBER_OBJECT       (0xFEDCBA98)
#define REFERENCE_MAGIC_NUMBER_HANDLE       (0x6789ABCD)

#define REFERENCE_MAGIC_NUMBER_EVENT_SUPPLIER_INTERFACE    (0x0002ABCD)
#define REFERENCE_MAGIC_NUMBER_EVENT_CONSUMER_INTERFACE    (0x0003ABCD)
#define REFERENCE_MAGIC_NUMBER_EVENT_SUPPLIER    (0x0004ABCD)
#define REFERENCE_MAGIC_NUMBER_EVENT_CONSUMER    (0x0005ABCD)

#define REFERENCE_MAGIC_NUMBER_EVENT_QUEUE       (0x0001ABCD)

typedef struct
{
    list_node_t node;

    uint32_t type;
    uint32_t magic_number;

    object_reference_t owner;

    atomic_uint32_t number_of_references;
    spinlock_t lock;
    
    bool is_static;

//    p_hash_element_t element;
    
} reference_struct_t;

typedef reference_struct_t * p_reference_struct_t;

//extern reference_t reference_create (p_reference_struct_t reference_struct);
//extern void reference_destroy (reference_t reference);

