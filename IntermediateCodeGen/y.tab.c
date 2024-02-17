/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "2005018.y"

#include<bits/stdc++.h>
#include "ASMmain.h"
// #include <ParseTree>
//#define YYSTYPE SymbolInfo*
#define pb(x) push_back(x)

using namespace std; 

int yyparse(void);  
int yylex(void);

extern FILE *yyin;
extern int line_count; 
int err_sem = 0;

SymbolTable table(11); 

string var_type = "";

ofstream logfile,errf,parsefile,ASM,optASM;/// ASM -> show whole code. need to be optimized.

vector<SymbolInfo*> params;
vector<string>function_arg_types;
int args_ID_cnt = 0;   


void yyerror(const char *s){
    cout << "Error: " << s << "\n"; 
    // cout << line_count << "\n";  
}

#line 104 "y.tab.c"

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

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    CONST_INT = 258,               /* CONST_INT  */
    CONST_FLOAT = 259,             /* CONST_FLOAT  */
    CONST_CHAR = 260,              /* CONST_CHAR  */
    ADDOP = 261,                   /* ADDOP  */
    MULOP = 262,                   /* MULOP  */
    LOGICOP = 263,                 /* LOGICOP  */
    RELOP = 264,                   /* RELOP  */
    ID = 265,                      /* ID  */
    IF = 266,                      /* IF  */
    ELSE = 267,                    /* ELSE  */
    FOR = 268,                     /* FOR  */
    WHILE = 269,                   /* WHILE  */
    DO = 270,                      /* DO  */
    CONTINUE = 271,                /* CONTINUE  */
    INT = 272,                     /* INT  */
    FLOAT = 273,                   /* FLOAT  */
    CHAR = 274,                    /* CHAR  */
    DOUBLE = 275,                  /* DOUBLE  */
    VOID = 276,                    /* VOID  */
    RETURN = 277,                  /* RETURN  */
    INCOP = 278,                   /* INCOP  */
    DECOP = 279,                   /* DECOP  */
    ASSIGNOP = 280,                /* ASSIGNOP  */
    LPAREN = 281,                  /* LPAREN  */
    RPAREN = 282,                  /* RPAREN  */
    LCURL = 283,                   /* LCURL  */
    RCURL = 284,                   /* RCURL  */
    LTHIRD = 285,                  /* LTHIRD  */
    RTHIRD = 286,                  /* RTHIRD  */
    SEMICOLON = 287,               /* SEMICOLON  */
    COMMA = 288,                   /* COMMA  */
    NOT = 289,                     /* NOT  */
    PRINTLN = 290,                 /* PRINTLN  */
    LOWER_THAN_ELSE = 291          /* LOWER_THAN_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define CONST_INT 258
#define CONST_FLOAT 259
#define CONST_CHAR 260
#define ADDOP 261
#define MULOP 262
#define LOGICOP 263
#define RELOP 264
#define ID 265
#define IF 266
#define ELSE 267
#define FOR 268
#define WHILE 269
#define DO 270
#define CONTINUE 271
#define INT 272
#define FLOAT 273
#define CHAR 274
#define DOUBLE 275
#define VOID 276
#define RETURN 277
#define INCOP 278
#define DECOP 279
#define ASSIGNOP 280
#define LPAREN 281
#define RPAREN 282
#define LCURL 283
#define RCURL 284
#define LTHIRD 285
#define RTHIRD 286
#define SEMICOLON 287
#define COMMA 288
#define NOT 289
#define PRINTLN 290
#define LOWER_THAN_ELSE 291

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 34 "2005018.y"

    SymbolInfo* symbVal;

#line 233 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_CONST_INT = 3,                  /* CONST_INT  */
  YYSYMBOL_CONST_FLOAT = 4,                /* CONST_FLOAT  */
  YYSYMBOL_CONST_CHAR = 5,                 /* CONST_CHAR  */
  YYSYMBOL_ADDOP = 6,                      /* ADDOP  */
  YYSYMBOL_MULOP = 7,                      /* MULOP  */
  YYSYMBOL_LOGICOP = 8,                    /* LOGICOP  */
  YYSYMBOL_RELOP = 9,                      /* RELOP  */
  YYSYMBOL_ID = 10,                        /* ID  */
  YYSYMBOL_IF = 11,                        /* IF  */
  YYSYMBOL_ELSE = 12,                      /* ELSE  */
  YYSYMBOL_FOR = 13,                       /* FOR  */
  YYSYMBOL_WHILE = 14,                     /* WHILE  */
  YYSYMBOL_DO = 15,                        /* DO  */
  YYSYMBOL_CONTINUE = 16,                  /* CONTINUE  */
  YYSYMBOL_INT = 17,                       /* INT  */
  YYSYMBOL_FLOAT = 18,                     /* FLOAT  */
  YYSYMBOL_CHAR = 19,                      /* CHAR  */
  YYSYMBOL_DOUBLE = 20,                    /* DOUBLE  */
  YYSYMBOL_VOID = 21,                      /* VOID  */
  YYSYMBOL_RETURN = 22,                    /* RETURN  */
  YYSYMBOL_INCOP = 23,                     /* INCOP  */
  YYSYMBOL_DECOP = 24,                     /* DECOP  */
  YYSYMBOL_ASSIGNOP = 25,                  /* ASSIGNOP  */
  YYSYMBOL_LPAREN = 26,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 27,                    /* RPAREN  */
  YYSYMBOL_LCURL = 28,                     /* LCURL  */
  YYSYMBOL_RCURL = 29,                     /* RCURL  */
  YYSYMBOL_LTHIRD = 30,                    /* LTHIRD  */
  YYSYMBOL_RTHIRD = 31,                    /* RTHIRD  */
  YYSYMBOL_SEMICOLON = 32,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 33,                     /* COMMA  */
  YYSYMBOL_NOT = 34,                       /* NOT  */
  YYSYMBOL_PRINTLN = 35,                   /* PRINTLN  */
  YYSYMBOL_LOWER_THAN_ELSE = 36,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 37,                  /* $accept  */
  YYSYMBOL_start = 38,                     /* start  */
  YYSYMBOL_program = 39,                   /* program  */
  YYSYMBOL_unit = 40,                      /* unit  */
  YYSYMBOL_func_declaration = 41,          /* func_declaration  */
  YYSYMBOL_func_definition = 42,           /* func_definition  */
  YYSYMBOL_parameter_list = 43,            /* parameter_list  */
  YYSYMBOL_compound_statement = 44,        /* compound_statement  */
  YYSYMBOL_45_1 = 45,                      /* $@1  */
  YYSYMBOL_var_declaration = 46,           /* var_declaration  */
  YYSYMBOL_type_specifier = 47,            /* type_specifier  */
  YYSYMBOL_declaration_list = 48,          /* declaration_list  */
  YYSYMBOL_statements = 49,                /* statements  */
  YYSYMBOL_statement = 50,                 /* statement  */
  YYSYMBOL_expression_statement = 51,      /* expression_statement  */
  YYSYMBOL_variable = 52,                  /* variable  */
  YYSYMBOL_expression = 53,                /* expression  */
  YYSYMBOL_logic_expression = 54,          /* logic_expression  */
  YYSYMBOL_rel_expression = 55,            /* rel_expression  */
  YYSYMBOL_simple_expression = 56,         /* simple_expression  */
  YYSYMBOL_term = 57,                      /* term  */
  YYSYMBOL_unary_expression = 58,          /* unary_expression  */
  YYSYMBOL_factor = 59,                    /* factor  */
  YYSYMBOL_argument_list = 60,             /* argument_list  */
  YYSYMBOL_arguments = 61                  /* arguments  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
typedef yytype_int8 yy_state_t;

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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

#if 1

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
#endif /* 1 */

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
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   162

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  71
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  126

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   291


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

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
      35,    36
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    55,    55,    73,    81,    89,    96,   106,   114,   146,
     172,   177,   211,   251,   257,   277,   287,   306,   316,   315,
     341,   350,   360,   365,   376,   386,   397,   432,   472,   501,
     540,   547,   556,   563,   570,   577,   590,   601,   614,   625,
     647,   658,   663,   669,   676,   684,   690,   714,   777,   787,
     849,   859,   951,   961,  1030,  1039,  1163,  1173,  1471,  1490,
    1511,  1522,  1530,  1566,  1576,  1589,  1602,  1630,  1657,  1665,
    1669,  1679
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "CONST_INT",
  "CONST_FLOAT", "CONST_CHAR", "ADDOP", "MULOP", "LOGICOP", "RELOP", "ID",
  "IF", "ELSE", "FOR", "WHILE", "DO", "CONTINUE", "INT", "FLOAT", "CHAR",
  "DOUBLE", "VOID", "RETURN", "INCOP", "DECOP", "ASSIGNOP", "LPAREN",
  "RPAREN", "LCURL", "RCURL", "LTHIRD", "RTHIRD", "SEMICOLON", "COMMA",
  "NOT", "PRINTLN", "LOWER_THAN_ELSE", "$accept", "start", "program",
  "unit", "func_declaration", "func_definition", "parameter_list",
  "compound_statement", "$@1", "var_declaration", "type_specifier",
  "declaration_list", "statements", "statement", "expression_statement",
  "variable", "expression", "logic_expression", "rel_expression",
  "simple_expression", "term", "unary_expression", "factor",
  "argument_list", "arguments", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-73)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-3)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     108,   -73,   -73,   -73,   -73,    14,   121,   -73,   -73,   -73,
     -73,    15,   -73,   -73,   -13,    11,    29,   -73,    73,    21,
     -73,    69,   -73,    44,    27,    77,    33,     9,    63,   -73,
     -73,    54,    93,   -73,   -73,   104,   -73,   102,   -73,   -73,
      94,    86,   -73,   -73,   -73,    49,   101,    92,   106,   107,
      49,    49,   -73,    49,   109,   -73,   -73,    25,    67,   -73,
     -73,   120,   114,   -73,   132,    23,   134,   -73,   -73,   -73,
     -73,    74,   -73,    49,    49,    49,    17,    49,     8,   122,
     -73,   137,   118,   -73,   -73,   -73,   -73,    49,   -73,    49,
      49,    49,    49,   -73,   123,   119,   124,   126,    17,   127,
     -73,   -73,   -73,   129,   -73,   -73,   134,   145,   -73,   -73,
      49,   -73,   102,    49,   102,    16,   -73,   146,   130,   -73,
     -73,   -73,   102,   102,   -73,   -73
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    13,    23,    24,    25,     0,     0,     4,     6,     7,
       5,     0,     1,     3,     0,    28,     0,    22,     0,     0,
      21,     0,    10,     0,     0,    17,     0,    26,    18,     9,
      12,     0,     0,    16,    29,     0,    20,     0,     8,    11,
      15,     0,    45,    64,    65,     0,    46,     0,     0,     0,
       0,     0,    43,     0,     0,    34,    32,     0,     0,    30,
      33,    61,     0,    48,    50,    52,    54,    56,    60,    14,
      27,    61,    58,    69,     0,     0,     0,     0,     0,     0,
      59,     0,    28,    19,    31,    66,    67,     0,    44,     0,
       0,     0,     0,    71,     0,    68,     0,     0,     0,     0,
      42,    40,    63,     0,    49,    51,    55,    53,    57,    62,
       0,    47,     0,     0,     0,     0,    70,    36,     0,    38,
      41,    39,     0,     0,    37,    35
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -73,   -73,   -73,   153,   -73,   -73,   -73,   -18,   -73,    57,
       4,   -73,   -73,   -56,   -64,   -45,   -44,   -72,    71,    70,
      72,   -42,   -73,   -73,   -73
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     5,     6,     7,     8,     9,    24,    55,    37,    56,
      57,    16,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    94,    95
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      71,    93,    84,    72,    11,    30,    78,    79,    71,   100,
      11,    80,    98,    39,    12,   104,    14,   120,    42,    17,
      43,    44,    25,    45,    26,    15,    14,    46,    71,    90,
      96,    97,    91,    99,   113,    82,    40,    18,   116,    35,
     101,    19,    71,    51,    71,    71,    71,    71,   121,    52,
     108,    53,    43,    44,    31,    45,   117,    10,   119,    46,
      32,    20,    21,    10,    34,    71,   124,   125,    42,   118,
      43,    44,    28,    45,    22,    51,    29,    46,    47,    27,
      48,    49,    28,    53,     2,     3,    38,    33,     4,    50,
       2,     3,    36,    51,     4,    28,    83,    85,    86,    52,
      23,    53,    54,    42,    69,    43,    44,    41,    45,     1,
       2,     3,    46,    47,     4,    48,    49,    70,    75,     2,
       3,    -2,     1,     4,    50,     2,     3,    73,    51,     4,
      28,    74,    76,    77,    52,    81,    53,    54,     2,     3,
      89,    92,     4,    85,    86,    87,    88,   103,    19,   102,
     109,    90,   110,   112,   114,   111,   115,   123,   122,    13,
     105,   107,   106
};

