/*
  This file is part of the kholidays library.

  Copyright (c) 2001 Cornelius Schumacher <schumacher@kde.org>
  Copyright (c) 2004 Allen Winter <winter@kde.org>

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
       Return a list of all available locations which have a holiday definition.
       One of these can then be passed to the constructor for a new KHolidays
       object.
    */
    static QStringList locations();

    KHolidays( const QString &location );
    ~KHolidays();

    /**
      Returns the holiday location.
    */
    QString location() const;

    QList<KHoliday> getHolidays( const QDate &qd );

    enum {
      WORKDAY,
      HOLIDAY
    };

  private:
    bool parseFile( const QDate &qd );

    QString mLocation;    // location string used to determine holidays file
    QString mHolidayFile; // name of file containing holiday data
    int mYearLast;        // save off the last year we have seen
};

}

#endif
