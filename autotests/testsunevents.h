/*
    SPDX-FileCopyrightText: 2025 Vlad Zahorodnii <vlad.zahorodnii@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef TESTSUNEVENTS_H
#define TESTSUNEVENTS_H

#include <QObject>

class SunEventsTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void pole();
    void transitTime_data();
    void transitTime();
    void polarDayNight();
};

#endif