static const yytype_int8 yycheck[] =
{
      45,    73,    58,    45,     0,    23,    50,    51,    53,     1,
       6,    53,    76,    31,     0,    87,     1,     1,     1,    32,
       3,     4,    18,     6,     3,    10,     1,    10,    73,     6,
      74,    75,     9,    77,    98,    10,    32,    26,   110,    30,
      32,    30,    87,    26,    89,    90,    91,    92,    32,    32,
      92,    34,     3,     4,    27,     6,   112,     0,   114,    10,
      33,    32,    33,     6,    31,   110,   122,   123,     1,   113,
       3,     4,    28,     6,     1,    26,    32,    10,    11,    10,
      13,    14,    28,    34,    17,    18,    32,    10,    21,    22,
      17,    18,    29,    26,    21,    28,    29,    23,    24,    32,
      27,    34,    35,     1,    10,     3,     4,     3,     6,     1,
      17,    18,    10,    11,    21,    13,    14,    31,    26,    17,
      18,     0,     1,    21,    22,    17,    18,    26,    26,    21,
      28,    30,    26,    26,    32,    26,    34,    35,    17,    18,
       8,     7,    21,    23,    24,    25,    32,    10,    30,    27,
      27,     6,    33,    27,    27,    31,    27,    27,    12,     6,
      89,    91,    90
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,    17,    18,    21,    38,    39,    40,    41,    42,
      46,    47,     0,    40,     1,    10,    48,    32,    26,    30,
      32,    33,     1,    27,    43,    47,     3,    10,    28,    32,
      44,    27,    33,    10,    31,    30,    29,    45,    32,    44,
      47,     3,     1,     3,     4,     6,    10,    11,    13,    14,
      22,    26,    32,    34,    35,    44,    46,    47,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    10,
      31,    52,    58,    26,    30,    26,    26,    26,    53,    53,
      58,    26,    10,    29,    50,    23,    24,    25,    32,     8,
       6,     9,     7,    54,    60,    61,    53,    53,    51,    53,
       1,    32,    27,    10,    54,    55,    57,    56,    58,    27,
      33,    31,    27,    51,    27,    27,    54,    50,    53,    50,
       1,    32,    12,    27,    50,    50
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    37,    38,    39,    39,    40,    40,    40,    41,    41,
      41,    42,    42,    42,    43,    43,    43,    43,    45,    44,
      44,    46,    46,    47,    47,    47,    48,    48,    48,    48,
      49,    49,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    51,    51,    51,    52,    52,    53,    53,
      54,    54,    55,    55,    56,    56,    57,    57,    58,    58,
      58,    59,    59,    59,    59,    59,    59,    59,    60,    60,
      61,    61
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     6,     5,
       4,     6,     5,     1,     4,     3,     2,     1,     0,     4,
       2,     3,     3,     1,     1,     1,     3,     6,     1,     4,
       1,     2,     1,     1,     1,     7,     5,     7,     5,     5,
       3,     5,     3,     1,     2,     1,     1,     4,     1,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     2,     2,
       1,     1,     4,     3,     1,     1,     2,     2,     1,     0,
       3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
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
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
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
# endif
#endif

#ifndef yytnamerr
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
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
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
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
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
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
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
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
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


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

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
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
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
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  case 2: /* start: program  */
#line 56 "2005018.y"
                {
            (yyval.symbVal) = new SymbolInfo("start", "grammar");
            (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[0].symbVal)->node->getfirstLine(),"start : program","NULL");
            (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node); 
			logfile << "start : program\n"; 
            
            logfile << "Total Lines: " << line_count << "\n"; 
            logfile << "Total Errors: " << err_sem << "\n"; 

            (yyval.symbVal)->node->printParseTree((yyval.symbVal)->node,0,parsefile); 
            InitiateASM(); 
            trav((yyval.symbVal)->node);
            ASM.close();
            Peephole_Optimization();
		}
#line 1650 "y.tab.c"
    break;

  case 3: /* program: program unit  */
#line 74 "2005018.y"
{ 
    (yyval.symbVal) = new SymbolInfo("program", "grammar");
    (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[-1].symbVal)->node->getfirstLine(),"program : program unit","NULL");
    (yyval.symbVal)->node->addChild((yyvsp[-1].symbVal)->node);
    (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node);
    logfile << "program : program unit\n"; 
}
#line 1662 "y.tab.c"
    break;

  case 4: /* program: unit  */
#line 82 "2005018.y"
{  
    (yyval.symbVal) = new SymbolInfo("program", "grammar");
    (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[0].symbVal)->node->getfirstLine(),"program : unit","NULL");
    (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node);
    logfile << "program : unit\n";
}
#line 1673 "y.tab.c"
    break;

  case 5: /* unit: var_declaration  */
#line 90 "2005018.y"
        {
            (yyval.symbVal) = new SymbolInfo("unit", "grammar"); 
            logfile << "unit  : var_declaration\n"; 
            (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[0].symbVal)->node->getfirstLine(),"unit  : var_declaration","NULL");
            (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node);   
        }
#line 1684 "y.tab.c"
    break;

  case 6: /* unit: func_declaration  */
#line 97 "2005018.y"
        {
            (yyval.symbVal) = new SymbolInfo("unit", "grammar"); 
            logfile << "unit : func_declaration\n";
            vector< treeNode* > vect = (yyval.symbVal)->node->getChildren(); 
            for(auto node: vect){
                 cout << node->getRule() << "\n";}  
            (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[0].symbVal)->node->getfirstLine(),"unit : func_declaration","NULL");
            (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node); 
        }
#line 1698 "y.tab.c"
    break;

  case 7: /* unit: func_definition  */
#line 107 "2005018.y"
        {
            (yyval.symbVal) = new SymbolInfo("unit", "grammar"); 
            logfile << "unit : func_definition\n";
            (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[0].symbVal)->node->getfirstLine(),"unit : func_definition","NULL");
            (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node);
        }
#line 1709 "y.tab.c"
    break;

  case 8: /* func_declaration: type_specifier ID LPAREN parameter_list RPAREN SEMICOLON  */
#line 115 "2005018.y"
                    {
                        (yyval.symbVal) = new SymbolInfo("func_declaration", "grammar"); 
                        (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[-5].symbVal)->node->getfirstLine(),"func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON","NULL");
                        (yyval.symbVal)->node->addChild((yyvsp[-5].symbVal)->node); 
                        (yyval.symbVal)->node->addChild((yyvsp[-4].symbVal)->node); 
                        (yyval.symbVal)->node->addChild((yyvsp[-3].symbVal)->node); 
                        (yyval.symbVal)->node->addChild((yyvsp[-2].symbVal)->node); 
                        (yyval.symbVal)->node->addChild((yyvsp[-1].symbVal)->node); 
                        (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node); 

                        logfile << "func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON\n";
                        string nameID = (yyvsp[-4].symbVal)->getname();
                        string IDtype = "FUNC";     
                        SymbolInfo *check = table.LookUp2(nameID,IDtype);
                        if(check){
                            errf << "Line# " << line_count << ": Function '"<< nameID <<"' already declared\n"; 
                            err_sem++; 
                            cout << "here\n"; 
                        }
                        else{
                            //This section is for ID which is of type 'FUNC. It has a vector that stores function argtypes. 
                            SymbolInfo *newSymb = new SymbolInfo(nameID,"ID");
                            newSymb->setIDType("FUNC");
                            newSymb->setFuncRet((yyvsp[-5].symbVal)->getVarType()); 
                            for(int i =0 ; i < function_arg_types.size(); ++i ){
                                newSymb->push_params(function_arg_types[i]); 
                            }
                            table.Insert(newSymb); 
                            function_arg_types.clear(); 
                        }
                    }
#line 1745 "y.tab.c"
    break;

  case 9: /* func_declaration: type_specifier ID LPAREN RPAREN SEMICOLON  */
#line 147 "2005018.y"
                    {
                        (yyval.symbVal) = new SymbolInfo("func_declaration", "grammar"); 
                        (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[-4].symbVal)->node->getfirstLine(),"func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON","NULL");
                        (yyval.symbVal)->node->addChild((yyvsp[-4].symbVal)->node); 
                        (yyval.symbVal)->node->addChild((yyvsp[-3].symbVal)->node); 
                        (yyval.symbVal)->node->addChild((yyvsp[-2].symbVal)->node); 
                        (yyval.symbVal)->node->addChild((yyvsp[-1].symbVal)->node); 
                        (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node); 
                        logfile << "func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON\n";
                        string nameID = (yyvsp[-3].symbVal)->getname();
                        string IDtype = "FUNC";     
                        SymbolInfo *check = table.LookUp2(nameID,IDtype);
                        if(check){
                            errf << "Line# " << line_count << ": Function '"<< nameID <<"' already declared\n"; 
                            err_sem++; 
                        }
                        else{
                            //This section is for ID which is of type 'FUNC. It has a vector that stores function argtypes. 
                            SymbolInfo *newSymb = new SymbolInfo(nameID,"ID");
                            newSymb->setIDType("FUNC");
                            newSymb->setFuncRet((yyvsp[-4].symbVal)->getVarType()); 
                            table.Insert(newSymb); 
                            function_arg_types.clear(); 
                        }
                    }
#line 1775 "y.tab.c"
    break;

  case 10: /* func_declaration: type_specifier ID LPAREN error  */
#line 173 "2005018.y"
                    {
                        errf << "Line# " << line_count << ": Syntax error at parameter list of function definition\n"; 
                    }
#line 1783 "y.tab.c"
    break;

  case 11: /* func_definition: type_specifier ID LPAREN parameter_list RPAREN compound_statement  */
#line 178 "2005018.y"
                {
                    (yyval.symbVal) = new SymbolInfo("func_definition", "grammar"); 
                    (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[-5].symbVal)->node->getfirstLine(),"func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement","NULL");
                    (yyval.symbVal)->node->addChild((yyvsp[-5].symbVal)->node); 
                    (yyval.symbVal)->node->addChild((yyvsp[-4].symbVal)->node);
                    (yyval.symbVal)->node->addChild((yyvsp[-3].symbVal)->node); 
                    (yyval.symbVal)->node->addChild((yyvsp[-2].symbVal)->node); 
                    (yyval.symbVal)->node->addChild((yyvsp[-1].symbVal)->node);
                    (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node);

                    logfile << "func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement\n";
                    string nameID = (yyvsp[-4].symbVal)->getname(), IDtype = "FUNC";
                    string typeOfFunc = (yyvsp[-5].symbVal)->getVarType();   

                    SymbolInfo *curr = table.LookUp2(nameID, IDtype); 
                    if(curr){
                        err_sem++; 
                        errf << "Line# "<<  line_count << " : Redefinition of function " << nameID << "\n" ;
                    }
                    else{
                        (yyvsp[-4].symbVal)->setFuncDefined(); 
                        (yyvsp[-4].symbVal)->setIDType("FUNC");
                        (yyvsp[-4].symbVal)->setFuncRet(typeOfFunc); 
                        for(int i =0; i <  function_arg_types.size(); ++i){
                            (yyvsp[-4].symbVal)->push_params(function_arg_types[i]);
                        }
                        table.Insert((yyvsp[-4].symbVal));
                        ////---------------------
                        (yyvsp[-4].symbVal)->node->_name = nameID;
                    } 
                    args_ID_cnt =0;
                    function_arg_types.clear(); 
                }
#line 1821 "y.tab.c"
    break;

  case 12: /* func_definition: type_specifier ID LPAREN RPAREN compound_statement  */
#line 212 "2005018.y"
                {
                    (yyval.symbVal) = new SymbolInfo("func_definition", "grammar"); 
                    (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[-4].symbVal)->node->getfirstLine(),"func_definition : type_specifier ID LPAREN RPAREN compound_statement","NULL");
                    (yyval.symbVal)->node->addChild((yyvsp[-4].symbVal)->node); 
                    (yyval.symbVal)->node->addChild((yyvsp[-3].symbVal)->node); 
                    (yyval.symbVal)->node->addChild((yyvsp[-2].symbVal)->node); 
                    (yyval.symbVal)->node->addChild((yyvsp[-1].symbVal)->node); 
                    (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node);
                    logfile << "func_definition : type_specifier ID LPAREN RPAREN compound_statement\n";
                    string nameID = (yyvsp[-3].symbVal)->getname(), IDtype = "FUNC";
                    string typeOfFunc = (yyvsp[-4].symbVal)->getVarType();   

                    SymbolInfo *curr = table.LookUp2(nameID, IDtype); 
                    if(curr){
                        if(curr->isFuncDefined()){
                            err_sem++; 
                            errf << "Line# "<<  line_count << ": Function '"<< nameID <<"'' already defined\n";
                        }
                        else if(curr->getFuncRet() != typeOfFunc){
                            err_sem++; 
                            cout << "Line# "<<  line_count << ": Function return type does not match declaration\n";
                        }
                        else if(curr->List_params.size() != function_arg_types.size()){
                            err_sem++; 
                            cout << "Line# " <<  line_count << "Function parameter list does not match declaration\n";
                        }
                    }
                    else{
                        SymbolInfo *newSymb = new SymbolInfo(nameID, "ID");
                        newSymb->setFuncDefined(); 
                        newSymb->setIDType("FUNC");
                        newSymb->setFuncRet(typeOfFunc); 
                        table.Insert(newSymb);
                        //------------ For ICG part 
                        (yyvsp[-3].symbVal)->node->_name = nameID; 
                    } 
                    args_ID_cnt =0;
                    function_arg_types.clear();
                }
#line 1865 "y.tab.c"
    break;

  case 13: /* func_definition: error  */
#line 252 "2005018.y"
                {
                    err_sem++; 
                    errf << "Line# " << line_count << " : Syntax error at parameter list of function definition\n"; 
                }
#line 1874 "y.tab.c"
    break;

  case 14: /* parameter_list: parameter_list COMMA type_specifier ID  */
#line 258 "2005018.y"
                {
                    (yyval.symbVal) = new SymbolInfo("parameter_list", "grammar"); 
                    (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[-3].symbVal)->node->getfirstLine(),"parameter_list : parameter_list COMMA type_specifier ID","NULL");
                    (yyval.symbVal)->node->addChild((yyvsp[-3].symbVal)->node); 
                    (yyval.symbVal)->node->addChild((yyvsp[-2].symbVal)->node); 
                    (yyval.symbVal)->node->addChild((yyvsp[-1].symbVal)->node); 
                    (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node); 
                    logfile << "parameter_list  : parameter_list COMMA type_specifier ID\n";
                    string nameID = (yyvsp[0].symbVal)->getname(); 
                    //This one is from $3
                    function_arg_types.pb(var_type);
                    args_ID_cnt++; 
                    //also from $3
                    (yyvsp[0].symbVal)->setVarType(var_type);
                    (yyvsp[0].symbVal)->setIDType("VAR");
                    params.push_back((yyvsp[0].symbVal));  
                    ////-----------------
                    (yyvsp[0].symbVal)->node->_name = nameID;                   
                }
