/* $Id: trap.c,v 1.1.1.1 2000/09/26 19:08:16 plundis Exp $ */
/* Abstract: Handle CPU exceptions (called 'traps' on motorola.. ;) */
/* Authors: Henrik Hallin <hal@chaosdev.org>,
            Johan Thim <nospam@inter.net>,
            Per Lundberg <plundis@chaosdev.org> */

/* Copyright 1998-2000 chaos development. */

/* This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
   USA. */

/* Define this when debugging this module. */

#define DEBUG TRUE

/* Define this if you want to halt the system whenever an unhandled
   trap occurs. (Sometimes, the system will triple fault otherwise) */

#define HALT_ON_ERROR
//#define GROWING_STACK

#include <storm/state.h>
#include <storm/generic/cpu.h>
#include <storm/generic/debug.h>
#include <storm/generic/defines.h>
#include <storm/generic/dispatch.h>
#include <storm/generic/memory.h>
#include <storm/generic/memory_physical.h>
#include <storm/generic/memory_virtual.h>
#include <storm/generic/process.h>
#include <storm/generic/string.h>
#include <storm/generic/types.h>
#include <storm/ia32/descriptor.h>
#include <storm/ia32/flags.h>
#include <storm/ia32/gdt.h>
#include <storm/ia32/idt.h>
#include <storm/ia32/trap.h>
#include <storm/ia32/tss.h>

static descriptor_type trap_descriptor;
tss_type *trap_tss;
static void *trap_stack;

typedef union
{
  unsigned int error_code;
  page_error_type page_error;
  segment_error_type segment_error;
} ecode_type;

ecode_type ecode;

void trap_divide_error_fault (void);
void trap_debug_trap (void);
void trap_nmi (void);
void trap_breakpoint_trap (void);
void trap_overflow_trap (void);
void trap_bound_range_exceeded_fault (void);
void trap_invalid_opcode_fault (void);
void trap_device_not_available_fault (void);
void trap_double_fault (void);
void trap_coprocessor_segment_overrun_abort (void);
void trap_invalid_tss_fault (void);
void trap_segment_not_present_fault (void);
void trap_stack_fault (void);
void trap_general_protection_fault (void);
void trap_page_fault (void);
void trap_reserved (void);
void trap_floating_point_error_fault (void);
void trap_alignment_check_fault (void);
void trap_machine_check_abort (void);
void trap_streaming_simd_extensions_fault (void);

/* Display a exception screen. */

