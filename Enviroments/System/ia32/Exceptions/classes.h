/** 
 * @addtogroup group_exceptions Exceptions
 *
 * @{
 */

/** 
 * @defgroup group_exception_classes Exception classifications
 *
 * @brief               Exceptions are classified as faults, traps, or aborts 
 *                      depending on the way they are reported and whether the 
 *                      instruction that caused the exception can be restarted
 *                      with no loss of program or task continuity.
 *
 * @{
 */

#define EXCEPTION_CLASS_NONE       (0)
 
/**
 * @brief               A fault is an exception that can generally be corrected
 *                      and that, once corrected, allows the program to be 
 *                      restarted with no loss of continuity. 
 *
 * When a fault is reported, the processor restores the machine state to the 
 * state prior to the beginning of execution of the faulting instruction.
 * The return address (saved contents of the CS and EIP registers) for the
 * fault handler points to the faulting instruction, rather than the
 * instruction following the faulting instruction.
 *
 * @note  There are a small subset of exceptions that are normally reported 
 * as faults, but under architectural corner cases, they are not restartable
 * and some processor context will be lost. An example of these cases is the
 * execution of the POPAD instruction where the stack frame crosses over the
 * end of the stack segment. The exception handler will see that the CS:EIP has
 * been restored as if the POPAD instruction had not executed however internal
 * processor state (general purpose registers) will have been modified. These
 * corner cases are INTERRUPT AND EXCEPTION HANDLING considered programming
 * errors and an application causeing this class of exceptions will likely be
 * terminated by the operating system.
 */
#define EXCEPTION_CLASS_FAULT       (1)

/**
 * @brief               A trap is an exception that is reported immediately 
 *                      following the execution of the trapping instruction.
 *
 * Traps allow execution of a program or task to be continued without loss of
 * program continuity. The return address for the trap handler points to the
 * instruction to be executed after the trapping instruction.
 */    
#define EXCEPTION_CLASS_TRAP        (2)

/**
 * @brief               An abort is an exception that does not always report
 *                      the precise location of the instruction causing the 
 *                      exception and does not allow restart of the program or
 *                      task that caused the exception.
 *
 * Aborts are used to report severe errors, such as hardware errors and
 * inconsistent or illegal values in system tables.
 */
#define EXCEPTION_CLASS_ABORT       (3)

#define EXCEPTION_CLASS_INTERRUPT   (4)

/**
 * @} // end of group_exception_classes
 */

/**
 * }@ // end of group group_exceptions
 */
