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
    { driver.setFileCountryCode( QString() ); ;}
    break;

  case 5:
#line 102 "holidayparserplan.ypp"
    { driver.setFileCountryCode( QString::fromUtf8( (yysemantic_stack_[(2) - (2)].sval) ) ); ;}
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
    { driver.setFileName( QString() ); ;}
    break;

  case 9:
#line 110 "holidayparserplan.ypp"
    { driver.setFileName( QString::fromUtf8( (yysemantic_stack_[(2) - (2)].sval) ) ); ;}
    break;

  case 10:
#line 113 "holidayparserplan.ypp"
    { driver.setFileDescription( QString() ); ;}
    break;

  case 11:
#line 114 "holidayparserplan.ypp"
    { driver.setFileDescription( QString::fromUtf8( (yysemantic_stack_[(2) - (2)].sval) ) ); ;}
    break;

  case 16:
#line 125 "holidayparserplan.ypp"
    { driver.setEventColorName( 0 ); ;}
    break;

  case 17:
#line 126 "holidayparserplan.ypp"
    { driver.setEventColorName( (yysemantic_stack_[(1) - (1)].ival) ); ;}
    break;

  case 18:
#line 129 "holidayparserplan.ypp"
    { driver.setEventColorDay( 0 ); ;}
    break;

  case 19:
#line 130 "holidayparserplan.ypp"
    { driver.setEventColorDay( (yysemantic_stack_[(1) - (1)].ival) ); ;}
    break;

  case 20:
#line 133 "holidayparserplan.ypp"
    { driver.setEventName( QString::fromUtf8( (yysemantic_stack_[(1) - (1)].sval) ) ); ;}
    break;

  case 21:
#line 136 "holidayparserplan.ypp"
    { driver.setEventCalendarType( "gregorian" ); ;}
    break;

  case 22:
#line 137 "holidayparserplan.ypp"
    { driver.setEventCalendarType( QString::fromUtf8( (yysemantic_stack_[(1) - (1)].sval) ) ); ;}
    break;

  case 23:
#line 140 "holidayparserplan.ypp"
    { driver.setFromEaster( (yysemantic_stack_[(3) - (2)].ival), (yysemantic_stack_[(3) - (3)].ival) ); ;}
    break;

  case 24:
#line 141 "holidayparserplan.ypp"
    { driver.setFromPascha( (yysemantic_stack_[(3) - (2)].ival), (yysemantic_stack_[(3) - (3)].ival) ); ;}
    break;

  case 25:
#line 142 "holidayparserplan.ypp"
    { driver.setFromDate( (yysemantic_stack_[(4) - (2)].ival), (yysemantic_stack_[(4) - (3)].ival), (yysemantic_stack_[(4) - (4)].ival) ); ;}
    break;

  case 26:
#line 143 "holidayparserplan.ypp"
    { driver.setFromWeekdayInMonth( 1, (yysemantic_stack_[(3) - (1)].ival), 1, (yysemantic_stack_[(3) - (2)].ival), (yysemantic_stack_[(3) - (3)].ival) ); ;}
    break;

  case 27:
#line 144 "holidayparserplan.ypp"
    { driver.setFromWeekdayInMonth( (yysemantic_stack_[(4) - (1)].ival), (yysemantic_stack_[(4) - (2)].ival), 1, (yysemantic_stack_[(4) - (3)].ival), (yysemantic_stack_[(4) - (4)].ival) ); ;}
    break;

  case 28:
#line 145 "holidayparserplan.ypp"
    { driver.setFromWeekdayInMonth( (yysemantic_stack_[(6) - (1)].ival), (yysemantic_stack_[(6) - (2)].ival), (yysemantic_stack_[(6) - (4)].ival), (yysemantic_stack_[(6) - (5)].ival), (yysemantic_stack_[(6) - (6)].ival) ); ;}
    break;

  case 29:
