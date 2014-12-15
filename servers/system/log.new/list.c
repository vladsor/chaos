#include <memory/memory.h>
#include "list.h"

list_structure_type* add_after(list_structure_type* elem_after,void* elem)
{
  list_structure_type* new_struct;
  memory_allocate((void**)&new_struct,sizeof(list_structure_type));
  new_struct->data = elem;
  (struct list_structure_type*)new_struct->previous = 
    (struct list_structure_type*)elem_after;
  new_struct->next = NULL;
  if(elem_after != NULL)
    (struct list_structure_type*)elem_after->next = 
      (struct list_structure_type*)new_struct;
  return new_struct;        
}

void delete_after(list_structure_type* elem_after)
{
  list_structure_type* temp = 
    (list_structure_type*)((list_structure_type*)elem_after->next)->next;

  memory_deallocate((void**)elem_after->next);
  (struct list_structure_type*)elem_after->next = (struct list_structure_type*)temp;
}

void destroy_list_after(list_structure_type* elem_after)
{
  list_structure_type* current = elem_after;
  list_structure_type* temp;

  if(current == NULL)
    return;
  if(current->previous != NULL)
  {
    temp = current;
    (struct list_structure_type*)current = 
      (struct list_structure_type*)current->previous;
    current->next = NULL;
    current = temp;
  }
  
  while(current != NULL)
  {
    (struct list_structure_type*)temp = 
      (struct list_structure_type*)current->next;
    memory_deallocate((void**)&current);
    current = temp;
  }
}
