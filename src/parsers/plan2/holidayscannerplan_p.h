/*
    This file is part of the kholidays library.

    Copyright 2010 John Layt <john@layt.net>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#ifndef KHOLIDAYS_HOLIDAYSCANNERPLAN_P_H
#define KHOLIDAYS_HOLIDAYSCANNERPLAN_P_H

// Flex expects the signature of yylex to be defined in the macro YY_DECL, and
// the C++ parser expects it to be declared. We can factor both as follows.

#ifndef YY_DECL

#define YY_DECL                                                    \
    KHolidays::HolidayParserPlan::token_type                       \
    KHolidays::HolidayScannerPlan::lex(                            \
            KHolidays::HolidayParserPlan::semantic_type* yylval,       \
            KHolidays::HolidayParserPlan::location_type* yylloc        \
                                      )
#endif

#ifndef __FLEX_LEXER_H
#define yyFlexLexer HolidayScannerFlexLexer
#include "FlexLexer.h"
#undef yyFlexLexer
#endif

#include "holidayparserplan.hpp"

namespace KHolidays
{

/**
 * HolidayScannerPlan implementation class
 *
 * Implements the flex scanner for scanning Plan holiday files as
 * implemented in KDE SC 4.5 onwards.  This includes extensions to the file
 * format to support non-Gregorian calendar systems, metadata, and other new
 * features.
 *
 * Implemented using Flex C++ mode, based on the example at
 * http://idlebox.net/2007/flex-bison-cpp-example/ which is released to
 * Public Domain.
 *
 * @internal Private, for internal use only
 */

class HolidayScannerPlan : public HolidayScannerFlexLexer
{
public:
    HolidayScannerPlan(std::istream *arg_yyin = nullptr, std::ostream *arg_yyout = nullptr);

    ~HolidayScannerPlan() override;

    virtual HolidayParserPlan::token_type lex(HolidayParserPlan::semantic_type *yylval,
            HolidayParserPlan::location_type *yylloc);

    void set_debug(bool b);
};

} // namespace KHolidays

#endif // KHOLIDAYS_HOLIDAYSCANNERPLAN_P_H