#line 146 "holidayparserplan.ypp"
    { driver.setFromRelativeWeekday( (yysemantic_stack_[(5) - (2)].ival), (yysemantic_stack_[(5) - (1)].ival), (yysemantic_stack_[(5) - (4)].ival), (yysemantic_stack_[(5) - (5)].ival) ); ;}
    break;

  case 30:
#line 149 "holidayparserplan.ypp"
    { (yyval.ival) =   0; ;}
    break;

  case 31:
#line 150 "holidayparserplan.ypp"
    { (yyval.ival) =  (yysemantic_stack_[(2) - (2)].ival); ;}
    break;

  case 32:
#line 151 "holidayparserplan.ypp"
    { (yyval.ival) = -(yysemantic_stack_[(2) - (2)].ival); ;}
    break;

  case 33:
#line 154 "holidayparserplan.ypp"
    { (yyval.ival) = 0; ;}
    break;

  case 34:
#line 155 "holidayparserplan.ypp"
    { (yyval.ival) = ( (yysemantic_stack_[(4) - (2)].ival) << 8 ) | (yysemantic_stack_[(4) - (4)].ival); ;}
    break;

  case 35:
#line 158 "holidayparserplan.ypp"
    { (yyval.ival) = 0; ;}
    break;

  case 36:
#line 159 "holidayparserplan.ypp"
    { (yyval.ival) = ( 1 << (yysemantic_stack_[(1) - (1)].ival) ); ;}
    break;

  case 37:
#line 160 "holidayparserplan.ypp"
    { (yyval.ival) = ( 1 << (yysemantic_stack_[(3) - (1)].ival) ) | (yysemantic_stack_[(3) - (3)].ival); ;}
    break;

  case 38:
#line 163 "holidayparserplan.ypp"
    { (yyval.ival) =  1; ;}
    break;

  case 39:
#line 164 "holidayparserplan.ypp"
    { (yyval.ival) = (yysemantic_stack_[(2) - (2)].ival); ;}
    break;

  case 40:
#line 167 "holidayparserplan.ypp"
    { driver.setEventDate( -99999, (yysemantic_stack_[(3) - (3)].ival), (yysemantic_stack_[(3) - (1)].ival) ); ;}
    break;

  case 41:
#line 168 "holidayparserplan.ypp"
    { driver.setEventDate( -99999, (yysemantic_stack_[(4) - (3)].ival), (yysemantic_stack_[(4) - (1)].ival) ); ;}
    break;

  case 42:
#line 169 "holidayparserplan.ypp"
    { driver.setEventDate(     (yysemantic_stack_[(5) - (5)].ival), (yysemantic_stack_[(5) - (3)].ival), (yysemantic_stack_[(5) - (1)].ival) ); ;}
    break;

  case 43:
#line 170 "holidayparserplan.ypp"
    { driver.setEventDate( -99999, (yysemantic_stack_[(3) - (1)].ival), (yysemantic_stack_[(3) - (3)].ival) ); ;}
    break;

  case 44:
#line 171 "holidayparserplan.ypp"
    { driver.setEventDate(     (yysemantic_stack_[(5) - (5)].ival), (yysemantic_stack_[(5) - (1)].ival), (yysemantic_stack_[(5) - (3)].ival) ); ;}
    break;

  case 45:
#line 172 "holidayparserplan.ypp"
    { driver.setEventDate( -99999, (yysemantic_stack_[(2) - (1)].ival), (yysemantic_stack_[(2) - (2)].ival) ); ;}
    break;

  case 46:
#line 173 "holidayparserplan.ypp"
    { driver.setEventDate(     (yysemantic_stack_[(3) - (3)].ival), (yysemantic_stack_[(3) - (1)].ival), (yysemantic_stack_[(3) - (2)].ival) ); ;}
    break;

  case 47:
#line 174 "holidayparserplan.ypp"
    { driver.setEventDate( -99999, (yysemantic_stack_[(2) - (2)].ival), (yysemantic_stack_[(2) - (1)].ival) ); ;}
    break;

  case 48:
