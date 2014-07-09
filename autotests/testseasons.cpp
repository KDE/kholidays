/*
  This file is part of the kholidays library.

  Copyright (c) 2004,2006-2007 Allen Winter <winter@kde.org>

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

#include "testseasons.h"
#include <qtest.h>
#include <klocalizedstring.h>

QTEST_MAIN( SeasonsTest )

#include "astroseasons.h"
using namespace KHolidays;

void SeasonsTest::test2005()
{
  AstroSeasons as;
  QVERIFY( as.seasonAtDate( QDate( 2005, 3, 22 ) ) == AstroSeasons::MarchEquinox );
  QVERIFY( as.seasonAtDate( QDate( 2005, 6, 22 ) ) == AstroSeasons::JuneSolstice );
  QVERIFY( as.seasonAtDate( QDate( 2005, 9, 22 ) ) == AstroSeasons::SeptemberEquinox );
  QVERIFY( as.seasonAtDate( QDate( 2005, 12, 22 ) ) == AstroSeasons::DecemberSolstice );
  QVERIFY( as.seasonAtDate( QDate( 2005, 1, 22 ) ) == AstroSeasons::None );
  QVERIFY( as.seasonAtDate( QDate( 2005, 12, 31 ) ) == AstroSeasons::None );
}

void SeasonsTest::test2007()
{
  AstroSeasons as;
  QVERIFY( as.seasonAtDate( QDate( 2007, 3, 22 ) ) == AstroSeasons::MarchEquinox );
  QVERIFY( as.seasonAtDate( QDate( 2007, 6, 22 ) ) == AstroSeasons::JuneSolstice );
  QVERIFY( as.seasonAtDate( QDate( 2007, 9, 22 ) ) == AstroSeasons::SeptemberEquinox );
  QVERIFY( as.seasonAtDate( QDate( 2007, 12, 22 ) ) == AstroSeasons::DecemberSolstice );
  QVERIFY( as.seasonAtDate( QDate( 2007, 1, 2 ) ) == AstroSeasons::None );
  QVERIFY( as.seasonAtDate( QDate( 2007, 11, 30 ) ) == AstroSeasons::None );
}
