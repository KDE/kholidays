/*
    This file is part of the kholidays library.

    SPDX-FileCopyrightText: 2001 Cornelius Schumacher <schumacher@kde.org>
    SPDX-FileCopyrightText: 2004 Allen Winter <winter@kde.org>
    SPDX-FileCopyrightText: 2008 David Jarvie <djarvie@kde.org>
    SPDX-FileCopyrightText: 2010 John Layt <john@layt.net>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef KHOLIDAYS_HOLIDAYREGION_H
#define KHOLIDAYS_HOLIDAYREGION_H

#include "kholidays_export.h"

#include <QSharedDataPointer>
#include <QString>
#include <QStringList>

#include "holiday.h"

class QDate;
class QFileInfo;

namespace KHolidays
{
class HolidayRegionPrivate;

/*!
 * \class KHolidays::HolidayRegion
 * \inheaderfile KHolidays/HolidayRegion
 * \inmodule KHolidays
 *
 * \brief Represents a holiday region.
 */
class KHOLIDAYS_EXPORT HolidayRegion
{
public:
    /*!
     * Creates a new Holiday Region object for a given standard Region Code.
     *
     * \a regionCode The code for the Holiday Region.
     *                   If null or unknown, an empty instance will be created.
     */
    explicit HolidayRegion(const QString &regionCode = QString());

    /*!
     * Creates a new Holiday Region object from a given holiday file.
     * If file doesn't exist, an empty instance will be created.
     *
     * \a regionFile The code for the Holiday Region.
     */
    explicit HolidayRegion(const QFileInfo &regionFile);

    HolidayRegion(const HolidayRegion &);
    HolidayRegion(HolidayRegion &&);

    ~HolidayRegion();

    HolidayRegion &operator=(const HolidayRegion &);
    HolidayRegion &operator=(HolidayRegion &&);

    /*!
     * \since 4.5
     *
     * Return a list of all available Holiday Region codes.
     *
     * One of these can then be passed to the constructor for a new HolidayRegion
     * object, or to name() or language() to obtain the name and language of the region.
     *
     * \sa name()
     * \sa languageCode()
     */
    static QStringList regionCodes();

    /*!
     * \since 4.6
     *
     * Return a reasonable default Holiday Region code
     *
     * If a required country/language is not provided then the current KDE
     * country/language is used.
     *
     * \a country The country or region to find a default Holiday Region for.
     *   This can be either an ISO 3166-1 or ISO 3166-2 code.
     *
     * \a language The language to find a default Holiday Region for
     *
     * Returns the full region code of the default file
     *
     * \warning This methods is expensive as it involves parsing all holiday definition files.
     */
    static QString defaultRegionCode(const QString &country = QString(), const QString &language = QString());

    /*!
     * \since 4.5
     *
     * Returns the unique Holiday Region code.
     *
     * Clients should not infer any meaning from the format of the code.
     *
     * Returns region code, or null if the instance was constructed with
     *         an unknown region
     */
    QString regionCode() const;

    /*!
     * \since 4.5
     *
     * Return the ISO 3166 country code of the file
     *
     * May be either just a country code ("US" = USA) or may include a regional
     * identifier ("US-CA" = California).  Returns "XX" if not a country.
     *
     * See https://en.wikipedia.org/wiki/ISO_3166-2
     */
    QString countryCode() const;

    /*!
     * \since 4.5
     *
     * Return the ISO 3166 country code of a given Holiday Region
     *
     * May be either just a country code ("US" = USA) or may include a regional
     * identifier ("US-CA" = California).  Returns "XX" if not a country.
     *
     * See https://en.wikipedia.org/wiki/ISO_3166-2
     *
     * \a regionCode The code for the Holiday Region.
     *
     * \warning This methods is expensive as it involves parsing the corresponding holiday
     *   definition file. Prefer HolidayRegion::countryCode().
     */
    static QString countryCode(const QString &regionCode);

    /*!
     * \since 4.5
     *
     * Return the ISO 639-1 language code of the file
     *
     * May be either just a language code ("en" = US English) or may include a country
     * identifier ("en_GB" = British English).
     */
    QString languageCode() const;

    /*!
     * \since 4.5
     *
     * Return the ISO 639-1 language code of a given Holiday Region
     *
     * May be either just a language code ("en" = US English) or may include a country
     * identifier ("en_GB" = British English).
     *
     * \a regionCode The code for the Holiday Region.
     *
     * \warning This methods is expensive as it involves parsing the corresponding holiday
     *   definition file. Prefer HolidayRegion::languageCode().
     */
    static QString languageCode(const QString &regionCode);

    /*!
     * \since 4.5
     *
     * Return the name of the Holiday Region.
     * This may be a country, region, or type.
     */
    QString name() const;

    /*!
     * \since 4.5
     *
     * Return the name of a given Holiday Region
     *
     * \a regionCode The code for the Holiday Region.
     */
    static QString name(const QString &regionCode);

    /*!
     * \since 4.5
     *
     * Return the description of the Holiday Region if available
     */
    QString description() const;

    /*!
     * \since 4.5
     *
     * Return the description of a given Holiday Region if available
     */
    static QString description(const QString &regionCode);

    /*!
     * \since 5.95
     *
     * Returns the list of holidays and astronomical season dates (equinoxes
     * and solstices) that occur between \a startDate and \a endDate.
     *
     */
    Holiday::List rawHolidaysWithAstroSeasons(const QDate &startDate, const QDate &endDate) const;

    /*!
     * \since 5.97
     *
     * Returns the list of holidays that occur between \a startDate and \a endDate.
     */
    Holiday::List rawHolidays(const QDate &startDate, const QDate &endDate) const;

    /*!
     * \since 5.95
     *
     * Returns the list of holidays and astronomical season dates (equinoxes
     * and solstices) that occur on a \a date.
     */
    Holiday::List rawHolidaysWithAstroSeasons(const QDate &date) const;

    /*!
     * \since 5.95
     *
     * Returns the list of holidays and astronomical season dates (equinoxes
     * and solstices) that occur in a Gregorian calendar year \a calendarYear.
     */
    Holiday::List rawHolidaysWithAstroSeasons(int calendarYear) const;

    /*!
     * \since 5.95
     *
     * Returns the list of holidays that occur between \a startDate and \a endDate and with \a category.
     */
    Holiday::List rawHolidays(const QDate &startDate, const QDate &endDate, const QString &category) const;

    /*!
     * Checks whether there is any holiday defined for a \a date.
     */
    bool isHoliday(const QDate &date) const;

    /*!
     * Returns whether the instance contains any holiday data.
     */
    bool isValid() const;

    /*!
     * \since 4.5
     *
     * Returns whether the Region Code is valid.
     */
    static bool isValid(const QString &regionCode);

private:
    QExplicitlySharedDataPointer<HolidayRegionPrivate> d;
};

}

#endif // KHOLIDAYS_HOLIDAYREGION_H
