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

#include "testparseholiday.h"

#include <QString>
#include <QFile>

#include <KStandardDirs>
#include <qtest_kde.h>
#include <KLocale>
#include <KDebug>

#include "../parsers/plan1/holidayparserdriverplanold_p.h"
#include "../parsers/plan2/holidayparserdriverplan_p.h"
#include "holiday.h"

QTEST_KDEMAIN( ParseHolidayTest, NoGUI )

void ParseHolidayTest::parseFileOld( const QString &filePath, int year )
{
    QFileInfo testFile( filePath );

    kDebug() << "Test file = " << testFile.filePath() << " exists() = " << testFile.exists();
    kDebug() << "Loading v1, year = " << year;

    KHolidays::HolidayParserDriverPlanOld driverOld( testFile.filePath() );

    kDebug() << "Country code = " << driverOld.fileCountryCode();
    kDebug() << "Language code = " << driverOld.fileLanguageCode();
    kDebug() << "Name = " << driverOld.fileName();
    kDebug() << "Description = " << driverOld.fileDescription();

    KHolidays::Holiday::List holidaysOld = driverOld.parseHolidays( year, "gregorian" );

    if ( holidaysOld.count() > 0 ) {
        foreach ( const KHolidays::Holiday &holidayOld, holidaysOld ) {
            kDebug() << "Date = " << holidayOld.date() << " Name = " << holidayOld.text();
        }
    } else {
        kDebug() << "No holidays returned";
    }

    kDebug() << "";
}

void ParseHolidayTest::parseFileNew( const QString &filePath, int year )
{
    QFileInfo testFile( filePath );

    kDebug() << "Test file = " << testFile.filePath() << " exists() = " << testFile.exists();
    kDebug() << "Loading v2, year = " << year;

    KHolidays::HolidayParserDriverPlan driver( testFile.filePath() );

    kDebug() << "Country code = " << driver.fileCountryCode();
    kDebug() << "Language code = " << driver.fileLanguageCode();
    kDebug() << "Name = " << driver.fileName();
    kDebug() << "Description = " << driver.fileDescription();

    KHolidays::Holiday::List holidays = driver.parseHolidays( year, "gregorian" );

    if ( holidays.count() > 0 ) {
        foreach ( const KHolidays::Holiday &holiday, holidays ) {
            kDebug() << "Date = " << holiday.date() << " Name = " << holiday.text();
        }
    } else {
        kDebug() << "No holidays returned";
    }

    kDebug() << "";
}

void ParseHolidayTest::testCalendar()
{
    for ( int y = 1980; y <= 2040; ++y ) {
        parseFileNew( KDESRCDIR "/holiday_gb-eaw_en-gb_Test", y );
    }
}

void ParseHolidayTest::testGb()
{
    QString testFile( KGlobal::dirs()->findResource( "data", "libkholidays/plan1/holiday_gb-eaw_en-gb" ) );
    parseFileOld( testFile, 2010 );
    parseFileNew( testFile, 2010 );
    parseFileOld( testFile, 2012 );
    parseFileNew( testFile, 2012 );
}

void ParseHolidayTest::testCompare()
{
    QStringList allFiles = KGlobal::dirs()->findAllResources( "data", "libkholidays/plan1/holiday_*", KStandardDirs::NoDuplicates );

    foreach( QString holidayFile, allFiles ) {

        QFileInfo testFile( holidayFile );
        KHolidays::HolidayParserDriverPlanOld driverOld( testFile.filePath() );
        KHolidays::HolidayParserDriverPlan    driverNew( testFile.filePath() );

        for ( int y = 1980; y <= 2040; ++y ) {

            KHolidays::Holiday::List holidaysOld = driverOld.parseHolidays( y, "gregorian" );
            KHolidays::Holiday::List holidaysNew = driverNew.parseHolidays( y, "gregorian" );

            kDebug() << "Test file " << testFile.fileName() << " Year = " << y << " Old Loaded = " << holidaysOld.count() << " New Loaded = " << holidaysNew.count();

            if ( holidaysOld.count() != holidaysNew.count() ) {
                kDebug() << "  Number of holidays differ";
                kDebug() << "  Old parser holidays:";
                foreach ( const KHolidays::Holiday &holiday, holidaysOld ) {
                    kDebug() << "    Date = " << holiday.date() << " Name = " << holiday.text();
                }
                kDebug() << "  New parser holidays:";
                foreach ( const KHolidays::Holiday &holiday, holidaysNew ) {
                    kDebug() << "    Date = " << holiday.date() << " Name = " << holiday.text();
                }
            }
            QCOMPARE( holidaysOld.count(), holidaysNew.count() );

            for ( int i = 0; i < holidaysOld.count(); ++i ) {

                if ( holidaysOld.at(i).date() != holidaysOld.at(i).date() ||
                     holidaysOld.at(i).text() != holidaysOld.at(i).text() ) {
                        kDebug() << "  Individual holidays differ";
                        kDebug() << "  Old: Date = " << holidaysOld.at(i).date() << " Name = " << holidaysOld.at(i).text();
                        kDebug() << "  New: Date = " << holidaysNew.at(i).date() << " Name = " << holidaysNew.at(i).text();
                    }

                QCOMPARE( holidaysOld.at(i).date(), holidaysOld.at(i).date() );
                QCOMPARE( holidaysOld.at(i).text(), holidaysOld.at(i).text() );
            }
        }
    }
}
