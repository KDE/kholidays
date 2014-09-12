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
#include <QDebug>

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

QString HolidayParserDriver::fileCountryCode() const
{
  return m_fileCountryCode;
}

QString HolidayParserDriver::fileLanguageCode() const
{
  return m_fileLanguageCode;
}

QString HolidayParserDriver::fileName() const
{
  return m_fileName;
}

QString HolidayParserDriver::fileDescription() const
{
  return m_fileDescription;
}

Holiday::List HolidayParserDriver::parseHolidays( const QDate &startDate, const QDate &endDate,
                                                  Holiday::MultidayMode multidayMode )
{
  m_multidayMode = multidayMode;
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

Holiday::List HolidayParserDriver::parseHolidays( const QDate &requestDate,
                                                  Holiday::MultidayMode multidayMode )
{
  return parseHolidays( requestDate, requestDate, multidayMode );
}

Holiday::List HolidayParserDriver::parseHolidays( int calendarYear, const QString &calendarType,
                                                  Holiday::MultidayMode multidayMode )
{
  m_resultList.clear();
  setParseCalendar( calendarType );
  if ( !m_parseCalendar->isValid( calendarYear, 1, 1 ) ) {
    return m_resultList;
  }

  QDate startDate, endDate;
  m_parseCalendar->setDate( startDate, calendarYear, 1, 1 );
  endDate = startDate.addDays( m_parseCalendar->daysInYear( startDate ) - 1 );

  return parseHolidays( startDate, endDate, multidayMode );
}

void HolidayParserDriver::error( const QString &errorMessage )
{
  qDebug() << errorMessage;
}

void HolidayParserDriver::parse()
{
}

void HolidayParserDriver::parseMetadata()
{
}

void HolidayParserDriver::setParseCalendar( const QString &calendarType )
{
  delete m_parseCalendar;

  // this was removed from KCalendarSystem in KF5 for some reason, so copy it here until we have a QCalendarSystem
  KLocale::CalendarSystem cal = KLocale::QDateCalendar;
  if (calendarType == QLatin1String("coptic")) {
    cal = KLocale::CopticCalendar;
  } else if (calendarType == QLatin1String("ethiopian")) {
    cal = KLocale::EthiopianCalendar;
  } else if (calendarType == QLatin1String("gregorian")) {
    cal = KLocale::QDateCalendar;
  } else if (calendarType == QLatin1String("gregorian-proleptic")) {
    cal = KLocale::GregorianCalendar;
  } else if (calendarType == QLatin1String("hebrew")) {
    cal = KLocale::HebrewCalendar;
  } else if (calendarType == QLatin1String("hijri")) {
    cal = KLocale::IslamicCivilCalendar;
  } else if (calendarType == QLatin1String("indian-national")) {
    cal = KLocale::IndianNationalCalendar;
  } else if (calendarType == QLatin1String("jalali")) {
    cal = KLocale::JalaliCalendar;
  } else if (calendarType == QLatin1String("japanese")) {
    cal = KLocale::JapaneseCalendar;
  } else if (calendarType == QLatin1String("julian")) {
    cal = KLocale::JulianCalendar;
  } else if (calendarType == QLatin1String("minguo")) {
    cal = KLocale::MinguoCalendar;
  } else if (calendarType == QLatin1String("thai")) {
    cal = KLocale::ThaiCalendar;
  }

  m_parseCalendar = KCalendarSystem::create( cal );
}

void HolidayParserDriver::setParseStartEnd()
{
  // Set start year and end year to generate holidays for
  // TODO Maybe make +/- 1 more year to allow spanned holidays from previous/following years
  // Make sure requested date range falls within valid date range for current calendar system
  if ( m_requestStart > m_parseCalendar->latestValidDate() ||
       m_requestEnd < m_parseCalendar->earliestValidDate() ) {
    // Completely out of range, don't parse
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
