/*
  This file is part of the kholidays library.

  Copyright (c) 2001 Cornelius Schumacher <schumacher@kde.org>
  Copyright (c) 2004 Allen Winter <winter@kde.org>
  Copyright (c) 2008 David Jarvie <djarvie@kde.org>

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Library General Public
  License as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Library General Public License for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; see the file COPYING.LIB.  If not, write to the
  Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
  Boston, MA 02110-1301, USA.
*/

#include "kholidays.h"

#include <KStandardDirs>

#include <QDateTime>
#include <QFile>

using namespace KHolidays;

extern "C" {
  char *parse_holidays( const char *, int year, short force );
  /** \internal */
  struct holiday {
    char            *string;   /* name of holiday, 0=not a holiday */
    int             color;     /* color code, see scanholiday.lex */
    unsigned short  dup;       /* reference count */
    holiday         *next;     /* single-linked list if more than one holiday
                                  appears on a given date */
  };
  extern struct holiday holidays[366];
}

QStringList KHolidays::locations()
{
  const QStringList files =
    KGlobal::dirs()->findAllResources( "data", "libkholidays/holiday_*",
                                       KStandardDirs::NoDuplicates );
  QStringList locs;

  QStringList::ConstIterator it;
  for ( it = files.constBegin(); it != files.constEnd(); ++it ) {
    locs.append( (*it).mid( (*it).lastIndexOf( '_' ) + 1 ) );
  }

  return locs;
}

KHolidays::KHolidays( const QString &location )
  : mLocation( location ),
    mYearLast( 0 )
{
  if ( !location.isEmpty() ) {
    mHolidayFile = KStandardDirs::locate( "data", "libkholidays/holiday_" + location );
    if ( mHolidayFile.isEmpty() ) {
      mLocation.clear();
    }
  }
}

KHolidays::~KHolidays()
{
}

QString KHolidays::location() const
{
  return mLocation;
}

bool KHolidays::isValid() const
{
  return !mHolidayFile.isEmpty();
}

bool KHolidays::parseFile( const QDate &date ) const
{
  int lastYear = 0; //current year less 1900

  if ( mHolidayFile.isEmpty() || !date.isValid() ) {
    return false;
  }

  if ( ( date.year() != mYearLast ) || ( mYearLast == 0 ) ) {
    mYearLast = date.year();
    lastYear = date.year() - 1900; // silly parse_year takes 2 digit year...
    parse_holidays( QFile::encodeName( mHolidayFile ), lastYear, 1 );
  }

  return true;
}

QList<KHoliday> KHolidays::getHolidays( const QDate &date ) const
{
  QList<KHoliday> list;
  if ( !parseFile( date ) ) {
    return list;
  }
  struct holiday *hd = &holidays[date.dayOfYear()-1];
  while ( hd ) {
    if ( hd->string ) {
      KHoliday holiday;
      holiday.text = QString::fromUtf8( hd->string );
      holiday.shortText = holiday.text;
      holiday.Category = ( hd->color == 2/*red*/ ) || ( hd->color == 9/*weekend*/ ) ?
                         HOLIDAY : WORKDAY;
      list.append( holiday );
    }
    hd = hd->next;
  }
  return list;
}

bool KHolidays::isHoliday( const QDate &date ) const
{
  if ( !parseFile( date ) ) {
    return false;
  }
  struct holiday *hd = &holidays[date.dayOfYear()-1];
  while ( hd ) {
    if ( hd->string && ( hd->color == 2/*red*/ || hd->color == 9/*weekend*/ ) ) {
      return true;
    }
    hd = hd->next;
  }
  return false;
}
