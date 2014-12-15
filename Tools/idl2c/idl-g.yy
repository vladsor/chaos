%{
#include <stdlib.h>

#include "idl2c.h"

extern int yylex();
extern char* yytext;
%}

%union {
  long                 ival;           /* Long value           */
  double               dval;           /* Double value         */
  float                fval;           /* Float value          */
  char                 cval;           /* Char value           */

  char                 *strval;        /* char * value         */
}

%token          ABSTRACT
%token          ANY
%token          ATTRIBUTE;
%token          BOOLEAN;
%token          CASE;
%token          CHAR;
%token          CONST;
%token          CONTEXT;
%token          CUSTOM;
%token          DEFAULT;
%token          DOUBLE;
%token          ENUM;
%token          EXCEPTION;
%token          FACTORY;
%token          FALSE_TOKEN;
%token          FIXED;
%token          FLOAT;
%token          IN;
%token          INOUT;
%token          INTERFACE;
%token          LONG;
%token          MODULE;
%token          NATIVE;
%token          OBJECT;
%token          OCTET;
%token          ONEWAY;
%token          OUT;
%token          PRIVATE;
%token          PUBLIC;
%token          RAISES;
%token          READONLY;
%token          SEQUENCE;
%token          SHORT;
%token          STRING;
%token          STRUCT;
%token          SUPPORTS;
%token          SWITCH;
%token          TRUE_TOKEN;
%token          TRANCATABLE;
%token          TYPEDEF;
%token          UNION;
%token          UNSIGNED;
%token          VALUEBASE;
%token          VALUETYPE;
%token          VOID;
%token          WCHAR;
%token          WSTRING;

%token          LEFT_SHIFT
%token          RIGHT_SHIFT
%token          SCOPE_DELIMITOR

%token          INTEGER_LITERAL
%token          FLOATING_PT_LITERAL
%token          CHARACTER_LITERAL
%token          STRING_LITERAL
%token <strval> IDENTIFIER

%type  <strval> simple_declarator
%type  <strval> declarators
%type  <strval> declarator
%type  <strval> extend_declarators


%type  <ival>   type_spec
%type  <ival>   base_type_spec
%type  <ival>   simple_type_spec
%type  <ival>   template_type_spec
%type  <ival>   constr_type_spec

%type  <ival>   floating_pt_type

%type  <ival>   integer_type
%type  <ival>   signed_int
%type  <ival>   signed_long_long_int
%type  <ival>   signed_long_int
%type  <ival>   signed_short_int
%type  <ival>   unsigned_int
%type  <ival>   unsigned_long_long_int
%type  <ival>   unsigned_long_int
%type  <ival>   unsigned_short_int

%type  <ival>   char_type
%type  <ival>   wide_char_type
%type  <ival>   boolean_type
%type  <ival>   octet_type
%type  <ival>   any_type

%type  <ival>   sequence_type
%type  <ival>   string_type


%type  <strval> scoped_name
%type  <strval> interface_name

%type  <ival>   object_type

%type  <strval> op_type_spec
%type  <strval> param_type_spec
%type  <ival>   param_attribute

%start          specification

%%

specification           :       at_least_one_definition
                        ;

at_least_one_definition :       definition at_least_one_definition
                        |       definition
                        ;

definition              :       type_dcl ';'
                        |       const_dcl ';'
                        |       except_dcl ';'
                        |       interface ';'
                        |       module ';'
                        |       value ';'
                        ;

module                  :       MODULE IDENTIFIER 
                                '{' at_least_one_definition '}'
                        ;

interface               :       interface_dcl
                        |       forward_dcl
                        ;

interface_dcl           :       interface_header '{' interface_body '}'
                        ;

forward_dcl             :       INTERFACE IDENTIFIER
                {gen_add_type ($2, TYPE_INTERFACE);}                        ;

interface_header        :       INTERFACE IDENTIFIER inheritance_spec
                {
                                gen_add_type ($2, TYPE_INTERFACE);
                                gen_add_interface ($2);
                }
                        |       INTERFACE IDENTIFIER
                {
                                gen_add_type ($2, TYPE_INTERFACE);
                                gen_add_interface ($2);
                }
                        ;

interface_body          :       exports
                        ;

exports                 :       export exports
                        |       /* EMPTY */
                        ;

export                  :       type_dcl ';'
                        |       const_dcl ';'
                        |       except_dcl ';'
                        |       attr_dcl ';'
                        |       op_dcl ';'
                        ;

