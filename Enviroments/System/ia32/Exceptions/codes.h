/** 
 * @addtogroup group_exceptions Exceptions
 *
 * @{
 */

/** 
 * @defgroup group_exception_codes Exception codes
 *
 * The following sections describe conditions which generate exceptions and
 * interrupts. They are arranged in the order of vector numbers. The
 * information contained in these sections are as follows:
 *
 * @par                 Exception Class 
 * Indicates whether the exception class is a fault, trap, or abort type.
 * Some exceptions can be either a fault or trap type, depending on when the
 * error condition is detected. (This section is not applicable to interrupts.)
 *
 * @par                 Description 
 * Gives a general description of the purpose of the exception or interrupt
 * type. It also describes how the processor handles the exception or
 * interrupt.
 *
 * @par                 Exception Error Code 
 * Indicates whether an error code is saved for the exception. If one is saved,
 * the contents of the error code are described. (This section is not
 * applicable to interrupts.)
 *
 * @par                 Saved Instruction Pointer 
 * Describes which instruction the saved (or return) instruction pointer points
 * to. It also indicates whether the pointer can be used to restart a faulting
 * instruction.
 *
 * @par                 Program State Change 
 * Describes the effects of the exception or interrupt on the state of the
 * currently running program or task and the possibilities of restarting the
 * program or task without loss of continuity.
 *
 * @{
 */


/**
 * @brief               <H3>Interrupt 0—Divide Error Exception (#DE)</H3>
 *
 * @par                 Exception Class 
 * Fault.
 *
 * @par                 Description
 * Indicates the divisor operand for a DIV or IDIV instruction is 0 or that the
 * result cannot be represented in the number of bits specified for the
 * destination operand.
 *
 * @par                 Exception Error Code
 * None.
 *
 * @par                 Saved Instruction Pointer
 * Saved contents of CS and EIP registers point to the instruction that
 * generated the exception.
 *
 * @par                 Program State Change
 * A program-state change does not accompany the divide error, because the
 * exception occurs before the faulting instruction is executed.
 */
#define EXCEPTION_DIVIDE_ERROR                  (0)

/**
 * @brief               <H3>Interrupt 1—Debug Exception (#DB)</H3>
 *
 * @par                 Exception Class
 * Trap or Fault. The exception handler can distinguish between traps or faults
 * by examining the contents of DR6 and the other debug registers.
 *
 * @par                 Description
 * Indicates that one or more of several debug-exception conditions has been
 * detected. Whether the exception is a fault or a trap depends on the
 * condition, as shown below:
 * <TABLE> 
 *     <TR> 
 *         <TD> <B><CENTER>Exception Condition</CENTER></B> </TD>
 *         <TD> <B><CENTER>Exception Class</CENTER></B> </TD>
 *     </TR>
 *     <TR> 
 *         <TD> Instruction fetch breakpoint </TD>
 *         <TD> Fault </TD>
 *     </TR>
 *     <TR> 
 *         <TD> Data read or write breakpoint </TD>
 *         <TD> Trap </TD>
 *     </TR>
 *     <TR> 
 *         <TD> I/O read or write breakpoint </TD>
 *         <TD> Trap </TD>
 *     </TR>
 *     <TR> 
 *         <TD> General detect condition (in conjunction with in-circuit 
 *              emulation) </TD>
 *         <TD> Fault </TD>
 *     </TR>
 *     <TR> 
 *         <TD> Single-step </TD>
 *         <TD> Trap </TD>
 *     </TR>
 *     <TR>
 *         <TD> Task-switch </TD>
 *         <TD> Trap </TD>
 *     </TR>
 *     <TR> 
 *         <TD> Execution of INT 1 instruction </TD>
 *         <TD> Trap </TD>
 *     </TR>
 * </TABLE>
 * Refer to "Intel Architecture Software Developer’s Manual Volume 3: System
 * Programming" Chapter 15, <I>Debugging and Performance Monitoring</I>, for
 * detailed information about the debug exceptions.
 *
 * @par                 Exception Error Code
 * None. An exception handler can examine the debug registers to determine
 * which condition caused the exception.
 *
 * @par                 Saved Instruction Pointer
 * Fault — Saved contents of CS and EIP registers point to the instruction that
 * generated the exception.<BR>
 * Trap — Saved contents of CS and EIP registers point to the instruction
 * following the instruction that generated the exception.
 *
 * @par                 Program State Change
 * Fault — A program-state change does not accompany the debug exception, because
 * the exception occurs before the faulting instruction is executed. The
 * program can resume normal execution upon returning from the debug exception
 * handler.<BR>
 * Trap — A program-state change does accompany the debug exception, because the
 * instruction or task switch being executed is allowed to complete before the
 * exception is generated. However, the new state of the program is not
 * corrupted and execution of the program can continue reliably.
 */
#define EXCEPTION_DEBUG                         (1)

/**
 * @brief               <H3>Interrupt 2—NMI Interrupt</H3>
 *
 * @par                 Exception Class
 * Not applicable.
 *
 * @par                 Description
 * The nonmaskable interrupt (NMI) is generated externally by asserting the
 * processor’s NMI pin or through an NMI request set by the I/O APIC to the
 * local APIC on the APIC serial bus. This interrupt causes the NMI interrupt
 * handler to be called.
 *
 * @par                 Exception Error Code
 * Not applicable.
 *
 * @par                 Saved Instruction Pointer
 * The processor always takes an NMI interrupt on an instruction boundary. The
 * saved contents of CS and EIP registers point to the next instruction to be
 * executed at the point the interrupt is taken. Refer to Section 5.4., 
 * “Program or Task Restart” for more information about when the processor
 * takes NMI interrupts.
 *
 * @par                 Program State Change
 * The instruction executing when an NMI interrupt is received is completed
 * before the NMI is generated. A program or task can thus be restarted upon
 * returning from an interrupt handler without loss of continuity, provided the
 * interrupt handler saves the state of the processor before handling the
 * interrupt and restores the processor’s state prior to a return.
 */
#define EXCEPTION_NONMASKABLE_INTERRUPT         (2)

/**
 * @brief               <H3>Interrupt 3—Breakpoint Exception (#BP)</H3>
 *
 * @par                 Exception Class
 * Trap.
 *
 * @par                 Description
 * Indicates that a breakpoint instruction (INT 3) was executed, causing a
 * breakpoint trap to be generated. Typically, a debugger sets a breakpoint by
 * replacing the first opcode byte of an instruction with the opcode for the
 * INT 3 instruction. (The INT 3 instruction is one byte long, which makes it
 * easy to replace an opcode in a code segment in RAM with the breakpoint
 * opcode.) The operating system or a debugging tool can use a data segment
 * mapped to the same physical address space as the code segment to place an
 * INT 3 instruction in places where it is desired to call the debugger. With
 * the P6 family, Pentium®, Intel486™, and Intel386™ processors, it is
 * more convenient to set breakpoints with the debug registers. (Refer to
 * Section 15.3.2., “Breakpoint Exception (#BP)—Interrupt Vector 3”, in
 * Chapter 15, <I>Debugging and Performance Monitoring</I>, for information
 * about the breakpoint exception.) If more breakpoints are needed beyond what
 * the debug registers allow, the INT 3 instruction can be used. The breakpoint
 * (#BP) exception can also be generated by executing the INT n instruction
 * with an operand of 3. The action of this instruction (INT 3) is slightly
 * different than that of the INT 3 instruction (refer to “INTn/INTO/INT3—Call
 * to Interrupt Procedure” in Chapter 3 of the Intel Architecture Software
 * Developer’s Manual, Volume 2).
 *
 * @par                 Exception Error Code
 * None.
 *
 * @par                 Saved Instruction Pointer
 * Saved contents of CS and EIP registers point to the instruction following
 * the INT 3 instruction.
 *
 * @par                 Program State Change
 * Even though the EIP points to the instruction following the breakpoint
 * instruction, the state of the program is essentially unchanged because the
 * INT 3 instruction does not affect any register or memory locations. The
 * debugger can thus resume the suspended program by replacing the INT 3
 * instruction that caused the breakpoint with the original opcode and
 * decrementing the saved contents of the EIP register. Upon returning from the
 * debugger, program execution resumes with the replaced instruction.
 */
#define EXCEPTION_BREAKPOINT                    (3)

