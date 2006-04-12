#ifndef lint
static char const 
yyrcsid[] = "$FreeBSD: src/usr.bin/yacc/skeleton.c,v 1.28 2000/01/17 02:04:06 bde Exp $";
#endif
#include <stdlib.h>
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYLEX yylex()
#define YYEMPTY -1
#define yyclearin (yychar=(YYEMPTY))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING() (yyerrflag!=0)
static int yygrowstack();
#define yyparse kcalparse
#define yylex kcallex
#define yyerror kcalerror
#define yychar kcalchar
#define yyval kcalval
#define yylval kcallval
#define yydebug kcaldebug
#define yynerrs kcalnerrs
#define yyerrflag kcalerrflag
#define yyss kcalss
#define yyssp kcalssp
#define yyvs kcalvs
#define yyvsp kcalvsp
#define yylhs kcallhs
#define yylen kcallen
#define yydefred kcaldefred
#define yydgoto kcaldgoto
#define yysindex kcalsindex
#define yyrindex kcalrindex
#define yygindex kcalgindex
#define yytable kcaltable
#define yycheck kcalcheck
#define yyname kcalname
#define yyrule kcalrule
#define yysslim kcalsslim
#define yystacksize kcalstacksize
#define YYPREFIX "kcal"
#line 2 "parseholiday.y"
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
#line 102 "parseholiday.y"
typedef union { int ival; char *sval; } YYSTYPE;
#line 144 "parseholiday.c"
#define YYERRCODE 256
#define NUMBER 257
#define MONTH 258
#define WDAY 259
#define COLOR 260
#define STRING 261
#define IN 262
#define PLUS 263
#define MINUS 264
#define SMALL 265
#define CYEAR 266
#define LEAPYEAR 267
#define LENGTH 268
#define EASTER 269
#define EQ 270
#define NE 271
#define LE 272
#define GE 273
#define LT 274
#define GT 275
#define OR 276
#define AND 277
#define UMINUS 278
const short kcallhs[] = {                                        -1,
    0,   11,    0,    9,    9,    1,    1,   10,   10,   10,
   10,   10,   10,    2,    2,    2,    3,    3,   12,   12,
   12,   12,   12,   12,   12,   12,   12,   12,   12,    8,
    8,    8,    8,    8,    8,    8,    8,    8,    7,    7,
    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,
    4,    4,    4,    4,    4,    4,    4,    5,    5,    6,
    6,    6,    6,
};
const short kcallen[] = {                                         2,
    0,    0,    7,    0,    1,    0,    1,    3,    3,    3,
    4,    6,    5,    0,    2,    2,    0,    2,    3,    4,
    5,    3,    5,    2,    3,    2,    3,    4,    1,    1,
    1,    3,    4,    3,    2,    2,    3,    4,    1,    1,
    1,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    5,    2,    3,    3,    1,    1,
    2,    1,    2,
};
const short kcaldefred[] = {                                      1,
    0,    5,    0,    7,    0,    0,    2,    0,   60,    0,
    0,   62,    0,    0,    0,    0,    0,   59,    0,    3,
    0,    0,    0,    0,    0,    0,   63,    0,   61,    0,
    0,    0,   41,    0,    0,    0,    0,    0,   25,    0,
    0,    0,   10,    0,    0,    8,    0,    0,    0,   30,
   31,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   58,   27,
    0,    0,    0,   40,    0,    0,    9,    0,    0,   36,
    0,   35,    0,    0,    0,   57,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   39,    0,   11,   28,    0,    0,   13,   37,    0,    0,
   34,    0,    0,    0,   23,   38,   33,   55,   12,
};
const short kcaldgoto[] = {                                       1,
    5,   25,   43,   32,   33,   18,   19,   54,    3,   20,
    8,   21,
};
const short kcalsindex[] = {                                      0,
 -260,    0, -251,    0, -244, -251,    0,  390,    0,  -10,
  -37,    0,  -10, -250, -229,  -33,  -42,    0,  -14,    0,
 -250,  -10,  -33,  -33, -237,  -16,    0, -237,    0,  -33,
  366,  513,    0,  -10, -242,  473,  -10, -237,    0,  536,
  536,  -33,    0,  -44, -250,    0,  -29,  -10,  -10,    0,
    0,  -23,  -11,  -53,  -33,  -33,  -33,  -33,  -33,  -33,
  -33,  -33,  -33,  -33,  -33,  -33,  -33,  -33,    0,    0,
  479, -237,  -10,    0,   -5,   -2,    0,  536, -237,    0,
  -10,    0, -215,  479,  -10,    0,  558,  558,  558,  558,
  558,  558,  545,  558,  -31,  -31,  -29,  -29,  -29,  522,
    0, -250,    0,    0,  -33,  -10,    0,    0,  479,    5,
    0,  -33, -237,  536,    0,    0,    0,    0,    0,
};
const short kcalrindex[] = {                                      0,
 -234,    0, -244,    0,    0,  414,    0,    0,    0,    6,
  249,    0,    0,  249,    0,    0,  201,    0,    0,    0,
  249,  213,    0,    0,  281,    0,    0,  281,    0,    0,
    0,    0,    0,  219,  249,    0,    0,  281,    0,  255,
  267,    0,    0,  201,  249,    0,    1,    6,    0,    0,
    0,    7,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  281,  207,    0,  225,  231,    0,  288,  281,    0,
    0,    0,    0,    0,    0,    0,  109,  115,  133,  139,
  157,  163,  187,  181,   73,   91,   19,   37,   55,    0,
    0,  249,    0,    0,  237,    0,    0,    0,    0,  -41,
    0,    0,  281,  243,    0,    0,    0,    0,    0,
};
const short kcalgindex[] = {                                      0,
   59,    4,   29,  661,  629,    0,  -21,    0,    0,    0,
    0,   42,
};
#define YYTABLESIZE 833
const short kcaltable[] = {                                      30,
   56,   36,   16,   36,    2,   67,   16,   15,    4,   53,
   65,   15,   23,   24,   75,   66,    6,   28,   52,   71,
   23,   24,   84,   16,   38,    4,    4,   29,   15,   16,
   42,   68,   37,   68,   15,   85,   53,   56,   72,   86,
  105,   56,   56,   56,  106,   56,  109,   56,   79,  102,
  117,   32,   39,   40,   54,   52,   46,   31,   56,   52,
   52,   52,  110,   52,    7,   52,   77,   45,    0,    0,
    0,    0,   51,   53,    0,    0,   52,   53,   53,   53,
    0,   53,    0,   53,    0,    0,    0,  116,    0,    0,
   50,   54,    0,    0,   53,   54,   54,   54,    0,   54,
  103,   54,    0,    0,    0,  113,    0,  107,   44,    0,
    0,    0,   54,   51,   45,   51,    0,   51,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   51,   50,   46,   50,    0,   50,    0,    0,   47,    0,
    0,  119,    0,    0,    0,    0,    0,    0,   50,   44,
    0,    0,    0,    0,    0,   45,   48,    0,    0,    0,
    0,    0,   49,    0,    0,    0,   44,    0,    0,    0,
    0,    0,   45,   46,    0,    0,    0,    0,    0,   47,
   43,    0,    0,    0,    0,    0,   42,    0,    0,    0,
   46,    0,    0,    0,    0,    0,   47,   48,    0,    0,
   29,    0,    0,   49,    0,    0,   39,    0,    0,    0,
    0,    0,   24,   34,   48,   34,   35,    0,   26,    9,
   49,   43,    0,    9,   19,   23,   24,   42,   12,   13,
   22,    0,   12,   13,   82,   83,   20,    0,   43,    0,
    9,   10,   21,    0,   42,    0,    9,   40,   14,   12,
   13,    0,   39,    0,   15,   12,   13,    0,    0,    0,
   56,   56,    0,   56,   56,   56,   16,    0,   56,    0,
   56,   56,   56,   56,   56,   56,   56,   56,   52,   52,
   17,   52,   52,   52,    0,    0,   52,   18,   52,   52,
   52,   52,   52,   52,   52,   52,   53,   53,    0,   53,
   53,   53,    0,    0,   53,    0,   53,   53,   53,   53,
   53,   53,   53,   53,   54,   54,    0,   54,   54,   54,
    0,    0,   54,    0,   54,   54,   54,   54,   54,   54,
   54,   54,   51,   51,    0,   51,   51,   51,    0,    0,
   51,    0,   51,   51,   51,   51,   51,   51,   51,   51,
   50,   50,    0,   50,   50,   50,    0,    0,   50,    0,
   50,   50,   50,   50,   50,   50,   50,   50,   44,   44,
    0,   44,   44,   44,   45,   45,   44,   45,   45,   45,
    0,    0,   45,    0,   44,   44,    0,    0,    0,    0,
   45,   45,   46,   46,    0,   46,   46,   46,   47,   47,
   46,   47,   47,   47,    0,   16,   47,    0,   46,   46,
   15,    0,    0,    0,   47,   47,   48,   48,    0,   48,
   48,   48,   49,   49,   48,   49,   49,   49,    0,   16,
   49,    0,   48,   48,   15,    0,    0,    0,   49,   49,
   43,   43,    0,   43,   43,   43,   42,   42,   43,   42,
   42,   42,    0,    6,   42,    0,   43,   43,    6,    0,
   29,   29,   42,   29,   29,   29,   39,   39,   29,   39,
   39,   39,   24,   24,   39,   24,   24,   24,   26,   26,
   24,   26,   26,   26,   19,   19,   26,   19,   19,   19,
   22,   22,   19,   22,   22,   22,   20,   20,   22,   20,
   20,   20,   21,   21,   20,   21,   21,   21,   14,   14,
   21,    0,   16,   14,   15,   15,   14,   15,   16,   15,
    0,    0,   15,   15,    0,    0,   16,   16,    0,    0,
    0,   16,    0,    0,   16,    0,    0,    0,    0,    0,
   17,   17,    0,    0,    0,   17,    0,   18,   18,   67,
    0,    0,   18,   69,   65,   64,    0,   63,   67,   66,
    0,    0,    0,   65,   64,    0,   63,    0,   66,    0,
    0,    0,   67,    0,    0,   68,    0,   65,   64,  112,
   63,   67,   66,    0,   68,    0,   65,   64,    0,   63,
    0,   66,    0,    0,   67,    0,    0,    0,   68,   65,
   64,    0,   63,    0,   66,    0,    0,   68,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   68,    0,    9,   48,   49,    0,   50,    0,    0,    0,
    0,   12,   13,    0,   51,    0,   17,    0,   22,   26,
    0,   27,    0,    0,    0,    0,    9,   10,   11,    0,
   39,    0,    0,    0,   44,   12,   13,    0,   14,   52,
    0,    0,   70,    0,   74,   76,    0,    0,    0,    0,
    6,    6,    6,    0,    0,    0,   80,   81,    0,    6,
    6,    0,    6,   40,   41,    0,    0,    0,    0,    0,
   47,    0,    0,    0,    0,    0,    0,    0,    0,   74,
    0,  104,   78,    0,    0,    0,    0,    0,    0,  108,
    0,    0,   74,  111,    0,   87,   88,   89,   90,   91,
   92,   93,   94,   95,   96,   97,   98,   99,  100,    9,
   73,    0,    0,    0,  115,    9,  101,   74,   12,   13,
    0,    0,    0,    0,   12,   13,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  114,    0,    0,    0,    0,
    0,    0,  118,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   55,   56,   57,   58,   59,   60,   61,   62,
    0,   55,   56,   57,   58,   59,   60,   61,   62,    0,
    0,    0,    0,    0,    0,   55,   56,   57,   58,   59,
   60,   61,   62,    0,   55,   56,   57,   58,   59,   60,
    0,   62,    0,    0,    0,    0,    0,   55,   56,   57,
   58,   59,   60,
};
const short kcalcheck[] = {                                      33,
    0,   46,   40,   46,  265,   37,   40,   45,  260,   31,
   42,   45,  263,  264,   36,   47,  261,   14,    0,  262,
  263,  264,   46,   40,   21,  260,  261,  257,   45,   40,
  268,   63,   47,   63,   45,   47,    0,   37,   35,   93,
   46,   41,   42,   43,   47,   45,  262,   47,   45,   71,
   46,   93,   47,   47,    0,   37,   28,   91,   58,   41,
   42,   43,   84,   45,    6,   47,   38,   26,   -1,   -1,
   -1,   -1,    0,   37,   -1,   -1,   58,   41,   42,   43,
   -1,   45,   -1,   47,   -1,   -1,   -1,  109,   -1,   -1,
    0,   37,   -1,   -1,   58,   41,   42,   43,   -1,   45,
   72,   47,   -1,   -1,   -1,  102,   -1,   79,    0,   -1,
   -1,   -1,   58,   41,    0,   43,   -1,   45,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   58,   41,    0,   43,   -1,   45,   -1,   -1,    0,   -1,
   -1,  113,   -1,   -1,   -1,   -1,   -1,   -1,   58,   41,
   -1,   -1,   -1,   -1,   -1,   41,    0,   -1,   -1,   -1,
   -1,   -1,    0,   -1,   -1,   -1,   58,   -1,   -1,   -1,
   -1,   -1,   58,   41,   -1,   -1,   -1,   -1,   -1,   41,
    0,   -1,   -1,   -1,   -1,   -1,    0,   -1,   -1,   -1,
   58,   -1,   -1,   -1,   -1,   -1,   58,   41,   -1,   -1,
    0,   -1,   -1,   41,   -1,   -1,    0,   -1,   -1,   -1,
   -1,   -1,    0,  258,   58,  258,  259,   -1,    0,  257,
   58,   41,   -1,  257,    0,  263,  264,   41,  266,  267,
    0,   -1,  266,  267,  258,  259,    0,   -1,   58,   -1,
  257,  258,    0,   -1,   58,   -1,  257,   47,    0,  266,
  267,   -1,   46,   -1,    0,  266,  267,   -1,   -1,   -1,
  260,  261,   -1,  263,  264,  265,    0,   -1,  268,   -1,
  270,  271,  272,  273,  274,  275,  276,  277,  260,  261,
    0,  263,  264,  265,   -1,   -1,  268,    0,  270,  271,
  272,  273,  274,  275,  276,  277,  260,  261,   -1,  263,
  264,  265,   -1,   -1,  268,   -1,  270,  271,  272,  273,
  274,  275,  276,  277,  260,  261,   -1,  263,  264,  265,
   -1,   -1,  268,   -1,  270,  271,  272,  273,  274,  275,
  276,  277,  260,  261,   -1,  263,  264,  265,   -1,   -1,
  268,   -1,  270,  271,  272,  273,  274,  275,  276,  277,
  260,  261,   -1,  263,  264,  265,   -1,   -1,  268,   -1,
  270,  271,  272,  273,  274,  275,  276,  277,  260,  261,
   -1,  263,  264,  265,  260,  261,  268,  263,  264,  265,
   -1,   -1,  268,   -1,  276,  277,   -1,   -1,   -1,   -1,
  276,  277,  260,  261,   -1,  263,  264,  265,  260,  261,
  268,  263,  264,  265,   -1,   40,  268,   -1,  276,  277,
   45,   -1,   -1,   -1,  276,  277,  260,  261,   -1,  263,
  264,  265,  260,  261,  268,  263,  264,  265,   -1,   40,
  268,   -1,  276,  277,   45,   -1,   -1,   -1,  276,  277,
  260,  261,   -1,  263,  264,  265,  260,  261,  268,  263,
  264,  265,   -1,   40,  268,   -1,  276,  277,   45,   -1,
  260,  261,  276,  263,  264,  265,  260,  261,  268,  263,
  264,  265,  260,  261,  268,  263,  264,  265,  260,  261,
  268,  263,  264,  265,  260,  261,  268,  263,  264,  265,
  260,  261,  268,  263,  264,  265,  260,  261,  268,  263,
  264,  265,  260,  261,  268,  263,  264,  265,  260,  261,
  268,   -1,   40,  265,  260,  261,  268,   45,   40,  265,
   -1,   -1,  268,   45,   -1,   -1,  260,  261,   -1,   -1,
   -1,  265,   -1,   -1,  268,   -1,   -1,   -1,   -1,   -1,
  260,  261,   -1,   -1,   -1,  265,   -1,  260,  261,   37,
   -1,   -1,  265,   41,   42,   43,   -1,   45,   37,   47,
   -1,   -1,   -1,   42,   43,   -1,   45,   -1,   47,   -1,
   -1,   -1,   37,   -1,   -1,   63,   -1,   42,   43,   58,
   45,   37,   47,   -1,   63,   -1,   42,   43,   -1,   45,
   -1,   47,   -1,   -1,   37,   -1,   -1,   -1,   63,   42,
   43,   -1,   45,   -1,   47,   -1,   -1,   63,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   63,   -1,  257,  258,  259,   -1,  261,   -1,   -1,   -1,
   -1,  266,  267,   -1,  269,   -1,    8,   -1,   10,   11,
   -1,   13,   -1,   -1,   -1,   -1,  257,  258,  259,   -1,
   22,   -1,   -1,   -1,   26,  266,  267,   -1,  269,   31,
   -1,   -1,   34,   -1,   36,   37,   -1,   -1,   -1,   -1,
  257,  258,  259,   -1,   -1,   -1,   48,   49,   -1,  266,
  267,   -1,  269,   23,   24,   -1,   -1,   -1,   -1,   -1,
   30,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   71,
   -1,   73,   42,   -1,   -1,   -1,   -1,   -1,   -1,   81,
   -1,   -1,   84,   85,   -1,   55,   56,   57,   58,   59,
   60,   61,   62,   63,   64,   65,   66,   67,   68,  257,
  258,   -1,   -1,   -1,  106,  257,  258,  109,  266,  267,
   -1,   -1,   -1,   -1,  266,  267,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  105,   -1,   -1,   -1,   -1,
   -1,   -1,  112,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  270,  271,  272,  273,  274,  275,  276,  277,
   -1,  270,  271,  272,  273,  274,  275,  276,  277,   -1,
   -1,   -1,   -1,   -1,   -1,  270,  271,  272,  273,  274,
  275,  276,  277,   -1,  270,  271,  272,  273,  274,  275,
   -1,  277,   -1,   -1,   -1,   -1,   -1,  270,  271,  272,
  273,  274,  275,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 278
#if YYDEBUG
const char * const kcalname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"'!'",0,0,0,"'%'",0,0,"'('","')'","'*'","'+'",0,"'-'","'.'","'/'",0,0,0,0,0,0,0,
0,0,0,"':'",0,0,0,0,"'?'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"'['",0,"']'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,"NUMBER","MONTH","WDAY","COLOR","STRING","IN","PLUS",
"MINUS","SMALL","CYEAR","LEAPYEAR","LENGTH","EASTER","EQ","NE","LE","GE","LT",
"GT","OR","AND","UMINUS",
};
const char * const kcalrule[] = {
"$accept : list",
"list :",
"$$1 :",
"list : list small color STRING color $$1 entry",
"small :",
"small : SMALL",
"color :",
"color : COLOR",
"entry : EASTER offset length",
"entry : date offset length",
"entry : WDAY offset length",
"entry : pexpr WDAY offset length",
"entry : pexpr WDAY IN month offset length",
"entry : WDAY pexpr date offset length",
"offset :",
"offset : PLUS expr",
"offset : MINUS expr",
"length :",
"length : LENGTH expr",
"date : pexpr '.' month",
"date : pexpr '.' month '.'",
"date : pexpr '.' month '.' expr",
"date : month '/' pexpr",
"date : month '/' pexpr '/' pexpr",
"date : MONTH pexpr",
"date : MONTH pexpr pexpr",
"date : pexpr MONTH",
"date : pexpr MONTH pexpr",
"date : pexpr '.' MONTH pexpr",
"date : pexpr",
"reldate : STRING",
"reldate : EASTER",
"reldate : pexpr '.' month",
"reldate : pexpr '.' month '.'",
"reldate : month '/' pexpr",
"reldate : pexpr MONTH",
"reldate : MONTH pexpr",
"reldate : WDAY pexpr pexpr",
"reldate : pexpr WDAY IN month",
"month : MONTH",
"month : pexpr",
"expr : pexpr",
"expr : expr OR expr",
"expr : expr AND expr",
"expr : expr EQ expr",
"expr : expr NE expr",
"expr : expr LE expr",
"expr : expr GE expr",
"expr : expr LT expr",
"expr : expr GT expr",
"expr : expr '+' expr",
"expr : expr '-' expr",
"expr : expr '*' expr",
"expr : expr '/' expr",
"expr : expr '%' expr",
"expr : expr '?' expr ':' expr",
"expr : '!' expr",
"expr : '[' reldate ']'",
"pexpr : '(' expr ')'",
"pexpr : number",
"number : NUMBER",
"number : '-' NUMBER",
"number : CYEAR",
"number : LEAPYEAR pexpr",
};
#endif
#if YYDEBUG
#include <stdio.h>
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH 10000
#endif
#endif
#define YYINITSTACKSIZE 200
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short *yyss;
short *yysslim;
YYSTYPE *yyvs;
int yystacksize;
#line 218 "parseholiday.y"
	 
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

