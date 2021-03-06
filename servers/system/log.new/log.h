#include "list.h"
typedef struct
{
  u32 number;
  u8 hours;
  u8 minutes;
  u8 seconds;
  unsigned int urgency;
  char sender_name[IPC_LOG_MAX_CLASS_LENGTH];
  char message[IPC_LOG_MAX_MESSAGE_LENGTH];
}log_record_type;

typedef struct
{
  unsigned int log_counter;
  console_structure_type* console;
  char* title;

  list_structure_type* first_list_element;
  list_structure_type* last_list_element;
  list_structure_type* page_list_element;
  list_structure_type* current_list_element;
}internal_log_structure_type;

static inline void init_internal_log_structure(internal_log_structure_type* log,
  console_structure_type* console,char* title)
{
  log->console = console;
  log->title = title;
  log->log_counter = 0;
  log->first_list_element = NULL;
  log->last_list_element = NULL;
  log->page_list_element = NULL;
  log->current_list_element = NULL;
}
