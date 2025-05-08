/*
    This file is part of the kholidays library.

    Adapted from the Javascript found at https://www.esrl.noaa.gov/gmd/grad/solcalc
    which is in the public domain.

    SPDX-FileCopyrightText: 2012 Allen Winter <winter@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "sunriseset.h"
#include "sunevents.h"

#include <QTimeZone>

using namespace KHolidays;

#if KHOLIDAYS_BUILD_DEPRECATED_SINCE(6, 15)
using namespace SunRiseSet;

static QTime roundToMinute(const QTime &time)
{
    if (time.second() > 29) {
        return QTime(time.hour(), time.minute()).addSecs(60);
    } else {
        return QTime(time.hour(), time.minute());
    }
}

template <typename Event>
static QTime timeOfEvent(const QDate &date, double latitude, double longitude, Event event)
{
    const QDateTime referenceDateTime(date, QTime(12, 0), QTimeZone::utc());
    const SunEvents events(referenceDateTime, latitude, longitude);
    const QDateTime dateTime = event(&events);
    if (!dateTime.isValid()) {
        return QTime();
    } else {
        return roundToMinute(dateTime.toUTC().time());
    }
}

QTime KHolidays::SunRiseSet::utcSunrise(const QDate &date, double latitude, double longitude)
{
    return timeOfEvent(date, latitude, longitude, std::mem_fn(&SunEvents::sunrise));
}

QTime KHolidays::SunRiseSet::utcSunset(const QDate &date, double latitude, double longitude)
{
    return timeOfEvent(date, latitude, longitude, std::mem_fn(&SunEvents::sunset));
}

QTime SunRiseSet::utcDawn(const QDate &date, double latitude, double longitude)
{
    return timeOfEvent(date, latitude, longitude, std::mem_fn(&SunEvents::civilDawn));
}

QTime SunRiseSet::utcDusk(const QDate &date, double latitude, double longitude)
{
    return timeOfEvent(date, latitude, longitude, std::mem_fn(&SunEvents::civilDusk));
}

bool SunRiseSet::isPolarDay(const QDate &date, double latitude)
{
    return SunEvents(QDateTime(date, QTime(12, 0), QTimeZone::utc()), latitude, 0).isPolarDay();
}

bool SunRiseSet::isPolarTwilight(const QDate &date, double latitude)
{
    return SunEvents(QDateTime(date, QTime(12, 0), QTimeZone::utc()), latitude, 0).isPolarTwilight();
}

bool SunRiseSet::isPolarNight(const QDate &date, double latitude)
{
    return SunEvents(QDateTime(date, QTime(12, 0), QTimeZone::utc()), latitude, 0).isPolarNight();
}
#endif