/**
 * @brief               <H3>Interrupt 4—Overflow Exception (#OF)</H3>
 *
 * @par                 Exception Class
 * Trap.
 *
 * @par                 Description
 * Indicates that an overflow trap occurred when an INTO instruction was
 * executed. The INTO instruction checks the state of the OF flag in the EFLAGS
 * register. If the OF flag is set, an overflow trap is generated. Some
 * arithmetic instructions (such as the ADD and SUB) perform both signed and
 * unsigned arithmetic. These instructions set the OF and CF flags in the
 * EFLAGS register to indicate signed overflow and unsigned overflow,
 * respectively. When performing arithmetic on signed operands, the OF flag can
 * be tested directly or the INTO instruction can be used. The benefit of using
 * the INTO instruction is that if the overflow exception is detected, an
 * exception handler can be called automatically to handle the overflow
 * condition.
 *
 * @par                 Exception Error Code
 * None.
 *
 * @par                 Saved Instruction Pointer
 * The saved contents of CS and EIP registers point to the instruction
 * following the INTO instruction.
 *
 * @par                 Program State Change
 * Even though the EIP points to the instruction following the INTO
 * instruction, the state of the program is essentially unchanged because the
 * INTO instruction does not affect any register or memory locations. The
 * program can thus resume normal execution upon returning from the overflow
 * exception handler.
 */
#define EXCEPTION_OVERFLOW                      (4)

/**
 * @brief               <H3>Interrupt 5—BOUND Range Exceeded Exception (#BR)</H3>
 *
 * @par                 Exception Class
 * Fault.
 *
 * @par                 Description
 * Indicates that a BOUND-range-exceeded fault occurred when a BOUND
 * instruction was executed. The BOUND instruction checks that a signed array
 * index is within the upper and lower bounds of an array located in memory.
 * If the array index is not within the bounds of the array,
 * a BOUND-range-exceeded fault is generated. 
 *
 * @par                 Exception Error Code
 * None.
 *
 * @par                 Saved Instruction Pointer
 * The saved contents of CS and EIP registers point to the BOUND instruction
 * that generated the exception.
 *
 * @par                 Program State Change
 * A program-state change does not accompany the bounds-check fault, because
 * the operands for the BOUND instruction are not modified. Returning from the
 * BOUND-range-exceeded exception handler causes the BOUND instruction to be
 * restarted.
 */
#define EXCEPTION_BOUND_RANGE_EXCEEDED          (5)

/**
 * @brief               <H3>Interrupt 6—Invalid Opcode Exception (#UD)</H3>
 *
 * @par                 Exception Class
 * Fault.
 *
 * @par                 Description
 * Indicates that the processor did one of the following things:
 * <UL>
 *     <LI> 
 *         Attempted to execute a Streaming SIMD Extensions instruction in an
 *         Intel Architecture processor that does not support the Streaming
 *         SIMD Extensions.
 *     </LI>
 *     <LI>
 *         Attempted to execute a Streaming SIMD Extensions instruction when
 *         the OSFXSR bit is not set (0) in CR4. Note this does not include the
 *         following Streaming SIMD Extensions: PAVGB, PAVGW, PEXTRW, PINSRW,
 *         PMAXSW, PMAXUB, PMINSW, PMINUB, PMOVMSKB, PMULHUW, PSADBW, PSHUFW,
 *         MASKMOVQ, MOVNTQ, PREFETCH and SFENCE.
 *     </LI>
 *     <LI>
 *         Attempted to execute a Streaming SIMD Extensions instruction in an
 *         Intel Architecture processor which causes a numeric exception when 
 *         the OSXMMEXCPT bit is not set (0) in CR4.
 *     </LI>
 *     <LI>
 *         Attempted to execute an invalid or reserved opcode, including any 
 *         MMX™ instruction in an Intel Architecture processor that does not
 *         support the MMX™ architecture.
 *     </LI>
 *     <LI>
 *         Attempted to execute an MMX™ instruction or SIMD floating-point
 *         instruction when the EM flag in register CR0 is set. Note this does
 *         not include the following Streaming SIMD Extensions: SFENCE and 
 *         PREFETCH.
 *     </LI>
 *     <LI>
 *         Attempted to execute an instruction with an operand type that is
 *         invalid for its accompanying opcode; for example, the source operand
 *         for a LES instruction is not a memory location.
 *     </LI>
 *     <LI>
 *         Executed a UD2 instruction.
 *     </LI>
 *     <LI>
 *         Detected a LOCK prefix that precedes an instruction that may not be 
 *         locked or one that may be locked but the destination operand is not 
 *         a memory location.
 *     </LI>
 *     <LI>
 *         Attempted to execute an LLDT, SLDT, LTR, STR, LSL, LAR, VERR, VERW,
 *         or ARPL instruction while in real-address or virtual-8086 mode.
 *     </LI>
 *     <LI>
 *         Attempted to execute the RSM instruction when not in SMM mode.
 *     </LI>
 * </UL>
 * In the P6 family processors, this exception is not generated until an
 * attempt is made to retire the result of executing an invalid instruction;
 * that is, decoding and speculatively attempting to execute an invalid opcode
 * does not generate this exception. Likewise, in the Pentium® processor and
 * earlier Intel Architecture processors, this exception is not generated as
 * the result of prefetching and preliminary decoding of an invalid
 * instruction. (Refer to Section 5.4., “Program or Task Restart” for general
 * rules for taking of interrupts and exceptions.)<BR>
 * The opcodes D6 and F1 are undefined opcodes that are reserved by Intel.
 * These opcodes, even though undefined, do not generate an invalid opcode
 * exception.<BR>
 * The UD2 instruction is guaranteed to generate an invalid opcode
 * exception.
 *
 * @par                 Exception Error Code
 * None.
 * @par                 Saved Instruction Pointer
 * The saved contents of CS and EIP registers point to the instruction that
 * generated the exception.
 *
 * @par                 Program State Change
 * A program-state change does not accompany an invalid-opcode fault, because
 * the invalid instruction is not executed.
 */
#define EXCEPTION_INVALID_OPCODE                (6)

/**
 * @brief               <H3>Interrupt 7—Device Not Available Exception (#NM)</H3>
 *
 * @par                 Exception Class
 * Fault.
 *
 * @par                 Description
 * Indicates one of the following things:
 * The device-not-available fault is generated by either of three conditions:
 * <UL>
 *     <LI>
 *         The processor executed a floating-point instruction while the EM 
 *         flag of register CR0 was set.
 *     </LI>
 *     <LI>
 *         The processor executed a floating-point, MMX™ or SIMD floating-point
 *         (excluding prefetch, sfence or streaming store instructions)
 *         instruction while the TS flag of register CR0 was set.
 *     </LI>
 *     <LI>
 *         The processor executed a WAIT or FWAIT instruction while the MP and
 *         TS flags of register CR0 were set.
 *     </LI>
 * </UL>
 * The EM flag is set when the processor does not have an internal
 * floating-point unit. An exception is then generated each time a
 * floating-point instruction is encountered, allowing an exception handler to
 * call floating-point instruction emulation routines.<BR>
 * The TS flag indicates that a context switch (task switch) has occurred since
 * the last time a floating-point, MMX™ or SIMD floating-point (excluding
 * prefetch, sfence or streaming store instructions) instruction was executed,
 * but that the context of the FPU was not saved. When the TS flag is set, the
 * processor generates a device-not-available exception each time a
 * floating-point, MMX™ or SIMD floating-point (excluding prefetch, sfence or
 * streaming store instructions) instruction is encountered. The exception
 * handler can then save the context of the FPU before it executes the
 * instruction. Refer to Section 2.5., “Control Registers”, in Chapter 2,
 * System Architecture Overview, for more information about the TS flag.<BR>
 * The MP flag in control register CR0 is used along with the TS flag to
 * determine if WAIT or FWAIT instructions should generate a
 * device-not-available exception. It extends the function of the TS flag to
 * the WAIT and FWAIT instructions, giving the exception handler an opportunity
 * to save the context of the FPU before the WAIT or FWAIT instruction is
 * executed. The MP flag is provided primarily for use with the Intel286 and
 * Intel386™ DX processors. For programs running on the P6 family, Pentium®, or
 * Intel486™ DX processors, or the Intel 487 SX coprocessors, the MP flag
 * should always be set; for programs running on the Intel486™ SX processor,
 * the MP flag should be clear.
 *
 * @par                 Exception Error Code
 * None.
 *
 * @par                 Saved Instruction Pointer
 * The saved contents of CS and EIP registers point to the floating-point
 * instruction or the WAIT/FWAIT instruction that generated the exception.
 *
 * @par                 Program State Change
 * A program-state change does not accompany a device-not-available fault,
 * because the instruction that generated the exception is not executed.<BR>
 * If the EM flag is set, the exception handler can then read the
 * floating-point instruction pointed to by the EIP and call the appropriate
 * emulation routine.<BR>
 * If the MP and TS flags are set or the TS flag alone is set, the exception
 * handler can save the context of the FPU, clear the TS flag, and continue
 * execution at the interrupted floating-point or WAIT/FWAIT instruction.
 */
