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

namespace KHolidays {

class KHOLIDAYS_EXPORT HolidayRegion
{
  public:
    /**
     * Creates a new holidays object.
     *
     * @param location The code for the country or region.
     *                 If null or unknown, an empty instance will be created.
     */
    explicit HolidayRegion( const QString &location = QString() );

    /**
     * Destroys the holidays object.
     */
    ~HolidayRegion();

    /**
     *  Return a list of all available location codes which have a holiday definition.
     *
     *  One of these can then be passed to the constructor for a new HolidayRegion
     *  object.
     */
    static QStringList locations();

    /**
     * Returns the holiday location.
     *
     * The holiday location is a code representing the country or region.
     *
     * @return region code, or null if the instance was constructed with
     *         an unknown region
     */
    QString location() const;

    /**
     * Returns the list of holidays that occur on a @p date.
     */
    Holiday::List holidays( const QDate &startDate, const QDate &endDate ) const;

    /**
     * Returns the list of holidays that occur on a @p date.
     */
    Holiday::List holidays( const QDate &date ) const;

    /**
     * Returns the list of holidays that occur in a calendar year @p calendarYear.
     */
    Holiday::List holidays( int calendarYear, const QString &calendarType ) const;

    /**
     * Checks whether there is any holiday defined for a @p date.
     */
    bool isHoliday( const QDate &date ) const;

    /**
     * Returns whether the instance contains any holiday data.
     */
    bool isValid() const;

  private:
    Q_DISABLE_COPY( HolidayRegion )

    class Private;
    Private *const d;
};

}

#endif // KHOLIDAYS_HOLIDAYREGION_H
