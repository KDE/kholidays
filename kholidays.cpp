/*
    This file is part of KOrganizer.
    Copyright (c) 2001 Cornelius Schumacher <schumacher@kde.org>
    Copyright (c) 2004 Allen Winter <winter@kde.org>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#include <qfile.h>
#include <kapplication.h>
#include <kstandarddirs.h>

#include "kholidays.h"


extern "C" {
  char *parse_holidays( const char *, int year, short force );
  /** \internal */
  struct holiday {
    char            *string;        /* name of holiday, 0=not a holiday */
    unsigned short  dup;            /* reference count */
  };
  extern struct holiday holiday[366];
}


KHolidays::KHolidays( const QString& locale )
{
  mHolidayFile = locate( "data", "libkholidays/holiday_" + locale );

  mYearLast = 0;
}

KHolidays::~KHolidays()
{
}

QString KHolidays::shortText( const QDate &date )
{
  return getHoliday( date );
}

QString KHolidays::getHoliday( const QDate &date )
{
  int lastYear = 0; //current year less 1900

  if ( mHolidayFile.isEmpty() || date.isNull() ) return QString::null;

  if ( ( mYearLast == 0 ) || ( date.year() != mYearLast ) ) {
    mYearLast = date.year();
    lastYear = date.year() - 1900; // silly parse_year takes 2 digit year...
    parse_holidays( QFile::encodeName( mHolidayFile ), lastYear, 1 );
  }

  if ( holiday[date.dayOfYear()-1].string ) {
    return QString::fromUtf8( holiday[date.dayOfYear()-1].string );
  } else {
    return QString::null;
  }
}