inheritance_spec        :       ':' scoped_name extends_inheritance

extends_inheritance     :       ',' scoped_name extends_inheritance
                        |       /* EMPTY */
                        ;

interface_name          :       scoped_name
                {$$ = $1;}
                        ;

scoped_name             :       IDENTIFIER
                {$$ = $1;}
                        |       SCOPE_DELIMITOR IDENTIFIER
                {$$ = "void";}
                        |       scoped_name SCOPE_DELIMITOR IDENTIFIER
                {$$ = "void";}
                        ;

value                   :       value_dcl
                        |       value_abs_dcl
                        |       value_box_dcl
                        |       value_forward_dcl
                        ;

value_forward_dcl       :       ABSTRACT VALUETYPE IDENTIFIER
                        |       VALUETYPE IDENTIFIER
                        ;

value_box_dcl           :       VALUETYPE IDENTIFIER type_spec
                        ;

value_abs_dcl           :       ABSTRACT VALUETYPE IDENTIFIER 
                                    value_inheritance_spec "{" exports "}"
                        |       ABSTRACT VALUETYPE IDENTIFIER "{" exports "}"
                        ;

value_dcl               :       value_header "{" value_elements "}"
                        ;

value_header            :       CUSTOM VALUETYPE IDENTIFIER 
                                    value_inheritance_spec
                {gen_add_value ($3);}
                        |       VALUETYPE IDENTIFIER value_inheritance_spec
                {gen_add_value ($2);}
                        |       CUSTOM VALUETYPE IDENTIFIER
                {gen_add_value ($3);}
                        |       VALUETYPE IDENTIFIER
                {gen_add_value ($2);}
                        ;                

value_inheritance_spec  :       ":" TRANCATABLE value_name extends_value_name 
                                    SUPPORTS interface_name 
                                    extends_interface_name
                {gen_add_int_to_value ($6);}
                        |       ":" value_name extends_value_name 
                                SUPPORTS interface_name
                                extends_interface_name
                {gen_add_int_to_value ($5);}
                        |       ":" TRANCATABLE value_name extends_value_name  
                        |       ":" value_name extends_value_name 
                        |       SUPPORTS interface_name
                                extends_interface_name
                {gen_add_int_to_value ($2);}
                        ;

extends_interface_name  :       "," interface_name extends_interface_name
                {gen_add_int_to_value ($2);}
                        |       /* EMPTY */
                        ;

extends_value_name      :       "," value_name extends_value_name
                        |       /* EMPTY */
                        ;

value_name              :       scoped_name
                        ;

value_elements          :       value_element value_elements
                        |       /* EMPTY */
                        ;

value_element           :       export 
                        |       state_member 
                        |       init_dcl
                        ;

state_member            :       PUBLIC type_spec declarators ";"
                        |       PRIVATE type_spec declarators ";"
                        ;            

init_dcl                :       FACTORY IDENTIFIER "(" init_param_decls ")" ";"
                {gen_add_constr_to_value ($2);}
                        |       FACTORY IDENTIFIER "(" ")" ";"
                {gen_add_constr_to_value ($2);}
                        ;        

init_param_decls        :       init_param_decl extends_init_param_decl
                        ;

extends_init_param_decl :       "," init_param_decl extends_init_param_decl
                        |       /* EMPTY */
                        ;

init_param_decl         :       init_param_attribute param_type_spec
                                    simple_declarator
                        ;

init_param_attribute    :       IN
                        ;

const_dcl               :       CONST const_type IDENTIFIER '=' const_exp
                        ;

const_type              :       integer_type
                        |       char_type
                        |       boolean_type
                        |       floating_pt_type
                        |       string_type
                        |       scoped_name
                        ;

const_exp               :       or_expr
                        ;

or_expr                 :       xor_expr
                        |       or_expr '|' xor_expr
                        ;

xor_expr                :       and_expr
                        |       xor_expr '^' and_expr
                        ;

and_expr                :       shift_expr
                        |       and_expr '&' shift_expr
                        ;

shift_expr              :       add_expr
                        |       shift_expr RIGHT_SHIFT add_expr
                        |       shift_expr LEFT_SHIFT add_expr
                        ;

add_expr                :       mult_expr
                        |       add_expr '+' mult_expr
                        |       add_expr '-' mult_expr
                        ;

mult_expr               :       unary_expr
                        |       mult_expr '*' unary_expr
                        |       mult_expr '/' unary_expr
                        |       mult_expr '%' unary_expr
                        ;

