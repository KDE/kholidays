/*
    This file is part of the kholidays library.

    SPDX-FileCopyrightText: 2001 Cornelius Schumacher <schumacher@kde.org>
    SPDX-FileCopyrightText: 2004 Allen Winter <winter@kde.org>
    SPDX-FileCopyrightText: 2008 David Jarvie <djarvie@kde.org>
    SPDX-FileCopyrightText: 2010 John Layt <john@layt.net>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef KHOLIDAYS_HOLIDAY_H
#define KHOLIDAYS_HOLIDAY_H

#include "kholidays_export.h"

#include <QList>
#include <QSharedDataPointer>

class QDate;
class QString;

/*!
 * \namespace KHolidays
 * \inmodule KHolidays
 */
namespace KHolidays
{
class HolidayPrivate;
class HolidayRegion;

/*!
 * \class KHolidays::Holiday
 * \inheaderfile KHolidays/Holiday
 * \inmodule KHolidays
 *
 * \brief Represents a holiday event.
 */
class KHOLIDAYS_EXPORT Holiday
{
    friend class HolidayRegion;
    friend class HolidayParserDriver;
    friend class HolidayParserDriverPlan;
    friend class HolidayParserDriverPlanOld;

public:
    /*!
     * A list of holiday descriptions.
     */
    typedef QList<Holiday> List;

    /*!
     * Describes the date type of the holiday.
     * If any of the holidays on a date are non-workdays types, then the entire day is non-working.
     *
     * \value Workday The holiday is a workday
     * \value NonWorkday The holiday is a real holiday
     */
    enum DayType {
        Workday,
        NonWorkday,
    };

    /*!
     * Creates an empty holiday.
     */
    Holiday();

    /*!
     * Creates a holiday from an \a other holiday.
     */
    Holiday(const Holiday &other);

    ~Holiday();

    Holiday &operator=(const Holiday &other);

    /*!
     *
     */
    bool operator<(const Holiday &rhs) const;

    /*!
     *
     */
    bool operator>(const Holiday &rhs) const;

    /*!
     * \since 4.6
     *
     * Returns the observed start date of the holiday.
     */
    QDate observedStartDate() const;

    /*!
     * \since 4.6
     *
     * Returns the observed end date of the holiday.
     */
    QDate observedEndDate() const;

    /*!
     * \since 4.6
     *
     * Returns the duration of the holiday in days.
     */
    int duration() const;

    /*!
     * \since 5.0
     *
     * Returns the name of the Holiday.
     */
    QString name() const;

    /*!
     * \since 5.0
     *
     * Returns the description of the Holiday if available
     */
    QString description() const;

    /*!
     * Returns the day type of the holiday.
     */
    DayType dayType() const;

    /*!
     * \since 5.8
     *
     * Returns a QStringList of categories for the Holiday.
     *
     * If the Holiday has no categories then an empty list is returned.
     */
    QStringList categoryList() const;

private:
    QSharedDataPointer<HolidayPrivate> d;
};

}

Q_DECLARE_TYPEINFO(KHolidays::Holiday, Q_RELOCATABLE_TYPE);

#endif // KHOLIDAYS_HOLIDAY_H
