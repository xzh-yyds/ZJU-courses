/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include "grammartree.h"
#include <cstdio>
#include "func.h"

extern char* yytext;
extern int col;
extern FILE* yyin;
extern FILE* yyout;
GrammarTreeNode* root = NULL;
extern int yylineno;
extern void yyerror(const char* msg);
extern int yylex(void);

string int2string(int a);
GrammarTreeNode *treeCreate(std::string name, int arg_cnt, ...);
void treeNodeFree(GrammarTreeNode *node);
void treePrint(GrammarTreeNode *node, int level);


#line 91 "parser.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.hpp".  */
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
#line 69 "parser.y" /* yacc.c:355  */

    class GrammarTreeNode* gtn;

#line 263 "parser.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 280 "parser.cpp" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  36
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1650

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  89
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  71
/* YYNRULES -- Number of rules.  */
#define YYNRULES  238
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  406

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   319

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    81,     2,     2,     2,    77,    69,     2,
      83,    84,    75,    73,    66,    74,    68,    76,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    67,    65,
      79,    82,    78,    80,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    85,     2,    86,    72,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    87,    70,    88,    71,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    76,    76,    80,    81,    82,    83,    84,    85,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,   102,
     103,   107,   108,   109,   110,   111,   112,   116,   117,   118,
     119,   120,   121,   125,   126,   130,   131,   132,   133,   137,
     138,   139,   143,   144,   145,   149,   150,   151,   152,   153,
     157,   158,   159,   163,   164,   168,   169,   173,   174,   178,
     179,   183,   184,   188,   189,   193,   194,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   212,   213,
     217,   221,   222,   226,   227,   228,   229,   230,   231,   232,
     233,   237,   238,   242,   243,   247,   248,   249,   250,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   267,
     268,   273,   274,   275,   279,   280,   284,   285,   289,   293,
     294,   295,   296,   300,   301,   305,   306,   307,   311,   312,
     313,   314,   315,   319,   320,   324,   325,   329,   331,   335,
     339,   340,   344,   345,   346,   347,   348,   349,   350,   351,
     352,   353,   354,   355,   356,   360,   361,   362,   363,   367,
     368,   373,   374,   378,   379,   383,   384,   385,   389,   390,
     394,   395,   399,   400,   401,   405,   406,   407,   408,   409,
     410,   411,   412,   413,   414,   415,   419,   420,   421,   425,
     426,   427,   428,   432,   436,   437,   441,   442,   446,   447,
     448,   449,   450,   451,   452,   456,   460,   461,   462,   466,
     467,   471,   472,   476,   477,   481,   482,   486,   487,   488,
     492,   493,   494,   495,   496,   497,   501,   502,   503,   504,
     505,   509,   510,   514,   515,   519,   520,   524,   525
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "AUTO", "SIZEOF", "GOTO", "RETURN",
  "println", "DO", "WHILE", "FOR", "CONTINUE", "BREAK", "SWITCH",
  "DEFAULT", "CASE", "IF", "ELSE", "FLOAT", "DOUBLE", "CHAR", "VOID",
  "INT", "LONG", "BOOL", "SHORT", "VOLATILE", "CONST", "SIGNED",
  "UNSIGNED", "STATIC", "EXTERN", "INLINE", "TYPEDEF", "STRUCT", "ENUM",
  "UNION", "CONSTANT", "CONSTANT_INT", "CONSTANT_DOUBLE", "ELLIPSIS",
  "STRING_LITERAL", "ASSIGN_RIGHTSHIFT", "ASSIGN_LEFTSHIFT", "ASSIGN_ADD",
  "ASSIGN_SUB", "ASSIGN_MUL", "ASSIGN_DIV", "ASSIGN_MOD", "ASSIGN_AND",
  "ASSIGN_OR", "TYPE_NAME", "ASSIGN_XOR", "IDENTIFIER", "OP_RIGHTSHIFT",
  "OP_LEFTSHIFT", "OP_INC", "OP_DEC", "OP_PTR", "OP_AND", "OP_OR", "OP_LE",
  "OP_GE", "OP_EQ", "OP_NE", "';'", "','", "':'", "'.'", "'&'", "'|'",
  "'~'", "'^'", "'+'", "'-'", "'*'", "'/'", "'%'", "'>'", "'<'", "'?'",
  "'!'", "'='", "'('", "')'", "'['", "']'", "'{'", "'}'", "$accept",
  "program", "primary_expression", "postfix_expression",
  "argument_expression_list", "unary_expression", "unary_operator",
  "cast_expression", "multiplicative_expression", "additive_expression",
  "shift_expression", "relational_expression", "equality_expression",
  "and_expression", "exclusive_or_expression", "inclusive_or_expression",
  "logical_and_expression", "logical_or_expression",
  "conditional_expression", "assignment_expression", "assignment_operator",
  "expression", "constant_expression", "declaration",
  "declaration_specifiers", "init_declarator_list", "init_declarator",
  "storage_class_specifier", "type_specifier", "struct_or_union_specifier",
  "struct_or_union", "struct_declaration_list", "struct_declaration",
  "specifier_qualifier_list", "struct_declarator_list",
  "struct_declarator", "enum_specifier", "enumerator_list", "enumerator",
  "type_qualifier", "function_specifier", "declarator",
  "direct_declarator", "pointer", "type_qualifier_list",
  "parameter_type_list", "parameter_list", "parameter_declaration",
  "identifier_list", "type_name", "abstract_declarator",
  "direct_abstract_declarator", "initializer", "initializer_list",
  "designation", "designator_list", "designator", "statement",
  "print_statement", "labeled_statement", "compound_statement",
  "block_item_list", "block_item", "expression_statement",
  "selection_statement", "iteration_statement", "jump_statement",
  "translation_unit", "external_declaration", "function_definition",
  "declaration_list", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,    59,    44,    58,    46,    38,
     124,   126,    94,    43,    45,    42,    47,    37,    62,    60,
      63,    33,    61,    40,    41,    91,    93,   123,   125
};
# endif

