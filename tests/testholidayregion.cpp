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

void HolidayRegionTest::printMetadata( const QString &location )
{
    KHolidays::HolidayRegion region( location );

    kDebug() << "This location = " << region.location();
    kDebug() << "Is valid? = " << region.isValid();
    kDebug() << "Region code = " << region.regionCode();
    kDebug() << "Language code = " << region.languageCode();
    kDebug() << "Short name = " << region.shortName();
    kDebug() << "Long name = " << region.longName();
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

void HolidayRegionTest::parseRegionCalendarYear( const QString &location, int year, const QString &calendarType )
{
    kDebug() << "Parsing location = " << location << " year = " << year << " calendar = " << calendarType;

    KHolidays::HolidayRegion region( location );
    KHolidays::Holiday::List holidays = region.holidays( year, "gregorian" );

    printHolidays( holidays );

    kDebug() << "";
}

void HolidayRegionTest::parseRegionDateRange( const QString &location, const QDate &startDate, const QDate &endDate )
{
    kDebug() << "Parsing location = " << location <<
                " start date = " << startDate.toString( Qt::ISODate ) <<
                " end date = " << endDate.toString( Qt::ISODate );

    KHolidays::HolidayRegion region( location );
    KHolidays::Holiday::List holidays = region.holidays( startDate, endDate );

    printHolidays( holidays );

    kDebug() << "";
}

void HolidayRegionTest::parseRegionDate( const QString &location, const QDate &date )
{
    kDebug() << "Parsing location = " << location << " date = " << date.toString( Qt::ISODate );

    KHolidays::HolidayRegion region( location );
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

void HolidayRegionTest::testLocations()
{
    kDebug() << "Available locations:";
    QStringList locations = KHolidays::HolidayRegion::locations();
    foreach ( const QString &location, locations ) {
        kDebug() << location;
    }
    kDebug() << "";
}

