
/* Exception handlers prototypes. Low-level first: */
extern void EXCEPTION_HANDLER_DIVIDE_ERROR_LOWLEVEL (void);
extern void EXCEPTION_HANDLER_DEBUG_LOWLEVEL (void);
extern void EXCEPTION_HANDLER_NONMASKABLE_INTERRUPT_LOWLEVEL (void);
extern void EXCEPTION_HANDLER_BREAKPOINT_LOWLEVEL (void);
extern void EXCEPTION_HANDLER_OVERFLOW_LOWLEVEL (void);
extern void EXCEPTION_HANDLER_BOUND_RANGE_EXCEEDED_LOWLEVEL (void);
extern void EXCEPTION_HANDLER_INVALID_OPCODE_LOWLEVEL (void);
extern void EXCEPTION_HANDLER_DEVICE_NOT_AVAILABLE_LOWLEVEL (void);
extern void EXCEPTION_HANDLER_DOUBLE_FAULT_LOWLEVEL (void);
extern void EXCEPTION_HANDLER_COPROCESSOR_SEGMENT_OVERRUN_LOWLEVEL (void);
extern void EXCEPTION_HANDLER_INVALID_TSS_LOWLEVEL (void);
extern void EXCEPTION_HANDLER_SEGMENT_NOT_PRESENT_LOWLEVEL (void);
extern void EXCEPTION_HANDLER_STACK_FAULT_LOWLEVEL (void);
extern void EXCEPTION_HANDLER_GENERAL_PROTECTION_LOWLEVEL (void);
extern void EXCEPTION_HANDLER_PAGE_FAULT_LOWLEVEL (void);
extern void EXCEPTION_HANDLER_DUMMY_LOWLEVEL (void);
extern void EXCEPTION_HANDLER_FLOATING_POINT_ERROR_LOWLEVEL (void);
extern void EXCEPTION_HANDLER_ALIGNMENT_CHECK_LOWLEVEL (void);
extern void EXCEPTION_HANDLER_MACHINE_CHECK_LOWLEVEL (void);
extern void EXCEPTION_HANDLER_STREAMING_SIMD_EXTENSIONS_LOWLEVEL (void);

/* ...and the C functions. */
extern void EXCEPTION_HANDLER_DIVIDE_ERROR (
    exception_hardware_info_t exception_info);
    
extern void EXCEPTION_HANDLER_DEBUG (exception_hardware_info_t exception_info);

extern void EXCEPTION_HANDLER_NONMASKABLE_INTERRUPT (
    exception_hardware_info_t exception_info);
    
extern void EXCEPTION_HANDLER_BREAKPOINT (
    exception_hardware_info_t exception_info);
    
extern void EXCEPTION_HANDLER_OVERFLOW (
    exception_hardware_info_t exception_info);
    
extern void EXCEPTION_HANDLER_BOUND_RANGE_EXCEEDED (
    exception_hardware_info_t exception_info);

extern void EXCEPTION_HANDLER_INVALID_OPCODE (
    exception_hardware_info_t exception_info);
    
extern void EXCEPTION_HANDLER_DEVICE_NOT_AVAILABLE (
    exception_hardware_info_t exception_info);

extern void EXCEPTION_HANDLER_DOUBLE_FAULT (
    exception_hardware_with_error_code_info_t exception_info);
    
extern void EXCEPTION_HANDLER_COPROCESSOR_SEGMENT_OVERRUN (
    exception_hardware_info_t exception_info);
    
extern void EXCEPTION_HANDLER_INVALID_TSS (
    exception_hardware_segment_info_t exception_info);

extern void EXCEPTION_HANDLER_SEGMENT_NOT_PRESENT (
    exception_hardware_segment_info_t exception_info);
    
extern void EXCEPTION_HANDLER_STACK_FAULT (
    exception_hardware_segment_info_t exception_info);
    
extern void EXCEPTION_HANDLER_GENERAL_PROTECTION (
    exception_hardware_segment_info_t exception_info);

extern void EXCEPTION_HANDLER_PAGE_FAULT (
    exception_hardware_page_info_t exception_info);

extern void EXCEPTION_HANDLER_DUMMY (exception_hardware_info_t exception_info);

extern void EXCEPTION_HANDLER_FLOATING_POINT_ERROR (
    exception_hardware_info_t exception_info);
    
extern void EXCEPTION_HANDLER_ALIGNMENT_CHECK (
    exception_hardware_with_error_code_info_t exception_info);
    
extern void EXCEPTION_HANDLER_MACHINE_CHECK (
    exception_hardware_info_t exception_info);
    
extern void EXCEPTION_HANDLER_STREAMING_SIMD_EXTENSIONS (
    exception_hardware_info_t exception_info);

