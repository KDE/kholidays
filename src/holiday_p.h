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

#ifndef KHOLIDAYS_HOLIDAY_P_H
#define KHOLIDAYS_HOLIDAY_P_H

#include "holiday.h"

#include <QtCore/QDateTime>
#include <QtCore/QFile>
#include <QtCore/QSharedData>

namespace KHolidays {

class HolidayPrivate : public QSharedData
{
  public:
    HolidayPrivate()
    {
    }

    HolidayPrivate( const HolidayPrivate &other ) : QSharedData( other )
    {
        mObservedDate = other.mObservedDate;
        mDuration = other.mDuration;
        mName = other.mName;
        mDescription = other.mDescription;
        mDayType = other.mDayType;
    }

    QDate mObservedDate;
    int mDuration;
    QString mName;
    QString mDescription;
    Holiday::DayType mDayType;
};

}

#endif // KHOLIDAYS_HOLIDAY_P_H
