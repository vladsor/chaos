/* $Id: command.c,v 1.8 2000/10/18 00:01:34 plundis Exp $ */
/* Abstract: Cludio internal commands. */
/* Authors: Per Lundberg <plundis@chaosdev.org>
            Henrik Hallin <hal@chaosdev.org> */

/* Copyright 1999-2000 chaos development. */

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

#include "config.h"
#include "cluido.h"

#define VFS_BUFFER_SIZE         4096

const char *file_type[] =
{
  /* Directory. */

  "[DIR]",

  /* Ordinary file. */

  "[FILE]",

  /* Soft link. */
  
  "[SLNK]",

  /* Hard link. */

  "[HLNK]"
};

void command_event (int number_of_arguments, char **argument);
void command_event_queue (int number_of_arguments, char **argument);

void command_arp (int number_of_arguments, char **argument);
void command_benchmark (int number_of_arguments, char **argument);

void command_char_set (int number_of_arguments, char **argument);

void command_clear (int number_of_arguments, char **argument);
void command_cpu (int number_of_arguments, char **argument);
void command_crash (int number_of_arguments, char **argument);
void command_demo (int number_of_arguments, char **argument);
void command_directory_change_working (int number_of_arguments,
                                       char **argument);
void command_directory_list (int number_of_arguments, char **argument);
void command_execute (int number_of_arguments, char **argument);
void command_font_set (int number_of_arguments, char **argument);
void command_help (int number_of_arguments, char **argument);
void command_ip (int number_of_arguments, char **argument);

void command_ipc_info (int number_of_arguments, char **argument);

void command_irq (int number_of_arguments, char **argument);
void command_kill (int number_of_arguments, char **argument);
void command_memory (int number_of_arguments, char **argument);
void command_mount (int number_of_arguments, char **argument);

void command_output_to_log(int number_of_arguments, char **argument);

void command_pci (int number_of_arguments, char **argument);
void command_ports (int number_of_arguments, char **argument);
void command_processes (int number_of_arguments, char **argument);
void command_reboot (int number_of_arguments, char **argument);
void command_run (int number_of_arguments, char **argument);
void command_set (int number_of_arguments, char **argument);
void command_show (int number_of_arguments, char **argument);
void command_show_file (int number_of_arguments, char **argument);
void command_shutdown (int number_of_arguments, char **argument);
void command_sleep (int number_of_arguments, char **argument);
void command_test (int number_of_arguments, char **argument);
void command_threads (int number_of_arguments, char **argument);
void command_time (int number_of_arguments, char **argument);
void command_top (int number_of_arguments, char **argument);
void command_torus (int number_of_arguments, char **argument);
void command_unset (int number_of_arguments, char **argument);
void command_uptime (int number_of_arguments, char **argument);
void command_version (int number_of_arguments, char **argument);

void command_cdrom (int number_of_arguments, char **argument);

void command_bug (int number_of_arguments, char **argument);


void command_cdrom (int number_of_arguments __attribute__ ((unused)), 
char **argument __attribute__ ((unused)))
{
  mailbox_id_type mailbox_id[10];
  unsigned int services = 1;  
  message_parameter_type message_parameter;
  unsigned int cdrom_command;

  ipc_structure_type ipc_structure;

  if (number_of_arguments != 2)
  {
    return;
  }

  if (ipc_service_resolve ("cdrom", mailbox_id, &services, 5, &empty_tag) !=
      IPC_RETURN_SUCCESS)
  {
    log_print (&log_structure, LOG_URGENCY_EMERGENCY, 
               "No block services found.");
    return;
  }

  ipc_structure.output_mailbox_id = mailbox_id[0];

  /* Connect to this service. */

  if (ipc_service_connection_request (&ipc_structure) != IPC_RETURN_SUCCESS)
  {
    return;
  }
  
  string_to_number(argument[1], &cdrom_command, NULL);

  message_parameter.protocol = IPC_PROTOCOL_BLOCK;
  message_parameter.message_class = IPC_BLOCK_CONTROL;
  message_parameter.data = &cdrom_command;
  message_parameter.length = sizeof (cdrom_command);
  message_parameter.block = TRUE;
  ipc_send (ipc_structure.output_mailbox_id, &message_parameter);
}


static void rec(int level)
{
  console_print_formatted (&console_structure, "level %u\n", level);
  rec(level+1);
}
void command_bug (int number_of_arguments __attribute__ ((unused)),
                  char **argument __attribute__ ((unused)))
{
  if (!string_compare(argument[1], "stack"))
  {
    unsigned int i,temp;
    unsigned int repeat;
    string_to_number(argument[2], &repeat, NULL);
    for(i=0;i<repeat;i++)
    {
      console_print_formatted (&console_structure, "push %u\n" ,i );
      asm("pushl $0x0");
      asm("pushl $0x0");
    }
    for(i=0;i<repeat;i++)
    {
      console_print_formatted (&console_structure, "pop %u\n" ,i );
      asm("popl %%eax " : "=&a"(temp));
      asm("popl %%eax " : "=&a"(temp));
    }
  }
  else if (!string_compare(argument[1], "rec"))
  {
    rec(0);
  }
  else if (!string_compare(argument[1], "int"))
  {
    asm("int $3");
  }
  else if (!string_compare(argument[1], "break"))
  {
    unsigned int i= 50;
    console_print_formatted (&console_structure, "%u\n" ,i/0 );
  }
  else if (!string_compare(argument[1], "memory"))
  {
    u16 temp;
    asm("\
      mov $0xFFFF, %%ax
      mov %%ax, %%ss
    "
    : "=&a"(temp));
  }
}

static void ArithTest (void);
static void ArithTest (void)
{
  unsigned int eax, ebx, ecx, edx;
  asm ("
    incl %%ecx
    movl $0x08088405, %%edx
    mull %%edx
    movl %%eax,  %%ebx
    cdq
    idivl %%ecx
    lea	3(%%edx,%%eax,2), %%eax
    roll %%cl, %%edx
    xorl %%edx, %%edx
    divl %%ecx
    imull %%edx
    sbbl %%edx, %%eax
    movl %%ebx, %%eax
  " 
  : "=&a"(eax),
    "=&b"(ebx),
    "=&c"(ecx),
    "=&d"(edx));
}


/* Structure for holding a list of all the commands, and which
   functions they correspond to. */

command_type command[] =
{
  { "?", "", "Display help about available commands.", command_help },
  { "arp", "", "Show the entries in the ARP table.", command_arp },
  { "benchmark", "", "Do some basic IPC benchmarking.", command_benchmark },
  { "bug","","",command_bug },
  { "char_set","","Show current char set.", command_char_set },

  { "clear", "", "Clear the console.", command_clear },
  { "cpu", "", "Display information about installed CPUs.", command_cpu },
  { "crash", "", "Cause this process to crash.", command_crash },
  { "cd", "DIRECTORY",
    "Change the current working directory.",
    command_directory_change_working },
  { "cdrom", "", "Control CD-ROM", command_cdrom },
  { "demo", "", "A little graphic demo.", command_demo },
  { "dir", "", "List the contents of the current directory.",
    command_directory_list },

  { "event", "generate [number] | wait | counter-info", "Manipulate events.", command_event },
  { "event_queue", "create | destroy | info", "Manipulate events' queue", command_event_queue },

  { "execute", "FILE", "Executes the given file.", command_execute },
  { "font_set", "FILE", "Set the font to the one in FILE", command_font_set },
  { "help", "[COMMAND]", "Display help about available commands.",
    command_help },
  { "ip", "(--dhcp interface | --set interface address netmask [gateway] | --forward { on | off })", "Configure IPv4 networking.", command_ip },

  { "ipc_info", "", "Show ipc info.", command_ipc_info },

  { "irq", "", "Display information about the IRQ levels in use.",
    command_irq },
  { "log", "", "", command_output_to_log },
  
  { "ls", "", "See 'dir'", command_directory_list },
  { "kill", "THREAD", "Kills the given thread.", command_kill },
  { "memory", "", "Display memory amount and usage.", command_memory },

  { "mount", "","Mount device.", command_mount },

  //  { "nibbles", "", "Deathmatch Nibbles - another game.", command_nibbles },
  { "pci", "", "Display information about any PCI device in the system.",
    command_pci },
  { "ports", "", "Display information about the I/O ports in use.",
    command_ports },
  { "processes", "", "Display information about the running processes.",
    command_processes },
  { "reboot", "", "Reboot the system.", command_reboot },
  { "run", "SCRIPT", "Run a cluido script (just a list of commands).", command_run },
  { "shutdown", "", "Shutdown system by telling the boot server to shutdown the system.",
    command_shutdown },
  { "set", "VARIABLE VALUE", "Set VARIABLE to VALUE in the environment",
    command_set },
  { "show", "", "Show the contents of the environment.", command_show },
  { "show_file", "FILE", "Show the contents of the given file.", 
    command_show_file },
  { "sleep", "TIME", "Sleep for TIME seconds.", command_sleep },
  { "test", "", "Basic test command.", command_test },
  { "threads", "", "Display information about the all threads in the system.",
    command_threads },
  { "time", "", "Show the time.", command_time },
  { "top", "",
    "Display information about the running threads sorted on CPU usage.",
    command_top },
  { "torus", "", "Displays a 3D-projection of a torus.",
    command_torus },
  { "unset", "VARIABLE", "Unset VARIABLE in the environment.", command_unset },
  { "uptime", "", "Display current machine uptime.", command_uptime },
  { "version", "", "Show the program version", command_version }
};

