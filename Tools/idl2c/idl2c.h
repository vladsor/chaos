typedef struct 
{
  int attribute;

  char *type_name;
  char *val_name;

  void *next;
} par_struct;

struct func_struct;

typedef struct 
{
  char *name;

  char *return_type;

  par_struct *pars;
  int num_of_pars;

  void *next;
} func_struct;

typedef struct 
{
  char *name;
  func_struct *funcs;
  int num_of_funcs;

  struct int_struct *next;
} int_struct;

enum
{
    TYPE_INTERFACE,
    TYPE_STRUCT,
    TYPE_SEQUENCE,
    TYPE_STRING,
    TYPE_BASE,
};

typedef struct
{
    char *name;
    
    int type;
    
    struct type_struct *next;
} type_struct;

typedef struct
{
    char *name;
    
    struct exc_struct *next;
} exc_struct;

typedef struct
{
    char *name;
    
    int num_of_int;
    int_struct *ints;
    
    func_struct *constructor;
    
    struct val_struct *next;
} val_struct;

extern int class_id;
extern int interface_id;
extern int exception_id;

extern void gen_add_value (char *name);
extern void gen_add_int_to_value (char *name);
extern void gen_add_constr_to_value (char *name);

extern void gen_add_interface (char *name);
extern void gen_add_operation (char *return_type, char *name);
extern void gen_add_op_parameter (int attribute, char *type, char *name);
extern char * gen_translate_stdtype (int type_code);

extern int generate_exceptions (void);
extern int generate();
extern int generate_values (void);

typedef enum
{
  ENUM_VOID,

  ENUM_FLOAT,
  ENUM_DOUBLE,

  ENUM_SIGNED_LONG_LONG_INT,
  ENUM_SIGNED_LONG_INT,
  ENUM_SIGNED_SHORT_INT,
  ENUM_UNSIGNED_LONG_LONG_INT,
  ENUM_UNSIGNED_LONG_INT,
  ENUM_UNSIGNED_SHORT_INT,

  ENUM_CHAR,
  ENUM_WIDE_CHAR,

  ENUM_OCTET,
  ENUM_BOOLEAN,
  ENUM_ANY,
  ENUM_OBJECT,

} stdtype_enum;

