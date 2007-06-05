/*
  This file is part of libkholidays.
  Copyright (c) 2004,2006 Allen Winter <winter@kde.org>

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

#include <qtest_kde.h>
#include <klocale.h>

#include "testlunar.h"
#include "testlunar.moc"

QTEST_KDEMAIN( LunarTest, NoGUI )

#include "libkholidays/lunarphase.h"
using namespace LibKHolidays;

void LunarTest::testValidity()
{
  LunarPhase lp;
  QVERIFY( lp.hemisphereStr() == i18n( "Northern" ) );
}

void LunarTest::test2005()
{

  QList<QDate> fQ2005, fM2005, lQ2005, nM2005;
  //2005 first quarter moons
  fQ2005.append( QDate( 2005,  1, 17 ) );
  fQ2005.append( QDate( 2005,  2, 15 ) );
  fQ2005.append( QDate( 2005,  3, 17 ) );
  fQ2005.append( QDate( 2005,  4, 16 ) );
  fQ2005.append( QDate( 2005,  5, 16 ) );
  fQ2005.append( QDate( 2005,  6, 14 ) );
  fQ2005.append( QDate( 2005,  7, 14 ) );
  fQ2005.append( QDate( 2005,  8, 12 ) );
  fQ2005.append( QDate( 2005,  9, 11 ) );
  fQ2005.append( QDate( 2005, 10, 10 ) );
  fQ2005.append( QDate( 2005, 11,  8 ) );
  fQ2005.append( QDate( 2005, 12,  8 ) );

  //2005 full moons
  fM2005.append( QDate( 2005,  1, 24 ) );
  fM2005.append( QDate( 2005,  2, 23 ) );
  fM2005.append( QDate( 2005,  3, 25 ) );
  fM2005.append( QDate( 2005,  4, 24 ) );
  fM2005.append( QDate( 2005,  5, 23 ) );
  fM2005.append( QDate( 2005,  6, 21 ) );
  fM2005.append( QDate( 2005,  7, 21 ) );
  fM2005.append( QDate( 2005,  8, 19 ) );
  fM2005.append( QDate( 2005,  9, 17 ) );
  fM2005.append( QDate( 2005, 10, 17 ) );
  fM2005.append( QDate( 2005, 11, 15 ) );
  fM2005.append( QDate( 2005, 12, 15 ) );

  //2005 last quarter moons
  lQ2005.append( QDate( 2005,  1,  3 ) );
  lQ2005.append( QDate( 2005,  2,  2 ) );
  lQ2005.append( QDate( 2005,  3,  3 ) );
  lQ2005.append( QDate( 2005,  4,  1 ) );
  lQ2005.append( QDate( 2005,  5,  1 ) );
  lQ2005.append( QDate( 2005,  5, 30 ) );
  lQ2005.append( QDate( 2005,  6, 28 ) );
  lQ2005.append( QDate( 2005,  7, 27 ) );
  lQ2005.append( QDate( 2005,  8, 26 ) );
  lQ2005.append( QDate( 2005,  9, 25 ) );
  lQ2005.append( QDate( 2005, 10, 24 ) );
  lQ2005.append( QDate( 2005, 11, 23 ) );
  lQ2005.append( QDate( 2005, 12, 23 ) );

  //2005 new moons
  nM2005.append( QDate( 2005,  1, 10 ) );
  nM2005.append( QDate( 2005,  2,  8 ) );
  nM2005.append( QDate( 2005,  3, 10 ) );
  nM2005.append( QDate( 2005,  4,  8 ) );
  nM2005.append( QDate( 2005,  5,  8 ) );
  nM2005.append( QDate( 2005,  6,  6 ) );
  nM2005.append( QDate( 2005,  7,  6 ) );
  nM2005.append( QDate( 2005,  8,  4 ) );
  nM2005.append( QDate( 2005,  9,  3 ) );
  nM2005.append( QDate( 2005, 10,  3 ) );
  nM2005.append( QDate( 2005, 11,  1 ) );
  nM2005.append( QDate( 2005, 12,  1 ) );
  nM2005.append( QDate( 2005, 12, 30 ) );

  LunarPhase lp;
  QDate qd( 2004, 12, 31 );
  QList<QDate> firstQuarter, fullMoon, lastQuarter, newMoon;
  for ( int i=1; i<=365; ++i ) {
    qd = qd.addDays( 1 );
    LunarPhase::Phase phase = lp.phase( qd );
    if ( phase == LunarPhase::FirstQuarter ) {
      firstQuarter.append( qd );
      kDebug() << "first quarter " << qd << endl;
    }
    else if ( phase == LunarPhase::FullMoon ) {
      fullMoon.append( qd );
      kDebug() << "full moon " << qd << endl;
    }
    else if ( phase == LunarPhase::LastQuarter ) {
      lastQuarter.append( qd );
      kDebug() << "last quarter " << qd << endl;
    }
    else if ( phase == LunarPhase::NewMoon ) {
      newMoon.append( qd );
      kDebug() << "new moon " << qd << endl;
    }
  }
  QVERIFY( fQ2005 == firstQuarter );
  QVERIFY( fM2005 == fullMoon );
  QVERIFY( lQ2005 == lastQuarter );
  QVERIFY( nM2005 == newMoon );
}

void LunarTest::test2007()
{
  QList<QDate> fQ2007, fM2007, lQ2007, nM2007;
  //2007 first quarter moons
  fQ2007.append( QDate( 2007,  1, 25 ) );
  fQ2007.append( QDate( 2007,  2, 24 ) );
  fQ2007.append( QDate( 2007,  3, 25 ) );
  fQ2007.append( QDate( 2007,  4, 24 ) );
  fQ2007.append( QDate( 2007,  5, 23 ) );
  fQ2007.append( QDate( 2007,  6, 22 ) );
  fQ2007.append( QDate( 2007,  7, 22 ) );
  fQ2007.append( QDate( 2007,  8, 20 ) );
  fQ2007.append( QDate( 2007,  9, 19 ) );
  fQ2007.append( QDate( 2007, 10, 19 ) );
  fQ2007.append( QDate( 2007, 11, 17 ) );
  fQ2007.append( QDate( 2007, 12, 17 ) );

  //2007 full moons
  fM2007.append( QDate( 2007,  1,  3 ) );
  fM2007.append( QDate( 2007,  2,  1 ) );
  fM2007.append( QDate( 2007,  3,  3 ) );
  fM2007.append( QDate( 2007,  4,  2 ) );
  fM2007.append( QDate( 2007,  5,  2 ) );
  fM2007.append( QDate( 2007,  5, 31 ) );
  fM2007.append( QDate( 2007,  6, 30 ) );
  fM2007.append( QDate( 2007,  7, 29 ) );
  fM2007.append( QDate( 2007,  8, 28 ) );
  fM2007.append( QDate( 2007,  9, 26 ) );
  fM2007.append( QDate( 2007, 10, 25 ) );
  fM2007.append( QDate( 2007, 11, 24 ) );
  fM2007.append( QDate( 2007, 12, 23 ) );

  //2007 last quarter moons
  lQ2007.append( QDate( 2007,  1, 11 ) );
  lQ2007.append( QDate( 2007,  2, 10 ) );
  lQ2007.append( QDate( 2007,  3, 11 ) );
  lQ2007.append( QDate( 2007,  4, 10 ) );
  lQ2007.append( QDate( 2007,  5, 10 ) );
  lQ2007.append( QDate( 2007,  6,  8 ) );
  lQ2007.append( QDate( 2007,  7,  7 ) );
  lQ2007.append( QDate( 2007,  8,  5 ) );
  lQ2007.append( QDate( 2007,  9,  3 ) );
  lQ2007.append( QDate( 2007, 10,  3 ) );
  lQ2007.append( QDate( 2007, 11,  1 ) );
  lQ2007.append( QDate( 2007, 12,  1 ) );
  lQ2007.append( QDate( 2007, 12, 31 ) );

  //2007 new moons
  nM2007.append( QDate( 2007,  1, 18 ) );
  nM2007.append( QDate( 2007,  2, 17 ) );
  nM2007.append( QDate( 2007,  3, 18 ) );
  nM2007.append( QDate( 2007,  4, 17 ) );
  nM2007.append( QDate( 2007,  5, 16 ) );
  nM2007.append( QDate( 2007,  6, 14 ) );
  nM2007.append( QDate( 2007,  7, 14 ) );
  nM2007.append( QDate( 2007,  8, 12 ) );
  nM2007.append( QDate( 2007,  9, 11 ) );
  nM2007.append( QDate( 2007, 10, 10 ) );
  nM2007.append( QDate( 2007, 11,  9 ) );
  nM2007.append( QDate( 2007, 12,  9 ) );

  LunarPhase lp;
  QDate qd( 2006, 12, 31 );
  QList<QDate> firstQuarter, fullMoon, lastQuarter, newMoon;
  for ( int i=1; i<=365; ++i ) {
    qd = qd.addDays( 1 );
    LunarPhase::Phase phase = lp.phase( qd );
    if ( phase == LunarPhase::FirstQuarter ) {
      firstQuarter.append( qd );
      kDebug() << "first quarter " << qd << endl;
    }
    else if ( phase == LunarPhase::FullMoon ) {
      fullMoon.append( qd );
      kDebug() << "full moon " << qd << endl;
    }
    else if ( phase == LunarPhase::LastQuarter ) {
      lastQuarter.append( qd );
      kDebug() << "last quarter " << qd << endl;
    }
    else if ( phase == LunarPhase::NewMoon ) {
      newMoon.append( qd );
      kDebug() << "new moon " << qd << endl;
    }
  }
  QVERIFY( fQ2007 == firstQuarter );
  QVERIFY( fM2007 == fullMoon );
  QVERIFY( lQ2007 == lastQuarter );
  QVERIFY( nM2007 == newMoon );
}
