/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "token.h"
#include "symbol_table.h"

extern FILE *yyin;
extern int alpha_yylex(Token *token);
Token t;

SymTable_T sym_table;
int current_scope = 0, loop_depth = 0, function_depth = 0;
char* current_lvalue = NULL;

void print_reduce(char *a, char* b){
	printf("%s -> %s\n", a, b);
}

int yylex(void) {
	return alpha_yylex(&t);
}

void yyerror(const char *s);

#line 97 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    LINE_COMMENT = 258,
    NESTED_COMMENT = 259,
    BLOCK_COMMENT = 260,
    STRING = 261,
    LEFT_BRACE = 262,
    RIGHT_BRACE = 263,
    LEFT_BRACKET = 264,
    RIGHT_BRACKET = 265,
    LEFT_PARENTHESIS = 266,
    RIGHT_PARENTHESIS = 267,
    DOUBLE_COLON = 268,
    DOUBLE_DOT = 269,
    COLON = 270,
    DOT = 271,
    COMMA = 272,
    SEMI_COLON = 273,
    IF = 274,
    ELSE = 275,
    WHILE = 276,
    FOR = 277,
    FUNCTION = 278,
    RETURN = 279,
    BREAK = 280,
    CONTINUE = 281,
    AND = 282,
    NOT = 283,
    OR = 284,
    LOCAL = 285,
    TRUE = 286,
    FALSE = 287,
    NIL = 288,
    EQUAL = 289,
    NOT_EQUAL = 290,
    LESS_EQUAL = 291,
    GREATER_EQUAL = 292,
    ASSIGN = 293,
    LESS = 294,
    GREATER = 295,
    PLUS_PLUS = 296,
    PLUS = 297,
    MINUS_MINUS = 298,
    MINUS = 299,
    MULTIPLY = 300,
    DIVISION = 301,
    MOD = 302,
    CONST_INT = 303,
    CONST_REAL = 304,
    ID = 305
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 28 "parser.y"

	char* strVal;
	char* idVal;
	int intVal;
	double realVal;

#line 207 "parser.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  72
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   457

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  93
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  161

#define YYUNDEFTOK  2
#define YYMAXUTOK   305


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    47,    47,    51,    52,    53,    54,    57,    58,    59,
      60,    61,    62,    66,    70,    71,    72,    76,    77,    78,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    98,    99,   100,   101,   102,   103,   104,
     105,   109,   113,   114,   115,   116,   117,   121,   135,   149,
     158,   162,   163,   164,   165,   169,   170,   187,   193,   194,
     198,   202,   206,   207,   208,   212,   216,   217,   221,   222,
     226,   230,   230,   243,   243,   265,   266,   267,   268,   269,
     270,   274,   282,   290,   294,   298,   299,   304,   303,   315,
     314,   325,   333,   334
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "LINE_COMMENT", "NESTED_COMMENT",
  "BLOCK_COMMENT", "STRING", "LEFT_BRACE", "RIGHT_BRACE", "LEFT_BRACKET",
  "RIGHT_BRACKET", "LEFT_PARENTHESIS", "RIGHT_PARENTHESIS", "DOUBLE_COLON",
  "DOUBLE_DOT", "COLON", "DOT", "COMMA", "SEMI_COLON", "IF", "ELSE",
  "WHILE", "FOR", "FUNCTION", "RETURN", "BREAK", "CONTINUE", "AND", "NOT",
  "OR", "LOCAL", "TRUE", "FALSE", "NIL", "EQUAL", "NOT_EQUAL",
  "LESS_EQUAL", "GREATER_EQUAL", "ASSIGN", "LESS", "GREATER", "PLUS_PLUS",
  "PLUS", "MINUS_MINUS", "MINUS", "MULTIPLY", "DIVISION", "MOD",
  "CONST_INT", "CONST_REAL", "ID", "$accept", "program", "statement",
  "stmt", "expr", "op", "term", "assignexpr", "primary", "lvalue",
  "member", "call", "callsuffix", "normcall", "methodcall", "elist",
  "objectdef", "obj", "indexed", "indexedelem", "block", "$@1", "funcdef",
  "$@2", "const", "idlist", "ifstmt", "elsestmt", "whilestmt", "$@3",
  "forstmt", "$@4", "returnstmt", "returnvalue", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305
};
# endif

