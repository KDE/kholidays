/* A Bison parser, made from parseholiday.y
   by GNU bison 1.35.  */

#define YYBISON 1  /* Identify Bison output.  */

#define yyparse kcalparse
#define yylex kcallex
#define yyerror kcalerror
#define yylval kcallval
#define yychar kcalchar
#define yydebug kcaldebug
#define yynerrs kcalnerrs
# define	NUMBER	257
# define	MONTH	258
# define	WDAY	259
# define	COLOR	260
# define	STRING	261
# define	IN	262
# define	PLUS	263
# define	MINUS	264
# define	SMALL	265
# define	CYEAR	266
# define	LEAPYEAR	267
# define	LENGTH	268
# define	EASTER	269
# define	EQ	270
# define	NE	271
# define	LE	272
# define	GE	273
# define	LT	274
# define	GT	275
# define	OR	276
# define	AND	277
# define	UMINUS	278

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
 * Taken from plan by Thomas Driemeyer (thomas@bitrot.de)
 * Adapted for use in KOrganizer by Preston Brown (pbrown@kde.org)
 */

#include <config.h>

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

/**** Private forward declarations ****/
extern int       kcallex(void);          /* external lexical analyzer */
static void      kcalerror(char *s);
static time_t    date_to_time(int day, int month, int year, 
			      int *wkday, int *julian, int *weeknum);
static time_t    tm_to_time(struct tm *tm);
static int	 day_from_name(char *str);
static int	 day_from_easter(void);
static int	 day_from_monthday(int m, int d);
static int	 day_from_wday(int day, int wday, int num);
static void	 monthday_from_day(int day, int *m, int *d, int *y);
static int	 calc_easter();
static void      setliteraldate();
static void      seteaster();
static void      setdate(int month, int day, int year, int off, int length);
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

struct holiday {
  char            *string;        /* name of holiday, 0=not a holiday */
  int             color;
  unsigned short  dup;            /* reference count */
};

struct holiday	 holiday[366];		/* info for each day, separate for */
/*struct holiday   sm_holiday[366];*/	/* full-line texts under, and small */
					/* texts next to day number */

#line 101 "parseholiday.y"
#ifndef YYSTYPE
typedef union { int ival; char *sval; } yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif
#ifndef YYDEBUG
# define YYDEBUG 0
#endif



#define	YYFINAL		121
#define	YYFLAG		-32768
#define	YYNTBASE	38

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 278 ? yytranslate[x] : 51)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    29,     2,     2,     2,    28,     2,     2,
      36,    37,    26,    25,     2,    24,    33,    27,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    32,     2,
       2,     2,     2,    31,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    34,     2,    35,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    30
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     1,     2,    10,    11,    13,    14,    16,    20,
      24,    28,    33,    40,    46,    47,    50,    53,    54,    57,
      61,    66,    72,    76,    82,    85,    89,    92,    96,   101,
     103,   105,   107,   111,   116,   120,   123,   126,   130,   135,
     137,   139,   141,   145,   149,   153,   157,   161,   165,   169,
     173,   177,   181,   185,   189,   193,   199,   202,   206,   210,
     212,   214,   217,   219
};
static const short yyrhs[] =
{
      -1,     0,    38,    40,    41,     7,    41,    39,    42,     0,
       0,    11,     0,     0,     6,     0,    15,    43,    44,     0,
      45,    43,    44,     0,     5,    43,    44,     0,    49,     5,
      43,    44,     0,    49,     5,     8,    47,    43,    44,     0,
       5,    49,    45,    43,    44,     0,     0,     9,    48,     0,
      10,    48,     0,     0,    14,    48,     0,    49,    33,    47,
       0,    49,    33,    47,    33,     0,    49,    33,    47,    33,
      48,     0,    47,    27,    49,     0,    47,    27,    49,    27,
      49,     0,     4,    49,     0,     4,    49,    49,     0,    49,
       4,     0,    49,     4,    49,     0,    49,    33,     4,    49,
       0,    49,     0,     7,     0,    15,     0,    49,    33,    47,
       0,    49,    33,    47,    33,     0,    47,    27,    49,     0,
      49,     4,     0,     4,    49,     0,     5,    49,    49,     0,
      49,     5,     8,    47,     0,     4,     0,    49,     0,    49,
       0,    48,    22,    48,     0,    48,    23,    48,     0,    48,
      16,    48,     0,    48,    17,    48,     0,    48,    18,    48,
       0,    48,    19,    48,     0,    48,    20,    48,     0,    48,
      21,    48,     0,    48,    25,    48,     0,    48,    24,    48,
       0,    48,    26,    48,     0,    48,    27,    48,     0,    48,
      28,    48,     0,    48,    31,    48,    32,    48,     0,    29,
      48,     0,    34,    46,    35,     0,    36,    48,    37,     0,
      50,     0,     3,     0,    24,     3,     0,    12,     0,    13,
      49,     0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,   120,   121,   121,   127,   128,   131,   132,   135,   136,
     137,   138,   139,   140,   143,   144,   145,   148,   149,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     166,   167,   168,   170,   172,   174,   176,   178,   180,   186,
     186,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   207,   208,
     211,   212,   213,   214
};
#endif