#define EXCEPTION_DEVICE_NOT_AVAILABLE          (7)

/**
 * @brief               <H3>Interrupt 8—Double Fault Exception (#DF)</H3>
 *
 * @par                 Exception Class 
 * Abort.
 *
 * @par                 Description
 * Indicates that the processor detected a second exception while calling an
 * exception handler for a prior exception. Normally, when the processor
 * detects another exception while trying to call an exception handler, the two
 * exceptions can be handled serially. If, however, the processor cannot handle
 * them serially, it signals the double-fault exception. To determine when two
 * faults need to be signaled as a double fault, the processor divides the
 * exceptions into three classes: benign exceptions, contributory exceptions,
 * and page faults (refer to Table 5-4).
 * <TABLE>
 *     <CAPTION>
 *         Table 5-4. Interrupt and Exception Classes
 *     </CAPTION>
 *     <TR>
 *         <TD> <B><CENTER>Class</CENTER></B> </TD>
 *         <TD> <B><CENTER>Vector Number</CENTER></B> </TD>
 *         <TD> <B><CENTER>Description</CENTER></B> </TD>
 *     </TR>
 *     <TR>
 *         <TD> Benign Exceptions and Interrupts </TD>
 *         <TD>
 *             1<BR>
 *             2<BR>
 *             3<BR>
 *             4<BR>
 *             5<BR>
 *             6<BR>
 *             7<BR>
 *             9<BR>
 *             16<BR>
 *             17<BR>
 *             18<BR>
 *             19<BR>
 *             All<BR>
 *             All<BR>
 *         </TD>
 *         <TD>
 *             Debug Exception<BR>
 *             NMI Interrupt<BR>
 *             Breakpoint<BR>
 *             Overflow<BR>
 *             BOUND Range Exceeded<BR>
 *             Invalid Opcode<BR>
 *             Device Not Available<BR>
 *             Coprocessor Segment Overrun<BR>
 *             Floating-Point Error<BR>
 *             Alignment Check<BR>
 *             Machine Check<BR>
 *             SIMD floating-point extensions<BR>
 *             INT <I>n</I><BR>
 *             INTR<BR>
 *         </TD>
 *     </TR>
 *     <TR>
 *         <TD> Contributory Exceptions </TD>
 *         <TD>
 *             0<BR>
 *             10<BR>
 *             11<BR>
 *             12<BR>
 *             13<BR>
 *         </TD>
 *         <TD>
 *             Divide Error<BR>
 *             Invalid TSS<BR>
 *             Segment Not Present<BR>
 *             Stack Fault<BR>
 *             General Protection<BR>
 *         </TD>
 *     </TR>
 *     <TR>
 *         <TD> Page Faults </TD>
 *         <TD> 14 </TD>
 *         <TD> Page Fault </TD>
 *     </TR>
 * </TABLE>
 * Table 5-5 shows the various combinations of exception classes that cause a
 * double fault to be generated. A double-fault exception falls in the abort
 * class of exceptions. The program or task cannot be restarted or resumed. The
 * double-fault handler can be used to collect diagnostic information about the
 * state of the machine and/or, when possible, to shut the application and/or
 * system down gracefully or restart the system.<BR>
 * A segment or page fault may be encountered while prefetching instructions;
 * however, this behavior is outside the domain of Table 5-5. Any further
 * faults generated while the processor is attempting to transfer control to
 * the appropriate fault handler could still lead to a double-fault sequence.
 * <TABLE>
 *     <CAPTION>
 *         Table 5-5. Conditions for Generating a Double Fault
 *     </CAPTION>
 *     <TR>
 *         <TD> <B><CENTER>First Exception</CENTER></B> </TD>
 *         <TD> <B><CENTER>Second Exception</CENTER></B> </TD>
 *     </TR>
 *     <TR>
 *         <TD>
 *             <TABLE>
 *                 <TR><TD> <B>Classes</B> </TD></TR>
 *                 <TR><TD> <B>Benign</B> </TD></TR>
 *                 <TR><TD> <B>Contributory</B> </TD></TR>
 *                 <TR><TD> <B>Page Fault</B> </TD></TR>
 *             </TABLE>
 *         <TD>
 *              <TABLE>
 *                 <TR> 
 *                     <TD> <B><CENTER>Benign</CENTER></B> </TD>
 *                     <TD> <B><CENTER>Contributory</CENTER></B> </TD>
 *                     <TD> <B><CENTER>Page Fault</CENTER></B> </TD>
 *                 </TR>
 *                 <TR>
 *                     <TD> Handle Exceptions Serially </TD>
 *                     <TD> Handle Exceptions Serially </TD>
 *                     <TD> Handle Exceptions Serially </TD>
 *                 </TR>
 *                 <TR>
 *                     <TD> Handle Exceptions Serially </TD>
 *                     <TD> Generate a Double Fault </TD>
 *                     <TD> Handle Exceptions Serially </TD>
 *                     </TR>
 *                 <TR>
 *                     <TD> Handle Exceptions Serially </TD>
 *                     <TD> Generate a Double Fault </TD> 
 *                     <TD> Generate a Double Fault </TD>
 *                 </TR>
 *             </TABLE>
 *         </TD>
 *         </TD>
 *     </TR>
 * </TABLE>
 * If another exception occurs while attempting to call the double-fault
 * handler, the processor enters shutdown mode. This mode is similar to the
 * state following execution of an HLT instruction. In this mode, the processor
 * stops executing instructions until an NMI interrupt, SMI interrupt, hardware
 * reset, or INIT# is received. The processor generates a special bus cycle to
 * indicate that it has entered shutdown mode. Software designers may need to
 * be aware of the response of hardware to receiving this signal. For example,
 * hardware may turn on an indicator light on the front panel, generate an NMI
 * interrupt to record diagnostic information, invoke reset initialization,
 * generate an INIT initialization, or generate an SMI.<BR>
 * If the shutdown occurs while the processor is executing an NMI interrupt
 * handler, then only a hardware reset can restart the processor.
 *
 * @par                 Exception Error Code
 * Zero. The processor always pushes an error code of 0 onto the stack of the
 * double-fault handler.
 *
 * @par                 Saved Instruction Pointer
 * The saved contents of CS and EIP registers are undefined.
 *
 * @par                 Program State Change
 * A program-state following a double-fault exception is undefined. The program
 * or task cannot be resumed or restarted. The only available action of the
 * double-fault exception handler is to collect all possible context
 * information for use in diagnostics and then close the application and/or
 * shut down or reset the processor.
 */
#define EXCEPTION_DOUBLE_FAULT                  (8)

/**
 * @brief               <H3>Interrupt 9—Coprocessor Segment Overrun</H3>
 * @attention           (Intel reserved; do not use. Recent Intel Architecture
 *                      processors do not generate this exception.)
 * 
 * @par                 Exception Class 
 * Abort. 
 *
 * @par                 Description
 * Indicates that an Intel386™ CPU-based systems with an Intel 387 math
 * coprocessor detected a page or segment violation while transferring the
 * middle portion of an Intel 387 math coprocessor operand. The P6 family,
 * Pentium®, and Intel486™ processors do not generate this exception; instead,
 * this condition is detected with a general protection exception (#GP),
 * interrupt 13.
 *
 * @par                 Exception Error Code
 * None.
 *
 * @par                 Saved Instruction Pointer
 * The saved contents of CS and EIP registers point to the instruction that
 * generated the exception.
 *
 * @par                 Program State Change
 * A program-state following a coprocessor segment-overrun exception is
 * undefined. The program or task cannot be resumed or restarted. The only
 * available action of the exception handler is to save the instruction pointer
 * and reinitialize the FPU using the FNINIT instruction.
 */
