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

#ifndef KHOLIDAYS_HOLIDAYREGION_H
#define KHOLIDAYS_HOLIDAYREGION_H

#include "kholidays_export.h"

#include <QtCore/QList>
#include <QtCore/QSharedDataPointer>
#include <QtCore/QString>

#include "holiday.h"

class QDate;
class QStringList;
class QFileInfo;

namespace KHolidays {

class KHOLIDAYS_EXPORT HolidayRegion
{
  public:
    /**
     * Creates a new Holiday Region object for a given standard Region Code.
     *
     * From 4.5 onwards this constructor requires the new Region Code not the
     * deprecated Location Code.  If a Location Code is provided the first
     * match will be created.
     *
     * @param regionCode The code for the Holiday Region.
     *                   If null or unknown, an empty instance will be created.
     */
    explicit HolidayRegion( const QString &regionCode = QString() );

    /**
     * Creates a new Holiday Region object from a given holiday file.
     * If file doesn't exist, an empty instance will be created.
     *
     * @param regionFile The code for the Holiday Region.
     */
    explicit HolidayRegion( const QFileInfo &regionFile );

    /**
     * Destroys the holidays object.
     */
    ~HolidayRegion();

    /**
     * @deprecated use regions() instead
     *
     *  Return a list of all available location codes which have a holiday definition.
     *
     *  One of these can then be passed to the constructor for a new HolidayRegion
     *  object.
     *
     * @see regions()
     */
    static QStringList locations();

    /**
     * @deprecated use regionCode() or countryCode() instead
     *
     * Returns the holiday location.
     *
     * The holiday location is a code representing the holiday region.
     *
     * @return region code, or null if the instance was constructed with
     *         an unknown region
     *
     * @see regionCode()
     * @see languageCode()
     */
    QString location() const;

    /**
     * @since 4.5
     *
     *  Return a list of all available Holiday Region codes.
     *
     *  One of these can then be passed to the constructor for a new HolidayRegion
     *  object, or to name() or language() to obtain the name and language of the region.
     *
     * @see name()
     * @see languageCode()
     */
    static QStringList regionCodes();

    /**
     * @since 4.6
     *
     * Return a reasonable default Holiday Region code
     *
     * If a required country/language is not provided then the current KDE
     * country/lanaguage is used.
     *
     * @param country The country to find a default Holiday Region for
     * @param language The lanaguage to find a default Holiday Region for
     * @return the full region code of the default file
     */
    static QString defaultRegionCode( const QString &country = QString(),
                                      const QString &language = QString() );

    /**
     * @since 4.5
     *
     * Returns the unique Holiday Region code.
     *
     * Clients should not infer any meaning from the format of the code.
     *
     * @return region code, or null if the instance was constructed with
     *         an unknown region
     */
    QString regionCode() const;

    /**
     * @since 4.5
     *
     * Return the ISO 3166 country code of the file
     *
     * May be either just a country code ("US" = USA) or may include a regional
     * identifier ("US-CA" = California).  Returns "XX" if not a country.
     *
     * See http://en.wikipedia.org/wiki/ISO_3166-2
     *
     * @return the full region code of the file
     */
    QString countryCode() const;

    /**
     * @since 4.5
     *
     * Return the ISO 3166 country code of a given Holiday Region
     *
     * May be either just a country code ("US" = USA) or may include a regional
     * identifier ("US-CA" = California).  Returns "XX" if not a country.
     *
     * See http://en.wikipedia.org/wiki/ISO_3166-2
     *
     * @param regionCode The code for the Holiday Region.
     * @return the full region code of the file
     */
    static QString countryCode( const QString &regionCode );

    /**
     * @since 4.5
     *
     * Return the ISO 639-1 language code of the file
     *
     * May be either just a language code ("en" = US English) or may include a country
     * identifier ("en_GB" = British English).
     *
     * @return the language code of the file
     */
    QString languageCode() const;

    /**
     * @since 4.5
     *
     * Return the ISO 639-1 language code of a given Holiday Region
     *
     * May be either just a language code ("en" = US English) or may include a country
     * identifier ("en_GB" = British English).
     *
     * @param regionCode The code for the Holiday Region.
     * @return the language code of the file
     */
    static QString languageCode( const QString &regionCode );

    /**
     * @since 4.5
     *
     * Return the name of the Holiday Region.
     * This may be a country, region, or type.
     *
     * @return the short name code of the file
     */
    QString name() const;

    /**
     * @since 4.5
     *
     * Return the name of a given Holiday Region
     *
     * @param regionCode The code for the Holiday Region.
     * @return the name of the Holiday Region
     */
    static QString name( const QString &regionCode );

    /**
     * @since 4.5
     *
     * Return the description of the Holiday Region if available
     *
     * @return the description of the Holiday Region
     */
    QString description() const;

    /**
     * @since 4.5
     *
     * Return the description of a given Holiday Region if available
     *
     * @return the description of the Holiday Region
     */
    static QString description( const QString &regionCode );

    /**
     * @since 4.6
     *
     * Returns the list of holidays that occur between @p startDate and @p endDate.
     */
    Holiday::List holidays( const QDate &startDate, const QDate &endDate, Holiday::MultidayMode multidayMode = Holiday::MultidayHolidaysAsMultipleEvents ) const;

    /**
     * @since 4.6
     *
     * Returns the list of holidays that occur on a @p date.
     */
    Holiday::List holidays( const QDate &date, Holiday::MultidayMode multidayMode = Holiday::MultidayHolidaysAsMultipleEvents ) const;

    /**
     * @since 4.6
     *
     * Returns the list of holidays that occur in a calendar year @p calendarYear.
     */
    Holiday::List holidays( int calendarYear, const QString &calendarType,
                            Holiday::MultidayMode multidayMode = Holiday::MultidayHolidaysAsMultipleEvents) const;

    /**
     * Checks whether there is any holiday defined for a @p date.
     */
    bool isHoliday( const QDate &date ) const;

    /**
     * Returns whether the instance contains any holiday data.
     */
    bool isValid() const;

    /**
     * @since 4.5
     *
     * Returns whether the Region Code is valid.
     */
    static bool isValid( const QString &regionCode );

  private:
    Q_DISABLE_COPY( HolidayRegion )

    class Private;
    Private *const d;
};

}

#endif // KHOLIDAYS_HOLIDAYREGION_H
