%{
#include <stdlib.h>
#include <stdio.h>

#include "y.tab.h"

static double  idl_atof(char *);
static long    idl_atoi(char *, long);
static unsigned char idl_escape_reader (char *str);
%}

%%

abstract        return ABSTRACT;
any             return ANY;
attribute       return ATTRIBUTE;
boolean         return BOOLEAN;
case            return CASE;
char            return CHAR;
const           return CONST;
context         return CONTEXT;
custom          return CUSTOM;
default         return DEFAULT;
double          return DOUBLE;
enum            return ENUM;
exception       return EXCEPTION;
factory         return FACTORY;
FALSE           return FALSE_TOKEN;
fixed           return FIXED;
float           return FLOAT;
in              return IN;
inout           return INOUT;
interface       return INTERFACE;
long            return LONG;
module          return MODULE;
native          return NATIVE;
Object          return OBJECT;
octet           return OCTET;
oneway          return ONEWAY;
out             return OUT;
private         return PRIVATE;
public          return PUBLIC;
raises          return RAISES;
readonly        return READONLY;
sequence        return SEQUENCE;
short           return SHORT;
string          return STRING;
struct          return STRUCT;
supports        return SUPPORTS;
switch          return SWITCH;
TRUE            return TRUE_TOKEN;
trancatable     return TRANCATABLE;
typedef         return TYPEDEF;
union           return UNION;
unsigned        return UNSIGNED;
ValueBase       return VALUEBASE;
valuetype       return VALUETYPE;
void            return VOID;
wchar           return WCHAR;
wstring         return WSTRING;

\<\<           return LEFT_SHIFT;

\>\>           return RIGHT_SHIFT;

\:\:           {
                 yylval.strval = "::";
                 return SCOPE_DELIMITOR;
               }

[a-zA-Z][a-zA-Z0-9_]* {
                 char *z = (char *) malloc (strlen (yytext) + 1);
                 strcpy (z, yytext);
                 yylval.strval = z;
                 
                 return IDENTIFIER;
               }

[0-9]*"."[0-9]*([eE][+-]?[0-9]+)?[lLfF]? {
                 yylval.dval = idl_atof (yytext);
                 
                 printf ("Flat: [%f]\n", yylval.dval);
                 return FLOATING_PT_LITERAL;
               }

[0-9]+[eE][+-]?[0-9]+[lLfF]? {
                 yylval.dval = idl_atof (yytext);
                 return FLOATING_PT_LITERAL;
               }

[1-9][0-9]*    {
                 yylval.ival = idl_atoi (yytext, 10);
                 return INTEGER_LITERAL;
               }

0[xX][a-fA-F0-9]+ {
                 yylval.ival = idl_atoi (yytext, 16);
                 return INTEGER_LITERAL;
               }

0[0-7]*        {
                 yylval.ival = idl_atoi (yytext, 8);
                 return INTEGER_LITERAL;
               }

"\""([^\"\\]|\\.)*"\"" {
                 char *z = (char *) malloc (strlen (yytext) + 1);
                 strcpy (z, yytext);
                 yylval.strval = z;
                 return STRING_LITERAL;
               }

"'"."'"        {
                 yylval.cval = yytext[1];
                 return CHARACTER_LITERAL;
               }

"'"\\([0-7]{1,3})"'"   {
                 // octal character constant
                 yylval.cval = idl_escape_reader(yytext + 1);
                 return CHARACTER_LITERAL;
               }

"'"\\([xX][0-9a-fA-F]{1,2})"'" {
                 // hex character constant
                 yylval.cval = idl_escape_reader(yytext + 1);
                 return CHARACTER_LITERAL;
               }

[ \t\n\r]* ;

.        return yytext[0];

%%

/*
 * idl_atoi - Convert a string of digits into an integer according to base b
 */
static long idl_atoi(char *s, long b)
{
       long    r = 0;
       long    negative = 0;

       if (*s == '-') {
         negative = 1;
         s++;
       }
       if (b == 8 && *s == '0')
         s++;
       else if (b == 16 && *s == '0' && (*(s + 1) == 'x' || *(s + 1) == 'X'))
         s += 2;

       for (; *s; s++)
         if (*s <= '9' && *s >= '0')
           r = (r * b) + (*s - '0');
         else if (b > 10 && *s <= 'f' && *s >= 'a')
           r = (r * b) + (*s - 'a' + 10);
         else if (b > 10 && *s <= 'F' && *s >= 'A')
           r = (r * b) + (*s - 'A' + 10);
         else
           break;

       if (negative)
         r *= -1;

       return r;
}

/*
 * Convert a string to a float; atof doesn't seem to work, always.
 */
static double idl_atof(char *s)
{

       double  d = 0.0;

       double  e, k;
       long    neg = 0, negexp = 0;

       if (*s == '-') {
         neg = 1;
         s++;
       }
       while (*s >= '0' && *s <= '9') {
               d = (d * 10) + *s - '0';
               s++;
       }
       if (*s == '.') {
               s++;
               e = 10;
               while (*s >= '0' && *s <= '9') {
                       d += (*s - '0') / (e * 1.0);
                       e *= 10;
                       s++;
               }
       }
       if (*s == 'e' || *s == 'E') {
               s++;
               if (*s == '-') {
                       negexp = 1;
                       s++;
               } else if (*s == '+')
                       s++;
               e = 0;
               while (*s >= '0' && *s <= '9') {
                       e = (e * 10) + *s - '0';
                       s++;
               }
               if (e > 0) {
                       for (k = 1; e > 0; k *= 10, e--);
                       if (negexp)
                               d /= k;
                       else
                               d *= k;
               }
       }

       if (neg) d *= -1.0;

       return d;
}

/*
 * Convert (some) escaped characters into their ascii values
 */
static unsigned char idl_escape_reader (char *str)
{
    if (str[0] != '\\') {
       return str[0];
    }

    switch (str[1]) {
      case 'n':
       return '\n';
      case 't':
       return '\t';
      case 'v':
       return '\v';
      case 'b':
       return '\b';
      case 'r':
       return '\r';
      case 'f':
       return '\f';
      case 'a':
       return '\a';
      case '\\':
       return '\\';
      case '\?':
       return '?';
      case '\'':
       return '\'';
      case '"':
       return '"';
      case 'x':
       {
           // hex value
           int i;
           char save, out;

           for (i = 2; str[i] != '\0' && isxdigit(str[i]); i++)
           {
               continue;
           }

           save = str[i];
           str[i] = '\0';
           out = (char)idl_atoi(&str[2], 16);
           str[i] = save;
           return out;
       }
       break;
      default:
       // check for octal value
       if (str[1] >= '0' && str[1] <= '7')
       {
           int i;
           char save, out;

           for (i = 1; str[i] >= '0' && str[i] <= '7'; i++)
           {
               continue;
           }

           save = str[i];
           str[i] = '\0';
           out = (char)idl_atoi(&str[1], 8);
           str[i] = save;
           return out;
       }
       else
       {
         return str[1] - 'a';
       }

       break;
    }

    return 0;
}
