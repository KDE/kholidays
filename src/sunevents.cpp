/*
    SPDX-FileCopyrightText: 2012 Allen Winter <winter@kde.org>
    SPDX-FileCopyrightText: 2025 Vlad Zahorodnii <vlad.zahorodnii@kde.org>

    SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
*/

#include "sunevents.h"
#include "sunevents_p.h"

namespace KHolidays
{

// Formulas are taken from https://gml.noaa.gov/grad/solcalc/calcdetails.html

static const double secondsPerDay = 86400.0;
static const double j2000 = 2451545.0;
static const double julianUnixEpoch = 2440587.5;
static const double julianYear = 365.25;
static const double julianCentury = julianYear * 100;

static const double astronomicalTwilightElevation = -18.0;
static const double nauticalTwilightElevation = -12.0;
static const double civilTwilightElevation = -6.0;
static const double sunriseOrSunsetElevation = -0.833;

static QDateTime julianDateToDateTime(double jd)
{
    return QDateTime::fromSecsSinceEpoch(std::round((jd - julianUnixEpoch) * secondsPerDay));
}

static double dateTimeToJulianDate(const QDateTime &dateTime)
{
    return dateTime.toSecsSinceEpoch() / secondsPerDay + julianUnixEpoch;
}

static double julianDateToJulianCenturies(double jd)
{
    return (jd - j2000) / julianCentury;
}

static double sunGeometricMeanLongitude(double jcent)
{
    return qDegreesToRadians(fmod(280.46646 + jcent * (36000.76983 + jcent * 0.0003032), 360));
}

static double sunGeometricMeanAnomaly(double jcent)
{
    return qDegreesToRadians(357.52911 + jcent * (35999.05029 - 0.0001537 * jcent));
}

static double earthOrbitEccentricity(double jcent)
{
    return 0.016708634 - jcent * (0.000042037 + 0.0000001267 * jcent);
}

static double equationOfCenter(double jcent)
{
    const double anomaly = sunGeometricMeanAnomaly(jcent);
    return qDegreesToRadians(std::sin(anomaly) * (1.914602 - jcent * (0.004817 + 0.000014 * jcent))
                             + std::sin(2 * anomaly) * (0.019993 - 0.000101 * jcent) + std::sin(3 * anomaly) * 0.000289);
}

static double sunTrueLongitude(double jcent)
{
    return sunGeometricMeanLongitude(jcent) + equationOfCenter(jcent);
}

static double sunApparentLongitude(double jcent)
{
    return qDegreesToRadians(qRadiansToDegrees(sunTrueLongitude(jcent)) - 0.00569 - 0.00478 * std::sin(qDegreesToRadians(125.04 - 1934.136 * jcent)));
}

static double obliquityCorrection(double jcent)
{
    const double meanEclipticObliquity = 23 + (26 + ((21.448 - jcent * (46.815 + jcent * (0.00059 - jcent * 0.001813)))) / 60) / 60;
    return qDegreesToRadians(meanEclipticObliquity + 0.00256 * std::cos(qDegreesToRadians(125.04 - 1934.136 * jcent)));
}

static double sunDeclination(double jcent)
{
    return std::asin(std::sin(obliquityCorrection(jcent)) * std::sin(sunApparentLongitude(jcent)));
}

static double sunHourAngle(double jcent, double elevation, double latitude)
{
    const double declination = sunDeclination(jcent);
    const double angle = std::acos(std::cos(elevation) / (std::cos(latitude) * std::cos(declination)) - std::tan(latitude) * std::tan(declination));
    return std::copysign(angle, -elevation);
}

static double equationOfTime(double jcent)
{
    const double eccentricity = earthOrbitEccentricity(jcent);
    const double meanLongitude = sunGeometricMeanLongitude(jcent);
    const double meanAnomaly = sunGeometricMeanAnomaly(jcent);
    const double varY = std::pow(std::tan(obliquityCorrection(jcent) / 2), 2);

    return varY * std::sin(2 * meanLongitude)
        - 2 * eccentricity * std::sin(meanAnomaly)
        + 4 * eccentricity * varY * std::sin(meanAnomaly) * std::cos(2 * meanLongitude)
        - 0.5 * varY * varY * std::sin(4 * meanLongitude)
        - 1.25 * eccentricity * eccentricity * std::sin(2 * meanAnomaly);
}

static double timeOfNoon(double jd, double longitude)
{
    const double offset = longitude / (2 * M_PI);
    double noon = std::round(jd + offset) - offset;
    noon -= equationOfTime(julianDateToJulianCenturies(noon)) / (2 * M_PI);
    return noon;
}

SunEvents::SunEvents(const QDateTime &dateTime, double latitude, double longitude)
    : d(new SunEventsData)
{
    d->latitude = qDegreesToRadians(std::clamp(latitude, -90.0, 90.0));
    d->longitude = qDegreesToRadians(std::clamp(longitude, -180.0, 180.0));

    d->solarNoon = timeOfNoon(dateTimeToJulianDate(dateTime), d->longitude);
}

SunEvents::SunEvents(const SunEvents &other)
    : d(other.d)
{
}

SunEvents::~SunEvents()
{
}

SunEvents &SunEvents::operator=(const SunEvents &other)
{
    d = other.d;
    return *this;
}

bool SunEvents::isPolarDay() const
{
    const double solarDeclination = sunDeclination(julianDateToJulianCenturies(d->solarNoon));
    const double maxSolarZenithAngle = 180.0 - qRadiansToDegrees(std::abs(d->latitude + solarDeclination));

    return maxSolarZenithAngle <= 90.0 - sunriseOrSunsetElevation;
}

bool SunEvents::isPolarNight() const
{
    const double solarDeclination = sunDeclination(julianDateToJulianCenturies(d->solarNoon));
    const double minSolarZenithAngle = qRadiansToDegrees(std::abs(d->latitude - solarDeclination));

    return minSolarZenithAngle > 90.0 - civilTwilightElevation;
}

bool SunEvents::isPolarTwilight() const
{
    const double solarDeclication = sunDeclination(julianDateToJulianCenturies(d->solarNoon));
    const double minSolarZenithAngle = qRadiansToDegrees(std::abs(d->latitude - solarDeclication));

    return minSolarZenithAngle > 90.0 - sunriseOrSunsetElevation && minSolarZenithAngle <= 90.0 - civilTwilightElevation;
}

QDateTime SunEvents::dateTimeByElevationAngle(double elevationAngle) const
{
    const double hourAngle = sunHourAngle(julianDateToJulianCenturies(d->solarNoon), qDegreesToRadians(elevationAngle), d->latitude) / (2 * M_PI);
    if (std::isnan(hourAngle)) {
        return QDateTime();
    }

    // With extreme hour angles, the timings are less predictable.
    const double absoluteHourAngle = std::abs(hourAngle);
    if (absoluteHourAngle < 0.05 || absoluteHourAngle > 0.45) {
        return QDateTime();
    }

    return julianDateToDateTime(d->solarNoon + hourAngle);
}

QDateTime SunEvents::astronomicalDawn() const
{
    return dateTimeByElevationAngle(90 - astronomicalTwilightElevation);
}

QDateTime SunEvents::nauticalDawn() const
{
    return dateTimeByElevationAngle(90 - nauticalTwilightElevation);
}

QDateTime SunEvents::civilDawn() const
{
    return dateTimeByElevationAngle(90 - civilTwilightElevation);
}

QDateTime SunEvents::sunrise() const
{
    return dateTimeByElevationAngle(90 - sunriseOrSunsetElevation);
}

QDateTime SunEvents::solarNoon() const
{
    return julianDateToDateTime(d->solarNoon);
}

QDateTime SunEvents::sunset() const
{
    return dateTimeByElevationAngle(-90 + sunriseOrSunsetElevation);
}

QDateTime SunEvents::civilDusk() const
{
    return dateTimeByElevationAngle(-90 + civilTwilightElevation);
}

QDateTime SunEvents::nauticalDusk() const
{
    return dateTimeByElevationAngle(-90 + nauticalTwilightElevation);
}

QDateTime SunEvents::astronomicalDusk() const
{
    return dateTimeByElevationAngle(-90 + astronomicalTwilightElevation);
}

}