#define YYPACT_NINF -275

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-275)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1595,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,   -27,
    -275,    23,  -275,     1,  1595,  1595,  -275,   -15,  -275,  1595,
    1595,  1595,  -275,  -275,   -17,    25,  -275,  -275,  -275,    26,
      50,   125,  -275,   490,    67,    -4,  -275,  -275,     7,  1614,
    -275,  -275,  -275,    25,    27,    20,  -275,  -275,  -275,    26,
      18,  -275,    50,   711,   331,  -275,     1,  -275,   524,  1057,
     876,    67,  1614,  1614,   292,  -275,    37,  1614,    55,  1396,
     -33,  -275,  -275,  -275,  -275,  -275,    41,  1435,  -275,  -275,
    -275,  -275,    64,  1458,  1458,  -275,  -275,  -275,  -275,  -275,
    -275,  1296,   672,  -275,   190,   183,  1396,  -275,   186,   215,
     242,   175,   236,   107,   114,   113,   140,    31,  -275,  -275,
    -275,   166,  1346,   124,   649,   211,   221,   131,   184,   226,
     174,  1396,   265,    -6,  -275,  -275,  -275,   237,  -275,  -275,
    -275,  -275,  -275,   417,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,    -2,   171,   193,  -275,    62,   281,   285,
    -275,   289,   926,  1524,  -275,  -275,  -275,  1396,   258,  -275,
     314,  -275,   -32,  -275,  -275,  -275,  -275,  -275,  -275,  1296,
    -275,  1166,  1296,  -275,  -275,   111,   202,   185,   329,  1396,
    -275,    56,   711,   208,  -275,  -275,  -275,   330,   332,  1396,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  1396,  -275,  1396,  1396,  1396,  1396,  1396,  1396,  1396,
    1396,  1396,  1396,  1396,  1396,  1396,  1396,  1396,  1396,  1396,
    1396,  1396,   321,  -275,   266,   348,   381,  1396,  1127,  -275,
    -275,  1396,   649,   324,  1396,   649,  -275,  1396,  -275,  -275,
     807,   965,  -275,    -3,  -275,   127,  -275,  1551,   339,  -275,
    1335,  -275,  -275,  1396,   307,  -275,   308,  -275,  -275,  -275,
      37,  1396,  -275,   311,  -275,   121,  -275,   313,  -275,   843,
     199,  -275,   734,  -275,   312,   525,  -275,  -275,  -275,  -275,
    -275,  -275,     9,  -275,  -275,  -275,  -275,   186,   186,   215,
     215,   242,   242,   242,   242,   175,   175,   236,   107,   114,
     113,   140,   334,  -275,  -275,   333,   325,   122,  1385,  1385,
     109,  -275,   649,   116,  -275,  -275,  -275,   323,   326,   327,
    -275,   371,   127,  1093,   988,  -275,  -275,  -275,   373,   374,
    -275,  -275,  -275,  -275,   322,  1396,  -275,   322,   672,  -275,
    -275,  -275,  -275,   711,  -275,  1396,  1396,  1396,   649,  1189,
    1228,   649,  -275,   649,  -275,  -275,  -275,  -275,  -275,   350,
     375,  -275,   376,  -275,  -275,  -275,    60,  -275,  -275,   137,
     168,  -275,   649,   172,   649,   176,  -275,   394,  -275,  -275,
    -275,   564,  -275,   351,   352,  -275,   649,  -275,   649,   649,
    -275,  -275,  -275,  -275,  -275,  -275
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    98,   104,   105,   100,    99,   102,   103,   108,   101,
     138,   137,   106,   107,    97,    96,   139,    95,   114,     0,
     115,     0,   234,     0,    83,    85,   109,     0,   110,    87,
      89,     2,   231,   233,   132,     0,     1,   142,    81,   155,
       0,     0,    91,    93,   141,     0,    84,    86,   113,     0,
      88,    90,   232,     0,   135,     0,   133,   159,   157,   156,
       0,    82,     0,     0,     0,   237,     0,   236,     0,     0,
       0,   140,     0,   120,     0,   116,     0,   122,     0,     0,
       0,   128,   160,   158,   143,    92,    93,     0,     4,     5,
       6,     7,     3,     0,     0,    27,    31,    29,    30,    28,
      32,     0,     0,     9,    21,    33,     0,    35,    39,    42,
      45,    50,    53,    55,    57,    59,    61,    63,    65,   186,
      94,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     3,   215,   209,    78,     0,   213,   214,
     204,   198,   199,     0,   211,   200,   201,   202,   203,   238,
     235,   168,   154,   167,     0,   161,   163,     0,     0,    28,
     151,     0,     0,     0,   119,   112,   117,     0,     0,   123,
     125,   121,     0,   129,    33,    80,   136,   130,   134,     0,
      25,     0,     0,    22,    23,     0,   170,     0,     0,     0,
     189,     0,     0,     0,   194,    15,    16,     0,     0,     0,
      74,    73,    71,    72,    68,    69,    70,    75,    77,    76,
      67,     0,    24,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   229,     0,     0,     0,     0,     0,   227,
     228,     0,     0,     0,     0,     0,   216,     0,   210,   212,
       0,     0,   165,   172,   166,   173,   152,     0,     0,   153,
       0,   150,   146,     0,    28,   145,     0,   111,   126,   118,
       0,     0,   131,     0,    11,     0,    19,     0,     8,     0,
     172,   171,     0,   197,     0,     0,   187,   190,   193,   195,
      14,    13,     0,    66,    36,    37,    38,    40,    41,    44,
      43,    48,    49,    47,    46,    51,    52,    54,    56,    58,
      60,    62,     0,   226,   230,     0,     0,     0,     0,     0,
       0,   208,     0,     0,   206,    79,   182,     0,     0,    28,
     176,     0,   174,     0,     0,   162,   164,   169,     0,     0,
     149,   144,   124,   127,    26,     0,    12,     0,     0,    34,
     196,   188,   191,     0,    10,     0,     0,     0,     0,     0,
       0,     0,   207,     0,   183,   175,   180,   177,   184,     0,
      28,   178,     0,   147,   148,    20,     0,   192,    64,     0,
       0,   220,     0,     0,     0,     0,   219,   217,   185,   181,
     179,     0,    17,     0,     0,   224,     0,   222,     0,     0,
      18,   205,   221,   225,   223,   218
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -275,  -275,  -275,  -275,  -275,   -60,  -275,   -74,   157,   158,
     -85,   154,  -182,   188,   235,   238,   234,  -275,   -57,   -62,
    -275,   -86,  -126,   -29,     0,  -275,   403,  -275,    15,  -275,
    -275,   396,   -58,   -64,  -275,   196,  -275,   416,   -73,   143,
    -275,   -19,   -35,   -11,   -52,   -66,  -275,   214,  -275,  -114,
    -141,  -195,   -61,   128,  -274,  -275,   279,  -118,  -275,  -275,
      -1,  -275,   335,  -221,  -275,  -275,  -275,  -275,   444,  -275,
    -275
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    21,   103,   104,   275,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   136,
     211,   137,   176,    22,    66,    41,    42,    24,    25,    26,
      27,    74,    75,    76,   168,   169,    28,    55,    56,    29,
      30,    60,    44,    45,    59,   327,   155,   156,   157,   187,
     328,   255,   190,   191,   192,   193,   194,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,    31,    32,    33,
      68
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
      23,   119,   120,   154,    43,   243,   236,   178,   161,   164,
      71,   353,   254,   171,    65,   185,   166,   319,   162,   174,
      54,    54,   175,    36,    46,    47,    34,   180,    58,    50,
      51,    23,   212,   183,   184,   138,   234,   186,    48,   149,
     119,   268,    67,    86,   307,   281,   174,    86,    83,    37,
      37,    37,    10,    11,    37,   177,   272,   170,   332,   320,
      35,   245,   323,   284,    73,   273,    38,   150,   277,   153,
      53,   174,    49,    39,   175,   247,    39,   181,    54,    40,
     250,   250,   251,   251,    40,   332,    80,    73,    73,    73,
      37,   230,    73,   185,    72,   354,   185,   359,   360,   178,
     266,    39,    84,    37,   167,   166,   260,   174,    81,    79,
     175,   231,    39,   292,   138,   186,    73,   353,   186,   276,
      40,   172,   285,    63,   321,    39,   391,   324,   258,   174,
     119,   287,   175,    40,   252,   301,   302,   303,   304,   294,
     295,   296,   253,   173,   286,   343,   259,   181,   392,   293,
      69,   317,    70,   174,   174,   174,   174,   174,   174,   174,
     174,   174,   174,   174,   174,   174,   174,   174,   174,   174,
     174,   174,   224,   225,   312,   280,   226,   247,    73,   224,
     225,   174,    57,   228,   174,   325,   227,   345,   247,   331,
      61,    62,    77,   361,    73,   278,   239,    73,   338,   229,
     363,   339,    82,   247,   362,   346,   358,   235,   349,   318,
     333,   174,   334,    57,   175,    77,    77,    77,    71,   232,
      77,   393,   174,   119,   352,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   247,   209,   220,   221,   247,   253,
     381,   242,   247,   386,    77,   387,   195,   196,   197,   240,
     153,   170,   394,   222,   223,   256,   396,   153,   198,   257,
     398,   213,   214,   215,   395,   210,   397,   369,   280,   282,
     379,   380,   372,   383,   385,   199,   188,    39,   403,   153,
     404,   405,   279,   375,   251,   279,   119,   251,   216,   217,
     288,   119,   377,   189,   237,   174,   218,   219,   378,   224,
     225,    57,   246,   247,   238,    82,    77,    10,    11,   241,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    77,   269,   270,    77,    18,    19,    20,   119,
     352,   314,   247,   153,     1,    87,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   244,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    88,    89,
      90,   261,    91,   297,   298,   262,   299,   300,   305,   306,
     165,   271,   283,   290,   133,   291,   313,    93,    94,   315,
     316,   322,   337,   340,   341,   344,   134,   347,   350,   356,
      95,   355,    96,    82,    97,    98,    99,   364,   357,   348,
     365,   399,   100,   366,   101,   308,   401,   402,    64,   135,
       1,    87,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   388,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    88,    89,    90,   367,    91,   373,
     374,   389,   390,   309,   311,    85,   342,   310,   163,    78,
     133,   336,   289,    93,    94,    52,   376,     0,   249,     0,
       0,     0,   134,     0,     0,     0,    95,     0,    96,     0,
      97,    98,    99,     1,     0,     0,     0,     0,   100,     0,
     101,     0,     0,     0,    64,   248,     0,     0,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,     1,     0,    87,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,     0,    88,    89,    90,     0,    91,     0,    87,     0,
       0,     0,    63,     0,     0,     0,     0,    64,    92,     0,
       0,    93,    94,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   188,    95,     0,    96,     0,    97,    98,
      99,    88,    89,    90,     0,    91,   100,     0,   101,     0,
     189,    64,   102,   351,     0,     0,     0,    92,     0,     0,
      93,    94,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   188,    95,     0,    96,     0,    97,    98,    99,
       0,     0,     0,     0,     0,   100,     0,   101,     0,   189,
       0,   102,   400,    87,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    87,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    88,    89,    90,     0,
      91,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   133,     0,     0,    93,    94,     0,     0,    88,
      89,    90,     0,    91,   134,    87,     0,     0,    95,     0,
      96,     0,    97,    98,    99,    92,     0,     0,    93,    94,
     100,     0,   101,     0,     0,     0,    64,     0,    87,     0,
     188,    95,     0,    96,     0,    97,    98,    99,    88,    89,
      90,     0,    91,   100,     0,   101,     0,   189,     0,   102,
       0,     0,     0,     0,    92,     0,     0,    93,    94,     0,
       0,    88,    89,    90,     0,    91,     0,     0,     0,     0,
      95,     0,    96,     0,    97,    98,    99,    92,     0,     0,
      93,    94,   100,     0,   101,     0,     0,     0,   102,     0,
       0,     0,     0,    95,     0,    96,     0,    97,    98,    99,
       1,     0,     0,     0,     0,   100,     0,   101,     0,     0,
       0,   348,     0,     0,     0,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,     0,     0,     1,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      37,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      87,     0,    39,     0,     0,     0,     0,     0,     0,     0,
     250,   326,   251,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    10,    11,     0,     0,   158,     0,     0,     0,
       0,     0,     0,    88,    89,    90,     0,    91,    39,     0,
       0,     0,     0,     0,     0,     0,   279,   326,   251,    92,
      87,     0,    93,    94,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    95,     0,    96,     0,    97,
      98,   159,    10,    11,     0,     0,   263,   100,     0,   101,
       0,     0,   160,    88,    89,    90,     0,    91,     0,    87,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    92,
       0,     0,    93,    94,     0,     0,     0,     0,     0,     0,
       0,     0,    87,     0,     0,    95,     0,    96,     0,    97,
      98,   264,    88,    89,    90,     0,    91,   100,     0,   101,
       0,     0,   265,     0,     0,     0,     0,     0,    92,     0,
       0,    93,    94,     0,     0,    88,    89,    90,     0,    91,
       0,     0,     0,     0,    95,     0,    96,     0,    97,    98,
     329,    92,     0,     0,    93,    94,   100,     0,   101,     0,
       0,   330,     0,     0,     0,     0,     0,    95,     0,    96,
       1,    97,    98,   370,     0,     0,     0,     0,     0,   100,
       0,   101,     0,     0,   371,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,     0,     0,     1,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     151,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
       1,    87,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   152,     0,     0,     0,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    88,    89,    90,     0,    91,     0,
      87,     0,     0,     0,     0,     0,     0,   368,     0,     0,
      92,     0,     0,    93,    94,     0,     0,     0,     0,     0,
       0,     0,   134,    87,     0,     0,    95,     0,    96,     0,
      97,    98,    99,    88,    89,    90,     0,    91,   100,     0,
     101,     0,     0,     0,     0,     0,     0,     0,     0,    92,
       0,     0,    93,    94,     0,     0,    88,    89,    90,     0,
      91,     0,    87,     0,     0,    95,     0,    96,     0,    97,
      98,    99,    92,     0,     0,    93,    94,   100,     0,   101,
     274,     0,     0,     0,     0,     0,     0,     0,    95,     0,
      96,     0,    97,    98,    99,    88,    89,    90,     0,    91,
     100,     0,   101,   382,     0,     0,     0,     0,     0,     0,
       0,    92,     0,     0,    93,    94,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    95,     0,    96,
      87,    97,    98,    99,     0,     0,     0,     0,     0,   100,
       0,   101,   384,     0,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,     0,     0,     0,     0,
      18,    19,    20,    88,    89,    90,     0,    91,     0,    87,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    92,
      87,     0,    93,    94,     0,     0,     0,     0,     0,     0,
       0,    10,    11,     0,     0,    95,     0,    96,     0,    97,
      98,    99,    88,    89,    90,     0,    91,   100,     0,   101,
       0,     0,     0,    88,    89,    90,     0,    91,    92,    87,
       0,    93,    94,     0,     0,     0,     0,     0,     0,    92,
      87,     0,    93,    94,    95,     0,    96,     0,    97,    98,
      99,   233,     0,     0,     0,    95,   100,    96,   101,    97,
      98,    99,    88,    89,    90,     0,    91,   100,     0,   101,
       0,     0,     0,    88,    89,    90,     0,    91,    92,    87,
       0,    93,    94,     0,     0,     0,     0,     0,     0,    92,
     134,     0,    93,    94,    95,     0,    96,     0,    97,    98,
      99,     0,    87,     0,     0,    95,   100,    96,   101,    97,
      98,    99,    88,    89,    90,     0,    91,   100,     0,   101,
       0,     0,     0,     0,     0,     0,     0,     0,    92,     0,
       0,    93,    94,     0,     0,    88,    89,    90,     0,    91,
       0,     0,     0,     0,    95,     0,    96,     0,    97,    98,
      99,    92,     0,     0,    93,    94,   100,     0,   179,     0,
       0,     0,     0,     0,     0,     0,     0,    95,     0,    96,
       0,    97,    98,    99,     0,     0,     0,     0,     0,   100,
       0,   182,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,     1,     0,     0,     0,    18,    19,
      20,     0,     0,     0,     0,     0,     0,     0,     0,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,     0,     0,
       0,   335,     0,     0,     0,     0,     0,     0,     1,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   267,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,     0,     0,     0,     0,    18,    19,
      20
};