static void exception_screen (const char *class, 
                       const char *description,
                       const char *reason,
                       char error_code_type, 
                       volatile storm_tss_type *dump_tss)
{
  debug_print ("Kernel:\n");
  debug_print ("  Exception class : %s\n", class);
  debug_print ("    Description: %s\n", description);
  debug_print ("    Possible reason: %s\n", reason);
  if (error_code_type != EXCEPTION_CODE_NONE)
  {
    debug_print ("    Error code: 0x%x\n", ecode);
    if (ecode.error_code != 0)
    {
      switch (error_code_type)
      {
        case EXCEPTION_CODE_PAGE:
	{
          debug_print ("    Page Error: ");

          if (ecode.page_error.RSVD)
	  {
            debug_print ("RSVD,");
	  }

          if (ecode.page_error.U_S)
	  {
            debug_print ("Supervisor,");
	  }
	  else
	  {
            debug_print ("User,");
	  }

          if (ecode.page_error.W_R)
	  {
            debug_print ("Write,");
	  }
	  else
	  {
            debug_print ("Read,");
	  }

          if (ecode.page_error.P)
	  {
            debug_print ("Page Not Present");
	  }
          debug_print ("\n");

	  break;
	}
	case EXCEPTION_CODE_SEGMENT:
	{
          debug_print ("    Segment Error: ");

          debug_print ("Selector Index: %u,", 
	               ecode.segment_error.segment_selector_index);
		       
          if (ecode.segment_error.TI & !ecode.segment_error.IDT)
	  {
            debug_print ("in LDT,");
	  }
	  else if (!ecode.segment_error.TI & !ecode.segment_error.IDT)
	  {
            debug_print ("in GDT,");
	  }
          else if (ecode.segment_error.IDT)
	  {
            debug_print ("in IDT,");
	  }
	  
          if (ecode.segment_error.EXT)
	  {
            debug_print ("External Event,");
	  }
	  else
	  {
            debug_print ("Internal Event,");
	  }
          debug_print ("\n");

	  break;
	}
      }
    }
  }

  debug_print ("Causing process:\n");

  debug_print ("  Process: %s (PROCESS ID %u).\n",
               ((process_info_type *) dump_tss-> process_info)->name,
               dump_tss->process_id);
  debug_print ("  Thread: %s (THREAD ID %u).\n",
               dump_tss->thread_name, dump_tss->thread_id);
  debug_print ("  Process was dispatched %u times.\n", dump_tss->timeslices);
  debug_print ("  Exception occured at address %x:%x\n",
               dump_tss->cs, dump_tss->eip);
  debug_print ("Registers:\n");

  debug_print ("  EAX: 0x%x EBX: 0x%x ECX: 0x%x EDX: 0x%x\n",
               dump_tss->eax, dump_tss->ebx, dump_tss->ecx, dump_tss->edx);
  debug_print ("  ESP: 0x%x EBP: 0x%x ESI: 0x%x EDI: 0x%x\n",
               dump_tss->esp, dump_tss->ebp, dump_tss->esi, dump_tss->edi);
  debug_print ("   DS: 0x%x  ES: 0x%x  FS: 0x%x  GS: 0x%x\n",
               dump_tss->ds, dump_tss->es, dump_tss->fs, dump_tss->gs);
  debug_print ("  CR2: 0x%x CR3: 0x%x              EFLAGS: 0x%x\n",
               cpu_get_cr2 (), dump_tss->cr3, dump_tss->eflags);

  debug_print ("  STACK SS:ESP 0x%x : 0x%x\n",
               dump_tss->ss, dump_tss->esp);
}

/* Now, it's time for some exception handlers. */

void trap_divide_error_fault (void)
{
  exception_screen ("Fault", "Divide Error", 
                    "DIV and IDIV instructions.",
                    EXCEPTION_CODE_NONE, current_tss);
  current_tss->state = STATE_ZOMBIE;
  dispatch_next ();
}

void trap_debug_trap (void)
{
  exception_screen ("Fault/Trap", "Debug",
                    "Any code or data reference or the INT 1 instruction.",
                    EXCEPTION_CODE_NONE, current_tss);
  debug_run ();
}

void trap_nmi (void)
{
  exception_screen ("Interrupt", "NMI Interrupt",
                    "Nonmaskable external interrupt.", 
                    EXCEPTION_CODE_NONE, current_tss);
  DEBUG_HALT ("System halted.");
}

void trap_breakpoint_trap (void)
{
  exception_screen ("Trap", "Breakpoint", 
                    "INT 3 instruction.",
                    EXCEPTION_CODE_NONE, current_tss);
  debug_run ();
}

void trap_overflow_trap (void)
{
  exception_screen ("Trap", "Overflow",
                    "INTO instruction.",
                    EXCEPTION_CODE_NONE, current_tss);
  current_tss->state = STATE_ZOMBIE;
  dispatch_next ();
}

void trap_bound_range_exceeded_fault (void)
{
  /* FIXME: What do we do here? */
  exception_screen ("Fault", "BOUND Range Exceeded",
                    "BOUND instruction.", 
                    EXCEPTION_CODE_NONE, current_tss);
  current_tss->state = STATE_ZOMBIE;
  dispatch_next ();
}

void trap_invalid_opcode_fault (void)
{
  exception_screen ("Fault", "Invalid Opcode (Undefined Opcode)",
                    "UD2 instruction or reserved opcode.", 
                    EXCEPTION_CODE_NONE, current_tss);
  current_tss->state = STATE_ZOMBIE;
  dispatch_next ();
}

