/*
    This file is part of the kholidays library.

    SPDX-FileCopyrightText: 2015 Martin Klapetek <mklapetek@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kholidaysdeclarativeplugin.h"
#include "holidayregionsmodel.h"

#include <KHolidays/LunarPhase>
#include <KHolidays/SunRiseSet>

#include <QCoreApplication>
#include <QQmlEngine>

// convert to/from QDateTime for JS
class LunarPhaseWrapper
{
    Q_GADGET
public:
    static Q_INVOKABLE KHolidays::LunarPhase::Phase phaseAtDate(const QDateTime &date)
    {
        return KHolidays::LunarPhase::phaseAtDate(date.date());
    }
    static Q_INVOKABLE QString phaseNameAtDate(const QDateTime &date)
    {
        return KHolidays::LunarPhase::phaseNameAtDate(date.date());
    }
    static Q_INVOKABLE QString phaseName(KHolidays::LunarPhase::Phase phase)
    {
        return KHolidays::LunarPhase::phaseName(phase);
    }
};

class SunRiseSetWrapper
{
    Q_GADGET
public:
    static Q_INVOKABLE QDateTime utcSunrise(const QDateTime &date, double latitude, double longitude)
    {
        return QDateTime(date.date(), KHolidays::SunRiseSet::utcSunrise(date.date(), latitude, longitude), Qt::UTC);
    }
    static Q_INVOKABLE QDateTime utcSunset(const QDateTime &date, double latitude, double longitude)
    {
        return QDateTime(date.date(), KHolidays::SunRiseSet::utcSunset(date.date(), latitude, longitude), Qt::UTC);
    }
    static Q_INVOKABLE QDateTime utcDawn(const QDateTime &date, double latitude, double longitude)
    {
        return QDateTime(date.date(), KHolidays::SunRiseSet::utcDawn(date.date(), latitude, longitude), Qt::UTC);
    }
    static Q_INVOKABLE QDateTime utcDusk(const QDateTime &date, double latitude, double longitude)
    {
        return QDateTime(date.date(), KHolidays::SunRiseSet::utcDusk(date.date(), latitude, longitude), Qt::UTC);
    }
};

void KHolidaysDeclarativePlugin::registerTypes(const char *uri)
{
    qmlRegisterType<HolidayRegionsDeclarativeModel>(uri, 1, 0, "HolidayRegionsModel");
    qRegisterMetaType<KHolidays::LunarPhase::Phase>();
    qmlRegisterUncreatableType<KHolidays::LunarPhase>(uri, 1, 0, "LunarPhase", {});

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