static const yytype_int16 yycheck[] =
{
       0,    63,    63,    69,    23,   131,   124,    80,    70,    73,
      45,   285,   153,    77,    43,   101,    74,   238,    70,    79,
      53,    53,    79,     0,    24,    25,    53,    87,    39,    29,
      30,    31,   106,    93,    94,    64,   122,   101,    53,    68,
     102,   167,    43,    62,   226,   186,   106,    66,    59,    53,
      53,    53,    26,    27,    53,    88,    88,    76,   253,   241,
      87,    67,   244,   189,    49,   179,    65,    68,   182,    69,
      87,   131,    87,    75,   131,    66,    75,    83,    53,    83,
      83,    83,    85,    85,    83,   280,    66,    72,    73,    74,
      53,    60,    77,   179,    87,    86,   182,   318,   319,   172,
     162,    75,    84,    53,    67,   163,   158,   167,    88,    82,
     167,    80,    75,   199,   143,   179,   101,   391,   182,   181,
      83,    66,    66,    82,   242,    75,    66,   245,    66,   189,
     192,   192,   189,    83,   153,   220,   221,   222,   223,   213,
     214,   215,   153,    88,    88,   271,    84,    83,    88,   211,
      83,   237,    85,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,    63,    64,   231,   186,    69,    66,   163,    63,
      64,   241,    39,    70,   244,   247,    72,    66,    66,   251,
      65,    66,    49,    84,   179,    84,    65,   182,   260,    59,
      84,   263,    59,    66,   322,    84,    84,    83,   282,   238,
      83,   271,    85,    70,   271,    72,    73,    74,   253,    53,
      77,    84,   282,   285,   285,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    66,    52,    61,    62,    66,   250,
     358,    67,    66,   361,   101,   363,    56,    57,    58,    65,
     250,   270,    84,    78,    79,    84,    84,   257,    68,    66,
      84,    75,    76,    77,   382,    82,   384,   333,   279,    84,
     356,   357,   334,   359,   360,    85,    68,    75,   396,   279,
     398,   399,    83,   345,    85,    83,   348,    85,    73,    74,
      82,   353,   353,    85,    83,   355,    54,    55,   355,    63,
      64,   158,    65,    66,    83,   162,   163,    26,    27,    83,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,   179,    65,    66,   182,    34,    35,    36,   391,
     391,    65,    66,   333,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    83,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    86,    41,   216,   217,    86,   218,   219,   224,   225,
      88,    67,    53,    53,    53,    53,    65,    56,    57,    41,
       9,    67,    53,    86,    86,    84,    65,    84,    86,    66,
      69,    67,    71,   260,    73,    74,    75,    84,    83,    87,
      84,    17,    81,    86,    83,   227,    65,    65,    87,    88,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    84,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    86,    41,    86,
      86,    86,    86,   228,   230,    62,   270,   229,    72,    53,
      53,   257,   193,    56,    57,    31,   348,    -1,   143,    -1,
      -1,    -1,    65,    -1,    -1,    -1,    69,    -1,    71,    -1,
      73,    74,    75,     3,    -1,    -1,    -1,    -1,    81,    -1,
      83,    -1,    -1,    -1,    87,    88,    -1,    -1,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,     3,    -1,     4,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    -1,    37,    38,    39,    -1,    41,    -1,     4,    -1,
      -1,    -1,    82,    -1,    -1,    -1,    -1,    87,    53,    -1,
      -1,    56,    57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    68,    69,    -1,    71,    -1,    73,    74,
      75,    37,    38,    39,    -1,    41,    81,    -1,    83,    -1,
      85,    87,    87,    88,    -1,    -1,    -1,    53,    -1,    -1,
      56,    57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    68,    69,    -1,    71,    -1,    73,    74,    75,
      -1,    -1,    -1,    -1,    -1,    81,    -1,    83,    -1,    85,
      -1,    87,    88,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     4,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    37,    38,    39,    -1,
      41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    53,    -1,    -1,    56,    57,    -1,    -1,    37,
      38,    39,    -1,    41,    65,     4,    -1,    -1,    69,    -1,
      71,    -1,    73,    74,    75,    53,    -1,    -1,    56,    57,
      81,    -1,    83,    -1,    -1,    -1,    87,    -1,     4,    -1,
      68,    69,    -1,    71,    -1,    73,    74,    75,    37,    38,
      39,    -1,    41,    81,    -1,    83,    -1,    85,    -1,    87,
      -1,    -1,    -1,    -1,    53,    -1,    -1,    56,    57,    -1,
      -1,    37,    38,    39,    -1,    41,    -1,    -1,    -1,    -1,
      69,    -1,    71,    -1,    73,    74,    75,    53,    -1,    -1,
      56,    57,    81,    -1,    83,    -1,    -1,    -1,    87,    -1,
      -1,    -1,    -1,    69,    -1,    71,    -1,    73,    74,    75,
       3,    -1,    -1,    -1,    -1,    81,    -1,    83,    -1,    -1,
      -1,    87,    -1,    -1,    -1,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,     3,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      53,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
       4,    -1,    75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      83,    84,    85,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    26,    27,    -1,    -1,    30,    -1,    -1,    -1,
      -1,    -1,    -1,    37,    38,    39,    -1,    41,    75,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    83,    84,    85,    53,
       4,    -1,    56,    57,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    69,    -1,    71,    -1,    73,
      74,    75,    26,    27,    -1,    -1,    30,    81,    -1,    83,
      -1,    -1,    86,    37,    38,    39,    -1,    41,    -1,     4,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,
      -1,    -1,    56,    57,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     4,    -1,    -1,    69,    -1,    71,    -1,    73,
      74,    75,    37,    38,    39,    -1,    41,    81,    -1,    83,
      -1,    -1,    86,    -1,    -1,    -1,    -1,    -1,    53,    -1,
      -1,    56,    57,    -1,    -1,    37,    38,    39,    -1,    41,
      -1,    -1,    -1,    -1,    69,    -1,    71,    -1,    73,    74,
      75,    53,    -1,    -1,    56,    57,    81,    -1,    83,    -1,
      -1,    86,    -1,    -1,    -1,    -1,    -1,    69,    -1,    71,
       3,    73,    74,    75,    -1,    -1,    -1,    -1,    -1,    81,
      -1,    83,    -1,    -1,    86,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,     3,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      53,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
       3,     4,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    84,    -1,    -1,    -1,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    -1,    41,    -1,
       4,    -1,    -1,    -1,    -1,    -1,    -1,    84,    -1,    -1,
      53,    -1,    -1,    56,    57,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    65,     4,    -1,    -1,    69,    -1,    71,    -1,
      73,    74,    75,    37,    38,    39,    -1,    41,    81,    -1,
      83,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,
      -1,    -1,    56,    57,    -1,    -1,    37,    38,    39,    -1,
      41,    -1,     4,    -1,    -1,    69,    -1,    71,    -1,    73,
      74,    75,    53,    -1,    -1,    56,    57,    81,    -1,    83,
      84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,    -1,
      71,    -1,    73,    74,    75,    37,    38,    39,    -1,    41,
      81,    -1,    83,    84,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    53,    -1,    -1,    56,    57,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,    -1,    71,
       4,    73,    74,    75,    -1,    -1,    -1,    -1,    -1,    81,
      -1,    83,    84,    -1,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    -1,    -1,    -1,    -1,
      34,    35,    36,    37,    38,    39,    -1,    41,    -1,     4,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,
       4,    -1,    56,    57,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    26,    27,    -1,    -1,    69,    -1,    71,    -1,    73,
      74,    75,    37,    38,    39,    -1,    41,    81,    -1,    83,
      -1,    -1,    -1,    37,    38,    39,    -1,    41,    53,     4,
      -1,    56,    57,    -1,    -1,    -1,    -1,    -1,    -1,    53,
       4,    -1,    56,    57,    69,    -1,    71,    -1,    73,    74,
      75,    65,    -1,    -1,    -1,    69,    81,    71,    83,    73,
      74,    75,    37,    38,    39,    -1,    41,    81,    -1,    83,
      -1,    -1,    -1,    37,    38,    39,    -1,    41,    53,     4,
      -1,    56,    57,    -1,    -1,    -1,    -1,    -1,    -1,    53,
      65,    -1,    56,    57,    69,    -1,    71,    -1,    73,    74,
      75,    -1,     4,    -1,    -1,    69,    81,    71,    83,    73,
      74,    75,    37,    38,    39,    -1,    41,    81,    -1,    83,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,
      -1,    56,    57,    -1,    -1,    37,    38,    39,    -1,    41,
      -1,    -1,    -1,    -1,    69,    -1,    71,    -1,    73,    74,
      75,    53,    -1,    -1,    56,    57,    81,    -1,    83,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,    -1,    71,
      -1,    73,    74,    75,    -1,    -1,    -1,    -1,    -1,    81,
      -1,    83,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,     3,    -1,    -1,    -1,    34,    35,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      -1,    40,    -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    88,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    -1,    -1,    -1,    -1,    34,    35,
      36
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    90,   112,   113,   116,   117,   118,   119,   125,   128,
     129,   156,   157,   158,    53,    87,     0,    53,    65,    75,
      83,   114,   115,   130,   131,   132,   113,   113,    53,    87,
     113,   113,   157,    87,    53,   126,   127,   128,   132,   133,
     130,    65,    66,    82,    87,   112,   113,   149,   159,    83,
      85,   131,    87,   117,   120,   121,   122,   128,   126,    82,
      66,    88,   128,   132,    84,   115,   130,     4,    37,    38,
      39,    41,    53,    56,    57,    69,    71,    73,    74,    75,
      81,    83,    87,    91,    92,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     141,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    53,    65,    88,   108,   110,   112,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   112,
     149,    53,    84,   113,   134,   135,   136,   137,    30,    75,
      86,   108,   133,   120,   122,    88,   121,    67,   123,   124,
     130,   122,    66,    88,    94,   107,   111,    88,   127,    83,
      94,    83,    83,    94,    94,   110,   122,   138,    68,    85,
     141,   142,   143,   144,   145,    56,    57,    58,    68,    85,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    52,
      82,   109,    96,    75,    76,    77,    73,    74,    54,    55,
      61,    62,    78,    79,    63,    64,    69,    72,    70,    59,
      60,    80,    53,    65,   110,    83,   146,    83,    83,    65,
      65,    83,    67,   111,    83,    67,    65,    66,    88,   151,
      83,    85,   130,   132,   139,   140,    84,    66,    66,    84,
     133,    86,    86,    30,    75,    86,   108,    88,   111,    65,
      66,    67,    88,   138,    84,    93,   108,   138,    84,    83,
     132,   139,    84,    53,   111,    66,    88,   141,    82,   145,
      53,    53,   110,   108,    96,    96,    96,    97,    97,    98,
      98,    99,    99,    99,    99,   100,   100,   101,   102,   103,
     104,   105,   107,    65,    65,    41,     9,   110,   112,   152,
     101,   146,    67,   101,   146,   108,    84,   134,   139,    75,
      86,   108,   140,    83,    85,    40,   136,    53,   108,   108,
      86,    86,   124,   111,    84,    66,    84,    84,    87,    96,
      86,    88,   141,   143,    86,    67,    66,    83,    84,   152,
     152,    84,   146,    84,    84,    84,    86,    86,    84,   134,
      75,    86,   108,    86,    86,   108,   142,   141,   107,   110,
     110,   146,    84,   110,    84,   110,   146,   146,    84,    86,
      86,    66,    88,    84,    84,   146,    84,   146,    84,    17,
      88,    65,    65,   146,   146,   146
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    89,    90,    91,    91,    91,    91,    91,    91,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    93,
      93,    94,    94,    94,    94,    94,    94,    95,    95,    95,
      95,    95,    95,    96,    96,    97,    97,    97,    97,    98,
      98,    98,    99,    99,    99,   100,   100,   100,   100,   100,
     101,   101,   101,   102,   102,   103,   103,   104,   104,   105,
     105,   106,   106,   107,   107,   108,   108,   109,   109,   109,
     109,   109,   109,   109,   109,   109,   109,   109,   110,   110,
     111,   112,   112,   113,   113,   113,   113,   113,   113,   113,
     113,   114,   114,   115,   115,   116,   116,   116,   116,   117,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   118,   118,   118,   119,   119,   120,   120,   121,   122,
     122,   122,   122,   123,   123,   124,   124,   124,   125,   125,
     125,   125,   125,   126,   126,   127,   127,   128,   128,   129,
     130,   130,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   132,   132,   132,   132,   133,
     133,   134,   134,   135,   135,   136,   136,   136,   137,   137,
     138,   138,   139,   139,   139,   140,   140,   140,   140,   140,
     140,   140,   140,   140,   140,   140,   141,   141,   141,   142,
     142,   142,   142,   143,   144,   144,   145,   145,   146,   146,
     146,   146,   146,   146,   146,   147,   148,   148,   148,   149,
     149,   150,   150,   151,   151,   152,   152,   153,   153,   153,
     154,   154,   154,   154,   154,   154,   155,   155,   155,   155,
     155,   156,   156,   157,   157,   158,   158,   159,   159
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     3,     1,
       4,     3,     4,     3,     3,     2,     2,     6,     7,     1,
       3,     1,     2,     2,     2,     2,     4,     1,     1,     1,
       1,     1,     1,     1,     4,     1,     3,     3,     3,     1,
       3,     3,     1,     3,     3,     1,     3,     3,     3,     3,
       1,     3,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     5,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     2,     3,     1,     2,     1,     2,     1,     2,     1,
       2,     1,     3,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     5,     4,     2,     1,     1,     1,     2,     3,     2,
       1,     2,     1,     1,     3,     1,     2,     3,     4,     5,
       5,     6,     2,     1,     3,     1,     3,     1,     1,     1,
       2,     1,     1,     3,     5,     4,     4,     6,     6,     5,
       4,     3,     4,     4,     3,     1,     2,     2,     3,     1,
       2,     1,     3,     1,     3,     2,     2,     1,     1,     3,
       1,     2,     1,     1,     2,     3,     2,     3,     3,     4,
       3,     4,     2,     3,     3,     4,     1,     3,     4,     1,
       2,     3,     4,     2,     1,     2,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     7,     3,     4,     3,     2,
       3,     1,     2,     1,     1,     1,     2,     5,     7,     5,
       5,     7,     6,     7,     6,     7,     3,     2,     2,     2,
       3,     1,     2,     1,     1,     4,     3,     1,     2
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 76 "parser.y" /* yacc.c:1646  */
    { (yyval.gtn) = treeCreate("program",1,(yyvsp[0].gtn));root = (yyval.gtn);}
#line 1927 "parser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 80 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("primary_expression",1,(yyvsp[0].gtn));}
#line 1933 "parser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 81 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("primary_expression",1,(yyvsp[0].gtn));}
#line 1939 "parser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 82 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("primary_expression",1,(yyvsp[0].gtn));}
#line 1945 "parser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 83 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("primary_expression",1,(yyvsp[0].gtn));}
#line 1951 "parser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 84 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("primary_expression",1,(yyvsp[0].gtn));}
#line 1957 "parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 85 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("primary_expression",3,(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 1963 "parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 89 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("postfix_expression",1,(yyvsp[0].gtn));}
#line 1969 "parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 90 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("postfix_expression",4,(yyvsp[-3].gtn),(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 1975 "parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 91 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("postfix_expression",3,(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 1981 "parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 92 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("postfix_expression",4,(yyvsp[-3].gtn),(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 1987 "parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 93 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("postfix_expression",3,(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 1993 "parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 94 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("postfix_expression",3,(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 1999 "parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 95 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("postfix_expression",2,(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2005 "parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 96 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("postfix_expression",2,(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2011 "parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 97 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("postfix_expression",6,(yyvsp[-5].gtn),(yyvsp[-4].gtn),(yyvsp[-3].gtn),(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2017 "parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 98 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("postfix_expression",7,(yyvsp[-6].gtn),(yyvsp[-5].gtn),(yyvsp[-4].gtn),(yyvsp[-3].gtn),(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2023 "parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 102 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("argument_expression_list",1,(yyvsp[0].gtn));}
#line 2029 "parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 103 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("argument_expression_list",3,(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2035 "parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 107 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("unary_expression",1,(yyvsp[0].gtn));}
#line 2041 "parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 108 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("unary_expression",2,(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2047 "parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 109 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("unary_expression",2,(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2053 "parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 110 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("unary_expression",2,(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2059 "parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 111 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("unary_expression",2,(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2065 "parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 112 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("unary_expression",4,(yyvsp[-3].gtn),(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2071 "parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 116 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("unary_operator",1,(yyvsp[0].gtn));}
#line 2077 "parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 117 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("unary_operator",1,(yyvsp[0].gtn));}
#line 2083 "parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 118 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("unary_operator",1,(yyvsp[0].gtn));}
#line 2089 "parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 119 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("unary_operator",1,(yyvsp[0].gtn));}
#line 2095 "parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 120 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("unary_operator",1,(yyvsp[0].gtn));}
#line 2101 "parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 121 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("unary_operator",1,(yyvsp[0].gtn));}
#line 2107 "parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 125 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("cast_expression",1,(yyvsp[0].gtn));}
#line 2113 "parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 126 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("cast_expression",4,(yyvsp[-3].gtn),(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2119 "parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 130 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("multiplicative_expression",1,(yyvsp[0].gtn));}
#line 2125 "parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 131 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("multiplicative_expression",3,(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2131 "parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 132 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("multiplicative_expression",3,(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2137 "parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 133 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("multiplicative_expression",3,(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2143 "parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 137 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("additive_expression",1,(yyvsp[0].gtn));}
#line 2149 "parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 138 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("additive_expression",3,(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2155 "parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 139 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("additive_expression",3,(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2161 "parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 143 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("shift_expression",1,(yyvsp[0].gtn));}
#line 2167 "parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 144 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("shift_expression",3,(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2173 "parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 145 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("shift_expression",3,(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2179 "parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 149 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("relational_expression",1,(yyvsp[0].gtn));}
#line 2185 "parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 150 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("relational_expression",3,(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2191 "parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 151 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("relational_expression",3,(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2197 "parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 152 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("relational_expression",3,(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2203 "parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 153 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("relational_expression",3,(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2209 "parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 157 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("equality_expression",1,(yyvsp[0].gtn));}
#line 2215 "parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 158 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("equality_expression",3,(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2221 "parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 159 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("equality_expression",3,(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2227 "parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 163 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("and_expression",1,(yyvsp[0].gtn));}
#line 2233 "parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 164 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("and_expression",3,(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2239 "parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 168 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("exclusive_or_expression",1,(yyvsp[0].gtn));}
#line 2245 "parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 169 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("exclusive_or_expression",3,(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2251 "parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 173 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("inclusive_or_expression",1,(yyvsp[0].gtn));}
#line 2257 "parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 174 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("inclusive_or_expression",3,(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2263 "parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 178 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("logical_and_expression",1,(yyvsp[0].gtn));}
#line 2269 "parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 179 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("logical_and_expression",3,(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2275 "parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 183 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("logical_or_expression",1,(yyvsp[0].gtn));}
#line 2281 "parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 184 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("logical_or_expression",3,(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2287 "parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 188 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("conditional_expression",1,(yyvsp[0].gtn));}
#line 2293 "parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 189 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("conditional_expression",5,(yyvsp[-4].gtn),(yyvsp[-3].gtn),(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2299 "parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 193 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("assignment_expression",1,(yyvsp[0].gtn));}
#line 2305 "parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 194 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("assignment_expression",3,(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2311 "parser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 198 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("assignment_operator",1,(yyvsp[0].gtn));}
#line 2317 "parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 199 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("assignment_operator",1,(yyvsp[0].gtn));}
#line 2323 "parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 200 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("assignment_operator",1,(yyvsp[0].gtn));}
#line 2329 "parser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 201 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("assignment_operator",1,(yyvsp[0].gtn));}
#line 2335 "parser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 202 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("assignment_operator",1,(yyvsp[0].gtn));}
#line 2341 "parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 203 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("assignment_operator",1,(yyvsp[0].gtn));}
#line 2347 "parser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 204 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("assignment_operator",1,(yyvsp[0].gtn));}
#line 2353 "parser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 205 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("assignment_operator",1,(yyvsp[0].gtn));}
#line 2359 "parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 206 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("assignment_operator",1,(yyvsp[0].gtn));}
#line 2365 "parser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 207 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("assignment_operator",1,(yyvsp[0].gtn));}
#line 2371 "parser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 208 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("assignment_operator",1,(yyvsp[0].gtn));}
#line 2377 "parser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 212 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("expression",1,(yyvsp[0].gtn));}
#line 2383 "parser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 213 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("expression",3,(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2389 "parser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 217 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("constant_expression",1,(yyvsp[0].gtn));}
#line 2395 "parser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 221 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("declaration",2,(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2401 "parser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 222 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("declaration",3,(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2407 "parser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 226 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("declaration_specifiers",1,(yyvsp[0].gtn));}
#line 2413 "parser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 227 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("declaration_specifiers",2,(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2419 "parser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 228 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("declaration_specifiers",1,(yyvsp[0].gtn));}
#line 2425 "parser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 229 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("declaration_specifiers",2,(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2431 "parser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 230 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("declaration_specifiers",1,(yyvsp[0].gtn));}
#line 2437 "parser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 231 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("declaration_specifiers",2,(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2443 "parser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 232 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("declaration_specifiers",1,(yyvsp[0].gtn));}
#line 2449 "parser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 233 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("declaration_specifiers",2,(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2455 "parser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 237 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("init_declarator_list",1,(yyvsp[0].gtn));}
#line 2461 "parser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 238 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("init_declarator_list",3,(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2467 "parser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 242 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("init_declarator",1,(yyvsp[0].gtn));}
#line 2473 "parser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 243 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("init_declarator",3,(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2479 "parser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 247 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("storage_class_specifier",1,(yyvsp[0].gtn));}
#line 2485 "parser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 248 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("storage_class_specifier",1,(yyvsp[0].gtn));}
#line 2491 "parser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 249 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("storage_class_specifier",1,(yyvsp[0].gtn));}
#line 2497 "parser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 250 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("storage_class_specifier",1,(yyvsp[0].gtn));}
#line 2503 "parser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 255 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("type_specifier",1,(yyvsp[0].gtn));}
#line 2509 "parser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 256 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("type_specifier",1,(yyvsp[0].gtn));}
#line 2515 "parser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 257 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("type_specifier",1,(yyvsp[0].gtn));}
#line 2521 "parser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 258 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("type_specifier",1,(yyvsp[0].gtn));}
#line 2527 "parser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 259 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("type_specifier",1,(yyvsp[0].gtn));}
#line 2533 "parser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 260 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("type_specifier",1,(yyvsp[0].gtn));}
#line 2539 "parser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 261 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("type_specifier",1,(yyvsp[0].gtn));}
#line 2545 "parser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 262 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("type_specifier",1,(yyvsp[0].gtn));}
#line 2551 "parser.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 263 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("type_specifier",1,(yyvsp[0].gtn));}
#line 2557 "parser.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 264 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("type_specifier",1,(yyvsp[0].gtn));}
#line 2563 "parser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 267 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("type_specifier",1,(yyvsp[0].gtn));}
#line 2569 "parser.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 268 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("type_specifier",1,(yyvsp[0].gtn));}
#line 2575 "parser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 273 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("struct_or_union_specifier",5,(yyvsp[-4].gtn),(yyvsp[-3].gtn),(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2581 "parser.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 274 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("struct_or_union_specifier",4,(yyvsp[-3].gtn),(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2587 "parser.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 275 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("struct_or_union_specifier",2,(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2593 "parser.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 279 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("struct_or_union",1,(yyvsp[0].gtn));}
#line 2599 "parser.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 280 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("struct_or_union",1,(yyvsp[0].gtn));}
#line 2605 "parser.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 284 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("struct_declarator_list",1,(yyvsp[0].gtn));}
#line 2611 "parser.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 285 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("struct_declarator_list",2,(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2617 "parser.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 289 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("struct_declaration",3,(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2623 "parser.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 293 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("specifier_qualifier_list",2,(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2629 "parser.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 294 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("specifier_qualifier_list",1,(yyvsp[0].gtn));}
#line 2635 "parser.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 295 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("specifier_qualifier_list",2,(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2641 "parser.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 296 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("specifier_qualifier_list",1,(yyvsp[0].gtn));}
#line 2647 "parser.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 300 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("struct_declarator_list",1,(yyvsp[0].gtn));}
#line 2653 "parser.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 301 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("struct_declarator_list",3,(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2659 "parser.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 305 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("struct_declarator",1,(yyvsp[0].gtn));}
#line 2665 "parser.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 306 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("struct_declarator",2,(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2671 "parser.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 307 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("struct_declarator",3,(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2677 "parser.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 311 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("enum_specifier",4,(yyvsp[-3].gtn),(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2683 "parser.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 312 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("enum_specifier",5,(yyvsp[-4].gtn),(yyvsp[-3].gtn),(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2689 "parser.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 313 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("enum_specifier",5,(yyvsp[-4].gtn),(yyvsp[-3].gtn),(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2695 "parser.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 314 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("enum_specifier",6,(yyvsp[-5].gtn),(yyvsp[-4].gtn),(yyvsp[-3].gtn),(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2701 "parser.cpp" /* yacc.c:1646  */
    break;

  case 132:
#line 315 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("enum_specifier",2,(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2707 "parser.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 319 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("enumerator_list",1,(yyvsp[0].gtn));}
#line 2713 "parser.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 320 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("enumerator_list",3,(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2719 "parser.cpp" /* yacc.c:1646  */
    break;

  case 135:
#line 324 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("enumerator",1,(yyvsp[0].gtn));}
#line 2725 "parser.cpp" /* yacc.c:1646  */
    break;

  case 136:
#line 325 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("enumerator",3,(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2731 "parser.cpp" /* yacc.c:1646  */
    break;

  case 137:
#line 329 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("type_qualifier",1,(yyvsp[0].gtn));}
#line 2737 "parser.cpp" /* yacc.c:1646  */
    break;

  case 138:
#line 331 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("type_qualifier",1,(yyvsp[0].gtn));}
#line 2743 "parser.cpp" /* yacc.c:1646  */
    break;

  case 139:
#line 335 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("function_specifier",1,(yyvsp[0].gtn));}
#line 2749 "parser.cpp" /* yacc.c:1646  */
    break;

  case 140:
#line 339 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("declarator",2,(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2755 "parser.cpp" /* yacc.c:1646  */
    break;

  case 141:
#line 340 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("declarator",1,(yyvsp[0].gtn));}
#line 2761 "parser.cpp" /* yacc.c:1646  */
    break;

  case 142:
#line 344 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("direct_declarator",1,(yyvsp[0].gtn));}
#line 2767 "parser.cpp" /* yacc.c:1646  */
    break;

  case 143:
#line 345 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("direct_declarator",3,(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2773 "parser.cpp" /* yacc.c:1646  */
    break;

  case 144:
#line 346 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("direct_declarator",5,(yyvsp[-4].gtn),(yyvsp[-3].gtn),(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2779 "parser.cpp" /* yacc.c:1646  */
    break;

  case 145:
#line 347 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("direct_declarator",4,(yyvsp[-3].gtn),(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2785 "parser.cpp" /* yacc.c:1646  */
    break;

  case 146:
#line 348 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("direct_declarator",4,(yyvsp[-3].gtn),(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2791 "parser.cpp" /* yacc.c:1646  */
    break;

  case 147:
#line 349 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("direct_declarator",6,(yyvsp[-5].gtn),(yyvsp[-4].gtn),(yyvsp[-3].gtn),(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2797 "parser.cpp" /* yacc.c:1646  */
    break;

  case 148:
#line 350 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("direct_declarator",6,(yyvsp[-5].gtn),(yyvsp[-4].gtn),(yyvsp[-3].gtn),(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2803 "parser.cpp" /* yacc.c:1646  */
    break;

  case 149:
#line 351 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("direct_declarator",5,(yyvsp[-4].gtn),(yyvsp[-3].gtn),(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2809 "parser.cpp" /* yacc.c:1646  */
    break;

  case 150:
#line 352 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("direct_declarator",4,(yyvsp[-3].gtn),(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2815 "parser.cpp" /* yacc.c:1646  */
    break;

  case 151:
#line 353 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("direct_declarator",3,(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2821 "parser.cpp" /* yacc.c:1646  */
    break;

  case 152:
#line 354 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("direct_declarator",4,(yyvsp[-3].gtn),(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2827 "parser.cpp" /* yacc.c:1646  */
    break;

  case 153:
#line 355 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("direct_declarator",4,(yyvsp[-3].gtn),(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2833 "parser.cpp" /* yacc.c:1646  */
    break;

  case 154:
#line 356 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("direct_declarator",3,(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2839 "parser.cpp" /* yacc.c:1646  */
    break;

  case 155:
#line 360 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("pointer",1,(yyvsp[0].gtn));}
#line 2845 "parser.cpp" /* yacc.c:1646  */
    break;

  case 156:
#line 361 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("pointer",2,(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2851 "parser.cpp" /* yacc.c:1646  */
    break;

  case 157:
#line 362 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("pointer",2,(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2857 "parser.cpp" /* yacc.c:1646  */
    break;

  case 158:
#line 363 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("pointer",3,(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2863 "parser.cpp" /* yacc.c:1646  */
    break;

  case 159:
#line 367 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("type_qualifier_list",1,(yyvsp[0].gtn));}
#line 2869 "parser.cpp" /* yacc.c:1646  */
    break;

  case 160:
#line 368 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("type_qualifier_list",2,(yyvsp[0].gtn));}
#line 2875 "parser.cpp" /* yacc.c:1646  */
    break;

  case 161:
#line 373 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("parameter_type_list",1,(yyvsp[0].gtn));}
#line 2881 "parser.cpp" /* yacc.c:1646  */
    break;

  case 162:
#line 374 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("parameter_type_list",3,(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2887 "parser.cpp" /* yacc.c:1646  */
    break;

  case 163:
#line 378 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("parameter_list",1,(yyvsp[0].gtn));}
#line 2893 "parser.cpp" /* yacc.c:1646  */
    break;

  case 164:
#line 379 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("parameter_list",3,(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2899 "parser.cpp" /* yacc.c:1646  */
    break;

  case 165:
#line 383 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("parameter_declaration",2,(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2905 "parser.cpp" /* yacc.c:1646  */
    break;

  case 166:
#line 384 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("parameter_declaration",2,(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2911 "parser.cpp" /* yacc.c:1646  */
    break;

  case 167:
#line 385 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("parameter_declaration",1,(yyvsp[0].gtn));}
#line 2917 "parser.cpp" /* yacc.c:1646  */
    break;

  case 168:
#line 389 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("identifier_list",1,(yyvsp[0].gtn));}
#line 2923 "parser.cpp" /* yacc.c:1646  */
    break;

  case 169:
#line 390 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("identifier_list",3,(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2929 "parser.cpp" /* yacc.c:1646  */
    break;

  case 170:
#line 394 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("type_name",1,(yyvsp[0].gtn));}
#line 2935 "parser.cpp" /* yacc.c:1646  */
    break;

  case 171:
#line 395 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("type_name",2,(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2941 "parser.cpp" /* yacc.c:1646  */
    break;

  case 172:
#line 399 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("abstract_declarator",1,(yyvsp[0].gtn));}
#line 2947 "parser.cpp" /* yacc.c:1646  */
    break;

  case 173:
#line 400 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("abstract_declarator",1,(yyvsp[0].gtn));}
#line 2953 "parser.cpp" /* yacc.c:1646  */
    break;

  case 174:
#line 401 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("abstract_declarator",2,(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2959 "parser.cpp" /* yacc.c:1646  */
    break;

  case 186:
#line 419 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("initializer",1,(yyvsp[0].gtn));}
#line 2965 "parser.cpp" /* yacc.c:1646  */
    break;

  case 187:
#line 420 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("initializer",3,(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2971 "parser.cpp" /* yacc.c:1646  */
    break;

  case 188:
#line 421 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("initializer",4,(yyvsp[-3].gtn),(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2977 "parser.cpp" /* yacc.c:1646  */
    break;

  case 189:
#line 425 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("initializer_list",1,(yyvsp[0].gtn));}
#line 2983 "parser.cpp" /* yacc.c:1646  */
    break;

  case 190:
#line 426 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("initializer_list",2,(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2989 "parser.cpp" /* yacc.c:1646  */
    break;

  case 191:
#line 427 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("initializer_list",3,(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 2995 "parser.cpp" /* yacc.c:1646  */
    break;

  case 192:
#line 428 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("initializer_list",4,(yyvsp[-3].gtn),(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 3001 "parser.cpp" /* yacc.c:1646  */
    break;

  case 193:
#line 432 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("designation",2,(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 3007 "parser.cpp" /* yacc.c:1646  */
    break;

  case 194:
#line 436 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("designator_list",1,(yyvsp[0].gtn));}
#line 3013 "parser.cpp" /* yacc.c:1646  */
    break;

  case 195:
#line 437 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("designator_list",2,(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 3019 "parser.cpp" /* yacc.c:1646  */
    break;

  case 196:
#line 441 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("designator",3,(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 3025 "parser.cpp" /* yacc.c:1646  */
    break;

  case 197:
#line 442 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("designator",2,(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 3031 "parser.cpp" /* yacc.c:1646  */
    break;

  case 198:
#line 446 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("statement",1,(yyvsp[0].gtn));}
#line 3037 "parser.cpp" /* yacc.c:1646  */
    break;

  case 199:
#line 447 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("statement",1,(yyvsp[0].gtn));}
#line 3043 "parser.cpp" /* yacc.c:1646  */
    break;

  case 200:
#line 448 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("statement",1,(yyvsp[0].gtn));}
#line 3049 "parser.cpp" /* yacc.c:1646  */
    break;

  case 201:
#line 449 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("statement",1,(yyvsp[0].gtn));}
#line 3055 "parser.cpp" /* yacc.c:1646  */
    break;

  case 202:
#line 450 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("statement",1,(yyvsp[0].gtn));}
#line 3061 "parser.cpp" /* yacc.c:1646  */
    break;

  case 203:
#line 451 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("statement",1,(yyvsp[0].gtn));}
#line 3067 "parser.cpp" /* yacc.c:1646  */
    break;

  case 204:
#line 452 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("statement",1,(yyvsp[0].gtn));}
#line 3073 "parser.cpp" /* yacc.c:1646  */
    break;

  case 205:
#line 456 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("print_statement",7,(yyvsp[-6].gtn),(yyvsp[-5].gtn),(yyvsp[-4].gtn),(yyvsp[-3].gtn),(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 3079 "parser.cpp" /* yacc.c:1646  */
    break;

  case 206:
#line 460 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("labeled_statement",3,(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 3085 "parser.cpp" /* yacc.c:1646  */
    break;

  case 207:
#line 461 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("labeled_statement",4,(yyvsp[-3].gtn),(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 3091 "parser.cpp" /* yacc.c:1646  */
    break;

  case 208:
#line 462 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("labeled_statement",3,(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 3097 "parser.cpp" /* yacc.c:1646  */
    break;

  case 209:
#line 466 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("compound_statement",2,(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 3103 "parser.cpp" /* yacc.c:1646  */
    break;

  case 210:
#line 467 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("compound_statement",3,(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 3109 "parser.cpp" /* yacc.c:1646  */
    break;

  case 211:
#line 471 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("block_item_list",1,(yyvsp[0].gtn));}
#line 3115 "parser.cpp" /* yacc.c:1646  */
    break;

  case 212:
#line 472 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("block_item_list",2,(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 3121 "parser.cpp" /* yacc.c:1646  */
    break;

  case 213:
#line 476 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("block_item",1,(yyvsp[0].gtn));}
#line 3127 "parser.cpp" /* yacc.c:1646  */
    break;

  case 214:
#line 477 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("block_item",1,(yyvsp[0].gtn));}
#line 3133 "parser.cpp" /* yacc.c:1646  */
    break;

  case 215:
#line 481 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("expression_statement",1,(yyvsp[0].gtn));}
#line 3139 "parser.cpp" /* yacc.c:1646  */
    break;

  case 216:
#line 482 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("expression_statement",2,(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 3145 "parser.cpp" /* yacc.c:1646  */
    break;

  case 217:
#line 486 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("selection_statement",5,(yyvsp[-4].gtn),(yyvsp[-3].gtn),(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 3151 "parser.cpp" /* yacc.c:1646  */
    break;

  case 218:
#line 487 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("selection_statement",7,(yyvsp[-6].gtn),(yyvsp[-5].gtn),(yyvsp[-4].gtn),(yyvsp[-3].gtn),(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 3157 "parser.cpp" /* yacc.c:1646  */
    break;

  case 219:
#line 488 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("selection_statement",5,(yyvsp[-4].gtn),(yyvsp[-3].gtn),(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 3163 "parser.cpp" /* yacc.c:1646  */
    break;

  case 220:
#line 492 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("iteration_statement",5,(yyvsp[-4].gtn),(yyvsp[-3].gtn),(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 3169 "parser.cpp" /* yacc.c:1646  */
    break;

  case 221:
#line 493 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("iteration_statement",7,(yyvsp[-6].gtn),(yyvsp[-5].gtn),(yyvsp[-4].gtn),(yyvsp[-3].gtn),(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 3175 "parser.cpp" /* yacc.c:1646  */
    break;

  case 222:
#line 494 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("iteration_statement",6,(yyvsp[-5].gtn),(yyvsp[-4].gtn),(yyvsp[-3].gtn),(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 3181 "parser.cpp" /* yacc.c:1646  */
    break;

  case 223:
#line 495 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("iteration_statement",7,(yyvsp[-6].gtn),(yyvsp[-5].gtn),(yyvsp[-4].gtn),(yyvsp[-3].gtn),(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 3187 "parser.cpp" /* yacc.c:1646  */
    break;

  case 224:
#line 496 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("iteration_statement",6,(yyvsp[-5].gtn),(yyvsp[-4].gtn),(yyvsp[-3].gtn),(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 3193 "parser.cpp" /* yacc.c:1646  */
    break;

  case 225:
#line 497 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("iteration_statement",7,(yyvsp[-6].gtn),(yyvsp[-5].gtn),(yyvsp[-4].gtn),(yyvsp[-3].gtn),(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 3199 "parser.cpp" /* yacc.c:1646  */
    break;

  case 226:
#line 501 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("jump_statement",3,(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 3205 "parser.cpp" /* yacc.c:1646  */
    break;

  case 227:
#line 502 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("jump_statement",2,(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 3211 "parser.cpp" /* yacc.c:1646  */
    break;

  case 228:
#line 503 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("jump_statement",2,(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 3217 "parser.cpp" /* yacc.c:1646  */
    break;

  case 229:
#line 504 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("jump_statement",2,(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 3223 "parser.cpp" /* yacc.c:1646  */
    break;

  case 230:
#line 505 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("jump_statement",3,(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 3229 "parser.cpp" /* yacc.c:1646  */
    break;

  case 231:
#line 509 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("translation_unit",1,(yyvsp[0].gtn));}
#line 3235 "parser.cpp" /* yacc.c:1646  */
    break;

  case 232:
#line 510 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("translation_unit",2,(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 3241 "parser.cpp" /* yacc.c:1646  */
    break;

  case 233:
#line 514 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("external_declaration",1,(yyvsp[0].gtn));}
#line 3247 "parser.cpp" /* yacc.c:1646  */
    break;

  case 234:
#line 515 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("external_declaration",1,(yyvsp[0].gtn));}
#line 3253 "parser.cpp" /* yacc.c:1646  */
    break;

  case 235:
#line 519 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("function_definition",4,(yyvsp[-3].gtn),(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 3259 "parser.cpp" /* yacc.c:1646  */
    break;

  case 236:
#line 520 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("function_definition",3,(yyvsp[-2].gtn),(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 3265 "parser.cpp" /* yacc.c:1646  */
    break;

  case 237:
#line 524 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("declaration_list",1,(yyvsp[0].gtn));}
#line 3271 "parser.cpp" /* yacc.c:1646  */
    break;

  case 238:
#line 525 "parser.y" /* yacc.c:1646  */
    {(yyval.gtn) = treeCreate("declaration_list",2,(yyvsp[-1].gtn),(yyvsp[0].gtn));}
#line 3277 "parser.cpp" /* yacc.c:1646  */
    break;


#line 3281 "parser.cpp" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 529 "parser.y" /* yacc.c:1906  */


void yyerror(char const *s){
	fflush(stdout);
	printf("\n%*s\n%*s\n", col, "^", col, s);
}



int main(int argc, char* argv[]){
    if(argc>1){
        yyin=fopen(argv[1],"r");
    }else{
        yyin=stdin;
    }
    yyparse();
    printf("\n");
    treePrint(root,0);
	// printtree(root);
    
	gen(root,argv[1]);

	string cmd = "llc ";
	cmd+=argv[1];
	cmd+=".ll -o ";
	cmd+=argv[1];
	cmd+=".s & clang ";
	cmd+=argv[1];
	cmd+=".s -o ";
	cmd+=argv[1];
	cmd+=".out ";
	// string cmd = "llc "+argv[1]+" -o "+ argv[1]+".s & gcc "+argv[1]+".s -o "+argv[1]+".out"
	system(cmd.c_str());

    // treeNodeFree(root);

    fclose(yyin);

    return 0;
}