int number_of_commands =  (sizeof (command) / sizeof (command_type));

event_queue_id_type test_queue_id = 0;

static unsigned int events_counter = 0;

static void event_handler(void)
{
  events_counter++;
/*  console_print (&console_structure, "event : OK" );*/
}

void command_event (int number_of_arguments, char **argument )
{
  return_type return_value;
  event_parameter_type event_parameter;
  unsigned int repeat = 1;

  if(!string_compare(argument[1],"generate"))
  {
    kernelfs_time_type kernelfs_begin_time;
    kernelfs_time_type kernelfs_end_time;

    event_parameter.protocol = 0;
    event_parameter.event_class = 0;
    event_parameter.time_out = 0;
    event_parameter.data = NULL;
    event_parameter.length = 0;

    kernelfs_begin_time.kernelfs_class = KERNELFS_CLASS_TIME_READ;
    system_call_kernelfs_entry_read (&kernelfs_begin_time);

    if(number_of_arguments > 2)
    {
       string_to_number(argument[2], &repeat, NULL);
    }

    for( ; repeat>0 ; repeat-- )
    {
      system_call_event_queue_send(test_queue_id,&event_parameter);  
    }

    kernelfs_end_time.kernelfs_class = KERNELFS_CLASS_TIME_READ;
    system_call_kernelfs_entry_read (&kernelfs_end_time);

    console_print_formatted (&console_structure, " OK , time : %llu\n",
      kernelfs_end_time.time - kernelfs_begin_time.time);
  }
  else if(!string_compare(argument[1],"wait"))
  {
    event_parameter.event_class = 0;
    event_parameter.data = NULL;
    event_parameter.length = 0;

    return_value = event_wait(test_queue_id,&event_parameter);  

    console_print_formatted (&console_structure, "ret : [%lu]\n" ,return_value );
  }
  else if(!string_compare(argument[1], "handler"))
  {
    event_set_handler(event_handler, test_queue_id, &event_parameter);
  }
  else if(!string_compare(argument[1], "counter-info"))
  {
    console_print_formatted (&console_structure, "counter : [%lu]\n" ,events_counter );
  }
  
  return;
}
void command_event_queue (int number_of_arguments __attribute__ ((unused)),
                  char **argument )
{
  if(!string_compare(argument[1],"create"))
  {
    system_call_event_queue_create(&test_queue_id,"Test_queue"); 
    console_print (&console_structure, "creation successfull\n" ); 
  }
  else if(!string_compare(argument[1],"destroy"))
  {
  }
  else if(!string_compare(argument[1],"info"))
  {
    kernelfs_event_queue_info_type *kernelfs_event_queue_info;
    u32 number;
    u32 i;

    number = KERNELFS_CLASS_EVENT_QUEUE_AMOUNT;
    system_call_kernelfs_entry_read (&number);
  
    memory_allocate( (void **)&kernelfs_event_queue_info,
      sizeof(kernelfs_event_queue_info_type) * number );
    
    kernelfs_event_queue_info->kernelfs_class = KERNELFS_CLASS_EVENT_QUEUE_INFO;
    system_call_kernelfs_entry_read ( kernelfs_event_queue_info );

    console_print( &console_structure, "QUEUE_ID EVENTS NAME\n");
        
    for(i=0;i<number;i++)
    {
      console_print_formatted( &console_structure, "%-8lu %-6lu %s.\n",
	kernelfs_event_queue_info[i].event_queue_id,
	kernelfs_event_queue_info[i].number_of_events,
	kernelfs_event_queue_info[i].name);
    }
    
  }

  return;
}

void command_char_set (int number_of_arguments __attribute__ ((unused)),
                  char **argument __attribute__ ((unused)))
{
  message_parameter_type message_parameter;

  message_parameter.protocol = IPC_PROTOCOL_CONSOLE;
  message_parameter.message_class = IPC_CONSOLE_PRINT_CHAR_SET;
  message_parameter.data = NULL;
  message_parameter.length = 0;
  message_parameter.block = TRUE;

  system_call_mailbox_send (console_structure.ipc_structure.output_mailbox_id,
                            &message_parameter);

  console_print (&console_structure, "\n");
}

void command_ipc_info (int number_of_arguments __attribute__ ((unused)),
                  char **argument __attribute__ ((unused)))
{
  kernelfs_ipc_info_type ipc_info;
  ipc_info.kernelfs_class = KERNELFS_CLASS_IPC_INFO;
  system_call_kernelfs_entry_read (&ipc_info);
  console_print (&console_structure, "IPC info :\n");
  console_print_formatted(&console_structure, "mailbox numbers : %lu \n", ipc_info.mailbox_numbers );
  console_print_formatted(&console_structure, "event queue numbers : %lu \n", ipc_info.event_queue_numbers );
  
}

void command_mount (int number_of_arguments __attribute__ ((unused)),
                  char **argument __attribute__ ((unused)))
{
  mailbox_id_type mailbox_id[10];
  unsigned int services = 1;  
  virtual_file_system_mount_type mount;
  message_parameter_type message_parameter;

  if (number_of_arguments != 2)
  {
    return;
  }

  if (ipc_service_resolve ("block", mailbox_id, &services, 5, &empty_tag) !=
      IPC_RETURN_SUCCESS)
  {
    log_print (&log_structure, LOG_URGENCY_EMERGENCY, 
               "No block services found.");
    return;
  }

  mount.mailbox_id = mailbox_id[0];
  string_copy (mount.location, argument[1]);

  /* That's it. Send the message. */

  message_parameter.protocol = IPC_PROTOCOL_VIRTUAL_FILE_SYSTEM;
  message_parameter.message_class = IPC_VIRTUAL_FILE_SYSTEM_MOUNT;
  message_parameter.data = &mount;
  message_parameter.length = sizeof (virtual_file_system_mount_type);
  message_parameter.block = TRUE;
  ipc_send (vfs_structure.output_mailbox_id, &message_parameter);

  log_print_formatted (&log_structure, LOG_URGENCY_DEBUG,
             "Mounted the first available block service as //%s.",
	     argument[1]);
}

/* Show the entries in the ARP table. */

void command_arp (int number_of_arguments __attribute__ ((unused)),
                  char **argument __attribute__ ((unused)))
{
  message_parameter_type message_parameter;
  int amount;
  int counter;
  ipv4_arp_entry_type arp;

  message_parameter.protocol = IPC_PROTOCOL_IPV4;
  message_parameter.message_class = IPC_IPV4_ARP_GET_AMOUNT;
  message_parameter.data = &amount;
  message_parameter.length = 0;
  message_parameter.block = TRUE;
  ipc_send (network_structure.output_mailbox_id, &message_parameter);

  message_parameter.length = sizeof (int);
  ipc_receive (network_structure.input_mailbox_id, &message_parameter, NULL);

  message_parameter.message_class = IPC_IPV4_ARP_GET_NUMBER;
  for (counter = 0; counter < amount; counter++)
  {
    message_parameter.data = &counter;
    message_parameter.length = sizeof (int);
    ipc_send (network_structure.output_mailbox_id, &message_parameter);

    message_parameter.data = &arp;
    message_parameter.length = sizeof (ipv4_arp_entry_type);
    ipc_receive (network_structure.input_mailbox_id, &message_parameter, NULL);
    
    console_print_formatted (&console_structure, 
                             "%u.%u.%u.%u %02X:%02X:%02X:%02X:%02X:%02X\n",
                             (arp.ip_address >> 0) & 0xFF, 
                             (arp.ip_address >> 8) & 0xFF,
                             (arp.ip_address >> 16) & 0xFF,
                             (arp.ip_address >> 24) & 0xFF,
                             arp.ethernet_address[0],
                             arp.ethernet_address[1],
                             arp.ethernet_address[2],
                             arp.ethernet_address[3],
                             arp.ethernet_address[4],
                             arp.ethernet_address[5]);
  }
}

