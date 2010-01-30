/*
  This file is part of the kholidays library.

  Copyright (c) 2001 Cornelius Schumacher <schumacher@kde.org>
  Copyright (c) 2004 Allen Winter <winter@kde.org>
  Copyright (c) 2008 David Jarvie <djarvie@kde.org>
  Copyright 2010 John Layt <john@layt.net>

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

#include "holidayregion.h"

#include <QtCore/QDateTime>
#include <QtCore/QFile>
#include <QtCore/QSharedData>

#include <KStandardDirs>
#include <KGlobal>
#include <KLocale>

#include "holiday_p.h"
#include "parsers/plan1/holidayparserdriverplanold_p.h"

using namespace KHolidays;

class HolidayRegion::Private
{
  public:
    Private( const QString &location )
      : mDriver( 0 ), mLocation( location )
    {
      if ( !mLocation.isEmpty() ) {
        mHolidayFile = KStandardDirs::locate( "data", "libkholidays/plan1/holiday_" + mLocation );
        if ( mHolidayFile.isEmpty() ) {
          mLocation.clear();
        } else {
          mDriver = new HolidayParserDriverPlanOld( mHolidayFile );
        }
      }
    }

    ~Private()
    {
      delete mDriver;
    }

    HolidayParserDriver  *mDriver;
    QString mLocation;     // location string used to determine holidays file
    QString mHolidayFile;  // full path of file containing holiday data, or null
};

HolidayRegion::HolidayRegion( const QString &location )
  : d( new Private( location ) )
{
}

HolidayRegion::~HolidayRegion()
{
  delete d;
}

QStringList HolidayRegion::locations()
{
  const QStringList files = KGlobal::dirs()->findAllResources( "data", "libkholidays/plan1/holiday_*",
                                                               KStandardDirs::NoDuplicates );

  QStringList locations;
  foreach ( const QString &filename, files ) {
    locations.append( filename.mid( filename.lastIndexOf("holiday_") + 8 ) );
  }

  qSort( locations );
  return locations;
}

QString HolidayRegion::location() const
{
  return d->mLocation;
}

QString HolidayRegion::regionCode() const
{
  return d->mDriver->fileRegionCode();
}

QString HolidayRegion::languageCode() const
{
  return d->mDriver->fileLanguageCode();
}

// TODO Translation
QString HolidayRegion::shortName() const
{
  QString tempName = d->mDriver->fileShortName();
  if ( tempName.isEmpty() ) {
    tempName = KGlobal::locale()->countryCodeToName( regionCode().left( 2 ) );
    if ( tempName.isEmpty() ) {
      tempName = "Unknown";
    }
  }
  return tempName;
}

// TODO Translation
QString HolidayRegion::longName() const
{
  QString tempName = KGlobal::locale()->languageCodeToName( languageCode() );
  if ( tempName.isEmpty() ) {
    tempName = "Unknown";
  }
  return shortName() + " (" + tempName + ")";
}

bool HolidayRegion::isValid() const
{
  return !d->mHolidayFile.isEmpty() && d->mDriver;
}

Holiday::List HolidayRegion::holidays( const QDate &startDate, const QDate &endDate ) const
{
  if ( isValid() ) {
    return d->mDriver->parseHolidays( startDate, endDate );
  } else {
    return Holiday::List();
  }
}

Holiday::List HolidayRegion::holidays( const QDate &date ) const
{
  if ( isValid() ) {
    return d->mDriver->parseHolidays( date );
  } else {
    return Holiday::List();
  }
}

Holiday::List HolidayRegion::holidays( int calendarYear, const QString &calendarType ) const
{
  if ( isValid() ) {
    return d->mDriver->parseHolidays( calendarYear, calendarType );
  } else {
    return Holiday::List();
  }
}

bool HolidayRegion::isHoliday( const QDate &date ) const
{
  Holiday::List holidayList = holidays( date );
  if ( holidayList.count() > 0 ) {
    foreach ( const KHolidays::Holiday &holiday, holidayList ) {
      if ( holiday.dayType() == Holiday::NonWorkday ) {
        return true;
      }
    }
  }
  return false;
}
