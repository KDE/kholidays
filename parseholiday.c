/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0

/* Substitute the variable and function names.  */
#define yyparse kcalparse
#define yylex   kcallex
#define yyerror kcalerror
#define yylval  kcallval
#define yychar  kcalchar
#define yydebug kcaldebug
#define yynerrs kcalnerrs


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NUMBER = 258,
     MONTH = 259,
     WDAY = 260,
     COLOR = 261,
     STRING = 262,
     IN = 263,
     PLUS = 264,
     MINUS = 265,
     SMALL = 266,
     CYEAR = 267,
     LEAPYEAR = 268,
     SHIFT = 269,
     IF = 270,
     LENGTH = 271,
     EASTER = 272,
     EQ = 273,
     NE = 274,
     LE = 275,
     GE = 276,
     LT = 277,
     GT = 278,
     OR = 279,
     AND = 280,
     UMINUS = 281
   };
#endif
/* Tokens.  */
#define NUMBER 258
#define MONTH 259
#define WDAY 260
#define COLOR 261
#define STRING 262
#define IN 263
#define PLUS 264
#define MINUS 265
#define SMALL 266
#define CYEAR 267
#define LEAPYEAR 268
#define SHIFT 269
#define IF 270
#define LENGTH 271
#define EASTER 272
#define EQ 273
#define NE 274
#define LE 275
#define GE 276
#define LT 277
#define GT 278
#define OR 279
#define AND 280
#define UMINUS 281




/* Copy the first part of user declarations.  */
#line 1 "parseholiday.y"

/*
 * deals with the holiday file. A yacc parser is used to parse the file.
 * All the holidays of the specified year are calculated at once and stored
 * in two arrays that have one entry for each day of the year. The day
 * drawing routines just use the julian date to index into these arrays.
 * There are two arrays because holidays can be printed either on a full
 * line under the day number, or as a small line to the right of the day
 * number. It's convenient to have both.
 *
 *	parse_holidays(year, force)	read the holiday file and evaluate
 *					all the holiday definitions for
 *					<year>. Sets holiday and sm_holiday
 *					arrays. If force is set, re-eval even
 *					if year is the same as last time.
 *
 * Taken from plan by Thomas Driemeyer <thomas@bitrot.de>
 * Adapted for use in KOrganizer by Preston Brown <pbrown@kde.org> and
 * Reinhold Kainhofer <reinhold@kainhofer.com>
 */

#include <config.h>
#include <config-libkholidays.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#include <limits.h>

#ifdef HAVE_MALLOC_H
#include <malloc.h>
#endif

/*** Macro definitions and constants ***/
/*
 * Before you mail and complain that the following macro is incorrect,
 * please consider that this is one of the main battlegrounds of the
 * Annual Usenet Flame Wars. 2000 is a leap year. Just trust me on this :-)
 */

#define ISLEAPYEAR(y)	!((y)&3)
#define JULIAN(m,d)	(monthbegin[m] + (d)-1+((m)>1 && ISLEAPYEAR(parse_year)))
#define LAST		999
#define ANY		0
#define	BEFORE		-1
#define AFTER		-2
/**** Public forward declarations  ****/
char *parse_holidays(const char *holidays, int year, short force);

/**** Private forward declarations ****/
extern int       kcallex(void);          /* external lexical analyzer */
static void      kcalerror(const char *s);
static time_t    date_to_time(int day, int month, int year, 
			      int *wkday, int *julian, int *weeknum);
static time_t    tm_to_time(struct tm *tm);
static int	 day_from_name(char *str);
static int	 day_from_easter(void);
static int	 day_from_monthday(int month, int day);
static int	 day_from_wday(int day, int wday, int num);
static void	 monthday_from_day(int day, int *m, int *d, int *y);
static int       calc_easter(int year);
static void      setliteraldate(int month, int day, int off, int *ddup);
static void      seteaster(int off, int length);
static void      setdate(int month, int day, int year, int off, int conditionaloff, int length);
static void      setwday(int num, int wday, int month, int off, int length); 
static void      setdoff(int wday, int rel, int month, int day, 
			 int year, int off, int length);
/*** Variables and structures ***/
static int	 m, d, y;
int              kcallineno;	       	/* current line # being parsed */
FILE            *kcalin;                  /* file currently being processed */
int	         yacc_small;		/* small string or on its own line? */
int	         yacc_stringcolor;	/* color of holiday name text, 1..8 */
char	        *yacc_string;		/* holiday name text */
int	         yacc_daycolor;		/* color of day number, 1..8 */
char	        *progname;		/* argv[0] */
int	         parse_year = -1;	/* year being parsed, 0=1970..99=2069*/
static const char *filename;		/* holiday filename */
static char	 errormsg[PATH_MAX+200];/* error message if any, or "" */
static int	 easter_julian;		/* julian date of Easter Sunday */
static char	*holiday_name;		/* strdup'd yacc_string */
short 	         monthlen[12] = { 31, 28, 31, 30, 
				 31, 30, 31, 31,
				 30, 31, 30, 31 };
short	         monthbegin[12] = { 0, 31, 59, 90,
				    120, 151, 181, 
				    212, 243, 273,
				    304, 334 };

/* struct holiday;*/
struct holiday {
  char            *string;        /* name of holiday, 0=not a holiday */
  int             color;
  unsigned short  dup;            /* reference count */
  struct holiday         *next;
};

struct holiday	 holidays[366];		/* info for each day, separate for */
/*struct holiday   sm_holiday[366];*/	/* full-line texts under, and small */
					/* texts next to day number */