extern FILE  *kcalin;                /* file currently being processed */
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
#line 947 "parseholiday.c"
/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack()
{
    int newsize, i;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = yystacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;
    i = yyssp - yyss;
    newss = yyss ? (short *)realloc(yyss, newsize * sizeof *newss) :
      (short *)malloc(newsize * sizeof *newss);
    if (newss == NULL)
        return -1;
    yyss = newss;
    yyssp = newss + i;
    newvs = yyvs ? (YYSTYPE *)realloc(yyvs, newsize * sizeof *newvs) :
      (YYSTYPE *)malloc(newsize * sizeof *newvs);
    if (newvs == NULL)
        return -1;
    yyvs = newvs;
    yyvsp = newvs + i;
    yystacksize = newsize;
    yysslim = yyss + newsize - 1;
    return 0;
}

#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab

#ifndef YYPARSE_PARAM
#if defined(__cplusplus) || __STDC__
#define YYPARSE_PARAM_ARG void
#define YYPARSE_PARAM_DECL
#else	/* ! ANSI-C/C++ */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif	/* ANSI-C/C++ */
#else	/* YYPARSE_PARAM */
#ifndef YYPARSE_PARAM_TYPE
#define YYPARSE_PARAM_TYPE void *
#endif
#if defined(__cplusplus) || __STDC__
#define YYPARSE_PARAM_ARG YYPARSE_PARAM_TYPE YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else	/* ! ANSI-C/C++ */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL YYPARSE_PARAM_TYPE YYPARSE_PARAM;
#endif	/* ANSI-C/C++ */
#endif	/* ! YYPARSE_PARAM */

