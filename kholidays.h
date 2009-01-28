/*
  This file is part of the kholidays library.

  Copyright (c) 2001 Cornelius Schumacher <schumacher@kde.org>
  Copyright (c) 2004 Allen Winter <winter@kde.org>
  Copyright (c) 2008 David Jarvie <djarvie@kde.org>

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
#ifndef KHOLIDAYS_HOLIDAYS_H
#define KHOLIDAYS_HOLIDAYS_H

#include "kholidays_export.h"

#include <QList>
#include <QString>
#include <QStringList>

class QDate;

namespace LibKHolidays {

struct KHoliday {
  QString text;
  QString shortText;
  int Category;
};

class KHOLIDAYS_EXPORT KHolidays
{
  public:
    /**
       Return a list of all available location codes which have a holiday definition.
       One of these can then be passed to the constructor for a new KHolidays
       object.
    */
    static QStringList locations();

    /**
       Constructor.
       @param location the code for the country or region. If null
              or unknown, an empty instance will be created.
     */
    explicit KHolidays( const QString &location = QString() );
    ~KHolidays();

    /**
      Returns the holiday location.
      This is a code representing the country or region.
      @return region code, or null if the instance was constructed with
              an unknown region
    */
    QString location() const;

    QList<KHoliday> getHolidays( const QDate &date ) const;

    /**
       Checks whether there is any holiday defined for a date.
     */
    bool isHoliday( const QDate &date ) const;

    /**
       Returns whether the instance contains any holiday data.
     */
    bool isValid() const;

    enum {
      WORKDAY,
      HOLIDAY
    };

  private:
    // Prohibit copying
    KHolidays( const KHolidays & );
    KHolidays &operator=( const KHolidays & );

    bool parseFile( const QDate &date ) const;

    QString mLocation;    // location string used to determine holidays file
    QString mHolidayFile; // full path of file containing holiday data, or null
    mutable int mYearLast;// save of the last year we have seen
};

}

#endif
