#include <storm/event.h>
#include <storm/generic/defines.h>
//#include <storm/generic/mutex.h>
#include <storm/generic/types.h>

typedef struct
{
  event_parameter_type* parameter_type;
  list_item_type* previous;
  list_item_type* next;
}list_item_type;

typedef 

extern return_type generate_event(event_parameter_type* event);
extern return_type wait_event(event_parameter_type* event);

