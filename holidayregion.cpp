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
#include <QtCore/QFileInfo>

#include <KStandardDirs>
#include <KGlobal>
#include <KLocale>
#include <KDebug>

#include "holiday_p.h"
#include "parsers/plan2/holidayparserdriverplan_p.h"

using namespace KHolidays;

class HolidayRegion::Private
{
  public:
    Private( const QString &regionCode ) : mDriver( 0 ),
                                           mRegionCode( regionCode )
    {
      if ( !mRegionCode.isEmpty() ) {

        if ( mRegionCode.length() == 2 ) { //Backwards compatible mode for old location code
          mLocation = mRegionCode;
          QStringList locationFiles = KGlobal::dirs()->findAllResources( "data",
                                                                         "libkholidays/plan2/holiday_" + mLocation + "*",
                                                                         KStandardDirs::NoDuplicates );
          if ( locationFiles.count() > 0 ) {
            mRegionCode = locationFiles.at( 0 ).mid( locationFiles.at( 0 ).lastIndexOf( "holiday_" ) + 8 );
          }
        }

        mHolidayFile.setFile( KStandardDirs::locate( "data", "libkholidays/plan2/holiday_" + mRegionCode ) );
      }

      init();
    }

    Private( const QFileInfo &regionFile ) : mDriver( 0 ),
                                             mHolidayFile( regionFile )
    {
      init();
    }

    ~Private()
    {
      delete mDriver;
    }

    void init()
    {
      if ( mHolidayFile.exists() ) {
        mDriver = new HolidayParserDriverPlan( mHolidayFile.absoluteFilePath() );
        if ( mDriver ) {

          if ( mLocation.isEmpty() ) {
            mLocation = mDriver->fileCountryCode().left( 2 );
          }

          if ( mRegionCode.isEmpty() ) {
            if ( mHolidayFile.fileName().startsWith( QLatin1String( "holiday_" ) ) ) {
              mRegionCode = mHolidayFile.fileName().mid( 8 );
            } else {
              mRegionCode = mHolidayFile.fileName();
            }
          }

        } else {
          mRegionCode.clear();
          mLocation.clear();
        }
      } else {
        mRegionCode.clear();
        mLocation.clear();
      }
    }

    HolidayParserDriver  *mDriver;  // The parser driver for the holiday file
    QString mRegionCode;            // region code of holiday region
    QString mLocation;              // old location code, use now deprecated
    QFileInfo mHolidayFile;         // file containing holiday data, or null
};

HolidayRegion::HolidayRegion( const QString &regionCode )
  : d( new Private( regionCode ) )
{
}

HolidayRegion::HolidayRegion( const QFileInfo &regionFile )
             : d( new Private( regionFile ) )
{
}

HolidayRegion::~HolidayRegion()
{
  delete d;
}

QStringList HolidayRegion::locations()
{
  const QStringList files =
    KGlobal::dirs()->findAllResources( "data", "libkholidays/plan2/holiday_*",
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

QStringList HolidayRegion::regionCodes()
{
  const QStringList files =
    KGlobal::dirs()->findAllResources( "data", "libkholidays/plan2/holiday_*",
                                       KStandardDirs::NoDuplicates );

  QStringList regionCodesList;
  foreach ( const QString &filename, files ) {
    regionCodesList.append( filename.mid( filename.lastIndexOf( "holiday_" ) + 8 ) );
  }

  qSort( regionCodesList );
  return regionCodesList;
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
    QStringList countryParts = countryCode().toLower().split( '-' );
    QString country = countryParts.at( 0 );
    QString regionName, typeName;

    if ( country != "xx" ) {
      if ( countryParts.count() == 2 ) {
        // Temporary measure to get regions translated, only those files that already exist
        // In 4.6 hope to have isocodes project integration for translations via KLocale
        QString subdivision = countryParts.at( 1 );
        if ( country == "ca" && subdivision == "qc" ) {
          regionName = i18nc( "Canadian region", "Quebec" );
        } else if ( country == "de" && subdivision == "by" ) {
          regionName = i18nc( "German region", "Bavaria" );
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
        } else if ( country == "au" && subdivision == "wa" ) {
          regionName = i18nc( "Australian Region", "Western Australia" );
        } else if ( country == "au" && subdivision == "tas" ) {
          regionName = i18nc( "Australian Region", "Tasmania" );
        } else {
          regionName = KGlobal::locale()->countryCodeToName( country );
        }
      } else {
          regionName = KGlobal::locale()->countryCodeToName( country );
      }
    }

    //Cheat on type for now,take direct from region code until API is introduced in SC 4.6
    QStringList regionParts = regionCode().toLower().split( '_' );
    if ( regionParts.count() == 3 ) {
      QString type = regionParts.at( 2 );
      // Will create lots more in 4.6
      // Religious types, just simple for now
      if ( type == "public" ) {
        typeName = i18nc( "Holiday type", "Public" );
      } else if ( type == "religious" ) {
        typeName = i18nc( "Holiday type", "Religious" );
      } else if ( type == "financial" ) {
        typeName = i18nc( "Holiday type", "Financial" );
      } else if ( type == "cultural" ) {
        typeName = i18nc( "Holiday type", "Cultural" );
      } else if ( type == "school" ) {
        typeName = i18nc( "Holiday type", "School" );
      } else if ( type == "seasons" ) {
        typeName = i18nc( "Holiday type", "Seasons" );
      } else if ( type == "name" ) {
        typeName = i18nc( "Holiday type", "Name Days" );
      } else if ( type == "personal" ) {
        typeName = i18nc( "Holiday type", "Personal" );
      } else if ( type == "catholic" ) {
        typeName = i18nc( "Holiday type", "Catholic" );
      } else if ( type == "protestant" ) {
        typeName = i18nc( "Holiday type", "Protestant" );
      } else if ( type == "orthodox" ) {
        typeName = i18nc( "Holiday type", "Orthodox" );
      } else if ( type == "jewish" ) {
        typeName = i18nc( "Holiday type", "Jewish" );
      } else if ( type == "islamic" ) {
        typeName = i18nc( "Holiday type", "Islamic" );
      }
    }

    if ( !regionName.isEmpty() ) {
      if ( !typeName.isEmpty() ) {
        //TODO translate when not frozen
        tempName = QString( "%1 - %2" ).arg( regionName ).arg( typeName );
      } else {
        tempName = regionName;
      }
    } else if ( !typeName.isEmpty() ) {
      tempName = typeName;
    } else {
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
  return d->mHolidayFile.exists() && d->mDriver;
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
