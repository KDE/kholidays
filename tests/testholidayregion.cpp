/*
    This file is part of the kholidays library.

    Copyright 2010 John Layt <john@layt.net>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "testholidayregion.h"

#include <QString>
#include <QFile>

#include <qtest_kde.h>
#include <KLocale>
#include <KDebug>

QTEST_KDEMAIN( HolidayRegionTest, NoGUI )

void HolidayRegionTest::printMetadata( const QString &regionCode )
{
    KHolidays::HolidayRegion region( regionCode );

    if ( region.isValid() ) {
      kDebug() << "This regionCode = " << region.regionCode();
      kDebug() << "Is valid? = " << region.isValid();
      kDebug() << "Country code = " << region.countryCode();
      kDebug() << "Language code = " << region.languageCode();
      kDebug() << "Name = " << region.name();
      kDebug() << "Description = " << region.description();
    } else {
      kDebug() << "Not Valid!";
    }
    kDebug() << "";
}

void HolidayRegionTest::printHolidays( KHolidays::Holiday::List holidays )
{
    if ( holidays.count() > 0 ) {
        foreach ( const KHolidays::Holiday &holiday, holidays ) {
            kDebug() << "Date = " << holiday.date().toString( Qt::ISODate ) << " Name = " << holiday.text();
        }
    } else {
        kDebug() << "No holidays";
    }
}

void HolidayRegionTest::parseRegionCalendarYear( const QString &regionCode, int year, const QString &calendarType )
{
    kDebug() << "Parsing region = " << regionCode << " year = " << year << " calendar = " << calendarType;

    KHolidays::HolidayRegion region( regionCode );
    KHolidays::Holiday::List holidays = region.holidays( year, calendarType );

    printHolidays( holidays );

    kDebug() << "";
}

void HolidayRegionTest::parseRegionDateRange( const QString &regionCode, const QDate &startDate, const QDate &endDate )
{
    kDebug() << "Parsing regionCode = " << regionCode <<
                " start date = " << startDate.toString( Qt::ISODate ) <<
                " end date = " << endDate.toString( Qt::ISODate );

    KHolidays::HolidayRegion region( regionCode );
    KHolidays::Holiday::List holidays = region.holidays( startDate, endDate );

    printHolidays( holidays );

    kDebug() << "";
}

void HolidayRegionTest::parseRegionDate( const QString &regionCode, const QDate &date )
{
    kDebug() << "Parsing regionCode = " << regionCode << " date = " << date.toString( Qt::ISODate );

    KHolidays::HolidayRegion region( regionCode );
    KHolidays::Holiday::List holidays = region.holidays( date );

    printHolidays( holidays );

    kDebug() << "";
}

void HolidayRegionTest::testGb()
{
    printMetadata( "gb-eaw_en-gb" );
    parseRegionDateRange( "gb-eaw_en-gb", QDate( 2010, 7, 1), QDate( 2011, 6, 30 ) );
    parseRegionDateRange( "gb-eaw_en-gb", QDate( 2010, 1, 1), QDate( 2012, 12, 31 ) );
    parseRegionDateRange( "gb-eaw_en-gb", QDate( 2010, 1, 1), QDate( 2010, 12, 31 ) );
    parseRegionCalendarYear( "gb-eaw_en-gb", 2010, "gregorian" );
    parseRegionDate( "gb-eaw_en-gb", QDate( 2010, 1, 1 ) );
}

void HolidayRegionTest::testIran()
{
  printMetadata( "ir_en-us" );
  parseRegionCalendarYear( "ir_en-us", 2010 );
  parseRegionCalendarYear( "ir_en-us", 2011 );
  parseRegionCalendarYear( "ir_en-us", 2012 );
  parseRegionCalendarYear( "ir_en-us", 2013 );
  parseRegionCalendarYear( "ir_en-us", 2014 );
  parseRegionCalendarYear( "ir_en-us", 2015 );
}

void HolidayRegionTest::testIsrael()
{
  printMetadata( "il_en-us" );
  parseRegionCalendarYear( "il_en-us", 2010 );
  parseRegionCalendarYear( "il_en-us", 2011 );
  parseRegionCalendarYear( "il_en-us", 2012 );
  parseRegionCalendarYear( "il_en-us", 2013 );
  parseRegionCalendarYear( "il_en-us", 2014 );
  parseRegionCalendarYear( "il_en-us", 2015 );

}

void HolidayRegionTest::testRegions()
{
  kDebug() << "Available regions:";
  QStringList regions = KHolidays::HolidayRegion::regions();
  foreach ( const QString &regionCode, regions ) {
    KHolidays::HolidayRegion testRegion( regionCode );
    kDebug() << regionCode << " = " << testRegion.name();
  }
  kDebug() << "";

  kDebug() << "This years holidays:";
  foreach ( const QString &regionCode, regions ) {
    printMetadata( regionCode );
    parseRegionCalendarYear( regionCode, QDate::currentDate().year() );
    kDebug() << "";
  }
  kDebug() << "";
}

void HolidayRegionTest::testLocations()
{
  kDebug() << "Available locations:";
  QStringList locations = KHolidays::HolidayRegion::locations();
  foreach ( const QString &location, locations ) {
    KHolidays::HolidayRegion testRegion( location );
    kDebug() << location << " = " << testRegion.regionCode() << testRegion.name();
  }
  kDebug() << "";
}

