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
#include <KDebug>

#include "holiday_p.h"
#include "parsers/plan1/holidayparserdriverplanold_p.h"

using namespace KHolidays;

class HolidayRegion::Private
{
  public:
    Private( const QString &regionCode )
      : mDriver( 0 ), mRegionCode( regionCode )
    {
      if ( !mRegionCode.isEmpty() ) {
        if ( mRegionCode.length() == 2 ) { //Backwards compatible mode for old location code
          mLocation = mRegionCode;
          QStringList locationFiles = KGlobal::dirs()->findAllResources( "data",
                                                                         "libkholidays/plan1/holiday_" + mLocation + "*",
                                                                         KStandardDirs::NoDuplicates );
          if ( locationFiles.count() > 0 ) {
            mRegionCode = locationFiles.at( 0 ).mid( locationFiles.at( 0 ).lastIndexOf( "holiday_" ) + 8 );
          }
        } else {
          mLocation = mRegionCode.left( 2 );
        }
        mHolidayFile = KStandardDirs::locate( "data", "libkholidays/plan1/holiday_" + mRegionCode );
        if ( mHolidayFile.isEmpty() ) {
          mRegionCode.clear();
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

    HolidayParserDriver  *mDriver;  // The parser driver for the holiday file
    QString mRegionCode;            // region code of holiday region
    QString mLocation;              // old location code, use now deprecated
    QString mHolidayFile;           // full path of file containing holiday data, or null
};

HolidayRegion::HolidayRegion( const QString &regionCode )
  : d( new Private( regionCode ) )
{
}

HolidayRegion::~HolidayRegion()
{
  delete d;
}

QStringList HolidayRegion::locations()
{
  const QStringList files =
    KGlobal::dirs()->findAllResources( "data", "libkholidays/plan1/holiday_*",
                                       KStandardDirs::NoDuplicates );

  QStringList locations;
  foreach ( const QString &filename, files ) {
    locations.append( filename.mid( filename.lastIndexOf( "holiday_" ) + 8, 2 ) );
  }

  locations.removeDuplicates();
  qSort( locations );
  return locations;
}

QString HolidayRegion::location() const
{
  return d->mLocation;
}

QStringList HolidayRegion::regions()
{
  const QStringList files =
    KGlobal::dirs()->findAllResources( "data", "libkholidays/plan1/holiday_*",
                                       KStandardDirs::NoDuplicates );

  QStringList regions;
  foreach ( const QString &filename, files ) {
    regions.append( filename.mid( filename.lastIndexOf( "holiday_" ) + 8 ) );
  }

  qSort( regions );
  return regions;
}

QString HolidayRegion::regionCode() const
{
  return d->mRegionCode;
}

QString HolidayRegion::countryCode() const
{
  return d->mDriver->fileCountryCode();
}

QString HolidayRegion::countryCode( const QString &regionCode )
{
  HolidayRegion temp = HolidayRegion( regionCode );
  if ( temp.isValid() ) {
    return temp.countryCode();
  } else {
    return QString();
  }
}

QString HolidayRegion::languageCode() const
{
  return d->mDriver->fileLanguageCode();
}

QString HolidayRegion::languageCode( const QString &regionCode )
{
  HolidayRegion temp = HolidayRegion( regionCode );
  if ( temp.isValid() ) {
    return temp.languageCode();
  } else {
    return QString();
  }
}

QString HolidayRegion::name() const
{
  QString tempName = d->mDriver->fileName();
  if ( tempName.isEmpty() ) {
    QString country = countryCode().left( 2 ).toLower();
    QString regionName, typeName;;

    if ( country != "xx" ) {
      if ( countryCode().length() > 2 ) {
        // Temporary measure to get regions translated, only those files that already exist
        // In 4.6 hope to have isocodes project integration for translations via KLocale
        QString subdivision = countryCode().right( 2 ).toLower();
        if ( country == "ca" && subdivision == "qc" ) {
          regionName = i18nc( "Canadian region", "Quebec" );
        } else if ( country == "de" && subdivision == "by" ) {
          regionName = i18nc( "German region", "Baveria" );
        } else if ( country == "es" && subdivision == "ct" ) {
          regionName = i18nc( "Spanish region", "Catalonia" );
        } else if ( country == "gb" && subdivision == "eaw" ) {
          regionName = i18nc( "UK Region", "England and Wales" );
        } else if ( country == "gb" && subdivision == "eng" ) {
          regionName = i18nc( "UK Region", "England" );
        } else if ( country == "gb" && subdivision == "wls" ) {
          regionName = i18nc( "UK Region", "Wales" );
        } else if ( country == "gb" && subdivision == "sct" ) {
          regionName = i18nc( "UK Region", "Scotland" );
        } else if ( country == "gb" && subdivision == "nir" ) {
          regionName = i18nc( "UK Region", "Northern Ireland" );
        } else if ( country == "it" && subdivision == "bz" ) {
          regionName = i18nc( "Italian Region", "South Tyrol" );
        } else if ( country == "au" && subdivision == "nsw" ) {
          regionName = i18nc( "Australian Region", "New South Wales" );
        } else if ( country == "au" && subdivision == "qld" ) {
          regionName = i18nc( "Australian Region", "Queensland" );
        } else if ( country == "au" && subdivision == "vic" ) {
          regionName = i18nc( "Australian Region", "Victoria" );
        } else if ( country == "au" && subdivision == "sa" ) {
          regionName = i18nc( "Australian Region", "South Australia" );
        } else if ( country == "au" && subdivision == "nt" ) {
          regionName = i18nc( "Australian Region", "Northern Territory" );
        } else if ( country == "au" && subdivision == "act" ) {
          regionName = i18nc( "Australian Region", "Australian Capital Territory" );
        } else {
          regionName = KGlobal::locale()->countryCodeToName( country );
        }
      } else {
          regionName = KGlobal::locale()->countryCodeToName( country );
      }
    }

    if ( false ) { //TODO holiday types!
      // Will create lots more in 4.6
      typeName = i18nc( "Holiday type", "Public" );
      typeName = i18nc( "Holiday type", "Religious" );
      typeName = i18nc( "Holiday type", "Financial" );
      typeName = i18nc( "Holiday type", "Cultural" );
      typeName = i18nc( "Holiday type", "School" );
      typeName = i18nc( "Holiday type", "Seasons" );
      typeName = i18nc( "Holiday type", "Name Days" );
      typeName = i18nc( "Holiday type", "Personal" );
      // Religious types, just simple for now
      typeName = i18nc( "Holiday type", "Catholic" );
      typeName = i18nc( "Holiday type", "Protestant" );
      typeName = i18nc( "Holiday type", "Orthodox" );
      typeName = i18nc( "Holiday type", "Jewish" );
      typeName = i18nc( "Holiday type", "Islamic" );
    }

    if ( tempName.isEmpty() ) {
      tempName = i18nc( "Unknown holiday region", "Unknown" );
    }
  }
  return tempName;
}

QString HolidayRegion::name( const QString &regionCode )
{
  HolidayRegion temp = HolidayRegion( regionCode );
  if ( temp.isValid() ) {
    return temp.name();
  } else {
    return QString();
  }
}

QString HolidayRegion::description() const
{
  return d->mDriver->fileDescription();
}

QString HolidayRegion::description( const QString &regionCode )
{
  HolidayRegion temp = HolidayRegion( regionCode );
  if ( temp.isValid() ) {
    return temp.description();
  } else {
    return QString();
  }
}

bool HolidayRegion::isValid() const
{
  return !d->mHolidayFile.isEmpty() && d->mDriver;
}

bool HolidayRegion::isValid( const QString &regionCode )
{
  HolidayRegion temp = HolidayRegion( regionCode );
  return temp.isValid();
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