#line 1898 "y.tab.c"
    break;

  case 15: /* parameter_list: parameter_list COMMA type_specifier  */
#line 278 "2005018.y"
                { 
                    (yyval.symbVal) = new SymbolInfo("parameter_list", "grammar");
                    (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[-2].symbVal)->node->getfirstLine(),"parameter_list : parameter_list COMMA type_specifier","NULL");
                    (yyval.symbVal)->node->addChild((yyvsp[-2].symbVal)->node); 
                    (yyval.symbVal)->node->addChild((yyvsp[-1].symbVal)->node); 
                    (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node); 
                    logfile << "parameter_list  : parameter_list COMMA type_specifier\n";
                    function_arg_types.pb((yyvsp[0].symbVal)->getVarType()); 
                }
#line 1912 "y.tab.c"
    break;

  case 16: /* parameter_list: type_specifier ID  */
#line 288 "2005018.y"
                {
                    (yyval.symbVal) = new SymbolInfo("parameter_list", "grammar");
                    (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[-1].symbVal)->node->getfirstLine(),"parameter_list : type_specifier ID","NULL");
                    (yyval.symbVal)->node->addChild((yyvsp[-1].symbVal)->node); 
                    (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node); 
                    logfile << "parameter_list  : type_specifier ID\n";
                    string nameID = (yyvsp[0].symbVal)->getname();
                    string IDtype = "VAR";  

                    function_arg_types.pb(var_type); 
                    args_ID_cnt++; 

                    params.push_back((yyvsp[0].symbVal));
                    (yyvsp[0].symbVal)->setIDType("VAR");//VAR,FUNC etc. 
                    (yyvsp[0].symbVal)->setVarType(var_type);//This is type of ID. 
                    ////-------------------
                    (yyvsp[0].symbVal)->node->_name = nameID;
                }
#line 1935 "y.tab.c"
    break;

  case 17: /* parameter_list: type_specifier  */
#line 307 "2005018.y"
                {
                    (yyval.symbVal) = new SymbolInfo("parameter_list", "grammar");
                    (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[0].symbVal)->node->getfirstLine(),"parameter_list : type_specifier","NULL");
                    (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node); 
                    logfile << "parameter_list  : type_specifier\n";
                    function_arg_types.pb(var_type);
                }
#line 1947 "y.tab.c"
    break;

  case 18: /* $@1: %empty  */
#line 316 "2005018.y"
                {
                    table.EnterScope(); 
                    int currOff= 2;
                    for(int i =params.size()-1; i >= 0; --i) 
                    {
                        currOff += 2;
                        table.Insert(params[i]);
                        /////------------------------------------
                        params[i]->node->stackOff = currOff;
                    }
                    params.clear(); 
                    //-------------------------------
                }
#line 1965 "y.tab.c"
    break;

  case 19: /* compound_statement: LCURL $@1 statements RCURL  */
#line 329 "2005018.y"
                {
                    logfile << "compound_statement : LCURL statements RCURL\n";
                    (yyval.symbVal) = new SymbolInfo("compound_statement", "grammar");
                    (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[-3].symbVal)->node->getfirstLine(),"compound_statement : LCURL statements RCURL","NULL");
                    (yyval.symbVal)->node->addChild((yyvsp[-3].symbVal)->node); 
                    (yyval.symbVal)->node->addChild((yyvsp[-1].symbVal)->node);
                    (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node);   
                    table.PrintAllScopeTables(logfile);
                    table.ExitScope(); 
                    ////--------
                       
                }
#line 1982 "y.tab.c"
    break;

  case 20: /* compound_statement: LCURL RCURL  */
#line 342 "2005018.y"
                {
                    (yyval.symbVal) = new SymbolInfo("compound_statement", "grammar");
                    (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[-1].symbVal)->node->getfirstLine(),"compound_statement : LCURL RCURL","NULL");
                    (yyval.symbVal)->node->addChild((yyvsp[-1].symbVal)->node); 
                    (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node);
                    logfile << "compound_statement : LCURL RCURL\n";
                }
#line 1994 "y.tab.c"
    break;

  case 21: /* var_declaration: type_specifier declaration_list SEMICOLON  */
#line 351 "2005018.y"
                { 
                    (yyval.symbVal) = new SymbolInfo("var_declaration","grammar"); 
                    (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[-2].symbVal)->node->getfirstLine(),"var_declaration : type_specifier declaration_list SEMICOLON","NULL");  
                    (yyval.symbVal)->node->addChild((yyvsp[-2].symbVal)->node);
                    (yyval.symbVal)->node->addChild((yyvsp[-1].symbVal)->node);
                    (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node);
                    logfile << "var_declaration : type_specifier declaration_list SEMICOLON\n";
                    ///-------------------------------------ICG
                }
#line 2008 "y.tab.c"
    break;

  case 22: /* var_declaration: type_specifier error SEMICOLON  */
#line 361 "2005018.y"
                {
                    errf << "Line# " << line_count << ": Syntax error at declaration list of variable declaration\n"; 
                }
#line 2016 "y.tab.c"
    break;

  case 23: /* type_specifier: INT  */
#line 366 "2005018.y"
                {
                    logfile << "type_specifier  : INT\n";
                    var_type = "INT";
                    SymbolInfo *symb = new SymbolInfo(var_type);
                    symb->node = new treeNode(line_count, line_count,"type_specifier  : INT","NULL");
                    (yyval.symbVal) = symb;
                    (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[0].symbVal)->node->getfirstLine(),"type_specifier : INT","NULL");
                    (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node); 
                    ///-------------------------ICG
                }
#line 2031 "y.tab.c"
    break;

  case 24: /* type_specifier: FLOAT  */
#line 377 "2005018.y"
                {
                    logfile << "type_specifier  : FLOAT\n";
                    var_type = "FLOAT";
                    SymbolInfo *symb = new SymbolInfo(var_type);
                    symb->node = new treeNode(line_count, line_count,"type_specifier  : FLOAT","NULL");
                    (yyval.symbVal) = symb;
                    (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[0].symbVal)->node->getfirstLine(),"type_specifier : FLOAT","NULL");
                    (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node); 
                }
#line 2045 "y.tab.c"
    break;

  case 25: /* type_specifier: VOID  */
#line 387 "2005018.y"
                {
                    logfile << "type_specifier  : VOID\n";
                    var_type = "VOID"; 
                    SymbolInfo *symb = new SymbolInfo(var_type);
                    symb->node = new treeNode(line_count, line_count,"type_specifier  : VOID","NULL");
                    (yyval.symbVal) = symb;
                    (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[0].symbVal)->node->getfirstLine(),"type_specifier : VOID","NULL");
                    (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node);
                }
#line 2059 "y.tab.c"
    break;

  case 26: /* declaration_list: declaration_list COMMA ID  */
#line 398 "2005018.y"
                {
                    (yyval.symbVal) = new SymbolInfo("declaration_list", "grammar");
                    (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[-2].symbVal)->node->getfirstLine(),"declaration_list : declaration_list COMMA ID","NULL");
                    (yyval.symbVal)->node->addChild((yyvsp[-2].symbVal)->node);
                    (yyval.symbVal)->node->addChild((yyvsp[-1].symbVal)->node);
                    (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node);
                    treeNode *comma_node = new treeNode(line_count, line_count, "COMMA","NULL");
                    logfile << "declaration_list : declaration_list COMMA ID\n"; 
                    string nameID = (yyvsp[0].symbVal)->getname();
                    string IDtype = "VAR"; 
                    if(var_type == "VOID"){
                        err_sem++; 
                        errf << "Line# " << line_count << ": variable cant be void\n"; 
                    }
                    else{
                        if( table.LookUp2(nameID,IDtype) ){
                            err_sem++;
                            errf << "Line# " << line_count << ": variable '" << nameID << "' already declared\n";
                        }
                        else{
                            SymbolInfo *varID = new SymbolInfo(nameID,(yyvsp[0].symbVal)->gettype()); 
                            varID->setIDType("VAR"); 
                            varID->setVarType(var_type); 
                            table.Insert(varID);
                            /////--------------------------ICG
                            (yyvsp[0].symbVal)->node->_name =varID->node->_name = (yyvsp[0].symbVal)->getname();
                            table.setStackOffTable(table.getCurrStackOffset()-2);
                            varID->node->stackOff = table.getStackOffset(); 
                            varID->node->is_global = (table.getCurrentID() == "1" ?  1:0);
                            (yyvsp[0].symbVal)->node->stackOff = varID->node->stackOff;
                            (yyvsp[0].symbVal)->node->is_global = varID->node->is_global;  
                        }
                    }
                }
#line 2098 "y.tab.c"
    break;

  case 27: /* declaration_list: declaration_list COMMA ID LTHIRD CONST_INT RTHIRD  */
#line 433 "2005018.y"
                {
                    (yyval.symbVal) = new SymbolInfo("declaration_list", "grammar");
                    (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[-5].symbVal)->node->getfirstLine(),"declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD","NULL");
                    (yyval.symbVal)->node->addChild((yyvsp[-5].symbVal)->node);
                    (yyval.symbVal)->node->addChild((yyvsp[-4].symbVal)->node);
                    (yyval.symbVal)->node->addChild((yyvsp[-3].symbVal)->node);
                    (yyval.symbVal)->node->addChild((yyvsp[-2].symbVal)->node);
                    (yyval.symbVal)->node->addChild((yyvsp[-1].symbVal)->node);
                    (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node);
                    logfile << "declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD\n";
                    string nameID = (yyvsp[-3].symbVal)->getname(), arr_sz_str = (yyvsp[-1].symbVal)->getname();  
                    if(var_type == "VOID"){
                        err_sem++; 
                        errf << "Line# " << line_count << ": array type cannot be void\n"; 
                    }
                    else{
                        int array_sz = stoi(arr_sz_str); 
                        SymbolInfo *arrID = new SymbolInfo(nameID,"ID"); 
                        arrID->setIDType("ARA"); 
                        arrID->setVarType(var_type); 
                        arrID->setArraySize(array_sz); 
                        if(var_type == "INT"){
                            for(int i = arrID->all_ints.size(); i < array_sz; ++i ) arrID->all_ints.pb(0);   
                        }
                        else if(var_type == "FLOAT"){
                            for(int i = arrID->all_floats.size() ; i < array_sz; ++i ) arrID->all_floats.pb(0);
                        }
                        table.Insert(arrID); 
                        /////--------------------------ICG
                        (yyvsp[-3].symbVal)->node->_name = arrID->node->_name = (yyvsp[-3].symbVal)->getname(); 
                        (yyvsp[-3].symbVal)->node->isArr.first = arrID->node->isArr.first = 1;
                        (yyvsp[-3].symbVal)->node->isArr.second = arrID->node->isArr.second = (yyvsp[-1].symbVal)->getname(); 
                        table.setStackOffTable(table.getCurrStackOffset()-2*array_sz);
                        arrID->node->stackOff = table.getStackOffset();
                        arrID->node->is_global = (table.getCurrentID() == "1" ?  1:0);
                        (yyvsp[-3].symbVal)->node->stackOff = arrID->node->stackOff;
                        (yyvsp[-3].symbVal)->node->is_global = arrID->node->is_global; 
                    }
                }
#line 2142 "y.tab.c"
    break;

  case 28: /* declaration_list: ID  */
#line 473 "2005018.y"
                {
                    (yyval.symbVal) = new SymbolInfo("declaration_list", "grammar");
                    (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[0].symbVal)->node->getfirstLine(),"declaration_list : ID","NULL");
                    (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node);
                    logfile << "declaration_list : ID\n";
                    string nameID = (yyvsp[0].symbVal)->getname(); 
                    string IDtype =  "VAR"; 
                    if( var_type ==  "VOID"){
                        err_sem++; 
                        errf << "Line# " << line_count << ": variable cant be void\n";
                    }
                    else{
                        SymbolInfo *varID = new SymbolInfo(nameID,(yyvsp[0].symbVal)->gettype()); 
                        varID->setIDType("VAR"); 
                        varID->setVarType(var_type); 
                        table.Insert(varID);
                        ////---------------------ICG
                        // cout << nameID << " : " << table.getStackOffset() << "\n"; 
                        table.setStackOffTable(table.getCurrStackOffset()-2);
                        varID->node->stackOff = table.getStackOffset(); 
                        // cout<< nameID<< " : " << table.getStackOffset() << "\n" ; 
                        varID->node->is_global = (table.getCurrentID() == "1" ?  1:0);
                        // cout << "here " << table.getCurrentID() << "\n"; 
                        (yyvsp[0].symbVal)->node->_name =varID->node->_name  = nameID;
                        (yyvsp[0].symbVal)->node->stackOff = varID->node->stackOff;
                        (yyvsp[0].symbVal)->node->is_global = varID->node->is_global;
                    } 
                }
#line 2175 "y.tab.c"
    break;

  case 29: /* declaration_list: ID LTHIRD CONST_INT RTHIRD  */