/* Benchmark the system. This includes IPC and console. */
/* FIXME: Add file benchmarking as soon as file creation/deletion is done. */

void command_benchmark (int number_of_arguments __attribute__ ((unused)),
                        char **argument __attribute__ ((unused)))
{
  int counter;
  time_type start_time, end_time, phony;
  unsigned long int i;
  
  system_call_timer_read (&start_time);
    
  for (counter = 0; counter < 10000; counter++)
  {
    console_print (&console_structure, 
                   "\rBenchmarking IPC and console server...");
  }

  system_call_timer_read (&end_time);
  console_print_formatted (&console_structure, 
                           "\n%llu milliseconds (10 000 prints).\n",
                           end_time - start_time);

  console_print (&console_structure, "Benchmarking system calls...\n");
  system_call_timer_read (&start_time);
  for (counter = 0; counter < 1000000; counter++)
  {
    system_call_timer_read (&phony);
  }
  system_call_timer_read (&end_time);
  console_print_formatted (&console_structure,
                           "%llu milliseconds (1 000 000 system calls).\n",
                           end_time - start_time);

  system_call_timer_read (&start_time);
  for(i=0;i<4000000000LL;i++)
  {
    ArithTest();
  }
  system_call_timer_read (&end_time);
  console_print_formatted (&console_structure,
                           "%llu milliseconds (MAXINT).\n",
                           end_time - start_time);
}

/* Clear the screen. */

void command_clear (int number_of_arguments __attribute__ ((unused)),
                    char **argument __attribute__ ((unused)))
{
  console_clear (&console_structure);
}

/* Get information about installed CPU:s. */
typedef struct
{
  unsigned int cap;
  char* info;
} cpu_cap_record;

cpu_cap_record CPU_Cap_records [] =
{
  { CPU_FEATURE_CPUID	,"Supports CPUID instruction"},
  { CPU_FEATURE_FPU  	,"FPU present"},
  { CPU_FEATURE_VME  	,"Virtual Mode Extensions"},
  { CPU_FEATURE_DEBUG	,"Debug Extensions"},
  { CPU_FEATURE_PSE  	,"Page Size Extensions"},
  { CPU_FEATURE_TSC  	,"Time Stamp Counter"},
  { CPU_FEATURE_MSR  	,"Model Specific Registers"},
  { CPU_FEATURE_PAE  	,"Page Address Exceptions"},
  { CPU_FEATURE_MCE  	,"Machine Check Extensions"},
  { CPU_FEATURE_CMPXCHG8,"CMPXCHG8 instruction"},
  { CPU_FEATURE_APIC	,"APIC"},
  { CPU_FEATURE_SYSENTER,"SYSENTER/SYSEXIT instruction"},
  { CPU_FEATURE_MTRR	,"Memory Type Range Registers"},
  { CPU_FEATURE_GPE	,"Global Paging Extensions"},
  { CPU_FEATURE_MCA	,"Machine Check Architecture"},
  { CPU_FEATURE_CMOV	,"CMOV instruction"},
  { CPU_FEATURE_PAT	,"Page Attribue Table"},
  { CPU_FEATURE_PSE36	,"PSE36 (Page Size Extensions)"},
  { CPU_FEATURE_FXSAVE	,"FXSAVE/FXRSTOR instruction"},

  { CPU_FEATURE_MMX	,"MMX support"},
  { CPU_FEATURE_MMX_EXT	,"MMX Extensions"},

  { CPU_FEATURE_SSE	,"SSE"},
  { CPU_FEATURE_SSE_FP	,"SSE FP support"},
  { CPU_FEATURE_SSE_MMX	,"SSE MMX support (same as MMX extensions)"},

  { CPU_FEATURE_3DNOW	,"3DNow! support"},
  { CPU_FEATURE_3DNOW_EXT,"Extended 3DNow! support"},
    
  { CPU_FEATURE_SELF_SNOOP,"Self Snoop"},
  { CPU_FEATURE_ACC	,"Automatic Clock Control"},
  { CPU_FEATURE_IA_64	,"Intel Architecture - 64"},
  { CPU_FEATURE_PSN	,"Product Serial Number"},
  { CPU_FEATURE_CLFLSH	,"Cache line flush instruction CLFLSH"},
  { CPU_FEATURE_DTES	,"Debug Trace and EMON Store"},
  { CPU_FEATURE_ACPI	,"Processor duty cycle control (ACPI)"},
  { CPU_FEATURE_SSE_2	,"SSE2 instructions"},
  { CPU_FEATURE_AA_64	,"AMD Architecture - 64"},
  { CPU_FEATURE_VIDC	,"Voltage ID Control Suport"},
  { CPU_FEATURE_BMC	,"Bus Multiplier Control"}
};

static kernelfs_cpu_info_type cpu_info;
void command_cpu (int number_of_arguments __attribute__ ((unused)),
                  char **argument __attribute__ ((unused)))
{
  cpu_info.kernelfs_class = KERNELFS_CLASS_CPU_INFO;
  system_call_kernelfs_entry_read (&cpu_info);

  switch(number_of_arguments)
  {
    case 1:
    {
        console_print_formatted (&console_structure, "CPU 0: %s ",
                                 cpu_info.info.cpu_name);
        console_print_formatted (&console_structure, "at %u %cHz\n",
                cpu_info.info.scaled_frequency,cpu_info.info.frequency_scale);
        break;
    }

    case 2:
    {
	if(!string_compare(argument[1],"-all"))
	{
	    int number = sizeof(CPU_Cap_records)/sizeof(cpu_cap_record);
	    int i;
	    console_print_formatted (&console_structure, "CPU 0: %s %s,",
                                     cpu_info.info.cpu_name);
            console_print_formatted (&console_structure, " model %X%X%X.\n",
                           (u16)cpu_info.info.family, (u16)cpu_info.info.model, 
			   (u16)cpu_info.info.stepping);

            console_print_formatted (&console_structure, "Generation %u.\n",
                                     cpu_info.info.generation);
            console_print_formatted (&console_structure, "Vendor: %s.\n",
                               cpu_info.info.vendor_name);
            console_print_formatted (&console_structure, "Vendor string: %s.\n",
                               cpu_info.info.vendor_string);
            console_print_formatted (&console_structure, "FPU: %s.\n",
                               cpu_info.info.fpu_name);
            console_print_formatted (&console_structure, "frequency %u Hz\n",
                               cpu_info.info.frequency);

            if (cpu_feature_get(cpu_info.info, CPU_FEATURE_CACHE_L1_INFO))
	    {
              console_print_formatted (&console_structure, "Cache L1 size"	    
	    " data: %uKB, instruction: %uKB\n",
                               cpu_info.info.data_cache_l1_size,
			       cpu_info.info.instructions_cache_l1_size);
	    }       
            if (cpu_feature_get(cpu_info.info, CPU_FEATURE_CACHE_L2_INFO))
            {
              console_print_formatted (&console_structure, "Cache L2 size: %uKB\n",
			       cpu_info.info.cache_l2_size);
	    }
            console_print (&console_structure, "Supports:\n");
	    for(i=0; i<number ;i++)
	    {
        	if(cpu_feature_get(cpu_info.info,CPU_Cap_records[i].cap))
		{
	           console_print_formatted (&console_structure, "%s\n",
                           CPU_Cap_records[i].info);
		}
	    }
	}
	break;	
    }
    default :
  }
}


#define WIDTH           320
#define HEIGHT          200
#define DEPTH           8

#define X_MIN           500
#define X_MAX          1000

#define Y_MIN           500
#define Y_MAX          1000

#define B00011100       0x1C
#define B11100000       0xE0



/* Cause an illegal pagefault. */

void command_crash (int number_of_arguments __attribute__ ((unused)),
                    char **argument __attribute__ ((unused)))
{
  *(u32 *) NULL = 0x42424242;
}

/* Show a graphic demonstration. */

