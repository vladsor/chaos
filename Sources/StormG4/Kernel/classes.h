
typedef class_reference_t (kernel_class_init_function_t) (void);
typedef kernel_class_init_function_t * p_kernel_class_init_function_t;

enum
{
    KERNEL_CLASS_FLAT_NAMESPACE_INDEX,
    KERNEL_CLASS_STORM_MODULE_INDEX,
    KERNEL_CLASS_STORM_PROGRAM_INDEX,
};

typedef struct
{
    const wchar_t *name;
    p_kernel_class_init_function_t init;
    class_reference_t class;
    bool enabled;

} kernel_class_info_t;

extern kernel_class_info_t kernel_classes_info[];

extern class_reference_t flat_namespace_class_init (void);
extern class_reference_t storm_module_class_init (void);
extern class_reference_t storm_program_class_init (void);


    