#line 175 "holidayparserplan.ypp"
    { driver.setEventDate(     (yysemantic_stack_[(3) - (3)].ival), (yysemantic_stack_[(3) - (2)].ival), (yysemantic_stack_[(3) - (1)].ival) ); ;}
    break;

  case 49:
#line 176 "holidayparserplan.ypp"
    { driver.setEventDate(     (yysemantic_stack_[(4) - (4)].ival), (yysemantic_stack_[(4) - (3)].ival), (yysemantic_stack_[(4) - (1)].ival) ); ;}
    break;

  case 50:
#line 177 "holidayparserplan.ypp"
    { driver.setEventDate( (yysemantic_stack_[(1) - (1)].ival) ); ;}
    break;

  case 51:
#line 180 "holidayparserplan.ypp"
    { (yyval.ival) = driver.julianDayFromEventName( (yysemantic_stack_[(1) - (1)].sval) ); ;}
    break;

  case 52:
#line 181 "holidayparserplan.ypp"
    { (yyval.ival) = driver.julianDayFromEaster(); ;}
    break;

  case 53:
#line 182 "holidayparserplan.ypp"
    { (yyval.ival) = driver.julianDayFromPascha(); ;}
    break;

  case 54:
#line 183 "holidayparserplan.ypp"
    { (yyval.ival) = driver.julianDayFromMonthDay( (yysemantic_stack_[(3) - (3)].ival), (yysemantic_stack_[(3) - (1)].ival) ); ;}
    break;

  case 55:
#line 184 "holidayparserplan.ypp"
    { (yyval.ival) = driver.julianDayFromMonthDay( (yysemantic_stack_[(4) - (3)].ival), (yysemantic_stack_[(4) - (1)].ival) ); ;}
    break;

  case 56:
#line 185 "holidayparserplan.ypp"
    { (yyval.ival) = driver.julianDayFromMonthDay( (yysemantic_stack_[(3) - (1)].ival), (yysemantic_stack_[(3) - (3)].ival) ); ;}
    break;

  case 57:
#line 186 "holidayparserplan.ypp"
    { (yyval.ival) = driver.julianDayFromMonthDay( (yysemantic_stack_[(2) - (2)].ival), (yysemantic_stack_[(2) - (1)].ival) ); ;}
    break;

  case 58:
#line 187 "holidayparserplan.ypp"
    { (yyval.ival) = driver.julianDayFromMonthDay( (yysemantic_stack_[(2) - (1)].ival), (yysemantic_stack_[(2) - (2)].ival) ); ;}
    break;

  case 59:
#line 188 "holidayparserplan.ypp"
    { (yyval.ival) = driver.julianDayFromRelativeWeekday( (yysemantic_stack_[(3) - (2)].ival), (yysemantic_stack_[(3) - (1)].ival), (yysemantic_stack_[(3) - (3)].ival) ); ;}
    break;

  case 60:
#line 189 "holidayparserplan.ypp"
    { (yyval.ival) = driver.julianDayFromWeekdayInMonth( (yysemantic_stack_[(4) - (1)].ival), (yysemantic_stack_[(4) - (2)].ival), (yysemantic_stack_[(4) - (4)].ival) ); ;}
    break;

  case 62:
#line 193 "holidayparserplan.ypp"
    { (yyval.ival) = driver.adjustedMonthNumber( (yysemantic_stack_[(1) - (1)].ival) ); ;}
    break;

  case 63:
#line 196 "holidayparserplan.ypp"
    { (yyval.ival) = driver.adjustedMonthNumber( (yysemantic_stack_[(1) - (1)].ival) ); ;}
    break;

  case 64:
#line 199 "holidayparserplan.ypp"
    { (yyval.ival) = (yysemantic_stack_[(1) - (1)].ival); ;}
    break;

  case 65:
#line 200 "holidayparserplan.ypp"
    { (yyval.ival) = (yysemantic_stack_[(3) - (1)].ival) || (yysemantic_stack_[(3) - (3)].ival); ;}
    break;

  case 66:
