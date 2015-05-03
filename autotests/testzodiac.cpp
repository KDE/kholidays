/*
  This file is part of kholidays library.

  Copyright (c) 2005,2006 Allen Winter <winter@kde.org>

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

#include "zodiac.h"

#include <qdebug.h>
#include <klocalizedstring.h>
#include <kcmdlineargs.h>

#include <QDateTime>
#include <QCoreApplication>

#include <stdlib.h>
#include <iostream>

using namespace KHolidays;
using namespace std;

int main( int argc, char **argv )
{

  QCoreApplication app( argc, argv );

  Zodiac::ZodiacSigns sign;
  QString pStr;

  int year = 2004;
  int days = ( QDate::isLeapYear( year ) ? 366 : 355 );

  Zodiac zd( Zodiac::Tropical );
  QDate qd( year, 1, 1 );
  for ( int i=1; i<=days; ++i ) {
      sign = zd.signAtDate( qd );
      pStr = zd.signName( sign );
      if ( !pStr.isNull() ) {
          cout << qd.toString( Qt::TextDate ).toLocal8Bit().constData() << ": "
               << pStr.toLocal8Bit().constData()
               << " [" << qPrintable( zd.signSymbol( sign ) ) << "]"
               << endl;
      }
      qd = qd.addDays( 1 );
  }

  Zodiac zd2( Zodiac::Sidereal );
  QDate qd2( year, 1, 1 );
  for ( int i=1; i<=days; ++i ) {
      sign = zd2.signAtDate( qd2 );
      pStr = zd2.signName( sign );
      if ( !pStr.isNull() ) {
          cout << qd2.toString( Qt::TextDate ).toLocal8Bit().constData() << ": "
               << pStr.toLocal8Bit().constData()
               << " [" << qPrintable( zd2.signSymbol( sign ) ) << "]"
               << endl;
      }
      qd2 = qd2.addDays( 1 );
  }
}