int
yyparse (YYPARSE_PARAM_ARG)
    YYPARSE_PARAM_DECL
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register const char *yys;

    if ((yys = getenv("YYDEBUG")))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    if (yyss == NULL && yygrowstack()) goto yyoverflow;
    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if ((yyn = yydefred[yystate])) goto yyreduce;
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
        if (yyssp >= yysslim && yygrowstack())
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
#if defined(lint) || defined(__GNUC__)
    goto yynewerror;
#endif
yynewerror:
    yyerror("syntax error");
#if defined(lint) || defined(__GNUC__)
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
                if (yyssp >= yysslim && yygrowstack())
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
case 2:
#line 122 "parseholiday.y"
{ yacc_stringcolor = yyvsp[-2].ival;
						  yacc_string	= yyvsp[-1].sval;
						  yacc_daycolor	= yyvsp[0].ival; }
break;
case 3:
#line 125 "parseholiday.y"
{ free(yacc_string); }
break;
case 4:
#line 128 "parseholiday.y"
{ yacc_small = 0; }
break;
case 5:
#line 129 "parseholiday.y"
{ yacc_small = 1; }
break;
case 6:
#line 132 "parseholiday.y"
{ yyval.ival = 0; }
break;
case 7:
#line 133 "parseholiday.y"
{ yyval.ival = yyvsp[0].ival; }
break;
case 8:
#line 136 "parseholiday.y"
{ seteaster(yyvsp[-1].ival, yyvsp[0].ival); }
break;
case 9:
#line 137 "parseholiday.y"
{ setdate( m,  d,  y, yyvsp[-1].ival, yyvsp[0].ival);}
break;
case 10:
#line 138 "parseholiday.y"
{ setwday( 0, yyvsp[-2].ival,  0, yyvsp[-1].ival, yyvsp[0].ival);}
break;
case 11:
#line 139 "parseholiday.y"
{ setwday(yyvsp[-3].ival, yyvsp[-2].ival,  0, yyvsp[-1].ival, yyvsp[0].ival);}
break;
case 12:
#line 140 "parseholiday.y"
{ setwday(yyvsp[-5].ival, yyvsp[-4].ival, yyvsp[-2].ival, yyvsp[-1].ival, yyvsp[0].ival);}
break;
case 13:
#line 141 "parseholiday.y"
{ setdoff(yyvsp[-4].ival, yyvsp[-3].ival,m,d,y,yyvsp[-1].ival,yyvsp[0].ival);}
break;
case 14:
#line 144 "parseholiday.y"
{ yyval.ival =	0; }
break;
case 15:
#line 145 "parseholiday.y"
{ yyval.ival =	yyvsp[0].ival; }
break;
case 16:
#line 146 "parseholiday.y"
{ yyval.ival = -yyvsp[0].ival; }
break;
case 17:
#line 149 "parseholiday.y"
{ yyval.ival =	1; }
break;
case 18:
#line 150 "parseholiday.y"
{ yyval.ival =	yyvsp[0].ival; }
break;
case 19:
#line 153 "parseholiday.y"
{ m = yyvsp[0].ival; d = yyvsp[-2].ival; y = 0;  }
break;
case 20:
#line 154 "parseholiday.y"
{ m = yyvsp[-1].ival; d = yyvsp[-3].ival; y = 0;  }
break;
case 21:
#line 155 "parseholiday.y"
{ m = yyvsp[-2].ival; d = yyvsp[-4].ival; y = yyvsp[0].ival; }
break;
case 22:
#line 156 "parseholiday.y"
{ m = yyvsp[-2].ival; d = yyvsp[0].ival; y = 0;  }
break;
case 23:
#line 157 "parseholiday.y"
{ m = yyvsp[-4].ival; d = yyvsp[-2].ival; y = yyvsp[0].ival; }
break;
case 24:
#line 158 "parseholiday.y"
{ m = yyvsp[-1].ival; d = yyvsp[0].ival; y = 0;  }
break;
case 25:
#line 159 "parseholiday.y"
{ m = yyvsp[-2].ival; d = yyvsp[-1].ival; y = yyvsp[0].ival; }
break;
case 26:
#line 160 "parseholiday.y"
{ m = yyvsp[0].ival; d = yyvsp[-1].ival; y = 0;  }
break;
case 27:
#line 161 "parseholiday.y"
{ m = yyvsp[-1].ival; d = yyvsp[-2].ival; y = yyvsp[0].ival; }
break;
case 28:
#line 162 "parseholiday.y"
{ m = yyvsp[-1].ival; d = yyvsp[-3].ival; y = yyvsp[0].ival; }
break;
case 29:
#line 163 "parseholiday.y"
{ monthday_from_day(yyvsp[0].ival,
								 &m, &d, &y); }
