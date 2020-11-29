/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    AUTO = 258,
    SIZEOF = 259,
    GOTO = 260,
    RETURN = 261,
    println = 262,
    DO = 263,
    WHILE = 264,
    FOR = 265,
    CONTINUE = 266,
    BREAK = 267,
    SWITCH = 268,
    DEFAULT = 269,
    CASE = 270,
    IF = 271,
    ELSE = 272,
    FLOAT = 273,
    DOUBLE = 274,
    CHAR = 275,
    VOID = 276,
    INT = 277,
    LONG = 278,
    BOOL = 279,
    SHORT = 280,
    VOLATILE = 281,
    CONST = 282,
    SIGNED = 283,
    UNSIGNED = 284,
    STATIC = 285,
    EXTERN = 286,
    INLINE = 287,
    TYPEDEF = 288,
    STRUCT = 289,
    ENUM = 290,
    UNION = 291,
    CONSTANT = 292,
    CONSTANT_INT = 293,
    CONSTANT_DOUBLE = 294,
    ELLIPSIS = 295,
    STRING_LITERAL = 296,
    ASSIGN_RIGHTSHIFT = 297,
    ASSIGN_LEFTSHIFT = 298,
    ASSIGN_ADD = 299,
    ASSIGN_SUB = 300,
    ASSIGN_MUL = 301,
    ASSIGN_DIV = 302,
    ASSIGN_MOD = 303,
    ASSIGN_AND = 304,
    ASSIGN_OR = 305,
    TYPE_NAME = 306,
    ASSIGN_XOR = 307,
    IDENTIFIER = 308,
    OP_RIGHTSHIFT = 309,
    OP_LEFTSHIFT = 310,
    OP_INC = 311,
    OP_DEC = 312,
    OP_PTR = 313,
    OP_AND = 314,
    OP_OR = 315,
    OP_LE = 316,
    OP_GE = 317,
    OP_EQ = 318,
    OP_NE = 319
  };
#endif
/* Tokens.  */
#define AUTO 258
#define SIZEOF 259
#define GOTO 260
#define RETURN 261
#define println 262
#define DO 263
#define WHILE 264
#define FOR 265
#define CONTINUE 266
#define BREAK 267
#define SWITCH 268
#define DEFAULT 269
#define CASE 270
#define IF 271
#define ELSE 272
#define FLOAT 273
#define DOUBLE 274
#define CHAR 275
#define VOID 276
#define INT 277
#define LONG 278
#define BOOL 279
#define SHORT 280
#define VOLATILE 281
#define CONST 282
#define SIGNED 283
#define UNSIGNED 284
#define STATIC 285
#define EXTERN 286
#define INLINE 287
#define TYPEDEF 288
#define STRUCT 289
#define ENUM 290
#define UNION 291
#define CONSTANT 292
#define CONSTANT_INT 293
#define CONSTANT_DOUBLE 294
#define ELLIPSIS 295
#define STRING_LITERAL 296
#define ASSIGN_RIGHTSHIFT 297
#define ASSIGN_LEFTSHIFT 298
#define ASSIGN_ADD 299
#define ASSIGN_SUB 300
#define ASSIGN_MUL 301
#define ASSIGN_DIV 302
#define ASSIGN_MOD 303
#define ASSIGN_AND 304
#define ASSIGN_OR 305
#define TYPE_NAME 306
#define ASSIGN_XOR 307
#define IDENTIFIER 308
#define OP_RIGHTSHIFT 309
#define OP_LEFTSHIFT 310
#define OP_INC 311
#define OP_DEC 312
#define OP_PTR 313
#define OP_AND 314
#define OP_OR 315
#define OP_LE 316
#define OP_GE 317
#define OP_EQ 318
#define OP_NE 319

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 69 "parser.y" /* yacc.c:1909  */

    class GrammarTreeNode* gtn;

#line 186 "parser.hpp" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */
