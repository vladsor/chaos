#include <stdio.h>

#include "idl2c.h"

#include "y.tab.h"

type_struct *head_type = NULL;
type_struct *curr_type = NULL;
type_struct *tail_type = NULL;

int_struct *head_int = NULL;
int_struct *curr_int = NULL;
int_struct *tail_int = NULL;

func_struct *head_func = NULL;
func_struct *curr_func = NULL;
func_struct *tail_func = NULL;

par_struct *head_par = NULL;
par_struct *curr_par = NULL;
par_struct *tail_par = NULL;

exc_struct *head_exc = NULL;
exc_struct *curr_exc = NULL;
exc_struct *tail_exc = NULL;

val_struct *head_val = NULL;
val_struct *curr_val = NULL;
val_struct *tail_val = NULL;

void gen_add_type (char *name, int type)
{
    printf ("Add type: %s %u\n", name, type);
}

void gen_add_value (char *name)
{
    printf ("Add value: %s.\n", name);

    curr_val = (val_struct *) malloc (sizeof(val_struct));

    curr_val->next = NULL;
    curr_val->num_of_int = 0;
    curr_val->name = name;

    if (tail_val != NULL)
    {
        tail_val->next = (struct val_struct *) curr_val;
        tail_val = curr_val;
    }
    else
    {
        head_val = tail_val = curr_val;
    }
}

void gen_add_int_to_value (char *name)
{
    printf ("Add interface: %s to value\n", name);
}

void gen_add_constr_to_value (char *name)
{
    printf ("Add constructor: %s to value\n", name);
}

void gen_add_exc (char *name)
{
    printf ("Add exception: %s\n", name);

    curr_exc = (exc_struct *) malloc (sizeof(exc_struct));

    curr_exc->next = NULL;
    curr_exc->name = name;

    if (tail_exc != NULL)
    {
        tail_exc->next = (struct exc_struct *) curr_exc;
        tail_exc = curr_exc;
    }
    else
    {
        head_exc = tail_exc = curr_exc;
    }
}

void gen_add_interface (char *name)
{
    printf ("Add interface: %s\n", name);

  curr_int = (int_struct *) malloc (sizeof(func_struct));
  curr_int->next = NULL;
  curr_int->funcs = NULL;
  curr_int->name = name;
  curr_int->num_of_funcs = 0;

  if (tail_int != NULL)
  {
    tail_int->next = (struct int_struct *) curr_int;
    tail_int = curr_int;
  }
  else
  {
    head_int = tail_int = curr_int;
  }

  head_func = NULL;
  tail_func = NULL;
  
  head_par = NULL;
  tail_par = NULL;
}

void gen_add_operation (char *return_type, char *name)
{
    printf ("Add operation: %s\n", name);

  curr_int->num_of_funcs++;

//  curr_func = (func_struct *) malloc (sizeof(func_struct));
//  curr_func->next = NULL;
  curr_func->pars = head_par;
  curr_func->name = name;
//  curr_func->num_of_pars = 0;
  
  if (return_type == NULL)
  {
    printf ("Attention: return type is NULL.\n");
    curr_func->return_type = "void";
  }
  else
  {
    curr_func->return_type = return_type;
  }
/*
  if (tail_func != NULL)
  {
    tail_func->next = curr_func;
    tail_func = curr_func;
  }
  else
  {
    head_func = tail_func = curr_func;
    tail_int->funcs = head_func;
  }
*/
  head_par = NULL;
  tail_par = NULL;
  curr_func = NULL;
}

char * gen_translate_attribute (char *type, int attr)
{
    if (attr == IN)
    {
        char *str;
        str = (char *) malloc(strlen(type) + 3);
        strcpy(str, type);
        strcat(str, " *");
        
        return str;
    }
    else if (attr = OUT)
    {
        return type;
    }
    else
    {
        char *str;
        str = (char *) malloc(strlen(type) + 3);
        strcpy(str, type);
        strcat(str, " *");
        
        return str;
    }
}