void command_demo (int number_of_arguments __attribute__ ((unused)),
                   char *argument[] __attribute__ ((unused)))
{
#if FALSE
  bool done = FALSE;
  u8 *screen = (u8 *) 0xA0000;
  int x, y, index, fov = 256;
  time_type random_seed;
  keyboard_packet_type keyboard_packet;
  ipc_mouse_event_type *ipc_mouse_event =
    (ipc_mouse_event_type *) &keyboard_packet;

  /* First of all, resolve the console service. */

#define NUM_STARS 500

  int *star_x;
  int *star_y;
  int *star_z;
  u8 *star_c;
  u8 *buffer;

  int mouse_x = 160, mouse_y = 100;

  /* Allocate some memory. */

  memory_allocate ((void **) &buffer, 64000);
  memory_allocate ((void **) &star_x, sizeof (int) * NUM_STARS);
  memory_allocate ((void **) &star_y, sizeof (int) * NUM_STARS);
  memory_allocate ((void **) &star_z, sizeof (int) * NUM_STARS);
  memory_allocate ((void **) &star_c, sizeof (u8) * NUM_STARS);

  /* FIXME. */
  if (console_mode_set (&console_structure, WIDTH, HEIGHT, DEPTH, 
                        VIDEO_MODE_TYPE_GRAPHIC) != CONSOLE_RETURN_SUCCESS)
  {
    return;
  }

  memory_set_u8 (screen, 0, WIDTH * HEIGHT);
  
  /* Initialise random sequence. */

  system_call_timer_read (&random_seed);

  random_init ((int) random_seed);

  for (index = 0; index < NUM_STARS; index ++)
  {
    star_z[index] = random (1500) + 1;
    star_x[index] = X_MIN - random (X_MAX);
    star_y[index] = Y_MIN - random (Y_MAX);
    star_c[index] = random (256);
  }

  while (!done)
  {
    int event_type;

    console_event_wait (&console_structure, &keyboard_packet,
                        &event_type, FALSE);
    
    if (event_type == CONSOLE_EVENT_KEYBOARD &&
        keyboard_packet.key_pressed &&
        keyboard_packet.has_special_key &&
        keyboard_packet.special_key == IPC_KEYBOARD_SPECIAL_KEY_ESCAPE)
    {
      done = TRUE;
    }
    else if (event_type == CONSOLE_EVENT_MOUSE)
    {
      mouse_x = (ipc_mouse_event->x / 2);
      mouse_x = 320 - mouse_x;
        
      if (ipc_mouse_event->button == 1)
      {
        fov -= 1;
        if (fov < 0) fov = 0;
      }
      
      if (ipc_mouse_event->button == 2)
      {
        fov += 1;
      }
      
      if (ipc_mouse_event->button == 4)
      {
        fov = 256;
      }
      
      mouse_y = (ipc_mouse_event->y >> 1);
    }
    
    for (index = 0; index < NUM_STARS; index++)
    {
      if (mouse_x < 0)
      {
        mouse_x = 0;
      }

      if (mouse_y < 0)
      {
        mouse_y = 0;
      }

      if (mouse_x > 319)
      {
        mouse_x = 319;
      }

      if (mouse_y > 199)
      {
        mouse_y = 199;
      }

      x = mouse_x + (star_x[index] * fov) / star_z[index];
      y = mouse_y - (star_y[index] * fov) / star_z[index];

      star_z[index]--;

      if (star_z[index] == 0) 
      {
        star_x[index] = X_MIN - random (X_MAX);
        star_y[index] = Y_MIN - random (Y_MAX);
        star_c[index] = random (256);
        star_z[index] = random (1500) + 1;
      }

      if (x > -1 && x < 320 && y > -1 && y < 200)
      {
        buffer[(y * 320) + x] = star_c[index];
      }
    }    
    memory_copy (screen, &buffer, 64000);
    memory_set_u32 ((u32 *) &buffer, 0, 16000);
  }

  if (console_mode_set (&console_structure, 80, 50, 4, 
                        VIDEO_MODE_TYPE_TEXT) !=
      VIDEO_RETURN_SUCCESS)
  {
    return;
  }

  console_clear (&console_structure);
#endif
}

/* Change current working directory. */

void command_directory_change_working (int number_of_arguments,
                                       char *argument[])
{
  file_verbose_directory_entry_type directory_entry;

  /* FIXME: Ugly. */

  char new_working_directory[256];

  string_copy (new_working_directory, working_directory);

  if (number_of_arguments != 2)
  {
    return;
  }

  if (string_compare (argument[1], ".") == 0)
  {
    return;
  }

  if (string_compare (argument[1], "..") == 0)
  {
    /* Go up a level. */

    int index = string_length (new_working_directory) - 1;
    
    while (new_working_directory[index] != '\0' &&
           new_working_directory[index] != '/')
    {
      index--;
    }

    if (index > 0 && new_working_directory[index] == '/' &&
        new_working_directory[index - 1] == '/')
    {
      new_working_directory[index + 1] = '\0';
    }
    else
    {
      new_working_directory[index] = '\0';
    }
  }
  else if (argument[1][0] == '/')
  {
    /* Absolute path. */

    string_copy (new_working_directory, argument[1]);
  }
  else
  {
    /* Relative path. */

    if (string_compare (working_directory, "//") != 0)
    {
      string_append (new_working_directory, "/");
    }
    string_append (new_working_directory, argument[1]);
  }

  string_copy_max (directory_entry.path_name, new_working_directory,
                   MAX_PATH_NAME_LENGTH);
  file_get_info (&vfs_structure, &directory_entry);

  if (!directory_entry.success || 
      directory_entry.type != FILE_ENTRY_TYPE_DIRECTORY)
  {
    console_print_formatted (&console_structure, "%s is not a directory.\n",
                             new_working_directory);
  }
  else
  {
    string_copy (working_directory, new_working_directory);
  }
}

/* List files. */

void command_directory_list (int number_of_arguments __attribute__ ((unused)),
                             char *argument[] __attribute__ ((unused)))
{
  u8 *buffer;
  file_directory_entry_read_type *directory_entry;
  unsigned int index;

  memory_allocate ((void **) &buffer, VFS_BUFFER_SIZE);
  directory_entry = (file_directory_entry_read_type *) buffer;

  directory_entry->start_entry = 0;
  directory_entry->entries = ((VFS_BUFFER_SIZE - 
                               sizeof (file_directory_entry_read_type)) /
                              sizeof (file_directory_entry_type));
  directory_entry->end_reached = FALSE;

  while (directory_entry->end_reached != TRUE)
  {
    string_copy (directory_entry->path_name, working_directory);

    if (file_directory_entry_read (&vfs_structure, directory_entry) !=
        FILE_RETURN_SUCCESS)
    {
      break;
    }
    
    for (index = 0; index < directory_entry->entries; index++)
    {
      file_verbose_directory_entry_type verbose_directory_entry;

      string_copy (verbose_directory_entry.path_name, working_directory);
      if (string_compare (working_directory, "//") != 0)
      {
        string_append (verbose_directory_entry.path_name, "/");
      }
      string_append (verbose_directory_entry.path_name,
                     directory_entry->entry[index].name);

      file_get_info (&vfs_structure, &verbose_directory_entry);

      if (directory_entry->entry[index].type == FILE_ENTRY_TYPE_FILE)
      {
        console_print_formatted (&console_structure, "%-10u %s\n",
                                 verbose_directory_entry.size,
                                 directory_entry->entry[index].name);
      }
      else
      {
        console_print_formatted (&console_structure, "%-10s %s\n",
                                 file_type[directory_entry->entry[index].type],
                                 directory_entry->entry[index].name);
      }
    }
    directory_entry->start_entry += directory_entry->entries;
  }

  memory_deallocate ((void **) &buffer);
}

/* Executes the given file. */

void command_execute (int number_of_arguments, char **argument)
{
  u8 *buffer;
  file_handle_type handle;
  file_verbose_directory_entry_type directory_entry;
  process_id_type process_id;
  unsigned int bytes_read = 0;

  if (number_of_arguments != 2)
  {
    console_print_formatted (&console_structure,
                             "Wrong number of arguments! Try 'help %s'.\n",
                             argument[0]);
    return;
  }

  string_copy (directory_entry.path_name, argument[1]);
  if (file_get_info (&vfs_structure, &directory_entry) != FILE_RETURN_SUCCESS)
  {
    console_print_formatted (&console_structure, 
                             "Could not get information about file %s.\n",
                             argument[1]);
    return;
  }

  /* Allocate a buffer, so we can read the entire file. */

  memory_allocate ((void **) &buffer, directory_entry.size);

  file_open (&vfs_structure, argument[1], FILE_MODE_READ, &handle);

  /* Read the file. */

  while (bytes_read < directory_entry.size)
  {
    unsigned int bytes;
    
    bytes = directory_entry.size - bytes_read;
    if (bytes > 32 * KB)
    {
      bytes = 32 * KB;
    }
    file_read (&vfs_structure, handle, bytes, &buffer[bytes_read]);
    bytes_read += bytes;
  }

  switch (execute_elf ((elf_header_type *) buffer, "", &process_id))
  {
    case EXECUTE_ELF_RETURN_SUCCESS:
    {
      console_print_formatted (&console_structure, 
                               "New process ID %lu.\n", process_id);
      break;
    }

    case EXECUTE_ELF_RETURN_IMAGE_INVALID:
    {
      console_print (&console_structure, "Invalid ELF image.\n");
      break;
    }

    case EXECUTE_ELF_RETURN_ELF_UNSUPPORTED:
    {
      console_print (&console_structure, "Unsupported ELF.\n");
      break;
    }

    case EXECUTE_ELF_RETURN_FAILED:
    {
      console_print (&console_structure, 
                     "system_call_process_create failed.\n");
      break;
    }
  }

  memory_deallocate ((void **) &buffer);
}