break;
case 30:
#line 167 "parseholiday.y"
{ yyval.ival = day_from_name(yyvsp[0].sval); }
break;
case 31:
#line 168 "parseholiday.y"
{ yyval.ival = day_from_easter(); }
break;
case 32:
#line 169 "parseholiday.y"
{ yyval.ival = day_from_monthday
								 (yyvsp[0].ival, yyvsp[-2].ival); }
break;
case 33:
#line 171 "parseholiday.y"
{ yyval.ival = day_from_monthday
								 (yyvsp[-1].ival, yyvsp[-3].ival); }
break;
case 34:
#line 173 "parseholiday.y"
{ yyval.ival = day_from_monthday
								 (yyvsp[-2].ival, yyvsp[0].ival); }
break;
case 35:
#line 175 "parseholiday.y"
{ yyval.ival = day_from_monthday
								 (yyvsp[0].ival, yyvsp[-1].ival); }
break;
case 36:
#line 177 "parseholiday.y"
{ yyval.ival = day_from_monthday
								 (yyvsp[-1].ival, yyvsp[0].ival); }
break;
case 37:
#line 179 "parseholiday.y"
{ yyval.ival = day_from_wday(yyvsp[0].ival, yyvsp[-2].ival,
							 yyvsp[-1].ival == -1 ? -1 : 0); }