#if (YYDEBUG) || defined YYERROR_VERBOSE

/* YYTNAME[TOKEN_NUM] -- String name of the token TOKEN_NUM. */
static const char *const yytname[] =
{
  "$", "error", "$undefined.", "NUMBER", "MONTH", "WDAY", "COLOR", "STRING", 
  "IN", "PLUS", "MINUS", "SMALL", "CYEAR", "LEAPYEAR", "LENGTH", "EASTER", 
  "EQ", "NE", "LE", "GE", "LT", "GT", "OR", "AND", "'-'", "'+'", "'*'", 
  "'/'", "'%'", "'!'", "UMINUS", "'?'", "':'", "'.'", "'['", "']'", "'('", 
  "')'", "list", "@1", "small", "color", "entry", "offset", "length", 
  "date", "reldate", "month", "expr", "pexpr", "number", 0
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,    38,    39,    38,    40,    40,    41,    41,    42,    42,
      42,    42,    42,    42,    43,    43,    43,    44,    44,    45,
      45,    45,    45,    45,    45,    45,    45,    45,    45,    45,
      46,    46,    46,    46,    46,    46,    46,    46,    46,    47,
      47,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    48,    48,    49,    49,
      50,    50,    50,    50
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     0,     0,     7,     0,     1,     0,     1,     3,     3,
       3,     4,     6,     5,     0,     2,     2,     0,     2,     3,
       4,     5,     3,     5,     2,     3,     2,     3,     4,     1,
       1,     1,     3,     4,     3,     2,     2,     3,     4,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     5,     2,     3,     3,     1,
       1,     2,     1,     2
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       1,     4,     5,     6,     7,     0,     6,     2,     0,    60,
      39,    14,    62,     0,    14,     0,     0,     3,    14,     0,
      29,    59,    24,     0,     0,    17,     0,    63,    17,    61,
       0,     0,     0,    41,    17,     0,    26,    14,     0,    25,
      15,    16,     0,    10,    14,    29,     8,    56,    39,     0,
      30,    31,     0,     0,    40,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    58,
       9,    22,    27,     0,    17,    39,    19,    40,    18,    17,
      36,     0,    57,     0,    35,     0,     0,    44,    45,    46,
      47,    48,    49,    42,    43,    51,    50,    52,    53,    54,
       0,     0,    39,    14,    11,    28,    20,    13,    37,    34,
       0,    32,     0,    23,    17,    21,    38,    33,    55,    12,
       0,     0
};

static const short yydefgoto[] =
{
       1,     8,     3,     5,    17,    25,    43,    18,    52,    19,
      32,    33,    21
};

static const short yypact[] =
{
  -32768,    11,-32768,    -5,-32768,    -3,    -5,-32768,    84,-32768,
     142,    97,-32768,   142,    15,    17,   110,-32768,    15,    -6,
       2,-32768,   142,   110,   110,    20,   125,-32768,    20,-32768,
     110,    79,   165,-32768,    20,   142,   142,     7,   139,-32768,
     204,   204,   110,-32768,    15,     6,-32768,     5,   142,   142,
  -32768,-32768,     8,    37,     4,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,-32768,
  -32768,    39,-32768,   144,    20,   142,    38,-32768,   204,    20,
  -32768,   142,-32768,   142,-32768,    62,   144,   236,   236,   236,
     236,   236,   236,   220,   236,    32,    32,     5,     5,     5,
     187,   142,-32768,    15,-32768,-32768,   110,-32768,-32768,-32768,
     144,    41,   110,-32768,    20,   204,-32768,-32768,-32768,-32768,
      76,-32768
};

static const short yypgoto[] =
{
  -32768,-32768,-32768,    73,-32768,    24,    -2,    54,-32768,    31,
     -11,    -8,-32768
};


#define	YYLAST		267