/* Change the VGA font accordingly. */

void command_font_set (int number_of_arguments, char **argument)
{
  u8 *buffer;
  message_parameter_type message_parameter;
  mailbox_id_type mailbox_id[10];
  ipc_structure_type ipc_structure;
  file_verbose_directory_entry_type directory_entry;
  file_handle_type handle;
  unsigned int services = 10;

  /* FIXME: Support fonts of different sizes. */

  unsigned int font_size = 2048;

  if (number_of_arguments != 2)
  {
    console_print_formatted (&console_structure,
                             "Wrong number of arguments! Try 'help %s'.\n",
                             argument[0]);
    return;
  }

  memory_allocate ((void **) &buffer, font_size);
  
  string_copy (directory_entry.path_name, argument[1]);
  if (file_get_info (&vfs_structure, &directory_entry) != FILE_RETURN_SUCCESS)
  {
    console_print_formatted (&console_structure, 
                             "Could not get information about file %s.\n",
                             argument[1]);
    memory_deallocate ((void **) &buffer);
    return;
  }

  file_open (&vfs_structure, argument[1], FILE_MODE_READ, &handle);

  /* Read the file.  */

  file_read (&vfs_structure, handle, font_size, buffer);

  /* Set the font. */
  /* FIXME: Have a library function for this, and make it go through
     the console server. */

  ipc_service_resolve ("video", mailbox_id, &services, 5, &empty_tag);

  ipc_structure.output_mailbox_id = mailbox_id[0];
  ipc_service_connection_request (&ipc_structure);

  message_parameter.protocol = IPC_PROTOCOL_VIDEO;
  message_parameter.message_class = IPC_VIDEO_FONT_SET;
  message_parameter.data = buffer;
  message_parameter.length = font_size;

  ipc_send (ipc_structure.output_mailbox_id, &message_parameter);

  memory_deallocate ((void **) &buffer);
}

/* Show a list of the available commands, with a short description */

void command_help (int number_of_arguments, char **argument)
{
  int counter;

  if (number_of_arguments == 2)
  {
    for (counter = 0; counter < number_of_commands; counter++)
    {
      if (string_compare (command[counter].name, argument[1]) == 0)
      {
        console_print_formatted (&console_structure, 
                                 "SYNOPSIS: %s %s\n\n  DESCRIPTION: %s\n",
                                 command[counter].name,
                                 command[counter].arguments, 
                                 command[counter].description);
        break;
      }
    }
    
    if (counter == number_of_commands)
    {
      console_print (&console_structure, "Unknown command. Try 'help'.\n");
    }
  }
  else
  {
    console_print (&console_structure,
                   "Available commands. (try 'help command' for help about a specific command)\n\n");

    for (counter = 0; counter < number_of_commands; counter++)
    {
      console_print_formatted (&console_structure,
                               "  %-10s %s\n", command[counter].name,
                               command[counter].description);
    }
  }
}

/* Configure IP networking. */

void command_ip (int number_of_arguments, char **argument)
{
  /* If no arguments are given, print information about the current
     interfaces. */

  if (number_of_arguments == 1)
  {
    ipv4_interface_type ipv4_interface;
    message_parameter_type message_parameter;
    unsigned int index;
    unsigned int amount;
    unsigned int flags;

    message_parameter.protocol = IPC_PROTOCOL_IPV4;
    message_parameter.message_class = IPC_IPV4_INTERFACE_GET_AMOUNT;
    message_parameter.data = &amount;
    message_parameter.length = 0;
    message_parameter.block = TRUE;
    ipc_send (network_structure.output_mailbox_id, &message_parameter);

    message_parameter.length = sizeof (unsigned int);
    ipc_receive (network_structure.input_mailbox_id, &message_parameter, NULL);

    for (index = 0; index < amount; index++)
    {
      message_parameter.data = &index;
      message_parameter.message_class = IPC_IPV4_INTERFACE_GET_NUMBER;
      message_parameter.length = sizeof (unsigned int);
      ipc_send (network_structure.output_mailbox_id, &message_parameter);
      
      message_parameter.data = &ipv4_interface;
      message_parameter.length = sizeof (ipv4_interface_type);
      ipc_receive (network_structure.input_mailbox_id,
                   &message_parameter, NULL);

      console_print_formatted (&console_structure, 
                               "Interface: %s\n",
                               ipv4_interface.identification);
      console_print_formatted (&console_structure,
                               "  Ethernet address: %02X:%02X:%02X:%02X:%02X:%02X\n",
                               ipv4_interface.hardware_address[0],
                               ipv4_interface.hardware_address[1],
                               ipv4_interface.hardware_address[2],
                               ipv4_interface.hardware_address[3],
                               ipv4_interface.hardware_address[4],
                               ipv4_interface.hardware_address[5]);
      console_print_formatted (&console_structure, 
                               "  IP address: %lu.%lu.%lu.%lu, netmask: %lu.%lu.%lu.%lu, gateway: %lu.%lu.%lu.%lu\n",
                               ipv4_interface.ip_address & 0xFF,
                               (ipv4_interface.ip_address >> 8) & 0xFF, 
                               (ipv4_interface.ip_address >> 16) & 0xFF, 
                               ipv4_interface.ip_address >> 24,
                               ipv4_interface.netmask & 0xFF,
                               (ipv4_interface.netmask >> 8) & 0xFF, 
                               (ipv4_interface.netmask >> 16) & 0xFF, 
                               ipv4_interface.netmask >> 24,
                               ipv4_interface.gateway & 0xFF,
                               (ipv4_interface.gateway >> 8) & 0xFF, 
                               (ipv4_interface.gateway >> 16) & 0xFF, 
                               ipv4_interface.gateway >> 24);
      console_print_formatted (&console_structure,
                               "  Flags: %s, %s\n", 
                               ipv4_interface.dhcp ? "DHCP" : "Static",
                               ipv4_interface.up ? "Up" : "Down");
    }

    network_get_flags (&network_structure, &flags);
    console_print_formatted (&console_structure, "General flags: %s\n",
                             (flags & IPC_IPV4_FLAG_FORWARD) == 
                             IPC_IPV4_FLAG_FORWARD ? "IP forwarding enabled" :
                             "IP forwarding disabled");
  }

  /* Otherwise, we are probably trying to set the interface up. */

  else if (number_of_arguments > 1)
  {
    ipv4_interface_type interface;
    message_parameter_type message_parameter;

    if (string_compare (argument[1], "--dhcp") == 0 &&
        number_of_arguments == 3)
    {
      interface.dhcp = TRUE;
      interface.up = TRUE;
      string_copy (interface.identification, argument[2]);

      message_parameter.protocol = IPC_PROTOCOL_IPV4;
      message_parameter.message_class = IPC_IPV4_INTERFACE_CONFIGURE;
      message_parameter.data = &interface;
      message_parameter.length = sizeof (ipv4_interface_type);
      message_parameter.block = TRUE;
      ipc_send (network_structure.output_mailbox_id,
                &message_parameter);
    }
    
    /* Disable/enable IP forwarding. */

    else if (string_compare (argument[1], "--forward") == 0 &&
             number_of_arguments == 3)
    {
      bool forward;
      unsigned int flags;

      if (string_compare (argument[2], "on") == 0)
      {
        forward = TRUE;
      }
      else if (string_compare (argument[2], "off") == 0)
      {
        forward = FALSE;
      }
      else
      {
        console_print_formatted (&console_structure,
                                 "Syntax error. Try 'help %s'.\n",
                                 argument[0]);
        return;
      }

      network_get_flags (&network_structure, &flags);

      if (forward)
      {
        flags |= IPC_IPV4_FLAG_FORWARD;
      }

      network_set_flags (&network_structure, flags);
    }
    else if (string_compare (argument[1], "--set") == 0 &&
             number_of_arguments >= 5)
    {
      interface.dhcp = FALSE;
      interface.up = TRUE;
      string_copy (interface.identification, argument[2]);

      if (network_string_to_binary_ip_address
          (argument[3], &interface.ip_address) != NETWORK_RETURN_SUCCESS)
      {
        console_print (&console_structure, "Invalid IP address specified!\n");
        return;
      }

      if (network_string_to_binary_ip_address
          (argument[4], &interface.netmask) != NETWORK_RETURN_SUCCESS)
      {
        console_print (&console_structure, "Invalid netmask specified!\n");
        return;
      }

      if (number_of_arguments == 6)
      {
        if (network_string_to_binary_ip_address
            (argument[5], &interface.gateway) != NETWORK_RETURN_SUCCESS)
        {
          console_print (&console_structure, "Invalid gateway address specified!\n");
          return;
        }
      }
      else
      {
        interface.gateway = 0;
      }

      message_parameter.protocol = IPC_PROTOCOL_IPV4;
      message_parameter.message_class = IPC_IPV4_INTERFACE_CONFIGURE;
      message_parameter.data = &interface;
      message_parameter.length = sizeof (ipv4_interface_type);
      message_parameter.block = TRUE;
      ipc_send (network_structure.output_mailbox_id,
                &message_parameter);
    }
    else
    {
      console_print_formatted (&console_structure,
                               "Unknown parameter: %s, or wrong number of arguments. Try 'help %s'.\n",
                               argument[1], argument[0]);
    }
  }
}

