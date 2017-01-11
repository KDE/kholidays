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
#include <QtCore/QDirIterator>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QSharedData>
#include <QtCore/QStandardPaths>
#include <QtCore/QCoreApplication>

#include "holiday_p.h"
#include "parsers/plan2/holidayparserdriverplan_p.h"

using namespace KHolidays;

static QStringList allHolidayFiles(const QString &location = QString())
{
    const QStringList dirs = QStandardPaths::locateAll(QStandardPaths::GenericDataLocation,
                             QStringLiteral("kf5/libkholidays/plan2"),
                             QStandardPaths::LocateDirectory);
    QStringList files;
    foreach (const QString &dir, dirs) {
        QDirIterator it(dir, QStringList() << QStringLiteral("holiday_") + location + '*');
        while (it.hasNext()) {
            files.push_back(it.next());
        }
    }
    return files;
}

class Q_DECL_HIDDEN HolidayRegion::HolidayRegionPrivate
{
public:
    HolidayRegionPrivate(const QString &regionCode) : mDriver(nullptr),
        mRegionCode(regionCode)
    {
        if (!mRegionCode.isEmpty()) {
            mHolidayFile.setFile(
                QStandardPaths::locate(QStandardPaths::GenericDataLocation,
                                       QLatin1String("kf5/libkholidays/plan2/holiday_") + mRegionCode));
        }

        init();
    }

    HolidayRegionPrivate(const QFileInfo &regionFile) : mDriver(nullptr),
        mHolidayFile(regionFile)
    {
        init();
    }

    ~HolidayRegionPrivate()
    {
        delete mDriver;
    }

    void init()
    {
        if (mHolidayFile.exists()) {
            mDriver = new HolidayParserDriverPlan(mHolidayFile.absoluteFilePath());
            if (mDriver) {

                if (mRegionCode.isEmpty()) {
                    if (mHolidayFile.fileName().startsWith(QLatin1String("holiday_"))) {
                        mRegionCode = mHolidayFile.fileName().mid(8);
                    } else {
                        mRegionCode = mHolidayFile.fileName();
                    }
                }

            } else {
                mRegionCode.clear();
            }
        } else {
            mRegionCode.clear();
        }
    }

    HolidayParserDriver  *mDriver;  // The parser driver for the holiday file
    QString mRegionCode;            // region code of holiday region
    QFileInfo mHolidayFile;         // file containing holiday data, or null
};

HolidayRegion::HolidayRegion(const QString &regionCode)
    : d(new HolidayRegionPrivate(regionCode))
{
}

HolidayRegion::HolidayRegion(const QFileInfo &regionFile)
    : d(new HolidayRegionPrivate(regionFile))
{
}

HolidayRegion::~HolidayRegion()
{
    delete d;
}