static const short yytable[] =
{
      20,     4,    22,    26,     6,    27,    36,    37,    84,    85,
      36,   120,    40,    41,    39,    73,    23,    24,    45,    47,
      29,    35,     2,    54,    23,    24,    46,    71,    72,   -40,
      77,    78,    70,   -40,    42,    38,    68,    86,    28,    38,
      80,    81,    34,    82,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,    65,    66,
      67,    74,    53,    68,    83,    77,   101,   105,    79,    76,
     110,   106,   104,   108,   117,   109,   121,   107,    77,     7,
      44,     0,     9,    48,    49,     0,    50,     9,    10,    11,
       0,    12,    13,   113,    51,   115,    12,    13,     0,    14,
       9,   118,    77,    15,   103,     0,    23,    24,    15,    12,
      13,     0,   119,     9,     0,    16,     0,   111,     0,     0,
      16,    15,    12,    13,     0,     0,     0,   114,     9,    10,
       0,     0,     0,    16,    15,     0,     0,    12,    13,    30,
       0,   116,     9,    75,    31,     9,    16,     9,   102,    15,
       0,    12,    13,     0,    12,    13,    12,    13,     0,     0,
       0,    16,     0,    15,     0,     0,    15,     0,    15,     0,
       0,     0,     0,     0,     0,    16,     0,     0,    16,     0,
      16,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,     0,     0,    68,     0,     0,     0,
       0,     0,    69,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,     0,     0,    68,   112,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,     0,     0,    68,    55,    56,    57,    58,
      59,    60,     0,    62,    63,    64,    65,    66,    67,     0,
       0,    68,    55,    56,    57,    58,    59,    60,     0,     0,
      63,    64,    65,    66,    67,     0,     0,    68
};

static const short yycheck[] =
{
       8,     6,    10,    11,     7,    13,     4,     5,     4,     5,
       4,     0,    23,    24,    22,     8,     9,    10,    26,    30,
       3,    27,    11,    31,     9,    10,    28,    35,    36,    27,
      38,    42,    34,    27,    14,    33,    31,    33,    14,    33,
      48,    49,    18,    35,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    26,    27,
      28,    37,    31,    31,    27,    73,    27,    75,    44,    38,
       8,    33,    74,    81,    33,    83,     0,    79,    86,     6,
      26,    -1,     3,     4,     5,    -1,     7,     3,     4,     5,
      -1,    12,    13,   101,    15,   106,    12,    13,    -1,    15,
       3,   112,   110,    24,    73,    -1,     9,    10,    24,    12,
      13,    -1,   114,     3,    -1,    36,    -1,    86,    -1,    -1,
      36,    24,    12,    13,    -1,    -1,    -1,   103,     3,     4,
      -1,    -1,    -1,    36,    24,    -1,    -1,    12,    13,    29,
      -1,   110,     3,     4,    34,     3,    36,     3,     4,    24,
      -1,    12,    13,    -1,    12,    13,    12,    13,    -1,    -1,
      -1,    36,    -1,    24,    -1,    -1,    24,    -1,    24,    -1,
      -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,    36,    -1,
      36,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    -1,    -1,    31,    -1,    -1,    -1,
      -1,    -1,    37,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    -1,    -1,    31,    32,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    -1,    -1,    31,    16,    17,    18,    19,
      20,    21,    -1,    23,    24,    25,    26,    27,    28,    -1,
      -1,    31,    16,    17,    18,    19,    20,    21,    -1,    -1,
      24,    25,    26,    27,    28,    -1,    -1,    31
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/share/bison/bison.simple"

/* Skeleton output parser for bison,

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software
   Foundation, Inc.

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
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* This is the parser code that is written into each bison parser when
   the %semantic_parser declaration is not specified in the grammar.
   It was written by Richard Stallman by simplifying the hairy parser
   used when %semantic_parser is specified.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

#if ! defined (yyoverflow) || defined (YYERROR_VERBOSE)

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || defined (YYERROR_VERBOSE) */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYLTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
# if YYLSP_NEEDED
  YYLTYPE yyls;
# endif
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAX (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# if YYLSP_NEEDED
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE) + sizeof (YYLTYPE))	\
      + 2 * YYSTACK_GAP_MAX)
# else
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAX)
# endif

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
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
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAX;	\
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif


#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
#define YYERROR		goto yyerrlab1
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
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");			\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).

   When YYLLOC_DEFAULT is run, CURRENT is set the location of the
   first token.  By default, to implement support for ranges, extend
   its range to the last symbol.  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)       	\
   Current.last_line   = Rhs[N].last_line;	\
   Current.last_column = Rhs[N].last_column;
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#if YYPURE
# if YYLSP_NEEDED
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, &yylloc, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval, &yylloc)
#  endif
# else /* !YYLSP_NEEDED */
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval)
#  endif
# endif /* !YYLSP_NEEDED */
#else /* !YYPURE */
# define YYLEX			yylex ()
#endif /* !YYPURE */


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
} while (0)
/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
#endif /* !YYDEBUG */

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

