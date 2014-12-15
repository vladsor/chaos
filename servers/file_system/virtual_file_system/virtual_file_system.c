/* $Id: virtual_file_system.c,v 1.2 2000/10/03 22:17:51 plundis Exp $ */
/* Abstract: Virtual File System (VFS) server for chaos. This server
   abstracts all file system servers into one generic interface. The
   Virtual File System protocol is actually merely a superset of the
   File System interface (as understood by the specific file system
   servers). */
/* Author: Per Lundberg <plundis@chaosdev.org> */

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

#include <console/console.h>
#include <log/log.h>
#include <ipc/ipc.h>
#include <memory/memory.h>
#include <string/string.h>

#include "config.h"
#include "virtual_file_system.h"

/* This array holds the list of mounted file systems and their
   services. Some stuff is always present. */
/* FIXME: Make this a linked list. */

mount_point_type mount_point[MAX_VOLUMES] =
{
  { "", "VFS", TRUE, { MAILBOX_ID_NONE, MAILBOX_ID_NONE } },
};

unsigned int mounted_volumes = 1;
assign_point_type assign_point[MAX_ASSIGNS];

#define ROOT_ENTRIES (sizeof (root) / sizeof (file_system_directory_entry_type))

static char *slash = (char *) "/";

static log_structure_type log_structure;

/* FIXME: Linked list for this. */

static unsigned int file_handle[MAX_FILE_HANDLES];
static unsigned int number_of_file_handles = 0;

static tag_type empty_tag =
{
  0, 0, ""
};

/* Split a path name to its components. */

static void path_split (char *path_name, char **output, unsigned int *elements)
{
  unsigned int index = 0;
  unsigned int output_index = 0;

  if (path_name[0] == '/')
  {
    /* Are we at the meta root? */

    if (path_name[1] == '/')
    {
      output[0] = &path_name[2];
      output_index = 1;
      index = 2;
    }
    else
    {
      output[0] = slash;
      output[1] = &path_name[1];
      index = 2;
      output_index += 2;
    }
  }

  while (path_name[index] != '\0' && output_index < *elements)
  {
    if (path_name[index] == PATH_NAME_SEPARATOR &&
        path_name[index + 1] != '\0')
    {
      path_name[index] = '\0';
      output[output_index] = &path_name[index + 1];
      output_index++;
    }
    index++;
  }
  *elements = output_index;
}

/* Initialise the VFS system. */

static bool vfs_init (ipc_structure_type *ipc_structure)
{
  system_process_name_set (PACKAGE_NAME);
  system_thread_name_set ("Initialising");

  log_init (&log_structure, PACKAGE_NAME, &empty_tag);

  memory_set_u8 ((u8 *) assign_point, 0, sizeof (assign_point));

  if (ipc_service_create ("virtual_file_system", ipc_structure, 
                          &empty_tag) != IPC_RETURN_SUCCESS)
  {
    system_call_debug_print_simple ("Couldn't create virtual_file_system service.");
    return FALSE;
  }
  else
  {
    return TRUE;
  }
}

/* Get the volume number for the given path. */

static int get_volume (char **outpath, char *inpath, unsigned int *elements)
{
  unsigned int index;
  unsigned int volume;

  path_split (inpath, outpath, elements);

  /* We got an empty string. Not very fun, indeed. */

  if (*elements == 0)
  {
    return -1;
  }

  if (string_compare (outpath[0], "/") == 0)
  {
    for (index = 0; assign_point[index].location[0] != 0; index++)
    {
      if (string_compare (assign_point[index].location, "/") == 0)
      {
        outpath[0] =
          (char *) &mount_point[assign_point[index].volume].location;
      }
    }

    if (assign_point[index].location[0] == '\0')
    {
      log_print (&log_structure, LOG_URGENCY_DEBUG, "assign_point[index].location[0] == 0");
      return -1;
    }
  }

  /* Now, find out which service to contact about this file system. */

  for (volume = 0; volume < mounted_volumes; volume++)
  {
    if (string_compare (outpath[0], mount_point[volume].location) == 0)
    {
      break;
    }
  }  

  return volume;
}

/* Read directory entries from one of the file systems in this VFS. */
/* FIXME: Much of this code should be put in a 'meta'-function to be
   called by both this and vfs_file_get_info () */