#line 502 "2005018.y"
                {
                    (yyval.symbVal) = new SymbolInfo("declaration_list", "grammar");
                    (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[-3].symbVal)->node->getfirstLine(),"declaration_list : ID LTHIRD CONST_INT RTHIRD","NULL");
                    (yyval.symbVal)->node->addChild((yyvsp[-3].symbVal)->node);
                    (yyval.symbVal)->node->addChild((yyvsp[-2].symbVal)->node);
                    (yyval.symbVal)->node->addChild((yyvsp[-1].symbVal)->node);
                    (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node);
                    logfile << "declaration_list : ID LTHIRD CONST_INT RTHIRD\n";
                    string nameID = (yyvsp[-3].symbVal)->getname(), arr_sz_str = (yyvsp[-1].symbVal)->getname();    
                    if(var_type == "VOID"){
                        err_sem++; 
                        errf << "Line# " << line_count << ": array type cannot be void\n";
                    }
                    else{
                        int array_sz = stoi(arr_sz_str); 
                        SymbolInfo *arrID = new SymbolInfo(nameID,(yyvsp[-1].symbVal)->gettype()); 
                        arrID->setIDType("ARA"); 
                        arrID->setVarType(var_type); 
                        arrID->setArraySize(array_sz); 
                        if(var_type == "INT"){
                            for(int i = arrID->all_ints.size(); i < array_sz; ++i ) arrID->all_ints.pb(0);  
                        }
                        else if(var_type == "FLOAT"){
                            for(int i = arrID->all_floats.size() ; i < array_sz; ++i ) arrID->all_floats.pb(0);
                        }
                        table.Insert(arrID); 
                        ////---------------------ICG
                        (yyvsp[-3].symbVal)->node->isArr.first = arrID->node->isArr.first = 1;
                        (yyvsp[-3].symbVal)->node->isArr.second = arrID->node->isArr.second = (yyvsp[-1].symbVal)->getname(); 
                        (yyvsp[-3].symbVal)->node->_name = arrID->node->_name  = (yyvsp[-3].symbVal)->getname(); 
                        table.setStackOffTable(table.getCurrStackOffset()-2*array_sz);
                        arrID->node->stackOff = table.getStackOffset();
                        arrID->node->is_global = (table.getCurrentID() == "1" ?  1:0);
                        (yyvsp[-3].symbVal)->node->stackOff = arrID->node->stackOff;
                        (yyvsp[-3].symbVal)->node->is_global = arrID->node->is_global;                         
                    }
                }
#line 2217 "y.tab.c"
    break;

  case 30: /* statements: statement  */
#line 541 "2005018.y"
            {
                (yyval.symbVal) = new SymbolInfo("statements", "grammar");
                (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[0].symbVal)->node->getfirstLine(),"statements : statement","NULL");
                (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node);
                logfile << "statements : statement\n";
            }
#line 2228 "y.tab.c"
    break;

  case 31: /* statements: statements statement  */
#line 548 "2005018.y"
            {
                (yyval.symbVal) = new SymbolInfo("statements", "grammar");
                (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[-1].symbVal)->node->getfirstLine(),"statements : statements statement","NULL");
                (yyval.symbVal)->node->addChild((yyvsp[-1].symbVal)->node);
                (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node);
                logfile << "statements : statements statement\n";
            }
#line 2240 "y.tab.c"
    break;

  case 32: /* statement: var_declaration  */
#line 557 "2005018.y"
            {
                (yyval.symbVal) = new SymbolInfo("statement", "grammar");
                (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[0].symbVal)->node->getfirstLine(),"statement : var_declaration","NULL");
                (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node);
                logfile << "statement : var declaration\n";
            }
#line 2251 "y.tab.c"
    break;

  case 33: /* statement: expression_statement  */
#line 564 "2005018.y"
            {
                (yyval.symbVal) = new SymbolInfo("statement", "grammar");
                (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[0].symbVal)->node->getfirstLine(),"statement : expression_statement","NULL");
                (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node);
                logfile << "statement : expression_satement\n";
            }
#line 2262 "y.tab.c"
    break;

  case 34: /* statement: compound_statement  */
#line 571 "2005018.y"
            {
                (yyval.symbVal) = new SymbolInfo("statement", "grammar");
                (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[0].symbVal)->node->getfirstLine(),"statement : compound_statement","NULL");
                (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node);
                logfile << "statement : compound_satement\n";
            }
#line 2273 "y.tab.c"
    break;

  case 35: /* statement: FOR LPAREN expression_statement expression_statement expression RPAREN statement  */
#line 578 "2005018.y"
            {
                (yyval.symbVal) = new SymbolInfo("statement", "grammar");
                (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[-6].symbVal)->node->getfirstLine(),"statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement","NULL");
                (yyval.symbVal)->node->addChild((yyvsp[-6].symbVal)->node);
                (yyval.symbVal)->node->addChild((yyvsp[-5].symbVal)->node);
                (yyval.symbVal)->node->addChild((yyvsp[-4].symbVal)->node);
                (yyval.symbVal)->node->addChild((yyvsp[-3].symbVal)->node);
                (yyval.symbVal)->node->addChild((yyvsp[-2].symbVal)->node);
                (yyval.symbVal)->node->addChild((yyvsp[-1].symbVal)->node);
                (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node);
                logfile << "statement : FOR LPAREN expression statement expression statement expression RPAREN statement\n";
            }
#line 2290 "y.tab.c"
    break;

  case 36: /* statement: IF LPAREN expression RPAREN statement  */
#line 591 "2005018.y"
            {
                (yyval.symbVal) = new SymbolInfo("statement", "grammar");
                (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[-4].symbVal)->node->getfirstLine(),"statement : IF LPAREN expression RPAREN statement","NULL");
                (yyval.symbVal)->node->addChild((yyvsp[-4].symbVal)->node);
                (yyval.symbVal)->node->addChild((yyvsp[-3].symbVal)->node);
                (yyval.symbVal)->node->addChild((yyvsp[-2].symbVal)->node);
                (yyval.symbVal)->node->addChild((yyvsp[-1].symbVal)->node);
                (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node);
                logfile << "statement : IF LPAREN expression RPAREN statement\n";
            }
#line 2305 "y.tab.c"
    break;

  case 37: /* statement: IF LPAREN expression RPAREN statement ELSE statement  */
#line 602 "2005018.y"
            {
                (yyval.symbVal) = new SymbolInfo("statement", "grammar");
                (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[-6].symbVal)->node->getfirstLine(),"statement : IF LPAREN expression RPAREN statement ELSE statement","NULL");
                (yyval.symbVal)->node->addChild((yyvsp[-6].symbVal)->node);
                (yyval.symbVal)->node->addChild((yyvsp[-5].symbVal)->node);
                (yyval.symbVal)->node->addChild((yyvsp[-4].symbVal)->node);
                (yyval.symbVal)->node->addChild((yyvsp[-3].symbVal)->node);
                (yyval.symbVal)->node->addChild((yyvsp[-2].symbVal)->node);
                (yyval.symbVal)->node->addChild((yyvsp[-1].symbVal)->node);
                (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node);
                logfile << "statement : IF LPAREN expression RPAREN statement ELSE statement\n";
            }
#line 2322 "y.tab.c"
    break;

  case 38: /* statement: WHILE LPAREN expression RPAREN statement  */
#line 615 "2005018.y"
            {
                (yyval.symbVal) = new SymbolInfo("statement", "grammar");
                (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[-4].symbVal)->node->getfirstLine(),"statement : WHILE LPAREN expression RPAREN statement","NULL");
                (yyval.symbVal)->node->addChild((yyvsp[-4].symbVal)->node);
                (yyval.symbVal)->node->addChild((yyvsp[-3].symbVal)->node);
                (yyval.symbVal)->node->addChild((yyvsp[-2].symbVal)->node);
                (yyval.symbVal)->node->addChild((yyvsp[-1].symbVal)->node);
                (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node);
                logfile << "statement : WHILE LPAREN expression RPAREN statement\n";
            }
#line 2337 "y.tab.c"
    break;

  case 39: /* statement: PRINTLN LPAREN ID RPAREN SEMICOLON  */
#line 626 "2005018.y"
            {
                (yyval.symbVal) = new SymbolInfo("statement", "grammar");
                (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[-4].symbVal)->node->getfirstLine(),"statement : PRINTLN LPAREN ID RPAREN SEMICOLON","NULL");
                (yyval.symbVal)->node->addChild((yyvsp[-4].symbVal)->node);
                (yyval.symbVal)->node->addChild((yyvsp[-3].symbVal)->node);
                (yyval.symbVal)->node->addChild((yyvsp[-2].symbVal)->node);
                (yyval.symbVal)->node->addChild((yyvsp[-1].symbVal)->node);
                (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node);
                logfile << "statement : PRINTLN LPAREN ID RPAREN SEMICOLON\n";
                ///---------------
                string name = (yyvsp[-2].symbVal)->getname(); 
                SymbolInfo* find = table.LookUp(name);
                // table.PrintAllScopeTables2();
                if(find)
                { 
                    // cout << name << " : " << find->node->stackOff << "\n"; 
                    (yyvsp[-2].symbVal)->node->_name = find->node->_name; 
                    (yyvsp[-2].symbVal)->node->is_global = find->node->is_global; 
                    (yyvsp[-2].symbVal)->node->stackOff = find->node->stackOff; 
                }
            }
#line 2363 "y.tab.c"
    break;

  case 40: /* statement: RETURN expression SEMICOLON  */
#line 648 "2005018.y"
            {
                (yyval.symbVal) = new SymbolInfo("statement", "grammar");
                (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[-2].symbVal)->node->getfirstLine(),"statement : RETURN expression SEMICOLON","NULL");
                (yyval.symbVal)->node->addChild((yyvsp[-2].symbVal)->node);
                (yyval.symbVal)->node->addChild((yyvsp[-1].symbVal)->node);
                (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node);
                logfile << "statement : RETURN expression SEMICOLON\n";
                ///------------------------------------------------
                ///need to somehow find func_name here.
            }
#line 2378 "y.tab.c"
    break;

  case 41: /* statement: PRINTLN LPAREN ID RPAREN error  */
#line 659 "2005018.y"
            {
                errf << "Line# " << line_count << ": semicolon missing\n"; 
                err_sem++; 
            }
#line 2387 "y.tab.c"
    break;

  case 42: /* statement: RETURN expression error  */
#line 664 "2005018.y"
            {
                err_sem++; 
                errf << "Line# " << line_count << ": semicolon missing\n";  
            }
#line 2396 "y.tab.c"
    break;

  case 43: /* expression_statement: SEMICOLON  */
#line 670 "2005018.y"
                {
                    (yyval.symbVal) = new SymbolInfo("expresion_statement", "grammar");
                    (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[0].symbVal)->node->getfirstLine(),"expression_statement : SEMICOLON","NULL");
                    (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node);
                    logfile << "expression_statement : SEMICOLON\n";
                }
#line 2407 "y.tab.c"
    break;

  case 44: /* expression_statement: expression SEMICOLON  */
#line 677 "2005018.y"
                {
                    (yyval.symbVal) = new SymbolInfo("expresion_statement", "grammar");
                    (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[-1].symbVal)->node->getfirstLine(),"expression_statement : expression SEMICOLON","NULL");
                    (yyval.symbVal)->node->addChild((yyvsp[-1].symbVal)->node);
                    (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node);
                    logfile << "expression_statement : expression SEMICOLON\n";
                }
#line 2419 "y.tab.c"
    break;

  case 45: /* expression_statement: error  */
#line 685 "2005018.y"
                {
                    err_sem++; 
                    errf << "Line# "<< line_count << ": Syntax error at expression of expression statement\n"; 
                }
#line 2428 "y.tab.c"
    break;

  case 46: /* variable: ID  */
#line 691 "2005018.y"
        {
            (yyval.symbVal) = new SymbolInfo("variable", "grammar");
            logfile << "variable : ID\n";
            string nameID = (yyvsp[0].symbVal)->getname();
            SymbolInfo *id = table.LookUp(nameID);
            treeNode *curr = (yyvsp[0].symbVal)->node; 
            if(id){ 
            }
            else{
                err_sem++; 
                errf << "Line# "<< line_count << ": Undeclared variable'" << nameID << "'\n";   
            }
            //will also take undeclared variable in the parse tree.
            (yyval.symbVal) = (yyvsp[0].symbVal); 
            (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[0].symbVal)->node->getfirstLine(),"variable : ID","NULL");
            (yyval.symbVal)->node->addChild(curr);
            ////---------------------------------
            if(id) {
                (yyval.symbVal)->node->_name = nameID; 
                (yyval.symbVal)->node->stackOff = id->node->stackOff;
                (yyval.symbVal)->node->is_global = id->node->is_global;
            }
        }
#line 2456 "y.tab.c"
    break;

  case 47: /* variable: ID LTHIRD expression RTHIRD  */
#line 715 "2005018.y"
        {
            logfile << "variable : ID LTHIRD expression RTHIRD\n";
            string nameID = (yyvsp[-3].symbVal)->getname(), IDtype = "ARA";  
            SymbolInfo *curr = table.LookUp2(nameID,IDtype); 
            if(curr){
                if(curr->getAraySize() <= (yyvsp[-1].symbVal)->all_ints[0]){
                    ///Array Index out of bounds error. 
                    err_sem++; 
                    errf << "Line# " << line_count << " : " << nameID << " array index out of bound\n";
                    (yyval.symbVal) = new SymbolInfo("Error_variable", "grammar");
                    (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[-3].symbVal)->node->getfirstLine(),"variable : ID LTHIRD expression RTHIRD","NULL");
                    (yyval.symbVal)->node->addChild((yyvsp[-3].symbVal)->node);
                    (yyval.symbVal)->node->addChild((yyvsp[-2].symbVal)->node);
                    (yyval.symbVal)->node->addChild((yyvsp[-1].symbVal)->node);
                    (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node); 
                }
                else if( (yyvsp[-1].symbVal)->getVarType() == "FLOAT"){
                    ///Float index error
                    err_sem++; 
                    errf << "Line# " << line_count << " : " << nameID << " array index cannot be float\n";
                    (yyval.symbVal) = new SymbolInfo("Error_variable", "grammar");
                    (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[-3].symbVal)->node->getfirstLine(),"variable : ID LTHIRD expression RTHIRD","NULL");
                    (yyval.symbVal)->node->addChild((yyvsp[-3].symbVal)->node);
                    (yyval.symbVal)->node->addChild((yyvsp[-2].symbVal)->node);
                    (yyval.symbVal)->node->addChild((yyvsp[-1].symbVal)->node);
                    (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node);
                }
                else {
                    curr->setArrayInd((yyvsp[-1].symbVal)->all_ints[0]);
                    if(curr->getVarType() == "INT"){
                        while( curr->all_ints.size() <= curr->getAraIndex()) curr->all_ints.pb(0); 
                     }
                    else if( curr->getVarType() == "FLOAT"){
                        while( curr->all_floats.size() <= curr->getAraIndex()) curr->all_floats.pb(0);
                    }
                    treeNode *curr = (yyvsp[-3].symbVal)->node; 
                    (yyval.symbVal) = (yyvsp[-3].symbVal);  
                    (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[-3].symbVal)->node->getfirstLine(),"variable : ID LTHIRD expression RTHIRD","NULL");
                    (yyval.symbVal)->node->addChild(curr);
                    (yyval.symbVal)->node->addChild((yyvsp[-2].symbVal)->node);
                    (yyval.symbVal)->node->addChild((yyvsp[-1].symbVal)->node);
                    (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node); 
                }
                ////----------I guess now its ok.
                (yyval.symbVal)->node->_name = curr->node->_name; 
                (yyval.symbVal)->node->stackOff = curr->node->stackOff;
                (yyval.symbVal)->node->is_global = curr->node->is_global;
                (yyval.symbVal)->node->isArr.first = 1;
                (yyval.symbVal)->node->isArr.second = curr->node->isArr.second; 
            } 
            else{
                err_sem++; 
                errf << "Line# " << line_count << " : variable " << nameID << " undeclared.\n";  
                (yyval.symbVal) = new SymbolInfo("Error_variable", "grammar");
                (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[-3].symbVal)->node->getfirstLine(),"variable : ID LTHIRD expression RTHIRD","NULL");
                (yyval.symbVal)->node->addChild((yyvsp[-3].symbVal)->node);
                (yyval.symbVal)->node->addChild((yyvsp[-2].symbVal)->node);
                (yyval.symbVal)->node->addChild((yyvsp[-1].symbVal)->node);
                (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node);
            }
        }
