/*
  This file is part of the kholidays library.

  Copyright (c) 2012 Allen Winter <winter@kde.org>

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Library General Public
  License as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Library General Public License for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; see the file COPYING.LIB.  If not, write to
  the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
  Boston, MA 02110-1301, USA.
*/

#ifndef KHOLIDAYS_SUNRISESET_H
#define KHOLIDAYS_SUNRISESET_H

#include "kholidays_export.h"
#include <QTime>

namespace KHolidays {

/**
  @brief
  Methods for determining the sunrise and sunset times for a given date and Earth location.
*/

namespace SunRiseSet {

  /**
    Compute the sunrise time (UTC) for a date and Earth location.
    @param date is any valid QDate.
    @param latitude is a floating point representing a valid latitude (-90.0, 90.0)
    @param longitude is a floating point representing a valid longitude (-180.0, 180.0)
    @return the QTime of the sunrise in UTC.

    @note the latitude and longitude are truncated as needed to fit into their proper range.

  */
  KHOLIDAYS_EXPORT QTime utcSunrise( const QDate &date, double latitude, double longitude );

  /**
    Compute the sunset time (UTC) for a date and Earth location.
    @param date is any valid QDate.
    @param latitude is a floating point representing a valid latitude (-90.0, 90.0)
    @param longitude is a floating point representing a valid longitude (-180.0, 180.0)
    @return the QTime of the sunset in UTC.

    @note the latitude and longitude are truncated as needed to fit into their proper range.
  */
  KHOLIDAYS_EXPORT QTime utcSunset( const QDate &date, double latitude, double longitude );

}

}

#endif
