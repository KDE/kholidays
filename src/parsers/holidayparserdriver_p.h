/*
    This file is part of the kholidays library.

    SPDX-FileCopyrightText: 2010 John Layt <john@layt.net>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef KHOLIDAYS_HOLIDAYPARSERDRIVER_P_H
#define KHOLIDAYS_HOLIDAYPARSERDRIVER_P_H

#include "qcalendarsystem_p.h"

#include <QDate>
#include <QString>

#include "holiday.h"

namespace KHolidays
{
/*!
 * HolidayParserDriver abstract base class
 *
 * Defines a standard interface for parsing holiday files of various formats
 *
 * Derived classes must implement method parse(), other methods should work for
 * most circumstances
 *
 * \internal Private, for internal use only
 */
class HolidayParserDriver
{
public:
    /*!
     * Constructor of abstract holiday file parser driver class.
     * This will be called by derived classes.
     *
     * \a filePath full path to holiday file
     */
    explicit HolidayParserDriver(const QString &filePath);

    /*!
     * Destructor.
     */
    virtual ~HolidayParserDriver();

    /*!
     * Return the ISO 3166 country/region code of the file
     *
     * May be either just a country code ("US" = USA) or may include a regional
     * identifier ("US-CA" = California).  Returns "XX" if not a country.
     */
    virtual QString fileCountryCode() const;

    /*!
     * Return the ISO 639-1 language code of the file
     *
     * May be either just a language code ("en" = US English) or may include a country
     * identifier ("en_GB" = British English).
     */
    virtual QString fileLanguageCode() const;

    /*!
     * Return the untranslated name of the file
     */
    virtual QString fileName() const;

    /*!
     * Return the untranslated description of the file if available
     */
    virtual QString fileDescription() const;

    /*!
     * Return a list of holidays falling between any two dates with category
     *
     * \a startDate start date of the holiday parse range
     *
     * \a endDate end date of the holiday parse range
     *
     * \a category only holidays with corresponing category
     */
    virtual Holiday::List parseHolidays(const QDate &startDate, const QDate &endDate, const QString &category);

    /*!
     * Return a list of holidays falling between any two dates inclusive astro seasons
     *
     * \a startDate start date of the holiday parse range
     *
     * \a endDate end date of the holiday parse range
     */
    virtual Holiday::List parseHolidays(const QDate &startDate, const QDate &endDate);

    /*!
     * Convenience function
     * Return a list of holidays falling on a given date
     *
     * \a date date to return holidays for
     */
    virtual Holiday::List parseHolidays(const QDate &date);

    /*!
     * Return a list of holidays falling between any two dates without astro seasons
     *
     * \a startDate start date of the holiday parse range
     *
     * \a endDate end date of the holiday parse range
     */
    virtual Holiday::List parseRawHolidays(const QDate &startDate, const QDate &endDate);

    /*!
     * Convenience function
     * Return a list of holidays falling in a given calendar year
     *
     * \a calendarYear year to return holidays for
     *
     * \a calendar calendar system of year
     */
    virtual Holiday::List parseHolidays(int calendarYear, QCalendarSystem::CalendarSystem calendar = QCalendarSystem::GregorianCalendar);

    /*!
     * Standard error message handling
     *
     * \a errorMessage error message to log
     */
    virtual void error(const QString &errorMessage);

protected:
    /*!
     * Actually parse the file, must be re-implemented by derived classes
     */
    virtual void parse();

    /*!
     * Parse the file for metadata only and populate the metadata variables
     */
    virtual void parseMetadata();

    /*!
     * Set the calendar system to use
     *
     * \a calendar The QCalendarSystem calendar system to use
     */
    virtual void setParseCalendar(QCalendarSystem::CalendarSystem calendar);

    /*!
     * Initialise parse year variables for calendar system
     */
    virtual void setParseStartEnd();

    QString m_filePath; // File to be parsed

    QString m_fileCountryCode; // File country code in ISO 3166-2 standard
    QString m_fileLanguageCode; // File language
    QString m_fileName; // File name
    QString m_fileDescription; // File description

    QDate m_requestStart; // First day of period being requested
    QDate m_requestEnd; // Last day of period being requested

    Holiday::List m_resultList; // List of requested holidays

    QCalendarSystem m_parseCalendar; // Calendar system being parsed
    int m_parseYear; // Year currently being parsed
    int m_parseStartYear; // First year to parse in parse calendar
    int m_parseEndYear; // Last year to parse in parse calendar
};

}

#endif // KHOLIDAYS_HOLIDAYPARSERDRIVER_P_H