#line 2522 "y.tab.c"
    break;

  case 48: /* expression: logic_expression  */
#line 778 "2005018.y"
            {
                treeNode *curr = (yyvsp[0].symbVal)->node;
                logfile << "expression  : logic_expression\n";
                (yyvsp[0].symbVal)->all_floats.pb(0); 
                (yyvsp[0].symbVal)->all_ints.pb(0);
                (yyval.symbVal) = (yyvsp[0].symbVal); 
                (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[0].symbVal)->node->getfirstLine(),"expression : logic_expression","NULL");
                (yyval.symbVal)->node->addChild(curr);
            }
#line 2536 "y.tab.c"
    break;

  case 49: /* expression: variable ASSIGNOP logic_expression  */
#line 788 "2005018.y"
            {
                logfile << "expression  : variable ASSIGNOP logic_expression\n";
                treeNode *curr = (yyvsp[-2].symbVal)->node; 
                string varType = (yyvsp[-2].symbVal)->getVarType();
                string varType2 = (yyvsp[0].symbVal)->getVarType(); 
                string IDtype = (yyvsp[-2].symbVal)->getIDType();
                string IDtype2 = (yyvsp[0].symbVal)->getIDType();
                if(varType == "INT"){
                    (yyvsp[-2].symbVal)->all_ints.pb(0);
                    if(IDtype == "VAR"){
                        if(varType2 == "INT"){
                            if(IDtype2 == "VAR") (yyvsp[-2].symbVal)->all_ints[0] = (yyvsp[0].symbVal)->all_ints[0]; 
                            else (yyvsp[-2].symbVal)->all_ints[0] = (yyvsp[0].symbVal)->all_ints[ (yyvsp[0].symbVal)->getAraIndex() ];  
                        }
                        else{
                            errf << "Line# " << line_count <<" : warning: possible loss of data in assignment of FLOAT to INT\n"; 
                        }
                    }
                    else if(IDtype == "ARA"){
                        int ind = (yyvsp[-2].symbVal)->getAraIndex(); 
                        if(varType2 == "INT"){
                            if(IDtype2 == "VAR") (yyvsp[-2].symbVal)->all_ints[ind] = (yyvsp[0].symbVal)->all_ints[0]; 
                            else (yyvsp[-2].symbVal)->all_ints[ind] = (yyvsp[0].symbVal)->all_ints[ (yyvsp[0].symbVal)->getAraIndex() ];  
                        }
                        else{
                            errf << "Warning at line " << line_count <<" : Assigning float value to integer\n"; 
                        }
                    } 
                }
                else if(varType == "FLOAT"){
                    (yyvsp[-2].symbVal)->all_floats.pb(0);
                    if(IDtype == "VAR"){
                        if(varType2 == "FLOAT"){
                            if(IDtype2 == "VAR") (yyvsp[-2].symbVal)->all_floats[0] = (yyvsp[0].symbVal)->all_floats[0]; 
                            else (yyvsp[-2].symbVal)->all_floats[0] = (yyvsp[0].symbVal)->all_floats[ (yyvsp[0].symbVal)->getAraIndex() ];  
                        }
                        else{
                            errf << "Line# " << line_count <<" : Assigning integer value to float\n"; 
                        }
                    }
                    else if(IDtype == "ARA"){
                        int ind = (yyvsp[-2].symbVal)->getAraIndex(); 
                        if(varType2 == "FLOAT"){
                            if(IDtype2 == "VAR") 
                            {
                                (yyvsp[-2].symbVal)->all_floats[ind] = (yyvsp[0].symbVal)->all_floats[0];
                            } 
                            else (yyvsp[-2].symbVal)->all_floats[ind] = (yyvsp[0].symbVal)->all_floats[ (yyvsp[0].symbVal)->getAraIndex() ];  
                        }
                        else{
                            errf << "Warning at line " << line_count <<" : Assigning integer value to float\n"; 
                        }
                    } 
                }
                (yyval.symbVal) = (yyvsp[-2].symbVal);
                (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[-2].symbVal)->node->getfirstLine(),"expression : variable ASSIGNOP logic_expression","NULL");
                (yyval.symbVal)->node->addChild(curr);
                (yyval.symbVal)->node->addChild((yyvsp[-1].symbVal)->node);
                (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node);
            }
#line 2601 "y.tab.c"
    break;

  case 50: /* logic_expression: rel_expression  */
#line 850 "2005018.y"
                {
                    treeNode *curr = (yyvsp[0].symbVal)->node; 
                    logfile << "logic_expression : rel_expression\n";
					(yyvsp[0].symbVal)->all_ints.pb(0);
					(yyvsp[0].symbVal)->all_floats.pb(0);
                    (yyval.symbVal) = (yyvsp[0].symbVal); 
                    (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[0].symbVal)->node->getfirstLine(),"logic_expression : rel_expression","NULL");
                    (yyval.symbVal)->node->addChild(curr);
                }
#line 2615 "y.tab.c"
    break;

  case 51: /* logic_expression: rel_expression LOGICOP rel_expression  */
#line 860 "2005018.y"
                {
                    (yyval.symbVal) = new SymbolInfo("logic_expression", "grammar");
                    logfile << "logic_expression : rel_expression LOGICOP rel_expression\n";
                    SymbolInfo *curr = new SymbolInfo("INT");
                    string logicOp = (yyvsp[-1].symbVal)->getname(); 
                    string first_var = (yyvsp[-2].symbVal)->getVarType(), second_var = (yyvsp[0].symbVal)->getVarType();
                    if(logicOp == "&&"){
                        if(first_var == "FLOAT"){
                            (yyvsp[-2].symbVal)->all_floats.pb(0);
                            if((yyvsp[-2].symbVal)->all_floats[0] == 0){
                                curr->all_ints[0] = 0; 
                            }
                            else{
                                if(second_var == "INT"){
                                    (yyvsp[0].symbVal)->all_ints.pb(0); 
                                    if((yyvsp[0].symbVal)->all_ints[0] == 0) curr->all_ints[0] = 0; 
                                    else curr->all_ints[0] = 1;
                                } 
                                else{
                                    (yyvsp[0].symbVal)->all_floats.pb(0); 
                                    if((yyvsp[0].symbVal)->all_floats[0] == 0) curr->all_ints[0] = 0; 
                                    else curr->all_ints[0]  = 1; 
                                }
                            }
                        }
                        else if(first_var == "INT"){
                            (yyvsp[-2].symbVal)->all_ints.pb(0);
                            if((yyvsp[-2].symbVal)->all_ints[0] == 0){
                                curr->all_ints[0] = 0; 
                            }
                            else{
                                if(second_var == "INT"){
                                    (yyvsp[0].symbVal)->all_ints.pb(0); 
                                    if((yyvsp[0].symbVal)->all_ints[0] == 0) curr->all_ints[0] = 0; 
                                    else curr->all_ints[0] = 1;
                                } 
                                else{
                                    (yyvsp[0].symbVal)->all_floats.pb(0); 
                                    if((yyvsp[0].symbVal)->all_floats[0] == 0) curr->all_ints[0] = 0; 
                                    else curr->all_ints[0]  = 1; 
                                }
                            }
                        }
                    } 
                    else if( logicOp == "||"){
                        if(first_var == "FLOAT"){
                            (yyvsp[-2].symbVal)->all_floats.pb(0);
                            if((yyvsp[-2].symbVal)->all_floats[0] != 0){
                                curr->all_ints[0] = 1; 
                            }
                            else{
                                if(second_var == "INT"){
                                    (yyvsp[0].symbVal)->all_ints.pb(0); 
                                    if((yyvsp[0].symbVal)->all_ints[0] != 0) curr->all_ints[0] = 1; 
                                    else curr->all_ints[0] = 0;
                                } 
                                else{
                                    (yyvsp[0].symbVal)->all_floats.pb(0); 
                                    if((yyvsp[0].symbVal)->all_floats[0] != 0) curr->all_ints[0] = 1; 
                                    else curr->all_ints[0]  = 0; 
                                }
                            }
                        }
                        else if(first_var == "INT"){
                            (yyvsp[-2].symbVal)->all_ints.pb(0);
                            if((yyvsp[-2].symbVal)->all_ints[0] != 0){
                                curr->all_ints[0] = 1; 
                            }
                            else{
                                if(second_var == "INT"){
                                    (yyvsp[0].symbVal)->all_ints.pb(0); 
                                    if((yyvsp[0].symbVal)->all_ints[0] != 0) curr->all_ints[0] = 1; 
                                    else curr->all_ints[0] = 0;
                                } 
                                else{
                                    (yyvsp[0].symbVal)->all_floats.pb(0); 
                                    if((yyvsp[0].symbVal)->all_floats[0] != 0) curr->all_ints[0] = 1; 
                                    else curr->all_ints[0]  = 0; 
                                }
                            }
                        }
                    }
                    (yyval.symbVal) = curr; 
                    (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[-2].symbVal)->node->getfirstLine(),"logic_expression : rel_expression LOGICOP rel_expression","NULL");
                    (yyval.symbVal)->node->addChild((yyvsp[-2].symbVal)->node);
                    (yyval.symbVal)->node->addChild((yyvsp[-1].symbVal)->node);
                    (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node);
                    ////------------------------
                    (yyvsp[-1].symbVal)->node->_name = logicOp; 
                }
#line 2710 "y.tab.c"
    break;

  case 52: /* rel_expression: simple_expression  */
#line 952 "2005018.y"
                {
                    logfile << "rel_expression  : simple_expression\n";
                    treeNode* curr = (yyvsp[0].symbVal)->node; 
                    (yyvsp[0].symbVal)->all_floats.pb(0);
                    (yyvsp[0].symbVal)->all_ints.pb(0); 
                    (yyval.symbVal) = (yyvsp[0].symbVal);
                    (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[0].symbVal)->node->getfirstLine(),"rel_expression : simple_expression","NULL");
                    (yyval.symbVal)->node->addChild(curr);
                }
#line 2724 "y.tab.c"
    break;

  case 53: /* rel_expression: simple_expression RELOP simple_expression  */
#line 962 "2005018.y"
                {
                    logfile << "rel_expression : simple_expression RELOP simple_expression\n";
                    SymbolInfo *curr = new SymbolInfo("INT"); 
                    string varType1 = (yyvsp[-2].symbVal)->getVarType(), varType2 = (yyvsp[0].symbVal)->getVarType(); 
                    string relOp = (yyvsp[-1].symbVal)->getname(); 
                        if(relOp == "=="){
                            if(varType1 != varType2){
                                errf << "Line# " << line_count << " : type mismatch\n";
                            }
                            else{
                                if( varType1 == "FLOAT") curr->all_ints[0] = (  (yyvsp[-2].symbVal)->all_floats[0] == (yyvsp[0].symbVal)->all_floats[0] ? 1: 0 );
                                else curr->all_ints[0] = (  (yyvsp[-2].symbVal)->all_ints[0] == (yyvsp[0].symbVal)->all_ints[0] ? 1: 0 );
                            }
                        }
                        else if(relOp == "!="){
                            if(varType1 != varType2){
                                errf << "Line# " << line_count << " : type mismatch\n";
                            }
                            else{
                                if( varType1 == "FLOAT") curr->all_ints[0] = (  (yyvsp[-2].symbVal)->all_floats[0] != (yyvsp[0].symbVal)->all_floats[0] ? 1: 0 );
                                else curr->all_ints[0] = (  (yyvsp[-2].symbVal)->all_ints[0] != (yyvsp[0].symbVal)->all_ints[0] ? 1: 0 );
                            }
                        }
                        else if(relOp == ">"){
                            if(varType1 != varType2){
                                errf << "Line# " << line_count << " : type mismatch\n";
                            }
                            else{
                                if( varType1 == "FLOAT") curr->all_ints[0] = (  (yyvsp[-2].symbVal)->all_floats[0] > (yyvsp[0].symbVal)->all_floats[0] ? 1: 0 );
                                else curr->all_ints[0] = (  (yyvsp[-2].symbVal)->all_ints[0] > (yyvsp[0].symbVal)->all_ints[0] ? 1: 0 );
                            }
                        }   
                        else if(relOp == "<"){
                            if(varType1 != varType2){
                                errf << "Line# " << line_count << " : type mismatch\n";
                            }
                            else{
                                if( varType1 == "FLOAT") curr->all_ints[0] = (  (yyvsp[-2].symbVal)->all_floats[0] < (yyvsp[0].symbVal)->all_floats[0] ? 1: 0 );
                                else curr->all_ints[0] = (  (yyvsp[-2].symbVal)->all_ints[0] < (yyvsp[0].symbVal)->all_ints[0] ? 1: 0 );
                            }
                        }
                        else if(relOp == ">="){
                            if(varType1 != varType2){
                                errf << "Line# " << line_count << " : type mismatch\n";
                            }
                            else{
                                if( varType1 == "FLOAT") curr->all_ints[0] = (  (yyvsp[-2].symbVal)->all_floats[0] >= (yyvsp[0].symbVal)->all_floats[0] ? 1: 0 );
                                else curr->all_ints[0] = (  (yyvsp[-2].symbVal)->all_ints[0] >= (yyvsp[0].symbVal)->all_ints[0] ? 1: 0 );
                            }
                        }
                        else if(relOp == "<="){
                            if(varType1 != varType2){
                                errf << "Line# " << line_count << " : type mismatch\n";
                            }
                            else{
                                if( varType1 == "FLOAT") curr->all_ints[0] = (  (yyvsp[-2].symbVal)->all_floats[0] <= (yyvsp[0].symbVal)->all_floats[0] ? 1: 0 );
                                else curr->all_ints[0] = (  (yyvsp[-2].symbVal)->all_ints[0] <= (yyvsp[0].symbVal)->all_ints[0] ? 1: 0 );
                            }
                        }
                        (yyval.symbVal) = curr; 
                        (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[-2].symbVal)->node->getfirstLine(),"rel_expression : simple_expression RELOP simple_expression","NULL");
                        (yyval.symbVal)->node->addChild((yyvsp[-2].symbVal)->node);
                        (yyval.symbVal)->node->addChild((yyvsp[-1].symbVal)->node);
                        (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node);
                        ///------------
                        (yyvsp[-1].symbVal)->node->_name = relOp;
                }
