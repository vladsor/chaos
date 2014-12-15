#include <stdio.h>

#include "idl2c.h"

int class_id;
int interface_id;
int exception_id;

main()
{
    FILE *fl;
    
    fl = fopen ("idl2c.ini", "rt");
    fscanf(fl, "class_id=%u\n", &class_id);
    fscanf(fl, "interface_id=%u\n", &interface_id);
    fscanf(fl, "exception_id=%u\n", &exception_id);
    fclose (fl);
    
    if (!yyparse())
    {
	   generate_exceptions ();
	   generate ();
	   generate_values ();
	   
       fl = fopen ("idl2c.ini", "wt");
       fprintf(fl, "class_id=%u\n", class_id);
       fprintf(fl, "interface_id=%u\n", interface_id);
       fprintf(fl, "exception_id=%u\n", exception_id);
       fclose (fl);
	}
}
extern int yylineno;
extern char yytext[];
yyerror( char *s )
{
	fprintf( stderr, "Error: %s in line: %u before %s\n", 
        s, yylineno, yytext);
}

