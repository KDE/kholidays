/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison LALR(1) parsers in C++

   Copyright (C) 2002, 2003, 2004, 2005, 2006 Free Software Foundation, Inc.

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

// Take the name prefix into account.
#define yylex   KHolidayslex

#include "holidayparserplan.hpp"

/* User implementation prologue.  */
#line 70 "holidayparserplan.ypp"

//Fix broken skeleton define of yylex as KHolidayslex
#define yylex yylex
#include "holidayparserdriverplan_p.h"


/* Line 317 of lalr1.cc.  */
#line 50 "holidayparserplan.cpp"

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* FIXME: INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#define YYUSE(e) ((void) (e))

/* A pseudo ostream that takes yydebug_ into account.  */
# define YYCDEBUG							\
  for (bool yydebugcond_ = yydebug_; yydebugcond_; yydebugcond_ = false)	\
    (*yycdebug_)

/* Enable debugging if requested.  */
#if YYDEBUG

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)	\
do {							\
  if (yydebug_)						\
    {							\
      *yycdebug_ << Title << ' ';			\
      yy_symbol_print_ ((Type), (Value), (Location));	\
      *yycdebug_ << std::endl;				\
    }							\
} while (false)

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug_)				\
    yy_reduce_print_ (Rule);		\
} while (false)

# define YY_STACK_PRINT()		\
do {					\
  if (yydebug_)				\
    yystack_print_ ();			\
} while (false)

#else /* !YYDEBUG */

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_REDUCE_PRINT(Rule)
# define YY_STACK_PRINT()

#endif /* !YYDEBUG */

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab

namespace KHolidays
{
#if YYERROR_VERBOSE

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  HolidayParserPlan::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
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
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

#endif

  /// Build a parser object.
  HolidayParserPlan::HolidayParserPlan (HolidayParserDriverPlan &driver_yyarg)
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
      driver (driver_yyarg)
  {
  }

  HolidayParserPlan::~HolidayParserPlan ()
  {
  }

#if YYDEBUG
  /*--------------------------------.
  | Print this symbol on YYOUTPUT.  |
  `--------------------------------*/

  inline void
  HolidayParserPlan::yy_symbol_value_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yyvaluep);
    switch (yytype)
      {
         default:
	  break;
      }
  }


  void
  HolidayParserPlan::yy_symbol_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    *yycdebug_ << (yytype < yyntokens_ ? "token" : "nterm")
	       << ' ' << yytname_[yytype] << " ("
	       << *yylocationp << ": ";
    yy_symbol_value_print_ (yytype, yyvaluep, yylocationp);
    *yycdebug_ << ')';
  }