#line 2796 "y.tab.c"
    break;

  case 54: /* simple_expression: term  */
#line 1031 "2005018.y"
                {
                    treeNode *curr = (yyvsp[0].symbVal)->node; 
                    logfile << "simple_expression : term\n"; 
                    (yyvsp[0].symbVal)->all_ints.pb(0); (yyvsp[0].symbVal)->all_floats.pb(0);
                    (yyval.symbVal) = (yyvsp[0].symbVal);
                    (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[0].symbVal)->node->getfirstLine(),"simple_expression : term","NULL");
                    (yyval.symbVal)->node->addChild(curr);
                }
#line 2809 "y.tab.c"
    break;

  case 55: /* simple_expression: simple_expression ADDOP term  */
#line 1040 "2005018.y"
                {
                    string addop = (yyvsp[-1].symbVal)->getname(); 
                    logfile << "simple_expression : simple_expression ADDOP term\n";
                    string ID1 = (yyvsp[-2].symbVal)->getIDType(), ID2 = (yyvsp[0].symbVal)->getIDType();  
                    string var_1 = (yyvsp[-2].symbVal)->getVarType(), var_2 = (yyvsp[0].symbVal)->getVarType(); 
                    SymbolInfo *curr = new SymbolInfo("INT"); //will change accordingly. 
                    if(addop == "+"){
                        if(ID1 == "VAR"){
                        if(ID2 == "VAR"){
                            if(var_1 == "FLOAT"){
                                curr->setVarType("FLOAT"); 
                                curr->all_floats[0] = (yyvsp[-2].symbVal)->all_floats[0] + (  var_2 == "INT" ? (yyvsp[0].symbVal)->all_ints[0] : (yyvsp[0].symbVal)->all_floats[0]); 
                            }
                            else if(var_2 == "FLOAT"){
                                curr->setVarType("FLOAT");
                                curr->all_floats[0] = (yyvsp[0].symbVal)->all_floats[0] + (  var_1 == "INT" ? (yyvsp[-2].symbVal)->all_ints[0]: (yyvsp[-2].symbVal)->all_floats[0]);
                            }
                            else curr->all_ints[0] = (yyvsp[0].symbVal)->all_ints[0] + (yyvsp[-2].symbVal)->all_ints[0]; 
                        }
                        else if(ID2 == "ARA"){
                            int ind2 = (yyvsp[0].symbVal)->getAraIndex(); 
                            if(var_1 == "FLOAT"){
                                curr->setVarType("FLOAT"); 
                                curr->all_floats[0] = (yyvsp[-2].symbVal)->all_floats[0] + (  var_2 == "INT" ? (yyvsp[0].symbVal)->all_ints[ind2] : (yyvsp[0].symbVal)->all_floats[ind2]); 
                            }
                            else if(var_2 == "FLOAT"){
                                curr->setVarType("FLOAT");
                                curr->all_floats[0] = (yyvsp[0].symbVal)->all_floats[ind2] + (  var_1 == "INT" ? (yyvsp[-2].symbVal)->all_ints[0] : (yyvsp[-2].symbVal)->all_floats[0]);
                            }
                            else curr->all_ints[0] = (yyvsp[0].symbVal)->all_ints[ind2] + (yyvsp[-2].symbVal)->all_ints[0];
                        }
                    }
                    else if(ID1 == "ARA"){ 
                        int ind = (yyvsp[-2].symbVal)->getAraIndex();
                        if(ID2 == "VAR"){
                            if(var_1 == "FLOAT"){
                                curr->setVarType("FLOAT"); 
                                curr->all_floats[0] = (yyvsp[-2].symbVal)->all_floats[ind] + (  var_2 == "INT" ? (yyvsp[0].symbVal)->all_ints[0] : (yyvsp[0].symbVal)->all_floats[0]); 
                            }
                            else if(var_2 == "FLOAT"){
                                curr->setVarType("FLOAT");
                                curr->all_floats[0] = (yyvsp[0].symbVal)->all_floats[0] + (  var_1 == "INT" ? (yyvsp[-2].symbVal)->all_ints[ind] : (yyvsp[-2].symbVal)->all_floats[ind]);
                                }
                            else {
                                curr->all_ints[0] = (yyvsp[0].symbVal)->all_ints[0] + (yyvsp[-2].symbVal)->all_ints[ind];   
                            } 
                            }
                            else if(ID2 == "ARA"){
                                int ind2 = (yyvsp[0].symbVal)->getAraIndex(); 
                                if(var_1 == "FLOAT"){
                                curr->setVarType("FLOAT"); 
                                curr->all_floats[0] = (yyvsp[-2].symbVal)->all_floats[ind] + (  var_2 == "INT" ? (yyvsp[0].symbVal)->all_ints[ind2] : (yyvsp[0].symbVal)->all_floats[ind2]); 
                                }
                            else if(var_2 == "FLOAT"){
                                curr->setVarType("FLOAT");
                                curr->all_floats[0] = (yyvsp[0].symbVal)->all_floats[ind2] + (  var_1 == "INT" ? (yyvsp[-2].symbVal)->all_ints[ind] : (yyvsp[-2].symbVal)->all_floats[ind]);
                            }
                            else curr->all_ints[0] = (yyvsp[0].symbVal)->all_ints[ind2] + (yyvsp[-2].symbVal)->all_ints[ind];
                            }
                        }   
                    }
                    else if(addop == "-"){
                        if(ID1 == "VAR"){
                        if(ID2 == "VAR"){
                            if(var_1 == "FLOAT"){
                                curr->setVarType("FLOAT"); 
                                curr->all_floats[0] = (yyvsp[-2].symbVal)->all_floats[0] - (  var_2 == "INT" ? (yyvsp[0].symbVal)->all_ints[0] : (yyvsp[0].symbVal)->all_floats[0]); 
                            }
                            else if(var_2 == "FLOAT"){
                                curr->setVarType("FLOAT");
                                curr->all_floats[0] = (yyvsp[0].symbVal)->all_floats[0] - (  var_1 == "INT" ? (yyvsp[-2].symbVal)->all_ints[0]: (yyvsp[-2].symbVal)->all_floats[0]);
                            }
                            else curr->all_ints[0] = (yyvsp[0].symbVal)->all_ints[0] - (yyvsp[-2].symbVal)->all_ints[0]; 
                        }
                        else if(ID2 == "ARA"){
                            int ind2 = (yyvsp[0].symbVal)->getAraIndex(); 
                            if(var_1 == "FLOAT"){
                                curr->setVarType("FLOAT"); 
                                curr->all_floats[0] = (yyvsp[-2].symbVal)->all_floats[0] - (  var_2 == "INT" ? (yyvsp[0].symbVal)->all_ints[ind2] : (yyvsp[0].symbVal)->all_floats[ind2]); 
                            }
                            else if(var_2 == "FLOAT"){
                                curr->setVarType("FLOAT");
                                curr->all_floats[0] = (yyvsp[0].symbVal)->all_floats[ind2] - (  var_1 == "INT" ? (yyvsp[-2].symbVal)->all_ints[0] : (yyvsp[-2].symbVal)->all_floats[0]);
                            }
                            else curr->all_ints[0] = (yyvsp[0].symbVal)->all_ints[ind2] - (yyvsp[-2].symbVal)->all_ints[0];
                        }
                    }
                    else if(ID1 == "ARA"){
                        int ind = (yyvsp[-2].symbVal)->getAraIndex();
                        if(ID2 == "VAR"){
                            if(var_1 == "FLOAT"){
                                curr->setVarType("FLOAT"); 
                                curr->all_floats[0] = (yyvsp[-2].symbVal)->all_floats[ind] - (  var_2 == "INT" ? (yyvsp[0].symbVal)->all_ints[0] : (yyvsp[0].symbVal)->all_floats[0]); 
                            }
                            else if(var_2 == "FLOAT"){
                                curr->setVarType("FLOAT");
                                curr->all_floats[0] = (yyvsp[0].symbVal)->all_floats[0] - (  var_1 == "INT" ? (yyvsp[-2].symbVal)->all_ints[ind] : (yyvsp[-2].symbVal)->all_floats[ind]);
                                }
                            else curr->all_ints[0] = (yyvsp[0].symbVal)->all_ints[0]- (yyvsp[-2].symbVal)->all_ints[ind]; 
                            }
                            else if(ID2 == "ARA"){
                                int ind2 = (yyvsp[0].symbVal)->getAraIndex(); 
                                if(var_1 == "FLOAT"){
                                curr->setVarType("FLOAT"); 
                                curr->all_floats[0] = (yyvsp[-2].symbVal)->all_floats[ind] - (  var_2 == "INT" ? (yyvsp[0].symbVal)->all_ints[ind2] : (yyvsp[0].symbVal)->all_floats[ind2]); 
                                }
                            else if(var_2 == "FLOAT"){
                                curr->setVarType("FLOAT");
                                curr->all_floats[0] = (yyvsp[0].symbVal)->all_floats[ind2] - (  var_1 == "INT" ? (yyvsp[-2].symbVal)->all_ints[ind] : (yyvsp[-2].symbVal)->all_floats[ind]);
                            }
                            else curr->all_ints[0] = (yyvsp[0].symbVal)->all_ints[ind2] - (yyvsp[-2].symbVal)->all_ints[ind];
                            }
                        }
                    }
                    (yyval.symbVal) = curr; 
                    (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[-2].symbVal)->node->getfirstLine(),"simple_expression : simple_expression ADDOP term","NULL");
                    (yyval.symbVal)->node->addChild((yyvsp[-2].symbVal)->node);
                    (yyval.symbVal)->node->addChild((yyvsp[-1].symbVal)->node);
                    (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node);
                    ////--------------
                    (yyvsp[-1].symbVal)->node->_name = (yyvsp[-1].symbVal)->getname(); 
                }
#line 2936 "y.tab.c"
    break;

  case 56: /* term: unary_expression  */
#line 1164 "2005018.y"
                {
                    logfile << "term :  unary_expression\n"; 
                    treeNode *curr = (yyvsp[0].symbVal)->node; 
                    (yyvsp[0].symbVal)->all_ints.pb(0); 
                    (yyvsp[0].symbVal)->all_floats.pb(0);
                    (yyval.symbVal) = (yyvsp[0].symbVal); 
                    (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[0].symbVal)->node->getfirstLine(),"term : unary_expression","NULL");
                    (yyval.symbVal)->node->addChild(curr);
                }
#line 2950 "y.tab.c"
    break;

  case 57: /* term: term MULOP unary_expression  */
