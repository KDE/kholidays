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

#ifndef KHOLIDAYS_HOLIDAYPARSERDRIVER_P_H
#define KHOLIDAYS_HOLIDAYPARSERDRIVER_P_H

#include "qcalendarsystem_p.h"

#include <QDate>
#include <QString>

#include "holiday.h"

namespace KHolidays {

/**
 * HolidayParserDriver abstract base class
 *
 * Defines a standard interface for parsing holiday files of various formats
 *
 * Derived classes must implemet method parse(), other methods should work for
 * most circumstances
 *
 * @internal Private, for internal use only
 */
class HolidayParserDriver
{
  public:

    /**
     * Constructor of abstract holiday file parser driver class.
     * This will be called by derived classes.
     *
     * @param filePath full path to holiday file
     */
    explicit HolidayParserDriver( const QString &filePath );

    /**
     * Destructor.
     */
    virtual ~HolidayParserDriver();

    /**
     * Return the ISO 3166 country/region code of the file
     *
     * May be either just a country code ("US" = USA) or may include a regional
     * identifier ("US-CA" = California).  Returns "XX" if not a country.
     *
     * @return the full country code of the file
     */
    virtual QString fileCountryCode() const;

    /**
     * Return the ISO 639-1 language code of the file
     *
     * May be either just a language code ("en" = US English) or may include a country
     * identifier ("en_GB" = British English).
     *
     * @return the language code of the file
     */
    virtual QString fileLanguageCode() const;

    /**
     * Return the untranslated name of the file
     *
     * @return the untranslated name code of the file
     */
    virtual QString fileName() const;

    /**
     * Return the untranslated description of the file if available
     *
     * @return the untranslated description of the file
     */
    virtual QString fileDescription() const;

    /**
     * Return a list of holidays falling between any two dates
     *
     * @param startDate start date of the holiday parse range
     * @param endDate end date of the holiday parse range
     *
     * @return a list of holidays
     */
    virtual Holiday::List parseHolidays( const QDate &startDate, const QDate &endDate );

    /**
     * Convenience function
     * Return a list of holidays falling on a given date
     *
     * @param date date to return holidays for
     *
     * @return a list of holidays
     */
    virtual Holiday::List parseHolidays( const QDate &date );

    /**
     * Convenience function
     * Return a list of holidays falling in a given calendar year
     *
     * @param calendarYear year to return holidays for
     * @param calendar calendar system of year
     *
     * @return a list of holidays
     */
    virtual Holiday::List parseHolidays( int calendarYear,
                                         QCalendarSystem::CalendarSystem calendar = QCalendarSystem::GregorianCalendar );

    /**
     * Standard error message handling
     *
     * @param errorMessage error message to log
     */
    virtual void error( const QString &errorMessage );

  protected:
    /**
     * Actually parse the file, must be re-implemented by derived classes
     */
    virtual void parse();

    /**
     * Parse the file for metadata only and populate the metadata variables
     */
    virtual void parseMetadata();

    /**
     * Set the calendar system to use
     *
     * @param calendar The QCalendarSystem calendar system to use
     */
    virtual void setParseCalendar( QCalendarSystem::CalendarSystem calendar );

    /**
     * Initialise parse year variables for calendar system
     */
    virtual void setParseStartEnd();

    QString          m_filePath;           // File to be parsed

    QString          m_fileCountryCode;    // File country code in ISO 3166-2 standard
    QString          m_fileLanguageCode;   // File language
    QString          m_fileName;           // File name
    QString          m_fileDescription;    // File description

    QDate            m_requestStart;       // First day of period being requested
    QDate            m_requestEnd;         // Last day of period being requested

    Holiday::List    m_resultList;         // List of requested holidays

    QCalendarSystem  m_parseCalendar;      // Calendar system being parsed
    int              m_parseYear;          // Year currently being parsed
    int              m_parseStartYear;     // First year to parse in parse calendar
    int              m_parseEndYear;       // Last year to parse in parse calendar
};

}

#endif // KHOLIDAYS_HOLIDAYPARSERDRIVER_P_H