unary_expr              :       unary_operator primary_expr
                        |       primary_expr
                        ;

unary_operator          :       '-'
                        |       '+'
                        |       '~'
                        ;

primary_expr            :       scoped_name
                        |       literal
                        |       '(' const_exp ')'
                        ;

literal                 :       INTEGER_LITERAL
                        |       STRING_LITERAL
                        |       CHARACTER_LITERAL
                        |       FLOATING_PT_LITERAL
                        |       boolean_literal
                        ;

boolean_literal         :       TRUE_TOKEN
                        |       FALSE_TOKEN
                        ;

positive_int_const      :       const_exp
                        ;

type_dcl                :       TYPEDEF type_declarator
                        |       struct_type
                        |       union_type
                        |       enum_type
                        ;

type_declarator         :       type_spec declarators
            {gen_add_type ($2, $1);}
                        ;

type_spec               :       simple_type_spec
                {$$ = $1;}
                        |       constr_type_spec
                {$$ = $1;}
                        ;

simple_type_spec        :       base_type_spec
                {$$ = $1;}
                        |       template_type_spec
                {$$ = $1;}
                        |       scoped_name
                {$$ = 0;}
                        ;

base_type_spec          :       floating_pt_type
                {$$ = $1;}
                        |       integer_type
                {$$ = $1;}
                        |       char_type
                {$$ = $1;}
                        |       wide_char_type
                {$$ = $1;}
                        |       boolean_type
                {$$ = $1;}
                        |       octet_type
                {$$ = $1;}
                        |       any_type
                {$$ = $1;}
                        |       object_type
                {$$ = $1;}
                        ;

template_type_spec      :       sequence_type
                {$$ = $1;}
                        |       string_type
                {$$ = $1;}
                        ;

constr_type_spec        :       struct_type
                {$$ = 0;}
                        |       union_type
                {$$ = 0;}
                        |       enum_type
                {$$ = 0;}
                        ;

declarators             :       declarator extend_declarators
                {$$ = $1;}
                        ;

extend_declarators      :       ',' declarator extend_declarators
                {$$ = $2;}
                        |       /* EMPTY */
                {$$ = 0;}
                        ;

declarator              :       simple_declarator
                {$$ = $1;}
                        |       complex_declarator
                {$$ = 0;}
                        ;

simple_declarator       :       IDENTIFIER
                {$$ = $1;}
                        ;

complex_declarator      :       array_declarator
                        ;

floating_pt_type        :       FLOAT
                {$$ = ENUM_FLOAT;}
                        |       DOUBLE
                {$$ = ENUM_DOUBLE;}
                        ;

integer_type            :       signed_int
                {$$ = $1;}
                        |       unsigned_int
                {$$ = $1;}
                        ;

signed_int              :       signed_long_long_int
                {$$ = $1;}
                        |       signed_long_int
                {$$ = $1;}
                        |       signed_short_int
                {$$ = $1;}
                        ;

signed_long_long_int    :       LONG LONG
                {$$ = ENUM_SIGNED_LONG_LONG_INT;}
                        ;

signed_long_int         :       LONG
                {$$ = ENUM_SIGNED_LONG_INT;}
                        ;

signed_short_int        :       SHORT
                {$$ = ENUM_SIGNED_SHORT_INT;}
                        ;

unsigned_int            :       unsigned_long_long_int
                        |       unsigned_long_int
                        |       unsigned_short_int
                        ;

unsigned_long_long_int  :       UNSIGNED LONG LONG
                {$$ = ENUM_UNSIGNED_LONG_LONG_INT;}
                        ;

unsigned_long_int       :       UNSIGNED LONG
                {$$ = ENUM_UNSIGNED_LONG_INT;}
                        ;

unsigned_short_int      :       UNSIGNED SHORT
                {$$ = ENUM_UNSIGNED_SHORT_INT;}
                        ;

char_type               :       CHAR
                {$$ = ENUM_CHAR;}
                        ;

wide_char_type          :       WCHAR
                {$$ = ENUM_WIDE_CHAR;}
                        ;

boolean_type            :       BOOLEAN
                {$$ = ENUM_BOOLEAN;}
                        ;

octet_type              :       OCTET
                {$$ = ENUM_OCTET;}
                        ;

any_type                :       ANY
                {$$ = ENUM_ANY;}
                        ;

object_type             :       OBJECT
                {$$ = ENUM_OBJECT;}
                        ;