#define YYPACT_NINF (-121)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     125,   125,   125,  -121,  -121,    17,   199,   -47,  -121,    11,
      14,    18,   -41,   228,    13,    16,   228,   -12,  -121,  -121,
    -121,     6,     6,   228,  -121,  -121,  -121,    40,  -121,   125,
     373,  -121,  -121,  -121,    48,  -121,     5,  -121,  -121,  -121,
    -121,  -121,  -121,  -121,  -121,  -121,  -121,   125,   228,   410,
      25,    45,    56,  -121,   294,    50,  -121,   228,   228,   228,
    -121,   410,    62,  -121,  -121,   410,  -121,    65,    59,     5,
      59,   410,  -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,
    -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,   228,   228,
     228,    32,   228,  -121,  -121,  -121,  -121,  -121,   228,   228,
      42,    82,   359,   228,  -121,    89,  -121,    97,   315,   336,
      83,   100,  -121,   101,   410,   252,    -2,   108,   410,   273,
      20,  -121,  -121,   228,   410,  -121,   228,   170,  -121,   228,
      72,    97,  -121,  -121,   228,  -121,  -121,    70,    29,   103,
     170,   396,  -121,    57,    60,  -121,  -121,   170,  -121,  -121,
     228,   113,    75,  -121,  -121,    64,  -121,  -121,  -121,   170,
    -121
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       6,     6,     6,    77,    71,    64,     0,     0,    16,     0,
       0,     0,     0,    93,     0,     0,     0,     0,    79,    80,
      78,     0,     0,     0,    75,    76,    47,     0,     2,     6,
       0,    19,    17,    40,    42,    50,    43,    44,    14,    15,
      46,     8,     9,    10,    11,     4,     5,     6,     0,    62,
      66,     0,    67,    68,     0,     0,    49,     0,     0,    64,
      73,    92,     0,    12,    13,    35,    48,     0,    36,     0,
      38,    34,     1,     3,     7,    31,    32,    29,    30,    28,
      26,    27,    25,    20,    21,    22,    23,    24,     0,     0,
      64,     0,     0,    37,    39,    56,    58,    59,     0,    64,
       0,     0,     0,     0,    65,     0,    33,    45,     0,     0,
       0,     0,    91,     0,    18,     0,     0,    51,    41,     0,
       0,    53,    72,     0,    63,    69,    64,     0,    87,     0,
      83,     0,    52,    60,    64,    54,    55,     0,     0,    86,
       0,     0,    81,     0,     0,    70,    57,     0,    84,    88,
      64,     0,     0,    61,    85,     0,    74,    82,    89,     0,
      90
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -121,  -121,     4,  -120,    -5,  -121,  -121,  -121,  -121,    -9,
    -121,    81,  -121,  -121,  -121,   -55,  -121,  -121,  -121,    21,
     -24,  -121,    -4,  -121,  -121,  -121,  -121,  -121,  -121,  -121,
    -121,  -121,  -121,  -121
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    27,    28,    29,    30,    88,    31,    32,    33,    34,
      35,    36,    95,    96,    97,    50,    37,    51,    52,    53,
      38,    47,    39,   111,    40,   143,    41,   148,    42,   140,
      43,   159,    44,    62
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      49,    54,    55,    56,   110,    45,    46,   139,    61,    60,
     133,    65,    68,    70,    98,   103,    99,    67,    71,     7,
     149,   100,    57,     3,    48,    58,     5,   154,     6,    59,
       7,    63,   136,    73,    64,   116,    17,   103,    66,   160,
      72,   146,   103,   102,   120,    16,   103,    17,    18,    19,
      20,   101,   108,   109,    49,   104,    26,    89,    21,    90,
      22,    23,   107,   113,    91,    24,    25,    26,    89,   151,
      90,   138,   153,   105,   152,    91,   158,   103,   145,   144,
     112,   103,   117,   114,   115,    49,    92,   118,    12,    93,
     122,    94,   121,   119,    49,   155,    48,    75,   124,    76,
     103,   129,    69,    69,    77,    78,    79,    80,   126,    81,
      82,   130,    83,   131,    84,    85,    86,    87,   137,   134,
       4,    49,   142,   147,   141,   157,   125,   156,     1,    49,
       2,     3,     4,     0,     5,     0,     6,     0,     7,     0,
       0,     0,     0,     8,     9,    49,    10,    11,    12,    13,
      14,    15,     0,    16,     0,    17,    18,    19,    20,     0,
       0,     0,     0,     0,     0,     0,    21,     0,    22,    23,
       0,     0,     0,    24,    25,    26,     3,     4,     0,     5,
       0,     6,     0,     7,     0,     0,     0,     0,     8,     9,
       0,    10,    11,    12,    13,    14,    15,     0,    16,     0,
      17,    18,    19,    20,     0,     3,     0,     0,     5,     0,
       6,    21,     7,    22,    23,     0,     0,     0,    24,    25,
      26,     0,    12,     0,     0,     0,     0,    16,     0,    17,
      18,    19,    20,     0,     3,     0,     0,     5,     0,     6,
      21,     7,    22,    23,     0,     0,     0,    24,    25,    26,
       0,     0,     0,     0,     0,     0,    16,     0,    17,    18,
      19,    20,   132,     0,     0,     0,     0,     0,     0,    21,
       0,    22,    23,     0,     0,     0,    24,    25,    26,    75,
       0,    76,     0,   135,     0,     0,    77,    78,    79,    80,
       0,    81,    82,     0,    83,     0,    84,    85,    86,    87,
      75,     0,    76,     0,     0,     0,   106,    77,    78,    79,
      80,     0,    81,    82,     0,    83,     0,    84,    85,    86,
      87,    75,     0,    76,     0,     0,     0,   127,    77,    78,
      79,    80,     0,    81,    82,     0,    83,     0,    84,    85,
      86,    87,    75,     0,    76,     0,     0,     0,   128,    77,
      78,    79,    80,     0,    81,    82,     0,    83,     0,    84,
      85,    86,    87,    75,     0,    76,     0,     0,     0,     0,
      77,    78,    79,    80,   123,    81,    82,     0,    83,     0,
      84,    85,    86,    87,     0,     0,    75,     0,    76,     0,
       0,    74,     0,    77,    78,    79,    80,     0,    81,    82,
      75,    83,    76,    84,    85,    86,    87,    77,    78,    79,
      80,     0,    81,    82,   150,    83,     0,    84,    85,    86,
      87,     0,     0,    75,     0,    76,     0,     0,     0,     0,
      77,    78,    79,    80,     0,    81,    82,    75,    83,    76,
      84,    85,    86,    87,    77,    78,    79,    80,     0,    81,
      82,     0,    83,     0,    84,    85,    86,    87
};