#ifdef YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif
#endif

#line 315 "/usr/share/bison/bison.simple"


/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
#  define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL
# else
#  define YYPARSE_PARAM_ARG YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
# endif
#else /* !YYPARSE_PARAM */
# define YYPARSE_PARAM_ARG
# define YYPARSE_PARAM_DECL
#endif /* !YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
# ifdef YYPARSE_PARAM
int yyparse (void *);
# else
int yyparse (void);
# endif
#endif

/* YY_DECL_VARIABLES -- depending whether we use a pure parser,
   variables are global, or local to YYPARSE.  */

#define YY_DECL_NON_LSP_VARIABLES			\
/* The lookahead symbol.  */				\
int yychar;						\
							\
/* The semantic value of the lookahead symbol. */	\
YYSTYPE yylval;						\
							\
/* Number of parse errors so far.  */			\
int yynerrs;

#if YYLSP_NEEDED
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES			\
						\
/* Location data for the lookahead symbol.  */	\
YYLTYPE yylloc;
#else
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES
#endif


/* If nonreentrant, generate the variables here. */

#if !YYPURE
YY_DECL_VARIABLES
#endif  /* !YYPURE */

int
yyparse (YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  /* If reentrant, generate the variables here. */
#if YYPURE
  YY_DECL_VARIABLES
#endif  /* !YYPURE */

  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yychar1 = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack. */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;

#if YYLSP_NEEDED
  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
#endif

#if YYLSP_NEEDED
# define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
# define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  YYSIZE_T yystacksize = YYINITDEPTH;


  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
#if YYLSP_NEEDED
  YYLTYPE yyloc;
#endif

  /* When reducing, the number of symbols on the RHS of the reduced
     rule. */
  int yylen;

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
#if YYLSP_NEEDED
  yylsp = yyls;
#endif
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  */
# if YYLSP_NEEDED
	YYLTYPE *yyls1 = yyls;
	/* This used to be a conditional around just the two extra args,
	   but that might be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
# else
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);
# endif
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
# if YYLSP_NEEDED
	YYSTACK_RELOCATE (yyls);
# endif
# undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
#if YYLSP_NEEDED
      yylsp = yyls + yysize - 1;
#endif

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yychar1 = YYTRANSLATE (yychar);

#if YYDEBUG
     /* We have to keep this `#if YYDEBUG', since we use variables
	which are defined only if `YYDEBUG' is set.  */
      if (yydebug)
	{
	  YYFPRINTF (stderr, "Next token is %d (%s",
		     yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise
	     meaning of a token, for further debugging info.  */
# ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
# endif
	  YYFPRINTF (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %d (%s), ",
	      yychar, yytname[yychar1]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
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

     Otherwise, the following line sets YYVAL to the semantic value of
     the lookahead token.  This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

#if YYLSP_NEEDED
  /* Similarly for the default location.  Let the user run additional
     commands if for instance locations are ranges.  */
  yyloc = yylsp[1-yylen];
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
#endif

#if YYDEBUG
  /* We have to keep this `#if YYDEBUG', since we use variables which
     are defined only if `YYDEBUG' is set.  */
  if (yydebug)
    {
      int yyi;

      YYFPRINTF (stderr, "Reducing via rule %d (line %d), ",
		 yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (yyi = yyprhs[yyn]; yyrhs[yyi] > 0; yyi++)
	YYFPRINTF (stderr, "%s ", yytname[yyrhs[yyi]]);
      YYFPRINTF (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif

  switch (yyn) {

case 2:
#line 121 "parseholiday.y"
{ yacc_stringcolor = yyvsp[-2].ival;
						  yacc_string	= yyvsp[-1].sval;
						  yacc_daycolor	= yyvsp[0].ival; ;
    break;}
case 3:
#line 124 "parseholiday.y"
{ free(yacc_string); ;
    break;}
case 4:
#line 127 "parseholiday.y"
{ yacc_small = 0; ;
    break;}
case 5:
#line 128 "parseholiday.y"
{ yacc_small = 1; ;
    break;}
case 6:
#line 131 "parseholiday.y"
{ yyval.ival = 0; ;
    break;}
case 7:
#line 132 "parseholiday.y"
{ yyval.ival = yyvsp[0].ival; ;
    break;}
case 8:
#line 135 "parseholiday.y"
{ seteaster(yyvsp[-1].ival, yyvsp[0].ival); ;
    break;}
case 9:
#line 136 "parseholiday.y"
{ setdate( m,  d,  y, yyvsp[-1].ival, yyvsp[0].ival);;
    break;}
case 10:
#line 137 "parseholiday.y"
{ setwday( 0, yyvsp[-2].ival,  0, yyvsp[-1].ival, yyvsp[0].ival);;
    break;}
case 11:
#line 138 "parseholiday.y"
{ setwday(yyvsp[-3].ival, yyvsp[-2].ival,  0, yyvsp[-1].ival, yyvsp[0].ival);;
    break;}
case 12:
#line 139 "parseholiday.y"
{ setwday(yyvsp[-5].ival, yyvsp[-4].ival, yyvsp[-2].ival, yyvsp[-1].ival, yyvsp[0].ival);;
    break;}
case 13:
#line 140 "parseholiday.y"
{ setdoff(yyvsp[-4].ival, yyvsp[-3].ival,m,d,y,yyvsp[-1].ival,yyvsp[0].ival);;
    break;}
case 14:
#line 143 "parseholiday.y"
{ yyval.ival =	0; ;
    break;}
case 15:
#line 144 "parseholiday.y"
{ yyval.ival =	yyvsp[0].ival; ;
    break;}
case 16:
#line 145 "parseholiday.y"
{ yyval.ival = -yyvsp[0].ival; ;
    break;}
case 17:
#line 148 "parseholiday.y"
{ yyval.ival =	1; ;
    break;}
case 18:
#line 149 "parseholiday.y"
{ yyval.ival =	yyvsp[0].ival; ;
    break;}
case 19:
#line 152 "parseholiday.y"
{ m = yyvsp[0].ival; d = yyvsp[-2].ival; y = 0;  ;
    break;}
case 20:
#line 153 "parseholiday.y"
{ m = yyvsp[-1].ival; d = yyvsp[-3].ival; y = 0;  ;
    break;}
case 21:
#line 154 "parseholiday.y"
{ m = yyvsp[-2].ival; d = yyvsp[-4].ival; y = yyvsp[0].ival; ;
    break;}
case 22:
#line 155 "parseholiday.y"
{ m = yyvsp[-2].ival; d = yyvsp[0].ival; y = 0;  ;
    break;}
case 23:
#line 156 "parseholiday.y"
{ m = yyvsp[-4].ival; d = yyvsp[-2].ival; y = yyvsp[0].ival; ;
    break;}
case 24:
#line 157 "parseholiday.y"
{ m = yyvsp[-1].ival; d = yyvsp[0].ival; y = 0;  ;
    break;}
case 25:
#line 158 "parseholiday.y"
{ m = yyvsp[-2].ival; d = yyvsp[-1].ival; y = yyvsp[0].ival; ;
    break;}
case 26:
#line 159 "parseholiday.y"
{ m = yyvsp[0].ival; d = yyvsp[-1].ival; y = 0;  ;
    break;}
case 27:
#line 160 "parseholiday.y"
{ m = yyvsp[-1].ival; d = yyvsp[-2].ival; y = yyvsp[0].ival; ;
    break;}
case 28:
#line 161 "parseholiday.y"
{ m = yyvsp[-1].ival; d = yyvsp[-3].ival; y = yyvsp[0].ival; ;
    break;}
case 29:
#line 162 "parseholiday.y"
{ monthday_from_day(yyvsp[0].ival,
								 &m, &d, &y); ;
    break;}
case 30:
#line 166 "parseholiday.y"
{ yyval.ival = day_from_name(yyvsp[0].sval); ;
    break;}
case 31:
#line 167 "parseholiday.y"
{ yyval.ival = day_from_easter(); ;
    break;}
case 32:
#line 168 "parseholiday.y"
{ yyval.ival = day_from_monthday
								 (yyvsp[0].ival, yyvsp[-2].ival); ;
    break;}
case 33:
#line 170 "parseholiday.y"
{ yyval.ival = day_from_monthday
								 (yyvsp[-1].ival, yyvsp[-3].ival); ;
    break;}
case 34:
#line 172 "parseholiday.y"
{ yyval.ival = day_from_monthday
								 (yyvsp[-2].ival, yyvsp[0].ival); ;
    break;}
case 35:
#line 174 "parseholiday.y"
{ yyval.ival = day_from_monthday
								 (yyvsp[0].ival, yyvsp[-1].ival); ;
    break;}
case 36:
#line 176 "parseholiday.y"
{ yyval.ival = day_from_monthday
								 (yyvsp[-1].ival, yyvsp[0].ival); ;
    break;}
case 37:
#line 178 "parseholiday.y"
{ yyval.ival = day_from_wday(yyvsp[0].ival, yyvsp[-2].ival,
							 yyvsp[-1].ival == -1 ? -1 : 0); ;
    break;}
case 38:
#line 180 "parseholiday.y"
{ int d=day_from_monthday(yyvsp[0].ival,1);
						   yyval.ival = yyvsp[-3].ival == 999
						    ? day_from_wday(d+1,yyvsp[-2].ival,-1)
						    : day_from_wday(d,yyvsp[-2].ival,yyvsp[-3].ival-1);;
    break;}
case 41:
#line 188 "parseholiday.y"
{ yyval.ival = yyvsp[0].ival; ;
    break;}
case 42:
#line 189 "parseholiday.y"
{ yyval.ival = yyvsp[-2].ival || yyvsp[0].ival; ;
    break;}
case 43:
#line 190 "parseholiday.y"
{ yyval.ival = yyvsp[-2].ival && yyvsp[0].ival; ;
    break;}
case 44:
#line 191 "parseholiday.y"
{ yyval.ival = yyvsp[-2].ival == yyvsp[0].ival; ;
    break;}
case 45:
#line 192 "parseholiday.y"
{ yyval.ival = yyvsp[-2].ival != yyvsp[0].ival; ;
    break;}
case 46:
#line 193 "parseholiday.y"
{ yyval.ival = yyvsp[-2].ival <= yyvsp[0].ival; ;
    break;}
case 47:
#line 194 "parseholiday.y"
{ yyval.ival = yyvsp[-2].ival >= yyvsp[0].ival; ;
    break;}
case 48:
#line 195 "parseholiday.y"
{ yyval.ival = yyvsp[-2].ival <  yyvsp[0].ival; ;
    break;}
case 49:
#line 196 "parseholiday.y"
{ yyval.ival = yyvsp[-2].ival >  yyvsp[0].ival; ;
    break;}
case 50:
#line 197 "parseholiday.y"
{ yyval.ival = yyvsp[-2].ival +  yyvsp[0].ival; ;
    break;}
case 51:
#line 198 "parseholiday.y"
{ yyval.ival = yyvsp[-2].ival -  yyvsp[0].ival; ;
    break;}
case 52:
#line 199 "parseholiday.y"
{ yyval.ival = yyvsp[-2].ival *  yyvsp[0].ival; ;
    break;}
case 53:
#line 200 "parseholiday.y"
{ yyval.ival = yyvsp[0].ival ?  yyvsp[-2].ival / yyvsp[0].ival : 0; ;
    break;}
case 54:
#line 201 "parseholiday.y"
{ yyval.ival = yyvsp[0].ival ?  yyvsp[-2].ival % yyvsp[0].ival : 0; ;
    break;}
case 55:
#line 202 "parseholiday.y"
{ yyval.ival = yyvsp[-4].ival ?  yyvsp[-2].ival : yyvsp[0].ival; ;
    break;}
case 56:
#line 203 "parseholiday.y"
{ yyval.ival = !yyvsp[0].ival; ;
    break;}
case 57:
#line 204 "parseholiday.y"
{ yyval.ival = yyvsp[-1].ival; ;
    break;}
case 58:
#line 207 "parseholiday.y"
{ yyval.ival = yyvsp[-1].ival; ;
    break;}
case 59:
#line 208 "parseholiday.y"
{ yyval.ival = yyvsp[0].ival; ;
    break;}
case 61:
#line 212 "parseholiday.y"
{ yyval.ival = -yyvsp[0].ival; ;
    break;}
case 62:
#line 213 "parseholiday.y"
{ yyval.ival = parse_year; ;
    break;}
case 63:
#line 214 "parseholiday.y"
{ yyval.ival = !((yyvsp[0].ival) & 3); ;
    break;}
}

#line 705 "/usr/share/bison/bison.simple"


  yyvsp -= yylen;
  yyssp -= yylen;
#if YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;
#if YYLSP_NEEDED
  *++yylsp = yyloc;
#endif

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("parse error, unexpected ") + 1;
	  yysize += yystrlen (yytname[YYTRANSLATE (yychar)]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "parse error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[YYTRANSLATE (yychar)]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx)
		      {
			const char *yyq = ! yycount ? ", expecting " : " or ";
			yyp = yystpcpy (yyp, yyq);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yycount++;
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exhausted");
	}
      else
#endif /* defined (YYERROR_VERBOSE) */
	yyerror ("parse error");
    }
  goto yyerrlab1;


/*--------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action |
`--------------------------------------------------*/
yyerrlab1:
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;
      YYDPRINTF ((stderr, "Discarding token %d (%s).\n",
		  yychar, yytname[yychar1]));
      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;


/*-------------------------------------------------------------------.
| yyerrdefault -- current state does not do anything special for the |
| error token.                                                       |
`-------------------------------------------------------------------*/
yyerrdefault:
#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */

  /* If its default is to accept any token, ok.  Otherwise pop it.  */
  yyn = yydefact[yystate];
  if (yyn)
    goto yydefault;
#endif


/*---------------------------------------------------------------.
| yyerrpop -- pop the current state because it cannot handle the |
| error token                                                    |
`---------------------------------------------------------------*/
yyerrpop:
  if (yyssp == yyss)
    YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#if YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "Error: state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

/*--------------.
| yyerrhandle.  |
`--------------*/
yyerrhandle:
  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

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

/*---------------------------------------------.
| yyoverflowab -- parser overflow comes here.  |
`---------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}
#line 216 "parseholiday.y"

	 
/*** Private Yacc callbacks and helper functions ***/
static void kcalerror(char *msg)
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
  time_t                  time;
  
  tm.tm_sec   = 0;
  tm.tm_min   = 0;
  tm.tm_hour  = 0;
  tm.tm_mday  = day;
  tm.tm_mon   = month;
  tm.tm_year  = year;
  time = tm_to_time(&tm);
  if (wkday)
    *wkday   = tm.tm_wday;
  if (julian)
    *julian  = tm.tm_yday;
  if (weeknum)
    *weeknum = 0
      ? tm.tm_yday / 7
      : tm.tm_yday ? ((tm.tm_yday - 1) /7) + 1 : 0;
  return(time == -1 || day != tm.tm_mday ? 0 : time);
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
  int		m, n, d, l, mlen, wday1;
  int		dup = 0;
  
  if (month != ANY)
    min_month = max_month = month-1;
  if (month == LAST)
    min_month = max_month = 11;
  if (num != ANY)
    min_num = max_num = num-1;
  
  holiday_name = yacc_string;
  for (m=min_month; m <= max_month; m++) {
    (void)date_to_time(1, m, parse_year, &wday1, 0, 0);
    d = (wday-1 - (wday1-1) +7) % 7 + 1;
    mlen = monthlen[m] + (m==1 && ISLEAPYEAR(parse_year));
    if (num == LAST)
      for (l=0; l < length; l++)
	setliteraldate(m, d+28<=mlen ? d+28 : d+21,
		       off+l, &dup);
    else
      for (d+=min_num*7, n=min_num; n <= max_num; n++, d+=7)
	if (d >= 1 && d <= mlen)
	  for (l=0; l < length; l++)
	    setliteraldate(m,d,off+l,&dup);
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
  int		m, d, nd, l, wday1;
  int		dup = 0;
  
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
  for (m=min_month; m <= max_month; m++)
    if (day == LAST) {
      (void)date_to_time(monthlen[m], m, parse_year,
			 &wday1, 0, 0);
      nd = (((wday - wday1 + 7) % 7) -
	    ((rel == BEFORE) ? 7 : 0)) % 7;
      for (l=0; l < length; l++)
	setliteraldate(m,monthlen[m]+nd, off+l, &dup);
    } else
      for (d=min_day; d <= max_day; d++) {
	(void)date_to_time(d, m, parse_year,
			   &wday1, 0, 0);
	nd = (((wday - wday1 + 7) % 7) -
	      ((rel == BEFORE) ? 7 : 0)) % 7;
	for (l=0; l < length; l++)
	  setliteraldate(m, d+nd, off+l, &dup);
      }
}


/*
 * set holiday by date. Ignore holidays in the wrong year. The code is
 * complicated by expressions such as "any/last/any" (every last day of
 * the month).
 */

static void setdate(int month, int day, int year, int off, int length)
{
  int		min_month = 0, max_month = 11;
  int		min_day   = 1, max_day   = 31;
  int		m, d, l;
  int		dup = 0;
  
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
  for (m=min_month; m <= max_month; m++)
    if (day == LAST)
      for (l=0; l < length; l++)
	setliteraldate(m, monthlen[m], off+l, &dup);
    else
      for (d=min_day; d <= max_day; d++)
	for (l=0; l < length; l++)
	  setliteraldate(m, d, off+l, &dup);
}


/*
 * After the two routines above have removed ambiguities (ANY) and resolved
 * weekday specifications, this routine registers the holiday in the holiday
 * array. There are two of these, for full-line holidays (they take away one
 * appointment line in the month calendar daybox) and "small" holidays, which
 * appear next to the day number. If the day is already some other holiday,
 * ignore the new one. <dup> is information stored for parse_holidays(), it
 * will free() the holiday name only if its dup field is 0 (because many
 * string fields can point to the same string, which was allocated only once
 * by the lexer, and should therefore only be freed once).
 */

static void setliteraldate(int month, int day, int off, int *dup)
{
  int julian = JULIAN(month, day) + off;
  /*  struct holiday *hp = yacc_small ? &sm_holiday[julian]
      : &holiday[julian]; */
  struct holiday *hp = &holiday[julian];

  if (julian >= 0 && julian <= 365 && !hp->string) {
    if (!*dup)
      holiday_name = strdup(holiday_name);
    hp->string	= holiday_name;
    hp->color   = (yacc_stringcolor == 0) ? yacc_daycolor : yacc_stringcolor;
    hp->dup		= (*dup)++;
  }
}


/*
 * set a holiday relative to Easter
 */

static void seteaster(int off, int length)
{
  int		dup = 0;	/* flag for later free() */
  int julian = easter_julian + off;
  /*  struct holiday *hp = yacc_small ? &sm_holiday[julian]
      : &holiday[julian];*/
  struct holiday *hp = &holiday[julian];
  
  holiday_name = yacc_string;
  while (length-- > 0) {
    if (julian >= 0 && julian <= 365 && !hp->string) {
      if (!dup)
	holiday_name = strdup(holiday_name);
      hp->string	= holiday_name;
      hp->color     = (yacc_stringcolor == 0) ? yacc_daycolor : yacc_stringcolor;
      hp->dup		= dup++;
    }
    julian++, hp++;
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
 * day_from_monthday (m, d)		gets <day> from <month/day>
 * day_from_wday (day, wday, num)	gets num-th day (wday) after <day> day
 * monthday_from_day (day, *m, *d, *y)	gets month/day/cur_year from <day>
 */

static int day_from_name(char *str)
{
  int	i;
  char	*name;
  
  for (i=0; i < 366; i++) {
    name = holiday[i].string;
    if (name && !strcmp(str, name))
      return(i);
  }
  return(-1);
}


static int day_from_easter(void)
{
  return(easter_julian);
}


static int day_from_monthday(int m, int d)
{
  if (m == 13)
    return(365 + ISLEAPYEAR(parse_year));
  return(JULIAN(m - 1, d));
}


static void monthday_from_day(int day, int *m, int *d, int *y)
{
  int	i, len;
  
  *y = parse_year;
  *m = 0;
  *d = 0;
  if (day < 0)
    return;
  for (i=0; i < 12; i++) {
    len = monthlen[i] + (i == 1 && ISLEAPYEAR(parse_year));
    if (day < len) {
      *m = i + 1;
      *d = day + 1;
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

static char *resolve_tilde(char *path)
{
  struct passwd   *pw;                    /* for searching home dirs */
  static char     pathbuf[512];           /* path with ~ expanded */
  char            *p, *q;                 /* username copy pointers */
  char            *home = 0;              /* home dir (if ~ in path) */
  
  if (*path != '~')
    return(path);
  
  if (!path[1] || path[1] == '/') {
    *pathbuf = 0;
    if (!(home = getenv("HOME")))
      home = getenv("home");
  } else {
    for (p=path+1, q=pathbuf; *p && *p != '/'; p++, q++)
      *q = *p;
    *q = 0;
    if ((pw = getpwnam(pathbuf)))
      home = pw->pw_dir;
  }
  if (!home) {
    fprintf(stderr, "%s: can't evaluate ~%s in %s, using .\n",
	    progname, pathbuf, path);
    home = ".";
  }
  sprintf(pathbuf, "%s/%s", home, path+1);
  return(pathbuf);
}

/*** Public Functions ***/
/*
 * parse the holiday text file, and set up the holiday arrays for a year.
 * If year is -1, re-parse the last year parsed (this is used when the
 * holiday file changes). If there is a CPP_PATH, check if the executable
 * really exists, and if so, pipe the holioday files through it.
 * Return an error message if an error occurred, 0 otherwise.
 */

char *parse_holidays(const char *holidays, int year, short force)
{
  register struct holiday *hp;
  register int		d, n;
  short			piped = 0;
  char			buf[200];
  char *kdedir;

  if (year == parse_year && !force)
      return(0);
  if (year < 0)
      year = parse_year;
  parse_year = year;
  easter_julian = calc_easter(year + 1900);
  
  for (hp=holiday, d=0; d < 366; d++, hp++)
  {
      hp->color = 0;
      if (hp->string) {
	  if (!hp->dup)
	      free(hp->string);
	  hp->string      = 0;
      }
  }
  /*  for (hp=sm_holiday, d=0; d < 366; d++, hp++)
      if (hp->string) {
      if (!hp->dup)
      free(hp->string);
      hp->string      = 0;
      }*/

  filename = holidays;
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