#define EXCEPTION_COPROCESSOR_SEGMENT_OVERRUN   (9)

/**
 * @brief               <H3>Interrupt 10—Invalid TSS Exception (#TS)</H3>
 *
 * @par                 Exception Class
 * Fault.
 *
 * @par                 Description
 * Indicates that a task switch was attempted and that invalid information was
 * detected in the TSS for the target task. Table 5-6 shows the conditions that
 * will cause an invalid-TSS exception to be generated. In general, these
 * invalid conditions result from protection violations for the TSS descriptor;
 * the LDT pointed to by the TSS; or the stack, code, or data segments
 * referenced by the TSS.
 * <TABLE>
 *     <CAPTION>
 *         Table 5-6. Invalid TSS Conditions
 *     </CAPTION>
 *     <TR>
 *         <TD> <B><CENTER>Error Code Index</CENTER></B> </TD>
 *         <TD> <B><CENTER>Invalid Condition</CENTER></B> </TD>
 *     </TR>
 *     <TR>
 *         <TD> TSS segment selector index </TD>
 *         <TD> TSS segment limit less than 67H for 32-bit TSS or less than 2CH
 *              for 16-bit TSS.</TD>
 *     </TR>
 *     <TR>
 *         <TD> LDT segment selector index </TD>
 *         <TD> Invalid LDT or LDT not present </TD>
 *     </TR>
 *     <TR>
 *         <TD> Stack-segment selector index </TD>
 *         <TD> Stack-segment selector exceeds descriptor table limit </TD>
 *     </TR>
 *     <TR>
 *         <TD> Stack-segment selector index </TD>
 *         <TD> Stack segment is not writable </TD>
 *     </TR>
 *     <TR>
 *         <TD> Stack-segment selector index </TD>
 *         <TD> Stack segment DPL <> CPL <TD>
 *     </TR>
 *     <TR>
 *         <TD> Stack-segment selector index </TD>
 *         <TD> Stack-segment selector RPL <> CPL </TD>
 *     </TR>
 *     <TR>
 *         <TD> Code-segment selector index </TD>
 *         <TD> Code-segment selector exceeds descriptor table limit </TD>
 *     </TR>
 *     <TR>
 *         <TD> Code-segment selector index </TD>
 *         <TD> Code segment is not executable </TD>
 *     </TR>
 *     <TR>
 *         <TD> Code-segment selector index </TD>
 *         <TD> Nonconforming code segment DPL <> CPL </TD>
 *     </TR>
 *     <TR>
 *         <TD> Code-segment selector index </TD>
 *         <TD> Conforming code segment DPL greater than CPL </TD>
 *     </TR>
 *     <TR>
 *         <TD> Data-segment selector index </TD>
 *         <TD> Data-segment selector exceeds descriptor table limit </TD>
 *     </TR>
 *     <TR>
 *         <TD> Data-segment selector index </TD>
 *         <TD> Data segment not readable </TD>
 *     </TR>
 * </TABLE>
 * This exception can generated either in the context of the original task or
 * in the context of the new task (refer to Section 6.3., “Task Switching” in
 * Chapter 6, Task Management). Until the processor has completely verified the
 * presence of the new TSS, the exception is generated in the context of the
 * original task. Once the existence of the new TSS is verified, the task
 * switch is considered complete. Any invalid-TSS conditions detected after
 * this point are handled in the context of the new task. (A task switch is
 * considered complete when the task register is loaded with the segment
 * selector for the new TSS and, if the switch is due to a procedure call or
 * interrupt, the previous task link field of the new TSS references the old
 * TSS.)<BR>
 * To insure that a valid TSS is available to process the exception, the
 * invalid-TSS exception handler must be a task called using a task gate.
 *
 * @par                 Exception Error Code
 * An error code containing the segment selector index for the segment
 * descriptor that caused the violation is pushed onto the stack of the
 * exception handler. If the EXT flag is set, it indicates that the exception
 * was caused by an event external to the currently running program (for
 * example, if an external interrupt handler using a task gate attempted a task
 * switch to an invalid TSS).
 *
 * @par                 Saved Instruction Pointer
 * If the exception condition was detected before the task switch was carried
 * out, the saved contents of CS and EIP registers point to the instruction
 * that invoked the task switch. If the exception condition was detected after
 * the task switch was carried out, the saved contents of CS and EIP registers
 * point to the first instruction of the new task.
 *
 * @par                 Program State Change
 * The ability of the invalid-TSS handler to recover from the fault depends on
 * the error condition than causes the fault. Refer to Section 6.3., “Task
 * Switching” in Chapter 6, Task Management for more information on the task
 * switch process and the possible recovery actions that can be taken.<BR>
 * If an invalid TSS exception occurs during a task switch, it can occur before
 * or after the commit-to-new-task point. If it occurs before the commit point,
 * no program state change occurs. If it occurs after the commit point (when
 * the segment descriptor information for the new segment selectors have been
 * loaded in the segment registers), the processor will load all the state
 * information from the new TSS before it generates the exception. During a
 * task switch, the processor first loads all the segment registers with
 * segment selectors from the TSS, then checks their contents for validity. If
 * an invalid TSS exception is discovered, the remaining segment registers are
 * loaded but not checked for validity and therefore may not be usable for
 * referencing memory. The invalid TSS handler should not rely on being able to
 * use the segment selectors found in the CS, SS, DS, ES, FS, and GS registers
 * without causing another exception. The exception handler should load all
 * segment registers before trying to resume the new task; otherwise,
 * general-protection exceptions (#GP) may result later under conditions that
 * make diagnosis more difficult. The Intel recommended way of dealing
 * situation is to use a task for the invalid TSS exception handler. The task
 * switch back to the interrupted task from the invalid-TSS exceptionhandler
 * task will then cause the processor to check the registers as it loads them
 * from the TSS.
 */
#define EXCEPTION_INVALID_TSS                   (10)

/**
 * @brief               <H3>Interrupt 11—Segment Not Present (#NP)</H3>
 *
 * @par                 Exception Class
 * Fault.
 *
 * @par                 Description
 *  Indicates that the present flag of a segment or gate descriptor is clear.
 * The processor can generate this exception during any of the following
 * operations:
 * <UL>
 *     <LI>
 *         While attempting to load CS, DS, ES, FS, or GS registers. [Detection
 *         of a not-present segment while loading the SS register causes a
 *         stack fault exception (#SS) to be generated.] This situation can
 *         occur while performing a task switch.
 *     </LI>
 *     <LI>
 *         While attempting to load the LDTR using an LLDT instruction.
 *         Detection of a not-present LDT while loading the LDTR during a task
 *         switch operation causes an invalid-TSS exception (#TS) to be
 *         generated.
 *     </LI>
 *     <LI>
 *         When executing the LTR instruction and the TSS is marked not
 *         present. While attempting to use a gate descriptor or TSS that is
 *         marked segment-not-present, but is otherwise valid.
 *     </LI>
 * </UL>
 * An operating system typically uses the segment-not-present exception to
 * implement virtual memory at the segment level. If the exception handler
 * loads the segment and returns, the interrupted program or task resumes
 * execution.<BR>
 * A not-present indication in a gate descriptor, however, does not indicate
 * that a segment is not present (because gates do not correspond to segments).
 * The operating system may use the present flag for gate descriptors to
 * trigger exceptions of special significance to the operating system.
 *
 * @par                 Exception Error Code
 * An error code containing the segment selector index for the segment
 * descriptor that caused the violation is pushed onto the stack of the
 * exception handler. If the EXT flag is set, it indicates that the exception
 * resulted from an external event (NMI or INTR) that caused an interrupt,
 * which subsequently referenced a not-present segment. The IDT flag is set if
 * the error code refers to an IDT entry (e.g., an INT instruction referencing
 * a not-present gate).
 *
 * @par                 Saved Instruction Pointer
 * The saved contents of CS and EIP registers normally point to the instruction
 * that generated the exception. If the exception occurred while loading
 * segment descriptors for the segment selectors in a new TSS, the CS and EIP
 * registers point to the first instruction in the new task. If the exception
 * occurred while accessing a gate descriptor, the CS and EIP registers point
 * to the instruction that invoked the access (for example a CALL instruction
 * that references a call gate).
 *
 * @par                 Program State Change
 * If the segment-not-present exception occurs as the result of loading a
 * register (CS, DS, SS, ES, FS, GS, or LDTR), a program-state change does
 * accompany the exception, because the register is not loaded. Recovery from
 * this exception is possible by simply loading the missing segment into memory
 * and setting the present flag in the segment descriptor.<BR> 
 * If the segment-not-present exception occurs while accessing a gate
 * descriptor, a program-state change does not accompany the exception.
 * Recovery from this exception is possible merely by setting the present flag
 * in the gate descriptor.<BR>
 * If a segment-not-present exception occurs during a task switch, it can occur
 * before or after the commit-to-new-task point (refer to Section 6.3., “Task
 * Switching” in Chapter 6, Task Management). If it occurs before the commit
 * point, no program state change occurs. If it occurs after the commit point,
 * the processor will load all the state information from the new TSS (without
 * performing any additional limit, present, or type checks) before it
 * generates the exception. The segment-not-present exception handler should
 * thus not rely on being able to use the segment selectors found in the CS,
 * SS, DS, ES, FS, and GS registers without causing another exception. (Refer
 * to the Program State Change description for “Interrupt 10—Invalid TSS
 * Exception (#TS)” in this chapter for additional information on how to handle
 * this situation.)
 */