static const yytype_int16 yycheck[] =
{
       5,     6,     6,    50,    59,     1,     2,   127,    13,    50,
      12,    16,    21,    22,     9,    17,    11,    11,    23,    13,
     140,    16,    11,     6,     7,    11,     9,   147,    11,    11,
      13,    18,    12,    29,    18,    90,    30,    17,    50,   159,
       0,    12,    17,    48,    99,    28,    17,    30,    31,    32,
      33,    47,    57,    58,    59,    10,    50,     9,    41,    11,
      43,    44,    12,    67,    16,    48,    49,    50,     9,    12,
      11,   126,    12,    17,    17,    16,    12,    17,     8,   134,
      18,    17,    50,    88,    89,    90,    38,    92,    23,    41,
       8,    43,    50,    98,    99,   150,     7,    27,   103,    29,
      17,    18,    21,    22,    34,    35,    36,    37,    11,    39,
      40,    11,    42,    12,    44,    45,    46,    47,   123,    11,
       7,   126,    50,    20,   129,    50,   105,   151,     3,   134,
       5,     6,     7,    -1,     9,    -1,    11,    -1,    13,    -1,
      -1,    -1,    -1,    18,    19,   150,    21,    22,    23,    24,
      25,    26,    -1,    28,    -1,    30,    31,    32,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    41,    -1,    43,    44,
      -1,    -1,    -1,    48,    49,    50,     6,     7,    -1,     9,
      -1,    11,    -1,    13,    -1,    -1,    -1,    -1,    18,    19,
      -1,    21,    22,    23,    24,    25,    26,    -1,    28,    -1,
      30,    31,    32,    33,    -1,     6,    -1,    -1,     9,    -1,
      11,    41,    13,    43,    44,    -1,    -1,    -1,    48,    49,
      50,    -1,    23,    -1,    -1,    -1,    -1,    28,    -1,    30,
      31,    32,    33,    -1,     6,    -1,    -1,     9,    -1,    11,
      41,    13,    43,    44,    -1,    -1,    -1,    48,    49,    50,
      -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,    30,    31,
      32,    33,    10,    -1,    -1,    -1,    -1,    -1,    -1,    41,
      -1,    43,    44,    -1,    -1,    -1,    48,    49,    50,    27,
      -1,    29,    -1,    10,    -1,    -1,    34,    35,    36,    37,
      -1,    39,    40,    -1,    42,    -1,    44,    45,    46,    47,
      27,    -1,    29,    -1,    -1,    -1,    12,    34,    35,    36,
      37,    -1,    39,    40,    -1,    42,    -1,    44,    45,    46,
      47,    27,    -1,    29,    -1,    -1,    -1,    12,    34,    35,
      36,    37,    -1,    39,    40,    -1,    42,    -1,    44,    45,
      46,    47,    27,    -1,    29,    -1,    -1,    -1,    12,    34,
      35,    36,    37,    -1,    39,    40,    -1,    42,    -1,    44,
      45,    46,    47,    27,    -1,    29,    -1,    -1,    -1,    -1,
      34,    35,    36,    37,    15,    39,    40,    -1,    42,    -1,
      44,    45,    46,    47,    -1,    -1,    27,    -1,    29,    -1,
      -1,    18,    -1,    34,    35,    36,    37,    -1,    39,    40,
      27,    42,    29,    44,    45,    46,    47,    34,    35,    36,
      37,    -1,    39,    40,    18,    42,    -1,    44,    45,    46,
      47,    -1,    -1,    27,    -1,    29,    -1,    -1,    -1,    -1,
      34,    35,    36,    37,    -1,    39,    40,    27,    42,    29,
      44,    45,    46,    47,    34,    35,    36,    37,    -1,    39,
      40,    -1,    42,    -1,    44,    45,    46,    47
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     5,     6,     7,     9,    11,    13,    18,    19,
      21,    22,    23,    24,    25,    26,    28,    30,    31,    32,
      33,    41,    43,    44,    48,    49,    50,    52,    53,    54,
      55,    57,    58,    59,    60,    61,    62,    67,    71,    73,
      75,    77,    79,    81,    83,    53,    53,    72,     7,    55,
      66,    68,    69,    70,    55,    73,    50,    11,    11,    11,
      50,    55,    84,    18,    18,    55,    50,    11,    60,    62,
      60,    55,     0,    53,    18,    27,    29,    34,    35,    36,
      37,    39,    40,    42,    44,    45,    46,    47,    56,     9,
      11,    16,    38,    41,    43,    63,    64,    65,     9,    11,
      16,    53,    55,    17,    10,    17,    12,    12,    55,    55,
      66,    74,    18,    73,    55,    55,    66,    50,    55,    55,
      66,    50,     8,    15,    55,    70,    11,    12,    12,    18,
      11,    12,    10,    12,    11,    10,    12,    55,    66,    54,
      80,    55,    50,    76,    66,     8,    12,    20,    78,    54,
      18,    12,    17,    12,    54,    66,    71,    50,    12,    82,
      54
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    51,    52,    53,    53,    53,    53,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    55,    55,    55,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    57,    57,    57,    57,    57,    57,    57,
      57,    58,    59,    59,    59,    59,    59,    60,    60,    60,
      60,    61,    61,    61,    61,    62,    62,    62,    63,    63,
      64,    65,    66,    66,    66,    67,    68,    68,    69,    69,
      70,    72,    71,    74,    73,    75,    75,    75,    75,    75,
      75,    76,    76,    76,    77,    78,    78,    80,    79,    82,
      81,    83,    84,    84
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     2,     2,     0,     2,     1,     1,
       1,     1,     2,     2,     1,     1,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     2,     2,     2,     2,     2,     2,
       1,     3,     1,     1,     1,     3,     1,     1,     2,     2,
       1,     3,     4,     3,     4,     4,     2,     6,     1,     1,
       3,     5,     1,     3,     0,     3,     1,     1,     1,     3,
       5,     0,     4,     0,     7,     1,     1,     1,     1,     1,
       1,     1,     3,     0,     6,     2,     0,     0,     6,     0,
      10,     3,     1,     0
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

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
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
#line 47 "parser.y"
                 { print_reduce("program", "statement"); }
#line 1562 "parser.tab.c"
    break;

  case 3:
#line 51 "parser.y"
                        { print_reduce("statement", "stmt statement"); }
#line 1568 "parser.tab.c"
    break;

  case 4:
#line 52 "parser.y"
                                 { print_reduce("statement", "LINE_COMMENT statement"); }
#line 1574 "parser.tab.c"
    break;

  case 5:
#line 53 "parser.y"
                                  { print_reduce("statement", "BLOCK_COMMENT statement"); }
#line 1580 "parser.tab.c"
    break;

  case 6:
#line 54 "parser.y"
                      { print_reduce("statement", "empty"); }
#line 1586 "parser.tab.c"
    break;

  case 7:
#line 57 "parser.y"
                        { print_reduce("stmt", "expr SEMI_COLON"); }
#line 1592 "parser.tab.c"
    break;

  case 8:
#line 58 "parser.y"
                 { print_reduce("stmt", "ifstmt"); }
#line 1598 "parser.tab.c"
    break;

  case 9:
#line 59 "parser.y"
                    { print_reduce("stmt", "ifstmt"); }
#line 1604 "parser.tab.c"
    break;

  case 10:
#line 60 "parser.y"
                  { print_reduce("stmt", "forstmt"); }
#line 1610 "parser.tab.c"
    break;

  case 11:
#line 61 "parser.y"
                     { print_reduce("stmt", "returnstmt"); }
#line 1616 "parser.tab.c"
    break;

  case 12:
#line 62 "parser.y"
                           {
		if(loop_depth == 0) printf("Error: break called outside of loop at line %d\n", t.line);	
		print_reduce("stmt", "returnstmt");
	}
#line 1625 "parser.tab.c"
    break;

  case 13:
#line 66 "parser.y"
                              {
                if(loop_depth == 0) printf("Error: continue called outside of loop at line %d\n", t.line);
		print_reduce("stmt", "CONTINUE SEMI_COLON");
	}
#line 1634 "parser.tab.c"
    break;

  case 14:
#line 70 "parser.y"
                { print_reduce("stmt", "block"); }
#line 1640 "parser.tab.c"
    break;

  case 15:
#line 71 "parser.y"
                  { print_reduce("stmt", "funcdef"); }
#line 1646 "parser.tab.c"
    break;

  case 16:
#line 72 "parser.y"
                     { print_reduce("stmt", "SEMI_COLON"); }
#line 1652 "parser.tab.c"
    break;

  case 17:
#line 76 "parser.y"
                   { print_reduce("expr", "assignexpr"); }
#line 1658 "parser.tab.c"
    break;

  case 18:
#line 77 "parser.y"
                       { print_reduce("expr", "expr op expr"); }
#line 1664 "parser.tab.c"
    break;

  case 19:
#line 78 "parser.y"
               { print_reduce("expr", "term"); }
#line 1670 "parser.tab.c"
    break;

  case 20:
#line 82 "parser.y"
             { print_reduce("op", "PLUS"); }
#line 1676 "parser.tab.c"
    break;

  case 21:
#line 83 "parser.y"
                { print_reduce("op", "MINUS"); }
#line 1682 "parser.tab.c"
    break;

  case 22:
#line 84 "parser.y"
                   { print_reduce("op", "MULTIPLY"); }
#line 1688 "parser.tab.c"
    break;

  case 23:
#line 85 "parser.y"
                   { print_reduce("op", "DIVISION"); }
#line 1694 "parser.tab.c"
    break;

  case 24:
#line 86 "parser.y"
              { print_reduce("op", "MOD"); }
#line 1700 "parser.tab.c"
    break;

  case 25:
#line 87 "parser.y"
                  { print_reduce("op", "GREATER"); }
#line 1706 "parser.tab.c"
    break;

  case 26:
#line 88 "parser.y"
                        { print_reduce("op", "GREATER_EQUAL"); }
#line 1712 "parser.tab.c"
    break;

  case 27:
#line 89 "parser.y"
               { print_reduce("op", "LESS"); }
#line 1718 "parser.tab.c"
    break;

  case 28:
#line 90 "parser.y"
                     { print_reduce("op", "LESS_EQUAL"); }
#line 1724 "parser.tab.c"
    break;

  case 29:
#line 91 "parser.y"
                { print_reduce("op", "EQUAL"); }
#line 1730 "parser.tab.c"
    break;

  case 30:
#line 92 "parser.y"
                    { print_reduce("op", "NOT_EQUAL"); }
#line 1736 "parser.tab.c"
    break;

  case 31:
#line 93 "parser.y"
              { print_reduce("op", "AND"); }
#line 1742 "parser.tab.c"
    break;

  case 32:
#line 94 "parser.y"
             { print_reduce("op", "OR"); }
#line 1748 "parser.tab.c"
    break;

  case 33:
#line 98 "parser.y"
                                                { print_reduce("term", "LEFT_PARENTHESIS expr RIGHT_PARENTHESIS"); }
#line 1754 "parser.tab.c"
    break;

  case 34:
#line 99 "parser.y"
                     { print_reduce("term", "MINUS expr"); }
#line 1760 "parser.tab.c"
    break;

  case 35:
#line 100 "parser.y"
                   { print_reduce("term", "NOT expr"); }
#line 1766 "parser.tab.c"
    break;

  case 36:
#line 101 "parser.y"
                           { print_reduce("term", "PLUS_PLUS lvalue"); }
#line 1772 "parser.tab.c"
    break;

  case 37:
#line 102 "parser.y"
                           { print_reduce("term", "lvalue PLUS_PLUS"); }
#line 1778 "parser.tab.c"
    break;

  case 38:
#line 103 "parser.y"
                             { print_reduce("term", "MINUS_MINUS lvalue"); }
#line 1784 "parser.tab.c"
    break;

  case 39:
#line 104 "parser.y"
                             { print_reduce("term", "lvalue MINUS_MINUS"); }
#line 1790 "parser.tab.c"
    break;

  case 40:
#line 105 "parser.y"
                  { print_reduce("term", "primary"); }
#line 1796 "parser.tab.c"
    break;

  case 41:
#line 109 "parser.y"
                             { print_reduce("assignexpr", "lvalue ASSIGN expr"); }
#line 1802 "parser.tab.c"
    break;

  case 42:
#line 113 "parser.y"
               { print_reduce("primary", "lvalue"); }
#line 1808 "parser.tab.c"
    break;

  case 43:
#line 114 "parser.y"
               { print_reduce("primary", "call"); }
#line 1814 "parser.tab.c"
    break;

  case 44:
#line 115 "parser.y"
                    { print_reduce("primary", "objectdef"); }
#line 1820 "parser.tab.c"
    break;

  case 45:
#line 116 "parser.y"
                                                     { print_reduce("primary", "LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS"); }
#line 1826 "parser.tab.c"
    break;

  case 46:
#line 117 "parser.y"
                { print_reduce("primary", "const"); }
#line 1832 "parser.tab.c"
    break;

  case 47:
#line 121 "parser.y"
           { /* add in current scope */
		Symbol *s = SymTable_lookup_scope(sym_table, (yyvsp[0].idVal), current_scope);
		
		if(s == NULL){
			s = Symbol_create((yyvsp[0].idVal), "variable", current_scope, t.line, 1);
            		SymTable_put(sym_table, s);
		}

		else if(s != NULL && strcmp(s->type, "function") == 0){
			current_lvalue = (yyvsp[0].idVal);
		}

		{ print_reduce("lvalue", "ID"); }
	}
#line 1851 "parser.tab.c"
    break;

  case 48:
#line 135 "parser.y"
                   { /* check for declaration then add */
		Symbol* s = SymTable_lookup_scope(sym_table, (yyvsp[0].idVal), current_scope);

		if(s != NULL){
                        printf("Error: redeclaration of local variable %s at line %d\n", (yyvsp[0].idVal), t.line);
                }

                else {
                        Symbol* new_s = Symbol_create((yyvsp[0].idVal), "local variable", current_scope, t.line, 1);
                        SymTable_put(sym_table, new_s);
                }

		{ print_reduce("lvalue", "LOCAL ID"); }
        }
#line 1870 "parser.tab.c"
    break;

  case 49:
#line 149 "parser.y"
                          { /* lookup in scope 0 */
		Symbol* s = SymTable_lookup_scope(sym_table, (yyvsp[0].idVal), 0);

		if(s == NULL){
			printf("Error: undefined global variable %s at line %d\n", (yyvsp[0].idVal), t.line);
		}

		{ print_reduce("lvalue", "DOUBLE_COLONID"); }
	}
#line 1884 "parser.tab.c"
    break;

  case 50:
#line 158 "parser.y"
                 { print_reduce("lvalue", "member"); }
#line 1890 "parser.tab.c"
    break;

  case 51:
#line 162 "parser.y"
                      { print_reduce("member", "lvalue DOT ID"); }
#line 1896 "parser.tab.c"
    break;

  case 52:
#line 163 "parser.y"
                                                 { print_reduce("member", "lvalue LEFT_BRACKET expr RIGHT_BRACKET"); }
#line 1902 "parser.tab.c"
    break;

  case 53:
#line 164 "parser.y"
                      { print_reduce("member", "call DOT ID"); }
#line 1908 "parser.tab.c"
    break;

  case 54:
#line 165 "parser.y"
                                               { print_reduce("member", "call LEFT_BRACKET expr RIGHT_BRACKET"); }
#line 1914 "parser.tab.c"
    break;

  case 55:
#line 169 "parser.y"
                                                  { print_reduce("call", "call LEFT_PARENTHESIS elist RIGHT_PARENTHESIS"); }
#line 1920 "parser.tab.c"
    break;

  case 56:
#line 170 "parser.y"
                        { /* check if symbol used as function is in the symbol table and if it is a function */
	if(current_lvalue != NULL){
		Symbol* s = SymTable_lookup(sym_table, current_lvalue, current_scope);

		if(s == NULL){
        		printf("Error: undefined function %s at line %d\n", current_lvalue, t.line);
		}

		else if(s != NULL && strcmp(s->type, "function") != 0){
			printf("Error: %s %s incorrectly used as function at line %d\n", s->type, current_lvalue, t.line);
		}

		current_lvalue = NULL;
	}

	{ print_reduce("call", "lvalue callsuffix"); }
    }
#line 1942 "parser.tab.c"
    break;

  case 57:
#line 187 "parser.y"
                                                                                          { 
	print_reduce("call", "LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS LEFT_PARENTHESIS elist RIGHT_PARENTHESIS");
    }
#line 1950 "parser.tab.c"
    break;

  case 58:
#line 193 "parser.y"
                 { print_reduce("callsuffix", "normcall"); }
#line 1956 "parser.tab.c"
    break;

  case 59:
#line 194 "parser.y"
                     { print_reduce("callsuffix", "methodcall"); }
#line 1962 "parser.tab.c"
    break;

  case 60:
#line 198 "parser.y"
                                                 { print_reduce("normcall", "LEFT_PARENTHESIS elist RIGHT_PARENTHESIS"); }
#line 1968 "parser.tab.c"
    break;

  case 61:
#line 202 "parser.y"
                                                          { print_reduce("methodcall", "DOT ID LEFT_PARENTHESIS elist RIGHT_PARENTHESIS"); }
#line 1974 "parser.tab.c"
    break;

  case 62:
#line 206 "parser.y"
             { print_reduce("elist", "expr"); }
#line 1980 "parser.tab.c"
    break;

  case 63:
#line 207 "parser.y"
                           { print_reduce("elist", "elist COMMA expr"); }
#line 1986 "parser.tab.c"
    break;

  case 64:
#line 208 "parser.y"
                      { print_reduce("elist", "empty"); }
#line 1992 "parser.tab.c"
    break;

  case 65:
#line 212 "parser.y"
                                        { print_reduce("objectdef", "LEFT_BRACKET obj RIGHT_BRACKET"); }
#line 1998 "parser.tab.c"
    break;

  case 66:
#line 216 "parser.y"
              { print_reduce("obj", "elist"); }
#line 2004 "parser.tab.c"
    break;

  case 67:
#line 217 "parser.y"
                  { print_reduce("obj", "indexed"); }
#line 2010 "parser.tab.c"
    break;

  case 68:
#line 221 "parser.y"
                    { print_reduce("indexed", "indexedelem"); }
#line 2016 "parser.tab.c"
    break;

  case 69:
#line 222 "parser.y"
                                    { print_reduce("indexed", "indexed COMMA indexedelem"); }
#line 2022 "parser.tab.c"
    break;

  case 70:
#line 226 "parser.y"
                                                  { print_reduce("indexedelem", "LEFT_BRACE expr COLON expr RIGHT_BRACE"); }
#line 2028 "parser.tab.c"
    break;

  case 71:
#line 230 "parser.y"
                   {
		current_scope++;
	}
#line 2036 "parser.tab.c"
    break;

  case 72:
#line 234 "parser.y"
                    {	
		SymTable_hide_scope(sym_table, current_scope); 
		current_scope--;

		print_reduce("block", "LEFT_BRACE statement RIGHT_BRACE");
	}
#line 2047 "parser.tab.c"
    break;

  case 73:
#line 243 "parser.y"
                   {
		if(SymTable_lookup_scope(sym_table, (yyvsp[0].idVal), current_scope) == NULL){
			Symbol* s = Symbol_create((yyvsp[0].idVal), "function", current_scope, t.line, 1);
			SymTable_put(sym_table, s);

                	function_depth++;
		}
		else {
			printf("Error: redeclaration of function %s at line %d\n", (yyvsp[0].idVal), t.line);
		}
	}
#line 2063 "parser.tab.c"
    break;

  case 74:
#line 255 "parser.y"
              {
		SymTable_hide_scope(sym_table, current_scope);

		function_depth--;

		print_reduce("funcdef", "FUNCTION ID LEFT_PARENTHESIS idlist RIGHT_PARENTHESIS block");
	}
#line 2075 "parser.tab.c"
    break;

  case 75:
#line 265 "parser.y"
                  { print_reduce("const", "CONST_INT"); }
#line 2081 "parser.tab.c"
    break;

  case 76:
#line 266 "parser.y"
                     { print_reduce("const", "CONST_REAL"); }
#line 2087 "parser.tab.c"
    break;

  case 77:
#line 267 "parser.y"
                 { print_reduce("const", "STRING"); }
#line 2093 "parser.tab.c"
    break;

  case 78:
#line 268 "parser.y"
              { print_reduce("const", "NIL"); }
#line 2099 "parser.tab.c"
    break;

  case 79:
#line 269 "parser.y"
               { print_reduce("const", "TRUE"); }
#line 2105 "parser.tab.c"
    break;

  case 80:
#line 270 "parser.y"
                { print_reduce("const", "FALSE"); }
#line 2111 "parser.tab.c"
    break;

  case 81:
#line 274 "parser.y"
           { 	
		if(SymTable_lookup_scope(sym_table, (yyvsp[0].idVal), current_scope) == NULL){
			Symbol* s = Symbol_create((yyvsp[0].idVal), "parameter", current_scope, t.line, 1);
           		SymTable_put(sym_table, s); 
		}

		print_reduce("idlist", "ID");
	}
#line 2124 "parser.tab.c"
    break;

  case 82:
#line 282 "parser.y"
                          {
		if(SymTable_lookup_scope(sym_table, (yyvsp[0].idVal), current_scope) == NULL){
			Symbol* s = Symbol_create((yyvsp[0].idVal), "parameter", current_scope, t.line, 1);
                	SymTable_put(sym_table, s);
		}

		print_reduce("idlist", "idlist COMMA ID");
        }
#line 2137 "parser.tab.c"
    break;

  case 83:
#line 290 "parser.y"
                      { print_reduce("idlist", "empty"); }
#line 2143 "parser.tab.c"
    break;

  case 84:
#line 294 "parser.y"
                                                                 { print_reduce("ifstmt", "IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt elsestmt"); }
#line 2149 "parser.tab.c"
    break;

  case 85:
#line 298 "parser.y"
                  { print_reduce("elsestmt", "ELSE stmt"); }
#line 2155 "parser.tab.c"
    break;

  case 86:
#line 299 "parser.y"
                      { print_reduce("elsestmt", "empty"); }
#line 2161 "parser.tab.c"
    break;

  case 87:
#line 304 "parser.y"
        { loop_depth++; }
#line 2167 "parser.tab.c"
    break;

  case 88:
#line 306 "parser.y"
        { 
		loop_depth--; 
		
		print_reduce("whilestmt", "WHILE LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt");
	}
#line 2177 "parser.tab.c"
    break;

  case 89:
#line 315 "parser.y"
        { loop_depth++; }
#line 2183 "parser.tab.c"
    break;

  case 90:
#line 317 "parser.y"
        { 
		loop_depth--; 

		print_reduce("forstmt", "FOR LEFT_PARENTHESIS elist SEMI_COLON expr SEMI_COLON elist RIGHT_PARENTHESIS");
	}
#line 2193 "parser.tab.c"
    break;

  case 91:
#line 325 "parser.y"
                                      {
		if(function_depth == 0) printf("Error: return called outside of function at line %d\n", t.line); 

		print_reduce("returnstmt", "RETURN returnvalue SEMI_COLON");
	}
#line 2203 "parser.tab.c"
    break;

  case 92:
#line 333 "parser.y"
             { print_reduce("returnvalue", "expr"); }
#line 2209 "parser.tab.c"
    break;

  case 93:
#line 334 "parser.y"
                      { print_reduce("returnvalue", "empty"); }
#line 2215 "parser.tab.c"
    break;


#line 2219 "parser.tab.c"

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
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
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
                  yystos[+*yyssp], yyvsp);
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
#line 337 "parser.y"


