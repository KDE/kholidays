/*
  This file is part of libkholidays.
  Copyright (c) 2001 Cornelius Schumacher <schumacher@kde.org>
  Copyright (c) 2004 Allen Winter <winter@kde.org>

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
#include "kholidays_version.h"

#include <QFile>
#include <kapplication.h>
#include <kstandarddirs.h>
#include <kdebug.h>

extern "C" {
  char *parse_holidays( const char *, int year, short force );
  /** \internal */
  struct holiday {
    char            *string;        /* name of holiday, 0=not a holiday */
    int             color;          /* color code, see scanholiday.lex */
    unsigned short  dup;            /* reference count */
    holiday         *next;          /* single-linked list if more than one holida appears on a given date */
  };
  extern struct holiday holidays[366];
}

QStringList KHolidays::locations()
{
  QStringList files =
    KGlobal::dirs()->findAllResources( "data", "libkholidays/holiday_*",
                                       KStandardDirs::NoDuplicates );
  QStringList locs;

  QStringList::ConstIterator it;
  for ( it = files.begin(); it != files.end(); ++it )
    locs.append( (*it).mid((*it).lastIndexOf('_') + 1) );

  return locs;
}

KHolidays::KHolidays( const QString& location )
  : mLocation( location )
{
  mHolidayFile = KStandardDirs::locate( "data", "libkholidays/holiday_" + location );

  mYearLast = 0;
}

KHolidays::~KHolidays()
{
}

QString KHolidays::location() const
{
  return mLocation;
}

QString KHolidays::shortText( const QDate &date )
{
  QList<KHoliday> lst = getHolidays( date );
  if ( !lst.isEmpty() )
    return lst.first().text;
  else return QString();
}

bool KHolidays::parseFile( const QDate &date )
{
// kDebug()<<"KHolidays::parseFile( date=" << date << ")"<<endl;
  int lastYear = 0; //current year less 1900

  if ( mHolidayFile.isNull() || mHolidayFile.isEmpty() || date.isNull() || !date.isValid() )
    return false;

  if ( ( date.year() != mYearLast ) || ( mYearLast == 0 ) ) {
// kDebug()<<kdBacktrace();
    mYearLast = date.year();
    lastYear = date.year() - 1900; // silly parse_year takes 2 digit year...
    parse_holidays( QFile::encodeName( mHolidayFile ), lastYear, 1 );
  }

  return true;
}

QString KHolidays::getHoliday( const QDate &date )
{
  QList<KHoliday> lst = getHolidays( date );
  if ( !lst.isEmpty() )
    return lst.first().text;
  else return QString();
}

QList<KHoliday> KHolidays::getHolidays( const QDate &date )
{
  QList<KHoliday> list;
  if ( !parseFile( date ) ) return list;
  struct holiday *hd = &holidays[date.dayOfYear()-1];
  while ( hd ) {
    if ( hd->string ) {
      KHoliday holiday;
      holiday.text = QString::fromUtf8( hd->string );
      holiday.shortText = holiday.text;
      holiday.Category = (hd->color == 2/*red*/) || (hd->color == 9/*weekend*/) ? HOLIDAY : WORKDAY;
      list.append( holiday );
    }
    hd = hd->next;
  }
  return list;
}

int KHolidays::category( const QDate &date )
{
  if ( !parseFile(date) ) return WORKDAY;

  return (holidays[date.dayOfYear()-1].color == 2/*red*/) ||
         (holidays[date.dayOfYear()-1].color == 9/*weekend*/) ? HOLIDAY : WORKDAY;
}