struct_type             :       STRUCT IDENTIFIER '{' member_list '}'
                {gen_add_type ($2, TYPE_STRUCT);}
                        ;

member_list             :       at_least_one_member
                        ;

at_least_one_member     :       member members
                        ;

members                 :       member members
                        |       /* EMPTY */

member                  :       type_spec declarators ';'
                        ;

union_type              :       UNION IDENTIFIER SWITCH '(' switch_type_spec ')'
                                '{' switch_body '}'
                        ;

switch_type_spec        :       integer_type
                        |       char_type
                        |       boolean_type
                        |       enum_type
                        |       scoped_name
                        ;

switch_body             :       at_least_one_case
                        ;

at_least_one_case       :       case at_least_one_case 
                        |       case
                        ;

case                    :       at_least_one_case_label element_spec ';'
                        ;

at_least_one_case_label :       case_label at_least_one_case_label
                        |       case_label
                        ;

case_label              :       CASE const_exp ':'
                        |       DEFAULT ':'
                        ;

element_spec            :       type_spec declarator
                        ;

enum_type               :       ENUM IDENTIFIER '{' enumerator extends_enum '}'
                        ;

extends_enum            :       ',' enumerator extends_enum
                        |       /* EMPTY */
                        ;

enumerator              :       IDENTIFIER
                        ;

sequence_type           :       SEQUENCE '<' simple_type_spec ',' 
                                        positive_int_const '>'
                {$$ = TYPE_SEQUENCE;}
                        |       SEQUENCE '<' simple_type_spec '>'
                {$$ = TYPE_SEQUENCE;}
                        ;

string_type             :       STRING '<' positive_int_const '>'
                {$$ = TYPE_STRING;}
                        |       STRING
                {$$ = TYPE_STRING;}
                        ;

array_declarator        :       IDENTIFIER at_least_one_fixed_array_size
                        ;

at_least_one_fixed_array_size : fixed_array_size at_least_one_fixed_array_size
                        |       fixed_array_size
                        ;

fixed_array_size        :       '[' positive_int_const ']'
                        ;

attr_dcl                :       ATTRIBUTE param_type_spec simple_declarator 
                                        extends_attr
                        |       READONLY ATTRIBUTE param_type_spec 
                                        simple_declarator extends_attr
                        ;

extends_attr            :       ',' simple_declarator extends_attr
                        |       /* EMPTY */
                        ;


except_dcl              :       EXCEPTION IDENTIFIER '{' members '}'
                {gen_add_exc ($2);}  
                        ;
                        
op_dcl                  :       op_type_spec IDENTIFIER
                                parameter_dcls
                {gen_add_operation ($1, $2);} 
                        |       op_attribute op_type_spec IDENTIFIER 
                                parameter_dcls
                        |       op_type_spec IDENTIFIER
                                parameter_dcls raises_expr
                        |       op_attribute op_type_spec IDENTIFIER 
                                parameter_dcls raises_expr
                        |       op_type_spec IDENTIFIER
                                parameter_dcls raises_expr context_expr
                        |       op_attribute op_type_spec IDENTIFIER 
                                parameter_dcls raises_expr context_expr
                        ;

op_attribute            :       ONEWAY
                        ;

op_type_spec            :       param_type_spec
                {$$ = $1;}
                        |       VOID
                {$$ = gen_translate_stdtype (VOID);}
                        ;

parameter_dcls          :       '(' param_dcl extends_param ')'
                        |       '(' ')'
                        ;

extends_param           :       ',' param_dcl extends_param
                        |       /* EMPTY */
                        ;

param_dcl               :       param_attribute param_type_spec 
                                        simple_declarator
                {gen_add_op_parameter ($1, $2, $3);}
                        ;

param_attribute         :       IN    
                {$$ = IN;}
                        |       OUT   
                {$$ = OUT;}
                        |       INOUT 
                {$$ = INOUT;}
                        ;

raises_expr             :       RAISES '(' scoped_name extends_raises ')'
                        ;

extends_raises          :       ',' scoped_name extends_raises
                        :       /* EMPTY */
                        ;

context_expr            :       CONTEXT '(' STRING_LITERAL extends_context ')'
                        ;

extends_context         :       ',' STRING_LITERAL extends_context
                        |       /* EMPTY */
                        ;

param_type_spec         :       base_type_spec
                {$$ = gen_translate_stdtype ($1);}
                        |       string_type
                {$$ = "void";}
                        |       scoped_name
                {$$ = $1;}
                        ;

%%

int yywrap()
{
  return 1;
}
