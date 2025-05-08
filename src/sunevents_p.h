/*
    SPDX-FileCopyrightText: 2025 Vlad Zahorodnii <vlad.zahorodnii@kde.org>

    SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
*/

#ifndef KHOLIDAYS_SUNTRANSIT_P_H
#define KHOLIDAYS_SUNTRANSIT_P_H

#include <QSharedData>

namespace KHolidays
{

class SunEventsData : public QSharedData
{
public:
    qreal latitude;
    qreal longitude;
    qreal solarNoon;
};

}

#endif
