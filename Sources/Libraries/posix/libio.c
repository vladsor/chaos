#include <enviroment.h>

#include <libio.h>

#include <Interfaces/input_stream.h>
#include <Interfaces/output_stream.h>

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

extern handle_t file_handles[100];

int _IO_getc (_IO_FILE *__fp)
{
    int ch;
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p)\n",
        __FILE__, __FUNCTION__, __fp);
        
    input_stream$read (&file_handles[__fp->_fileno], &ch, 1);
        
    return ch;
}

int _IO_putc (int __c, _IO_FILE *__fp)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%c [%u], %p) from %p\n",
        __FILE__, __FUNCTION__, __c, __c, __fp, ((uint32_t *)&__fp)[2]);

    output_stream$write (&file_handles[__fp->_fileno], &__c, 1);
        
    return __c;
}