#define EXCEPTION_SEGMENT_NOT_PRESENT           (11)

/**
 * @brief               <H3>Interrupt 12—Stack Fault Exception (#SS)</H3>
 *
 * @par                 Exception Class
 * Fault.
 *
 * @par                 Description
 * Indicates that one of the following stack related conditions was detected:
 * <UL>
 *     <LI>
 *         A limit violation is detected during an operation that refers to the
 *         SS register. Operations that can cause a limit violation include
 *         stack-oriented instructions such as POP, PUSH, CALL, RET, IRET,
 *         ENTER, and LEAVE, as well as other memory references which
 *         implicitly or explicitly use the SS register (for example, MOV AX,
 *         [BP+6] or MOV AX, SS:[EAX+6]). The ENTER instruction generates this
 *         exception when there is not enough stack space for allocating local
 *         variables.
 *     </LI>
 *     <LI>
 *         A not-present stack segment is detected when attempting to load the
 *         SS register. This violation can occur during the execution of a task
 *         switch, a CALL instruction to a different privilege level, a return
 *         to a different privilege level, an LSS instruction, or a MOV or POP
 *         instruction to the SS register.
 *     </LI>
 * </UL>
 * Recovery from this fault is possible by either extending the limit of the
 * stack segment (in the case of a limit violation) or loading the missing
 * stack segment into memory (in the case of a not-present violation.
 *
 * @par                 Exception Error Code
 * If the exception is caused by a not-present stack segment or by overflow of
 * the new stack during an inter-privilege-level call, the error code contains
 * a segment selector for the segment that caused the exception. Here, the
 * exception handler can test the present flag in the segment descriptor
 * pointed to by the segment selector to determine the cause of the exception.
 * For a normal limit violation (on a stack segment already in use) the error
 * code is set to 0.
 *
 * @par                 Saved Instruction Pointer
 * The saved contents of CS and EIP registers generally point to the
 * instruction that generated the exception. However, when the exception
 * results from attempting to load a not-present stack segment during a task
 * switch, the CS and EIP registers point to the first instruction of the new
 * task.
 *
 * @par                 Program State Change
 * A program-state change does not generally accompany a stack-fault exception,
 * because the instruction that generated the fault is not executed. Here, the
 * instruction can be restarted after the exception handler has corrected the
 * stack fault condition.<BR> 
 * If a stack fault occurs during a task switch, it occurs after the
 * commit-to-new-task point (refer to Section 6.3., “Task Switching” Chapter 6,
 * Task Management). Here, the processor loads all the state information from
 * the new TSS (without performing any additional limit, present, or type
 * checks) before it generates the exception. The stack fault handler should
 * thus not rely on being able to use the segment selectors found in the CS,
 * SS, DS, ES, FS, and GS registers without causing another exception. The
 * exception handler should check all segment registers before trying to resume
 * the new task; otherwise, general protection faults may result later under
 * conditions that are more difficult to diagnose. (Refer to the Program State
 * Change description for “Interrupt 10—Invalid TSS Exception (#TS)” for 
 * additional information on how to handle this situation.)
 */
#define EXCEPTION_STACK_FAULT                   (12)

/**
 * @brief               <H3>Interrupt 13—General Protection Exception (#GP)</H3>
 *
 * @par                 Exception Class
 * Fault.
 *
 * @par                 Description
 * Indicates that the processor detected one of a class of protection
 * violations called “general-protection violations.” The conditions that cause
 * this exception to be generated comprise all the protection violations that
 * do not cause other exceptions to be generated (such as, invalid-TSS,
 * segment-not-present, stack-fault, or page-fault exceptions). The following
 * conditions cause general-protection exceptions to be generated:
 * <UL>
 *     <LI>
 *         Exceeding the segment limit when accessing the CS, DS, ES, FS, or GS
 *         segments.
 *     </LI>
 *     <LI>
 *         Exceeding the segment limit when referencing a descriptor table
 *         (except during a task switch or a stack switch).
 *     </LI>
 *     <LI>
 *         Transferring execution to a segment that is not executable.
 *     </LI>
 *     <LI>
 *         Writing to a code segment or a read-only data segment.
 *     </LI>
 *     <LI>
 *         Reading from an execute-only code segment.
 *     </LI>
 *     <LI>
 *         Loading the SS register with a segment selector for a read-only
 *         segment (unless the selector comes from a TSS during a task switch,
 *         in which case an invalid-TSS exception occurs).
 *     </LI>
 *     <LI>
 *         Loading the SS, DS, ES, FS, or GS register with a segment selector
 *         for a system segment.
 *     </LI>
 *     <LI>
 *         Loading the DS, ES, FS, or GS register with a segment selector for
 *         an execute-only code segment.
 *     </LI>
 *     <LI>
 *         Loading the SS register with the segment selector of an executable
 *         segment or a null segment selector.
 *     </LI>
 *     <LI>
 *         Loading the CS register with a segment selector for a data segment
 *         or a null segment selector.
 *     </LI>
 *     <LI>
 *         Accessing memory using the DS, ES, FS, or GS register when
 *         it contains a null segment selector.
 *     </LI>
 *     <LI>
 *         Switching to a busy task during a call or jump to a TSS.
 *     </LI>
 *     <LI>
 *         Switching to an available (nonbusy) task during the execution of an
 *         IRET instruction.
 *     </LI>
 *     <LI>
 *         Using a segment selector on task switch that points to a TSS
 *         descriptor in the current LDT. TSS descriptors can only reside in
 *         the GDT.
 *     </LI>
 *     <LI>
 *         Violating any of the privilege rules described in Chapter 4,
 *         Protection.
 *     </LI>
 *     <LI>
 *         Exceeding the instruction length limit of 15 bytes (this only can
 *         occur when redundant refixes are placed before an instruction).
 *     </LI>
 *     <LI>
 *         Loading the CR0 register with a set PG flag (paging enabled) and a
 *         clear PE flag (protection disabled).
 *     </LI>
 *     <LI>
 *         Loading the CR0 register with a set NW flag and a clear CD flag.
 *     </LI>
 *     <LI>
 *         Referencing an entry in the IDT (following an interrupt or
 *         exception) that is not an interrupt, trap, or task gate.
 *     </LI>
 *     <LI>
 *         Attempting to access an interrupt or exception handler through an
 *         interrupt or trap gate from virtual-8086 mode when the handler’s
 *         code segment DPL is greater than 0.
 *     </LI>
 *     <LI>
 *         Attempting to write a 1 into a reserved bit of CR4.
 *     </LI>
 *     <LI>
 *         Attempting to execute a privileged instruction when the CPL is not
 *         equal to 0 (refer to Section 4.9., “Privileged Instructions” in
 *         Chapter 4, Protection for a list of privileged instructions).
 *     </LI>
 *     <LI>
 *         Writing to a reserved bit in an MSR.
 *     </LI>
 *     <LI>
 *         Accessing a gate that contains a null segment selector.
 *     </LI>
 *     <LI>
 *         Executing the INT n instruction when the CPL is greater than the DPL
 *         of the referenced interrupt, trap, or task gate.
 *     </LI>
 *     <LI>
 *         The segment selector in a call, interrupt, or trap gate does not
 *         point to a code segment.
 *     </LI>
 *     <LI>
 *         The segment selector operand in the LLDT instruction is a local type
 *         (TI flag is set) or does not point to a segment descriptor of the
 *         LDT type.
 *     </LI>
 *     <LI>
 *         The segment selector operand in the LTR instruction is local or
 *         points to a TSS that is not available.
 *     </LI>
 *     <LI>
 *         The target code-segment selector for a call, jump, or return is 
 *         null.
 *     </LI>
 *     <LI>
 *         If the PAE and/or PSE flag in control register CR4 is set and the
 *         processor detects any reserved bits in a
 *         page-directory-pointer-table entry set to 1. These bits are checked
 *         during a write to control registers CR0, CR3, or CR4 that causes a
 *         reloading of the page-directory-pointer-table entry.
 *     </LI>
 * </UL>
 * A program or task can be restarted following any general-protection
 * exception. If the exception occurs while attempting to call an interrupt
 * handler, the interrupted program can be restartable, but the interrupt may
 * be lost.
 *
 * @par                 Exception Error Code
 * The processor pushes an error code onto the exception handler’s stack. If
 * the fault condition was detected while loading a segment descriptor, the
 * error code contains a segment selector to or IDT vector number for the
 * descriptor; otherwise, the error code is 0. The source of the selector in an
 * error code may be any of the following:
 * <UL>
 *     <LI> An operand of the instruction. </LI>
 *     <LI> A selector from a gate which is the operand of the instruction. 
 *     </LI>
 *     <LI> A selector from a TSS involved in a task switch. </LI>
 *     <LI> IDT vector number. </LI>
 * </UL>
 *
 * @par Saved           Instruction Pointer
 * The saved contents of CS and EIP registers point to the instruction that
 * generated the exception.
 *
 * @par                 Program State Change
 * In general, a program-state change does not accompany a general-protection
 * exception, because the invalid instruction or operation is not executed. An
 * exception handler can be designed to correct all of the conditions that
 * cause general-protection exceptions and restart the program or task without
 * any loss of program continuity.<BR>
 * If a general-protection exception occurs during a task switch, it can occur
 * before or after the commit-to-new-task point (refer to Section 6.3., “Task
 * Switching” in Chapter 6, Task Management). If it occurs before the commit
 * point, no program state change occurs. If it occurs after the commit point,
 * the processor will load all the state information from the new TSS (without
 * performing any additional limit, present, or type checks) before it
 * generates the exception. The general-protection exception handler should
 * thus not rely on being able to use the segment selectors found in the CS,
 * SS, DS, ES, FS, and GS registers without causing another exception. (Refer
 * to the Program State Change description for “Interrupt 10—Invalid TSS
 * Exception (#TS)” in this chapter for additional information on how to handle
 * this situation.)
 */