static bool vfs_directory_entry_read
  (file_directory_entry_read_type *directory_entry_read)
{
  unsigned int elements = MAX_PATH_ELEMENTS;
  char *path[MAX_PATH_ELEMENTS];
  //  unsigned int element;
  //  bool done = FALSE;
  unsigned int index;
  unsigned int volume;

  volume = get_volume (path, directory_entry_read->path_name, &elements);

  if (volume == mounted_volumes ||
      volume == (unsigned int) -1)
  {
    log_print (&log_structure, LOG_URGENCY_DEBUG,
               "volume == mounted_volumes");
    return FALSE;
  }

  /* An external file system? */

  if (mount_point[volume].ipc_structure.output_mailbox_id != MAILBOX_ID_NONE)
  {
    message_parameter_type message_parameter;
    char path_name[MAX_PATH_NAME_LENGTH];

    memory_set_u8 (path_name, 0, MAX_PATH_NAME_LENGTH);

    for (index = 1; index < elements; index++)
    {
      string_print (path_name + string_length (path_name), "/%s",
                    path[index]);
    }

    string_copy (directory_entry_read->path_name, path_name);

    message_parameter.protocol = IPC_PROTOCOL_FILE_SYSTEM;
    message_parameter.message_class = IPC_FILE_SYSTEM_DIRECTORY_ENTRY_READ;
    message_parameter.length = sizeof (file_directory_entry_read_type);
    message_parameter.data = directory_entry_read;
    message_parameter.block = TRUE;
    ipc_send (mount_point[volume].ipc_structure.output_mailbox_id,
              &message_parameter);
    
    /* FIXME: This should be 
       sizeof (file_system_directory_entry_read_type) +
       (sizeof (file_system_directory_entry_type) *
        directory_entry_read->entries) */

    message_parameter.length = 16384;
    ipc_receive (mount_point[volume].ipc_structure.input_mailbox_id,
                 &message_parameter, NULL);
  }
  else
  {
    switch (volume)
    {
      /* Meta-root filesystem */

      case 0:
      {
        unsigned int input_index;
        unsigned int output_index = 0;
        unsigned int max_entries = directory_entry_read->entries;
        
        directory_entry_read->entries = 0;

        for (input_index = directory_entry_read->start_entry;
             (input_index < (directory_entry_read->start_entry + max_entries) &&
              input_index < mounted_volumes - 1); input_index++)
        {
          string_copy 
            (directory_entry_read->entry[output_index].name,
             mount_point[input_index + 1].location);
          directory_entry_read->entry[output_index].type = 
            FILE_ENTRY_TYPE_DIRECTORY;
          directory_entry_read->entries++;
          output_index++;
        }

        if (input_index == mounted_volumes - 1)
        {
          directory_entry_read->end_reached = TRUE;
        }
        else
        {
          directory_entry_read->end_reached = FALSE;
        }

        break;
      }

      /* Services. */

      case 2:
      {
        log_print (&log_structure, LOG_URGENCY_WARNING,
                   "Reading from services (unimplemented).");
        directory_entry_read->entries = 0;
        directory_entry_read->end_reached = TRUE;
        break;
      }
    }
  }

  return TRUE;
}

/* Get information about the given directory entry. */

