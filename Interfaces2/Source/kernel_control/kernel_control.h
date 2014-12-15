
#define KERNEL_CONTROL_INIT_WRAPPER() \
void init_wrapper (context_t context, \
    sequence_t parameters_in UNUSED, \
    sequence_t parameters_out UNUSED)

#define KERNEL_CONTROL_START_WRAPPER() \
void start_wrapper (context_t context, \
    sequence_t parameters_in UNUSED, \
    sequence_t parameters_out UNUSED)

#define KERNEL_CONTROL_STOP_WRAPPER() \
void stop_wrapper (context_t context, \
    sequence_t parameters_in UNUSED, \
    sequence_t parameters_out UNUSED)

extern 
    interface_reference_t 
        kernel_control_interface_register 
        (
            class_reference_t class_reference,
            p_kernel_control_interface_table_t table
        );