void trap_device_not_available_fault (void)
{
  exception_screen ("Fault", "Device Not Available (No Math Coprocessor)",
                    "Floating-point or WAIT/FWAIT instruction.", 
                    EXCEPTION_CODE_NONE, current_tss);
  current_tss->state = STATE_ZOMBIE;
  dispatch_next ();
}

void trap_double_fault (void)
{
  exception_screen ("Abort", "Double Fault", 
                    "Any instruction that can generate an exception, an NMI,"
                    " or an INTR (probably due to a kernel bug).",
                    EXCEPTION_CODE_SEGMENT, current_tss);
  DEBUG_HALT ("System halted.");
}

void trap_coprocessor_segment_overrun_abort (void)
{
  exception_screen ("Fault", "Coprocessor Segment Overrun",
                    "Floating-point instruction.", 
                    EXCEPTION_CODE_NONE, current_tss);
  current_tss->state = STATE_ZOMBIE;
  dispatch_next ();
}

void trap_invalid_tss_fault (void)
{
  exception_screen ("Fault", "Invalid TSS",
                    "Task switch or TSS access.", 
                    EXCEPTION_CODE_SEGMENT, current_tss);
  DEBUG_HALT ("System halted.");
}

void trap_segment_not_present_fault (void)
{
  exception_screen ("Fault", "Segment Not Present",
                    "Loading segment registers or accessing system segments.",
                    EXCEPTION_CODE_SEGMENT, current_tss);
  current_tss->state = STATE_ZOMBIE;
  dispatch_next ();
}

void trap_stack_fault (void)
{
  exception_screen ("Fault", "Stack-Segment Fault",
                    "Stack operations and SS register loads.", 
                    EXCEPTION_CODE_SEGMENT, current_tss);
  current_tss->state = STATE_ZOMBIE;
  dispatch_next ();
}

void trap_general_protection_fault (void)
{
  exception_screen ("Fault", "General Protection",
                    "Any memory reference and other protection checks.", 
                    EXCEPTION_CODE_SEGMENT, current_tss);
  current_tss->state = STATE_ZOMBIE;
  dispatch_next ();
}

void trap_page_fault (void)
{
#ifdef GROWING_STACK
//  while (TRUE)
  {
    u32 address;
    /* We need to check if this is a fault caused by the stack. */
    
    address = cpu_get_cr2 ();
    
    /* If this pagefault is caused by a growing stack, just map more
       memory. */
    
    if (address >= BASE_PROCESS_STACK)
    {

       if (current_tss->process_id == TASK_ID_KERNEL)
       {
         cpu_halt ();
       }

      DEBUG_MESSAGE (DEBUG, "Stack is growing (was %u pages)",
                     current_tss->stack_pages);
      if (memory_mutex == MUTEX_LOCKED)
      {
        DEBUG_MESSAGE (DEBUG, "Memory mutex was locked.");
      }
      else
      {
        u32 physical_page;

        mutex_kernel_wait (&memory_mutex);

        /* FIXME: Check return value. */

        memory_physical_allocate (&physical_page, 1, "Growing stack.");

        memory_virtual_map_other (current_tss, GET_PAGE_NUMBER (address),
                                  physical_page, 1,
                                  PAGE_WRITABLE | PAGE_NON_PRIVILEGED);
        mutex_kernel_signal (&memory_mutex);
        
        current_tss->stack_pages++;
        DEBUG_MESSAGE (DEBUG, "Done growing stack.");
      }
    }

    /* Ugly hack to detect (some) kernel stack overruns. */

    else if (address >= BASE_PROCESS_STACK - SIZE_PAGE)
    {
      debug_crash_screen ("Kernel stack overrun", current_tss);
      current_tss->state = STATE_ZOMBIE;

#ifdef HALT_ON_ERROR
      debug_run ();
#endif

      dispatch_next ();
    }
    
    /* ...or else, kill the thread. */
    
    else
    {
      while(TRUE){
      
      exception_screen ("Fault", "Page Fault",
                        "Any memory reference.",
                        EXCEPTION_CODE_PAGE, current_tss);
      current_tss->state = STATE_ZOMBIE;
#ifdef HALT_ON_ERROR
      debug_run ();
#endif
      dispatch_next ();
      }
    }
  DEBUG_MESSAGE (DEBUG, "Leaving handler.");
  }
#else
  exception_screen ("Fault", "Page Fault",
                    "Any memory reference.",
                    EXCEPTION_CODE_PAGE, current_tss);
  current_tss->state = STATE_ZOMBIE;
  debug_run ();
  dispatch_next ();  
#endif
}  


