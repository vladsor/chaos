#ifndef lint
static char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define yyclearin (yychar=(-1))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING (yyerrflag!=0)
#define YYPREFIX "yy"
#line 1 "./idl-g.yy"

#include <stdlib.h>

#include "idl2c.h"

extern int yylex();
extern char* yytext;
#line 10 "./idl-g.yy"
typedef union {
  long                 ival;           /* Long value           */
  double               dval;           /* Double value         */
  float                fval;           /* Float value          */
  char                 cval;           /* Char value           */

  char                 *strval;        /* char * value         */
} YYSTYPE;
#line 29 "y.tab.c"
#define ABSTRACT 257
#define ANY 258
#define ATTRIBUTE 259
#define BOOLEAN 260
#define CASE 261
#define CHAR 262
#define CONST 263
#define CONTEXT 264
#define CUSTOM 265
#define DEFAULT 266
#define DOUBLE 267
#define ENUM 268
#define EXCEPTION 269
#define FACTORY 270
#define FALSE_TOKEN 271
#define FIXED 272
#define FLOAT 273
#define IN 274
#define INOUT 275
#define INTERFACE 276
#define LONG 277
#define MODULE 278
#define NATIVE 279
#define OBJECT 280
#define OCTET 281
#define ONEWAY 282
#define OUT 283
#define PRIVATE 284
#define PUBLIC 285
#define RAISES 286
#define READONLY 287
#define SEQUENCE 288
#define SHORT 289
#define STRING 290
#define STRUCT 291
#define SUPPORTS 292
#define SWITCH 293
#define TRUE_TOKEN 294
#define TRANCATABLE 295
#define TYPEDEF 296
#define UNION 297
#define UNSIGNED 298
#define VALUEBASE 299
#define VALUETYPE 300
#define VOID 301
#define WCHAR 302
#define WSTRING 303
#define LEFT_SHIFT 304
#define RIGHT_SHIFT 305
#define SCOPE_DELIMITOR 306
#define INTEGER_LITERAL 307
#define FLOATING_PT_LITERAL 308
#define CHARACTER_LITERAL 309
#define STRING_LITERAL 310
#define IDENTIFIER 311
#define YYERRCODE 256
short yylhs[] = {                                        -1,
    0,   33,   33,   34,   34,   34,   34,   34,   34,   39,
   38,   38,   41,   42,   43,   43,   44,   46,   46,   47,
   47,   47,   47,   47,   45,   50,   50,   28,   27,   27,
   27,   40,   40,   40,   40,   54,   54,   53,   52,   52,
   51,   56,   56,   56,   56,   55,   55,   55,   55,   55,
   60,   60,   59,   59,   58,   57,   57,   61,   61,   61,
   62,   62,   63,   63,   64,   66,   66,   65,   67,   36,
   68,   68,   68,   68,   68,   68,   69,   70,   70,   71,
   71,   72,   72,   73,   73,   73,   74,   74,   74,   75,
   75,   75,   75,   76,   76,   77,   77,   77,   78,   78,
   78,   79,   79,   79,   79,   79,   80,   80,   81,   35,
   35,   35,   35,   82,    5,    5,    7,    7,    7,    6,
    6,    6,    6,    6,    6,    6,    6,    8,    8,    9,
    9,    9,    2,    4,    4,    3,    3,    1,   86,   10,
   10,   11,   11,   12,   12,   12,   13,   14,   15,   16,
   16,   16,   17,   18,   19,   20,   21,   22,   23,   24,
   29,   83,   88,   89,   91,   91,   90,   84,   92,   92,
   92,   92,   92,   93,   94,   94,   95,   96,   96,   98,
   98,   97,   85,  100,  100,   99,   25,   25,   26,   26,
   87,  101,  101,  102,   48,   48,  103,  103,   37,   49,
   49,   49,   49,   49,   49,  105,   30,   30,  104,  104,
  109,  109,  108,   32,   32,   32,  106,  110,  110,  107,
  111,  111,   31,   31,   31,
};
short yylen[] = {                                         2,
    1,    2,    1,    2,    2,    2,    2,    2,    2,    5,
    1,    1,    4,    2,    3,    2,    1,    2,    0,    2,
    2,    2,    2,    2,    3,    3,    0,    1,    1,    2,
    3,    1,    1,    1,    1,    3,    2,    3,    7,    6,
    4,    4,    3,    3,    2,    7,    6,    4,    3,    3,
    3,    0,    3,    0,    1,    2,    0,    1,    1,    1,
    4,    4,    6,    5,    2,    3,    0,    3,    1,    5,
    1,    1,    1,    1,    1,    1,    1,    1,    3,    1,
    3,    1,    3,    1,    3,    3,    1,    3,    3,    1,
    3,    3,    3,    2,    1,    1,    1,    1,    1,    1,
    3,    1,    1,    1,    1,    1,    1,    1,    1,    2,
    1,    1,    1,    2,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    2,    3,    0,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    2,    1,    1,    1,
    1,    1,    3,    2,    2,    1,    1,    1,    1,    1,
    1,    5,    1,    2,    2,    0,    3,    9,    1,    1,
    1,    1,    1,    1,    2,    1,    3,    2,    1,    3,
    2,    2,    6,    3,    0,    1,    6,    4,    4,    1,
    2,    2,    1,    3,    4,    5,    3,    0,    5,    3,
    4,    4,    5,    5,    6,    1,    1,    1,    4,    2,
    3,    0,    3,    1,    1,    1,    5,    2,    0,    5,
    3,    0,    1,    1,    1,
};
short yydefred[] = {                                      0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    1,    0,    0,    0,    0,    0,    0,    0,
   11,   12,    0,   32,   33,   34,   35,    0,  111,  112,
  113,    0,  158,  156,  141,  140,    0,  149,    0,    0,
    0,   29,   74,   71,  142,  144,  145,  146,  143,  150,
  151,  152,   72,   73,   75,    0,    0,    0,    0,    0,
    0,    0,    0,  160,  161,  159,    0,  157,    0,  117,
  115,  118,  116,  120,  121,  122,  123,  124,  125,  126,
  128,  129,    0,  127,  110,  130,  131,  132,    0,    0,
    2,    4,    5,    6,    7,    8,    9,    0,    0,    0,
  147,    0,    0,  155,   30,    0,    0,    0,    0,    0,
    0,   15,    0,    0,    0,    0,  136,  114,    0,  137,
  139,    0,    0,    0,   38,   43,    0,  206,    0,  208,
  223,  224,    0,    0,  207,    0,    0,    0,    0,   17,
    0,    0,    0,    0,    0,    0,    0,   58,    0,    0,
   59,   60,    0,    0,  108,  107,  102,  105,  104,  103,
    0,   97,   96,   98,    0,  109,    0,    0,    0,    0,
    0,    0,   90,    0,   95,  100,  106,    0,  153,   31,
    0,   42,  186,    0,    0,    0,    0,    0,    0,    0,
  163,    0,    0,    0,  191,    0,    0,  133,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   20,   21,   22,
   13,   18,   23,   24,    0,    0,    0,    0,   41,   56,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   94,  189,   70,    0,    0,    0,  165,
  199,    0,   25,   10,  162,  164,    0,  188,    0,  192,
    0,  169,  170,  171,    0,  172,    0,    0,   50,    0,
    0,    0,  138,    0,    0,    0,    0,    0,    0,    0,
    0,   40,    0,  101,    0,    0,    0,    0,    0,    0,
    0,   91,   92,   93,    0,  183,  167,    0,    0,  194,
  134,    0,    0,    0,    0,    0,    0,  195,    0,  214,
  216,  215,  210,    0,    0,    0,    0,    0,   69,    0,
    0,    0,    0,   62,   61,   39,  184,   26,  187,    0,
   51,    0,   53,    0,    0,  196,    0,    0,    0,    0,
    0,  204,    0,   64,    0,    0,   65,    0,    0,    0,
    0,  174,    0,    0,    0,    0,   47,  197,  213,    0,
  209,    0,    0,  205,   63,    0,   68,    0,  181,  168,
  175,    0,    0,  178,   46,  211,    0,    0,    0,   66,
  180,  182,  177,    0,  217,    0,    0,    0,  220,  221,
};
short yydgoto[] = {                                      12,
  117,  118,  119,  198,  185,  131,   71,   72,   73,   74,
   75,   45,   46,   47,   48,   49,   50,   51,   52,   76,
   77,   78,   79,   80,   81,  132,  165,  201,   84,  134,
  135,  304,   13,   14,  136,  137,  138,   18,   19,   20,
   21,   22,   23,  139,  112,  140,  141,  142,  143,  243,
   24,   25,   26,   27,  126,   28,  149,  204,  262,  259,
  150,  151,  152,  311,  312,  337,  313,   57,  166,  167,
  168,  169,  170,  171,  172,  173,  174,  175,  176,  177,
  178,   85,   29,   30,   31,  120,  121,  190,  191,  186,
  187,  257,  341,  342,  343,  344,  363,  345,  184,  238,
  195,  196,  298,  267,  144,  307,  332,  305,  329,  368,
  377,
};
short yysindex[] = {                                    515,
 -229,  492, -215, -178, -161, -157, -150, -143,  321, -117,
 -108,    0,    0,  515,  147,  165,  176,  177,  182,  185,
    0,    0,  122,    0,    0,    0,    0,  128,    0,    0,
    0,  -59,    0,    0,    0,    0,  -23,    0,  193, -200,
  -54,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  -46,  -50,  -45,  150,  160,
  226,  166,  174,    0,    0,    0,  235,    0,  -10,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  -46,    0,    0,    0,    0,    0,   25,  155,
    0,    0,    0,    0,    0,    0,    0,  266,  221,   -5,
    0,  -39,   38,    0,    0,   -8,  243,  -49,   -1,  321,
 -220,    0,  515,  321,  407,  228,    0,    0,  279,    0,
    0,  284, -220, -128,    0,    0,  468,    0,   66,    0,
    0,    0,  -46,   21,    0,  268,  271,  275,  210,    0,
  266,  277,  278,  431,   28,  321,  321,    0,  213,  221,
    0,    0,  266,  220,    0,    0,    0,    0,    0,    0,
  -39,    0,    0,    0,  -46,    0,  227,  250,  314, -236,
  172,  140,    0,  -32,    0,    0,    0,  294,    0,    0,
  -39,    0,    0,  315,  -10,  321,  233,  -42,  236,  248,
    0,  321,   58,  -39,    0,  228,  -10,    0,  457,  -46,
  332, -220,  -46,  342,   69,  468,  347,    0,    0,    0,
    0,    0,    0,    0,   80,  352,  -10,  -10,    0,    0,
  274,  266,  355,  -39,  -39,  -39,  -39,  -39,  -39,  -39,
  -39,  -39,  -39,    0,    0,    0,   -1,  276,  341,    0,
    0, -220,    0,    0,    0,    0,  -39,    0,  309,    0,
  279,    0,    0,    0,  -46,    0,  362, -220,    0,  342,
 -220,  112,    0,  361,   69,   33,  120,  347,  -36,  348,
  349,    0,  286,    0,  250,  314, -236,  172,  172,  140,
  140,    0,    0,    0,  315,    0,    0,  -42,  364,    0,
    0,  291,  332,  135,  342, -220,   69,    0,  361,    0,
    0,    0,    0,  468,  387,  401,  184,  120,    0,  390,
  410,  412,  468,    0,    0,    0,    0,    0,    0,  -24,
    0, -220,    0,  332,  361,    0,   69,  -53,  413, -220,
  418,    0,  184,    0,  400,  189,    0,   69,  -39,  404,
  339,    0,  -24,  321,  -24,  332,    0,    0,    0,  387,
    0,  -41,  157,    0,    0,  412,    0,  411,    0,    0,
    0,  -10,  406,    0,    0,    0, -220,  429,  427,    0,
    0,    0,    0,  -46,    0,  162,  434,  427,    0,    0,
};
short yyrindex[] = {                                      0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   27,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  -31,    0,  -20,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  167,    0,    0,    0,    0,
  -30,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  -12,    0,    0,    0,    0,    0,    0,   14,
    0,    0,    0,    0,    0,    0,    0,  351,  357,  426,
    0,    0,  -25,    0,    0,    0,    0,  354,    0,  370,
    0,    0,    0,    0,    0,   88,    0,    0,  428,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  175,    0,    0,    0,    0,    0,    0,    0,
  351,    0,    0,    0,    0,    0,    0,    0,    0,  357,
    0,    0,  351,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   17,    0,  304,   22,  134,  331,
  188,  247,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  371,    0,  370,    0,  374,    0,    0,
    0,  370,    0,    0,    0,  130,    0,    0,    0,    5,
  377,    0,  -29, -101,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  351,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  428,    0,    0,    0,  466,    0,    0,    0,    0, -101,
    0,  386,    0,  454,    0,    0,  455,    0,    0,    0,
    0,    0,    0,    0,  375,  336,  380,  316,  326,  255,
  288,    0,    0,    0,  371,    0,    0,  374,    0,    0,
    0,    0,  377,  392, -101,    0,    0,    0,  454,    0,
    0,    0,    0,    0,  475,    0,  461,  462,    0,    0,
    0,  489,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  377,  454,    0,    0,    0,    0,    0,
    0,    0,  472,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  415,    0,  366,  377,    0,    0,    0,  475,
    0,  495,    0,    0,    0,  489,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  496,    0,
    0,    0,    0,  497,    0,    0,    0,  496,    0,    0,
};
short yygindex[] = {                                      0,
 -162,  -58, -174,  290,   11,   16,  430,    0,    0,  540,
   10,    0,    0,    0,    0,    0,    0,    0,    0,   12,
    0,   15,    0,    0,    0,    9,   -2, -218,    0,  405,
 -106,    0,   53,    0,   30,   51,   56,    0,    0,    0,
    0,    0,    0,    0,    0, -115,  -33,    0,    0,  256,
    0,    0,    0,    0,  -18,    0,  408, -166, -203, -241,
    0,    0,    0,    0,  214,  198,    0,    0, -120,    0,
  337,  340,  343,    6,   19,  -52,    0,  396,    0,    0,
 -149,    0,   26,   39,   24,    0,    0,    0,    0,  452,
   13,    0,    0,  230,    0,  229,    0,    0,  334,  293,
  379,    0, -253,  308,    0,  272,  249,  257,  234,    0,
  208,
};
#define YYTABLESIZE 815
short yytable[] = {                                      56,
  161,  242,  367,  162,  310,  163,   83,  161,  124,  148,
   55,   44,  148,   53,   55,  154,   54,   82,  154,   69,
  205,   54,  251,  190,   70,  212,    3,  148,   14,   15,
  148,  119,   88,  154,   86,  260,  154,  221,  190,  293,
  223,  190,  264,   15,  249,  326,  119,   87,   28,  119,
   16,  321,  124,   99,   99,   17,  294,   99,   99,   99,
  236,   99,   78,   99,   16,  148,   91,  227,  228,   17,
   32,  348,   37,  303,   99,   99,  103,  324,   99,   78,
   78,  154,  347,   78,   58,   41,  164,   83,  104,  182,
   42,  323,   16,   55,  295,  133,  133,  289,   82,  265,
  125,  247,  299,  346,  365,   70,  273,   83,  188,   99,
   99,   83,   83,   88,   78,   86,  148,  153,   82,  248,
  200,  203,   82,   82,  133,   70,  239,   28,   87,   70,
   70,  138,   59,   88,  325,   86,   45,   88,  133,   86,
   99,  133,   15,   83,   83,   78,  138,  133,   87,   60,
  133,    3,   87,   61,   82,   82,  217,  218,  270,  271,
   62,   70,   70,   16,  349,  189,  202,   63,   17,   88,
   88,   86,   86,  193,   80,  357,  233,   41,  282,  283,
  284,  231,   42,   83,   87,   87,  232,  372,  193,   83,
   54,   80,   80,   89,   82,   80,  255,  327,  240,  203,
   82,   70,   90,  133,  246,   92,  338,   70,  252,   88,
  253,   86,  124,  254,  229,   88,  230,   86,  358,  133,
  300,  301,  256,   93,   87,   84,   80,   80,   84,  302,
   87,  155,  278,  279,   94,   95,  339,  309,  155,  288,
   96,  340,  123,   97,   98,   84,   84,  280,  281,   84,
   99,  100,  102,  101,  156,  200,  105,   80,  203,  106,
  107,  156,   55,  106,  106,  108,   41,  157,  158,  159,
  160,   42,  109,   41,  157,  158,  159,  160,   42,  148,
   84,   84,  110,  111,   87,  154,  123,   87,  113,   87,
  190,   87,   88,  200,  115,   88,  114,   88,  119,   88,
  116,  133,  180,  181,   87,   87,  300,  301,   87,  183,
  133,   84,   88,   88,  179,  302,   88,  122,  194,  200,
   99,   99,  197,  199,  206,   89,  208,  352,   89,  209,
   89,  207,   89,  210,  211,  213,  214,  219,  216,   87,
   87,   83,  222,  225,   77,   89,   89,   88,   88,   89,
  224,  226,   82,   86,  362,  235,   86,  241,  237,   70,
  244,   77,   77,   85,  374,   77,   85,   88,   82,   86,
   87,   82,  245,   86,   86,  258,   81,   86,   88,  263,
   89,   89,   87,   85,   85,  261,  266,   85,   82,   82,
  268,  269,   82,   81,   81,  274,   77,   81,  272,  287,
  286,  290,  292,  296,  297,  306,  314,  315,   86,   86,
  316,   89,   64,  320,   33,   79,   34,   83,   85,   85,
   83,   35,    4,   82,   82,  319,  322,   36,   81,   81,
  328,   37,   79,   79,   65,   66,   79,   83,   83,   86,
  330,   83,   67,   38,   39,    8,  123,  331,  334,   85,
  335,   10,   40,  351,   82,  336,   68,  353,  355,   81,
   41,  359,  309,  360,  373,   42,  369,   79,  371,  375,
  376,  378,   83,   83,  379,   19,   44,   76,   64,  127,
   33,   57,   34,    2,   36,  225,  135,   35,    4,    5,
  145,   84,   84,   36,  166,  185,   27,   37,   79,   52,
   65,   66,  128,   83,  146,  147,  173,  129,   49,   38,
   39,    8,  198,  200,   48,  212,    9,   10,   40,  202,
  201,  130,   68,   64,  127,   33,   41,   34,    2,   67,
  203,   42,   35,    4,    5,  219,  222,  218,   36,  176,
  291,   43,   37,  318,  193,   65,   66,  128,  215,  356,
   87,   87,  129,  370,   38,   39,    8,  220,   88,   88,
  275,    9,   10,   40,  276,  192,  130,   68,  277,  234,
  285,   41,  361,  364,  250,  308,   42,  317,   64,  333,
   33,  354,   34,  366,  350,  380,    0,   35,    4,    0,
    0,   89,   89,   36,    0,    0,    0,   37,    0,    0,
   65,   66,    0,    0,    0,    0,    0,    0,   67,   38,
   39,    8,    0,    0,    0,    0,    0,   10,   40,   86,
   86,    0,   68,  179,    0,  179,   41,  179,    0,   85,
   85,   42,  179,  179,    0,    0,    0,    0,  179,    0,
    0,    0,  179,    0,    0,  179,  179,    0,    0,    0,
    0,    0,    0,  179,  179,  179,  179,    0,    0,    0,
    0,    0,  179,  179,   64,    0,   33,  179,   34,    0,
    0,  179,    0,   35,    0,    0,  179,    0,    0,   36,
    0,    0,    0,   37,    0,    0,   65,   66,   64,    0,
   33,    0,   34,    0,   67,   38,   39,   35,    0,    0,
    0,    0,    0,   36,   40,    0,    0,   37,   68,    0,
   65,   66,   41,    0,    0,    0,   33,   42,   34,   38,
   39,    0,    0,    0,    4,   64,    0,   33,   40,   34,
    0,  130,   68,   37,   35,    0,   41,    0,    0,    0,
   36,   42,    0,    0,   37,   38,    0,   65,   66,    0,
    0,   33,    0,   34,   40,    0,   38,   39,   35,    0,
    0,    0,   41,    0,   36,   40,    0,   42,   37,   68,
    0,    1,    0,   41,    0,    0,    0,    2,   42,    3,
   38,   39,    4,    5,    0,    0,    0,    0,    0,   40,
    6,    0,    7,    0,    0,    0,    0,   41,    0,    0,
    0,    0,   42,    0,    0,    8,    0,    0,    0,    0,
    9,   10,    0,    0,   11,
};
short yycheck[] = {                                       2,
   40,   44,   44,   43,   41,   45,    9,   40,   58,   41,
    2,    2,   44,    2,   44,   41,    2,    9,   44,    9,
  127,  123,  197,   44,    9,  141,    0,   59,   59,    0,
   62,   44,    9,   59,    9,  202,   62,  153,   59,  258,
  161,   62,  205,   14,  194,  299,   59,    9,   44,   62,
    0,  293,   58,   37,   38,    0,  260,   41,   42,   43,
  181,   45,   41,   47,   14,   99,   14,  304,  305,   14,
  300,  325,   59,   41,   58,   59,  277,  296,   62,   58,
   59,  100,  324,   62,  300,  306,  126,   90,  289,  108,
  311,  295,  123,  123,  261,   98,   99,  247,   90,  206,
   90,   44,  265,  322,  346,   90,  222,  110,  111,   93,
   94,  114,  115,   90,   93,   90,  150,  123,  110,   62,
  123,  124,  114,  115,  127,  110,  185,  123,   90,  114,
  115,   44,  311,  110,  297,  110,  123,  114,  141,  114,
  124,  144,  113,  146,  147,  124,   59,  150,  110,  311,
  153,  125,  114,  311,  146,  147,  146,  147,  217,  218,
  311,  146,  147,  113,  327,  113,  295,  311,  113,  146,
  147,  146,  147,   44,   41,  338,   37,  306,  231,  232,
  233,   42,  311,  186,  146,  147,   47,  362,   59,  192,
  292,   58,   59,  311,  186,   62,  199,  304,  186,  202,
  192,  186,  311,  206,  192,   59,  313,  192,  199,  186,
  199,  186,   58,  199,   43,  192,   45,  192,  339,  222,
  274,  275,  199,   59,  186,   38,   93,   94,   41,  283,
  192,  271,  227,  228,   59,   59,  261,  274,  271,  242,
   59,  266,  292,   59,  123,   58,   59,  229,  230,   62,
  123,  311,   60,  277,  294,  258,  311,  124,  261,  306,
  311,  294,  292,  306,  306,  311,  306,  307,  308,  309,
  310,  311,  123,  306,  307,  308,  309,  310,  311,  311,
   93,   94,  123,   58,   38,  311,  292,   41,  123,   43,
  311,   45,   38,  296,   60,   41,  123,   43,  311,   45,
  311,  304,  311,   61,   58,   59,  274,  275,   62,  311,
  313,  124,   58,   59,  277,  283,   62,  293,   91,  322,
  304,  305,   44,   40,  259,   38,   59,  330,   41,   59,
   43,  311,   45,   59,  125,   59,   59,  125,  311,   93,
   94,  344,  123,   94,   41,   58,   59,   93,   94,   62,
  124,   38,  344,   38,  344,   62,   41,  125,   44,  344,
  125,   58,   59,   38,  367,   62,   41,  344,   38,  344,
  124,   41,  125,   58,   59,   44,   41,   62,  124,  311,
   93,   94,  344,   58,   59,   44,   40,   62,   58,   59,
  311,   40,   62,   58,   59,   41,   93,   62,  125,   59,
  125,   93,   41,  292,   44,  286,   59,   59,   93,   94,
  125,  124,  258,  123,  260,   41,  262,   38,   93,   94,
   41,  267,  268,   93,   94,   62,  292,  273,   93,   94,
   44,  277,   58,   59,  280,  281,   62,   58,   59,  124,
   40,   62,  288,  289,  290,  291,  292,  264,   59,  124,
   41,  297,  298,   41,  124,   44,  302,   40,   59,  124,
  306,   58,  274,  125,   59,  311,  310,   93,   58,   41,
   44,  310,   93,   94,   41,  125,  123,  311,  258,  259,
  260,  125,  262,  263,   59,  311,   59,  267,  268,  269,
  270,  304,  305,  273,  125,  125,  123,  277,  124,  123,
  280,  281,  282,  124,  284,  285,   41,  287,  123,  289,
  290,  291,   59,   59,  123,   41,  296,  297,  298,   59,
   59,  301,  302,  258,  259,  260,  306,  262,  263,   41,
   59,  311,  267,  268,  269,   41,   41,   41,  273,  125,
  251,    2,  277,  288,  115,  280,  281,  282,  144,  336,
  304,  305,  287,  356,  289,  290,  291,  150,  304,  305,
  224,  296,  297,  298,  225,  114,  301,  302,  226,  174,
  237,  306,  343,  345,  196,  268,  311,  285,  258,  308,
  260,  333,  262,  350,  328,  378,   -1,  267,  268,   -1,
   -1,  304,  305,  273,   -1,   -1,   -1,  277,   -1,   -1,
  280,  281,   -1,   -1,   -1,   -1,   -1,   -1,  288,  289,
  290,  291,   -1,   -1,   -1,   -1,   -1,  297,  298,  304,
  305,   -1,  302,  258,   -1,  260,  306,  262,   -1,  304,
  305,  311,  267,  268,   -1,   -1,   -1,   -1,  273,   -1,
   -1,   -1,  277,   -1,   -1,  280,  281,   -1,   -1,   -1,
   -1,   -1,   -1,  288,  289,  290,  291,   -1,   -1,   -1,
   -1,   -1,  297,  298,  258,   -1,  260,  302,  262,   -1,
   -1,  306,   -1,  267,   -1,   -1,  311,   -1,   -1,  273,
   -1,   -1,   -1,  277,   -1,   -1,  280,  281,  258,   -1,
  260,   -1,  262,   -1,  288,  289,  290,  267,   -1,   -1,
   -1,   -1,   -1,  273,  298,   -1,   -1,  277,  302,   -1,
  280,  281,  306,   -1,   -1,   -1,  260,  311,  262,  289,
  290,   -1,   -1,   -1,  268,  258,   -1,  260,  298,  262,
   -1,  301,  302,  277,  267,   -1,  306,   -1,   -1,   -1,
  273,  311,   -1,   -1,  277,  289,   -1,  280,  281,   -1,
   -1,  260,   -1,  262,  298,   -1,  289,  290,  267,   -1,
   -1,   -1,  306,   -1,  273,  298,   -1,  311,  277,  302,
   -1,  257,   -1,  306,   -1,   -1,   -1,  263,  311,  265,
  289,  290,  268,  269,   -1,   -1,   -1,   -1,   -1,  298,
  276,   -1,  278,   -1,   -1,   -1,   -1,  306,   -1,   -1,
   -1,   -1,  311,   -1,   -1,  291,   -1,   -1,   -1,   -1,
  296,  297,   -1,   -1,  300,
};
#define YYFINAL 12
#ifndef YYDEBUG
#define YYDEBUG 1
#endif
#define YYMAXTOKEN 311
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,"'%'","'&'",0,"'('","')'","'*'","'+'","','","'-'",0,"'/'",0,0,0,0,0,0,0,0,
0,0,"':'","';'","'<'","'='","'>'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,"'['",0,"']'","'^'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,"'{'","'|'","'}'","'~'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"ABSTRACT","ANY","ATTRIBUTE",
"BOOLEAN","CASE","CHAR","CONST","CONTEXT","CUSTOM","DEFAULT","DOUBLE","ENUM",
"EXCEPTION","FACTORY","FALSE_TOKEN","FIXED","FLOAT","IN","INOUT","INTERFACE",
"LONG","MODULE","NATIVE","OBJECT","OCTET","ONEWAY","OUT","PRIVATE","PUBLIC",
"RAISES","READONLY","SEQUENCE","SHORT","STRING","STRUCT","SUPPORTS","SWITCH",
"TRUE_TOKEN","TRANCATABLE","TYPEDEF","UNION","UNSIGNED","VALUEBASE","VALUETYPE",
"VOID","WCHAR","WSTRING","LEFT_SHIFT","RIGHT_SHIFT","SCOPE_DELIMITOR",
"INTEGER_LITERAL","FLOATING_PT_LITERAL","CHARACTER_LITERAL","STRING_LITERAL",
"IDENTIFIER",
};
char *yyrule[] = {
"$accept : specification",
"specification : at_least_one_definition",
"at_least_one_definition : definition at_least_one_definition",
"at_least_one_definition : definition",
"definition : type_dcl ';'",
"definition : const_dcl ';'",
"definition : except_dcl ';'",
"definition : interface ';'",
"definition : module ';'",
"definition : value ';'",
"module : MODULE IDENTIFIER '{' at_least_one_definition '}'",
"interface : interface_dcl",
"interface : forward_dcl",
"interface_dcl : interface_header '{' interface_body '}'",
"forward_dcl : INTERFACE IDENTIFIER",
"interface_header : INTERFACE IDENTIFIER inheritance_spec",
"interface_header : INTERFACE IDENTIFIER",
"interface_body : exports",
"exports : export exports",
"exports :",
"export : type_dcl ';'",
"export : const_dcl ';'",
"export : except_dcl ';'",
"export : attr_dcl ';'",
"export : op_dcl ';'",
"inheritance_spec : ':' scoped_name extends_inheritance",
"extends_inheritance : ',' scoped_name extends_inheritance",
"extends_inheritance :",
"interface_name : scoped_name",
"scoped_name : IDENTIFIER",
"scoped_name : SCOPE_DELIMITOR IDENTIFIER",
"scoped_name : scoped_name SCOPE_DELIMITOR IDENTIFIER",
"value : value_dcl",
"value : value_abs_dcl",
"value : value_box_dcl",
"value : value_forward_dcl",
"value_forward_dcl : ABSTRACT VALUETYPE IDENTIFIER",
"value_forward_dcl : VALUETYPE IDENTIFIER",
"value_box_dcl : VALUETYPE IDENTIFIER type_spec",
"value_abs_dcl : ABSTRACT VALUETYPE IDENTIFIER value_inheritance_spec '{' exports '}'",
"value_abs_dcl : ABSTRACT VALUETYPE IDENTIFIER '{' exports '}'",
"value_dcl : value_header '{' value_elements '}'",
"value_header : CUSTOM VALUETYPE IDENTIFIER value_inheritance_spec",
"value_header : VALUETYPE IDENTIFIER value_inheritance_spec",
"value_header : CUSTOM VALUETYPE IDENTIFIER",
"value_header : VALUETYPE IDENTIFIER",
"value_inheritance_spec : ':' TRANCATABLE value_name extends_value_name SUPPORTS interface_name extends_interface_name",
"value_inheritance_spec : ':' value_name extends_value_name SUPPORTS interface_name extends_interface_name",
"value_inheritance_spec : ':' TRANCATABLE value_name extends_value_name",
"value_inheritance_spec : ':' value_name extends_value_name",
"value_inheritance_spec : SUPPORTS interface_name extends_interface_name",
"extends_interface_name : ',' interface_name extends_interface_name",
"extends_interface_name :",
"extends_value_name : ',' value_name extends_value_name",
"extends_value_name :",
"value_name : scoped_name",
"value_elements : value_element value_elements",
"value_elements :",
"value_element : export",
"value_element : state_member",
"value_element : init_dcl",
"state_member : PUBLIC type_spec declarators ';'",
"state_member : PRIVATE type_spec declarators ';'",
"init_dcl : FACTORY IDENTIFIER '(' init_param_decls ')' ';'",
"init_dcl : FACTORY IDENTIFIER '(' ')' ';'",
"init_param_decls : init_param_decl extends_init_param_decl",
"extends_init_param_decl : ',' init_param_decl extends_init_param_decl",
"extends_init_param_decl :",
"init_param_decl : init_param_attribute param_type_spec simple_declarator",
"init_param_attribute : IN",
"const_dcl : CONST const_type IDENTIFIER '=' const_exp",
"const_type : integer_type",
"const_type : char_type",
"const_type : boolean_type",
"const_type : floating_pt_type",
"const_type : string_type",
"const_type : scoped_name",
"const_exp : or_expr",
"or_expr : xor_expr",
"or_expr : or_expr '|' xor_expr",
"xor_expr : and_expr",
"xor_expr : xor_expr '^' and_expr",
"and_expr : shift_expr",
"and_expr : and_expr '&' shift_expr",
"shift_expr : add_expr",
"shift_expr : shift_expr RIGHT_SHIFT add_expr",
"shift_expr : shift_expr LEFT_SHIFT add_expr",
"add_expr : mult_expr",
"add_expr : add_expr '+' mult_expr",
"add_expr : add_expr '-' mult_expr",
"mult_expr : unary_expr",
"mult_expr : mult_expr '*' unary_expr",
"mult_expr : mult_expr '/' unary_expr",
"mult_expr : mult_expr '%' unary_expr",
"unary_expr : unary_operator primary_expr",
"unary_expr : primary_expr",
"unary_operator : '-'",
"unary_operator : '+'",
"unary_operator : '~'",
"primary_expr : scoped_name",
"primary_expr : literal",
"primary_expr : '(' const_exp ')'",
"literal : INTEGER_LITERAL",
"literal : STRING_LITERAL",
"literal : CHARACTER_LITERAL",
"literal : FLOATING_PT_LITERAL",
"literal : boolean_literal",
"boolean_literal : TRUE_TOKEN",
"boolean_literal : FALSE_TOKEN",
"positive_int_const : const_exp",
"type_dcl : TYPEDEF type_declarator",
"type_dcl : struct_type",
"type_dcl : union_type",
"type_dcl : enum_type",
"type_declarator : type_spec declarators",
"type_spec : simple_type_spec",
"type_spec : constr_type_spec",
"simple_type_spec : base_type_spec",
"simple_type_spec : template_type_spec",
"simple_type_spec : scoped_name",
"base_type_spec : floating_pt_type",
"base_type_spec : integer_type",
"base_type_spec : char_type",
"base_type_spec : wide_char_type",
"base_type_spec : boolean_type",
"base_type_spec : octet_type",
"base_type_spec : any_type",
"base_type_spec : object_type",
"template_type_spec : sequence_type",
"template_type_spec : string_type",
"constr_type_spec : struct_type",
"constr_type_spec : union_type",
"constr_type_spec : enum_type",
"declarators : declarator extend_declarators",
"extend_declarators : ',' declarator extend_declarators",
"extend_declarators :",
"declarator : simple_declarator",
"declarator : complex_declarator",
"simple_declarator : IDENTIFIER",
"complex_declarator : array_declarator",
"floating_pt_type : FLOAT",
"floating_pt_type : DOUBLE",
"integer_type : signed_int",
"integer_type : unsigned_int",
"signed_int : signed_long_long_int",
"signed_int : signed_long_int",
"signed_int : signed_short_int",
"signed_long_long_int : LONG LONG",
"signed_long_int : LONG",
"signed_short_int : SHORT",
"unsigned_int : unsigned_long_long_int",
"unsigned_int : unsigned_long_int",
"unsigned_int : unsigned_short_int",
"unsigned_long_long_int : UNSIGNED LONG LONG",
"unsigned_long_int : UNSIGNED LONG",
"unsigned_short_int : UNSIGNED SHORT",
"char_type : CHAR",
"wide_char_type : WCHAR",
"boolean_type : BOOLEAN",
"octet_type : OCTET",
"any_type : ANY",
"object_type : OBJECT",
"struct_type : STRUCT IDENTIFIER '{' member_list '}'",
"member_list : at_least_one_member",
"at_least_one_member : member members",
"members : member members",
"members :",
"member : type_spec declarators ';'",
"union_type : UNION IDENTIFIER SWITCH '(' switch_type_spec ')' '{' switch_body '}'",
"switch_type_spec : integer_type",
"switch_type_spec : char_type",
"switch_type_spec : boolean_type",
"switch_type_spec : enum_type",
"switch_type_spec : scoped_name",
"switch_body : at_least_one_case",
"at_least_one_case : case at_least_one_case",
"at_least_one_case : case",
"case : at_least_one_case_label element_spec ';'",
"at_least_one_case_label : case_label at_least_one_case_label",
"at_least_one_case_label : case_label",
"case_label : CASE const_exp ':'",
"case_label : DEFAULT ':'",
"element_spec : type_spec declarator",
"enum_type : ENUM IDENTIFIER '{' enumerator extends_enum '}'",
"extends_enum : ',' enumerator extends_enum",
"extends_enum :",
"enumerator : IDENTIFIER",
"sequence_type : SEQUENCE '<' simple_type_spec ',' positive_int_const '>'",
"sequence_type : SEQUENCE '<' simple_type_spec '>'",
"string_type : STRING '<' positive_int_const '>'",
"string_type : STRING",
"array_declarator : IDENTIFIER at_least_one_fixed_array_size",
"at_least_one_fixed_array_size : fixed_array_size at_least_one_fixed_array_size",
"at_least_one_fixed_array_size : fixed_array_size",
"fixed_array_size : '[' positive_int_const ']'",
"attr_dcl : ATTRIBUTE param_type_spec simple_declarator extends_attr",
"attr_dcl : READONLY ATTRIBUTE param_type_spec simple_declarator extends_attr",
"extends_attr : ',' simple_declarator extends_attr",
"extends_attr :",
"except_dcl : EXCEPTION IDENTIFIER '{' members '}'",
"op_dcl : op_type_spec IDENTIFIER parameter_dcls",
"op_dcl : op_attribute op_type_spec IDENTIFIER parameter_dcls",
"op_dcl : op_type_spec IDENTIFIER parameter_dcls raises_expr",
"op_dcl : op_attribute op_type_spec IDENTIFIER parameter_dcls raises_expr",
"op_dcl : op_type_spec IDENTIFIER parameter_dcls raises_expr context_expr",
"op_dcl : op_attribute op_type_spec IDENTIFIER parameter_dcls raises_expr context_expr",
"op_attribute : ONEWAY",
"op_type_spec : param_type_spec",
"op_type_spec : VOID",
"parameter_dcls : '(' param_dcl extends_param ')'",
"parameter_dcls : '(' ')'",
"extends_param : ',' param_dcl extends_param",
"extends_param :",
"param_dcl : param_attribute param_type_spec simple_declarator",
"param_attribute : IN",
"param_attribute : OUT",
"param_attribute : INOUT",
"raises_expr : RAISES '(' scoped_name extends_raises ')'",
"extends_raises : ',' scoped_name",
"extends_raises :",
"context_expr : CONTEXT '(' STRING_LITERAL extends_context ')'",
"extends_context : ',' STRING_LITERAL extends_context",
"extends_context :",
"param_type_spec : base_type_spec",
"param_type_spec : string_type",
"param_type_spec : scoped_name",
};
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH 500
#endif
#endif
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short yyss[YYSTACKSIZE];
YYSTYPE yyvs[YYSTACKSIZE];
#define yystacksize YYSTACKSIZE
#line 674 "./idl-g.yy"


