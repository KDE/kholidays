/*
    SPDX-FileCopyrightText: 2025 Vlad Zahorodnii <vlad.zahorodnii@kde.org>

    SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
*/

#ifndef KHOLIDAYS_SUNEVENTS_H
#define KHOLIDAYS_SUNEVENTS_H

#include "kholidays_export.h"

#include <QDateTime>
#include <QSharedDataPointer>

namespace KHolidays
{

class SunEventsData;

/*!
 * \class SunEvents
 * \inmodule KHolidays
 * \brief TODO
 *
 * TODO: Complete the docs
 *
 * The next example shows how to use the SunEvents to determine the date and time of sunrise and
 * sunset:
 *
 * \code
 * SunEvents sunEvents(QDateTime::currentDateTime(), latitude, longitude);
 *
 * qDebug() << "Sunrise at:" << sunEvents.sunrise();
 * qDebug() << "Sunset at:" << sunEvents.sunset();
 * \endcode
 *
 * \since 6.15
 */
class KHOLIDAYS_EXPORT SunEvents
{
public:
    /*!
     * Constructs the SunEvents with the specified \a dateTime, \a latitude and \a longitude.
     *
     * The \a latitude is specified in decimal degrees between -90 and 90 degrees inclusive. If the
     * given latitude is outside the valid range, it will be clamped to fit into the [-90, 90] range.
     *
     * The \a longitude is specified in decimal degrees between -180 and 180 degrees inclusive. If
     * the given longitude is outside the valid range, it will be clamped to fit into the [-180, 180] range.
     */
    SunEvents(const QDateTime &dateTime, double latitude, double longitude);

    /*!
     * Constructs a copy of the \a other sun events.
     */
    SunEvents(const SunEvents &other);

    /*!
     * Destroys the sun events.
     */
    ~SunEvents();

    /*!
     * Assigns \a other to these sun events and returns a reference to these sun events.
     */
    SunEvents &operator=(const SunEvents &other);

    /*!
     * The date and time of astronomical sunrise when the Sun is 18 degrees below the horizon. At
     * extreme latitudes, the Sun may not rise during certain days, in which case, this function will
     * return an invalid QDateTime.
     *
     * Astronomical dawn is that point in time at which the Sun starts lightening the sky. Prior to
     * this time, the sky is completely dark.
     */
    QDateTime astronomicalDawn() const;

    /*!
     * The date and time of astronomical sunrise when the Sun is 12 degrees below the horizon. At
     * extreme latitudes, the Sun may not rise during certain days, in which case, this function will
     * return an invalid QDateTime.
     *
     * Nautical dawn is that point in time at which the there is just enough of sunlight for objects
     * to be distinguishable.
     */
    QDateTime nauticalDawn() const;

    /*!
     * The date and time of astronomical sunrise when the Sun is 6 degrees below the horizon. At
     * extreme latitudes, the Sun may not rise during certain days, in which case, this function will
     * return an invalid QDateTime.
     *
     * Civil dawn is that point in time at which there is enough of light for most objects to be
     * seen and outdoor activities may begin.
     */
    QDateTime civilDawn() const;

    /*!
     * The date and time of astronomical sunrise when the Sun is 0.833 degrees below the horizon. At
     * extreme latitudes, the Sun may not rise during certain days, in which case, this function will
     * return an invalid QDateTime.
     */
    QDateTime sunrise() const;

    /*!
     * The date and time when the Sun is at its highest position in the sky.
     */
    QDateTime solarNoon() const;

    /*!
     * The date and time of astronomical sunset when the Sun is 0.833 degrees below the horizon. At
     * extreme latitudes, the Sun may not set during certain days, in which case, this function will
     * return an invalid QDateTime.
     */
    QDateTime sunset() const;

    /*!
     * The date and time of astronomical sunset when the Sun is 6 degrees below the horizon. At
     * extreme latitudes, the Sun may not set during certain days, in which case, this function will
     * return an invalid QDateTime.
     *
     * Civil dusk is that point in time at which the light starts to fade but no artificial light
     * is needed for outdoor activities. The sky is often colored red and orange at this time.
     */
    QDateTime civilDusk() const;

    /*!
     * The date and time of astronomical sunset when the Sun is 12 degrees below the horizon. At
     * extreme latitudes, the Sun may not set during certain days, in which case, this function will
     * return an invalid QDateTime.
     *
     * Nautical dusk is that point in time at which most stars become visible.
     */
    QDateTime nauticalDusk() const;

    /*!
     * The date and time of astronomical sunset when the Sun is 18 degrees below the horizon. At
     * extreme latitudes, the Sun may not set during certain days, in which case, this function will
     * return an invalid QDateTime.
     *
     * Astronomical dusk is that point in time at which the Sun no longer illuminates the sky.
     */
    QDateTime astronomicalDusk() const;

    /*!
     * Returns \c true if it is polar day; otherwise returns \c false.
     *
     * Polar day is a natural phenomenon when the Sun stays above -0.83° relative to the horizon
     * at all times. Both sunrise/sunset and dawn/dusk times will be invalid for such a day.
     *
     * \sa isPolarNight(), isPolarTwilight()
     */
    bool isPolarDay() const;

    /*!
     * Returns \c true if it is polar night; otherwise returns \c false.
     *
     * Polar night is a natural phenomenon when the Sun stays below -6° relative to the horizon
     * at all times. Both sunrise/sunset and dawn/dusk times will be invalid for such a day.
     *
     * \sa isPolarDay(), isPolarTwilight()
     */
    bool isPolarNight() const;

    /*!
     * Returns \c true if it is polar twilight; otherwise returns \c false.
     *
     * Polar twilight is a natural phenomenon when the Sun rises at least above -6° relative the
     * horizon during the day, but remains below -0.83° at all times. Sunrise/sunset times will be
     * invalid for such a day, but dawn/dusk times will be available.
     *
     * \sa isPolarDay(), isPolarNight()
     */
    bool isPolarTwilight() const;

private:
    QDateTime dateTimeByElevationAngle(double elevationAngle) const;
    QSharedDataPointer<SunEventsData> d;
};

}

#endif
