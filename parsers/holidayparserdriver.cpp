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

#include "holidayparserdriver_p.h"

#include <KCalendarSystem>
#include <KDebug>

using namespace KHolidays;

HolidayParserDriver::HolidayParserDriver( const QString &filePath )
{
    m_filePath = filePath;
    m_parseCalendar = 0;
}

HolidayParserDriver::~HolidayParserDriver()
{
    delete m_parseCalendar;
}

Holiday::List HolidayParserDriver::parseHolidays( const QDate &startDate, const QDate &endDate )
{
    m_resultList.clear();
    if ( startDate.isNull() || endDate.isNull() ) {
        return m_resultList;
    }
    m_requestStart = startDate;
    m_requestEnd = endDate;
    parse();
    qSort( m_resultList );
    return m_resultList;
}

Holiday::List HolidayParserDriver::parseHolidays( const QDate &requestDate )
{
    return parseHolidays( requestDate, requestDate );
}

Holiday::List HolidayParserDriver::parseHolidays( int calendarYear, const QString &calendarType )
{
    m_resultList.clear();
    setParseCalendar( calendarType );
    if ( !m_parseCalendar->isValid( calendarYear, 1, 1 ) ) {
      return m_resultList;
    }

    QDate startDate, endDate;
    m_parseCalendar->setDate( startDate, calendarYear, 1, 1 );
    endDate = startDate.addDays( m_parseCalendar->daysInYear( startDate ) - 1 );

    return parseHolidays( startDate, endDate );
}

void HolidayParserDriver::error( const QString &errorMessage )
{
    kDebug() << errorMessage;
}

void HolidayParserDriver::parse()
{
}

void HolidayParserDriver::setParseCalendar( const QString &calendarType )
{
    delete m_parseCalendar;
    m_parseCalendar = KCalendarSystem::create( calendarType );
}

void HolidayParserDriver::setParseStartEnd()
{
    // Set start year and end year to generate holidays for
    // TODO Maybe make +/- 1 more year to allow spanned holidays from previous/following years
    // Make sure requested date range falls within valid date range for current calendar system
    if ( m_requestStart > m_parseCalendar->latestValidDate() ||
          m_requestEnd < m_parseCalendar->earliestValidDate() ) {  // Completely out of range, don't parse
        m_parseStartYear = 0;
        m_parseEndYear = m_parseStartYear - 1;
    } else {
        if ( m_requestStart < m_parseCalendar->earliestValidDate() ) {
            m_parseStartYear = m_parseCalendar->year( m_parseCalendar->earliestValidDate() );
        } else {
            m_parseStartYear = m_parseCalendar->year( m_requestStart );
        }

        if ( m_requestEnd > m_parseCalendar->latestValidDate() ) {
            m_parseEndYear = m_parseCalendar->year( m_parseCalendar->latestValidDate() );
        } else {
            m_parseEndYear = m_parseCalendar->year( m_requestEnd );
        }
    }
}
