#include <enviroment.h>

#include <stdio.h>

#include <Classes/console.h>
#include <Interfaces/input_stream.h>
#include <Interfaces/output_stream.h>
#include <Classes/integer.h>

#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#include <debug/macros.h>

handle_t file_handles[100];
int last_fileno = 3;
char current_directory[256] = "/";

FILE  __stdin__ = 
{
//  int _flags;		/* High-order word is _IO_MAGIC; rest is flags. */
    0,

  /* The following pointers correspond to the C++ streambuf protocol. */
  /* Note:  Tk uses the _IO_read_ptr and _IO_read_end fields directly. */
//  char* _IO_read_ptr;	/* Current read pointer */
    NULL,

//  char* _IO_read_end;	/* End of get area. */
    NULL,
    
//  char* _IO_read_base;	/* Start of putback+get area. */
    NULL,
    
//  char* _IO_write_base;	/* Start of put area. */
    NULL,
    
//  char* _IO_write_ptr;	/* Current put pointer. */
    NULL,
    
//  char* _IO_write_end;	/* End of put area. */
    NULL,
    
//  char* _IO_buf_base;	/* Start of reserve area. */
    NULL,
    
//  char* _IO_buf_end;	/* End of reserve area. */
    NULL,
    
  /* The following fields are used to support backing up and undo. */
//  char *_IO_save_base; /* Pointer to start of non-current get area. */
    NULL,
    
//  char *_IO_backup_base;  /* Pointer to first valid character of backup area */
    NULL,
    
//  char *_IO_save_end; /* Pointer to end of non-current get area. */
    NULL,

//  struct _IO_marker *_markers;
    NULL,

//  struct _IO_FILE *_chain;
    NULL,

//  int _fileno;
    0,
    
//  int _blksize;
    0,
    
//  _IO_off_t _old_offset; /* This used to be _offset but it's too small.  */
    0,

  /* 1+column number of pbase(); 0 is unknown. */
//  unsigned short _cur_column;
    0,
  
//  signed char _vtable_offset;
    0,
  
//  char _shortbuf[1];
    {0},

  /*  char* _save_gptr;  char* _save_egptr; */

//  _IO_lock_t *_lock;
    NULL,

//  _IO_off64_t _offset;
    0,
    
//  void *__pad1;
    NULL,
//  void *__pad2;
    NULL,

//  int _mode;
    0,

  /* Make sure we don't get into trouble again.  */
//  char _unused2[15 * sizeof (int) - 2 * sizeof (void *)];
  {
    0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,
  }
};

FILE  __stdout__ = 
{
//  int _flags;		/* High-order word is _IO_MAGIC; rest is flags. */
    0,

  /* The following pointers correspond to the C++ streambuf protocol. */
  /* Note:  Tk uses the _IO_read_ptr and _IO_read_end fields directly. */
//  char* _IO_read_ptr;	/* Current read pointer */
    NULL,

//  char* _IO_read_end;	/* End of get area. */
    NULL,
    
//  char* _IO_read_base;	/* Start of putback+get area. */
    NULL,
    
//  char* _IO_write_base;	/* Start of put area. */
    NULL,
    
//  char* _IO_write_ptr;	/* Current put pointer. */
    NULL,
    
//  char* _IO_write_end;	/* End of put area. */
    NULL,
    
//  char* _IO_buf_base;	/* Start of reserve area. */
    NULL,
    
//  char* _IO_buf_end;	/* End of reserve area. */
    NULL,
    
  /* The following fields are used to support backing up and undo. */
//  char *_IO_save_base; /* Pointer to start of non-current get area. */
    NULL,
    
//  char *_IO_backup_base;  /* Pointer to first valid character of backup area */
    NULL,
    
//  char *_IO_save_end; /* Pointer to end of non-current get area. */
    NULL,

//  struct _IO_marker *_markers;
    NULL,

//  struct _IO_FILE *_chain;
    NULL,

//  int _fileno;
    1,
    
//  int _blksize;
    0,
    
//  _IO_off_t _old_offset; /* This used to be _offset but it's too small.  */
    0,

  /* 1+column number of pbase(); 0 is unknown. */
//  unsigned short _cur_column;
    0,
  
//  signed char _vtable_offset;
    0,
  
//  char _shortbuf[1];
    {0},

  /*  char* _save_gptr;  char* _save_egptr; */

//  _IO_lock_t *_lock;
    NULL,

//  _IO_off64_t _offset;
    0,
    
//  void *__pad1;
    NULL,
//  void *__pad2;
    NULL,

//  int _mode;
    0,

  /* Make sure we don't get into trouble again.  */
//  char _unused2[15 * sizeof (int) - 2 * sizeof (void *)];
  {
    0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,
  }
};