/* Get information about IRQ levels. */

void command_irq (int number_of_arguments, 
                  char **argument __attribute__ ((unused)))
{
  unsigned int irqs = KERNELFS_CLASS_IRQ_AMOUNT;
  kernelfs_irq_info_type kernelfs_irq_info;
  unsigned int index;

  if (number_of_arguments != 1)
  {
    console_print_formatted (&console_structure, 
                             "Wrong number of arguments! Try 'help %s'.\n",
                             argument[0]);
    return;
  }

  if (system_call_kernelfs_entry_read (&irqs) != STORM_RETURN_SUCCESS)
  {
    console_print (&console_structure,
                   "Couldn't read number of allocated IRQs from kernel.");
    return;
  }
  
  kernelfs_irq_info.kernelfs_class = KERNELFS_CLASS_IRQ_INFO;
  
  console_print_formatted (&console_structure,
                           "%-3s %-10s %-10s %-10s %-10s %s\n",
                           "IRQ", "Process ID", "Cluster ID",
                           "Thread ID", "Occurred", "Description");

  for (index = 0; index < irqs; index++)
  {
    kernelfs_irq_info.which = index;
    if (system_call_kernelfs_entry_read (&kernelfs_irq_info) !=
        STORM_RETURN_SUCCESS)
    {
      console_print (&console_structure, "Failed to get IRQ information");
    }
    else
    {
      console_print_formatted (&console_structure,
                               "%-3u %-10u %-10u %-10u %-10u %s\n",
                               kernelfs_irq_info.level,
                               kernelfs_irq_info.process_id,
                               kernelfs_irq_info.cluster_id,
                               kernelfs_irq_info.thread_id,
                               (unsigned int) kernelfs_irq_info.occurred,
                               kernelfs_irq_info.description);
    }
  }
}

/* Kill a thread. */

void command_kill (int number_of_arguments, char **argument)
{
  process_id_type thread_id;

  if (number_of_arguments != 2)
  {
    console_print_formatted (&console_structure, 
                             "Wrong number of arguments! Try 'help %s'.\n",
                             argument[0]);
    return;
  }

  if (string_to_number (argument[1], (unsigned int *) &thread_id, NULL) !=
      STRING_RETURN_SUCCESS)
  {
    console_print_formatted (&console_structure, 
                             "Invalid thread ID specified!");
    return;
  }

  system_call_thread_control (thread_id, THREAD_TERMINATE, 0);
}

/* Print information about used and available memory. */

void command_memory (int number_of_arguments __attribute__ ((unused)),
                     char **argument __attribute__ ((unused)))
{
  kernelfs_memory_info_type memory_info;

  memory_info.kernelfs_class = KERNELFS_CLASS_MEMORY_INFO;
  system_call_kernelfs_entry_read (&memory_info);
  console_print_formatted 
    (&console_structure, 
     "Physical memory: %luK total, %luK free, %luK used\n",
     memory_info.total_memory / 1024,  memory_info.free_memory / 1024,
     (memory_info.total_memory - memory_info.free_memory) / 1024);
  console_print_formatted 
    (&console_structure, 
     "Global memory: %lu total, %lu free, %lu used\n",
     memory_info.total_global_memory, memory_info.free_global_memory,
     memory_info.total_global_memory - memory_info.free_global_memory);
}

void command_output_to_log (int number_of_arguments __attribute__ ((unused)),
                  char *argument[] __attribute__ ((unused)))
{
  if(number_of_arguments >= 1)
  {
     log_print_formatted(&log_structure,LOG_URGENCY_INFORMATIVE,
     "%s",argument[1]);
  }
}


/* Get information about installed PCI devices. */

void command_pci (int number_of_arguments __attribute__ ((unused)),
                  char *argument[] __attribute__ ((unused)))
{
  static unsigned int number_of_devices, i;
  message_parameter_type message_parameter;
  static pci_device_info_type *device_info;
  unsigned int size;

  message_parameter.protocol = IPC_PROTOCOL_PCI;
  message_parameter.message_class = IPC_PCI_DEVICE_GET_AMOUNT;
  message_parameter.data = NULL;
  message_parameter.length = 0;
  message_parameter.block = TRUE;
  ipc_send (pci_structure.output_mailbox_id, &message_parameter);
  
  message_parameter.data = &number_of_devices;
  message_parameter.length = sizeof (unsigned int);
  ipc_receive (pci_structure.input_mailbox_id, &message_parameter, &size);

  memory_allocate ((void **) &device_info,
                         number_of_devices * sizeof (pci_device_info_type));

  message_parameter.message_class = IPC_PCI_DEVICE_GET_INFO;
  message_parameter.data = NULL;
  message_parameter.length = 0;
  message_parameter.block = TRUE;
  ipc_send (pci_structure.output_mailbox_id, &message_parameter);

  message_parameter.data = device_info;
  message_parameter.length = number_of_devices * sizeof (pci_device_info_type);
  ipc_receive (pci_structure.input_mailbox_id, &message_parameter, &size);

  console_print_formatted (&console_structure, "%-35s %-35s %-4s\n",
                           "DEVICE NAME","VENDOR NAME","IRQ");

  for(i=0;i<number_of_devices;i++)
  {
    console_print_formatted (&console_structure, "%-35s %-35s %-4lu\n",
      device_info[i].device_name, device_info[i].vendor_name, 
      device_info[i].irq);
  }
  
  memory_deallocate ((void **) &device_info);
}

/* Get information about the status of the I/O ports in the system. */

void command_ports (int number_of_arguments, 
                    char *argument[] __attribute__ ((unused)))
{
  unsigned int ranges = KERNELFS_CLASS_PORT_AMOUNT;
  kernelfs_port_info_type kernelfs_port_info;
  unsigned int index;

  if (number_of_arguments != 1)
  {
    console_print_formatted (&console_structure, 
                             "Wrong number of arguments! Try 'help %s'.\n",
                             argument[0]);
    return;
  }

  if (system_call_kernelfs_entry_read (&ranges) != STORM_RETURN_SUCCESS)
  {
    console_print (&console_structure,
                   "Couldn't read information about the number of available port ranges from kernel.");
    return;
  }
  
  kernelfs_port_info.kernelfs_class = KERNELFS_CLASS_PORT_INFO;
  
  console_print_formatted (&console_structure,
                           "%-9s %-10s %-10s %-10s %s\n",
                           "Range", "Process ID",
                           "Cluster ID", "Thread ID", "Description");

  for (index = 0; index < ranges; index++)
  {
    kernelfs_port_info.port = index;
    system_call_kernelfs_entry_read (&kernelfs_port_info);

    console_print_formatted (&console_structure,
                             "%04X-%04X %-10u %-10u %-10u %s\n",
                             kernelfs_port_info.base,
                             kernelfs_port_info.base + 
                             kernelfs_port_info.length - 1,
                             kernelfs_port_info.process_id,
                             kernelfs_port_info.cluster_id,
                             kernelfs_port_info.thread_id,
                             kernelfs_port_info.description);
  }
}

/* List the processes. */