#line 201 "holidayparserplan.ypp"
    { (yyval.ival) = (yysemantic_stack_[(3) - (1)].ival) && (yysemantic_stack_[(3) - (3)].ival); ;}
    break;

  case 67:
#line 202 "holidayparserplan.ypp"
    { (yyval.ival) = (yysemantic_stack_[(3) - (1)].ival) == (yysemantic_stack_[(3) - (3)].ival); ;}
    break;

  case 68:
#line 203 "holidayparserplan.ypp"
    { (yyval.ival) = (yysemantic_stack_[(3) - (1)].ival) != (yysemantic_stack_[(3) - (3)].ival); ;}
    break;

  case 69:
#line 204 "holidayparserplan.ypp"
    { (yyval.ival) = (yysemantic_stack_[(3) - (1)].ival) <= (yysemantic_stack_[(3) - (3)].ival); ;}
    break;

  case 70:
#line 205 "holidayparserplan.ypp"
    { (yyval.ival) = (yysemantic_stack_[(3) - (1)].ival) >= (yysemantic_stack_[(3) - (3)].ival); ;}
    break;

  case 71:
#line 206 "holidayparserplan.ypp"
    { (yyval.ival) = (yysemantic_stack_[(3) - (1)].ival) <  (yysemantic_stack_[(3) - (3)].ival); ;}
    break;

  case 72:
#line 207 "holidayparserplan.ypp"
    { (yyval.ival) = (yysemantic_stack_[(3) - (1)].ival) >  (yysemantic_stack_[(3) - (3)].ival); ;}
    break;

  case 73:
#line 208 "holidayparserplan.ypp"
    { (yyval.ival) = (yysemantic_stack_[(3) - (1)].ival) +  (yysemantic_stack_[(3) - (3)].ival); ;}
    break;

  case 74:
#line 209 "holidayparserplan.ypp"
    { (yyval.ival) = (yysemantic_stack_[(3) - (1)].ival) -  (yysemantic_stack_[(3) - (3)].ival); ;}
    break;

  case 75:
#line 210 "holidayparserplan.ypp"
    { (yyval.ival) = (yysemantic_stack_[(3) - (1)].ival) *  (yysemantic_stack_[(3) - (3)].ival); ;}
    break;

  case 76:
#line 211 "holidayparserplan.ypp"
    { (yyval.ival) = (yysemantic_stack_[(3) - (3)].ival) ?  (yysemantic_stack_[(3) - (1)].ival) / (yysemantic_stack_[(3) - (3)].ival) : 0; ;}
    break;

  case 77:
#line 212 "holidayparserplan.ypp"
    { (yyval.ival) = (yysemantic_stack_[(3) - (3)].ival) ?  (yysemantic_stack_[(3) - (1)].ival) % (yysemantic_stack_[(3) - (3)].ival) : 0; ;}
    break;

  case 78:
#line 213 "holidayparserplan.ypp"
    { (yyval.ival) = (yysemantic_stack_[(5) - (1)].ival) ?  (yysemantic_stack_[(5) - (3)].ival) : (yysemantic_stack_[(5) - (5)].ival); ;}
    break;

  case 79:
#line 214 "holidayparserplan.ypp"
    { (yyval.ival) = !(yysemantic_stack_[(2) - (2)].ival); ;}
    break;

  case 80:
#line 215 "holidayparserplan.ypp"
    { (yyval.ival) = (yysemantic_stack_[(3) - (2)].ival); ;}
    break;

  case 81:
#line 218 "holidayparserplan.ypp"
    { (yyval.ival) = (yysemantic_stack_[(3) - (2)].ival); ;}
    break;

  case 82:
#line 219 "holidayparserplan.ypp"
    { (yyval.ival) = (yysemantic_stack_[(1) - (1)].ival); ;}
    break;

  case 84:
#line 223 "holidayparserplan.ypp"
    { (yyval.ival) = -(yysemantic_stack_[(2) - (2)].ival); ;}
    break;

  case 85:
#line 224 "holidayparserplan.ypp"
    { (yyval.ival) = driver.parseYear(); ;}
    break;

  case 86:
#line 225 "holidayparserplan.ypp"
    { (yyval.ival) = driver.isLeapYear( (yysemantic_stack_[(2) - (2)].ival) ); ;}
    break;


    /* Line 675 of lalr1.cc.  */
#line 789 "holidayparserplan.cpp"
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
  const short int HolidayParserPlan::yypact_ninf_ = -130;
  const short int
  HolidayParserPlan::yypact_[] =
  {
       -22,    10,    24,  -130,    -1,  -130,  -130,     6,    29,    12,
    -130,    25,  -130,    32,    13,  -130,    39,  -130,    60,  -130,
    -130,    62,  -130,  -130,    72,  -130,   115,  -130,  -130,   128,
    -130,   131,    -9,    -9,    66,    34,  -130,    -9,    47,   131,
     117,  -130,    34,    34,    74,    61,  -130,    74,    74,  -130,
      34,    83,   157,  -130,    77,   131,   131,    11,   122,   131,
     206,   206,    34,  -130,    -9,   126,  -130,  -130,    50,   131,
    -130,  -130,  -130,    51,    64,   131,     3,    34,    34,    34,
      34,    34,    34,    34,    34,    34,    34,    34,    34,    34,
      34,  -130,    90,    74,    65,  -130,    61,    74,   131,    63,
    -130,  -130,  -130,   206,    74,   131,  -130,   131,  -130,  -130,
      93,    61,   248,   248,   248,   248,   248,   248,   227,   248,
     114,   114,    50,    50,    50,   184,    79,    94,  -130,   131,
      -9,  -130,  -130,    34,  -130,  -130,  -130,    61,    73,    34,
      90,    90,  -130,    74,   206,  -130,  -130,  -130,  -130,  -130,
    -130
  };

  /* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
     doesn't specify something else to do.  Zero means the default is an
     error.  */
  const unsigned char
  HolidayParserPlan::yydefact_[] =
  {
         4,     0,     0,    12,     6,     5,     1,    14,     0,     8,
      15,    16,     7,     0,    10,    17,     0,     9,     0,     3,
      20,    18,    11,    19,    21,    22,     0,    83,    63,    30,
      85,     0,    30,    30,     0,     0,    13,    30,     0,    61,
      50,    82,     0,     0,    38,     0,    86,    38,    38,    84,
       0,     0,     0,    64,    33,     0,    45,    30,     0,    47,
      31,    32,     0,    26,    30,    50,    23,    24,    79,     0,
      51,    52,    53,     0,     0,    61,    62,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    81,    35,    38,    43,    46,     0,    38,    63,    40,
      61,    62,    48,    39,    38,     0,    80,     0,    58,    57,
       0,     0,    67,    68,    69,    70,    71,    72,    65,    66,
      74,    73,    75,    76,    77,     0,    36,     0,    25,     0,
      30,    27,    49,    41,    29,    59,    56,     0,    54,     0,
      35,    35,    44,    38,    42,    60,    55,    78,    37,    34,
      28
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  HolidayParserPlan::yypgoto_[] =
  {
      -130,  -130,  -130,  -130,  -130,  -130,  -130,  -130,  -130,  -130,
    -130,  -130,  -130,  -130,   -23,  -130,  -129,   -20,    68,  -130,
     -13,   106,   -27,   -26,  -130
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const signed char
  HolidayParserPlan::yydefgoto_[] =
  {
        -1,     2,     3,     4,     9,    14,    19,     7,    11,    16,
      24,    21,    26,    36,    44,    93,   127,    63,    37,    73,
      38,   100,    52,    53,    41
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If zero, do what YYDEFACT says.  */
  const signed char HolidayParserPlan::yytable_ninf_ = -63;
  const short int
  HolidayParserPlan::yytable_[] =
  {
        40,    42,    43,    45,     1,    46,    -2,   109,   110,    47,
      48,   148,   149,    56,    54,    60,    61,     5,    10,    65,
      96,    42,    43,    68,     6,    76,     8,    66,    67,    94,
      95,    15,   101,   102,    97,   103,    12,    27,    74,    17,
      13,   104,    18,   105,   111,    99,    20,    30,    31,   108,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,    27,    28,    34,    22,    23,    49,
     101,    50,   132,   128,    30,    31,    51,   131,    35,   135,
      25,   136,    55,   130,   134,   101,    27,    28,    69,    90,
      70,    62,    92,    34,   106,   126,    30,    31,   138,   107,
     129,    71,   137,   142,   133,    35,   144,   143,    72,   140,
     141,   101,   147,    64,   146,    34,     0,     0,    27,    28,
      29,    28,    57,   150,   145,    27,    98,    35,    30,    31,
      28,    27,    39,    32,    27,    30,    31,     0,    42,    43,
      33,    30,    31,     0,    30,    31,    59,    34,    87,    88,
      89,    39,   -62,    90,    34,     0,     0,    75,    58,    35,
      34,   -62,     0,    34,     0,     0,    35,    58,     0,     0,
       0,    59,    35,     0,     0,    35,    77,    78,    79,    80,
      81,    82,     0,     0,     0,     0,     0,    83,    84,    85,
      86,    87,    88,    89,     0,     0,    90,     0,     0,     0,
       0,     0,    91,    77,    78,    79,    80,    81,    82,     0,
       0,     0,     0,     0,    83,    84,    85,    86,    87,    88,
      89,     0,     0,    90,   139,    77,    78,    79,    80,    81,
      82,     0,     0,     0,     0,     0,    83,    84,    85,    86,
      87,    88,    89,     0,     0,    90,    77,    78,    79,    80,
      81,    82,     0,     0,     0,     0,     0,     0,    84,    85,
      86,    87,    88,    89,     0,     0,    90,    77,    78,    79,
      80,    81,    82,     0,     0,     0,     0,     0,     0,     0,
      85,    86,    87,    88,    89,     0,     0,    90
  };

  /* YYCHECK.  */
  const short int
  HolidayParserPlan::yycheck_[] =
  {
        26,    10,    11,    29,    26,    31,     0,     4,     5,    32,
      33,   140,   141,    39,    37,    42,    43,     7,    12,    45,
       9,    10,    11,    50,     0,    51,    27,    47,    48,    55,
      56,     6,    58,    59,    57,    62,     7,     3,    51,     7,
      28,    64,    29,    69,    41,    58,     7,    13,    14,    75,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,     3,     4,    32,     7,     6,     3,
      96,    37,    98,    93,    13,    14,    42,    97,    44,   105,
       8,   107,    35,    96,   104,   111,     3,     4,     5,    39,
       7,    17,    15,    32,    43,     5,    13,    14,   111,    35,
      35,    18,     9,   129,    41,    44,   133,   130,    25,    30,
      16,   137,   139,    45,    41,    32,    -1,    -1,     3,     4,
       5,     4,     5,   143,   137,     3,     4,    44,    13,    14,
       4,     3,    26,    18,     3,    13,    14,    -1,    10,    11,
      25,    13,    14,    -1,    13,    14,    40,    32,    34,    35,
      36,    45,    35,    39,    32,    -1,    -1,    51,    41,    44,
      32,    35,    -1,    32,    -1,    -1,    44,    41,    -1,    -1,
      -1,    65,    44,    -1,    -1,    44,    19,    20,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    45,    19,    20,    21,    22,    23,    24,    -1,
      -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      36,    -1,    -1,    39,    40,    19,    20,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    39,    19,    20,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,
      33,    34,    35,    36,    -1,    -1,    39,    19,    20,    21,
      22,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      32,    33,    34,    35,    36,    -1,    -1,    39
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  HolidayParserPlan::yystos_[] =
  {
         0,    26,    47,    48,    49,     7,     0,    53,    27,    50,
      12,    54,     7,    28,    51,     6,    55,     7,    29,    52,
       7,    57,     7,     6,    56,     8,    58,     3,     4,     5,
      13,    14,    18,    25,    32,    44,    59,    64,    66,    67,
      69,    70,    10,    11,    60,    69,    69,    60,    60,     3,
      37,    42,    68,    69,    60,    35,    69,     5,    41,    67,
      68,    68,    17,    63,    64,    69,    63,    63,    68,     5,
       7,    18,    25,    65,    66,    67,    69,    19,    20,    21,
      22,    23,    24,    30,    31,    32,    33,    34,    35,    36,
      39,    45,    15,    61,    69,    69,     9,    60,     4,    66,
      67,    69,    69,    68,    60,    69,    43,    35,    69,     4,
       5,    41,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,     5,    62,    63,    35,
      66,    63,    69,    41,    63,    69,    69,     9,    66,    40,
      30,    16,    69,    60,    68,    66,    41,    68,    62,    62,
      63
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
     285,   286,    45,    43,    42,    47,    37,    33,   287,    63,
      58,    46,    91,    93,    40,    41
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  HolidayParserPlan::yyr1_[] =
  {
         0,    46,    47,    48,    49,    49,    50,    50,    51,    51,
      52,    52,    53,    53,    54,    54,    55,    55,    56,    56,
      57,    58,    58,    59,    59,    59,    59,    59,    59,    59,
      60,    60,    60,    61,    61,    62,    62,    62,    63,    63,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    66,    66,    67,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    69,    69,    70,    70,    70,    70
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  HolidayParserPlan::yyr2_[] =
  {
         0,     2,     2,     4,     0,     2,     0,     2,     0,     2,
       0,     2,     0,     7,     0,     1,     0,     1,     0,     1,
       1,     0,     1,     3,     3,     4,     3,     4,     6,     5,
       0,     2,     2,     0,     4,     0,     1,     3,     0,     2,
       3,     4,     5,     3,     5,     2,     3,     2,     3,     4,
       1,     1,     1,     1,     3,     4,     3,     2,     2,     3,
       4,     1,     1,     1,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     5,     2,
       3,     3,     1,     1,     2,     1,     2
  };

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
  /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
     First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
  const char*
  const HolidayParserPlan::yytname_[] =
  {
    "END", "error", "$undefined", "NUMBER", "MONTH", "WDAY", "COLOR",
  "STRING", "CALENDAR", "INOP", "PLUS", "MINUS", "SMALL", "YEAR",
  "LEAPYEAR", "SHIFT", "IF", "LENGTH", "EASTER", "EQ", "NE", "LE", "GE",
  "LT", "GT", "PASCHA", "COUNTRY", "LANGUAGE", "NAME", "DESCRIPTION", "OR",
  "AND", "'-'", "'+'", "'*'", "'/'", "'%'", "'!'", "UMINUS", "'?'", "':'",
  "'.'", "'['", "']'", "'('", "')'", "$accept", "planfile", "metadata",
  "countrycode", "languagecode", "name", "description", "list", "small",
  "stringcolor", "daycolor", "eventname", "calendar", "eventrule",
  "offset", "conditionaloffset", "wdaycondition", "length", "date",
  "reldate", "month", "monthnumber", "expr", "pexpr", "number", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const HolidayParserPlan::rhs_number_type
  HolidayParserPlan::yyrhs_[] =
  {
        47,     0,    -1,    48,    53,    -1,    49,    50,    51,    52,
      -1,    -1,    26,     7,    -1,    -1,    27,     7,    -1,    -1,
      28,     7,    -1,    -1,    29,     7,    -1,    -1,    53,    54,
      55,    57,    56,    58,    59,    -1,    -1,    12,    -1,    -1,
       6,    -1,    -1,     6,    -1,     7,    -1,    -1,     8,    -1,
      18,    60,    63,    -1,    25,    60,    63,    -1,    64,    60,
      61,    63,    -1,     5,    60,    63,    -1,    69,     5,    60,
      63,    -1,    69,     5,     9,    66,    60,    63,    -1,     5,
      69,    64,    60,    63,    -1,    -1,    10,    68,    -1,    11,
      68,    -1,    -1,    15,    62,    16,    62,    -1,    -1,     5,
      -1,     5,    30,    62,    -1,    -1,    17,    68,    -1,    69,
      41,    66,    -1,    69,    41,    66,    41,    -1,    69,    41,
      66,    41,    68,    -1,    66,    35,    69,    -1,    66,    35,
      69,    35,    69,    -1,    67,    69,    -1,    67,    69,    69,
      -1,    69,    67,    -1,    69,    67,    69,    -1,    69,    41,
       4,    69,    -1,    69,    -1,     7,    -1,    18,    -1,    25,
      -1,    69,    41,    66,    -1,    69,    41,    66,    41,    -1,
      66,    35,    69,    -1,    69,     4,    -1,    67,    69,    -1,
       5,    69,    69,    -1,    69,     5,     9,    66,    -1,    67,
      -1,    69,    -1,     4,    -1,    69,    -1,    68,    30,    68,
      -1,    68,    31,    68,    -1,    68,    19,    68,    -1,    68,
      20,    68,    -1,    68,    21,    68,    -1,    68,    22,    68,
      -1,    68,    23,    68,    -1,    68,    24,    68,    -1,    68,
      33,    68,    -1,    68,    32,    68,    -1,    68,    34,    68,
      -1,    68,    35,    68,    -1,    68,    36,    68,    -1,    68,
      39,    68,    40,    68,    -1,    37,    68,    -1,    42,    65,
      43,    -1,    44,    68,    45,    -1,    70,    -1,     3,    -1,
      32,     3,    -1,    13,    -1,    14,    69,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned short int
  HolidayParserPlan::yyprhs_[] =
  {
         0,     0,     3,     6,    11,    12,    15,    16,    19,    20,
      23,    24,    27,    28,    36,    37,    39,    40,    42,    43,
      45,    47,    48,    50,    54,    58,    63,    67,    72,    79,
      85,    86,    89,    92,    93,    98,    99,   101,   105,   106,
     109,   113,   118,   124,   128,   134,   137,   141,   144,   148,
     153,   155,   157,   159,   161,   165,   170,   174,   177,   180,
     184,   189,   191,   193,   195,   197,   201,   205,   209,   213,
     217,   221,   225,   229,   233,   237,   241,   245,   249,   255,
     258,   262,   266,   268,   270,   273,   275
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned char
  HolidayParserPlan::yyrline_[] =
  {
         0,    95,    95,    98,   101,   102,   105,   106,   109,   110,
     113,   114,   117,   118,   121,   122,   125,   126,   129,   130,
     133,   136,   137,   140,   141,   142,   143,   144,   145,   146,
     149,   150,   151,   154,   155,   158,   159,   160,   163,   164,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   192,   193,   196,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   218,   219,   222,   223,   224,   225
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
       2,     2,     2,    37,     2,     2,     2,    36,     2,     2,
      44,    45,    34,    33,     2,    32,    41,    35,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    40,     2,
       2,     2,     2,    39,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    42,     2,    43,     2,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    38
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int HolidayParserPlan::yyeof_ = 0;
  const int HolidayParserPlan::yylast_ = 287;
  const int HolidayParserPlan::yynnts_ = 25;
  const int HolidayParserPlan::yyempty_ = -2;
  const int HolidayParserPlan::yyfinal_ = 6;
  const int HolidayParserPlan::yyterror_ = 1;
  const int HolidayParserPlan::yyerrcode_ = 256;
  const int HolidayParserPlan::yyntokens_ = 46;

  const unsigned int HolidayParserPlan::yyuser_token_number_max_ = 287;
  const HolidayParserPlan::token_number_type HolidayParserPlan::yyundef_token_ = 2;

} // namespace KHolidays

#line 227 "holidayparserplan.ypp"


/*** Private Yacc callbacks and helper functions ***/

void KHolidays::HolidayParserPlan::error( const KHolidays::HolidayParserPlan::location_type &errorLocation, const std::string &errorMessage )
{
    driver.error( errorLocation, errorMessage.c_str() );
}