FILE  __stderr__ = 
{
//  int _flags;		/* High-order word is _IO_MAGIC; rest is flags. */
    0,

  /* The following pointers correspond to the C++ streambuf protocol. */
  /* Note:  Tk uses the _IO_read_ptr and _IO_read_end fields directly. */
//  char* _IO_read_ptr;	/* Current read pointer */
    NULL,

//  char* _IO_read_end;	/* End of get area. */
    NULL,
    
//  char* _IO_read_base;	/* Start of putback+get area. */
    NULL,
    
//  char* _IO_write_base;	/* Start of put area. */
    NULL,
    
//  char* _IO_write_ptr;	/* Current put pointer. */
    NULL,
    
//  char* _IO_write_end;	/* End of put area. */
    NULL,
    
//  char* _IO_buf_base;	/* Start of reserve area. */
    NULL,
    
//  char* _IO_buf_end;	/* End of reserve area. */
    NULL,
    
  /* The following fields are used to support backing up and undo. */
//  char *_IO_save_base; /* Pointer to start of non-current get area. */
    NULL,
    
//  char *_IO_backup_base;  /* Pointer to first valid character of backup area */
    NULL,
    
//  char *_IO_save_end; /* Pointer to end of non-current get area. */
    NULL,

//  struct _IO_marker *_markers;
    NULL,

//  struct _IO_FILE *_chain;
    NULL,

//  int _fileno;
    2,
    
//  int _blksize;
    0,
    
//  _IO_off_t _old_offset; /* This used to be _offset but it's too small.  */
    0,

  /* 1+column number of pbase(); 0 is unknown. */
//  unsigned short _cur_column;
    0,
  
//  signed char _vtable_offset;
    0,
  
//  char _shortbuf[1];
    {0},

  /*  char* _save_gptr;  char* _save_egptr; */

//  _IO_lock_t *_lock;
    NULL,

//  _IO_off64_t _offset;
    0,
    
//  void *__pad1;
    NULL,
//  void *__pad2;
    NULL,

//  int _mode;
    0,

  /* Make sure we don't get into trouble again.  */
//  char _unused2[15 * sizeof (int) - 2 * sizeof (void *)];
  {
    0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,
  }
};

FILE *stdin = &__stdin__;		/* Standard input stream.  */
FILE *stdout = &__stdout__;		/* Standard output stream.  */
FILE *stderr = &__stderr__;		/* Standard error output stream.  */

static class_id_t console_cid;
static console_attribute_t attribute =
{
//    unsigned int width;
    80,
//    unsigned int height;
    25,
//    unsigned int depth;
    1,
//    unsigned int mode_type;
    0
};

extern void posix_init (void);
void posix_init (void)
{
    handle_t class;
    
    global_namespace_resolve ("/storm/classes/console", &class);
    register_object_open (&class, IID_INTEGER);
    integer$get (&class, &console_cid);
    register_object_close (&class);

    register_object_create (&file_handles[0], console_cid, &attribute);
    register_handle_clone (&file_handles[0], &file_handles[1], 0);
    register_handle_clone (&file_handles[0], &file_handles[2], 0);
    
    register_object_open (&file_handles[0], IID_INPUT_STREAM);
    register_object_open (&file_handles[1], IID_OUTPUT_STREAM);
    register_object_open (&file_handles[2], IID_OUTPUT_STREAM);
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%p - %p\n",
        file_handles[0].context.object_data,
        file_handles[0].context.handle_data);
}

/* Clear the error and EOF indicators for STREAM.  */
void clearerr (FILE *__stream)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);
}

/* Return the EOF indicator for STREAM.  */
int feof (FILE *__stream)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);
        
    return -1;
}

/* Return the error indicator for STREAM.  */
int ferror (FILE *__stream)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);
        
    return -1;
}

/* Close STREAM.  */
int fclose (FILE *__stream)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);
        
    return -1;
}

/* Flush STREAM, or all streams if STREAM is NULL.  */
int fflush (FILE *__stream)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p)\n",
        __FILE__, __FUNCTION__, __stream);
        
    return -1;
}

/* Create a new stream that refers to an existing system file descriptor.  */
FILE *fdopen (int __fd, __const char *__modes)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);
        
    return -1;
}

/* Get a newline-terminated string of finite length from STREAM.  */
char *fgets (char *__restrict __s, int __n, FILE *__restrict __stream)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);
        
    return NULL;
}

/* Return the system file descriptor for STREAM.  */
int fileno (FILE *__stream)
{
//    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
//        "%s::%s (%p)\n",
//        __FILE__, __FUNCTION__, __stream);
        
    return __stream->_fileno;
}

/* Open a file and create a new stream for it.  */
FILE *fopen (__const char *__restrict __filename,
		    __const char *__restrict __modes)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, %p)\n",
        __FILE__, __FUNCTION__, __filename, __modes);
        
    return NULL;
}

