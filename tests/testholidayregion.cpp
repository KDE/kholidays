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
    kDebug() << "Parsing  region = " << regionCode << " year = " << year << " calendar = " << calendarType;

    KHolidays::HolidayRegion region( regionCode );
    KHolidays::Holiday::List holidays = region.holidays( year, "gregorian" );

    printHolidays( holidays );

    kDebug() << "";
}

void HolidayRegionTest::parseRegionDateRange( const QString &regionCode, const QDate &startDate, const QDate &endDate )
{
    kDebug() << "Parsing  region = " << regionCode <<
                " start date = " << startDate.toString( Qt::ISODate ) <<
                " end date = " << endDate.toString( Qt::ISODate );

    KHolidays::HolidayRegion region( regionCode );
    KHolidays::Holiday::List holidays = region.holidays( startDate, endDate );

    printHolidays( holidays );

    kDebug() << "";
}

void HolidayRegionTest::parseRegionDate( const QString &regionCode, const QDate &date )
{
    kDebug() << "Parsing  region = " << regionCode << " date = " << date.toString( Qt::ISODate );

    KHolidays::HolidayRegion region( regionCode );
    KHolidays::Holiday::List holidays = region.holidays( date );

    printHolidays( holidays );

    kDebug() << "";
}

void HolidayRegionTest::testGb()
{
    parseRegionDateRange( "gb", QDate( 2010, 7, 1), QDate( 2011, 6, 30 ) );
    parseRegionDateRange( "gb", QDate( 2010, 1, 1), QDate( 2012, 12, 31 ) );
    parseRegionDateRange( "gb", QDate( 2010, 1, 1), QDate( 2010, 12, 31 ) );
    parseRegionCalendarYear( "gb", 2010, "gregorian" );
    parseRegionDate( "gb", QDate( 2010, 1, 1 ) );
}