#line 1174 "2005018.y"
                {
                    logfile << "term : term MULOP unary_expression\n";
                    string mulop_type = (yyvsp[-1].symbVal)->getname();
                    string first_T = (yyvsp[-2].symbVal)->getIDType(), second_T  = (yyvsp[0].symbVal)->getIDType(); 
                    string first_var = (yyvsp[-2].symbVal)->getVarType(), second_var = (yyvsp[0].symbVal)->getVarType();     
                    string final_var = "";                  
                    SymbolInfo *curr = new SymbolInfo("INT"); ///random type. will change later.
                    curr->all_floats.pb(0); 
                    curr->all_ints.pb(0);  
                    if(mulop_type == "*"){
                        if(first_T == "VAR"){
                            if( second_T == "VAR"){
                                if(first_var == "FLOAT"){
                                    final_var = "FLOAT";  
                                    if(second_var == "INT") {   curr->all_floats[0] = (yyvsp[-2].symbVal)->all_floats[0] * (yyvsp[0].symbVal)->all_ints[0]; } 
                                    else curr->all_floats[0] = (yyvsp[-2].symbVal)->all_floats[0] * (yyvsp[0].symbVal)->all_floats[0];  
                                }
                                else{
                                    if(second_var == "FLOAT"){
                                        final_var = "FLOAT";  
                                        curr->all_floats[0] = (yyvsp[-2].symbVal)->all_ints[0] * (yyvsp[0].symbVal)->all_floats[0];
                                    }
                                    else{
                                        final_var = "INT";  
                                        curr->all_ints[0] = (yyvsp[-2].symbVal)->all_ints[0] * (yyvsp[0].symbVal)->all_ints[0]; 
                                    }
                                }
                            }
                            else if( second_T == "ARA"){
                                int ind2 = (yyvsp[0].symbVal)->getAraIndex(); 
                                if(first_var == "FLOAT"){
                                    final_var = "FLOAT";  
                                    if(second_var == "INT") curr->all_floats[0] = (yyvsp[-2].symbVal)->all_floats[0] * (yyvsp[0].symbVal)->all_ints[ind2]; 
                                    else curr->all_floats[0] = (yyvsp[-2].symbVal)->all_floats[0] * (yyvsp[0].symbVal)->all_floats[ind2];
                                }
                                else{
                                    if(second_var == "FLOAT"){
                                        final_var = "FLOAT"; 
                                        curr->all_floats[0] = (yyvsp[-2].symbVal)->all_ints[0] * (yyvsp[0].symbVal)->all_floats[ind2];
                                    }
                                    else{
                                        final_var = "INT" ; \
                                        curr->all_ints[0] = (yyvsp[-2].symbVal)->all_ints[0] * (yyvsp[0].symbVal)->all_ints[ind2];
                                    }
                                }
                            }
                        }
                        else if( first_T == "ARA"){
                            int ind1 = (yyvsp[-2].symbVal)->getAraIndex();
                            if( second_T == "VAR"){ 
                                if(first_var == "FLOAT"){
                                    final_var = "FLOAT";  
                                    if(second_var == "INT") curr->all_floats[0] = (yyvsp[-2].symbVal)->all_floats[ind1] * (yyvsp[0].symbVal)->all_ints[0]; 
                                    else curr->all_floats[0] = (yyvsp[-2].symbVal)->all_floats[ind1] * (yyvsp[0].symbVal)->all_floats[0];
                                }
                                else{
                                    if(second_var == "FLOAT"){
                                        final_var = "FLOAT";  
                                        curr->all_floats[0] = (yyvsp[-2].symbVal)->all_ints[ind1] * (yyvsp[0].symbVal)->all_floats[0];
                                    }
                                    else{
                                        final_var = "INT";  
                                        curr->all_ints[0] = (yyvsp[-2].symbVal)->all_ints[ind1] * (yyvsp[0].symbVal)->all_ints[0];
                                    }
                                }
                            }
                            else if( second_T == "ARA"){
                                int ind2 = (yyvsp[0].symbVal)->getAraIndex(); 
                                if(first_var == "FLOAT"){
                                    final_var = "FLOAT";  
                                    if(second_var == "INT") curr->all_floats[0] = (yyvsp[-2].symbVal)->all_floats[ind1] * (yyvsp[0].symbVal)->all_ints[ind2]; 
                                    else curr->all_floats[0] = (yyvsp[-2].symbVal)->all_floats[ind1] * (yyvsp[0].symbVal)->all_floats[ind2];
                                }
                                else{
                                    if(second_var == "FLOAT"){
                                        final_var = "FLOAT";  
                                        curr->all_floats[0] = (yyvsp[-2].symbVal)->all_ints[ind1] * (yyvsp[0].symbVal)->all_floats[ind2];
                                    }
                                    else{
                                        final_var = "INT";  
                                        curr->all_ints[0] = (yyvsp[-2].symbVal)->all_ints[ind1] * (yyvsp[0].symbVal)->all_ints[ind2];
                                    }
                                }
                            }
                        }
                    }
                    else if(mulop_type == "/"){
                        if(first_T == "VAR"){
                            if( second_T == "VAR"){
                                if(first_var == "FLOAT"){
                                    final_var = "FLOAT";  
                                    if(second_var == "INT") {
                                        if((yyvsp[0].symbVal)->all_ints[0] == 0){
                                            err_sem++; 
                                            errf << "Line# " << line_count << " : Divide by zero\n"; 
                                            curr->all_floats[0] = numeric_limits<float>::infinity(); 
                                        }
                                        else curr->all_floats[0] = (yyvsp[-2].symbVal)->all_floats[0] / (yyvsp[0].symbVal)->all_ints[0];
                                    } 
                                    else {
                                        if((yyvsp[0].symbVal)->all_floats[0] == 0 ){
                                            err_sem++; 
                                            errf << "Line# " << line_count << ": Warning: Division by zero\n";  
                                            curr->all_floats[0] = numeric_limits<float>::infinity();
                                        }
                                        else curr->all_floats[0] = (yyvsp[-2].symbVal)->all_floats[0] / (yyvsp[0].symbVal)->all_floats[0];
                                    }
                                }
                                else{
                                    if(second_var == "FLOAT"){
                                        final_var = "FLOAT";  
                                        if((yyvsp[0].symbVal)->all_floats[0] == 0){
                                            err_sem++; 
                                            errf << "Line# " << line_count << ": Warning: Division by zero\n";
                                            curr->all_floats[0] = numeric_limits<float>::infinity();
                                        }
                                        else curr->all_floats[0] = (yyvsp[-2].symbVal)->all_ints[0] / (yyvsp[0].symbVal)->all_floats[0];
                                    }
                                    else{
                                        final_var = "INT"; 
                                        if((yyvsp[0].symbVal)->all_ints[0] == 0){
                                            err_sem++; 
                                            errf << "Line# " << line_count << ": Warning: Division by zero\n"; 
                                            curr->all_ints[0] = numeric_limits<int>::infinity();
                                        }
                                        else curr->all_ints[0] = (yyvsp[-2].symbVal)->all_ints[0] / (yyvsp[0].symbVal)->all_ints[0];
                                    }
                                }
                            }
                            else if( second_T == "ARA"){
                                int ind2 = (yyvsp[0].symbVal)->getAraIndex(); 
                                if(first_var == "FLOAT"){
                                    final_var = "FLOAT"; 
                                    if(second_var == "INT") {
                                        if((yyvsp[0].symbVal)->all_ints[ind2] == 0){
                                            err_sem++; 
                                            errf << "Line# " << line_count << ": Warning: Division by zero\n"; 
                                            curr->all_floats[0] = numeric_limits<float>::infinity();
                                        }
                                        else curr->all_floats[0] = (yyvsp[-2].symbVal)->all_floats[0] / (yyvsp[0].symbVal)->all_ints[ind2];
                                    } 
                                    else {
                                        if((yyvsp[0].symbVal)->all_floats[ind2] == 0){ 
                                            err_sem++; 
                                            errf << "Line# " << line_count << ": Warning: Division by zero\n";
                                            curr->all_floats[0] = numeric_limits<float>::infinity();
                                        }
                                        else curr->all_floats[0] = (yyvsp[-2].symbVal)->all_floats[0] / (yyvsp[0].symbVal)->all_floats[ind2];
                                    }
                                }
                                else{
                                    if(second_var == "FLOAT"){
                                        final_var = "FLOAT"; 
                                        if((yyvsp[0].symbVal)->all_floats[ind2] == 0){
                                            err_sem++; 
                                            errf << "Line# " << line_count << ": Warning: Division by zero\n"; 
                                            curr->all_floats[0] = numeric_limits<float>::infinity();
                                        }
                                        else curr->all_floats[0] = (yyvsp[-2].symbVal)->all_ints[0] / (yyvsp[0].symbVal)->all_floats[ind2];
                                    }
                                    else{
                                        final_var = "INT"; 
                                        if((yyvsp[0].symbVal)->all_ints[ind2] == 0){
                                            err_sem++; 
                                            errf << "Line# " << line_count << ": Warning: Division by zero\n"; 
                                            curr->all_ints[0] = numeric_limits<int>::infinity();
                                        }
                                        else curr->all_ints[0] = (yyvsp[-2].symbVal)->all_ints[0] / (yyvsp[0].symbVal)->all_ints[ind2];
                                    }
                                }
                            }
                        }
                        else if( first_T == "ARA"){
                            int ind1= (yyvsp[-2].symbVal)->getAraIndex(); 
                            if( second_T == "VAR"){
                                if(first_var == "FLOAT"){
                                    final_var = "FLOAT"; 
                                    if(second_var == "INT") {
                                        if((yyvsp[0].symbVal)->all_ints[0] == 0){
                                            err_sem++; 
                                            errf << "Line# " << line_count << ": Warning: Division by zero\n"; 
                                            curr->all_floats[0] = numeric_limits<float>::infinity(); 
                                        }
                                        else curr->all_floats[0] = (yyvsp[-2].symbVal)->all_floats[ind1] / (yyvsp[0].symbVal)->all_ints[0];
                                    } 
                                    else {
                                        if((yyvsp[0].symbVal)->all_floats[0] == 0 ){
                                            err_sem++; 
                                            errf << "Line# " << line_count << ": Warning: Division by zero\n"; 
                                            curr->all_floats[0] = numeric_limits<float>::infinity();
                                        }
                                        else curr->all_floats[0] = (yyvsp[-2].symbVal)->all_floats[ind1] / (yyvsp[0].symbVal)->all_floats[0];
                                    }
                                }
                                else{
                                    if(second_var == "FLOAT"){
                                        final_var = "FLOAT"; 
                                        if((yyvsp[0].symbVal)->all_floats[0] == 0){
                                            err_sem++; 
                                            errf << "Line# " << line_count << ": Warning: Division by zero\n";
                                            curr->all_floats[0] = numeric_limits<float>::infinity();
                                        }
                                        else curr->all_floats[0] = (yyvsp[-2].symbVal)->all_ints[ind1] / (yyvsp[0].symbVal)->all_floats[0];
                                    }
                                    else{
                                        final_var = "INT"; 
                                        if((yyvsp[0].symbVal)->all_ints[0] == 0){
                                            err_sem++; 
                                            errf << "Line# " << line_count << ": Warning: Division by zero\n"; 
                                            curr->all_ints[0] = numeric_limits<int>::infinity();
                                        }
                                        else curr->all_ints[0] = (yyvsp[-2].symbVal)->all_ints[ind1] / (yyvsp[0].symbVal)->all_ints[0];
                                    }
                                }
                            }
                            else if( second_T == "ARA"){
                                int ind2 = (yyvsp[0].symbVal)->getAraIndex(); 
                                if(first_var == "FLOAT"){
                                    final_var = "FLOAT"; 
                                    if(second_var == "INT") {
                                        if((yyvsp[0].symbVal)->all_ints[ind2] == 0){
                                            err_sem++; 
                                            errf << "Line# " << line_count << ": Warning: Division by zero\n"; 
                                            curr->all_floats[0] = numeric_limits<float>::infinity();
                                        }
                                        else curr->all_floats[0] = (yyvsp[-2].symbVal)->all_floats[ind1] / (yyvsp[0].symbVal)->all_ints[ind2];
                                    } 
                                    else {
                                        if((yyvsp[0].symbVal)->all_floats[ind2] == 0){ 
                                            err_sem++; 
                                            errf << "Line# " << line_count << ": Warning: Division by zero\n"; 
                                            curr->all_floats[0] = numeric_limits<float>::infinity();
                                        }
                                        else curr->all_floats[0] = (yyvsp[-2].symbVal)->all_floats[ind1] / (yyvsp[0].symbVal)->all_floats[ind2];
                                    }
                                }
                                else{
                                    if(second_var == "FLOAT"){
                                        final_var = "FLOAT"; 
                                        if((yyvsp[0].symbVal)->all_floats[ind2] == 0){
                                            err_sem++; 
                                            errf << "Line# " << line_count << ": Warning: Division by zero\n"; 
                                            curr->all_floats[0] = numeric_limits<float>::infinity();
                                        }
                                        else curr->all_floats[0] = (yyvsp[-2].symbVal)->all_ints[ind1] / (yyvsp[0].symbVal)->all_floats[ind2];
                                    }
                                    else{
                                        final_var = "INT"; 
                                        if((yyvsp[0].symbVal)->all_ints[ind2] == 0){
                                            err_sem++; 
                                            errf << "Line# " << line_count << ": Warning: Division by zero\n"; 
                                            curr->all_ints[0] = numeric_limits<int>::infinity();
                                        }
                                        else curr->all_ints[0] = (yyvsp[-2].symbVal)->all_ints[ind1] / (yyvsp[0].symbVal)->all_ints[ind2];
                                    }
                                }
                            }
                        }
                    }
                    else if(mulop_type == "%"){
                        
                        if(first_var == "FLOAT" || second_var == "FLOAT"){
                            errf << "Line# " << line_count << ": Operands of modulus must be integers\n";
                            err_sem++;  
                        }
                        else{
                            int check = (yyvsp[0].symbVal)->all_ints[0] ; 
                            if(check == 0){
                                err_sem++; 
                                errf << "Line# " << line_count << ": Warning: Division by zero\n"; 
                                final_var = "error";  
                            } 
                            else {
                                final_var = "INT";
                                 if(first_T == "VAR"){
                                if(second_T == "VAR") curr->all_ints[0] = (yyvsp[-2].symbVal)->all_ints[0] % (yyvsp[0].symbVal)->all_ints[0]; 
                                else curr->all_ints[0] = (yyvsp[-2].symbVal)->all_ints[0] % (yyvsp[0].symbVal)->all_ints[ (yyvsp[0].symbVal)->getAraIndex() ];
                            }
                            else{
                                int ind1= (yyvsp[-2].symbVal)->getAraIndex(); 
                                if(second_T == "VAR") curr->all_ints[0] = (yyvsp[-2].symbVal)->all_ints[ind1] % (yyvsp[0].symbVal)->all_ints[0]; 
                                else curr->all_ints[0] = (yyvsp[-2].symbVal)->all_ints[ind1] % (yyvsp[0].symbVal)->all_ints[ (yyvsp[0].symbVal)->getAraIndex() ];
                            }
                            } 
                        }
                    } 
                    (yyval.symbVal) = curr; 
                    (yyval.symbVal)->setIDType("VAR");
                    (yyval.symbVal)->setVarType(final_var); 
                    (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[-2].symbVal)->node->getfirstLine(),"term : term MULOP unary_expression","NULL");
                    (yyval.symbVal)->node->addChild((yyvsp[-2].symbVal)->node);
                    (yyval.symbVal)->node->addChild((yyvsp[-1].symbVal)->node);
                    (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node);
                    ////-----------------------------
                    (yyvsp[-1].symbVal)->node->_name = mulop_type;
                }
