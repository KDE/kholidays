/*
    This file is part of the kholidays library.

    SPDX-FileCopyrightText: 2015 Martin Klapetek <mklapetek@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kholidaysdeclarativeplugin.h"
#include "holidayregionsmodel.h"

#include <KHolidays/LunarPhase>
#include <KHolidays/SunEvents>

#include <QCoreApplication>
#include <QQmlEngine>

/*!
 * \qmltype Lunar
 * \inqmlmodule org.kde.kholidays
 */

/*!
 * \qmltype SunRiseSet
 * \inqmlmodule org.kde.kholidays
 */

// convert to/from QDateTime for JS
class LunarPhaseWrapper
{
    Q_GADGET
public:
    /*!
     * \qmlmethod enumeration Lunar::phaseAtDate(datetime date)
     *
     * \sa LunarPhase::Phase
     */
    static Q_INVOKABLE KHolidays::LunarPhase::Phase phaseAtDate(const QDateTime &date)
    {
        return KHolidays::LunarPhase::phaseAtDate(date.date());
    }

    /*!
     * \qmlmethod string Lunar::phaseNameAtDate(datetime date)
     */
    static Q_INVOKABLE QString phaseNameAtDate(const QDateTime &date)
    {
        return KHolidays::LunarPhase::phaseNameAtDate(date.date());
    }

    /*!
     * \qmlmethod string Lunar::phaseName(enumeration phase)
     */
    static Q_INVOKABLE QString phaseName(KHolidays::LunarPhase::Phase phase)
    {
        return KHolidays::LunarPhase::phaseName(phase);
    }
};

class SunRiseSetWrapper
{
    Q_GADGET
public:
    /*!
     * \qmlmethod datetime SunRiseSet::utcSunrise(datetime date, real latitude, real longitude)
     */
    static Q_INVOKABLE QDateTime utcSunrise(const QDateTime &date, double latitude, double longitude)
    {
        return KHolidays::SunEvents(date, latitude, longitude).sunrise().toUTC();
    }

    /*!
     * \qmlmethod datetime SunRiseSet::utcSunset(datetime date, real latitude, real longitude)
     */
    static Q_INVOKABLE QDateTime utcSunset(const QDateTime &date, double latitude, double longitude)
    {
        return KHolidays::SunEvents(date, latitude, longitude).sunset().toUTC();
    }

    /*!
     * \qmlmethod datetime SunRiseSet::utcDawn(datetime date, real latitude, real longitude)
     */
    static Q_INVOKABLE QDateTime utcDawn(const QDateTime &date, double latitude, double longitude)
    {
        return KHolidays::SunEvents(date, latitude, longitude).civilDawn().toUTC();
    }

    /*!
     * \qmlmethod datetime SunRiseSet::utcDusk(datetime date, real latitude, real longitude)
     */
    static Q_INVOKABLE QDateTime utcDusk(const QDateTime &date, double latitude, double longitude)
    {
        return KHolidays::SunEvents(date, latitude, longitude).civilDusk().toUTC();
    }

    /*!
     * \qmlmethod bool SunRiseSet::isPolarDay(datetime date, real latitude)
     */
    static Q_INVOKABLE bool isPolarDay(const QDateTime &date, double latitude)
    {
        return KHolidays::SunEvents(date, latitude, 0).isPolarDay();
    }

    /*!
     * \qmlmethod bool SunRiseSet::isPolarTwilight(datetime date, real latitude)
     */
    static Q_INVOKABLE bool isPolarTwilight(const QDateTime &date, double latitude)
    {
        return KHolidays::SunEvents(date, latitude, 0).isPolarTwilight();
    }

    /*!
     * \qmlmethod bool SunRiseSet::isPolarNight(datetime date, real latitude)
     */
    static Q_INVOKABLE bool isPolarNight(const QDateTime &date, double latitude)
    {
        return KHolidays::SunEvents(date, latitude, 0).isPolarNight();
    }
};

void KHolidaysDeclarativePlugin::registerTypes(const char *uri)
{
    qmlRegisterType<HolidayRegionsDeclarativeModel>(uri, 1, 0, "HolidayRegionsModel");
    qRegisterMetaType<KHolidays::LunarPhase::Phase>();
    qmlRegisterUncreatableMetaObject(KHolidays::LunarPhase::staticMetaObject, uri, 1, 0, "LunarPhase", {});

    // HACK qmlplugindump chokes on gadget singletons, to the point of breaking ecm_find_qmlmodule()
    if (QCoreApplication::applicationName() != QLatin1String("qmlplugindump")) {
        qmlRegisterSingletonType(uri, 1, 0, "Lunar", [](QQmlEngine *engine, QJSEngine *) -> QJSValue {
            return engine->toScriptValue(LunarPhaseWrapper());
        });
        qmlRegisterSingletonType(uri, 1, 0, "SunRiseSet", [](QQmlEngine *engine, QJSEngine *) -> QJSValue {
            return engine->toScriptValue(SunRiseSetWrapper());
        });
    }
}

#include "kholidaysdeclarativeplugin.moc"
#include "moc_kholidaysdeclarativeplugin.cpp"