#endif /* ! YYDEBUG */

  void
  HolidayParserPlan::yydestruct_ (const char* yymsg,
			   int yytype, semantic_type* yyvaluep, location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yymsg);
    YYUSE (yyvaluep);

    YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

    switch (yytype)
      {
  
	default:
	  break;
      }
  }

  void
  HolidayParserPlan::yypop_ (unsigned int n)
  {
    yystate_stack_.pop (n);
    yysemantic_stack_.pop (n);
    yylocation_stack_.pop (n);
  }

  std::ostream&
  HolidayParserPlan::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  HolidayParserPlan::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  HolidayParserPlan::debug_level_type
  HolidayParserPlan::debug_level () const
  {
    return yydebug_;
  }

  void
  HolidayParserPlan::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }


  int
  HolidayParserPlan::parse ()
  {
    /// Look-ahead and look-ahead in internal form.
    int yychar = yyempty_;
    int yytoken = 0;

    /* State.  */
    int yyn;
    int yylen = 0;
    int yystate = 0;

    /* Error handling.  */
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// Semantic value of the look-ahead.
    semantic_type yylval;
    /// Location of the look-ahead.
    location_type yylloc;
    /// The locations where the error started and ended.
    location yyerror_range[2];

    /// $$.
    semantic_type yyval;
    /// @$.
    location_type yyloc;

    int yyresult;

    YYCDEBUG << "Starting parse" << std::endl;


    /* User initialization code.  */
    #line 60 "holidayparserplan.ypp"
{
    yylloc.begin.filename = new std::string( driver.filePath().toLocal8Bit().data() );
    yylloc.end.filename = yylloc.begin.filename;
}
  /* Line 547 of yacc.c.  */
#line 287 "holidayparserplan.cpp"
    /* Initialize the stacks.  The initial state will be pushed in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystate_stack_ = state_stack_type (0);
    yysemantic_stack_ = semantic_stack_type (0);
    yylocation_stack_ = location_stack_type (0);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* New state.  */
  yynewstate:
    yystate_stack_.push (yystate);
    YYCDEBUG << "Entering state " << yystate << std::endl;
    goto yybackup;

    /* Backup.  */
  yybackup:

    /* Try to take a decision without look-ahead.  */
    yyn = yypact_[yystate];
    if (yyn == yypact_ninf_)
      goto yydefault;

    /* Read a look-ahead token.  */
    if (yychar == yyempty_)
      {
	YYCDEBUG << "Reading a token: ";
	yychar = yylex (&yylval, &yylloc, driver);
      }


    /* Convert token to internal form.  */
    if (yychar <= yyeof_)
      {
	yychar = yytoken = yyeof_;
	YYCDEBUG << "Now at end of input." << std::endl;
      }
    else
      {
	yytoken = yytranslate_ (yychar);
	YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
      }

    /* If the proper action on seeing token YYTOKEN is to reduce or to
       detect an error, take that action.  */
    yyn += yytoken;
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yytoken)
      goto yydefault;

    /* Reduce or error.  */
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
	if (yyn == 0 || yyn == yytable_ninf_)
	goto yyerrlab;
	yyn = -yyn;
	goto yyreduce;
      }

    /* Accept?  */
    if (yyn == yyfinal_)
      goto yyacceptlab;

    /* Shift the look-ahead token.  */
    YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

    /* Discard the token being shifted unless it is eof.  */
    if (yychar != yyeof_)
      yychar = yyempty_;

    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* Count tokens shifted since error; after three, turn off error
       status.  */
    if (yyerrstatus_)
      --yyerrstatus_;

    yystate = yyn;
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystate];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    /* If YYLEN is nonzero, implement the default value of the action:
       `$$ = $1'.  Otherwise, use the top of the stack.

       Otherwise, the following line sets YYVAL to garbage.
       This behavior is undocumented and Bison
       users should not rely upon it.  */
    if (yylen)
      yyval = yysemantic_stack_[yylen - 1];
    else
      yyval = yysemantic_stack_[0];

    {
      slice<location_type, location_stack_type> slice (yylocation_stack_, yylen);
      YYLLOC_DEFAULT (yyloc, slice, yylen);
    }
    YY_REDUCE_PRINT (yyn);
    switch (yyn)
      {
	  case 4:
#line 101 "holidayparserplan.ypp"
    { driver.setFileRegionCode( QString() ); ;}
    break;

  case 5:
#line 102 "holidayparserplan.ypp"
    { driver.setFileRegionCode( QString::fromUtf8( (yysemantic_stack_[(2) - (2)].sval) ) ); ;}
    break;

  case 6:
#line 105 "holidayparserplan.ypp"
    { driver.setFileLanguageCode( QString() ); ;}
    break;

  case 7:
#line 106 "holidayparserplan.ypp"
    { driver.setFileLanguageCode( QString::fromUtf8( (yysemantic_stack_[(2) - (2)].sval) ) ); ;}
    break;

  case 8:
#line 109 "holidayparserplan.ypp"
    { driver.setFileShortName( QString() ); ;}
    break;

  case 9:
#line 110 "holidayparserplan.ypp"
    { driver.setFileShortName( QString::fromUtf8( (yysemantic_stack_[(2) - (2)].sval) ) ); ;}
    break;

  case 14:
#line 121 "holidayparserplan.ypp"
    { driver.setEventColorName( 0 ); ;}
    break;

  case 15:
#line 122 "holidayparserplan.ypp"
    { driver.setEventColorName( (yysemantic_stack_[(1) - (1)].ival) ); ;}
    break;

  case 16:
#line 125 "holidayparserplan.ypp"
    { driver.setEventColorDay( 0 ); ;}
    break;

  case 17:
#line 126 "holidayparserplan.ypp"
    { driver.setEventColorDay( (yysemantic_stack_[(1) - (1)].ival) ); ;}
    break;

  case 18:
#line 129 "holidayparserplan.ypp"
    { driver.setEventName( QString::fromUtf8( (yysemantic_stack_[(1) - (1)].sval) ) ); ;}
    break;

  case 19:
#line 132 "holidayparserplan.ypp"
    { driver.setEventCalendarType( "gregorian" ); ;}
    break;

  case 20:
#line 133 "holidayparserplan.ypp"
    { driver.setEventCalendarType( QString::fromUtf8( (yysemantic_stack_[(1) - (1)].sval) ) ); ;}
    break;

  case 21:
#line 136 "holidayparserplan.ypp"
    { driver.setFromEaster( (yysemantic_stack_[(3) - (2)].ival), (yysemantic_stack_[(3) - (3)].ival) ); ;}
    break;

  case 22:
#line 137 "holidayparserplan.ypp"
    { driver.setFromPascha( (yysemantic_stack_[(3) - (2)].ival), (yysemantic_stack_[(3) - (3)].ival) ); ;}
    break;

  case 23:
#line 138 "holidayparserplan.ypp"
    { driver.setFromDate( (yysemantic_stack_[(4) - (2)].ival), (yysemantic_stack_[(4) - (3)].ival), (yysemantic_stack_[(4) - (4)].ival) ); ;}
    break;

  case 24:
#line 139 "holidayparserplan.ypp"
    { driver.setFromWeekdayInMonth( 1, (yysemantic_stack_[(3) - (1)].ival), 1, (yysemantic_stack_[(3) - (2)].ival), (yysemantic_stack_[(3) - (3)].ival) ); ;}
    break;

  case 25:
#line 140 "holidayparserplan.ypp"
    { driver.setFromWeekdayInMonth( (yysemantic_stack_[(4) - (1)].ival), (yysemantic_stack_[(4) - (2)].ival), 1, (yysemantic_stack_[(4) - (3)].ival), (yysemantic_stack_[(4) - (4)].ival) ); ;}
    break;

  case 26:
#line 141 "holidayparserplan.ypp"
    { driver.setFromWeekdayInMonth( (yysemantic_stack_[(6) - (1)].ival), (yysemantic_stack_[(6) - (2)].ival), (yysemantic_stack_[(6) - (4)].ival), (yysemantic_stack_[(6) - (5)].ival), (yysemantic_stack_[(6) - (6)].ival) ); ;}
    break;

  case 27:
#line 142 "holidayparserplan.ypp"
    { driver.setFromRelativeWeekday( (yysemantic_stack_[(5) - (2)].ival), (yysemantic_stack_[(5) - (1)].ival), (yysemantic_stack_[(5) - (4)].ival), (yysemantic_stack_[(5) - (5)].ival) ); ;}
    break;

  case 28:
#line 145 "holidayparserplan.ypp"
    { (yyval.ival) =   0; ;}
    break;

  case 29:
#line 146 "holidayparserplan.ypp"
    { (yyval.ival) =  (yysemantic_stack_[(2) - (2)].ival); ;}
    break;

  case 30:
#line 147 "holidayparserplan.ypp"
    { (yyval.ival) = -(yysemantic_stack_[(2) - (2)].ival); ;}
    break;

  case 31:
#line 150 "holidayparserplan.ypp"
    { (yyval.ival) = 0; ;}
    break;

  case 32:
#line 151 "holidayparserplan.ypp"
    { (yyval.ival) = ( (yysemantic_stack_[(4) - (2)].ival) << 8 ) | (yysemantic_stack_[(4) - (4)].ival); ;}
    break;

  case 33:
#line 154 "holidayparserplan.ypp"
    { (yyval.ival) = 0; ;}
    break;

  case 34:
#line 155 "holidayparserplan.ypp"
    { (yyval.ival) = ( 1 << (yysemantic_stack_[(1) - (1)].ival) ); ;}
    break;

  case 35:
#line 156 "holidayparserplan.ypp"
    { (yyval.ival) = ( 1 << (yysemantic_stack_[(3) - (1)].ival) ) | (yysemantic_stack_[(3) - (3)].ival); ;}
    break;

  case 36:
#line 159 "holidayparserplan.ypp"
    { (yyval.ival) =  1; ;}
    break;

  case 37:
#line 160 "holidayparserplan.ypp"
    { (yyval.ival) = (yysemantic_stack_[(2) - (2)].ival); ;}
    break;

  case 38:
#line 163 "holidayparserplan.ypp"
    { driver.setEventDate( -99999, (yysemantic_stack_[(3) - (3)].ival), (yysemantic_stack_[(3) - (1)].ival) ); ;}
    break;

  case 39:
#line 164 "holidayparserplan.ypp"
    { driver.setEventDate( -99999, (yysemantic_stack_[(4) - (3)].ival), (yysemantic_stack_[(4) - (1)].ival) ); ;}
    break;

  case 40:
#line 165 "holidayparserplan.ypp"
    { driver.setEventDate(     (yysemantic_stack_[(5) - (5)].ival), (yysemantic_stack_[(5) - (3)].ival), (yysemantic_stack_[(5) - (1)].ival) ); ;}
    break;

  case 41:
#line 166 "holidayparserplan.ypp"
    { driver.setEventDate( -99999, (yysemantic_stack_[(3) - (1)].ival), (yysemantic_stack_[(3) - (3)].ival) ); ;}
    break;

  case 42:
#line 167 "holidayparserplan.ypp"
    { driver.setEventDate(     (yysemantic_stack_[(5) - (5)].ival), (yysemantic_stack_[(5) - (1)].ival), (yysemantic_stack_[(5) - (3)].ival) ); ;}
    break;

  case 43:
#line 168 "holidayparserplan.ypp"
    { driver.setEventDate( -99999, (yysemantic_stack_[(2) - (1)].ival), (yysemantic_stack_[(2) - (2)].ival) ); ;}
    break;

  case 44:
#line 169 "holidayparserplan.ypp"
    { driver.setEventDate(     (yysemantic_stack_[(3) - (3)].ival), (yysemantic_stack_[(3) - (1)].ival), (yysemantic_stack_[(3) - (2)].ival) ); ;}
    break;

  case 45:
#line 170 "holidayparserplan.ypp"
    { driver.setEventDate( -99999, (yysemantic_stack_[(2) - (2)].ival), (yysemantic_stack_[(2) - (1)].ival) ); ;}
    break;

  case 46:
#line 171 "holidayparserplan.ypp"
    { driver.setEventDate(     (yysemantic_stack_[(3) - (3)].ival), (yysemantic_stack_[(3) - (2)].ival), (yysemantic_stack_[(3) - (1)].ival) ); ;}
    break;

  case 47:
#line 172 "holidayparserplan.ypp"
    { driver.setEventDate(     (yysemantic_stack_[(4) - (4)].ival), (yysemantic_stack_[(4) - (3)].ival), (yysemantic_stack_[(4) - (1)].ival) ); ;}
    break;

  case 48:
#line 173 "holidayparserplan.ypp"
    { driver.setEventDate( (yysemantic_stack_[(1) - (1)].ival) ); ;}
    break;

  case 49:
#line 176 "holidayparserplan.ypp"
    { (yyval.ival) = driver.julianDayFromEventName( (yysemantic_stack_[(1) - (1)].sval) ); ;}
    break;

  case 50:
#line 177 "holidayparserplan.ypp"
    { (yyval.ival) = driver.julianDayFromEaster(); ;}
    break;

  case 51:
#line 178 "holidayparserplan.ypp"
    { (yyval.ival) = driver.julianDayFromPascha(); ;}
    break;

  case 52:
#line 179 "holidayparserplan.ypp"
    { (yyval.ival) = driver.julianDayFromMonthDay( (yysemantic_stack_[(3) - (3)].ival), (yysemantic_stack_[(3) - (1)].ival) ); ;}
    break;

  case 53:
#line 180 "holidayparserplan.ypp"
    { (yyval.ival) = driver.julianDayFromMonthDay( (yysemantic_stack_[(4) - (3)].ival), (yysemantic_stack_[(4) - (1)].ival) ); ;}
    break;

  case 54:
#line 181 "holidayparserplan.ypp"
    { (yyval.ival) = driver.julianDayFromMonthDay( (yysemantic_stack_[(3) - (1)].ival), (yysemantic_stack_[(3) - (3)].ival) ); ;}
    break;

  case 55:
#line 182 "holidayparserplan.ypp"
    { (yyval.ival) = driver.julianDayFromMonthDay( (yysemantic_stack_[(2) - (2)].ival), (yysemantic_stack_[(2) - (1)].ival) ); ;}
    break;

  case 56:
#line 183 "holidayparserplan.ypp"
    { (yyval.ival) = driver.julianDayFromMonthDay( (yysemantic_stack_[(2) - (1)].ival), (yysemantic_stack_[(2) - (2)].ival) ); ;}
    break;

  case 57:
#line 184 "holidayparserplan.ypp"
    { (yyval.ival) = driver.julianDayFromRelativeWeekday( (yysemantic_stack_[(3) - (2)].ival), (yysemantic_stack_[(3) - (1)].ival), (yysemantic_stack_[(3) - (3)].ival) ); ;}
    break;

  case 58:
#line 185 "holidayparserplan.ypp"
    { (yyval.ival) = driver.julianDayFromWeekdayInMonth( (yysemantic_stack_[(4) - (1)].ival), (yysemantic_stack_[(4) - (2)].ival), (yysemantic_stack_[(4) - (4)].ival) ); ;}
    break;

  case 60:
#line 189 "holidayparserplan.ypp"
    { (yyval.ival) = driver.adjustedMonthNumber( (yysemantic_stack_[(1) - (1)].ival) ); ;}
    break;

  case 61:
#line 192 "holidayparserplan.ypp"
    { (yyval.ival) = driver.adjustedMonthNumber( (yysemantic_stack_[(1) - (1)].ival) ); ;}
    break;

  case 62:
#line 195 "holidayparserplan.ypp"
    { (yyval.ival) = (yysemantic_stack_[(1) - (1)].ival); ;}
    break;

  case 63:
#line 196 "holidayparserplan.ypp"
    { (yyval.ival) = (yysemantic_stack_[(3) - (1)].ival) || (yysemantic_stack_[(3) - (3)].ival); ;}
    break;

  case 64:
#line 197 "holidayparserplan.ypp"
    { (yyval.ival) = (yysemantic_stack_[(3) - (1)].ival) && (yysemantic_stack_[(3) - (3)].ival); ;}
    break;

  case 65:
#line 198 "holidayparserplan.ypp"
    { (yyval.ival) = (yysemantic_stack_[(3) - (1)].ival) == (yysemantic_stack_[(3) - (3)].ival); ;}
    break;

  case 66:
#line 199 "holidayparserplan.ypp"
    { (yyval.ival) = (yysemantic_stack_[(3) - (1)].ival) != (yysemantic_stack_[(3) - (3)].ival); ;}
    break;

  case 67:
#line 200 "holidayparserplan.ypp"
    { (yyval.ival) = (yysemantic_stack_[(3) - (1)].ival) <= (yysemantic_stack_[(3) - (3)].ival); ;}
    break;

  case 68:
#line 201 "holidayparserplan.ypp"
    { (yyval.ival) = (yysemantic_stack_[(3) - (1)].ival) >= (yysemantic_stack_[(3) - (3)].ival); ;}
    break;

  case 69:
#line 202 "holidayparserplan.ypp"
    { (yyval.ival) = (yysemantic_stack_[(3) - (1)].ival) <  (yysemantic_stack_[(3) - (3)].ival); ;}
    break;

  case 70:
#line 203 "holidayparserplan.ypp"
    { (yyval.ival) = (yysemantic_stack_[(3) - (1)].ival) >  (yysemantic_stack_[(3) - (3)].ival); ;}
    break;

  case 71:
#line 204 "holidayparserplan.ypp"
    { (yyval.ival) = (yysemantic_stack_[(3) - (1)].ival) +  (yysemantic_stack_[(3) - (3)].ival); ;}
    break;

  case 72:
#line 205 "holidayparserplan.ypp"
    { (yyval.ival) = (yysemantic_stack_[(3) - (1)].ival) -  (yysemantic_stack_[(3) - (3)].ival); ;}
    break;

  case 73:
#line 206 "holidayparserplan.ypp"
    { (yyval.ival) = (yysemantic_stack_[(3) - (1)].ival) *  (yysemantic_stack_[(3) - (3)].ival); ;}
    break;

  case 74:
#line 207 "holidayparserplan.ypp"
    { (yyval.ival) = (yysemantic_stack_[(3) - (3)].ival) ?  (yysemantic_stack_[(3) - (1)].ival) / (yysemantic_stack_[(3) - (3)].ival) : 0; ;}
    break;

  case 75:
#line 208 "holidayparserplan.ypp"
    { (yyval.ival) = (yysemantic_stack_[(3) - (3)].ival) ?  (yysemantic_stack_[(3) - (1)].ival) % (yysemantic_stack_[(3) - (3)].ival) : 0; ;}
    break;

  case 76:
#line 209 "holidayparserplan.ypp"
    { (yyval.ival) = (yysemantic_stack_[(5) - (1)].ival) ?  (yysemantic_stack_[(5) - (3)].ival) : (yysemantic_stack_[(5) - (5)].ival); ;}
    break;

  case 77:
#line 210 "holidayparserplan.ypp"
    { (yyval.ival) = !(yysemantic_stack_[(2) - (2)].ival); ;}
    break;

  case 78:
#line 211 "holidayparserplan.ypp"
    { (yyval.ival) = (yysemantic_stack_[(3) - (2)].ival); ;}
    break;

  case 79:
#line 214 "holidayparserplan.ypp"
    { (yyval.ival) = (yysemantic_stack_[(3) - (2)].ival); ;}
    break;

  case 80:
#line 215 "holidayparserplan.ypp"
    { (yyval.ival) = (yysemantic_stack_[(1) - (1)].ival); ;}
    break;

  case 82:
#line 219 "holidayparserplan.ypp"
    { (yyval.ival) = -(yysemantic_stack_[(2) - (2)].ival); ;}
    break;

  case 83:
#line 220 "holidayparserplan.ypp"
    { (yyval.ival) = driver.parseYear(); ;}
    break;

  case 84:
#line 221 "holidayparserplan.ypp"
    { (yyval.ival) = driver.isLeapYear( (yysemantic_stack_[(2) - (2)].ival) ); ;}
    break;


    /* Line 675 of lalr1.cc.  */
#line 779 "holidayparserplan.cpp"
	default: break;
      }
    YY_SYMBOL_PRINT ("-> $$ =", yyr1_[yyn], &yyval, &yyloc);

    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();

    yysemantic_stack_.push (yyval);
    yylocation_stack_.push (yyloc);

    /* Shift the result of the reduction.  */
    yyn = yyr1_[yyn];
    yystate = yypgoto_[yyn - yyntokens_] + yystate_stack_[0];
    if (0 <= yystate && yystate <= yylast_
	&& yycheck_[yystate] == yystate_stack_[0])
      yystate = yytable_[yystate];
    else
      yystate = yydefgoto_[yyn - yyntokens_];
    goto yynewstate;

  /*------------------------------------.
  | yyerrlab -- here on detecting error |
  `------------------------------------*/
  yyerrlab:
    /* If not already recovering from an error, report this error.  */
    if (!yyerrstatus_)
      {
	++yynerrs_;
	error (yylloc, yysyntax_error_ (yystate, yytoken));
      }

    yyerror_range[0] = yylloc;
    if (yyerrstatus_ == 3)
      {
	/* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

	if (yychar <= yyeof_)
	  {
	  /* Return failure if at end of input.  */
	  if (yychar == yyeof_)
	    YYABORT;
	  }
	else
	  {
	    yydestruct_ ("Error: discarding", yytoken, &yylval, &yylloc);
	    yychar = yyempty_;
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
    if (false)
      goto yyerrorlab;

    yyerror_range[0] = yylocation_stack_[yylen - 1];
    /* Do not reclaim the symbols of the rule which action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    yystate = yystate_stack_[0];
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;	/* Each real token shifted decrements this.  */

    for (;;)
      {
	yyn = yypact_[yystate];
	if (yyn != yypact_ninf_)
	{
	  yyn += yyterror_;
	  if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
	    {
	      yyn = yytable_[yyn];
	      if (0 < yyn)
		break;
	    }
	}

	/* Pop the current state because it cannot handle the error token.  */
	if (yystate_stack_.height () == 1)
	YYABORT;

	yyerror_range[0] = yylocation_stack_[0];
	yydestruct_ ("Error: popping",
		     yystos_[yystate],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);
	yypop_ ();
	yystate = yystate_stack_[0];
	YY_STACK_PRINT ();
      }

    if (yyn == yyfinal_)
      goto yyacceptlab;

    yyerror_range[1] = yylloc;
    // Using YYLLOC is tempting, but would change the location of
    // the look-ahead.  YYLOC is available though.
    YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yyloc);

    /* Shift the error token.  */
    YY_SYMBOL_PRINT ("Shifting", yystos_[yyn],
		   &yysemantic_stack_[0], &yylocation_stack_[0]);

    yystate = yyn;
    goto yynewstate;

    /* Accept.  */
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    /* Abort.  */
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (yychar != yyeof_ && yychar != yyempty_)
      yydestruct_ ("Cleanup: discarding lookahead", yytoken, &yylval, &yylloc);

    /* Do not reclaim the symbols of the rule which action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (yystate_stack_.height () != 1)
      {
	yydestruct_ ("Cleanup: popping",
		   yystos_[yystate_stack_[0]],
		   &yysemantic_stack_[0],
		   &yylocation_stack_[0]);
	yypop_ ();
      }

    return yyresult;
  }

  // Generate an error message.
  std::string
  HolidayParserPlan::yysyntax_error_ (int yystate, int tok)
  {
    std::string res;
    YYUSE (yystate);
#if YYERROR_VERBOSE
    int yyn = yypact_[yystate];
    if (yypact_ninf_ < yyn && yyn <= yylast_)
      {
	/* Start YYX at -YYN if negative to avoid negative indexes in
	   YYCHECK.  */
	int yyxbegin = yyn < 0 ? -yyn : 0;

	/* Stay within bounds of both yycheck and yytname.  */
	int yychecklim = yylast_ - yyn + 1;
	int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
	int count = 0;
	for (int x = yyxbegin; x < yyxend; ++x)
	  if (yycheck_[x + yyn] == x && x != yyterror_)
	    ++count;

	// FIXME: This method of building the message is not compatible
	// with internationalization.  It should work like yacc.c does it.
	// That is, first build a string that looks like this:
	// "syntax error, unexpected %s or %s or %s"
	// Then, invoke YY_ on this string.
	// Finally, use the string as a format to output
	// yytname_[tok], etc.
	// Until this gets fixed, this message appears in English only.
	res = "syntax error, unexpected ";
	res += yytnamerr_ (yytname_[tok]);
	if (count < 5)
	  {
	    count = 0;
	    for (int x = yyxbegin; x < yyxend; ++x)
	      if (yycheck_[x + yyn] == x && x != yyterror_)
		{
		  res += (!count++) ? ", expecting " : " or ";
		  res += yytnamerr_ (yytname_[x]);
		}
	  }
      }
    else
