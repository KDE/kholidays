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

#include <QtCore/QDateTime>
#include <QtCore/QFile>
#include <QtCore/QSharedData>

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

namespace KHolidays {

class KHolidayPrivate : public QSharedData
{
  public:
    KHolidayPrivate()
    {
    }

    KHolidayPrivate( const KHolidayPrivate &other )
      : QSharedData( other )
    {
      mText = other.mText;
      mShortText = other.mShortText;
      mDayType = other.mDayType;
    }

    QString mText;
    QString mShortText;
    KHoliday::DayType mDayType;
};

}

KHoliday::KHoliday()
  : d( new KHolidayPrivate )
{
}

KHoliday::KHoliday( const KHoliday &other )
  : d( other.d )
{
}

KHoliday::~KHoliday()
{
}

KHoliday &KHoliday::operator=( const KHoliday &other )
{
  if ( &other != this ) {
    d = other.d;
  }

  return *this;
}

QString KHoliday::text() const
{
  return d->mText;
}

QString KHoliday::shortText() const
{
  return d->mShortText;
}

KHoliday::DayType KHoliday::dayType() const
{
  return d->mDayType;
}

class KHolidayRegion::Private
{
  public:
    Private( const QString &location )
      : mLocation( location ),
        mYearLast( 0 )
    {
      if ( !mLocation.isEmpty() ) {
        mHolidayFile = KStandardDirs::locate( "data", "libkholidays/holiday_" + mLocation );
        if ( mHolidayFile.isEmpty() ) {
          mLocation.clear();
        }
      }
    }

    bool parseFile( const QDate &date ) const
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

    QString mLocation;     // location string used to determine holidays file
    QString mHolidayFile;  // full path of file containing holiday data, or null
    mutable int mYearLast; // save of the last year we have seen
};

KHolidayRegion::KHolidayRegion( const QString &location )
  : d( new Private( location ) )
{
}

KHolidayRegion::~KHolidayRegion()
{
  delete d;
}

QStringList KHolidayRegion::locations()
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

QString KHolidayRegion::location() const
{
  return d->mLocation;
}

bool KHolidayRegion::isValid() const
{
  return !d->mHolidayFile.isEmpty();
}

KHoliday::List KHolidayRegion::holidays( const QDate &date ) const
{
  KHoliday::List list;
  if ( !d->parseFile( date ) ) {
    return list;
  }

  struct holiday *hd = &::holidays[date.dayOfYear()-1];
  while ( hd ) {
    if ( hd->string ) {
      KHoliday holiday;
      holiday.d->mText = QString::fromUtf8( hd->string );
      holiday.d->mShortText = holiday.d->mText;
      holiday.d->mDayType = ( hd->color == 2/*red*/ ) || ( hd->color == 9/*weekend*/ ) ?
                              KHoliday::Holiday : KHoliday::Workday;
      list.append( holiday );
    }
    hd = hd->next;
  }
  return list;
}

bool KHolidayRegion::isHoliday( const QDate &date ) const
{
  if ( !d->parseFile( date ) ) {
    return false;
  }
  struct holiday *hd = &::holidays[date.dayOfYear()-1];
  while ( hd ) {
    if ( hd->string && ( hd->color == 2/*red*/ || hd->color == 9/*weekend*/ ) ) {
      return true;
    }
    hd = hd->next;
  }
  return false;
}