break;
case 38:
#line 181 "parseholiday.y"
{ int d=day_from_monthday(yyvsp[0].ival,1);
						   yyval.ival = yyvsp[-3].ival == 999
						    ? day_from_wday(d+1,yyvsp[-2].ival,-1)
						    : day_from_wday(d,yyvsp[-2].ival,yyvsp[-3].ival-1);}
break;
case 41:
#line 189 "parseholiday.y"
{ yyval.ival = yyvsp[0].ival; }
break;
case 42:
#line 190 "parseholiday.y"
{ yyval.ival = yyvsp[-2].ival || yyvsp[0].ival; }
break;
case 43:
#line 191 "parseholiday.y"
{ yyval.ival = yyvsp[-2].ival && yyvsp[0].ival; }
break;
case 44:
#line 192 "parseholiday.y"
{ yyval.ival = yyvsp[-2].ival == yyvsp[0].ival; }
break;
case 45:
#line 193 "parseholiday.y"
{ yyval.ival = yyvsp[-2].ival != yyvsp[0].ival; }
break;
case 46:
#line 194 "parseholiday.y"
{ yyval.ival = yyvsp[-2].ival <= yyvsp[0].ival; }
break;
case 47:
#line 195 "parseholiday.y"
{ yyval.ival = yyvsp[-2].ival >= yyvsp[0].ival; }
break;
case 48:
#line 196 "parseholiday.y"
{ yyval.ival = yyvsp[-2].ival <  yyvsp[0].ival; }
break;
case 49:
#line 197 "parseholiday.y"
{ yyval.ival = yyvsp[-2].ival >  yyvsp[0].ival; }
break;
case 50:
#line 198 "parseholiday.y"
{ yyval.ival = yyvsp[-2].ival +  yyvsp[0].ival; }
break;
case 51:
#line 199 "parseholiday.y"
{ yyval.ival = yyvsp[-2].ival -  yyvsp[0].ival; }
break;
case 52:
#line 200 "parseholiday.y"
{ yyval.ival = yyvsp[-2].ival *  yyvsp[0].ival; }
break;
case 53:
#line 201 "parseholiday.y"
{ yyval.ival = yyvsp[0].ival ?  yyvsp[-2].ival / yyvsp[0].ival : 0; }
break;
case 54:
#line 202 "parseholiday.y"
{ yyval.ival = yyvsp[0].ival ?  yyvsp[-2].ival % yyvsp[0].ival : 0; }
break;
case 55:
#line 203 "parseholiday.y"
{ yyval.ival = yyvsp[-4].ival ?  yyvsp[-2].ival : yyvsp[0].ival; }
break;
case 56:
#line 204 "parseholiday.y"
{ yyval.ival = !yyvsp[0].ival; }
break;
case 57:
#line 205 "parseholiday.y"
{ yyval.ival = yyvsp[-1].ival; }
break;
case 58:
#line 208 "parseholiday.y"
{ yyval.ival = yyvsp[-1].ival; }
break;
case 59:
#line 209 "parseholiday.y"
{ yyval.ival = yyvsp[0].ival; }
break;
case 61:
#line 213 "parseholiday.y"
{ yyval.ival = -yyvsp[0].ival; }
break;
case 62:
#line 214 "parseholiday.y"
{ yyval.ival = parse_year; }
break;
case 63:
#line 215 "parseholiday.y"
{ yyval.ival = !((yyvsp[0].ival) & 3); }
break;
#line 1390 "parseholiday.c"
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
    if (yyssp >= yysslim && yygrowstack())
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