void command_processes (int number_of_arguments __attribute__ ((unused)), 
                        char **argument __attribute__ ((unused)))
{
  kernelfs_process_info_type kernelfs_process_info;
  kernelfs_thread_info_type kernelfs_thread_info;
  u32 processes = KERNELFS_CLASS_PROCESS_AMOUNT;

  system_call_kernelfs_entry_read (&processes);
  console_print (&console_structure, "PROCESS_ID THREADS NAME\n");
  kernelfs_process_info.kernelfs_class = KERNELFS_CLASS_PROCESS_INFO;

  for (kernelfs_process_info.process_number = 0;
       kernelfs_process_info.process_number < processes; 
       kernelfs_process_info.process_number++)
  {
    system_call_kernelfs_entry_read (&kernelfs_process_info);
    console_print_formatted (&console_structure, "%-10lu %-7u %s.\n",
                             kernelfs_process_info.process_id,
                             kernelfs_process_info.number_of_threads,
                             kernelfs_process_info.name);
 
    kernelfs_thread_info.process_id = kernelfs_process_info.process_id;
  }
}

/* Reboot. */

void command_reboot (int number_of_arguments __attribute__ ((unused)),
                     char **argument __attribute__ ((unused)))
{
  system_call_thread_control (THREAD_ID_KERNEL, THREAD_TERMINATE, 0);
}

/* Run a script. */

void command_run (int number_of_arguments, char *argument[])
{
  file_handle_type handle;
  u8 *buffer;
  file_verbose_directory_entry_type directory_entry;
  unsigned int where;

  if (number_of_arguments != 2)
  {
    console_print_formatted (&console_structure, 
                             "Wrong number of arguments! Try 'help %s'.\n",
                             argument[0]);
    return;
  }

  memory_allocate ((void **) &buffer, VFS_BUFFER_SIZE);
  
  string_copy (directory_entry.path_name, argument[1]);
  if (file_get_info (&vfs_structure, &directory_entry) != FILE_RETURN_SUCCESS)
  {
    console_print_formatted (&console_structure, 
                             "Could not get information about file %s.\n",
                             argument[1]);
    memory_deallocate ((void **) &buffer);
    return;
  }

  file_open (&vfs_structure, argument[1], FILE_MODE_READ, &handle);

  /* Read the file (hopefully, it's not more than
     VFS_BUFFER_SIZE...) */

  file_read (&vfs_structure, handle, directory_entry.size, buffer);

  for (where = 0; where < directory_entry.size; where++)
  {
    if (buffer[where] == '\n')
    {
      buffer[where] = '\0';
    }
  }

  where = 0;
  while (where < directory_entry.size)
  {
    console_print_formatted (&console_structure,
                             "%s\n", &buffer[where]);
    run (&buffer[where]);
    where += string_length (&buffer[where]) + 1;
  }
    
  memory_deallocate ((void **) &buffer);
}

/* Set an environment variable. */

void command_set (int number_of_arguments, char *argument[])
{
  int index;

  if (number_of_arguments != 3)
  {
    console_print_formatted (&console_structure, 
                             "Wrong number of arguments! Try 'help %s'.\n",
                             argument[0]);
    return;
  }

  for (index = 0; index < 16 && environment[index].key[0] != '\0'; index++)
  {
    if (string_compare (environment[index].key, argument[1]) == 0)
    {
      string_copy (environment[index].value, argument[2]);
      break;
    }
  }

  /* FIXME: Rewrite this to a bintree or whatever suitable... */

  if (index == 16)
  {
    /* Okay, this is a new entry in the environment. Find an empty
       spot. */

    for (index = 0; index < 16 && environment[index].key[0] != '\0'; index++);

    if (index == 16)
    {
      console_print (&console_structure, 
                     "No space left in the environment. Please kill some dolphins.\n");
      return;
    }

    string_copy (environment[index].key, argument[1]);
    string_copy (environment[index].value, argument[2]);
  }
  else if (environment[index].key[0] == '\0')
  {
    string_copy (environment[index].key, argument[1]);
    string_copy (environment[index].value, argument[2]);
  }
}

/* Show the environmental variables. */

void command_show (int number_of_arguments,
                   char *argument[] __attribute__ ((unused)))
{
  int index;

  if (number_of_arguments != 1)
  {
    console_print_formatted (&console_structure, 
                             "Wrong number of arguments! Try 'help %s'.\n",
                             argument[0]);
    return;
  }

  console_print_formatted (&console_structure, "  %-16s Value\n", "Key");
  for (index = 0; index < 16 && environment[index].key[0] != '\0'; index++)
  {
    console_print_formatted (&console_structure, 
                             "  %-16s %s\n", environment[index].key, 
                             environment[index].value);
  }
}

/* Show the contents of the given file. */

void command_show_file (int number_of_arguments,
                        char *argument[])
{
  file_handle_type handle;
  u8 *buffer;
  file_verbose_directory_entry_type directory_entry;
  u32 read_bytes = 0;

  if (number_of_arguments != 2)
  {
    console_print_formatted (&console_structure, 
                             "Wrong number of arguments! Try 'help %s'.\n",
                             argument[0]);
    return;
  }

  memory_allocate ((void **) &buffer, VFS_BUFFER_SIZE);

  if (argument[1][0] == '.' && argument[1][1] == '/')
  {
    string_copy (directory_entry.path_name, working_directory);    
    string_append (directory_entry.path_name, argument[1] + 1);    
  }
  else
  {
    string_copy (directory_entry.path_name, argument[1]);
  }
  console_print_formatted (&console_structure, "Absolute path is %s'.\n",
			   directory_entry.path_name);

  if (file_get_info (&vfs_structure, &directory_entry) != FILE_RETURN_SUCCESS)
  {
    console_print_formatted (&console_structure, 
                             "Could not get information about file %s.\n",
                             argument[1]);
    memory_deallocate ((void **) &buffer);
    return;
  }

  if (file_open (&vfs_structure, argument[1], FILE_MODE_READ, &handle) 
      != FILE_RETURN_SUCCESS)
  {
    console_print_formatted (&console_structure, 
                             "Could not open file %s.\n",
                             argument[1]);
    memory_deallocate ((void **) &buffer);
    return;
  }

  /* Read the file, in blocks of 4 Kbytes. */

  while (read_bytes < directory_entry.size)
  {
    unsigned int bytes = directory_entry.size - read_bytes;

    if (bytes > VFS_BUFFER_SIZE)
    {
      bytes = VFS_BUFFER_SIZE;
    }
    read_bytes += bytes;
    file_read (&vfs_structure, handle, bytes, buffer);
    buffer[bytes] = '\0';
    console_print (&console_structure, buffer);
  }

  memory_deallocate ((void **) &buffer);
}

/* Shut down all running processes. */