void trap_reserved (void)
{
  exception_screen ("XXXX", "(Intel Reserved)", 
                    "Buggy CPU non-fault",
                    EXCEPTION_CODE_NONE, current_tss);
  DEBUG_HALT ("System halted.");
}

void trap_floating_point_error_fault (void)
{
  exception_screen ("Fault", "Floating-Point Error (Math Fault)",
                    "Floating-point or WAIT/FWAIT instruction.", 
                    EXCEPTION_CODE_NONE, current_tss);
  current_tss->state = STATE_ZOMBIE;
  dispatch_next ();
}

void trap_alignment_check_fault (void)
{
  exception_screen ("Fault", "Alignment Check",
                    "Any data reference in memory.",
                    EXCEPTION_CODE_SEGMENT, current_tss);
  current_tss->state = STATE_ZOMBIE;
  dispatch_next ();
}

void trap_machine_check_abort (void)
{
  exception_screen ("Abort", "Machine Check",
                    "Error codes (if any) and source are model dependent.", 
                    EXCEPTION_CODE_NONE, current_tss);
  DEBUG_HALT ("System halted.");
}

void trap_streaming_simd_extensions_fault (void)
{
  exception_screen ("Fault", "Streaming SIMD Extensions",
                    "SIMD floating-point instructions.", 
                    EXCEPTION_CODE_NONE, current_tss);
  current_tss->state = STATE_ZOMBIE;
  dispatch_next ();
}


/* Initialise traps. (Well, exceptions really, but they're called traps
   on Motorola. ;) */

static void trap_setup_handler (u32 number, tss_type *setup_tss,
                                void *trap_pointer)
{
  /* Virtual address to the TSS. */
  
  u32 trap_tss_address = BASE_PROCESS_TRAP_TSS + number * 104;

  setup_tss->cr3 = (u32) kernel_page_directory;

  /* Set the flags to AF only. */

  setup_tss->eflags = FLAG_ADJUST;

  setup_tss->eip = (u32) trap_pointer;
  setup_tss->esp = BASE_TRAP_STACK + SIZE_PAGE;

  /* Set up segment selectors. */

  setup_tss->cs = SELECTOR_KERNEL_CODE;
  setup_tss->ss = SELECTOR_KERNEL_DATA;
  setup_tss->ds = SELECTOR_KERNEL_DATA;
  setup_tss->es = SELECTOR_KERNEL_DATA;
  setup_tss->fs = SELECTOR_KERNEL_DATA;
  setup_tss->gs = SELECTOR_KERNEL_DATA;

  /* Create a descriptor for this TSS. */
  
  trap_descriptor.limit_lo = SIZE_PAGE - 1;
  trap_descriptor.limit_hi = 0;
  trap_descriptor.granularity = 0;
  trap_descriptor.base_lo = trap_tss_address & 0xFFFF;
  trap_descriptor.base_hi = (trap_tss_address >> 16) & 0xFF;
  trap_descriptor.base_hi2 = (trap_tss_address >> 24) & 0xFF;	
                                                        
  trap_descriptor.type = DESCRIPTOR_TYPE_TSS;
  trap_descriptor.descriptor_type = 0;
  trap_descriptor.dpl = 0;
  trap_descriptor.segment_present = 1;
  trap_descriptor.zero = 0;
  trap_descriptor.operation_size = 0;
  
  /* Add it to the GDT and IDT. */

  gdt_add_entry (GDT_BASE_EXCEPTIONS + number, &trap_descriptor);
  idt_setup_task_gate (number, GDT (GDT_BASE_EXCEPTIONS + number, 0), 3);
//  idt_setup_interrupt_gate (number, SELECTOR_KERNEL_CODE, trap_pointer, 3);
}

