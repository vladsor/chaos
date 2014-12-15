#ifndef __STORM_PROCESS_H__
#define __STORM_PROCESS_H__

#include <Common/process.h>

extern return_t process_init (int argc, char *argv[]);

/*
extern return_t process_create (process_t *process, 
    elf_header_t *elf_header);
*/

extern return_t process_name_set (process_t *process, char *name);
extern return_t process_name_get (process_t *process, char *name);

#endif /* !__STORM_PROCESS_H__ */
