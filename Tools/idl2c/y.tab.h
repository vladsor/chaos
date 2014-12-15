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
typedef union {
  long                 ival;           /* Long value           */
  double               dval;           /* Double value         */
  float                fval;           /* Float value          */
  char                 cval;           /* Char value           */

  char                 *strval;        /* char * value         */
} YYSTYPE;
extern YYSTYPE yylval;
