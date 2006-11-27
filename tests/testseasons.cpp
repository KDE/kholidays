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

#include <stdlib.h>
#include <iostream>
#include <kaboutdata.h>
#include <kdebug.h>
#include <klocale.h>
#include <kcmdlineargs.h>
#include <QCoreApplication>

#include "astroseasons.h"

using namespace LibKHolidays;
using namespace std;

static const KCmdLineOptions options[] =
{
  {"verbose", "Verbose output", 0},
  KCmdLineLastOption
};

int main(int argc,char **argv)
{
  KAboutData aboutData("testseasons","Test Astronomical Seasons","0.1");
  QCoreApplication app( argc, argv );

  AstroSeasons as;
  QString pStr;

  QDate qd( 2004, 11, 1 );
  for ( int i=0; i<=2500; ++i ) {
    qd = qd.addDays( 1 );
    pStr = as.seasonStr( qd );
    if ( !pStr.isNull() ) {
      cout << qd.toString( Qt::TextDate ).toLocal8Bit().constData() << ": "
           << pStr.toLocal8Bit().constData()
           << endl;
    }
  }
}