int main(int argc, char **argv) {

	assert(argc == 2);

	yyin = fopen(argv[1], "r");
	assert(yyin);

	printf("Parsing started.\n");

	sym_table = SymTable_create();

	/* library functions */
	SymTable_put(sym_table, Symbol_create("print", "library function", 0, 0, 1));
	SymTable_put(sym_table, Symbol_create("input", "library function", 0, 0, 1));
	SymTable_put(sym_table, Symbol_create("objectmemberkeys", "library function", 0, 0, 1));
        SymTable_put(sym_table, Symbol_create("objecttotalmembers", "library function", 0, 0, 1));
        SymTable_put(sym_table, Symbol_create("objectcopy", "library function", 0, 0, 1));
        SymTable_put(sym_table, Symbol_create("totalarguments", "library function", 0, 0, 1));
        SymTable_put(sym_table, Symbol_create("argument", "library function", 0, 0, 1));
        SymTable_put(sym_table, Symbol_create("typeof", "library function", 0, 0, 1));
        SymTable_put(sym_table, Symbol_create("strtonum", "library function", 0, 0, 1));
        SymTable_put(sym_table, Symbol_create("sqrt", "library function", 0, 0, 1));
        SymTable_put(sym_table, Symbol_create("cos", "library function", 0, 0, 1));
        SymTable_put(sym_table, Symbol_create("sin", "library function", 0, 0, 1));

	if(yyparse() != 0) {
        	SymTable_free(sym_table);
        	return 1;
    	}	

    	printf("Parsing finished.\n");

	SymTable_print(sym_table);

	SymTable_free(sym_table);
	fclose(yyin);
    	
	return 0;
}

void yyerror(const char *s) {
	fprintf(stderr, "Parse error: %s\n", s);
}

