/*
    This file is part of the kholidays library.

    SPDX-FileCopyrightText: 2015 Martin Klapetek <mklapetek@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kholidaysdeclarativeplugin.h"
#include "holidayregionsmodel.h"

#include <qqml.h>

void KHolidaysDeclarativePlugin::registerTypes(const char *uri)
{
    qmlRegisterType<HolidayRegionsDeclarativeModel>(uri, 1, 0, "HolidayRegionsModel");
}