/* Initialise traps. */

void trap_init (void)
{
  u32 physical_page;

  /* Allocate a page for the trap TSS:es. */

  /* FIXME: Check return value. */

  memory_physical_allocate (&physical_page, 1, "Trap TSS.");

  trap_tss = (void *) (physical_page * SIZE_PAGE);

  /* Allocate a page for the trap stack. */

  /* FIXME: Check return value. */

  memory_physical_allocate (&physical_page, 1, "Trap stack.");

  trap_stack = (void *) (physical_page * SIZE_PAGE);
  
  /* Map this. */

  memory_virtual_map_kernel
    (kernel_page_directory, GET_PAGE_NUMBER (BASE_PROCESS_TRAP_TSS),
     GET_PAGE_NUMBER (trap_tss), 1, PAGE_KERNEL);
  memory_virtual_map_kernel
    (kernel_page_directory, GET_PAGE_NUMBER (BASE_TRAP_STACK),
     GET_PAGE_NUMBER (trap_stack), 1, PAGE_KERNEL);

  /* Wipe the TSS. */

  memory_set_u8 ((u8 *) trap_tss, 0, SIZE_PAGE); 

  /* Setup exception handlers for all exceptions. */

  trap_setup_handler (0, &trap_tss[0], trap0_handler);

//  trap_setup_handler (1, &trap_tss[1], trap1_handler);
  idt_setup_interrupt_gate (1, SELECTOR_KERNEL_CODE, trap1_handler, 3);

  trap_setup_handler (2, &trap_tss[2], trap2_handler);

//  trap_setup_handler (3, &trap_tss[3], trap3_handler);
  idt_setup_interrupt_gate (3, SELECTOR_KERNEL_CODE, trap3_handler, 3);

  trap_setup_handler (4, &trap_tss[4], trap4_handler);
  trap_setup_handler (5, &trap_tss[5], trap5_handler);
  trap_setup_handler (6, &trap_tss[6], trap6_handler);
  trap_setup_handler (7, &trap_tss[7], trap7_handler);
  trap_setup_handler (8, &trap_tss[8], trap8_handler);
  trap_setup_handler (9, &trap_tss[9], trap9_handler);
  trap_setup_handler (10, &trap_tss[10], trap10_handler);
  trap_setup_handler (11, &trap_tss[11], trap11_handler);
  trap_setup_handler (12, &trap_tss[12], trap12_handler);
  trap_setup_handler (13, &trap_tss[13], trap13_handler);
  trap_setup_handler (14, &trap_tss[14], trap14_handler);

  trap_setup_handler (15, &trap_tss[15], trap_reserved_handler);

  trap_setup_handler (16, &trap_tss[16], trap_floating_point_error_fault);
  trap_setup_handler (17, &trap_tss[17], trap_alignment_check_fault);
  trap_setup_handler (18, &trap_tss[18], trap_machine_check_abort);
  trap_setup_handler (19, &trap_tss[19], trap_streaming_simd_extensions_fault);

  trap_setup_handler (20, &trap_tss[20], trap_reserved_handler);
  trap_setup_handler (21, &trap_tss[21], trap_reserved_handler);
  trap_setup_handler (22, &trap_tss[22], trap_reserved_handler);
  trap_setup_handler (23, &trap_tss[23], trap_reserved_handler);
  trap_setup_handler (24, &trap_tss[24], trap_reserved_handler);
  trap_setup_handler (25, &trap_tss[25], trap_reserved_handler);
  trap_setup_handler (26, &trap_tss[26], trap_reserved_handler);
  trap_setup_handler (27, &trap_tss[27], trap_reserved_handler);
  trap_setup_handler (28, &trap_tss[28], trap_reserved_handler);
  trap_setup_handler (29, &trap_tss[29], trap_reserved_handler);
  trap_setup_handler (30, &trap_tss[30], trap_reserved_handler);
  trap_setup_handler (31, &trap_tss[31], trap_reserved_handler);
}
