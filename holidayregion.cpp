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
#include <KLocalizedString>
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
                                      QLatin1String("libkholidays/plan2/holiday_") + mLocation + QLatin1Char('*'),
                                      KStandardDirs::NoDuplicates );
          if ( locationFiles.count() > 0 ) {
            mRegionCode = locationFiles.at( 0 ).
                          mid( locationFiles.at( 0 ).lastIndexOf( QLatin1String("holiday_") ) + 8 );
          }
        }

        mHolidayFile.setFile(
          KStandardDirs::locate( "data", QLatin1String("libkholidays/plan2/holiday_") + mRegionCode ) );
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
    KGlobal::dirs()->findAllResources( "data", QLatin1String("libkholidays/plan2/holiday_*"),
                                       KStandardDirs::NoDuplicates );

  QStringList locations;
  foreach ( const QString &filename, files ) {
    locations.append( filename.mid( filename.lastIndexOf( QLatin1String("holiday_") ) + 8, 2 ) );
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
    KGlobal::dirs()->findAllResources( "data", QLatin1String("libkholidays/plan2/holiday_*"),
                                       KStandardDirs::NoDuplicates );

  QStringList regionCodesList;
  foreach ( const QString &filename, files ) {
    regionCodesList.append( filename.mid( filename.lastIndexOf( QLatin1String("holiday_") ) + 8 ) );
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
    QStringList countryParts = countryCode().toLower().split( QLatin1Char('-') );
    QString country = countryParts.at( 0 );
    QString regionName, typeName;

    if ( country != QLatin1String("xx") ) {
      if ( countryParts.count() == 2 ) {
        // Temporary measure to get regions translated, only those files that already exist
        // In 4.6 hope to have isocodes project integration for translations via KLocale
        QString subdivision = countryParts.at( 1 );
        if ( country == QLatin1String("ca") && subdivision == QLatin1String("qc") ) {
          regionName = i18nc( "Canadian region", "Quebec" );
        } else if ( country == QLatin1String("de") && subdivision == QLatin1String("by") ) {
          regionName = i18nc( "German region", "Bavaria" );
        } else if ( country == QLatin1String("es") && subdivision == QLatin1String("ct") ) {
          regionName = i18nc( "Spanish region", "Catalonia" );
        } else if ( country == QLatin1String("gb") && subdivision == QLatin1String("eaw") ) {
          regionName = i18nc( "UK Region", "England and Wales" );
        } else if ( country == QLatin1String("gb") && subdivision == QLatin1String("eng") ) {
          regionName = i18nc( "UK Region", "England" );
        } else if ( country == QLatin1String("gb") && subdivision == QLatin1String("wls") ) {
          regionName = i18nc( "UK Region", "Wales" );
        } else if ( country == QLatin1String("gb") && subdivision == QLatin1String("sct") ) {
          regionName = i18nc( "UK Region", "Scotland" );
        } else if ( country == QLatin1String("gb") && subdivision == QLatin1String("nir") ) {
          regionName = i18nc( "UK Region", "Northern Ireland" );
        } else if ( country == QLatin1String("it") && subdivision == QLatin1String("bz") ) {
          regionName = i18nc( "Italian Region", "South Tyrol" );
        } else if ( country == QLatin1String("au") && subdivision == QLatin1String("nsw") ) {
          regionName = i18nc( "Australian Region", "New South Wales" );
        } else if ( country == QLatin1String("au") && subdivision == QLatin1String("qld") ) {
          regionName = i18nc( "Australian Region", "Queensland" );
        } else if ( country == QLatin1String("au") && subdivision == QLatin1String("vic") ) {
          regionName = i18nc( "Australian Region", "Victoria" );
        } else if ( country == QLatin1String("au") && subdivision == QLatin1String("sa") ) {
          regionName = i18nc( "Australian Region", "South Australia" );
        } else if ( country == QLatin1String("au") && subdivision == QLatin1String("nt") ) {
          regionName = i18nc( "Australian Region", "Northern Territory" );
        } else if ( country == QLatin1String("au") && subdivision == QLatin1String("act") ) {
          regionName = i18nc( "Australian Region", "Australian Capital Territory" );
        } else if ( country == QLatin1String("au") && subdivision == QLatin1String("wa") ) {
          regionName = i18nc( "Australian Region", "Western Australia" );
        } else if ( country == QLatin1String("au") && subdivision == QLatin1String("tas") ) {
          regionName = i18nc( "Australian Region", "Tasmania" );
        } else if ( country == QLatin1String("ba") && subdivision == QLatin1String("srp") ) {
          regionName = i18nc( "Bosnian and Herzegovinian Region", "Republic of Srpska" );
        } else {
          regionName = KGlobal::locale()->countryCodeToName( country );
        }
      } else {
          regionName = KGlobal::locale()->countryCodeToName( country );
      }
    }

    //Cheat on type for now,take direct from region code until API is introduced in SC 4.6
    QStringList regionParts = regionCode().toLower().split( QLatin1Char('_') );
    if ( regionParts.count() == 3 ) {
      QString type = regionParts.at( 2 );
      // Will create lots more in 4.6
      // Religious types, just simple for now
      if ( type == QLatin1String("public") ) {
        typeName = i18nc( "Holiday type", "Public" );
      } else if ( type == QLatin1String("civil") ) {
        typeName = i18nc( "Holiday type", "Civil" );
      } else if ( type == QLatin1String("religious") ) {
        typeName = i18nc( "Holiday type", "Religious" );
      } else if ( type == QLatin1String("government") ) {
        typeName = i18nc( "Holiday type", "Government" );
      } else if ( type == QLatin1String("financial") ) {
        typeName = i18nc( "Holiday type", "Financial" );
      } else if ( type == QLatin1String("cultural") ) {
        typeName = i18nc( "Holiday type", "Cultural" );
      } else if ( type == QLatin1String("commemorative") ) {
        typeName = i18nc( "Holiday type", "Commemorative" );
      } else if ( type == QLatin1String("historical") ) {
        typeName = i18nc( "Holiday type", "Historical" );
      } else if ( type == QLatin1String("school") ) {
        typeName = i18nc( "Holiday type", "School" );
      } else if ( type == QLatin1String("seasonal") ) {
        typeName = i18nc( "Holiday type", "Seasonal" );
      } else if ( type == QLatin1String("nameday") ) {
        typeName = i18nc( "Holiday type", "Name Days" );
      } else if ( type == QLatin1String("personal") ) {
        typeName = i18nc( "Holiday type", "Personal" );
      } else if ( type == QLatin1String("catholic") ) {
        typeName = i18nc( "Holiday type", "Catholic" );
      } else if ( type == QLatin1String("protestant") ) {
        typeName = i18nc( "Holiday type", "Protestant" );
      } else if ( type == QLatin1String("orthodox") ) {
        typeName = i18nc( "Holiday type", "Orthodox" );
      } else if ( type == QLatin1String("jewish") ) {
        typeName = i18nc( "Holiday type", "Jewish" );
      } else if ( type == QLatin1String("islamic") ) {
        typeName = i18nc( "Holiday type", "Islamic" );
      }
    }

    if ( !regionName.isEmpty() ) {
      if ( !typeName.isEmpty() ) {
        tempName = i18nc( "Holiday file display name, %1 = region name, %2 = holiday type", "%1 - %2" ).arg( regionName ).arg( typeName );
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
  return holidays( startDate, endDate, Holiday::MultidayHolidaysAsMultipleEvents );
}

Holiday::List HolidayRegion::holidays( const QDate &startDate, const QDate &endDate,
                                       Holiday::MultidayMode multidayMode ) const
{
  if ( isValid() ) {
    return d->mDriver->parseHolidays( startDate, endDate, multidayMode );
  } else {
    return Holiday::List();
  }
}

Holiday::List HolidayRegion::holidays( const QDate &date ) const
{
  return holidays( date, Holiday::MultidayHolidaysAsMultipleEvents );
}

Holiday::List HolidayRegion::holidays( const QDate &date, Holiday::MultidayMode multidayMode ) const
{
  if ( isValid() ) {
    return d->mDriver->parseHolidays( date, multidayMode );
  } else {
    return Holiday::List();
  }
}

Holiday::List HolidayRegion::holidays( int calendarYear, const QString &calendarType ) const
{
  return holidays( calendarYear, calendarType, Holiday::MultidayHolidaysAsMultipleEvents );
}

Holiday::List HolidayRegion::holidays( int calendarYear, const QString &calendarType,
                                       Holiday::MultidayMode multidayMode ) const
{
  if ( isValid() ) {
    return d->mDriver->parseHolidays( calendarYear, calendarType, multidayMode );
  } else {
    return Holiday::List();
  }
}

bool HolidayRegion::isHoliday( const QDate &date ) const
{
  Holiday::List holidayList = holidays( date, Holiday::MultidayHolidaysAsMultipleEvents );
  if ( holidayList.count() > 0 ) {
    foreach ( const KHolidays::Holiday &holiday, holidayList ) {
      if ( holiday.dayType() == Holiday::NonWorkday ) {
        return true;
      }
    }
  }
  return false;
}

QString HolidayRegion::defaultRegionCode( const QString &country, const QString &language )
{
  // Try to match against the users country and language, or failing that the language country.
  // Scan through all the regions finding the first match for each possible default
  // Holiday Region Country Code can be a country subdivision or the country itself,
  // e.g. US or US-CA for California, so we can try match on both but an exact match has priority
  // The Holiday Region file is in one language only, so give priority to any file in the
  // users language, e.g. bilingual countries with a separate file for each language
  // Locale language can have a country code embedded in it e.g. en_GB, which we can try use if
  // no country set, but a lot of countries use en_GB so it's a lower priority option

  QString localeCountry, localeLanguage, localeLanguageCountry;

  if ( country.isEmpty() ) {
    localeCountry = KGlobal::locale()->country().toLower();
  } else {
    localeCountry = country.toLower();
  }

  if ( language.isEmpty() ) {
    localeLanguage = KGlobal::locale()->language().toLower();
  } else {
    localeLanguage = language.toLower();
  }

  if ( localeLanguage.split( QLatin1Char('_') ).count() > 1 ) {
    localeLanguageCountry = localeLanguage.split( QLatin1Char('_') ).at( 1 );
  }

  QStringList regionList = KHolidays::HolidayRegion::regionCodes();

  QString countryAndLanguageMatch, countryOnlyMatch, subdivisionAndLanguageMatch,
          subdivisionOnlyMatch, languageCountryAndLanguageMatch, languageCountryOnlyMatch,
          languageSubdivisionAndLanguageMatch, languageSubdivisionOnlyMatch;

  foreach ( const QString &regionCode, regionList ) {
    QString regionCountry = KHolidays::HolidayRegion::countryCode( regionCode ).toLower();
    QString regionSubdivisionCountry;
    if ( regionCountry.split( QLatin1Char('-') ).count() > 1 ) {
      regionSubdivisionCountry = regionCountry.split( QLatin1Char('-') ).at( 0 );
    }
    QString regionLanguage = KHolidays::HolidayRegion::languageCode( regionCode ).toLower();

    if ( regionCountry == localeCountry && regionLanguage == localeLanguage ) {
      countryAndLanguageMatch = regionCode;
      break; // exact match so don't look further
    } else if ( regionCountry == localeCountry ) {
      if ( countryOnlyMatch.isEmpty() ) {
        countryOnlyMatch = regionCode;
      }
    } else if ( !regionSubdivisionCountry.isEmpty() &&
                regionSubdivisionCountry == localeCountry &&
                regionLanguage == localeLanguage ) {
      if ( subdivisionAndLanguageMatch.isEmpty() ) {
        subdivisionAndLanguageMatch = regionCode;
      }
    } else if ( !regionSubdivisionCountry.isEmpty() && regionSubdivisionCountry == localeCountry ) {
      if ( subdivisionOnlyMatch.isEmpty() ) {
        subdivisionOnlyMatch = regionCode;
      }
    } else if ( !localeLanguageCountry.isEmpty() &&
                regionCountry == localeLanguageCountry &&
                regionLanguage == localeLanguage ) {
      if ( languageCountryAndLanguageMatch.isEmpty() ) {
        languageCountryAndLanguageMatch = regionCode;
      }
    } else if ( !localeLanguageCountry.isEmpty() && regionCountry == localeLanguageCountry ) {
      if ( languageCountryOnlyMatch.isEmpty() ) {
        languageCountryOnlyMatch = regionCode;
      }
    } else if ( !regionSubdivisionCountry.isEmpty() &&
                !localeLanguageCountry.isEmpty() &&
                regionSubdivisionCountry == localeLanguageCountry &&
                regionLanguage == localeLanguage ) {
      if ( languageSubdivisionAndLanguageMatch.isEmpty() ) {
        languageSubdivisionAndLanguageMatch = regionCode;
      }
    } else if ( !regionSubdivisionCountry.isEmpty() &&
                !localeLanguageCountry.isEmpty() &&
                regionSubdivisionCountry == localeLanguageCountry ) {
      if ( languageSubdivisionOnlyMatch.isEmpty() ) {
        languageSubdivisionOnlyMatch = regionCode;
      }
    }
  }

  QString defaultRegionCode;

  if ( !countryAndLanguageMatch.isEmpty() ) {
    defaultRegionCode = countryAndLanguageMatch;
  } else if ( !countryOnlyMatch.isEmpty() ) {
    defaultRegionCode = countryOnlyMatch;
  } else if ( !subdivisionAndLanguageMatch.isEmpty() ) {
    defaultRegionCode = subdivisionAndLanguageMatch;
  } else if ( !subdivisionOnlyMatch.isEmpty() ) {
    defaultRegionCode = subdivisionOnlyMatch;
  } else if ( !languageCountryAndLanguageMatch.isEmpty() ) {
    defaultRegionCode = languageCountryAndLanguageMatch;
  } else if ( !languageCountryOnlyMatch.isEmpty() ) {
    defaultRegionCode = languageCountryOnlyMatch;
  } else if ( !languageSubdivisionAndLanguageMatch.isEmpty() ) {
    defaultRegionCode = languageSubdivisionAndLanguageMatch;
  } else if ( !languageSubdivisionOnlyMatch.isEmpty() ) {
    defaultRegionCode = languageSubdivisionOnlyMatch;
  }

  return defaultRegionCode;
}