void gen_add_op_parameter (int attribute, char *type, char *name)
{
    printf ("Add parameter: %s\n", name);

    if (curr_func == NULL)
    {
      curr_func = (func_struct *) malloc (sizeof(func_struct));
      curr_func->next = NULL;
      curr_func->pars = NULL;
      curr_func->num_of_pars = 0;
      
  if (tail_func != NULL)
  {
    tail_func->next = curr_func;
    tail_func = curr_func;
  }
  else
  {
    head_func = tail_func = curr_func;
    tail_int->funcs = head_func;
  }

    }  
    curr_func->num_of_pars++;

  curr_par = (par_struct *) malloc (sizeof(par_struct));
  curr_par->next = NULL;
  curr_par->val_name = name;
//  curr_par->attribute = attribute;

  if (type == NULL)
  {
    printf ("Attention: parameter type is NULL.\n");
    exit (-1);
  }
  else
  {
    curr_par->type_name = gen_translate_attribute(type, attribute);
  }

  if (tail_par != NULL)
  {
    tail_par->next = curr_par;
    tail_par = curr_par;
  }
  else
  {
    head_par = tail_par = curr_par;
    tail_func->pars = head_par;
  }
}


char * gen_translate_stdtype (int type_code)
{
  switch (type_code)
  { 
    case ENUM_FLOAT:
    {
      return "float";
    }

    case ENUM_DOUBLE:
    {
      return "double";
    }

    case ENUM_SIGNED_LONG_LONG_INT:
    {
      return "int64_t";
    }

    case ENUM_SIGNED_LONG_INT:
    {
      return "int32_t";
    }

    case ENUM_SIGNED_SHORT_INT:
    {
      return "int16_t";
    }

    case ENUM_UNSIGNED_LONG_LONG_INT:
    {
      return "uint64_t";
    }

    case ENUM_UNSIGNED_LONG_INT:
    {
      return "uint32_t";
    }

    case ENUM_UNSIGNED_SHORT_INT:
    {
      return "uint16_t";
    }

    case ENUM_CHAR:
    {
      return "char";
    }
/*
    wide_char_type:

    boolean_type:
*/ 
    case ENUM_OCTET:
    {
      return "uint8_t";
    }

    case ENUM_OBJECT:
    {
        return "handle_t";
    }
/*
    any_type:
*/
    case ENUM_VOID:
    default:
    {
      return "void";
    }
  }
}

int generate ()
{
  generate_public ();

  return 0;
}

void str_to_upper(char *source, char *dest)
{
    int i;
    
    for (i=0;source[i]!=0;i++)
    {
        dest[i] = toupper(source[i]);
    }
    
    dest[i] = 0;
}