QStringList HolidayRegion::regionCodes()
{
    const QStringList files = allHolidayFiles();

    QStringList regionCodesList;
    regionCodesList.reserve(files.count());
    foreach (const QString &filename, files) {
        regionCodesList.append(filename.mid(filename.lastIndexOf(QLatin1String("holiday_")) + 8));
    }

    qSort(regionCodesList);
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

QString HolidayRegion::countryCode(const QString &regionCode)
{
    HolidayRegion temp(regionCode);
    if (temp.isValid()) {
        return temp.countryCode();
    } else {
        return QString();
    }
}

QString HolidayRegion::languageCode() const
{
    return d->mDriver->fileLanguageCode();
}

QString HolidayRegion::languageCode(const QString &regionCode)
{
    HolidayRegion temp(regionCode);
    if (temp.isValid()) {
        return temp.languageCode();
    } else {
        return QString();
    }
}

QString HolidayRegion::name() const
{
    QString tempName = d->mDriver->fileName();

    if (tempName.isEmpty()) {
        QStringList countryParts = countryCode().toLower().split(QLatin1Char('-'));
        QString country = countryParts.at(0);
        QString regionName, typeName;

        if (country != QLatin1String("xx")) {
            if (countryParts.count() == 2) {
                // Temporary measure to get regions translated, only those files that already exist
                // In 4.6 hope to have isocodes project integration for translations via KLocale
                QString subdivision = countryParts.at(1);
                if (country == QLatin1String("ca") && subdivision == QLatin1String("qc")) {
                    regionName = QCoreApplication::translate("HolidayRegion", "Quebec",  "Canadian region");
                } else if (country == QLatin1String("de") && subdivision == QLatin1String("by")) {
                    regionName = QCoreApplication::translate("HolidayRegion", "Bavaria",  "German region");
                } else if (country == QLatin1String("es") && subdivision == QLatin1String("ct")) {
                    regionName = QCoreApplication::translate("HolidayRegion", "Catalonia",  "Spanish region");
                } else if (country == QLatin1String("gb") && subdivision == QLatin1String("eaw")) {
                    regionName = QCoreApplication::translate("HolidayRegion", "England and Wales",  "UK Region");
                } else if (country == QLatin1String("gb") && subdivision == QLatin1String("eng")) {
                    regionName = QCoreApplication::translate("HolidayRegion", "England",  "UK Region");
                } else if (country == QLatin1String("gb") && subdivision == QLatin1String("wls")) {
                    regionName = QCoreApplication::translate("HolidayRegion", "Wales",  "UK Region");
                } else if (country == QLatin1String("gb") && subdivision == QLatin1String("sct")) {
                    regionName = QCoreApplication::translate("HolidayRegion", "Scotland",  "UK Region");
                } else if (country == QLatin1String("gb") && subdivision == QLatin1String("nir")) {
                    regionName = QCoreApplication::translate("HolidayRegion", "Northern Ireland",  "UK Region");
                } else if (country == QLatin1String("it") && subdivision == QLatin1String("bz")) {
                    regionName = QCoreApplication::translate("HolidayRegion", "South Tyrol",  "Italian Region");
                } else if (country == QLatin1String("au") && subdivision == QLatin1String("nsw")) {
                    regionName = QCoreApplication::translate("HolidayRegion", "New South Wales");
                } else if (country == QLatin1String("au") && subdivision == QLatin1String("qld")) {
                    regionName = QCoreApplication::translate("HolidayRegion", "Queensland",  "Australian Region");
                } else if (country == QLatin1String("au") && subdivision == QLatin1String("vic")) {
                    regionName = QCoreApplication::translate("HolidayRegion", "Victoria",  "Australian Region");
                } else if (country == QLatin1String("au") && subdivision == QLatin1String("sa")) {
                    regionName = QCoreApplication::translate("HolidayRegion", "South Australia",  "Australian Region");
                } else if (country == QLatin1String("au") && subdivision == QLatin1String("nt")) {
                    regionName = QCoreApplication::translate("HolidayRegion", "Northern Territory",  "Australian Region");
                } else if (country == QLatin1String("au") && subdivision == QLatin1String("act")) {
                    regionName = QCoreApplication::translate("HolidayRegion", "Australian Capital Territory",  "Australian Region");
                } else if (country == QLatin1String("au") && subdivision == QLatin1String("wa")) {
                    regionName = QCoreApplication::translate("HolidayRegion", "Western Australia",  "Australian Region");
                } else if (country == QLatin1String("au") && subdivision == QLatin1String("tas")) {
                    regionName = QCoreApplication::translate("HolidayRegion", "Tasmania",  "Australian Region");
                } else if (country == QLatin1String("ba") && subdivision == QLatin1String("srp")) {
                    regionName = QCoreApplication::translate("HolidayRegion", "Republic of Srpska",  "Bosnian and Herzegovinian Region");
                } else {
                    // TODO Note this does not give the current QLocale translation!
                    regionName = QLocale::countryToString(codeToCountry(country));
                }
            } else {
                // TODO Note this does not give the current QLocale translation!
                regionName = QLocale::countryToString(codeToCountry(country));
            }
        }

        //Cheat on type for now,take direct from region code until API is introduced in SC 4.6
        QStringList regionParts = regionCode().toLower().split(QLatin1Char('_'));
        if (regionParts.count() == 3) {
            QString type = regionParts.at(2);
            // Will create lots more in 4.6
            // Religious types, just simple for now
            if (type == QLatin1String("public")) {
                typeName = QCoreApplication::translate("HolidayRegion", "Public",  "Holiday type");
            } else if (type == QLatin1String("civil")) {
                typeName = QCoreApplication::translate("HolidayRegion", "Civil",  "Holiday type");
            } else if (type == QLatin1String("religious")) {
                typeName = QCoreApplication::translate("HolidayRegion", "Religious",  "Holiday type");
            } else if (type == QLatin1String("government")) {
                typeName = QCoreApplication::translate("HolidayRegion", "Government",  "Holiday type");
            } else if (type == QLatin1String("financial")) {
                typeName = QCoreApplication::translate("HolidayRegion", "Financial",  "Holiday type");
            } else if (type == QLatin1String("cultural")) {
                typeName = QCoreApplication::translate("HolidayRegion", "Cultural",  "Holiday type");
            } else if (type == QLatin1String("commemorative")) {
                typeName = QCoreApplication::translate("HolidayRegion", "Commemorative",  "Holiday type");
            } else if (type == QLatin1String("historical")) {
                typeName = QCoreApplication::translate("HolidayRegion", "Historical",  "Holiday type");
            } else if (type == QLatin1String("school")) {
                typeName = QCoreApplication::translate("HolidayRegion", "School",  "Holiday type");
            } else if (type == QLatin1String("seasonal")) {
                typeName = QCoreApplication::translate("HolidayRegion", "Seasonal",  "Holiday type");
            } else if (type == QLatin1String("nameday")) {
                typeName = QCoreApplication::translate("HolidayRegion", "Name Days",  "Holiday type");
            } else if (type == QLatin1String("personal")) {
                typeName = QCoreApplication::translate("HolidayRegion", "Personal",  "Holiday type");
            } else if (type == QLatin1String("christian")) {
                typeName = QCoreApplication::translate("HolidayRegion", "Christian",  "Holiday type");
            } else if (type == QLatin1String("anglican")) {
                typeName = QCoreApplication::translate("HolidayRegion", "Anglican",  "Holiday type");
            } else if (type == QLatin1String("catholic")) {
                typeName = QCoreApplication::translate("HolidayRegion", "Catholic",  "Holiday type");
            } else if (type == QLatin1String("protestant")) {
                typeName = QCoreApplication::translate("HolidayRegion", "Protestant",  "Holiday type");
            } else if (type == QLatin1String("orthodox")) {
                typeName = QCoreApplication::translate("HolidayRegion", "Orthodox",  "Holiday type");
            } else if (type == QLatin1String("jewish")) {
                typeName = QCoreApplication::translate("HolidayRegion", "Jewish",  "Holiday type");
            } else if (type == QLatin1String("jewish-orthodox")) {
                typeName = QCoreApplication::translate("HolidayRegion", "Jewish Orthodox",  "Holiday type");
            } else if (type == QLatin1String("jewish-conservative")) {
                typeName = QCoreApplication::translate("HolidayRegion", "Jewish Conservative",  "Holiday type");
            } else if (type == QLatin1String("jewish-reform")) {
                typeName = QCoreApplication::translate("HolidayRegion", "Jewish Reform",  "Holiday type");
            } else if (type == QLatin1String("islamic")) {
                typeName = QCoreApplication::translate("HolidayRegion", "Islamic",  "Holiday type");
            } else if (type == QLatin1String("islamic-sunni")) {
                typeName = QCoreApplication::translate("HolidayRegion", "Islamic Sunni",  "Holiday type");
            } else if (type == QLatin1String("islamic-shia")) {
                typeName = QCoreApplication::translate("HolidayRegion", "Islamic Shia",  "Holiday type");
            } else if (type == QLatin1String("islamic-sufi")) {
                typeName = QCoreApplication::translate("HolidayRegion", "Islamic Sufi",  "Holiday type");
            }
        }

        if (!regionName.isEmpty()) {
            if (!typeName.isEmpty()) {
                tempName = QCoreApplication::translate("HolidayRegion", "%1 - %2",  "Holiday file display name, %1 = region name, %2 = holiday type").arg(regionName, typeName);
            } else {
                tempName = regionName;
            }
        } else if (!typeName.isEmpty()) {
            tempName = typeName;
        } else {
            tempName = QCoreApplication::translate("HolidayRegion", "Unknown",  "Unknown holiday region");
        }
    }
    return tempName;
}

QString HolidayRegion::name(const QString &regionCode)
{
    HolidayRegion temp(regionCode);
    if (temp.isValid()) {
        return temp.name();
    } else {
        return QString();
    }
}

QString HolidayRegion::description() const
{
    return d->mDriver->fileDescription();
}

QString HolidayRegion::description(const QString &regionCode)
{
    HolidayRegion temp(regionCode);
    if (temp.isValid()) {
        return temp.description();
    } else {
        return QString();
    }
}

bool HolidayRegion::isValid() const
{
    return d->mHolidayFile.exists() && d->mDriver;
}

bool HolidayRegion::isValid(const QString &regionCode)
{
    HolidayRegion temp(regionCode);
    return temp.isValid();
}

Holiday::List HolidayRegion::holidays(const QDate &startDate, const QDate &endDate) const
{
    if (isValid()) {
        return d->mDriver->parseHolidays(startDate, endDate);
    } else {
        return Holiday::List();
    }
}

Holiday::List HolidayRegion::holidays(const QDate &date) const
{
    if (isValid()) {
        return d->mDriver->parseHolidays(date);
    } else {
        return Holiday::List();
    }
}

Holiday::List HolidayRegion::holidays(int calendarYear) const
{
    if (isValid()) {
        return d->mDriver->parseHolidays(calendarYear);
    } else {
        return Holiday::List();
    }
}

bool HolidayRegion::isHoliday(const QDate &date) const
{
    Holiday::List holidayList = holidays(date);
    if (holidayList.count() > 0) {
        foreach (const KHolidays::Holiday &holiday, holidayList) {
            if (holiday.dayType() == Holiday::NonWorkday) {
                return true;
            }
        }
    }
    return false;
}

QString HolidayRegion::defaultRegionCode(const QString &country, const QString &language)
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

    if (country.isEmpty()) {
        localeCountry = countryToCode(QLocale().country()).toLower();
    } else {
        localeCountry = country.toLower();
    }

    if (language.isEmpty()) {
        localeLanguage = languageToCode(QLocale().language()).toLower();
    } else {
        localeLanguage = language.toLower();
    }

    if (localeLanguage.split(QLatin1Char('_')).count() > 1) {
        localeLanguageCountry = localeLanguage.split(QLatin1Char('_')).at(1);
    }

    QStringList regionList = KHolidays::HolidayRegion::regionCodes();

    QString countryAndLanguageMatch, countryOnlyMatch, subdivisionAndLanguageMatch,
            subdivisionOnlyMatch, languageCountryAndLanguageMatch, languageCountryOnlyMatch,
            languageSubdivisionAndLanguageMatch, languageSubdivisionOnlyMatch;

    foreach (const QString &regionCode, regionList) {
        QString regionCountry = KHolidays::HolidayRegion::countryCode(regionCode).toLower();
        QString regionSubdivisionCountry;
        if (regionCountry.split(QLatin1Char('-')).count() > 1) {
            regionSubdivisionCountry = regionCountry.split(QLatin1Char('-')).at(0);
        }
        QString regionLanguage = KHolidays::HolidayRegion::languageCode(regionCode).toLower();

        if (regionCountry == localeCountry && regionLanguage == localeLanguage) {
            countryAndLanguageMatch = regionCode;
            break; // exact match so don't look further
        } else if (regionCountry == localeCountry) {
            if (countryOnlyMatch.isEmpty()) {
                countryOnlyMatch = regionCode;
            }
        } else if (!regionSubdivisionCountry.isEmpty() &&
                   regionSubdivisionCountry == localeCountry &&
                   regionLanguage == localeLanguage) {
            if (subdivisionAndLanguageMatch.isEmpty()) {
                subdivisionAndLanguageMatch = regionCode;
            }
        } else if (!regionSubdivisionCountry.isEmpty() && regionSubdivisionCountry == localeCountry) {
            if (subdivisionOnlyMatch.isEmpty()) {
                subdivisionOnlyMatch = regionCode;
            }
        } else if (!localeLanguageCountry.isEmpty() &&
                   regionCountry == localeLanguageCountry &&
                   regionLanguage == localeLanguage) {
            if (languageCountryAndLanguageMatch.isEmpty()) {
                languageCountryAndLanguageMatch = regionCode;
            }
        } else if (!localeLanguageCountry.isEmpty() && regionCountry == localeLanguageCountry) {
            if (languageCountryOnlyMatch.isEmpty()) {
                languageCountryOnlyMatch = regionCode;
            }
        } else if (!regionSubdivisionCountry.isEmpty() &&
                   !localeLanguageCountry.isEmpty() &&
                   regionSubdivisionCountry == localeLanguageCountry &&
                   regionLanguage == localeLanguage) {
            if (languageSubdivisionAndLanguageMatch.isEmpty()) {
                languageSubdivisionAndLanguageMatch = regionCode;
            }
        } else if (!regionSubdivisionCountry.isEmpty() &&
                   !localeLanguageCountry.isEmpty() &&
                   regionSubdivisionCountry == localeLanguageCountry) {
            if (languageSubdivisionOnlyMatch.isEmpty()) {
                languageSubdivisionOnlyMatch = regionCode;
            }
        }
    }

    QString defaultRegionCode;

    if (!countryAndLanguageMatch.isEmpty()) {
        defaultRegionCode = countryAndLanguageMatch;
    } else if (!countryOnlyMatch.isEmpty()) {
        defaultRegionCode = countryOnlyMatch;
    } else if (!subdivisionAndLanguageMatch.isEmpty()) {
        defaultRegionCode = subdivisionAndLanguageMatch;
    } else if (!subdivisionOnlyMatch.isEmpty()) {
        defaultRegionCode = subdivisionOnlyMatch;
    } else if (!languageCountryAndLanguageMatch.isEmpty()) {
        defaultRegionCode = languageCountryAndLanguageMatch;
    } else if (!languageCountryOnlyMatch.isEmpty()) {
        defaultRegionCode = languageCountryOnlyMatch;
    } else if (!languageSubdivisionAndLanguageMatch.isEmpty()) {
        defaultRegionCode = languageSubdivisionAndLanguageMatch;
    } else if (!languageSubdivisionOnlyMatch.isEmpty()) {
        defaultRegionCode = languageSubdivisionOnlyMatch;
    }

    return defaultRegionCode;
}