#define EXCEPTION_GENERAL_PROTECTION            (13)

/**
 * @brief               <H3>Interrupt 14—Page-Fault Exception (#PF)</H3>
 *
 * @par                 Exception Class
 * Fault.
 *
 * @par                 Description
 * Indicates that, with paging enabled (the PG flag in the CR0 register is
 * set), the processor detected one of the following conditions while using the
 * page-translation mechanism to translate a linear address to a physical
 * address:
 * <UL>
 *     <LI>
 *         The P (present) flag in a page-directory or page-table entry needed for the address
 *         translation is clear, indicating that a page table or the page containing the operand is not
 *         present in physical memory.
 *     </LI>
 *     <LI>
 *         The procedure does not have sufficient privilege to access the indicated page (that is, a
 *         procedure running in user mode attempts to access a supervisor-mode page).
 *     </LI>
 *     <LI>
 *         Code running in user mode attempts to write to a read-only page. In the Intel486™ and
 *         later processors, if the WP flag is set in CR0, the page fault will also be triggered by code
 *         running in supervisor mode that tries to write to a read-only user-mode page.
 *     </LI>
 * </UL>
 * The exception handler can recover from page-not-present conditions and
 * restart the program or task without any loss of program continuity. It can
 * also restart the program or task after a privilege violation, but the
 * problem that caused the privilege violation may be uncorrectable.
 *
 * @par                 Exception Error Code
 * Yes (special format). The processor provides the page-fault handler with two
 * items of information to aid in diagnosing the exception and recovering from
 * it:
 * <UL>
 *     <LI>
 *         An error code on the stack. The error code for a page fault has a
 *         format different from that for other exceptions (refer to Figure
 *         5-7).
 *     </LI>
 *     <LI>
 *         The contents of the CR2 register. The processor loads the CR2
 *         register with the 32-bit linear address that generated the
 *         exception. The page-fault handler can use this address to locate
 *         the corresponding page directory and page-table entries. If another
 *         page fault can potentially occur during execution of the page-fault
 *         handler, the handler must push the contents of the CR2 register onto
 *         the stack before the second page fault occurs.
 *     </LI>
 * </UL>
 * If a page fault is caused by a page-level protection violation, the access
 * flag in the page-directory entry is set when the fault occurs. The behavior
 * of Intel Architecture processors regarding the access flag in the
 * corresponding page-table entry is model specific and not architecturally
 * defined.
 *
 * @par                 Saved Instruction Pointer
 * The saved contents of CS and EIP registers generally point to the
 * instruction that generated the exception. If the page-fault exception
 * occurred during a task switch, the CS and EIP registers may point to the
 * first instruction of the new task (as described in the following “Program
 * State Change” section).
 * @par                 Program State Change
 * A program-state change does not normally accompany a page-fault exception,
 * because the instruction that causes the exception to be generated is not
 * executed. After the page-fault exception handler has corrected the violation
 * (for example, loaded the missing page into memory), execution of the program
 * or task can be resumed.<BR>
 * When a page-fault exception is generated during a task switch, the
 * program-state may change, as follows. During a task switch, a page-fault
 * exception can occur during any of following operations:
 * <UL>
 *     <LI>
 *         While writing the state of the original task into the TSS of that
 *         task.
 *     </LI>
 *     <LI>
 *         While reading the GDT to locate the TSS descriptor of the new task.
 *     </LI>
 *     <LI>
 *         While reading the TSS of the new task.
 *     </LI>
 *     <LI>
 *         While reading segment descriptors associated with segment selectors
 *         from the new task.
 *     </LI>
 *     <LI>
 *         While reading the LDT of the new task to verify the segment
 *         registers stored in the new TSS.
 *     </LI>
 * </UL>
 * In the last two cases the exception occurs in the context of the new task.
 * The instruction pointer refers to the first instruction of the new task, not
 * to the instruction which caused the task switch (or the last instruction to
 * be executed, in the case of an interrupt). If the design of the operating
 * system permits page faults to occur during task-switches, the page-fault
 * handler should be called through a task gate.<BR>
 * If a page fault occurs during a task switch, the processor will load all the
 * state information from the new TSS (without performing any additional limit,
 * present, or type checks) before it generates the exception. The page-fault
 * handler should thus not rely on being able to use the segment selectors
 * found in the CS, SS, DS, ES, FS, and GS registers without causing another
 * exception. (Refer to the Program State Change description for “Interrupt
 * 10—Invalid TSS Exception (#TS)” for additional information on how to handle
 * this situation.)
 *
 * @par                 Additional Exception-Handling Information
 * Special care should be taken to ensure that an exception that occurs during
 * an explicit stack switch does not cause the processor to use an invalid
 * stack pointer (SS:ESP). Software written for 16-bit Intel Architecture
 * processors often use a pair of instructions to change to a new stack, for
 * example:
 * @code
 *     MOV SS, AX
 *     MOV SP, StackTop
 * @endcode
 * When executing this code on one of the 32-bit Intel Architecture processors,
 * it is possible to get a page fault, general-protection fault (#GP), or
 * alignment check fault (#AC) after the segment selector has been loaded into
 * the SS register but before the ESP register has been loaded. At this point,
 * the two parts of the stack pointer (SS and ESP) are inconsistent. The new
 * stack segment is being used with the old stack pointer.<BR>
 * The processor does not use the inconsistent stack pointer if the exception
 * handler switches to a well defined stack (that is, the handler is a task or
 * a more privileged procedure). However, if the exception handler is called at
 * the same privilege level and from the same task, the processor will attempt
 * to use the inconsistent stack pointer.<BR>
 * In systems that handle page-fault, general-protection, or alignment check
 * exceptions within the faulting task (with trap or interrupt gates), software
 * executing at the same privilege level as the exception handler should
 * initialize a new stack by using the LSS instruction rather than a pair of
 * MOV instructions, as described earlier in this note. When the exception
 * handler is running at privilege level 0 (the normal case), the problem is
 * limited to procedures or tasks that run at privilege level 0, typically the
 * kernel of the operating system.
 */
