/*
 *  This file is part of the kholidays library.
 *
 *  SPDX-FileCopyrightText: Allen Winter <winter@kde.org>
 *  SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include "holidaycategories.h"

#include <QDebug>
#include <QObject>
#include <QStringLiteral>

QStringList KHolidays::allHolidayCategories()
{
    return {
        QStringLiteral("public"),
        QStringLiteral("civil"),
        QStringLiteral("religious"),
        QStringLiteral("school"),
        QStringLiteral("government"),
        QStringLiteral("financial"),
        QStringLiteral("cultural"),
        QStringLiteral("commemorative"),
        QStringLiteral("historical"),
        QStringLiteral("nameday"),
        QStringLiteral("seasonal"),
    };
}

bool KHolidays::isHolidayCategoryValid(const QString &category)
{
    return KHolidays::allHolidayCategories().contains(category);
}

QString KHolidays::translateHolidayCategory(const QString &category)
{
    if (category == QStringLiteral("public")) {
        return QObject::tr("public", "public holiday type");
    }
    if (category == QStringLiteral("civil")) {
        return QObject::tr("civil", "civil holiday type");
    }
    if (category == QStringLiteral("religious")) {
        return QObject::tr("religious", "religious holiday type");
    }
    if (category == QStringLiteral("school")) {
        return QObject::tr("school", "school holiday type");
    }
    if (category == QStringLiteral("government")) {
        return QObject::tr("government", "government holiday type");
    }
    if (category == QStringLiteral("financial")) {
        return QObject::tr("financial", "financial holiday type");
    }
    if (category == QStringLiteral("cultural")) {
        return QObject::tr("cultural", "cultural holiday type");
    }
    if (category == QStringLiteral("commemorative")) {
        return QObject::tr("commemorative", "commemorative holiday type");
    }
    if (category == QStringLiteral("historical")) {
        return QObject::tr("historical", "historical holiday type");
    }
    if (category == QStringLiteral("nameday")) {
        return QObject::tr("nameday", "nameday holiday type");
    }
    if (category == QStringLiteral("seasonal")) {
        return QObject::tr("seasonal", "seasonal holiday type");
    }
    return {};
}

QString KHolidays::holidayCategoryDescription(const QString &category)
{
    if (category == QStringLiteral("public")) {
        return QObject::tr(
            "Public Holiday: a day-off from work or school (typically) to commemorate a historical event, or to honor people.  Public holidays are always "
            "bounded to a political region at national, regional or local level.");
    }
    if (category == QStringLiteral("civil")) {
        return QObject::tr("Civil Service Holiday: a day-off from work for government workers but not a day off for private sector workers.");
    }
    if (category == QStringLiteral("religious")) {
        return QObject::tr(
            "Religious Holiday: a special day in a religion and not bound to any political region. Religions can have holidays that range in devotion to those "
            "were work/school are forbidden, days of prayer obligation, to historical remembrances, etc. Governments often have public holidays for some "
            "religious holidays.");
    }
    if (category == QStringLiteral("school")) {
        return QObject::tr(
            "School Holiday: a day-off from school, either as a one-off Public Holiday or extended periods between school terms.  This can vary widely "
            "depending on school level, type, location.");
    }
    if (category == QStringLiteral("government")) {
        return QObject::tr("Government Holiday: a special day recognized by a political region but without a day-off for workers, students, etc.");
    }
    if (category == QStringLiteral("financial")) {
        return QObject::tr("Financial Holiday: banks and markets may close on some public holidays");
    }
    if (category == QStringLiteral("cultural")) {
        return QObject::tr(
            "Cultural Holiday: a special day in the culture and therefore usually bound to a political region. A day where people celebrate in some fashion. "
            "eg. Halloween, St. Valentines");
    }
    if (category == QStringLiteral("commemorative")) {
        return QObject::tr(
            "Commemorative Holiday: a special day to remember usually bound to a political region. Not a day-off from work or school; banks are open, etc.");
    }
    if (category == QStringLiteral("historical")) {
        return QObject::tr("Historical Holiday: similar to a Commemorative Holiday but historical in nature.");
    }
    if (category == QStringLiteral("nameday")) {
        return QObject::tr(
            "Name Day Holiday: in some political regions each day is assigned a first name and persons with that name celebrate that day as their \"Name "
            "Day\".");
    }
    if (category == QStringLiteral("seasonal")) {
        return QObject::tr("Seasonal Days: the day corresponds to a seasonal event like an equinox, solstice, daylight saving time starts/ends.");
    }
    return {};
}