#line 3251 "y.tab.c"
    break;

  case 58: /* unary_expression: ADDOP unary_expression  */
#line 1472 "2005018.y"
                    {
                        logfile << "unary_expression : ADDOP unary_expression\n";
					    if((yyvsp[-1].symbVal)->getname() == "-"){
						    if((yyvsp[0].symbVal)->getVarType() == "VAR"){
							    (yyvsp[0].symbVal)->all_ints[0] = (-1)*((yyvsp[0].symbVal)->all_ints[0]);
					    	}
						    else if((yyvsp[0].symbVal)->getVarType() == "ARA"){
							    (yyvsp[0].symbVal)->all_ints[(yyvsp[0].symbVal)->getAraIndex()] = (-1)*((yyvsp[0].symbVal)->all_ints[(yyvsp[0].symbVal)->getAraIndex()]);
						    }
					    }
					    (yyval.symbVal) = (yyvsp[0].symbVal);
                        treeNode *need = (yyvsp[0].symbVal)->node; 
                        (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[-1].symbVal)->node->getfirstLine(),"unary_expression : ADDOP unary_expression","NULL");
                        (yyval.symbVal)->node->addChild((yyvsp[-1].symbVal)->node);
                        (yyval.symbVal)->node->addChild(need);
                        ////-------------------------
                        (yyvsp[-1].symbVal)->node->_name = (yyvsp[-1].symbVal)->getname();
                    }
#line 3274 "y.tab.c"
    break;

  case 59: /* unary_expression: NOT unary_expression  */
#line 1491 "2005018.y"
                    {
                        logfile << "unary_expression : NOT unary_expression\n";
					    SymbolInfo *var = new SymbolInfo("INT");
                        var->setIDType("VAR");
                        int val; 
					    if((yyvsp[0].symbVal)->getVarType() == "INT"){
						    if((yyvsp[0].symbVal)->getIDType() == "VAR") val = (yyvsp[0].symbVal)->all_ints[0];
						    else if((yyvsp[0].symbVal)->getIDType() == "ARA")val = (yyvsp[0].symbVal)->all_ints[(yyvsp[0].symbVal)->getAraIndex()];
					    }
					    else if((yyvsp[0].symbVal)->getVarType() == "FLOAT"){
						    if((yyvsp[0].symbVal)->getIDType() == "VAR") val = (int)(yyvsp[0].symbVal)->all_floats[0];
						    else if((yyvsp[0].symbVal)->getIDType() == "ARA") val = (int)(yyvsp[0].symbVal)->all_floats[(yyvsp[0].symbVal)->getAraIndex()];
				    	}
                        val ^= 1; 
                        var->all_ints[0] = val; 
					    (yyval.symbVal) = var;
                        (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[-1].symbVal)->node->getfirstLine(),"unary_expression : NOT unary_expression","NULL");
                        (yyval.symbVal)->node->addChild((yyvsp[-1].symbVal)->node);
                        (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node);
                    }
#line 3299 "y.tab.c"
    break;

  case 60: /* unary_expression: factor  */
#line 1512 "2005018.y"
                    {
                        treeNode *curr = (yyvsp[0].symbVal)->node; 
                        logfile << "unary_expression : factor\n";
                        (yyvsp[0].symbVal)->all_ints.pb(0);
                        (yyvsp[0].symbVal)->all_floats.pb(0);
                        (yyval.symbVal) = (yyvsp[0].symbVal);
                        (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[0].symbVal)->node->getfirstLine(),"unary_expression : factor","NULL");
                        (yyval.symbVal)->node->addChild(curr); 
                    }
#line 3313 "y.tab.c"
    break;

  case 61: /* factor: variable  */
#line 1523 "2005018.y"
        {
            treeNode *curr = (yyvsp[0].symbVal)->node; 
            logfile << "factor  : variable\n"; 
            (yyval.symbVal) = (yyvsp[0].symbVal); 
            (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[0].symbVal)->node->getfirstLine(),"factor : variable","NULL");
            (yyval.symbVal)->node->addChild(curr);
        }
#line 3325 "y.tab.c"
    break;

  case 62: /* factor: ID LPAREN argument_list RPAREN  */
#line 1531 "2005018.y"
        {
            logfile << "factor : ID LPAREN argument_list RPAREN\n";
            string funcName = (yyvsp[-3].symbVal)->getname(); 
            string IDType = "FUNC";
            if(!table.LookUp2(funcName,IDType)){
                errf << "Line# " << line_count << ": Undeclared function'" << funcName <<  "'\n";
                err_sem++; 
                (yyval.symbVal) = new SymbolInfo("Error", "grammar"); 
                (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[-3].symbVal)->node->getfirstLine(),"factor : ID LPAREN argument_list RPAREN","NULL");
            } 
            else{
                string name = (yyvsp[-3].symbVal)->getname(), type = "FUNC"; 
                SymbolInfo *curr1 = table.LookUp2(name, type);
                string getReturn = curr1->getFuncRet(); 
                if(getReturn == "VOID"){
                    err_sem++; 
                    errf << "Line# " << line_count << ": Void cannot be used in expression\n";
                    (yyval.symbVal) = new SymbolInfo("Error", "grammar");
                    (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[-3].symbVal)->node->getfirstLine(),"factor : ID LPAREN argument_list RPAREN","NULL");
                }
                else{
                    SymbolInfo *curr = new SymbolInfo(getReturn);
					if((yyvsp[-3].symbVal)->getVarType() == "INT")curr->all_ints[0] = 0;
					else if((yyvsp[-3].symbVal)->getVarType() == "FLOAT")curr->all_floats[0] = 0;
					(yyval.symbVal) = curr;
                    (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[-3].symbVal)->node->getfirstLine(),"factor : ID LPAREN argument_list RPAREN","NULL");
                }
            }
            (yyval.symbVal)->node->addChild((yyvsp[-3].symbVal)->node);
            (yyval.symbVal)->node->addChild((yyvsp[-2].symbVal)->node);
            (yyval.symbVal)->node->addChild((yyvsp[-1].symbVal)->node);
            (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node);
            //////-----------------------------
            (yyvsp[-3].symbVal)->node->_name = funcName; 
        }
#line 3365 "y.tab.c"
    break;

  case 63: /* factor: LPAREN expression RPAREN  */
#line 1567 "2005018.y"
        {
            logfile << "factor : LPAREN expression RPAREN\n";
            treeNode *second_node = (yyvsp[-1].symbVal)->node; 
            (yyval.symbVal) = (yyvsp[-1].symbVal);
            (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[-2].symbVal)->node->getfirstLine(),"factor : LPAREN expression RPAREN","NULL");
            (yyval.symbVal)->node->addChild((yyvsp[-2].symbVal)->node);
            (yyval.symbVal)->node->addChild(second_node);
            (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node);
        }
#line 3379 "y.tab.c"
    break;

  case 64: /* factor: CONST_INT  */
#line 1577 "2005018.y"
        {
            logfile << "factor  : CONST_INT\n";
            treeNode *curr = (yyvsp[0].symbVal)->node; 
            (yyval.symbVal) = (yyvsp[0].symbVal);
            (yyval.symbVal)->setVarType("INT");
            (yyval.symbVal)->setIDType("VAR");
			(yyval.symbVal)->all_ints[0]= stoi((yyvsp[0].symbVal)->getname());
            (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[0].symbVal)->node->getfirstLine(),"factor  : CONST_INT","NULL");
            (yyval.symbVal)->node->addChild(curr);
            /////-------------------------
            (yyval.symbVal)->node->_name = (yyvsp[0].symbVal)->getname(); 
        }
#line 3396 "y.tab.c"
    break;

  case 65: /* factor: CONST_FLOAT  */
#line 1590 "2005018.y"
        {
            logfile << "factor : CONST_FLOAT\n";
            treeNode *curr = (yyvsp[0].symbVal)->node; 
			(yyval.symbVal) = (yyvsp[0].symbVal);
            (yyval.symbVal)->setVarType("FLOAT");
            (yyval.symbVal)->setIDType("VAR"); 
			(yyval.symbVal)->all_floats[0]= stof((yyvsp[0].symbVal)->getname());
            (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[0].symbVal)->node->getfirstLine(),"factor  : CONST_FLOAT","NULL");
            (yyval.symbVal)->node->addChild(curr);
            /////-------------------------
            (yyval.symbVal)->node->_name = (yyvsp[0].symbVal)->getname();
        }
#line 3413 "y.tab.c"
    break;

  case 66: /* factor: variable INCOP  */
#line 1603 "2005018.y"
        {
            logfile << "factor : variable INCOP\n";
            if((yyvsp[-1].symbVal)->getIDType() == "VAR"){
                if((yyvsp[-1].symbVal)->getVarType() == "INT"){
                    (yyvsp[-1].symbVal)->all_ints[0]++;
                }
                else if( (yyvsp[-1].symbVal)->getVarType() == "FLOAT"){
                    (yyvsp[-1].symbVal)->all_floats[0] += 1.0; 
                }
            }
            else if((yyvsp[-1].symbVal)->getIDType() == "ARA"){
                int ind = (yyvsp[-1].symbVal)->getAraIndex();
                if((yyvsp[-1].symbVal)->getVarType() == "INT"){
                    (yyvsp[-1].symbVal)->all_ints[ind]++; 
                }
                else if( (yyvsp[-1].symbVal)->getVarType() == "FLOAT"){
                    (yyvsp[-1].symbVal)->all_floats[ind] += 1.0; 
                }
            }
            treeNode *first_node = (yyvsp[-1].symbVal)->node; 
            (yyval.symbVal) = (yyvsp[-1].symbVal);
            (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[-1].symbVal)->node->getfirstLine(),"factor  : variable INCOP","NULL");
            (yyval.symbVal)->node->addChild(first_node);
            (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node);
            ////-----------------------------
            (yyvsp[0].symbVal)->node->_name = (yyvsp[0].symbVal)->getname(); 
        }
#line 3445 "y.tab.c"
    break;

  case 67: /* factor: variable DECOP  */
#line 1631 "2005018.y"
        {
            logfile << "factor : variable DECOP\n";
            if((yyvsp[-1].symbVal)->getIDType() == "VAR"){
                if((yyvsp[-1].symbVal)->getVarType() == "INT"){
                    (yyvsp[-1].symbVal)->all_ints[0]--;
                }
                else if( (yyvsp[-1].symbVal)->getVarType() == "FLOAT"){
                    (yyvsp[-1].symbVal)->all_floats[0] -= 1.0; 
                }
            }
            else if((yyvsp[-1].symbVal)->getIDType() == "ARA"){
                int ind = (yyvsp[-1].symbVal)->getAraIndex();
                if((yyvsp[-1].symbVal)->getVarType() == "INT"){
                    (yyvsp[-1].symbVal)->all_ints[ind]--; 
                }
                else if( (yyvsp[-1].symbVal)->getVarType() == "FLOAT"){
                    (yyvsp[-1].symbVal)->all_floats[ind] -= 1.0; 
                }
            }
            treeNode *first_node = (yyvsp[-1].symbVal)->node; 
            (yyval.symbVal) = (yyvsp[-1].symbVal);
            (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[-1].symbVal)->node->getfirstLine(),"factor  : variable DECOP","NULL");
            (yyval.symbVal)->node->addChild(first_node);
            (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node);
        }
#line 3475 "y.tab.c"
    break;

  case 68: /* argument_list: arguments  */
#line 1658 "2005018.y"
                {
                    (yyval.symbVal) = new SymbolInfo("arguments_list", "grammar");
                    logfile << "argument_list : arguments\n";
                    (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[0].symbVal)->node->getfirstLine(),"argument_list : arguments","NULL");
                    (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node);
                }
#line 3486 "y.tab.c"
    break;

  case 69: /* argument_list: %empty  */
#line 1665 "2005018.y"
                {
                    (yyval.symbVal) = new SymbolInfo("arguments_list","grammar");
                }
#line 3494 "y.tab.c"
    break;

  case 70: /* arguments: arguments COMMA logic_expression  */
#line 1670 "2005018.y"
                {
                    (yyval.symbVal) = new SymbolInfo("arguments", "grammar");
                    logfile << "arguments : arguments COMMA logic_expression\n";
                    (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[-2].symbVal)->node->getfirstLine(),"arguments : arguments COMMA logic_expression","NULL");
                    (yyval.symbVal)->node->addChild((yyvsp[-2].symbVal)->node);
                    (yyval.symbVal)->node->addChild((yyvsp[-1].symbVal)->node);
                    (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node);
                    ////------------------------
                }
#line 3508 "y.tab.c"
    break;

  case 71: /* arguments: logic_expression  */
#line 1680 "2005018.y"
                {
                    (yyval.symbVal) = new SymbolInfo("arguments", "grammar");
                    logfile << "arguments : logic_expression\n";
                    (yyval.symbVal)->node = new treeNode(line_count,(yyvsp[0].symbVal)->node->getfirstLine(),"arguments : logic_expression","NULL");
                    (yyval.symbVal)->node->addChild((yyvsp[0].symbVal)->node);
                }
#line 3519 "y.tab.c"
    break;


#line 3523 "y.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
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
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 1688 "2005018.y"


int main(int argc, char *argv[]){
    if((yyin=fopen(argv[1],"r"))==NULL){
        cout << "Cannot open input file.\n"; 
        exit(1);
    }
    logfile.open("2005018_log.txt");
    errf.open("2005018_errors.txt");
    parsefile.open("2005018_parsetree.txt"); 
    ASM.open("2005018.asm");
    table.EnterScope();  
	yyparse(); 
    parsefile.close(); 
    logfile.close(); 
    errf.close(); 
	return 0;
}