int yywrap()
{
  return 1;
}
#line 735 "y.tab.c"
#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
yyparse()
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register char *yys;
    extern char *getenv();

    if (yys = getenv("YYDEBUG"))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if (yyn = yydefred[yystate]) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yyss + yystacksize - 1)
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
#ifdef lint
    goto yynewerror;
#endif
yynewerror:
    yyerror("syntax error");
#ifdef lint
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yyss + yystacksize - 1)
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
case 14:
#line 151 "./idl-g.yy"
{gen_add_type (yyvsp[0].strval, TYPE_INTERFACE);}
break;
case 15:
#line 154 "./idl-g.yy"
{
                                gen_add_type (yyvsp[-1].strval, TYPE_INTERFACE);
                                gen_add_interface (yyvsp[-1].strval);
                }
break;
case 16:
#line 159 "./idl-g.yy"
{
                                gen_add_type (yyvsp[0].strval, TYPE_INTERFACE);
                                gen_add_interface (yyvsp[0].strval);
                }
break;
case 28:
#line 186 "./idl-g.yy"
{yyval.strval = yyvsp[0].strval;}
break;
case 29:
#line 190 "./idl-g.yy"
{yyval.strval = yyvsp[0].strval;}
break;
case 30:
#line 192 "./idl-g.yy"
{yyval.strval = "void";}
break;
case 31:
#line 194 "./idl-g.yy"
{yyval.strval = "void";}
break;
case 42:
#line 220 "./idl-g.yy"
{gen_add_value (yyvsp[-1].strval);}
break;
case 43:
#line 222 "./idl-g.yy"
{gen_add_value (yyvsp[-1].strval);}
break;
case 44:
#line 224 "./idl-g.yy"
{gen_add_value (yyvsp[0].strval);}
break;
case 45:
#line 226 "./idl-g.yy"
{gen_add_value (yyvsp[0].strval);}
break;
case 46:
#line 232 "./idl-g.yy"
{gen_add_int_to_value (yyvsp[-1].strval);}
break;
case 47:
#line 236 "./idl-g.yy"
{gen_add_int_to_value (yyvsp[-1].strval);}
break;
case 50:
#line 241 "./idl-g.yy"
{gen_add_int_to_value (yyvsp[-1].strval);}
break;
case 51:
#line 245 "./idl-g.yy"
{gen_add_int_to_value (yyvsp[-1].strval);}
break;
case 63:
#line 270 "./idl-g.yy"
{gen_add_constr_to_value (yyvsp[-4].strval);}
break;
case 64:
#line 272 "./idl-g.yy"
{gen_add_constr_to_value (yyvsp[-3].strval);}
break;
case 114:
#line 366 "./idl-g.yy"
{gen_add_type (yyvsp[0].strval, yyvsp[-1].ival);}
break;
case 115:
#line 370 "./idl-g.yy"
{yyval.ival = yyvsp[0].ival;}
break;
case 116:
#line 372 "./idl-g.yy"
{yyval.ival = yyvsp[0].ival;}
break;
case 117:
#line 376 "./idl-g.yy"
{yyval.ival = yyvsp[0].ival;}
break;
case 118:
#line 378 "./idl-g.yy"
{yyval.ival = yyvsp[0].ival;}
break;
case 119:
#line 380 "./idl-g.yy"
{yyval.ival = 0;}
break;
case 120:
#line 384 "./idl-g.yy"
{yyval.ival = yyvsp[0].ival;}
break;
case 121:
#line 386 "./idl-g.yy"
{yyval.ival = yyvsp[0].ival;}
break;
case 122:
#line 388 "./idl-g.yy"
{yyval.ival = yyvsp[0].ival;}
break;
case 123:
#line 390 "./idl-g.yy"
{yyval.ival = yyvsp[0].ival;}
break;
case 124:
#line 392 "./idl-g.yy"
{yyval.ival = yyvsp[0].ival;}
break;
case 125:
#line 394 "./idl-g.yy"
{yyval.ival = yyvsp[0].ival;}
break;
case 126:
#line 396 "./idl-g.yy"
{yyval.ival = yyvsp[0].ival;}
break;
case 127:
#line 398 "./idl-g.yy"
{yyval.ival = yyvsp[0].ival;}
break;
case 128:
#line 402 "./idl-g.yy"
{yyval.ival = yyvsp[0].ival;}
break;
case 129:
#line 404 "./idl-g.yy"
{yyval.ival = yyvsp[0].ival;}
break;
case 130:
#line 408 "./idl-g.yy"
{yyval.ival = 0;}
break;
case 131:
#line 410 "./idl-g.yy"
{yyval.ival = 0;}
break;
case 132:
#line 412 "./idl-g.yy"
{yyval.ival = 0;}
break;
case 133:
#line 416 "./idl-g.yy"
{yyval.strval = yyvsp[-1].strval;}
break;
case 134:
#line 420 "./idl-g.yy"
{yyval.strval = yyvsp[-1].strval;}
break;
case 135:
#line 422 "./idl-g.yy"
{yyval.strval = 0;}
break;
case 136:
#line 426 "./idl-g.yy"
{yyval.strval = yyvsp[0].strval;}
break;
case 137:
#line 428 "./idl-g.yy"
{yyval.strval = 0;}
break;
case 138:
#line 432 "./idl-g.yy"
{yyval.strval = yyvsp[0].strval;}
break;
case 140:
#line 439 "./idl-g.yy"
{yyval.ival = ENUM_FLOAT;}
break;
case 141:
#line 441 "./idl-g.yy"
{yyval.ival = ENUM_DOUBLE;}
break;
case 142:
#line 445 "./idl-g.yy"
{yyval.ival = yyvsp[0].ival;}
break;
case 143:
#line 447 "./idl-g.yy"
{yyval.ival = yyvsp[0].ival;}
break;
case 144:
#line 451 "./idl-g.yy"
{yyval.ival = yyvsp[0].ival;}
break;
case 145:
#line 453 "./idl-g.yy"
{yyval.ival = yyvsp[0].ival;}
break;
case 146:
#line 455 "./idl-g.yy"
{yyval.ival = yyvsp[0].ival;}
break;
case 147:
#line 459 "./idl-g.yy"
{yyval.ival = ENUM_SIGNED_LONG_LONG_INT;}
break;
case 148:
#line 463 "./idl-g.yy"
{yyval.ival = ENUM_SIGNED_LONG_INT;}
break;
case 149:
#line 467 "./idl-g.yy"
{yyval.ival = ENUM_SIGNED_SHORT_INT;}
break;
case 153:
#line 476 "./idl-g.yy"
{yyval.ival = ENUM_UNSIGNED_LONG_LONG_INT;}
break;
case 154:
#line 480 "./idl-g.yy"
{yyval.ival = ENUM_UNSIGNED_LONG_INT;}
break;
case 155:
#line 484 "./idl-g.yy"
{yyval.ival = ENUM_UNSIGNED_SHORT_INT;}
break;
case 156:
#line 488 "./idl-g.yy"
{yyval.ival = ENUM_CHAR;}
break;
case 157:
#line 492 "./idl-g.yy"
{yyval.ival = ENUM_WIDE_CHAR;}
break;
case 158:
#line 496 "./idl-g.yy"
{yyval.ival = ENUM_BOOLEAN;}
break;
case 159:
#line 500 "./idl-g.yy"
{yyval.ival = ENUM_OCTET;}
break;
case 160:
#line 504 "./idl-g.yy"
{yyval.ival = ENUM_ANY;}
break;
case 161:
#line 508 "./idl-g.yy"
{yyval.ival = ENUM_OBJECT;}
break;
case 162:
#line 512 "./idl-g.yy"
{gen_add_type (yyvsp[-3].strval, TYPE_STRUCT);}
break;
case 187:
#line 571 "./idl-g.yy"
{yyval.ival = TYPE_SEQUENCE;}
break;
case 188:
#line 573 "./idl-g.yy"
{yyval.ival = TYPE_SEQUENCE;}
break;
case 189:
#line 577 "./idl-g.yy"
{yyval.ival = TYPE_STRING;}
break;
case 190:
#line 579 "./idl-g.yy"
{yyval.ival = TYPE_STRING;}
break;
case 199:
#line 604 "./idl-g.yy"
{gen_add_exc (yyvsp[-3].strval);}
break;
case 200:
#line 609 "./idl-g.yy"
{gen_add_operation (yyvsp[-2].strval, yyvsp[-1].strval);}
break;
case 207:
#line 626 "./idl-g.yy"
{yyval.strval = yyvsp[0].strval;}
break;
case 208:
#line 628 "./idl-g.yy"
{yyval.strval = gen_translate_stdtype (VOID);}
break;
case 213:
#line 641 "./idl-g.yy"
{gen_add_op_parameter (yyvsp[-2].ival, yyvsp[-1].strval, yyvsp[0].strval);}
break;
case 214:
#line 645 "./idl-g.yy"
{yyval.ival = IN;}
break;
case 215:
#line 647 "./idl-g.yy"
{yyval.ival = OUT;}
break;
case 216:
#line 649 "./idl-g.yy"
{yyval.ival = INOUT;}
break;
case 223:
#line 667 "./idl-g.yy"
{yyval.strval = gen_translate_stdtype (yyvsp[0].ival);}
break;
case 224:
#line 669 "./idl-g.yy"
{yyval.strval = "void";}
break;
case 225:
#line 671 "./idl-g.yy"
{yyval.strval = yyvsp[0].strval;}
break;
#line 1190 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yyss + yystacksize - 1)
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    return (1);
yyaccept:
    return (0);
}
