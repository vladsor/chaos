
#define IID_MUTEX 0x00000001

enum
{
    MID_MUTEX_LOCK,
    MID_MUTEX_UNLOCK,
};

typedef return_t (mutex_lock_function_t) (context_t *context);
typedef return_t (mutex_unlock_function_t) (context_t *context);

    
typedef struct
{
    mutex_lock_function_t *lock;
    mutex_unlock_function_t *unlock;
} mutex_interface_t;

typedef struct
{
    mutex_lock_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[0];

} mutex_lock_method_t;

#define MUTEX_LOCK_METHOD(function) \
    (&(function)), \
    (MID_MUTEX_LOCK), \
    (0), \
    (0)
    
typedef struct
{
    mutex_unlock_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[0];

} mutex_unlock_method_t;

#define MUTEX_UNLOCK_METHOD(function) \
    (&(function)), \
    (MID_MUTEX_UNLOCK), \
    (0), \
    (0)

#define mutex$lock(handle) \
    ((mutex_interface_t *) ((handle)->functions))->lock ( \
        &((handle)->context))

#define mutex$unlock(handle) \
    ((mutex_interface_t *) ((handle)->functions))->unlock ( \
        &((handle)->context))