#define EXCEPTION_PAGE_FAULT                    (14)

/**
 * @brief               <H3>Interrupt 15—Dummy</H3>
 * @attention           (Intel reserved; do not use. Recent Intel Architecture
 *                      processors do not generate this exception.)
 */
#define EXCEPTION_DUMMY                         (15)

/**
 * @brief               <H3>Interrupt 16—Floating-Point Error Exception (#MF)</H3>
 *
 * @par                 Exception Class
 * Fault.
 *
 * @par                 Description
 * Indicates that the FPU has detected a floating-point-error exception. The NE
 * flag in the register CR0 must be set and the appropriate exception must be
 * unmasked (clear mask bit in the control register) for an interrupt 16,
 * floating-point-error exception to be generated. (Refer to Section 2.5.,
 * “Control Registers” in Chapter 2, System Architecture Overview for a
 * detailed description of the NE flag.)<BR>
 * While executing floating-point instructions, the FPU detects and reports six
 * types of floatingpoint errors:
 * <UL>
 *     <LI>
 *         Invalid operation (#I)
 *         <UL>
 *             <LI> Stack overflow or underflow (#IS) </LI>
 *             <LI> Invalid arithmetic operation (#IA) </LI>
 *         </UL>
 *     </LI>
 *     <LI> Divide-by-zero (#Z) </LI>
 *     <LI> Denormalized operand (#D) </LI>
 *     <LI> Numeric overflow (#O) </LI>
 *     <LI> Numeric underflow (#U) </LI>
 *     <LI> Inexact result (precision) (#P) </LI>
 * </UL>
 * For each of these error types, the FPU provides a flag in the FPU status
 * register and a mask bit in the FPU control register. If the FPU detects a
 * floating-point error and the mask bit for the error is set, the FPU handles
 * the error automatically by generating a predefined (default) response and
 * continuing program execution. The default responses have been designed to
 * provide a reasonable result for most floating-point applications.<BR>
 * If the mask for the error is clear and the NE flag in register CR0 is set,
 * the FPU does the following:
 * <OL>
 *     <LI>
 *         Sets the necessary flag in the FPU status register.
 *     </LI>
 *     <LI>
 *         Waits until the next “waiting” floating-point instruction or
 *         WAIT/FWAIT instruction is encountered in the program’s instruction
 *         stream. (The FPU checks for pending floatingpoint exceptions on
 *         “waiting” instructions prior to executing them. All the
 *         floating-point instructions except the FNINIT, FNCLEX, FNSTSW,
 *         FNSTSW AX, FNSTCW, FNSTENV, and FNSAVE instructions are “waiting”
 *         instructions.)
 *     </LI>
 *     <LI>
 *         Generates an internal error signal that causes the processor to
 *         generate a floating-pointerror exception.
 *     </LI>
 * </OL>
 * All of the floating-point-error conditions can be recovered from. The
 * floating-point-error exception handler can determine the error condition
 * that caused the exception from the settings of the flags in the FPU status
 * word. Refer to “Software Exception Handling” in Chapter 7 of the Intel
 * Architecture Software Developer’s Manual, Volume 1, for more information on
 * handling floating-point-error exceptions.
 *
 * @par                 Exception Error Code
 * None. The FPU provides its own error information.
 *
 * @par                 Saved Instruction Pointer
 * The saved contents of CS and EIP registers point to the floating-point or
 * WAIT/FWAIT instruction that was about to be executed when the
 * floating-point-error exception was generated. This is not the faulting
 * instruction in which the error condition was detected. The address of the
 * faulting instruction is contained in the FPU instruction pointer register.
 * Refer to “The FPU Instruction and Operand (Data) Pointers” in Chapter 7 of
 * the Intel Architecture Software Developer’s Manual, Volume 1, for more
 * information about information the FPU saves for use in handling
 * floating-point-error exceptions.
 *
 * @par                 Program State Change
 * A program-state change generally accompanies a floating-point-error
 * exception because the handling of the exception is delayed until the next
 * waiting floating-point or WAIT/FWAIT instruction following the faulting
 * instruction. The FPU, however, saves sufficient information about the error
 * condition to allow recovery from the error and re-execution of the faulting
 * instruction if needed.<BR>
 * In situations where nonfloating-point instructions depend on the results of
 * a floating-point instruction, a WAIT or FWAIT instruction can be inserted in
 * front of a dependent instruction to force a pending floating-point-error
 * exception to be handled before the dependent instruction is executed. Refer
 * to “Floating-Point Exception Synchronization” in Chapter 7 of the Intel
 * Architecture Software Developer’s Manual, Volume 1, for more information
 * about synchronization of floating-point-error exceptions.
 */
#define EXCEPTION_FLOATING_POINT_ERROR          (16)

/**
 * @brief               <H3>Interrupt 17—Alignment Check Exception (#AC)</H3>
 *
 * @par                 Exception Class
 * Fault.
 *
 * @par                 Description
 * Indicates that the processor detected an unaligned memory operand when
 * alignment checking was enabled. Alignment checks are only carried out in
 * data (or stack) segments (not in code or system segments). An example of an
 * alignment-check violation is a word stored at an odd byte address, or a
 * doubleword stored at an address that is not an integer multiple of 4. Table
 * 5-7 lists the alignment requirements various data types recognized by the
 * processor.
 * <TABLE>
 *     <CAPTION>
 *         Table 5-7. Alignment Requirements by Data Type
 *     </CAPTION>
 *     <TR>
 *         <TD> <B><CENTER>Data Type</CENTER></B> </TD>
 *         <TD> <B><CENTER>Address Must Be Divisible By</CENTER></B> </TD>
 *     </TR>
 *     <TR>
 *         <TD> Word </TD>
 *         <TD> 2 </TD>
 *     </TR>
 *     <TR>
 *         <TD> Doubleword </TD>
 *         <TD> 4 </TD>
 *     </TR>
 *     <TR>
 *         <TD> Single Real </TD>
 *         <TD> 4 </TD>
 *     </TR>
 *     <TR>
 *         <TD> Double Real </TD>
 *         <TD> 8 </TD>
 *     </TR>
 *     <TR>
 *         <TD> Extended Real </TD>
 *         <TD> 8 </TD>
 *     </TR>
 *     <TR>
 *         <TD> Segment Selector </TD>
 *         <TD> 2 </TD>
 *     </TR>
 *     <TR>
 *         <TD> 32-bit Far Pointer </TD>
 *         <TD> 2 </TD>
 *     </TR>
 *     <TR>
 *         <TD> 48-bit Far Pointer </TD>
 *         <TD> 4 </TD>
 *     </TR>
 *     <TR>
 *         <TD> 32-bit Pointer </TD>
 *         <TD> 4 </TD>
 *     </TR>
 *     <TR>
 *         <TD> GDTR, IDTR, LDTR, or Task Register Contents </TD>
 *         <TD> 4 </TD>
 *     </TR>
 *     <TR>
 *         <TD> FSTENV/FLDENV Save Area </TD>
 *         <TD> 4 or 2, depending on operand size </TD>
 *     </TR>
 *     <TR>
 *         <TD> FSAVE/FRSTOR Save Area </TD>
 *         <TD> 4 or 2, depending on operand size </TD>
 *     </TR>
 *     <TR>
 *         <TD> Bit String </TD>
 *         <TD> 2 or 4 depending on the operand-size attribute. </TD>
 *     </TR>
 *     <TR>
 *         <TD> 128-bit<SUP>1</SUP> </TD>
 *         <TD> 16 </TD>
 *     </TR>
 * </TABLE>
 * <SMALL>
 * 1. 128-bit datatype introduced with the Pentium ® III processor. This type
 * of alignment check is done for operands less than 128-bits in size: 32-bit
 * scalar single and 16-bit/32-bit/64-bit integer MMX™ technology; 2, 4, or 8
 * byte alignments checks are possible when #AC is enabled. Some exceptional
 * cases are:
 * <UL>
 *     <LI>
 *         The MOVUPS instruction, which performs a 128-bit unaligned load or
 *         store. In this case, 2/4/8-byte misalignments will be detected, but
 *         detection of 16-byte misalignment is not guaranteed and may vary
 *         with implementation.
 *     </LI>
 *     <LI>
 *         The FXSAVE/FXRSTOR instructions - refer to instruction descriptions
 *     </LI>
 * </UL>
 * </SMALL>
 * To enable alignment checking, the following conditions must be true:
 * <UL>
 *     <LI> AM flag in CR0 register is set. </LI>
 *     <LI> AC flag in the EFLAGS register is set. </LI>
 *     <LI> The CPL is 3 (protected mode or virtual-8086 mode). </LI>
 * </UL>
 * Alignment-check faults are generated only when operating at privilege level
 * 3 (user mode). Memory references that default to privilege level 0, such as
 * segment descriptor loads, do not generate alignment-check faults, even when
 * caused by a memory reference made from privilege level 3.<BR>
 * Storing the contents of the GDTR, IDTR, LDTR, or task register in memory
 * while at privilege level 3 can generate an alignment-check fault. Although
 * application programs do not normally store these registers, the fault can be
 * avoided by aligning the information stored on an even word-address.<BR>
 * FSAVE and FRSTOR instructions generate unaligned references which can cause
 * alignmentcheck faults. These instructions are rarely needed by application
 * programs.
 *
 * @par                 Exception Error Code
 * Yes (always zero).
 *
 * @par                 Saved Instruction Pointer
 * The saved contents of CS and EIP registers point to the instruction that
 * generated the exception.
 *
 * @par                 Program State Change
 * A program-state change does not accompany an alignment-check fault, because
 * the instruction is not executed.
 */
