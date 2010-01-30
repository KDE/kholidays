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

#ifndef KHOLIDAYS_HOLIDAYPARSERDRIVERPLAN_P_H
#define KHOLIDAYS_HOLIDAYPARSERDRIVERPLAN_P_H

#include "../holidayparserdriver_p.h"

// Bison C++ skeleton required include of Bison parser class implementation
#include "holidayparserplan.hpp"

// Bison C++ skeleton required declaration
# define YY_DECL                                             \
KHolidays::HolidayParserPlan::token_type                     \
yylex( KHolidays::HolidayParserPlan::semantic_type* yylval,  \
       KHolidays::HolidayParserPlan::location_type* yylloc,  \
       KHolidays::HolidayParserDriverPlan &driver )
YY_DECL;

namespace KHolidays {

/**
 * HolidayParserDriverPlan implementation class
 *
 * Implements the standard driver interface for parsing Plan holiday files as
 * implemented in KDE SC 4.5 onwards.  This includes extensions to the file
 * format to support non-Gregorian calendar systems, metadata, and other new
 * features.
 *
 * Implemented using Bison/Flex and the Bison C++ skeleton v2.1a, see README.
 * While almost all code is new, the structure of the parser is based on the
 * original Plan parser.
 *
 * @internal Private, for internal use only
 */
class HolidayParserDriverPlan : public HolidayParserDriver
{
public:

    /**
     * Constructor of Plan file parser driver
     *
     * @param filePath full path to holiday file
     */
    HolidayParserDriverPlan( const QString &planFilename );

    /**
     * Destructor.
     */
    ~HolidayParserDriverPlan();

    /**
     * Bison C++ skeleton error message handling
     *
     * @param errorMessage error message to log
     */
    void error( const KHolidays::location &errorLocation, const QString &errorMessage );

    /**
     * Standard error message handling
     *
     * @param errorMessage error message to log
     */
    void error( const QString &errorMessage );

protected:
    /**
     * Actually parse the file, new plan format implementation
     */
    void parse();

    /**
     * Parse the file for metadata only and populate the metadata variables
     */
    void parseMetadata();

    // Bison C++ skeleton required friend for Bison parser class implementation
    friend class HolidayParserPlan;

    // Accessor methods for parser to talk to driver

    QString filePath();

    // Calendar and date calculation utilities
    int   adjustedMonthNumber( int month );
    bool  isLeapYear( int year );
    int   parseYear();

    // Utilities for parser to calculate interim Julian Day Number during parsing
    int   julianDayFromEventName( const QString &eventName );
    int   julianDayFromEaster();
    int   julianDayFromPascha();
    int   julianDayFromMonthDay( int month, int day );
    int   julianDayFromRelativeWeekday( int occurrence, int weekday, int jd );
    int   julianDayFromWeekdayInMonth( int occurrence, int weekday, int month );

    // Utilities for parser to set variables during parsing
    void  setFileRegionCode( const QString &regionCode );
    void  setFileLanguageCode( const QString &languageCode );
    void  setFileShortName( const QString &shortName );
    void  setEventName( const QString &eventName );
    void  setEventColorName( int nameColor );
    void  setEventColorDay( int dayColor );
    void  setEventCalendarType( const QString &calendarType = "gregorian" );
    void  setEventDate( int eventYear, int eventMonth, int eventDay );
    void  setEventDate( int jd );

    // Terminal functions for parser to create holidays from parsed variables
    void  setFromEaster( int offset, int duration );
    void  setFromPascha( int offset, int duration );
    void  setFromDate( int offset, int condition, int duration );
    void  setFromWeekdayInMonth( int occurrence, int weekday, int month, int offset, int duration );
    void  setFromRelativeWeekday( int occurrence, int weekday, int offset, int duration );
    void  setEvent( int event_jd, int observe_offset, int duration );

private:
    // Utilites to control Flex scanner class
    void  scannerInitialise();
    void  scannerReset();
    void  scannerTerminate();

    // Calendar and date calculation utilities
    int   monthsInYear( int year );
    int   daysInMonth( int year, int month );
    int   julianDay( int year, int month, int day );
    void  julianDayToDate( int jd, int *year, int *month, int *day );
    QDate easter( int year );
    QDate pascha( int year );

    int   conditionalOffset( int year, int month, int day, int condition );

    bool               m_traceScanning;            // Bison C++ skeleton enable tracing in Flex scanner class
    bool               m_traceParsing;             // Bison C++ skeleton enable tracing in Bison parser class
    HolidayParserPlan *m_parser;                   // Bison C++ skeleton Bison parser class implementation

    QDate              m_parseYearStart;           // First day of year being parsed
    QDate              m_parseYearEaster;          // Easter in the parse year, Gregorian only
    QDate              m_parseYearPascha;          // Orthodox Easter in the parse year, Gregorian only

    QString            m_eventCalendarType;        // Calendar System for event rule
    QString            m_eventName;                // Event name text
    int                m_eventYear;                // Event date fields
    int                m_eventMonth;               // Event date fields
    int                m_eventDay;                 // Event date fields
    int                m_eventColorName;           // Color of event name text
    int                m_eventColorDay;            // Color of event day number
};

}

#endif // KHOLIDAYS_HOLIDAYPARSERDRIVERPLAN_P_H
