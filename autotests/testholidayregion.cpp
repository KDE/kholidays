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
#include <QFileInfo>
#include <qtest.h>
#include <KLocalizedString>
#include <QDebug>

QTEST_MAIN( HolidayRegionTest )

void HolidayRegionTest::printMetadata( const KHolidays::HolidayRegion &region )
{
    if ( region.isValid() ) {
      qDebug() << "This regionCode = " << region.regionCode();
      qDebug() << "Is valid? = " << region.isValid();
      qDebug() << "Country code = " << region.countryCode();
      qDebug() << "Language code = " << region.languageCode();
      qDebug() << "Name = " << region.name();
      qDebug() << "Description = " << region.description();
    } else {
      qDebug() << "Not Valid!";
    }
    qDebug() << "";
}

void HolidayRegionTest::printHolidays( KHolidays::Holiday::List holidays )
{
    if ( holidays.count() > 0 ) {
        foreach ( const KHolidays::Holiday &holiday, holidays ) {
            qDebug() << "Date = " << holiday.date().toString( Qt::ISODate ) << " Duration = " << holiday.duration() << " Name = " << holiday.text();
        }
    } else {
        qDebug() << "No holidays";
    }
}

void HolidayRegionTest::parseRegionCalendarYear( const KHolidays::HolidayRegion &region, int year,
                                                 const QString &calendarType, KHolidays::Holiday::MultidayMode multidayMode )
{
    qDebug() << "Parsing region = " << region.regionCode() << " year = " << year << " calendar = " << calendarType;
    printHolidays( region.holidays( year, calendarType, multidayMode ) );
    qDebug() << "";
}

void HolidayRegionTest::parseRegionDateRange( const KHolidays::HolidayRegion &region, const QDate &startDate,
                                              const QDate &endDate, KHolidays::Holiday::MultidayMode multidayMode )
{
    qDebug() << "Parsing regionCode = " << region.regionCode()
             << " start date = " << startDate.toString( Qt::ISODate )
             << " end date = " << endDate.toString( Qt::ISODate );
    printHolidays( region.holidays( startDate, endDate, multidayMode ) );
    qDebug() << "";
}

void HolidayRegionTest::parseRegionDate( const KHolidays::HolidayRegion &region, const QDate &date,
                                         KHolidays::Holiday::MultidayMode multidayMode )
{
    qDebug() << "Parsing regionCode = " << region.regionCode() << " date = " << date.toString( Qt::ISODate );
    printHolidays( region.holidays( date, multidayMode ) );
    qDebug() << "";
}

void HolidayRegionTest::testLoadFile()
{
    KHolidays::HolidayRegion region( QFileInfo( KDESRCDIR "/holiday_gb-eaw_en-gb_Test" ) );
    printMetadata( region );
    parseRegionCalendarYear( region, 2010, "gregorian", KHolidays::Holiday::MultidayHolidaysAsSingleEvents );
    parseRegionCalendarYear( region, 2010 );
    parseRegionCalendarYear( region, 2011 );
    parseRegionCalendarYear( region, 2012 );
    parseRegionCalendarYear( region, 2013 );
    parseRegionCalendarYear( region, 2014 );
    parseRegionCalendarYear( region, 2015 );
    qDebug() << "";
}

void HolidayRegionTest::testGb()
{
    KHolidays::HolidayRegion region( "gb-eaw_en-gb" );
    printMetadata( region );
    parseRegionDateRange( region, QDate( 2010, 7, 1 ), QDate( 2011, 6, 30 ) );
    parseRegionDateRange( region, QDate( 2010, 1, 1 ), QDate( 2012, 12, 31 ) );
    parseRegionDateRange( region, QDate( 2010, 1, 1 ), QDate( 2010, 12, 31 ) );
    parseRegionDate( region, QDate( 2010, 1, 1 ) );
    parseRegionCalendarYear( region, 2010 );
    parseRegionCalendarYear( region, 2011 );
    parseRegionCalendarYear( region, 2012 );
    parseRegionCalendarYear( region, 2013 );
    parseRegionCalendarYear( region, 2014 );
    parseRegionCalendarYear( region, 2015 );
}

void HolidayRegionTest::testIran()
{
    KHolidays::HolidayRegion region( "ir_en-us" );
    printMetadata( region );
    parseRegionCalendarYear( region, 2010 );
    parseRegionCalendarYear( region, 2011 );
    parseRegionCalendarYear( region, 2012 );
    parseRegionCalendarYear( region, 2013 );
    parseRegionCalendarYear( region, 2014 );
    parseRegionCalendarYear( region, 2015 );
}

void HolidayRegionTest::testIsrael()
{
    KHolidays::HolidayRegion region( "il_en-us" );
    printMetadata( region );
    parseRegionCalendarYear( region, 2010 );
    parseRegionCalendarYear( region, 2011 );
    parseRegionCalendarYear( region, 2012 );
    parseRegionCalendarYear( region, 2013 );
    parseRegionCalendarYear( region, 2014 );
    parseRegionCalendarYear( region, 2015 );
}

void HolidayRegionTest::testRegions()
{
  qDebug() << "Available region codes:";
  QStringList regionCodes = KHolidays::HolidayRegion::regionCodes();
  foreach ( const QString &regionCode, regionCodes ) {
    KHolidays::HolidayRegion testRegion( regionCode );
    qDebug() << regionCode << " = " << testRegion.name();
  }
  qDebug() << "";

  qDebug() << "This years holidays:";
  foreach ( const QString &regionCode, regionCodes ) {
    KHolidays::HolidayRegion testRegion( regionCode );
    printMetadata( testRegion );
    parseRegionCalendarYear( testRegion, QDate::currentDate().year() );
    qDebug() << "";
  }
  qDebug() << "";
}

void HolidayRegionTest::testLocations()
{
  qDebug() << "Available locations:";
  QStringList locations = KHolidays::HolidayRegion::locations();
  foreach ( const QString &location, locations ) {
    KHolidays::HolidayRegion testRegion( location );
    qDebug() << location << " = " << testRegion.regionCode() << testRegion.name();
  }
  qDebug() << "";
}

void HolidayRegionTest::testDefaultRegions()
{
  QCOMPARE( KHolidays::HolidayRegion::defaultRegionCode( "be", "nl" ), QString( "be_nl" ) );
  QCOMPARE( KHolidays::HolidayRegion::defaultRegionCode( "be", "fr" ), QString( "be_fr" ) );
  QCOMPARE( KHolidays::HolidayRegion::defaultRegionCode( "be", "xx" ), QString( "be_fr" ) );
  QCOMPARE( KHolidays::HolidayRegion::defaultRegionCode( "xx", "fr_BE" ), QString( "be_fr" ) );
  QCOMPARE( KHolidays::HolidayRegion::defaultRegionCode( "xx", "xx" ), QString() );
  QCOMPARE( KHolidays::HolidayRegion::defaultRegionCode( "au", "en_GB" ), QString( "au-act_en-gb" ) );
  QCOMPARE( KHolidays::HolidayRegion::defaultRegionCode( "au-VIC", "en_GB" ), QString( "au-vic_en-gb" ) );
}
