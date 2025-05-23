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
#if KHOLIDAYS_ENABLE_DEPRECATED_SINCE(6, 15)
/*!
 * \namespace KHolidays::SunRiseSet
 * \inheaderfile KHolidays/SunRiseSet
 * \inmodule KHolidays
 *
 * \brief Methods for determining the sunrise and sunset times for a given date and Earth location.
 * \deprecated[6.15] Use SunEvents instead
 */
namespace SunRiseSet
{
/*!
  Compute the sunrise time (UTC) for a date and Earth location.

  \a date is any valid QDate.

  \a latitude is a floating point representing a valid latitude (-90.0, 90.0)

  \a longitude is a floating point representing a valid longitude (-180.0, 180.0)

  Returns the QTime of the sunrise in UTC.

  \note the latitude and longitude are truncated as needed to fit into their proper range.

*/
KHOLIDAYS_EXPORT KHOLIDAYS_DEPRECATED_VERSION(6, 15, "Use SunEvents instead") QTime utcSunrise(const QDate &date, double latitude, double longitude);

/*!
  Compute the sunset time (UTC) for a date and Earth location.

  \a date is any valid QDate.

  \a latitude is a floating point representing a valid latitude (-90.0, 90.0)

  \a longitude is a floating point representing a valid longitude (-180.0, 180.0)

  Returns the QTime of the sunset in UTC.

  \note the latitude and longitude are truncated as needed to fit into their proper range.
*/
KHOLIDAYS_EXPORT KHOLIDAYS_DEPRECATED_VERSION(6, 15, "Use SunEvents instead") QTime utcSunset(const QDate &date, double latitude, double longitude);

/*!
  Compute the civil dawn time (UTC) for a date and Earth location.

  \a date is any valid QDate.

  \a latitude is a floating point representing a valid latitude (-90.0, 90.0)

  \a longitude is a floating point representing a valid longitude (-180.0, 180.0)

  \sa https://en.wikipedia.org/wiki/Twilight

  Returns the QTime of the sunrise in UTC.

  \note the latitude and longitude are truncated as needed to fit into their proper range.
  \since 5.77
*/
KHOLIDAYS_EXPORT KHOLIDAYS_DEPRECATED_VERSION(6, 15, "Use SunEvents instead") QTime utcDawn(const QDate &date, double latitude, double longitude);

/*!
  Compute the civil dawn time (UTC) for a date and Earth location.

  \a date is any valid QDate.

  \a latitude is a floating point representing a valid latitude (-90.0, 90.0)

  \a longitude is a floating point representing a valid longitude (-180.0, 180.0)

  \sa https://en.wikipedia.org/wiki/Twilight

  Returns the QTime of the sunset in UTC.

  \note the latitude and longitude are truncated as needed to fit into their proper range.
  \since 5.77
*/
KHOLIDAYS_EXPORT KHOLIDAYS_DEPRECATED_VERSION(6, 15, "Use SunEvents instead") QTime utcDusk(const QDate &date, double latitude, double longitude);

/*!
  Checks whether it is polar day on day \a date at \a latitude.

  That is, the sun stays above -0.83° relative to the horizon at all times.
  Both sunrise/sunset and dawn/dusk times will be invalid for such a day.

  \a latitude in degree (-90.0, 90.0)

  \sa isPolarNight(), isPolarTwilight()
  \sa https://en.wikipedia.org/wiki/Midnight_sun

  \since 5.97
*/
KHOLIDAYS_EXPORT KHOLIDAYS_DEPRECATED_VERSION(6, 15, "Use SunEvents instead") bool isPolarDay(const QDate &date, double latitude);

/*!
  Checks whether it is polar twilight on day \a date at \a latitude.
  That is, the sun rises at least above -6° relative the horizon during the day,
  but remains below -0.83° at all times. Sunrise/sunset times will be invalid
  for such a day, but dawn/dusk times will be available.

  \a latitude in degree (-90.0, 90.0)

  \sa isPolarDay(), isPolarNight()
  \sa https://en.wikipedia.org/wiki/Polar_night

  \since 5.97
*/
KHOLIDAYS_EXPORT KHOLIDAYS_DEPRECATED_VERSION(6, 15, "Use SunEvents instead") bool isPolarTwilight(const QDate &date, double latitude);

/*!
  Checks whether it is polar night on day \a date at \a latitude.
  That is, the sun stays below -6° relative to the horizon at all times.
  Both sunrise/sunset and dawn/dusk times will be invalid for such a day.

  \a latitude in degree (-90.0, 90.0)

  \sa isPolarDay(), isPolarTwilight()
  \sa https://en.wikipedia.org/wiki/Polar_night

  \since 5.97
*/
KHOLIDAYS_EXPORT KHOLIDAYS_DEPRECATED_VERSION(6, 15, "Use SunEvents instead") bool isPolarNight(const QDate &date, double latitude);
}
#endif

}

#endif