static void vfs_file_get_info (file_verbose_directory_entry_type 
                               *directory_entry)
{
  unsigned int elements = MAX_PATH_ELEMENTS;
  char *path[MAX_PATH_ELEMENTS];
  unsigned int index;
  unsigned int volume;

  volume = get_volume (path, directory_entry->path_name, &elements);

  if (volume == mounted_volumes ||
      volume == (unsigned int) -1)
  {
    directory_entry->success = FALSE;
    return;
  }

  if (elements == 1)
  {
    volume = 0;
  }

  /* An external file system? */

  if (mount_point[volume].ipc_structure.output_mailbox_id != MAILBOX_ID_NONE)
  {
    message_parameter_type message_parameter;
    char path_name[MAX_PATH_NAME_LENGTH];

    memory_set_u8 (path_name, 0, MAX_PATH_NAME_LENGTH);

    for (index = 1; index < elements; index++)
    {
      string_print (path_name + string_length (path_name), "/%s",
                    path[index]);
    }

    string_copy (directory_entry->path_name, path_name);

    message_parameter.protocol = IPC_PROTOCOL_FILE_SYSTEM;
    message_parameter.message_class = IPC_FILE_SYSTEM_FILE_GET_INFO;
    message_parameter.length = sizeof (file_verbose_directory_entry_type);
    message_parameter.data = directory_entry;
    message_parameter.block = TRUE;
    ipc_send (mount_point[volume].ipc_structure.output_mailbox_id,
              &message_parameter);

    /* FIXME: Should be 
       sizeof (file_system_directory_entry_read_type) +
       (sizeof (file_system_directory_entry_type) *
       directory_entry_read->entries) */

    message_parameter.length = 16384;

    ipc_receive (mount_point[volume].ipc_structure.input_mailbox_id,
                 &message_parameter, NULL);

    if (message_parameter.message_class == IPC_FILE_SYSTEM_RETURN_VALUE)
    {
      log_print (&log_structure, LOG_URGENCY_DEBUG,
                 "IPC_FILE_SYSTEM_GET_INFO failed.");
      directory_entry->success = FALSE;
    }
  }
  else
  {
    switch (volume)
    {
      /* Meta-root filesystem */

      case 0:
      {
        unsigned int input_index;
        
        for (input_index = 0; input_index < mounted_volumes; input_index++)
        {
          /* Did we got a match? */

          if (string_compare (path[0], mount_point[input_index].location) == 0)
          {
            directory_entry->type = FILE_ENTRY_TYPE_DIRECTORY;
            directory_entry->size = 0;

            /* FIXME */

            directory_entry->time = 42;
            break;
          }
        }

        /* Did the file not exist? */

        if (input_index == mounted_volumes)
        {
          directory_entry->success = FALSE;
          return;
        }

        break;
      }

      /* Services. */

      case 2:
      {
        log_print (&log_structure, LOG_URGENCY_DEBUG,
                   "Reading from services.");
        break;
      }
    }
    directory_entry->success = TRUE;
  }
}

/* Opens the given file and assigns a file handle. */
/* FIXME: This function must be mutexed, so we get unique file handles. */

static bool vfs_file_open (file_open_type *open,
                           file_handle_type *handle) __attribute__ ((unused));

static bool vfs_file_open (file_open_type *open,
                           file_handle_type *handle)
{
  unsigned int elements = MAX_PATH_ELEMENTS;
  char *path[MAX_PATH_ELEMENTS];
  unsigned int volume;
  unsigned int index;

  *handle = number_of_file_handles;
  volume = get_volume (path, open->file_name, &elements);

  if (volume == mounted_volumes ||
      volume == (unsigned int) -1)
  {
    return FALSE;
  }

  /* If this path only consists of one element, it is wrong, since we
     have no files in the root. */

  if (elements == 1)
  {
    return FALSE;
  }

  /* An external file system? */

  if (mount_point[volume].ipc_structure.output_mailbox_id != MAILBOX_ID_NONE)
  {
    message_parameter_type message_parameter;
    char path_name[MAX_PATH_NAME_LENGTH];
    ipc_file_system_open_type file_system_open;
    
    memory_set_u8 (path_name, 0, MAX_PATH_NAME_LENGTH);

    /* FIXME: Copy away the path name before splitting it to avoid
       having to unsplit it... */

    for (index = 1; index < elements; index++)
    {
      string_print (path_name + string_length (path_name), "/%s",
                    path[index]);
    }

    string_copy (file_system_open.file_name, path_name);
    file_system_open.mode = open->mode;
    file_system_open.file_handle = *handle;

    message_parameter.protocol = IPC_PROTOCOL_FILE_SYSTEM;
    message_parameter.message_class = IPC_FILE_SYSTEM_FILE_OPEN;
    message_parameter.length = sizeof (ipc_file_system_open_type);
    message_parameter.data = &file_system_open;
    message_parameter.block = TRUE;
    ipc_send (mount_point[volume].ipc_structure.output_mailbox_id,
              &message_parameter);

    /* FIXME: This should be something else. */

    message_parameter.length = 16384;

    if (ipc_receive (mount_point[volume].ipc_structure.input_mailbox_id,
                     &message_parameter, NULL) != IPC_RETURN_SUCCESS)
    {
      return FALSE;
    }
  }
  else
  {
    switch (volume)
    {
      /* Meta-root filesystem */

      case 0:
      {
        /* No files here, sir. */
        
        return FALSE;
      }
    }
  }

  file_handle[number_of_file_handles] = volume;
  number_of_file_handles++;
  return TRUE;
}

/* Read from the given file handle. */

