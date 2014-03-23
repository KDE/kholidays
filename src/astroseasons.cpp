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

#include "astroseasons.h"

#include <KLocalizedString>

#include <QtCore/QDate>

using namespace KHolidays;

QString AstroSeasons::seasonNameAtDate( const QDate &date )
{
  return seasonName( seasonAtDate( date ) );
}

QString AstroSeasons::seasonName( AstroSeasons::Season season )
{
  switch ( season ) {
  case JuneSolstice:
    return i18n( "June Solstice" );
  case DecemberSolstice:
    return i18n( "December Solstice" );
  case MarchEquinox:
    return i18n( "March Equinox" );
  case SeptemberEquinox:
    return i18n( "September Equinox" );
  default:
  case None:
    return QString();
  }
}

AstroSeasons::Season AstroSeasons::seasonAtDate( const QDate &date )
{
  // see http://www.hermetic.ch/cal_sw/ve/ve.php
  Season retSeason = None;

  const int year = date.year();
  //Use dumb method for now
  if ( date == QDate( year, 6, 22 ) ) {
    return JuneSolstice;
  }
  if ( date == QDate( year, 12, 22 ) ) {
    return DecemberSolstice;
  }
  if ( date == QDate( year, 3, 22 ) ) {
    return MarchEquinox;
  }
  if ( date == QDate( year, 9, 22 ) ) {
    return SeptemberEquinox;
  }

  return retSeason;
}