static int	initialized=0;


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 109 "parseholiday.y"
{ int ival; char *sval; }
/* Line 193 of yacc.c.  */
#line 266 "parseholiday.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 279 "parseholiday.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   271

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  16
/* YYNRULES -- Number of rules.  */
#define YYNRULES  69
/* YYNRULES -- Number of states.  */
#define YYNSTATES  129

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   281

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    31,     2,     2,     2,    30,     2,     2,
      38,    39,    28,    27,     2,    26,    35,    29,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    34,     2,
       2,     2,     2,    33,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    36,     2,    37,     2,     2,     2,     2,     2,     2,
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
      25,    32
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     4,     5,    13,    14,    16,    17,    19,
      23,    28,    32,    37,    44,    50,    51,    54,    57,    58,
      63,    64,    66,    70,    71,    74,    78,    83,    89,    93,
      99,   102,   106,   109,   113,   118,   120,   122,   124,   128,
     133,   137,   140,   143,   147,   152,   154,   156,   158,   162,
     166,   170,   174,   178,   182,   186,   190,   194,   198,   202,
     206,   210,   216,   219,   223,   227,   229,   231,   234,   236
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      41,     0,    -1,    -1,    -1,    41,    43,    44,     7,    44,
      42,    45,    -1,    -1,    11,    -1,    -1,     6,    -1,    17,
      46,    49,    -1,    50,    46,    47,    49,    -1,     5,    46,
      49,    -1,    54,     5,    46,    49,    -1,    54,     5,     8,
      52,    46,    49,    -1,     5,    54,    50,    46,    49,    -1,
      -1,     9,    53,    -1,    10,    53,    -1,    -1,    14,    48,
      15,    48,    -1,    -1,     5,    -1,     5,    24,    48,    -1,
      -1,    16,    53,    -1,    54,    35,    52,    -1,    54,    35,
      52,    35,    -1,    54,    35,    52,    35,    53,    -1,    52,
      29,    54,    -1,    52,    29,    54,    29,    54,    -1,     4,
      54,    -1,     4,    54,    54,    -1,    54,     4,    -1,    54,
       4,    54,    -1,    54,    35,     4,    54,    -1,    54,    -1,
       7,    -1,    17,    -1,    54,    35,    52,    -1,    54,    35,
      52,    35,    -1,    52,    29,    54,    -1,    54,     4,    -1,
       4,    54,    -1,     5,    54,    54,    -1,    54,     5,     8,
      52,    -1,     4,    -1,    54,    -1,    54,    -1,    53,    24,
      53,    -1,    53,    25,    53,    -1,    53,    18,    53,    -1,
      53,    19,    53,    -1,    53,    20,    53,    -1,    53,    21,
      53,    -1,    53,    22,    53,    -1,    53,    23,    53,    -1,
      53,    27,    53,    -1,    53,    26,    53,    -1,    53,    28,
      53,    -1,    53,    29,    53,    -1,    53,    30,    53,    -1,
      53,    33,    53,    34,    53,    -1,    31,    53,    -1,    36,
      51,    37,    -1,    38,    53,    39,    -1,    55,    -1,     3,
      -1,    26,     3,    -1,    12,    -1,    13,    54,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   128,   128,   129,   129,   135,   136,   139,   140,   143,
     144,   145,   146,   147,   148,   151,   152,   153,   156,   157,
     160,   161,   162,   165,   166,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   183,   184,   185,   187,
     189,   191,   193,   195,   197,   203,   203,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   224,   225,   228,   229,   230,   231
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUMBER", "MONTH", "WDAY", "COLOR",
  "STRING", "IN", "PLUS", "MINUS", "SMALL", "CYEAR", "LEAPYEAR", "SHIFT",
  "IF", "LENGTH", "EASTER", "EQ", "NE", "LE", "GE", "LT", "GT", "OR",
  "AND", "'-'", "'+'", "'*'", "'/'", "'%'", "'!'", "UMINUS", "'?'", "':'",
  "'.'", "'['", "']'", "'('", "')'", "$accept", "list", "@1", "small",
  "color", "entry", "offset", "conditionaloffset", "wdaycondition",
  "length", "date", "reldate", "month", "expr", "pexpr", "number", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,    45,    43,    42,    47,
      37,    33,   281,    63,    58,    46,    91,    93,    40,    41
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    40,    41,    42,    41,    43,    43,    44,    44,    45,
      45,    45,    45,    45,    45,    46,    46,    46,    47,    47,
      48,    48,    48,    49,    49,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    52,    52,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    54,    54,    55,    55,    55,    55
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     0,     7,     0,     1,     0,     1,     3,
       4,     3,     4,     6,     5,     0,     2,     2,     0,     4,
       0,     1,     3,     0,     2,     3,     4,     5,     3,     5,
       2,     3,     2,     3,     4,     1,     1,     1,     3,     4,
       3,     2,     2,     3,     4,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     5,     2,     3,     3,     1,     1,     2,     1,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     5,     1,     6,     7,     8,     0,     7,     3,     0,
      66,    45,    15,    68,     0,    15,     0,     0,     4,    15,
       0,    35,    65,    30,     0,     0,    23,     0,    69,    23,
      67,     0,     0,     0,    47,    18,     0,    32,    15,     0,
      31,    16,    17,     0,    11,    15,    35,     9,    62,    45,
       0,    36,    37,     0,     0,    46,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      64,    20,    23,    28,    33,     0,    23,    45,    25,    46,
      24,    23,    42,     0,    63,     0,    41,     0,     0,    50,
      51,    52,    53,    54,    55,    48,    49,    57,    56,    58,
      59,    60,     0,    21,     0,    10,     0,    45,    15,    12,
      34,    26,    14,    43,    40,     0,    38,     0,    20,    20,
      29,    23,    27,    44,    39,    61,    22,    19,    13
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     9,     4,     6,    18,    26,    72,   104,    44,
      19,    53,    20,    33,    34,    22
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -82
static const yytype_int16 yypact[] =
{
     -82,     4,   -82,   -82,     0,   -82,     2,     0,   -82,    97,
     -82,   139,    -2,   -82,   139,     7,    26,   108,   -82,     7,
      13,   132,   -82,   139,   108,   108,    27,   128,   -82,    27,
     -82,   108,    81,   167,   -82,    45,   139,   139,    24,   144,
     -82,   206,   206,   108,   -82,     7,    60,   -82,    30,   139,
     139,   -82,   -82,    33,    42,    57,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   108,   108,   108,   108,
     -82,    67,    27,    46,   -82,   146,    27,   139,    47,   -82,
     206,    27,   -82,   139,   -82,   139,   -82,    69,   146,   238,
     238,   238,   238,   238,   238,   222,   238,    -8,    -8,    30,
      30,    30,   189,    56,    66,   -82,   139,   -82,     7,   -82,
     -82,   108,   -82,   -82,   -82,   146,    48,   108,    67,    67,
     -82,    27,   206,   -82,   -82,   -82,   -82,   -82,   -82
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -82,   -82,   -82,   -82,    80,   -82,    20,   -82,   -81,    -3,
      63,   -82,    28,   -12,    -9,   -82
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -47
static const yytype_int16 yytable[] =
{
      21,    10,    23,    27,     2,    28,     5,    24,    25,     7,
      13,    14,    41,    42,    40,     3,    24,    25,    46,    48,
      66,    67,    68,    55,    16,    69,    47,    73,    74,    30,
      79,    80,    75,    24,    25,    29,    17,   126,   127,    35,
      82,    83,    36,    43,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,    76,    71,
      54,    86,    87,    69,    37,    81,    79,    78,   110,   105,
      84,    85,   103,   109,   113,   106,   114,   115,   112,    79,
     118,   119,   111,   124,    10,    49,    50,     8,    51,   -46,
      45,     0,    88,    13,    14,    39,     0,   120,    52,   122,
      10,    11,    12,   108,     0,   125,    79,    16,     0,    13,
      14,    10,     0,     0,    15,     0,   116,     0,   128,    17,
      13,    14,     0,    16,     0,     0,     0,     0,   121,     0,
       0,    10,    11,     0,    16,    17,    37,    38,     0,    31,
      13,    14,    10,   123,    32,     0,    17,    10,    77,    10,
     107,    13,    14,     0,    16,     0,    13,    14,    13,    14,
       0,   -46,     0,     0,     0,    16,    17,    39,     0,     0,
      16,     0,    16,     0,     0,     0,     0,    17,     0,     0,
       0,     0,    17,     0,    17,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,     0,     0,
      69,     0,     0,     0,     0,     0,    70,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
       0,     0,    69,   117,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,     0,     0,    69,
      56,    57,    58,    59,    60,    61,     0,    63,    64,    65,
      66,    67,    68,     0,     0,    69,    56,    57,    58,    59,
      60,    61,     0,     0,    64,    65,    66,    67,    68,     0,
       0,    69
};

static const yytype_int8 yycheck[] =
{
       9,     3,    11,    12,     0,    14,     6,     9,    10,     7,
      12,    13,    24,    25,    23,    11,     9,    10,    27,    31,
      28,    29,    30,    32,    26,    33,    29,    36,    37,     3,
      39,    43,     8,     9,    10,    15,    38,   118,   119,    19,
      49,    50,    29,    16,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    38,    14,
      32,     4,     5,    33,     4,    45,    75,    39,    77,    72,
      37,    29,     5,    76,    83,    29,    85,     8,    81,    88,
      24,    15,    35,    35,     3,     4,     5,     7,     7,    29,
      27,    -1,    35,    12,    13,    35,    -1,   106,    17,   111,
       3,     4,     5,    75,    -1,   117,   115,    26,    -1,    12,
      13,     3,    -1,    -1,    17,    -1,    88,    -1,   121,    38,
      12,    13,    -1,    26,    -1,    -1,    -1,    -1,   108,    -1,
      -1,     3,     4,    -1,    26,    38,     4,     5,    -1,    31,
      12,    13,     3,   115,    36,    -1,    38,     3,     4,     3,
       4,    12,    13,    -1,    26,    -1,    12,    13,    12,    13,
      -1,    29,    -1,    -1,    -1,    26,    38,    35,    -1,    -1,
      26,    -1,    26,    -1,    -1,    -1,    -1,    38,    -1,    -1,
      -1,    -1,    38,    -1,    38,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    -1,    -1,
      33,    -1,    -1,    -1,    -1,    -1,    39,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      -1,    -1,    33,    34,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    -1,    -1,    33,
      18,    19,    20,    21,    22,    23,    -1,    25,    26,    27,
      28,    29,    30,    -1,    -1,    33,    18,    19,    20,    21,
      22,    23,    -1,    -1,    26,    27,    28,    29,    30,    -1,
      -1,    33
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    41,     0,    11,    43,     6,    44,     7,    44,    42,
       3,     4,     5,    12,    13,    17,    26,    38,    45,    50,
      52,    54,    55,    54,     9,    10,    46,    54,    54,    46,
       3,    31,    36,    53,    54,    46,    29,     4,     5,    35,
      54,    53,    53,    16,    49,    50,    54,    49,    53,     4,
       5,     7,    17,    51,    52,    54,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    33,
      39,    14,    47,    54,    54,     8,    46,     4,    52,    54,
      53,    46,    54,    54,    37,    29,     4,     5,    35,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,     5,    48,    49,    29,     4,    52,    49,
      54,    35,    49,    54,    54,     8,    52,    34,    24,    15,
      54,    46,    53,    52,    35,    53,    48,    48,    49
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:
#line 129 "parseholiday.y"
    { yacc_stringcolor = (yyvsp[(3) - (5)].ival);
						  yacc_string	= (yyvsp[(4) - (5)].sval);
						  yacc_daycolor	= (yyvsp[(5) - (5)].ival); ;}
    break;

  case 4:
#line 132 "parseholiday.y"
    { free(yacc_string); ;}
    break;

  case 5:
#line 135 "parseholiday.y"
    { yacc_small = 0; ;}
    break;

  case 6:
#line 136 "parseholiday.y"
    { yacc_small = 1; ;}
    break;

  case 7:
#line 139 "parseholiday.y"
    { (yyval.ival) = 0; ;}
    break;

  case 8:
#line 140 "parseholiday.y"
    { (yyval.ival) = (yyvsp[(1) - (1)].ival); ;}
    break;

  case 9:
#line 143 "parseholiday.y"
    { seteaster((yyvsp[(2) - (3)].ival), (yyvsp[(3) - (3)].ival)); ;}
    break;

  case 10:
#line 144 "parseholiday.y"
    { setdate( m,  d,  y, (yyvsp[(2) - (4)].ival), (yyvsp[(3) - (4)].ival), (yyvsp[(4) - (4)].ival));;}
    break;

  case 11:
#line 145 "parseholiday.y"
    { setwday( 0, (yyvsp[(1) - (3)].ival),  0, (yyvsp[(2) - (3)].ival), (yyvsp[(3) - (3)].ival));;}
    break;

  case 12:
#line 146 "parseholiday.y"
    { setwday((yyvsp[(1) - (4)].ival), (yyvsp[(2) - (4)].ival),  0, (yyvsp[(3) - (4)].ival), (yyvsp[(4) - (4)].ival));;}
    break;

  case 13:
#line 147 "parseholiday.y"
    { setwday((yyvsp[(1) - (6)].ival), (yyvsp[(2) - (6)].ival), (yyvsp[(4) - (6)].ival), (yyvsp[(5) - (6)].ival), (yyvsp[(6) - (6)].ival));;}
    break;

  case 14:
#line 148 "parseholiday.y"
    { setdoff((yyvsp[(1) - (5)].ival), (yyvsp[(2) - (5)].ival),m,d,y,(yyvsp[(4) - (5)].ival),(yyvsp[(5) - (5)].ival));;}
    break;

  case 15:
#line 151 "parseholiday.y"
    { (yyval.ival) =	0; ;}
    break;

  case 16:
#line 152 "parseholiday.y"
    { (yyval.ival) =	(yyvsp[(2) - (2)].ival); ;}
    break;

  case 17:
#line 153 "parseholiday.y"
    { (yyval.ival) = -(yyvsp[(2) - (2)].ival); ;}
    break;

  case 18:
#line 156 "parseholiday.y"
    { (yyval.ival) = 0; ;}
    break;

  case 19:
#line 157 "parseholiday.y"
    { (yyval.ival) = ((yyvsp[(2) - (4)].ival)<<8) | (yyvsp[(4) - (4)].ival);printf("Shift to %i if %i\n", (yyvsp[(2) - (4)].ival), (yyvsp[(4) - (4)].ival)); ;}
    break;

  case 20:
#line 160 "parseholiday.y"
    { (yyval.ival) = 0; ;}
    break;

  case 21:
#line 161 "parseholiday.y"
    { (yyval.ival) = (1<<(yyvsp[(1) - (1)].ival)); ;}
    break;

  case 22:
#line 162 "parseholiday.y"
    { (yyval.ival) = (1<<(yyvsp[(1) - (3)].ival)) | (yyvsp[(3) - (3)].ival); ;}
    break;

  case 23:
#line 165 "parseholiday.y"
    { (yyval.ival) =	1; ;}
    break;

  case 24:
#line 166 "parseholiday.y"
    { (yyval.ival) =	(yyvsp[(2) - (2)].ival); ;}
    break;

  case 25:
#line 169 "parseholiday.y"
    { m = (yyvsp[(3) - (3)].ival); d = (yyvsp[(1) - (3)].ival); y = 0;  ;}
    break;

  case 26:
#line 170 "parseholiday.y"
    { m = (yyvsp[(3) - (4)].ival); d = (yyvsp[(1) - (4)].ival); y = 0;  ;}
    break;

  case 27:
#line 171 "parseholiday.y"
    { m = (yyvsp[(3) - (5)].ival); d = (yyvsp[(1) - (5)].ival); y = (yyvsp[(5) - (5)].ival); ;}
    break;

  case 28:
#line 172 "parseholiday.y"
    { m = (yyvsp[(1) - (3)].ival); d = (yyvsp[(3) - (3)].ival); y = 0;  ;}
    break;

  case 29:
#line 173 "parseholiday.y"
    { m = (yyvsp[(1) - (5)].ival); d = (yyvsp[(3) - (5)].ival); y = (yyvsp[(5) - (5)].ival); ;}
    break;

  case 30:
#line 174 "parseholiday.y"
    { m = (yyvsp[(1) - (2)].ival); d = (yyvsp[(2) - (2)].ival); y = 0;  ;}
    break;

  case 31:
#line 175 "parseholiday.y"
    { m = (yyvsp[(1) - (3)].ival); d = (yyvsp[(2) - (3)].ival); y = (yyvsp[(3) - (3)].ival); ;}
    break;

  case 32:
#line 176 "parseholiday.y"
    { m = (yyvsp[(2) - (2)].ival); d = (yyvsp[(1) - (2)].ival); y = 0;  ;}
    break;

  case 33:
#line 177 "parseholiday.y"
    { m = (yyvsp[(2) - (3)].ival); d = (yyvsp[(1) - (3)].ival); y = (yyvsp[(3) - (3)].ival); ;}
    break;

  case 34:
#line 178 "parseholiday.y"
    { m = (yyvsp[(3) - (4)].ival); d = (yyvsp[(1) - (4)].ival); y = (yyvsp[(4) - (4)].ival); ;}
    break;

  case 35:
#line 179 "parseholiday.y"
    { monthday_from_day((yyvsp[(1) - (1)].ival),
								 &m, &d, &y); ;}
    break;

  case 36:
#line 183 "parseholiday.y"
    { (yyval.ival) = day_from_name((yyvsp[(1) - (1)].sval)); ;}
    break;

  case 37:
#line 184 "parseholiday.y"
    { (yyval.ival) = day_from_easter(); ;}
    break;

  case 38:
#line 185 "parseholiday.y"
    { (yyval.ival) = day_from_monthday
								 ((yyvsp[(3) - (3)].ival), (yyvsp[(1) - (3)].ival)); ;}
    break;

  case 39:
#line 187 "parseholiday.y"
    { (yyval.ival) = day_from_monthday
								 ((yyvsp[(3) - (4)].ival), (yyvsp[(1) - (4)].ival)); ;}
    break;

  case 40:
#line 189 "parseholiday.y"
    { (yyval.ival) = day_from_monthday
								 ((yyvsp[(1) - (3)].ival), (yyvsp[(3) - (3)].ival)); ;}
    break;

  case 41:
#line 191 "parseholiday.y"
    { (yyval.ival) = day_from_monthday
								 ((yyvsp[(2) - (2)].ival), (yyvsp[(1) - (2)].ival)); ;}
    break;

  case 42:
#line 193 "parseholiday.y"
    { (yyval.ival) = day_from_monthday
								 ((yyvsp[(1) - (2)].ival), (yyvsp[(2) - (2)].ival)); ;}
    break;

  case 43:
#line 195 "parseholiday.y"
    { (yyval.ival) = day_from_wday((yyvsp[(3) - (3)].ival), (yyvsp[(1) - (3)].ival),
							 (yyvsp[(2) - (3)].ival) == -1 ? -1 : 0); ;}
    break;

  case 44:
#line 197 "parseholiday.y"
    { int day=day_from_monthday((yyvsp[(4) - (4)].ival),1);
						   (yyval.ival) = (yyvsp[(1) - (4)].ival) == 999
						    ? day_from_wday(day+1,(yyvsp[(2) - (4)].ival),-1)
						    : day_from_wday(day,(yyvsp[(2) - (4)].ival),(yyvsp[(1) - (4)].ival)-1);;}
    break;

  case 47:
#line 205 "parseholiday.y"
    { (yyval.ival) = (yyvsp[(1) - (1)].ival); ;}
    break;

  case 48:
#line 206 "parseholiday.y"
    { (yyval.ival) = (yyvsp[(1) - (3)].ival) || (yyvsp[(3) - (3)].ival); ;}
    break;

  case 49:
#line 207 "parseholiday.y"
    { (yyval.ival) = (yyvsp[(1) - (3)].ival) && (yyvsp[(3) - (3)].ival); ;}
    break;

  case 50:
#line 208 "parseholiday.y"
    { (yyval.ival) = (yyvsp[(1) - (3)].ival) == (yyvsp[(3) - (3)].ival); ;}
    break;

  case 51:
#line 209 "parseholiday.y"
    { (yyval.ival) = (yyvsp[(1) - (3)].ival) != (yyvsp[(3) - (3)].ival); ;}
    break;

  case 52:
#line 210 "parseholiday.y"
    { (yyval.ival) = (yyvsp[(1) - (3)].ival) <= (yyvsp[(3) - (3)].ival); ;}
    break;

  case 53:
#line 211 "parseholiday.y"
    { (yyval.ival) = (yyvsp[(1) - (3)].ival) >= (yyvsp[(3) - (3)].ival); ;}
    break;

  case 54:
#line 212 "parseholiday.y"
    { (yyval.ival) = (yyvsp[(1) - (3)].ival) <  (yyvsp[(3) - (3)].ival); ;}
    break;

  case 55:
#line 213 "parseholiday.y"
    { (yyval.ival) = (yyvsp[(1) - (3)].ival) >  (yyvsp[(3) - (3)].ival); ;}
    break;

  case 56:
#line 214 "parseholiday.y"
    { (yyval.ival) = (yyvsp[(1) - (3)].ival) +  (yyvsp[(3) - (3)].ival); ;}
    break;

  case 57:
#line 215 "parseholiday.y"
    { (yyval.ival) = (yyvsp[(1) - (3)].ival) -  (yyvsp[(3) - (3)].ival); ;}
    break;

  case 58:
#line 216 "parseholiday.y"
    { (yyval.ival) = (yyvsp[(1) - (3)].ival) *  (yyvsp[(3) - (3)].ival); ;}
    break;

  case 59:
#line 217 "parseholiday.y"
    { (yyval.ival) = (yyvsp[(3) - (3)].ival) ?  (yyvsp[(1) - (3)].ival) / (yyvsp[(3) - (3)].ival) : 0; ;}
    break;

  case 60:
#line 218 "parseholiday.y"
    { (yyval.ival) = (yyvsp[(3) - (3)].ival) ?  (yyvsp[(1) - (3)].ival) % (yyvsp[(3) - (3)].ival) : 0; ;}
    break;

  case 61:
#line 219 "parseholiday.y"
    { (yyval.ival) = (yyvsp[(1) - (5)].ival) ?  (yyvsp[(3) - (5)].ival) : (yyvsp[(5) - (5)].ival); ;}
    break;

  case 62:
#line 220 "parseholiday.y"
    { (yyval.ival) = !(yyvsp[(2) - (2)].ival); ;}
    break;

  case 63:
#line 221 "parseholiday.y"
    { (yyval.ival) = (yyvsp[(2) - (3)].ival); ;}
    break;

  case 64:
#line 224 "parseholiday.y"
    { (yyval.ival) = (yyvsp[(2) - (3)].ival); ;}
    break;

  case 65:
#line 225 "parseholiday.y"
    { (yyval.ival) = (yyvsp[(1) - (1)].ival); ;}
    break;

  case 67:
#line 229 "parseholiday.y"
    { (yyval.ival) = -(yyvsp[(2) - (2)].ival); ;}
    break;

  case 68:
#line 230 "parseholiday.y"
    { (yyval.ival) = parse_year; ;}
    break;

  case 69:
#line 231 "parseholiday.y"
    { (yyval.ival) = !(((yyvsp[(2) - (2)].ival)) & 3); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 1940 "parseholiday.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 233 "parseholiday.y"

	 
/*** Private Yacc callbacks and helper functions ***/
static void kcalerror(const char *msg)
{
  fprintf(stderr, "%s: %s in line %d of %s\n", progname,
	  msg, kcallineno+1, filename);
  if (!*errormsg)
    snprintf(errormsg,sizeof(errormsg),
	    "Problem with holiday file %s:\n%.80s in line %d",
	    filename, msg, kcallineno+1);
}

static time_t date_to_time(int day, int month, int year, 
			   int *wkday, int *julian, int *weeknum)
{
  struct tm               tm;
  time_t                  ttime;
  
  tm.tm_sec   = 0;
  tm.tm_min   = 0;
  tm.tm_hour  = 0;
  tm.tm_mday  = day;
  tm.tm_mon   = month;
  tm.tm_year  = year;
  ttime = tm_to_time(&tm);
  if (wkday)
    *wkday   = tm.tm_wday;
  if (julian)
    *julian  = tm.tm_yday;
  if (weeknum)
    *weeknum = 0
      ? tm.tm_yday / 7
      : tm.tm_yday ? ((tm.tm_yday - 1) /7) + 1 : 0;
  return(ttime == -1 || day != tm.tm_mday ? 0 : ttime);
} 

static time_t tm_to_time(struct tm *tm)
{
  time_t                  t;              /* return value */
  
  t  = monthbegin[tm->tm_mon]                     /* full months */
    + tm->tm_mday-1                              /* full days */
    + (!(tm->tm_year & 3) && tm->tm_mon > 1);    /* leap day this year*/
  tm->tm_yday = t;
  t += 365 * (tm->tm_year - 70)                   /* full years */
    + (tm->tm_year - 69)/4;                      /* past leap days */
  tm->tm_wday = (t + 4) % 7;
  
  t = t*86400 + tm->tm_hour*3600 + tm->tm_min*60 + tm->tm_sec;
  if (tm->tm_mday > monthlen[tm->tm_mon] +
      (!(tm->tm_year & 3) && tm->tm_mon == 1))
    return((time_t)-1);
  return(t);
} 

/*
 * set holiday by weekday (monday..sunday). The expression is
 * "every <num>-th <wday> of <month> plus <off> days". num and month
 * can be ANY or LAST.
 */

static void setwday(int num, int wday, int month, int off, int length)
{
  int		min_month = 0, max_month = 11;
  int		min_num   = 0, max_num   = 4;
  int		mn, n, dy, l, mlen, wday1;
  int		ddup = 0;
  
  if (month != ANY)
    min_month = max_month = month-1;
  if (month == LAST)
    min_month = max_month = 11;
  if (num != ANY)
    min_num = max_num = num-1;
  
  holiday_name = yacc_string;
  for (mn=min_month; mn <= max_month; mn++) {
    (void)date_to_time(1, mn, parse_year, &wday1, 0, 0);
    dy = (wday-1 - (wday1-1) +7) % 7 + 1;
    mlen = monthlen[mn] + (mn==1 && ISLEAPYEAR(parse_year));
    if (num == LAST)
      for (l=0; l < length; l++)
	setliteraldate(mn, dy+28<=mlen ? dy+28 : dy+21,
		       off+l, &ddup);
    else
      for (dy+=min_num*7, n=min_num; n <= max_num; n++, dy+=7)
	if (dy >= 1 && dy <= mlen)
	  for (l=0; l < length; l++)
	    setliteraldate(mn,dy,off+l,&ddup);
  }
}

/*
 * set holiday by weekday (monday..sunday) date offset. The expression is
 * "every <wday> before/after <date> plus <off> days". 
 * (This routine contributed by Peter Littlefield <plittle@sofkin.ca>)
 */

static void setdoff(int wday, int rel, int month, int day, 
		    int year, int off, int length)
{
  int		min_month = 0, max_month = 11;
  int		min_day   = 1, max_day   = 31;
  int		mn, dy, nd, l, wday1;
  int		ddup = 0;
  
  if (year != ANY) {
    year %= 100;
    if (year < 70) year += 100;
    if (year != parse_year)
      return;
  }
  if (month != ANY)
    min_month = max_month = month-1;
  if (month == LAST)
    min_month = max_month = 11;
  if (day != ANY)
    min_day   = max_day   = day;
  
  holiday_name = yacc_string;
  for (mn=min_month; mn <= max_month; mn++)
    if (day == LAST) {
      (void)date_to_time(monthlen[mn], mn, parse_year,
			 &wday1, 0, 0);
      nd = (((wday - wday1 + 7) % 7) -
	    ((rel == BEFORE) ? 7 : 0)) % 7;
      for (l=0; l < length; l++)
	setliteraldate(mn,monthlen[mn]+nd, off+l, &ddup);
    } else
      for (dy=min_day; dy <= max_day; dy++) {
	(void)date_to_time(dy, mn, parse_year,
			   &wday1, 0, 0);
	nd = (((wday - wday1 + 7) % 7) -
	      ((rel == BEFORE) ? 7 : 0)) % 7;
	for (l=0; l < length; l++)
	  setliteraldate(mn, dy+nd, off+l, &ddup);
      }
}

static int conditionalOffset( int day, int month, int year, int cond ) 
{
  int off = 0;
  int wday = 0;
  (void)date_to_time( day, month, year, &wday, 0, 0);
  if ( wday == 0 ) { wday = 7; } /* sunday is 7, not 0 */
  if ( cond & (1<<wday) ) { 
    /* condition matches -> higher 8 bits contain the possible days to shift to */
    int to = (cond >> 8);
    while ( !(to & (1<<((wday+off)%7))) && (off < 8) ) {
      ++off;
    }
  }
  if ( off >= 8 ) return 0;
  else return off;
}

/*
 * set holiday by date. Ignore holidays in the wrong year. The code is
 * complicated by expressions such as "any/last/any" (every last day of
 * the month).
 */

static void setdate(int month, int day, int year, int off, int conditionaloff, int length)
{
  int		min_month = 0, max_month = 11;
  int		min_day   = 1, max_day   = 31;
  int		mn, dy, l;
  int		ddup = 0;
  
  if (year != ANY) {
    year %= 100;
    if (year < 70) year += 100;
    if (year != parse_year)
      return;
  }
  if (month != ANY)
    min_month = max_month = month-1;
  if (month == LAST)
    min_month = max_month = 11;
  if (day != ANY)
    min_day   = max_day   = day;
  
  holiday_name = yacc_string;
  /** TODO: Include the conditionaloff variable. */
  /** The encoding of the conditional offset is:
        8 lower bits: conditions to shift (bit-register, bit 1=mon, ..., bit 7=sun)
        8 higher bits: weekday to shift to (bit-register, bit 1=mon, ..., bit 7=sun)
  */
  for (mn=min_month; mn <= max_month; mn++) {
    if (day == LAST) {
      int newoff = off + conditionalOffset( monthlen[mn], mn, parse_year, conditionaloff );
      for (l=0; l < length; l++)
	setliteraldate(mn, monthlen[mn], newoff+l, &ddup);
    } else {
      for (dy=min_day; dy <= max_day; dy++) {
        int newoff = off + conditionalOffset( dy, mn, parse_year, conditionaloff );
	for (l=0; l < length; l++)
	  setliteraldate(mn, dy, newoff+l, &ddup);
      }
    }
  }	  
}


/*
 * After the two routines above have removed ambiguities (ANY) and resolved
 * weekday specifications, this routine registers the holiday in the holiday
 * array. There are two of these, for full-line holidays (they take away one
 * appointment line in the month calendar daybox) and "small" holidays, which
 * appear next to the day number. If the day is already some other holiday,
 * add a new item to the singly-linked list and insert the holiday there.
 * <ddup> is information stored for parse_holidays(), it
 * will free() the holiday name only if its dup field is 0 (because many
 * string fields can point to the same string, which was allocated only once
 * by the lexer, and should therefore only be freed once).
 */

static void setliteraldate(int month, int day, int off, int *ddup)
{
  int julian = JULIAN(month, day) + off;
  /*  struct holiday *hp = yacc_small ? &sm_holiday[julian]
      : &holiday[julian]; */
  struct holiday *hp = 0;

  if (julian >= 0 && julian <= 365 ) {
    hp = &holidays[julian];
    if ( hp->string ) {
      while (hp->next) { hp = hp->next; }
      hp->next = malloc( sizeof(struct holiday)*2 );
      hp = hp->next;
      hp->next = 0;
    }
    if (!*ddup)
      holiday_name = strdup(holiday_name);
    hp->string	= holiday_name;
    hp->color   = (yacc_stringcolor == 0) ? yacc_daycolor : yacc_stringcolor;
    hp->dup		= (*ddup)++;
    
  }
}


/*
 * set a holiday relative to Easter
 */

static void seteaster(int off, int length)
{
  int		ddup = 0;	/* flag for later free() */
  int julian = easter_julian + off;
  /*  struct holiday *hp = yacc_small ? &sm_holiday[julian]
      : &holidays[julian];*/
  struct holiday *hp = 0;
  
  holiday_name = yacc_string;
  while (length-- > 0) {
    if (julian >= 0 && julian <= 365 ) {
      hp = &holidays[julian];
      if ( hp->string ) {
        while (hp->next) { hp = hp->next; }
        hp->next = malloc( sizeof(struct holiday)*2 );
        hp = hp->next;
        hp->next = 0;
      }
      if (!ddup)
	holiday_name = strdup(holiday_name);
      hp->string	= holiday_name;
      hp->color     = (yacc_stringcolor == 0) ? yacc_daycolor : yacc_stringcolor;
      hp->dup		= ddup++;
    }
    julian++;
  }
}


/*
 * calculate Easter Sunday as a julian date. I got this from Armin Liebl
 * <liebla@informatik.tu-muenchen.de>, who got it from Knuth. I hope I got
 * all this right...
 */

static int calc_easter(int year)
{
  int golden, cent, grcor, clcor, extra, epact, easter;
  
  golden = (year/19)*(-19);
  golden += year+1;
  cent = year/100+1;
  grcor = (cent*3)/(-4)+12;
  clcor = ((cent-18)/(-25)+cent-16)/3;
  extra = (year*5)/4+grcor-10;
  epact = golden*11+20+clcor+grcor;
  epact += (epact/30)*(-30);
  if (epact<=0)
    epact += 30;
  if (epact==25) {
    if (golden>11)
      epact += 1;
  } else {
    if (epact==24)
      epact += 1;
  }
  easter = epact*(-1)+44;
  if (easter<21)
    easter += 30;
  extra += easter;
  extra += (extra/7)*(-7);
  extra *= -1;
  easter += extra+7;
  easter += 31+28+!(year&3)-1;
  return(easter);
}


/*
 * functions used for [] syntax: (Erwin Hugo Achermann <acherman@inf.ethz.ch>)
 *
 * day_from_name (str)			gets day from symbolic name
 * day_from_easter ()			gets day as easter sunday
 * day_from_monthday (month, day)		gets <day> from <month/day>
 * day_from_wday (day, wday, num)	gets num-th day (wday) after <day> day
 * monthday_from_day (day, *m, *d, *y)	gets month/day/cur_year from <day>
 */

static int day_from_name(char *str)
{
  int	i;
  char	*name;
  
  for (i=0; i < 366; i++) {
    name = holidays[i].string;
    if (name && !strcmp(str, name))
      return(i);
  }
  return(-1);
}


static int day_from_easter(void)
{
  return(easter_julian);
}


static int day_from_monthday(int month, int day)
{
  if (month == 13)
    return(365 + ISLEAPYEAR(parse_year));
  return(JULIAN(month - 1, day));
}


static void monthday_from_day(int day, int *mn, int *dy, int *yr)
{
  int	i, len;
  
  *yr = parse_year;
  *mn = 0;
  *dy = 0;
  if (day < 0)
    return;
  for (i=0; i < 12; i++) {
    len = monthlen[i] + (i == 1 && ISLEAPYEAR(parse_year));
    if (day < len) {
      *mn = i + 1;
      *dy = day + 1;
      break;
    }
    day -= len;
  }
}


static int day_from_wday(int day, int wday, int num)
{
  int	wkday, yday, weeknum;
  
  (void)date_to_time(1, 0, parse_year, &wkday, &yday, &weeknum);
  day += (wday - wkday - day + 1001) % 7;
  day += num * 7;
  return (day);
}

static void initialize() 
{
  register struct holiday *hp;
  register int dy;
  initialized = 1;
  for (hp=holidays, dy=0; dy < 366; dy++, hp++)
  {
      hp->color = 0;
      hp->dup = 0;
      hp->string = 0;
      hp->next = 0;
  }
}

/*** Public Functions ***/
/*
 * parse the holiday text file, and set up the holiday arrays for a year.
 * If year is -1, re-parse the last year parsed (this is used when the
 * holiday file changes). If there is a CPP_PATH, check if the executable
 * really exists, and if so, pipe the holioday files through it.
 * Return an error message if an error occurred, 0 otherwise.
 */

char *parse_holidays(const char *holidayfile, int year, short force)
{
  register struct holiday *hp;
  register int		dy;
  short			piped = 0;
  if (!initialized)
    initialize();

  if (year == parse_year && !force)
      return(0);
  if (year < 0)
      year = parse_year;
  parse_year = year;
  easter_julian = calc_easter(year + 1900);
  
  for (hp=holidays, dy=0; dy < 366; dy++, hp++)
  {
      hp->color = 0;
      if (hp->string) {
        if (!hp->dup )
              free(hp->string);
          hp->string = 0;
      }
      {
      struct holiday *nx = hp->next;
      hp->next = 0;
      while (nx) {
        struct holiday *nxtmp;
        if ( nx->string && !nx->dup ) {
          free( nx->string );
        }
        nxtmp=nx;
        nx = nxtmp->next;
        free( nxtmp );
      }
      }
  }
  /*  for (hp=sm_holiday, d=0; d < 366; d++, hp++)
      if (hp->string) {
      if (!hp->dup)
      free(hp->string);
      hp->string      = 0;
      }*/

  filename = holidayfile;
  if (access(filename, R_OK)) return(0);
  kcalin = fopen(filename, "r");
  if (!kcalin) return(0);
  *errormsg = 0;
  kcallineno = 0;
  kcalparse();
  if (piped) pclose(kcalin);
  else fclose(kcalin);
  if (*errormsg) return(errormsg);

  return(0);
}