static bool vfs_file_read (file_read_type *read, void *buffer)
{
  message_parameter_type message_parameter;
  unsigned int volume;

  if (read->file_handle + 1 > number_of_file_handles)
  {
    return FALSE;
  }

  /* Is this a file system handled by the VFS server itself? */

  volume = file_handle[read->file_handle];

  if (mount_point[volume].ipc_structure.output_mailbox_id ==
      MAILBOX_ID_NONE)
  {
    return FALSE;
  }

  message_parameter.data = read;
  message_parameter.length = sizeof (file_read_type);
  message_parameter.protocol = IPC_PROTOCOL_FILE_SYSTEM;
  message_parameter.message_class = IPC_FILE_SYSTEM_FILE_READ;
  message_parameter.block = TRUE;

  ipc_send (mount_point[volume].ipc_structure.output_mailbox_id,
            &message_parameter);

  /* Get the data. */

  message_parameter.length = read->bytes;
  message_parameter.data = buffer;
  if (ipc_receive (mount_point[volume].ipc_structure.input_mailbox_id,
                   &message_parameter, NULL) != IPC_RETURN_SUCCESS)
  {
    return FALSE;
  }
  else
  {
    return TRUE;
  }
}

/* Mount the given service at the given location. */

static bool vfs_mount (virtual_file_system_mount_type *mount)
{
  mailbox_id_type mailbox_id[10];
  message_parameter_type message_parameter;
  unsigned int services = 10;

  /* Detect the file system type of this volume. We do this by
     resolving all "file_system" services and try to do a mount on 'em. */

  if (ipc_service_resolve ("file_system", mailbox_id, &services, 5, 
                           &empty_tag) != IPC_RETURN_SUCCESS)
  {
    log_print (&log_structure, LOG_URGENCY_ERROR,
               "Couldn't resolve any file system services.");
    return FALSE;
  }

  mount_point[mounted_volumes].ipc_structure.output_mailbox_id = mailbox_id[0];
  if (ipc_service_connection_request
      (&mount_point[mounted_volumes].ipc_structure) != IPC_RETURN_SUCCESS)
  {
    log_print (&log_structure, LOG_URGENCY_ERROR,
               "Failed to establish connection to file system service.");
    return FALSE;
  }

  /* Tell this file system to mount it. */
  
  message_parameter.protocol = IPC_PROTOCOL_FILE_SYSTEM;
  message_parameter.message_class = IPC_FILE_SYSTEM_MOUNT;
  message_parameter.length = sizeof (mailbox_id_type);
  message_parameter.data = &mount->mailbox_id;
  message_parameter.block = TRUE;
  if (ipc_send (mount_point[mounted_volumes].ipc_structure.output_mailbox_id,
                &message_parameter) != IPC_RETURN_SUCCESS)
  {
    log_print_formatted
      (&log_structure, LOG_URGENCY_ERROR,
       "Couldn't mount file system through service %u.",
       mount_point[mounted_volumes].ipc_structure.output_mailbox_id);
    return FALSE;
  }

  mount_point[mounted_volumes].handled_by_vfs = FALSE;
  string_copy_max (mount_point[mounted_volumes].location,
                   mount->location, MAX_PATH_NAME_LENGTH);
  mounted_volumes++;

  log_print_formatted (&log_structure, LOG_URGENCY_INFORMATIVE,
                       "Mounting mailbox ID %u at //%s.",
                       mount->mailbox_id, mount->location);
  return TRUE;
}

/* Assign the meta-mounted volume a place in the UNIX-wannabe tree. */

static bool vfs_assign (virtual_file_system_assign_type *assign __attribute__ ((unused)))
{
  return FALSE;
}

/* Handle an IPC connection request. */