void command_shutdown (int number_of_arguments __attribute__ ((unused)),
                       char **argument __attribute__ ((unused)))
{
  /* FIXME: Let the console server handle longer messages. */

  console_clear (&console_structure);
  console_print (&console_structure, "\
\e[2J\e[37;44m







                                 \e[34;47m chaos 2000 \e[37;44m");
  console_print (&console_structure, "\n
    \e[1;37mA fatal exception 0E has occured at 0028:080054f3 in VXD VMM(01) +
    \e[1;37mC0CAC01A. The current application will be terminated.

");

  console_print (&console_structure, "\
    \e[1;37m*  Press any key to terminate the current application.
    \e[1;37m*  Press CTRL+ALT+DEL aga1in to restart the computer. You will
    \e[1;37m   lose any unsaved information in all applications");
  console_print (&console_structure, "\
                                                                                
                             \e[1;37mPress any key to continue");
  while (TRUE);
}

/* Sleep for a given number of seconds. */

void command_sleep (int number_of_arguments, char *argument[])
{
  int seconds;

  if (number_of_arguments != 2)
  {
    console_print_formatted (&console_structure, 
                             "Wrong number of arguments! Try 'help %s'.\n",
                             argument[0]);
    return;
  }
  
  string_to_number (argument[1], &seconds, NULL);
  system_sleep (seconds * 1000);
}

/* Test command. When some functionality of storm, the libraries, the
   Universe, or whatever is a little untested, test it in this
   function. Nothing stays here forever. */

void command_test (int number_of_arguments __attribute__ ((unused)),
                   char *argument[] __attribute__ ((unused)))
{
  ipv4_socket_id_type socket_id;
  ipv4_send_type *ipv4_send;
  ipv4_connect_type ipv4_connect;
  u8 tftp_request[] = "\x00\x01/mnt/chaos/programs/cluido/cluido.gz\x00octet";
  u8 *buffer;
  unsigned int length;
  
  ipv4_connect.port = 69;
  ipv4_connect.address = 192 + (168 << 8) + (1 << 16) + (234 << 24);
  ipv4_connect.protocol = IPC_IPV4_PROTOCOL_UDP;

  network_connect (&network_structure, &ipv4_connect, &socket_id);
  memory_allocate ((void **) &ipv4_send, 
                   sizeof (ipv4_send_type) + sizeof (tftp_request));
  memory_allocate ((void **) &buffer, 512);
  ipv4_send->length = sizeof (tftp_request);
  memory_copy (ipv4_send->data, tftp_request, sizeof (tftp_request));
  ipv4_send->socket_id = socket_id;
  console_print_formatted (&console_structure, "%u\n", ipv4_send->socket_id);
  network_send (&network_structure, ipv4_send);
  network_receive (&network_structure, socket_id, (void **) &buffer, &length);
  console_print_formatted (&console_structure, "Got an UDP response");
  // memory_deallocate ((void **) &ipv4_send);
}

/* Show information about running threads. */

void command_threads (int number_of_arguments __attribute__ ((unused)),
                      char **argument __attribute__ ((unused)))
{
  kernelfs_process_info_type kernelfs_process_info;
  kernelfs_thread_info_type kernelfs_thread_info;
  u32 processes = KERNELFS_CLASS_PROCESS_AMOUNT;

  system_call_kernelfs_entry_read (&processes);
  console_print (&console_structure, "PROCESS_ID THREADS NAME\n");
  kernelfs_process_info.kernelfs_class = KERNELFS_CLASS_PROCESS_INFO;
  kernelfs_thread_info.kernelfs_class = KERNELFS_CLASS_THREAD_INFO;

  for (kernelfs_process_info.process_number = 0;
       kernelfs_process_info.process_number < processes; 
       kernelfs_process_info.process_number++)
  {
    system_call_kernelfs_entry_read (&kernelfs_process_info);
    console_print_formatted (&console_structure, "%-10lu %-7u %s.\n",
                             kernelfs_process_info.process_id,
                             kernelfs_process_info.number_of_threads,
                             kernelfs_process_info.name);
 
    kernelfs_thread_info.process_id = kernelfs_process_info.process_id;
    for (kernelfs_thread_info.thread_number = 0;
         kernelfs_thread_info.thread_number <
           kernelfs_process_info.number_of_threads;
         kernelfs_thread_info.thread_number++)
    {
      system_call_kernelfs_entry_read (&kernelfs_thread_info);
      console_print_formatted (&console_structure, 
                               "           %-7lu %s (%s)\n",
                               kernelfs_thread_info.thread_id,
                               kernelfs_thread_info.name,
                               kernelfs_thread_info.state);
    }
  }
}

/* Show the current time. */

void command_time (int number_of_arguments __attribute__ ((unused)),
                   char *argument[] __attribute__ ((unused)))
{
  kernelfs_time_type kernelfs_time;
  unsigned int hours, minutes, seconds;

  kernelfs_time.kernelfs_class = KERNELFS_CLASS_TIME_READ;
  system_call_kernelfs_entry_read (&kernelfs_time);

  hours = time_to_hours (kernelfs_time.time);
  minutes = time_to_minutes (kernelfs_time.time);
  seconds = time_to_seconds (kernelfs_time.time);

  console_print_formatted (&console_structure, "Current time: %02u:%02u:%02u\n", hours, minutes, 
                           seconds);
}

/* Top of Earth. */

void command_top (int number_of_arguments __attribute__ ((unused)),
                  char *argument[] __attribute__ ((unused)))
{
  kernelfs_process_info_type kernelfs_process_info;
  kernelfs_thread_info_verbose_type kernelfs_thread_info;
  u32 processes = KERNELFS_CLASS_PROCESS_AMOUNT;

  system_call_kernelfs_entry_read (&processes);
  console_print_formatted (&console_structure, 
                           "%-8s %-8s %-8s %-8s %-8s %-15s %-15s\n",
                           "Process", "Thread", "Time", "Memory", "IP",
                           "Process name", "Thread name");
  kernelfs_process_info.kernelfs_class = KERNELFS_CLASS_PROCESS_INFO;
  kernelfs_thread_info.kernelfs_class = KERNELFS_CLASS_THREAD_INFO_VERBOSE;

  for (kernelfs_process_info.process_number = 0;
       kernelfs_process_info.process_number < processes; 
       kernelfs_process_info.process_number++)
  {
    system_call_kernelfs_entry_read (&kernelfs_process_info);
    kernelfs_thread_info.process_id = kernelfs_process_info.process_id;

    for (kernelfs_thread_info.thread_number = 0;
         kernelfs_thread_info.thread_number <
           kernelfs_process_info.number_of_threads;
         kernelfs_thread_info.thread_number++)
    {
      system_call_kernelfs_entry_read (&kernelfs_thread_info);
      kernelfs_thread_info.process_name[15] = '\0';
      kernelfs_thread_info.thread_name[15] = '\0';
      console_print_formatted (&console_structure, 
                               "%-8lu %-8lu %-8lu %-8lu %08lX %-15s %-15s\n",
                               kernelfs_thread_info.process_id,
                               kernelfs_thread_info.thread_id,
                               (u32) kernelfs_thread_info.timeslices,
                               kernelfs_thread_info.main_memory / 1024,
                               /* kernelfs_thread_info.stack_memory / 1024, */
                               kernelfs_thread_info.instruction_pointer,
                               kernelfs_thread_info.process_name,
                               kernelfs_thread_info.thread_name);
    }
  }
}

/* Unset an environment variable. */

void command_unset (int number_of_arguments,
                    char *argument[])
{
  int index;
  int highest;
  int match = -1;

  if (number_of_arguments != 2)
  {
    console_print_formatted (&console_structure, 
                             "Wrong number of arguments! Try 'help %s'.\n",
                             argument[0]);
    return;
  }

  for (index = 0; index < 16 && environment[index].key[0] != '\0'; index++)
  {
    if (string_compare (environment[index].key, argument[1]) == 0)
    {
      match = index;
    }
  }

  highest = (index > 0 ? index - 1 : index);
  if (match == -1)
  {
    console_print (&console_structure, 
                   "The environment variable you tried to unset wasn't set.\n");
    return;
  }

  /* We have two cases to handle here. If this entry is the last, we
     just delete it. Otherwise, we move the last entry to this
     position and set the last as free. */

  if (highest == match)
  {
    environment[match].key[0] = '\0';
  }
  else
  {
    memory_copy (&environment[match], &environment[highest],
                 sizeof (environment_type));
    environment[highest].key[0] = '\0';
  }
}

/* Show the current uptime. */

void command_uptime (int number_of_arguments __attribute__ ((unused)),
                     char **argument __attribute__ ((unused)))
{
  u32 uptime = KERNELFS_CLASS_UPTIME_INFO;
  u32 days, hours, minutes, seconds;
  
  system_call_kernelfs_entry_read (&uptime);

  days = uptime / 86400;
  uptime %= 86400;

  hours = uptime / 3600;
  uptime %= 3600;
  
  minutes = uptime / 60;
  uptime %= 60;
  
  seconds = uptime;
    
  if (days > 0)
  {
    console_print_formatted (&console_structure, 
                             "System uptime: %lu days, %lu hours,"
                             " %lu minutes and %lu seconds.\n",
                             days, hours, minutes, seconds);
  }
  else
  {
    console_print_formatted (&console_structure, 
                             "System uptime: %lu hours, %lu minutes"
                             " and %lu seconds.\n",
                             hours, minutes, seconds);
  }
}

#define SEGMENTS 10
#define SECTIONS 10  
  
void command_torus (int number_of_arguments __attribute__ ((unused)),
                    char **argument __attribute__ ((unused)))
{
  double index = 0;
  int x, y;
  u8 *screen = (u8 *) 0xA0000;

  //  int vertex[SEGMENTS][SECTIONS];

  /* Create a torus. */

  if (console_mode_set (&console_structure, WIDTH, HEIGHT, DEPTH,
                        VIDEO_MODE_TYPE_GRAPHIC) != CONSOLE_RETURN_SUCCESS)
  {
    return;
  }

  memory_set_u8 (screen, 0, WIDTH * HEIGHT);
  
  for (index = 0; index < 100; index += 0.001)
  {
    x = (WIDTH / 2) + index * math_cosine (index);
    y = (HEIGHT / 2) + index * math_sine (index);

    screen[y * WIDTH + x] = 0xff;
  }
}

/* Shows the version of storm and cluido. */

void command_version (int number_of_arguments __attribute__ ((unused)),
                      char **argument __attribute__ ((unused)))
{
  kernelfs_storm_info_type storm_info;

  storm_info.kernelfs_class = KERNELFS_CLASS_STORM_INFO;
  system_call_kernelfs_entry_read (&storm_info);

  console_print_formatted (&console_structure, "storm version %s\n",
                           storm_info.version);
  console_print_formatted (&console_structure, "%s version %s\n",
                           PACKAGE_NAME, PACKAGE_VERSION);
}
