struct list_structure_type;
typedef struct
{
  void* data;
  struct list_structure* previous;
  struct list_structure* next;
} list_structure_type;

extern list_structure_type* add_after(list_structure_type* elem_after,void* elem);
extern void delete_after(list_structure_type* elem_after);
extern void destroy_list_after(list_structure_type* elem_after);
