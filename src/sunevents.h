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
 * \class KHolidays::SunEvents
 * \inheaderfile KHolidays/SunEvents
 * \inmodule KHolidays
 * \brief The SunEvents type provides dates for solar events, for example sunset or sunrise.
 *
 * The SunEvents type allows you to find dates for solar events at the specified location and date,
 * for example sunset or sunrise. It can also be used to determine whether midnight sun or polar
 * night can be observed for the given time and location.
 *
 * The following example shows how to use the SunEvents type to determine sunrise and sunset
 * times in Kyiv:
 *
 * \code
 * const SunEvents sunEvents(QDateTime::currentDateTime(), 50.45, 30.52);
 * qDebug() << "Sunrise at:" << sunEvents.sunrise().toUTC();
 * qDebug() << "Sunset at:" << sunEvents.sunset().toUTC();
 * \endcode
 *
 * \note Due to various approximations, the provided event times are not suitable for the scientific
 * purposes. However, they are good enough for other purposes where accuracy is not critical, for
 * example adjusting the screen color temperature depending on the elevation of the sun.
 *
 * \since 6.15
 */
class KHOLIDAYS_EXPORT SunEvents
{
public:
    /*!
     * Constructs the SunEvents with the specified \a dateTime, \a latitude, and \a longitude.
     *
     * The \a dateTime is used to find the closest solar noon. The times of solar events are provided
     * relative to the closest solar noon.
     *
     * The \a latitude is specified in decimal degrees between -90° and 90° inclusive. If the
     * given latitude is outside the valid range, it will be clamped to fit into the [-90, 90] range.
     *
     * The \a longitude is specified in decimal degrees between -180° and 180° inclusive. If
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
     * The date and time of astronomical sunrise when the sun is 18° below the horizon. At
     * extreme latitudes, the sun may not rise during certain days, in which case, this function will
     * return an invalid QDateTime.
     *
     * Astronomical dawn is that point in time at which the sun starts lightening the sky. Prior to
     * this time, the sky is completely dark.
     *
     * \sa astronomicalDusk()
     */
    QDateTime astronomicalDawn() const;

    /*!
     * The date and time of astronomical sunrise when the sun is 12° below the horizon. At
     * extreme latitudes, the sun may not rise during certain days, in which case, this function will
     * return an invalid QDateTime.
     *
     * Nautical dawn is that point in time at which the there is just enough of sunlight for objects
     * to be distinguishable.
     *
     * \sa nauticalDusk()
     */
    QDateTime nauticalDawn() const;

    /*!
     * The date and time of astronomical sunrise when the sun is 6° below the horizon. At
     * extreme latitudes, the sun may not rise during certain days, in which case, this function will
     * return an invalid QDateTime.
     *
     * Civil dawn is that point in time at which there is enough of light for most objects to be
     * seen and outdoor activities may begin.
     *
     * \sa civilDusk()
     */
    QDateTime civilDawn() const;

    /*!
     * The date and time of astronomical sunrise when the sun is 0.833° below the horizon. At
     * extreme latitudes, the sun may not rise during certain days, in which case, this function will
     * return an invalid QDateTime.
     *
     * \sa sunset()
     */
    QDateTime sunrise() const;

    /*!
     * The date and time when the sun is at its highest position in the sky. The provided date
     * and time is always valid.
     */
    QDateTime solarNoon() const;

    /*!
     * The date and time of astronomical sunset when the sun is 0.833° below the horizon. At
     * extreme latitudes, the sun may not set during certain days, in which case, this function will
     * return an invalid QDateTime.
     *
     * \sa sunrise()
     */
    QDateTime sunset() const;

    /*!
     * The date and time of astronomical sunset when the sun is 6° below the horizon. At
     * extreme latitudes, the sun may not set during certain days, in which case, this function will
     * return an invalid QDateTime.
     *
     * Civil dusk is that point in time at which the light starts to fade but no artificial light
     * is needed for outdoor activities. The sky is often colored red and orange at this time.
     *
     * \sa civilDawn()
     */
    QDateTime civilDusk() const;

    /*!
     * The date and time of astronomical sunset when the sun is 12° below the horizon. At
     * extreme latitudes, the sun may not set during certain days, in which case, this function will
     * return an invalid QDateTime.
     *
     * Nautical dusk is that point in time at which most stars become visible.
     *
     * \sa nauticalDawn()
     */
    QDateTime nauticalDusk() const;

    /*!
     * The date and time of astronomical sunset when the sun is 18° below the horizon. At
     * extreme latitudes, the sun may not set during certain days, in which case, this function will
     * return an invalid QDateTime.
     *
     * Astronomical dusk is that point in time at which the sun no longer illuminates the sky.
     *
     * \sa astronomicalDawn()
     */
    QDateTime astronomicalDusk() const;

    /*!
     * Returns \c true if it is polar day, also known as midnight sun; otherwise returns \c false.
     *
     * Polar day is a natural phenomenon when the sun stays above -0.83° relative to the horizon
     * at all times. Both sunrise/sunset and dawn/dusk times will be invalid for such a day.
     *
     * \sa isPolarNight(), isPolarTwilight()
     */
    bool isPolarDay() const;

    /*!
     * Returns \c true if it is polar night; otherwise returns \c false.
     *
     * Polar night is a natural phenomenon when the sun stays below -6° relative to the horizon
     * at all times. Both sunrise/sunset and dawn/dusk times will be invalid for such a day.
     *
     * \sa isPolarDay(), isPolarTwilight()
     */
    bool isPolarNight() const;

    /*!
     * Returns \c true if it is polar twilight; otherwise returns \c false.
     *
     * Polar twilight is a natural phenomenon when the sun rises at least above -6° relative the
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
