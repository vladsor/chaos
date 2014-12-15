#!/bin/sh
lex -l ./idl-g.ll
yacc -vtd ./idl-g.yy
gcc -c *.c
gcc -o idl2c main.o generator.o lex.yy.o y.tab.o