#define EXCEPTION_ALIGNMENT_CHECK               (17)

/**
 * @brief               <H3>Interrupt 18—Machine-Check Exception (#MC)</H3>
 *
 * @par                 Exception Class
 * Abort.
 *
 * @par                 Description
 * Indicates that the processor detected an internal machine error or a bus
 * error, or that an external agent detected a bus error. The machine-check
 * exception is model-specific, available only on the P6 family and Pentium®
 * processors. The implementation of the machine-check exception is different
 * between the P6 family and Pentium® processors, and these implementations may
 * not be compatible with future Intel Architecture processors. (Use the CPUID
 * instruction to determine whether this feature is present.)<BR>
 * Bus errors detected by external agents are signaled to the processor on
 * dedicated pins: the BINIT# pin on the P6 family processors and the BUSCHK#
 * pin on the Pentium® processor. When one of these pins is enabled, asserting
 * the pin causes error information to be loaded into machine-check registers
 * and a machine-check exception is generated.<BR>
 * The machine-check exception and machine-check architecture are discussed in
 * detail in Chapter 13, Machine-Check Architecture. Also, refer to the data
 * books for the individual processors for processor-specific hardware information.
 *
 * @par                 Exception Error Code
 * None. Error information is provide by machine-check MSRs.
 *
 * @par                 Saved Instruction Pointer
 * For the P6 family processors, if the EIPV flag in the MCG_STATUS MSR is set,
 * the saved contents of CS and EIP registers are directly associated with the
 * error that caused the machinecheck exception to be generated; if the flag is
 * clear, the saved instruction pointer may not be associated with the error
 * (refer to Section 13.3.1.2., “MCG_STATUS MSR”, in Chapter 13, Machine-Check
 * Architecture).<BR>
 * For the Pentium® processor, contents of the CS and EIP registers may not be
 * associated with the error.
 *
 * @par                 Program State Change
 * A program-state change always accompanies a machine-check exception. If the
 * machine-check mechanism is enabled (the MCE flag in control register CR4 is
 * set), a machine-check exception results in an abort; that is, information
 * about the exception can be collected from the machinecheck MSRs, but the
 * program cannot be restarted. If the machine-check mechanism is not enabled,
 * a machine-check exception causes the processor to enter the shutdown state.
 */
#define EXCEPTION_MACHINE_CHECK                 (18)

/**
 * @brief               <H3>Interrupt 19—SIMD Floating-Point Exception (#XF)</H3>
 *
 * @par                 Exception Class
 * Fault.
 *
 * @par                 Description
 * Indicates the processor has detected a SIMD floating-point execution unit
 * exception. The appropriate status flag in the MXCSR register must be set and
 * the particular exception unmasked for this interrupt to be generated.<BR>
 * There are six classes of numeric exception conditions that can occur while
 * executing Streaming SIMD Extensions:
 * <OL>
 *     <LI> Invalid operation (#I) </LI>
 *     <LI> Divide-by-zero (#Z) </LI>
 *     <LI> Denormalized operand (#D) </LI>
 *     <LI> Numeric overflow (#O) </LI>
 *     <LI> Numeric underflow (#U) </LI>
 *     <LI> Inexact result (Precision) (#P) </LI>
 * </OL>
 * Invalid, Divide-by-zero, and Denormal exceptions are pre-computation
 * exceptions, i.e., they are detected before any arithmetic operation occurs.
 * Underflow, Overflow, and Precision exceptions are post-computational
 * exceptions.<BR>
 * When numeric exceptions occur, a processor supporting Streaming SIMD
 * Extensions takes one of two possible courses of action:
 * <UL>
 *     <LI>
 *         The processor can handle the exception by itself, producing the most
 *         reasonable result and allowing numeric program execution to continue
 *         undisturbed (i.e., masked exception response).
 *     </LI>
 *     <LI>
 *         A software exception handler can be invoked to handle the exception
 *         (i.e., unmasked exception response).
 *     </LI>
 * </UL>
 * Each of the six exception conditions described above has corresponding flag
 * and mask bits in the MXCSR. If an exception is masked (the corresponding
 * mask bit in MXCSR = 1), the processor takes an appropriate default action
 * and continues with the computation. If the exception is unmasked (mask bit =
 * 0) and the OS supports SIMD floating-point exceptions (i.e. CR4.OSXMMEXCPT =
 * 1), a software exception handler is invoked immediately through SIMD
 * floating-point exception interrupt vector 19. If the exception is unmasked
 * (mask bit = 0) and the OS does not support SIMD floating-point exceptions
 * (i.e. CR4.OSXMMEXCPT = 0), an invalid opcode exception is signaled instead
 * of a SIMD floating-point exception.<BR> 
 * Note that because SIMD floating-point exceptions are precise and occur
 * immediately, the situation does not arise where an x87-FP instruction, an
 * FWAIT instruction, or another Streaming SIMD Extensions instruction will
 * catch a pending unmasked SIMD floating-point exception.
 *
 * @par                 Exception Error Code
 * None. The Streaming SIMD Extensions provide their own error information.
 *
 * @par                 Saved Instruction Pointer
 * The saved contents of CS and EIP registers point to the Streaming SIMD
 * Extensions instruction that was executed when the SIMD floating-point
 * exception was generated. This is the faulting instruction in which the error
 * condition was detected.
 *
 * @par                 Program State Change
 * A program-state change generally accompanies a SIMD floating-point exception
 * because the handling of the exception is immediate unless the particular
 * exception is masked. The Pentium® III processor contains sufficient
 * information about the error condition to allow recovery from the error and
 * re-execution of the faulting instruction if needed.<BR>
 * In situations where a SIMD floating-point exception occurred while the SIMD
 * floating-point exceptions were masked, SIMD floating-point exceptions were
 * then unmasked, and a Streaming SIMD Extensions instruction was executed,
 * then no exception is raised.
 */
#define EXCEPTION_STREAMING_SIMD_EXTENSIONS     (19)

/**
 * @} // end of group_exception_codes
 */

/**
 * }@ // end of group group_exceptions
 */
