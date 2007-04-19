/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

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
     PASCHA = 279,
     OR = 280,
     AND = 281,
     UMINUS = 282
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
#define PASCHA 279
#define OR 280
#define AND 281
#define UMINUS 282




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 110 "parseholiday.y"
{ int ival; char *sval; }
/* Line 1529 of yacc.c.  */
#line 105 "parseholiday.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE kcallval;

