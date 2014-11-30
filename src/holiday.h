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

#ifndef KHOLIDAYS_HOLIDAY_H
#define KHOLIDAYS_HOLIDAY_H

#include "kholidays_export.h"

#include <QtCore/QList>
#include <QtCore/QSharedDataPointer>

class QDate;
class QString;

namespace KHolidays {

class HolidayPrivate;
class HolidayRegion;

class KHOLIDAYS_EXPORT Holiday
{
  friend class HolidayRegion;
  friend class HolidayParserDriverPlan;
  friend class HolidayParserDriverPlanOld;

  public:
    /**
     * A list of holiday descriptions.
     */
    typedef QList<Holiday> List;

    /**
     * Describes the date type of the holiday.
     */
    enum DayType {
      Workday,   ///< The holiday is a workday
      NonWorkday ///< The holiday is a real holiday
    };

    /**
     * Creates an empty holiday.
     */
    Holiday();

    /**
     * Creates a holiday from an @p other holiday.
     */
    Holiday( const Holiday &other );

    /**
     * Destroys the holiday object.
     */
    ~Holiday();

    /**
     *
     */
    Holiday &operator=( const Holiday &other );

    /**
     *
     */
    bool operator<( const Holiday &rhs ) const;

    /**
     *
     */
    bool operator>( const Holiday &rhs ) const;

    /**
     * Returns the observed date of the holiday.
     */
    QDate date() const;

    /**
     * @since 4.6
     *
     * Returns the observed start date of the holiday.
     */
    QDate observedStartDate() const;

    /**
     * @since 4.6
     *
     * Returns the observed end date of the holiday.
     */
    QDate observedEndDate() const;

    /**
     * @since 4.6
     *
     * Returns the duration of the holiday in days.
     */
    int duration() const;

    /**
     * @since 5.0
     *
     * Returns the name of the Holiday.
     *
     * @return the name of the Holiday
     */
    QString name() const;

    /**
     * @since 5.0
     *
     * Returns the description of the Holiday if available
     *
     * @return the description of the Holiday
     */
    QString description() const;

    /**
     * Returns the day type of the holiday.
     */
    DayType dayType() const;

  private:
    QSharedDataPointer<HolidayPrivate> d;
};

}

#endif // KHOLIDAYS_HOLIDAY_H