static void handle_connection (mailbox_id_type reply_mailbox_id)
{
  message_parameter_type message_parameter;
  ipc_structure_type ipc_structure;
  bool done = FALSE;
  u8 *data;
  unsigned int data_size = 16384;

  memory_allocate ((void **) &data, data_size);

  /* Accept the connection. */ 

  ipc_structure.output_mailbox_id = reply_mailbox_id;
  ipc_connection_establish (&ipc_structure);
  
  message_parameter.block = TRUE;
    
  while (!done)
  {
    message_parameter.protocol = IPC_PROTOCOL_VIRTUAL_FILE_SYSTEM;
    message_parameter.message_class = IPC_CLASS_NONE;
    message_parameter.length = data_size;
    message_parameter.data = data;
  
    if (ipc_receive (ipc_structure.input_mailbox_id, &message_parameter,
                     &data_size) != IPC_RETURN_SUCCESS)
    {
      log_print_formatted (&log_structure, LOG_URGENCY_ERROR,
                           "Failed to read from mailbox %u",
                           ipc_structure.input_mailbox_id);
      while (TRUE);
      continue;
    }

    switch (message_parameter.message_class)
    {
      case IPC_VIRTUAL_FILE_SYSTEM_DIRECTORY_ENTRY_READ:
      {
        file_directory_entry_read_type *directory_entry_read =
          (file_directory_entry_read_type *) data;

        if (!vfs_directory_entry_read (directory_entry_read))
        {
          log_print_formatted (&log_structure, LOG_URGENCY_ERROR,
                               "Couldn't read a directory entry.");
          directory_entry_read->entries = 0;
        }
        message_parameter.length =
          (sizeof (file_directory_entry_read_type) +
           sizeof (file_directory_entry_type) * 
           directory_entry_read->entries);
        ipc_send (ipc_structure.output_mailbox_id, &message_parameter);
        break;
      }

      case IPC_VIRTUAL_FILE_SYSTEM_FILE_GET_INFO:
      {
        file_verbose_directory_entry_type *directory_entry =
          (file_verbose_directory_entry_type *) data;

        vfs_file_get_info (directory_entry);
        ipc_send (ipc_structure.output_mailbox_id, &message_parameter);
        break;
      }

      case IPC_VIRTUAL_FILE_SYSTEM_MOUNT:
      {
        virtual_file_system_mount_type *mount =
          (virtual_file_system_mount_type *) data;

        vfs_mount (mount);
        break;
      }

      case IPC_VIRTUAL_FILE_SYSTEM_ASSIGN:
      {
        virtual_file_system_assign_type *assign = 
          (virtual_file_system_assign_type *) data;

        vfs_assign (assign);
        break;
      }

      case IPC_VIRTUAL_FILE_SYSTEM_FILE_OPEN:
      {
        file_open_type *open = (file_open_type *) data;
        file_handle_type handle = 42;

        vfs_file_open (open, &handle);
        message_parameter.data = &handle;
        message_parameter.length = sizeof (file_handle_type);
        ipc_send (ipc_structure.output_mailbox_id, &message_parameter);
        break;
      }

      case IPC_VIRTUAL_FILE_SYSTEM_FILE_READ:
      {
        file_read_type *read = (file_read_type *) data;
        u8 *buffer;

        memory_allocate ((void **) &buffer, read->bytes);

        if (!vfs_file_read (read, buffer))
        {
          log_print (&log_structure, LOG_URGENCY_ERROR, 
                     "Failed to read file.");
          message_parameter.length = 0;
        }
        else
        {
          message_parameter.length = read->bytes;
        }
        message_parameter.data = buffer;
        ipc_send (ipc_structure.output_mailbox_id, &message_parameter);
        memory_deallocate ((void **) &buffer);
        break;
      }

      case IPC_VIRTUAL_FILE_SYSTEM_FILE_CLOSE:
      case IPC_VIRTUAL_FILE_SYSTEM_FILE_SEEK:
      case IPC_VIRTUAL_FILE_SYSTEM_FILE_WRITE:
      case IPC_VIRTUAL_FILE_SYSTEM_ACL_READ:
      case IPC_VIRTUAL_FILE_SYSTEM_ACL_WRITE:
      case IPC_VIRTUAL_FILE_SYSTEM_UNMOUNT:
      case IPC_VIRTUAL_FILE_SYSTEM_DEASSIGN:
      case IPC_VIRTUAL_FILE_SYSTEM_DETECT:
      default:
      {
        /* Yet unsupported calls. */

        log_print_formatted (&log_structure, LOG_URGENCY_ERROR,
                             "Unsupported message class (%u).",
                             message_parameter.message_class);
        break;
      }
    }
  }
}

/* Main function. */

int main (void)
{
  ipc_structure_type ipc_structure;

  if (!vfs_init (&ipc_structure))
  {
    return 1;
  }

  system_call_process_parent_unblock ();

  /* Main loop. */

  system_thread_name_set ("Service handler");
  while (TRUE)
  {
    mailbox_id_type reply_mailbox_id;

    ipc_service_connection_wait (&ipc_structure);
    reply_mailbox_id = ipc_structure.output_mailbox_id;

    if (system_thread_create () == SYSTEM_RETURN_THREAD_NEW)
    {
      system_thread_name_set ("Handling connection");
      handle_connection (reply_mailbox_id);
    }
  }    
}
