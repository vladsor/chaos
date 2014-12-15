
enum
{
    CLASS_TYPE_STATIC,    
    CLASS_TYPE_DYNAMIC,
};

typedef struct
{
    handle_reference_t handle;
    p_void_t data;
} transaction_control_t;

#include <hash_table.h>

typedef struct
{
    HASH_ELEMENT_PART;

    class_id_t id;
    
    char name[STRING_MAX_LENGTH];

    uint32_t number_of_references;
    bool is_static;
    
    bool is_active;

    sequence_t filtered_objects;
    sequence_t ignored_objects;

    sequence_t transaction_controls;

    uint32_t slot;
    sequence_t history;
} transaction_t;

typedef transaction_t * p_transaction_t;

extern transaction_reference_t transaction_create_static (p_transaction_t transaction);
extern void transaction_destroy_static (transaction_reference_t transaction);

extern transaction_reference_t transaction_create (sequence_t filtered_objects, 
    sequence_t ignored_objects, uint32_t history_depth, uint32_t options);
extern void transaction_destroy (transaction_reference_t transaction);

extern void transaction_begin (transaction_reference_t transaction);

extern void transaction_commit (transaction_reference_t transaction);
//extern void transaction_flush (transaction_reference_t transaction);

extern void transaction_rollback (transaction_reference_t transaction);

/*
extern uint32_t get_status (transaction_reference_t transaction);

    void get_options (
        out unsigned long options);

    void set_options (
        in  unsigned long options);
*/

//extern void transaction_pause (transaction_reference_t transaction);
//extern void transaction_resume (transaction_reference_t transaction);