static char buffer[256];
/* Write formatted output to STREAM.  */
int fprintf (FILE *__restrict __stream,
		    __const char *__restrict __format, ...)
{
    va_list arguments;
    int length;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, %s)\n",
        __FILE__, __FUNCTION__, __stream, __format);

    va_start (arguments, __format);
    string_print_va (buffer, __format, arguments);
    va_end (arguments);
    length = string_length (buffer);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%s, %i)\n",
        __FILE__, __FUNCTION__, buffer, __stream->_fileno);
    
    output_stream$write (&file_handles[__stream->_fileno], buffer, length);
        
    return 0;
}

/* Write formatted output to stdout.  */
int printf (__const char *__restrict __format, ...)
{
    va_list arguments;
    int length;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%s)\n",
        __FILE__, __FUNCTION__, __format);

    va_start (arguments, __format);
    string_print_va (buffer, __format, arguments);
    va_end (arguments);
    length = string_length (buffer);

//    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
//        "%s::%s (%s)\n",
//        __FILE__, __FUNCTION__, buffer);
    output_stream$write (&file_handles[stdout->_fileno], buffer, length);

    return 0;
}

/* Write formatted output to S.  */
int sprintf (char *__restrict __s,
		    __const char *__restrict __format, ...)
{
    va_list arguments;
    int ret;

//    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
//        "%s::%s ()\n",
//        __FILE__, __FUNCTION__);

    va_start (arguments, __format);
    ret = string_print_va (__s, __format, arguments);
    va_end (arguments);

//    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
//        "%s::%s (%s)\n",
//        __FILE__, __FUNCTION__, __s);

    return ret;
}

/* Write formatted output to S from argument list ARG.  */

int vfprintf (FILE *__restrict __s, __const char *__restrict __format,
		     _G_va_list __arg)
{
    int ret, length;
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, %s)\n",
        __FILE__, __FUNCTION__, __s, __format);

    ret = string_print_va (buffer, __format, __arg);
    length = string_length (buffer);
    output_stream$write (&file_handles[__s->_fileno], buffer, length);

    return 0;
}
		     
/* Write formatted output to stdout from argument list ARG.  */
int vprintf (__const char *__restrict __format, _G_va_list __arg)
{
    int ret, length;
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);

    ret = string_print_va (buffer, __format, __arg);
    length = string_length (buffer);
    output_stream$write (&file_handles[stdout->_fileno], buffer, length);

    return 0;
}

/* Write formatted output to S from argument list ARG.  */
int vsprintf (char *__restrict __s, __const char *__restrict __format,
		     _G_va_list __arg)
{
    int ret;
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);

    ret = string_print_va (__s, __format, __arg);
        
    return ret;
}


/* Read formatted input from STREAM.  */
int fscanf (FILE *__restrict __stream,
		   __const char *__restrict __format, ...)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);

    return -1;
}

/* Read formatted input from stdin.  */
int scanf (__const char *__restrict __format, ...)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);
        
    return -1;
}

/* Read formatted input from S.  */
int sscanf (__const char *__restrict __s,
		   __const char *__restrict __format, ...)
{
    va_list arguments;
    int ret;
    
//    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
//        "%s::%s (%s, %s)\n",
//        __FILE__, __FUNCTION__, __s, __format);

    va_start (arguments, __format);
    ret = string_scan_va (__s, __format, arguments);
    va_end (arguments);

    return ret;
}

/* Read chunks of generic data from STREAM.  */
/*
size_t fread (void *__restrict __ptr, size_t __size,
		     size_t __n, FILE *__restrict __stream)
{
}
*/
size_t fwrite (__const void *__restrict __ptr, size_t __size,
		      size_t __n, FILE *__restrict __s)
{
//    uint32_t i;
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, %u, %u, %p)\n",
        __FILE__, __FUNCTION__, __ptr, __size, __n, __s);
/*    
    for (i=0;i<__size;i++)
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, "%c", *((char *) __ptr + i));
    }
*/
    output_stream$write (&file_handles[__s->_fileno], __ptr, __size * __n);

    return 0;
}

/* Write a character to stdout.  */
int putchar (int __c)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%i)\n",
        __FILE__, __FUNCTION__, __c);

    output_stream$write (&file_handles[stdout->_fileno], &__c, 1);

    return __c;
}

/* If BUF is NULL, make STREAM unbuffered.
   Else make it use buffer BUF, of size BUFSIZ.  */
void setbuf (FILE *__restrict __stream, char *__restrict __buf)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, %p)\n",
        __FILE__, __FUNCTION__, __stream, __buf);

}

/* Make STREAM use buffering mode MODE.
   If BUF is not NULL, use N bytes of it for buffering;
   else allocate an internal buffer N bytes long.  */
int setvbuf (FILE *__restrict __stream, char *__restrict __buf,
		    int __modes, size_t __n)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, %p, %i, %u)\n",
        __FILE__, __FUNCTION__, __stream, __buf, __modes, __n);

    return -1;
}

