/*
    This file is part of the kholidays library.

    SPDX-FileCopyrightText: 2012 Allen Winter <winter@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef KHOLIDAYS_SUNRISESET_H
#define KHOLIDAYS_SUNRISESET_H

#include "kholidays_export.h"
#include <QTime>

namespace KHolidays
{
/**
  @brief
  Methods for determining the sunrise and sunset times for a given date and Earth location.
*/

namespace SunRiseSet
{
/**
  Compute the sunrise time (UTC) for a date and Earth location.
  @param date is any valid QDate.
  @param latitude is a floating point representing a valid latitude (-90.0, 90.0)
  @param longitude is a floating point representing a valid longitude (-180.0, 180.0)
  @return the QTime of the sunrise in UTC.

  @note the latitude and longitude are truncated as needed to fit into their proper range.

*/
KHOLIDAYS_EXPORT QTime utcSunrise(const QDate &date, double latitude, double longitude);

/**
  Compute the sunset time (UTC) for a date and Earth location.
  @param date is any valid QDate.
  @param latitude is a floating point representing a valid latitude (-90.0, 90.0)
  @param longitude is a floating point representing a valid longitude (-180.0, 180.0)
  @return the QTime of the sunset in UTC.

  @note the latitude and longitude are truncated as needed to fit into their proper range.
*/
KHOLIDAYS_EXPORT QTime utcSunset(const QDate &date, double latitude, double longitude);

/**
  Compute the civil dawn time (UTC) for a date and Earth location.
  @param date is any valid QDate.
  @param latitude is a floating point representing a valid latitude (-90.0, 90.0)
  @param longitude is a floating point representing a valid longitude (-180.0, 180.0)
  @see https://en.wikipedia.org/wiki/Twilight
  @return the QTime of the sunrise in UTC.

  @note the latitude and longitude are truncated as needed to fit into their proper range.
  @since 5.77
*/
KHOLIDAYS_EXPORT QTime utcDawn(const QDate &date, double latitude, double longitude);

/**
  Compute the civil dawn time (UTC) for a date and Earth location.
  @param date is any valid QDate.
  @param latitude is a floating point representing a valid latitude (-90.0, 90.0)
  @param longitude is a floating point representing a valid longitude (-180.0, 180.0)
  @see https://en.wikipedia.org/wiki/Twilight
  @return the QTime of the sunset in UTC.

  @note the latitude and longitude are truncated as needed to fit into their proper range.
  @since 5.77
*/
KHOLIDAYS_EXPORT QTime utcDusk(const QDate &date, double latitude, double longitude);

}

}

#endif