#endif
      res = YY_("syntax error");
    return res;
  }


  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
  const signed char HolidayParserPlan::yypact_ninf_ = -121;
  const short int
  HolidayParserPlan::yypact_[] =
  {
       -22,     0,    24,  -121,    -1,  -121,  -121,     8,    32,    12,
    -121,    38,  -121,    39,  -121,  -121,    41,  -121,  -121,    58,
    -121,    60,  -121,    96,  -121,  -121,   105,  -121,   132,    11,
      11,    68,   119,  -121,    11,    40,   132,    -3,  -121,   119,
     119,    61,   127,  -121,    61,    61,  -121,   119,    62,   158,
    -121,    67,   132,   132,    86,   140,   132,   205,   205,   119,
    -121,    11,     2,  -121,  -121,    48,   132,  -121,  -121,  -121,
      46,    70,   132,     7,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,  -121,    87,
      61,    79,  -121,   127,    61,   132,    77,  -121,  -121,  -121,
     205,    61,   132,  -121,   132,  -121,  -121,    93,   127,   245,
     245,   245,   245,   245,   245,   225,   245,    56,    56,    48,
      48,    48,   184,    91,   109,  -121,   132,    11,  -121,  -121,
     119,  -121,  -121,  -121,   127,    88,   119,    87,    87,  -121,
      61,   205,  -121,  -121,  -121,  -121,  -121,  -121
  };

  /* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
     doesn't specify something else to do.  Zero means the default is an
     error.  */
  const unsigned char
  HolidayParserPlan::yydefact_[] =
  {
         4,     0,     0,    10,     6,     5,     1,    12,     0,     8,
      13,    14,     7,     0,     3,    15,     0,     9,    18,    16,
      17,    19,    20,     0,    81,    61,    28,    83,     0,    28,
      28,     0,     0,    11,    28,     0,    59,    48,    80,     0,
       0,    36,     0,    84,    36,    36,    82,     0,     0,     0,
      62,    31,     0,    43,    28,     0,    45,    29,    30,     0,
      24,    28,    48,    21,    22,    77,     0,    49,    50,    51,
       0,     0,    59,    60,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    79,    33,
      36,    41,    44,     0,    36,    61,    38,    59,    60,    46,
      37,    36,     0,    78,     0,    56,    55,     0,     0,    65,
      66,    67,    68,    69,    70,    63,    64,    72,    71,    73,
      74,    75,     0,    34,     0,    23,     0,    28,    25,    47,
      39,    27,    57,    54,     0,    52,     0,    33,    33,    42,
      36,    40,    58,    53,    76,    35,    32,    26
  };

  /* YYPGOTO[NTERM-NUM].  */
  const signed char
  HolidayParserPlan::yypgoto_[] =
  {
      -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,
    -121,  -121,  -121,   -20,  -121,  -120,   -17,    84,  -121,   -10,
     124,   -24,   -23,  -121
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const signed char
  HolidayParserPlan::yydefgoto_[] =
  {
        -1,     2,     3,     4,     9,    14,     7,    11,    16,    21,
      19,    23,    33,    41,    90,   124,    60,    34,    70,    35,
      97,    49,    50,    38
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If zero, do what YYDEFACT says.  */
  const signed char HolidayParserPlan::yytable_ninf_ = -61;
  const short int
  HolidayParserPlan::yytable_[] =
  {
        37,    25,    54,    42,     1,    43,    25,     5,    -2,    44,
      45,   106,   107,    53,    51,    57,    58,   145,   146,    62,
      10,    39,    40,    65,     6,    73,     8,    63,    64,    91,
      92,   -60,    98,    99,    94,   100,   -60,    55,    71,    12,
      13,   101,    55,   102,    15,    96,    17,   108,    18,   105,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,    20,    24,    25,    66,    22,    67,
      98,    46,   129,   125,    52,    27,    28,   128,    59,   132,
      68,   133,    89,   127,   131,    98,    87,    69,   103,    84,
      85,    86,   123,    31,    87,    93,    39,    40,   135,    24,
      25,    26,   134,   139,   104,    32,   141,   140,    24,    27,
      28,    98,   144,   126,    29,    39,    40,   130,    27,    28,
     137,    30,    24,   147,   142,   138,    61,    31,   143,     0,
      24,    25,    27,    28,     0,    24,    31,     0,     0,    32,
      27,    28,     0,    24,    95,    27,    28,    36,    32,     0,
      31,     0,     0,    27,    28,    47,     0,     0,    31,     0,
      48,    56,    32,    31,     0,     0,    36,     0,     0,     0,
      32,    31,    72,     0,     0,    32,     0,    74,    75,    76,
      77,    78,    79,    32,     0,     0,    56,    80,    81,    82,
      83,    84,    85,    86,     0,     0,    87,     0,     0,     0,
       0,     0,    88,    74,    75,    76,    77,    78,    79,     0,
       0,     0,     0,    80,    81,    82,    83,    84,    85,    86,
       0,     0,    87,   136,    74,    75,    76,    77,    78,    79,
       0,     0,     0,     0,    80,    81,    82,    83,    84,    85,
      86,     0,     0,    87,    74,    75,    76,    77,    78,    79,
       0,     0,     0,     0,     0,    81,    82,    83,    84,    85,
      86,     0,     0,    87,    74,    75,    76,    77,    78,    79,
       0,     0,     0,     0,     0,     0,    82,    83,    84,    85,
      86,     0,     0,    87
  };

  /* YYCHECK.  */
  const short int
  HolidayParserPlan::yycheck_[] =
  {
        23,     4,     5,    26,    26,    28,     4,     7,     0,    29,
      30,     4,     5,    36,    34,    39,    40,   137,   138,    42,
      12,    10,    11,    47,     0,    48,    27,    44,    45,    52,
      53,    34,    55,    56,    54,    59,    34,    40,    48,     7,
      28,    61,    40,    66,     6,    55,     7,    40,     7,    72,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,     6,     3,     4,     5,     8,     7,
      93,     3,    95,    90,    34,    13,    14,    94,    17,   102,
      18,   104,    15,    93,   101,   108,    38,    25,    42,    33,
      34,    35,     5,    31,    38,     9,    10,    11,   108,     3,
       4,     5,     9,   126,    34,    43,   130,   127,     3,    13,
      14,   134,   136,    34,    18,    10,    11,    40,    13,    14,
      29,    25,     3,   140,   134,    16,    42,    31,    40,    -1,
       3,     4,    13,    14,    -1,     3,    31,    -1,    -1,    43,
      13,    14,    -1,     3,     4,    13,    14,    23,    43,    -1,
      31,    -1,    -1,    13,    14,    36,    -1,    -1,    31,    -1,
      41,    37,    43,    31,    -1,    -1,    42,    -1,    -1,    -1,
      43,    31,    48,    -1,    -1,    43,    -1,    19,    20,    21,
      22,    23,    24,    43,    -1,    -1,    62,    29,    30,    31,
      32,    33,    34,    35,    -1,    -1,    38,    -1,    -1,    -1,
      -1,    -1,    44,    19,    20,    21,    22,    23,    24,    -1,
      -1,    -1,    -1,    29,    30,    31,    32,    33,    34,    35,
      -1,    -1,    38,    39,    19,    20,    21,    22,    23,    24,
      -1,    -1,    -1,    -1,    29,    30,    31,    32,    33,    34,
      35,    -1,    -1,    38,    19,    20,    21,    22,    23,    24,
      -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    -1,    -1,    38,    19,    20,    21,    22,    23,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,
      35,    -1,    -1,    38
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  HolidayParserPlan::yystos_[] =
  {
         0,    26,    46,    47,    48,     7,     0,    51,    27,    49,
      12,    52,     7,    28,    50,     6,    53,     7,     7,    55,
       6,    54,     8,    56,     3,     4,     5,    13,    14,    18,
      25,    31,    43,    57,    62,    64,    65,    67,    68,    10,
      11,    58,    67,    67,    58,    58,     3,    36,    41,    66,
      67,    58,    34,    67,     5,    40,    65,    66,    66,    17,
      61,    62,    67,    61,    61,    66,     5,     7,    18,    25,
      63,    64,    65,    67,    19,    20,    21,    22,    23,    24,
      29,    30,    31,    32,    33,    34,    35,    38,    44,    15,
      59,    67,    67,     9,    58,     4,    64,    65,    67,    67,
      66,    58,    67,    42,    34,    67,     4,     5,    40,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    66,     5,    60,    61,    34,    64,    61,    67,
      40,    61,    67,    67,     9,    64,    39,    29,    16,    67,
      58,    66,    64,    40,    66,    60,    60,    61
  };

#if YYDEBUG
  /* TOKEN_NUMBER_[YYLEX-NUM] -- Internal symbol number corresponding
     to YYLEX-NUM.  */
  const unsigned short int
  HolidayParserPlan::yytoken_number_[] =
  {
         0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,    45,    43,    42,    47,    37,    33,   286,    63,    58,
      46,    91,    93,    40,    41
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  HolidayParserPlan::yyr1_[] =
  {
         0,    45,    46,    47,    48,    48,    49,    49,    50,    50,
      51,    51,    52,    52,    53,    53,    54,    54,    55,    56,
      56,    57,    57,    57,    57,    57,    57,    57,    58,    58,
      58,    59,    59,    60,    60,    60,    61,    61,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    64,
      64,    65,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    67,
      67,    68,    68,    68,    68
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  HolidayParserPlan::yyr2_[] =
  {
         0,     2,     2,     3,     0,     2,     0,     2,     0,     2,
       0,     7,     0,     1,     0,     1,     0,     1,     1,     0,
       1,     3,     3,     4,     3,     4,     6,     5,     0,     2,
       2,     0,     4,     0,     1,     3,     0,     2,     3,     4,
       5,     3,     5,     2,     3,     2,     3,     4,     1,     1,
       1,     1,     3,     4,     3,     2,     2,     3,     4,     1,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     5,     2,     3,     3,
       1,     1,     2,     1,     2
  };

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
  /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
     First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
  const char*
  const HolidayParserPlan::yytname_[] =
  {
    "END", "error", "$undefined", "NUMBER", "MONTH", "WDAY", "COLOR",
  "STRING", "CALENDAR", "IN", "PLUS", "MINUS", "SMALL", "YEAR", "LEAPYEAR",
  "SHIFT", "IF", "LENGTH", "EASTER", "EQ", "NE", "LE", "GE", "LT", "GT",
  "PASCHA", "REGION", "LANGUAGE", "SHORTNAME", "OR", "AND", "'-'", "'+'",
  "'*'", "'/'", "'%'", "'!'", "UMINUS", "'?'", "':'", "'.'", "'['", "']'",
  "'('", "')'", "$accept", "planfile", "metadata", "regioncode",
  "languagecode", "shortname", "list", "small", "stringcolor", "daycolor",
  "eventname", "calendar", "eventrule", "offset", "conditionaloffset",
  "wdaycondition", "length", "date", "reldate", "month", "monthnumber",
  "expr", "pexpr", "number", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const HolidayParserPlan::rhs_number_type
  HolidayParserPlan::yyrhs_[] =
  {
        46,     0,    -1,    47,    51,    -1,    48,    49,    50,    -1,
      -1,    26,     7,    -1,    -1,    27,     7,    -1,    -1,    28,
       7,    -1,    -1,    51,    52,    53,    55,    54,    56,    57,
      -1,    -1,    12,    -1,    -1,     6,    -1,    -1,     6,    -1,
       7,    -1,    -1,     8,    -1,    18,    58,    61,    -1,    25,
      58,    61,    -1,    62,    58,    59,    61,    -1,     5,    58,
      61,    -1,    67,     5,    58,    61,    -1,    67,     5,     9,
      64,    58,    61,    -1,     5,    67,    62,    58,    61,    -1,
      -1,    10,    66,    -1,    11,    66,    -1,    -1,    15,    60,
      16,    60,    -1,    -1,     5,    -1,     5,    29,    60,    -1,
      -1,    17,    66,    -1,    67,    40,    64,    -1,    67,    40,
      64,    40,    -1,    67,    40,    64,    40,    66,    -1,    64,
      34,    67,    -1,    64,    34,    67,    34,    67,    -1,    65,
      67,    -1,    65,    67,    67,    -1,    67,    65,    -1,    67,
      65,    67,    -1,    67,    40,     4,    67,    -1,    67,    -1,
       7,    -1,    18,    -1,    25,    -1,    67,    40,    64,    -1,
      67,    40,    64,    40,    -1,    64,    34,    67,    -1,    67,
       4,    -1,    65,    67,    -1,     5,    67,    67,    -1,    67,
       5,     9,    64,    -1,    65,    -1,    67,    -1,     4,    -1,
      67,    -1,    66,    29,    66,    -1,    66,    30,    66,    -1,
      66,    19,    66,    -1,    66,    20,    66,    -1,    66,    21,
      66,    -1,    66,    22,    66,    -1,    66,    23,    66,    -1,
      66,    24,    66,    -1,    66,    32,    66,    -1,    66,    31,
      66,    -1,    66,    33,    66,    -1,    66,    34,    66,    -1,
      66,    35,    66,    -1,    66,    38,    66,    39,    66,    -1,
      36,    66,    -1,    41,    63,    42,    -1,    43,    66,    44,
      -1,    68,    -1,     3,    -1,    31,     3,    -1,    13,    -1,
      14,    67,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned short int
  HolidayParserPlan::yyprhs_[] =
  {
         0,     0,     3,     6,    10,    11,    14,    15,    18,    19,
      22,    23,    31,    32,    34,    35,    37,    38,    40,    42,
      43,    45,    49,    53,    58,    62,    67,    74,    80,    81,
      84,    87,    88,    93,    94,    96,   100,   101,   104,   108,
     113,   119,   123,   129,   132,   136,   139,   143,   148,   150,
     152,   154,   156,   160,   165,   169,   172,   175,   179,   184,
     186,   188,   190,   192,   196,   200,   204,   208,   212,   216,
     220,   224,   228,   232,   236,   240,   244,   250,   253,   257,
     261,   263,   265,   268,   270
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned char
  HolidayParserPlan::yyrline_[] =
  {
         0,    95,    95,    98,   101,   102,   105,   106,   109,   110,
     113,   114,   117,   118,   121,   122,   125,   126,   129,   132,
     133,   136,   137,   138,   139,   140,   141,   142,   145,   146,
     147,   150,   151,   154,   155,   156,   159,   160,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   188,
     189,   192,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   214,
     215,   218,   219,   220,   221
  };

  // Print the state stack on the debug stream.
  void
  HolidayParserPlan::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (state_stack_type::const_iterator i = yystate_stack_.begin ();
	 i != yystate_stack_.end (); ++i)
      *yycdebug_ << ' ' << *i;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  HolidayParserPlan::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    /* Print the symbols being reduced, and their result.  */
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
	       << " (line " << yylno << "), ";
    /* The symbols being reduced.  */
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
		       yyrhs_[yyprhs_[yyrule] + yyi],
		       &(yysemantic_stack_[(yynrhs) - (yyi + 1)]),
		       &(yylocation_stack_[(yynrhs) - (yyi + 1)]));
  }
#endif // YYDEBUG

  /* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
  HolidayParserPlan::token_number_type
  HolidayParserPlan::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
           0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    36,     2,     2,     2,    35,     2,     2,
      43,    44,    33,    32,     2,    31,    40,    34,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    39,     2,
       2,     2,     2,    38,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    41,     2,    42,     2,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    37
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int HolidayParserPlan::yyeof_ = 0;
  const int HolidayParserPlan::yylast_ = 283;
  const int HolidayParserPlan::yynnts_ = 24;
  const int HolidayParserPlan::yyempty_ = -2;
  const int HolidayParserPlan::yyfinal_ = 6;
  const int HolidayParserPlan::yyterror_ = 1;
  const int HolidayParserPlan::yyerrcode_ = 256;
  const int HolidayParserPlan::yyntokens_ = 45;

  const unsigned int HolidayParserPlan::yyuser_token_number_max_ = 286;
  const HolidayParserPlan::token_number_type HolidayParserPlan::yyundef_token_ = 2;

} // namespace KHolidays

#line 223 "holidayparserplan.ypp"


/*** Private Yacc callbacks and helper functions ***/

void KHolidays::HolidayParserPlan::error( const KHolidays::HolidayParserPlan::location_type &errorLocation, const std::string &errorMessage )
{
    driver.error( errorLocation, errorMessage.c_str() );
}