int generate_public ()
{
  FILE *public_header;
//  FILE *private_header;
  int_struct *curr_int;
  func_struct *curr_func;
  par_struct *curr_par;

  printf ("Generating files for interfaces...\n");

  for (curr_int = head_int; curr_int != NULL; curr_int = curr_int->next)
  {
    char buffer[256] = "";
    char buffer2[256] = "";

    printf ("Generating files for %s interface.\n", curr_int->name);

    /*curr_int->name + ".h"*/
    strcpy (buffer, curr_int->name);
    strcat (buffer, ".h");
    public_header = fopen (buffer, "wt");

    /*curr_int->name + "_private.h"*/
    strcpy (buffer, curr_int->name);
    strcat (buffer, "_private.h");
//    private_header = fopen (buffer, "wt");
//    client_stab_source = fopen (curr_int->name + "_client.c", "wt");
//    server_stab_source = fopen (curr_int->name + "_server.c", "wt");

    /* generating public header */

    fprintf (public_header, 
      "/* ATTENTION! THIS FILE GENERATED BY IDL2C, DO NOT EDIT! */\n\n");

    str_to_upper(curr_int->name, buffer);
    fprintf (public_header, "#ifndef __INTERFACE_%s_H__\n",
        buffer);
    fprintf (public_header, "#define __INTERFACE_%s_H__\n\n",
        buffer);

    fprintf (public_header, 
      "#define IID_%s 0x%8.8X\n\n",
      buffer, interface_id);
    interface_id++;

    fprintf (public_header, "enum\n{\n");
    for (curr_func = curr_int->funcs ; curr_func != NULL ; 
      curr_func = curr_func->next)
    {
        str_to_upper(curr_int->name, buffer);
        fprintf (public_header, "    MID_%s_",
            buffer);
        str_to_upper(curr_func->name, buffer);
        fprintf (public_header, "%s,\n",
            buffer);   
    }
    fprintf (public_header, "};\n\n");

    for (curr_func = curr_int->funcs ; curr_func != NULL ; 
      curr_func = curr_func->next)
    {
      printf ("Generating operation: %s\n", curr_func->name);

      fprintf (public_header, "typedef %s (%s_%s_function_t) (", 
          curr_func->return_type, curr_int->name, curr_func->name);
 
      /*
      if not static
        fprintf (curr_int->name + "_interface_install");
        fprintf (curr_int->name + "_interface_uninstall");
        fprintf (public_header, "void *this_interface,\n");
      */
      if (1)
      {
        fprintf (public_header, "\n    context_t *context /* THIS  */");
      }

      for (curr_par = curr_func->pars; curr_par != NULL; 
        curr_par = curr_par->next)
      {
        if (1)
        {
          fprintf (public_header, ",");
        }

//        if (curr_par->attribute == IN)
        {
          fprintf (public_header, "\n    %s %s /* IN */", 
            curr_par->type_name, curr_par->val_name);
        }
//        else
//        {
//          fprintf (public_header, "\n    %s %s /* OUT */",
//            curr_par->type_name, curr_par->val_name);
//        }

        if (0 && curr_par->next != NULL)
        {
          fprintf (public_header, ",");
        }
      }
      fprintf (public_header, ");\n");

      if (curr_func->next != NULL)
      {
        fprintf (public_header, "\n");
      }
    }

  
    fprintf (public_header, "\n\ntypedef struct\n{\n");

    for (curr_func = curr_int->funcs ; curr_func != NULL ; 
      curr_func = curr_func->next)
    {
      fprintf (public_header, "    %s_%s_function_t *%s;\n",
        curr_int->name, curr_func->name, curr_func->name);
 
//      if (1)
//      {
//        fprintf (public_header, "\n/* THIS */ void *this");
//      }
/*
      for (curr_par = curr_func->pars ; curr_par != NULL ;
        curr_par = curr_par->next)
      {
        fprintf (public_header, "\n    %s %s",
          curr_par->type_name, curr_par->val_name);
 
        if (curr_par->next != NULL)
        {
          fprintf (public_header, ",");
        }
      }
      fprintf (public_header, ");\n");
*/
//      if (curr_func->next != NULL)
//      {
//        fprintf (public_header, "\n");
//      }
    }
 
    fprintf (public_header, "} interface_%s_t;\n",
      curr_int->name);

    fprintf (public_header, "\n");

    for (curr_func = curr_int->funcs; curr_func != NULL;
        curr_func = curr_func->next)
    {
        fprintf (public_header, "typedef struct\n{\n");

        fprintf (public_header, "    %s_%s_function_t *function;\n",
            curr_int->name, curr_func->name);
        
        fprintf (public_header, "    method_id_t method_id;\n");
        fprintf (public_header, "    uint32_t parameters_size;\n");
        fprintf (public_header, "    uint32_t number_of_parameters;\n");
        fprintf (public_header, "    parameter_t parameters[%u];\n",
            curr_func->num_of_pars);
      
        fprintf (public_header, "} %s_%s_method_t;\n",
            curr_int->name, curr_func->name);

        fprintf (public_header, "\n");
        
        if (curr_func->num_of_pars > 0)
        {
            fprintf (public_header, "typedef struct\n{\n");
        
            for (curr_par = curr_func->pars; curr_par != NULL;
                curr_par = curr_par->next)
            {
                fprintf (public_header, "    %s %s;\n",
                    curr_par->type_name, curr_par->val_name);
            }
      
            fprintf (public_header, "} %s_%s_parameters_t;\n",
                curr_int->name, curr_func->name);

            fprintf (public_header, "\n");
        }

        str_to_upper(curr_int->name, buffer);
        str_to_upper(curr_func->name, buffer2);

        fprintf (public_header, "#define %s_%s_METHOD(function) \\\n",
//            curr_int->name, curr_func->name);
            buffer, buffer2);
        fprintf (public_header, "    (&(function)), \\\n");
        fprintf (public_header, "    (MID_%s_%s), \\\n",
//            curr_int->name, curr_func->name);
            buffer, buffer2);
        
        if (curr_func->num_of_pars == 0)
        {
            fprintf (public_header, "    (0), \\\n");
        }
        else
        {
            fprintf (public_header, "    (sizeof (%s_%s_parameters_t)), \\\n",
                curr_int->name, curr_func->name);
        }
        
        if (curr_func->num_of_pars == 0)
        {
            fprintf (public_header, "    (0)\n");
        }
        else
        {
            fprintf (public_header, "    (%u), \\\n",
                curr_func->num_of_pars);

            fprintf (public_header, "    { \\\n");

            for (curr_par = curr_func->pars; curr_par != NULL; 
                curr_par = curr_par->next)
            {
                if (curr_par->next != NULL)
                {
                    fprintf (public_header, "        {sizeof (%s)}, \\\n",
                        curr_par->type_name);
                }
                else
                {
                    fprintf (public_header, "        {sizeof (%s)} \\\n",
                        curr_par->type_name);
                }
            }
            fprintf (public_header, "    }\n");
        }

        fprintf (public_header, "\n");
        
    } 

    for (curr_func = curr_int->funcs; curr_func != NULL;
        curr_func = curr_func->next)
    {
        fprintf (public_header, "#define %s$%s(handle",
            curr_int->name, curr_func->name);
            
        for (curr_par = curr_func->pars; curr_par != NULL; 
             curr_par = curr_par->next)
        {
            fprintf (public_header, ",%s",
                curr_par->val_name);
        }
        
        fprintf (public_header, ") \\\n");

        fprintf (public_header, 
            "    ((%s_interface_t *) ((handle)->functions))->%s ( \\\n",
            curr_int->name, curr_func->name);

//        if (curr_func->num_of_pars == 0)
//        {
//            fprintf (public_header, "        &((handle)->context))\n");
//        }
//        else
        {
            fprintf (public_header, "        &((handle)->context)");

            for (curr_par = curr_func->pars; curr_par != NULL; 
                curr_par = curr_par->next)
            {
            fprintf (public_header, ",\n        (%s)",
                curr_par->val_name);
            }
            fprintf (public_header, ")\n");
        }

        fprintf (public_header, "\n");
    }
    
    str_to_upper(curr_int->name, buffer);
    fprintf (public_header, "#endif /* !__INTERFACE_%s_H__ */\n\n",
        buffer);

    fclose (public_header);
//    fclose (private_header);
    /* end generating public header */
  }

  return 0;
}

int generate_exceptions (void)
{
    FILE *fout;

    printf ("Generating file for exceptions...\n");
    
    fout = fopen ("exceptions.h", "wt");
    
    for (curr_exc = head_exc; curr_exc != NULL; curr_exc = curr_exc->next)
    {
        fprintf (fout, "#define %s_ID 0x%8.8X\n", curr_exc->name, exception_id);
        exception_id++;
    }
    
    return 0;
}

int generate_values (void)
{
    FILE *public_header;
    
    printf ("Generating files for values...\n");
    
    for (curr_val = head_val; curr_val != NULL; curr_val = curr_val->next)
    {
        char buffer[256] = "";
        char buffer2[256] = "";

        printf ("Generating files for %s class.\n", curr_val->name);

        /*curr_val->name + ".h"*/
        strcpy (buffer, curr_val->name);
        strcat (buffer, ".h");
        public_header = fopen (buffer, "wt");
    }

    return 0;
}

