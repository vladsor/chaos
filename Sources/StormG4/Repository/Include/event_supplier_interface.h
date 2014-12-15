
#ifdef REPOSITORY_NOT_INLINE

extern p_event_supplier_interface_t 
    event_supplier_interface_create_static_internal (
        p_event_supplier_interface_t event_supplier_interface);

extern void event_supplier_interface_destroy_static_internal (
    p_event_supplier_interface_t event_supplier_interface);

extern p_event_supplier_interface_t event_supplier_interface_create_internal (
    p_event_supplier_interface_description_t event_supplier_interface_description, 
    sequence_t event_supplier_interface_methods);
    
extern void event_supplier_interface_destroy_internal (
    p_event_supplier_interface_t event_supplier_interface);

#else

#include "../EventSupplierInterface/Include/internal.h"

#endif /* REPOSITORY_NOT_INLINE */

