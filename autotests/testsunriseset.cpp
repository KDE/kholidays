/*
  This file is part of the kholidays library.

  Copyright (c) 2012 Allen Winter <winter@kde.org>

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

#include "testsunriseset.h"
#include <qtest.h>

QTEST_MAIN( SunriseTest )

#include "sunriseset.h"
using namespace KHolidays;
using namespace SunRiseSet;

void SunriseTest::TestSunrise()
{
  //test bogus latitudes and longitudes
  QVERIFY( utcSunrise( QDate( 2012, 1, 1 ), 1000.0, 1000.0 ) == QTime( 0, 0 ) );
  QVERIFY( utcSunrise( QDate( 2012, 7, 1 ), -1000.0, -1000.0 ) == QTime( 0, 0 ) );
  QVERIFY( utcSunrise( QDate( 2012, 12, 31 ), 1000.0, -1000.0 ) == QTime( 0, 0 ) );

  //NYC
  QVERIFY( utcSunrise( QDate( 2012, 1, 1 ), 40.72, -74.02 ) == QTime( 12, 20 ) );
  QVERIFY( utcSunrise( QDate( 2012, 7, 1 ), 40.72, -74.02 ) == QTime( 9, 29 ) );
  QVERIFY( utcSunrise( QDate( 2012, 12, 31 ), 40.72, -74.02 ) == QTime( 12, 20 ) );

  //LA
  QVERIFY( utcSunrise( QDate( 2012, 1, 1 ), 34.05, -118.23 ) == QTime( 14, 58 ) );
  QVERIFY( utcSunrise( QDate( 2012, 7, 1 ), 34.05, -118.23 ) == QTime( 12, 45 ) );
  QVERIFY( utcSunrise( QDate( 2012, 12, 31 ), 34.05, -118.23 ) == QTime( 14, 58 ) );

  //Berlin
  QVERIFY( utcSunrise( QDate( 2012, 1, 1 ), 51.40, 7.38 ) == QTime( 7, 36 ) );
  QVERIFY( utcSunrise( QDate( 2012, 7, 1 ), 51.40, 7.38 ) == QTime( 3, 19 ) );
  QVERIFY( utcSunrise( QDate( 2012, 12, 31 ), 51.40, 7.38 ) == QTime( 7, 36 ) );

  //Tasmania
  QVERIFY( utcSunrise( QDate( 2012, 1, 1 ), -14.60, 133.77 ) == QTime( 20, 39 ) );
  QVERIFY( utcSunrise( QDate( 2012, 7, 1 ), -14.60, 133.77 ) == QTime( 21, 31 ) );
  QVERIFY( utcSunrise( QDate( 2012, 12, 31 ), -14.60, 133.77 ) == QTime( 20, 39 ) );
}

void SunriseTest::TestSunset()
{
  //NYC
  QVERIFY( utcSunset( QDate( 2012, 1, 1 ), 40.72, -74.02 ) == QTime( 21, 39 ) );
  QVERIFY( utcSunset( QDate( 2012, 7, 1 ), 40.72, -74.02 ) == QTime( 00, 31 ) );
  QVERIFY( utcSunset( QDate( 2012, 12, 31 ), 40.72, -74.02 ) == QTime( 21, 38 ) );

  //LA
  QVERIFY( utcSunset( QDate( 2012, 1, 1 ), 34.05, -118.23 ) == QTime( 00, 54 ) );
  QVERIFY( utcSunset( QDate( 2012, 7, 1 ), 34.05, -118.23 ) == QTime( 3, 8 ) );
  QVERIFY( utcSunset( QDate( 2012, 12, 31 ), 34.05, -118.23 ) == QTime( 00, 54 ) );

  //Berlin
  QVERIFY( utcSunset( QDate( 2012, 1, 1 ), 51.40, 7.38 ) == QTime( 15, 32 ) );
  QVERIFY( utcSunset( QDate( 2012, 7, 1 ), 51.40, 7.38 ) == QTime( 19, 50 ) );
  QVERIFY( utcSunset( QDate( 2012, 12, 31 ), 51.40, 7.38 ) == QTime( 15, 32 ) );

  //Tasmania
  QVERIFY( utcSunset( QDate( 2012, 1, 1 ), -14.60, 133.77 ) == QTime( 9, 37 ) );
  QVERIFY( utcSunset( QDate( 2012, 7, 1 ), -14.60, 133.77 ) == QTime( 8, 47 ) );
  QVERIFY( utcSunset( QDate( 2012, 12, 31 ), -14.60, 133.77 ) == QTime( 9, 37 ) );
}
