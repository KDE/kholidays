/*
    This file is part of the kholidays library.

    SPDX-FileCopyrightText: Allen Winter <winter@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "testcategories.h"
#include "holidaycategories.h"

#include <QDebug>
#include <QTest>

QTEST_MAIN(CategoriesTest)

#include "kholidays/lunarphase.h"
using namespace KHolidays;

void CategoriesTest::testCategories()
{
    const QStringList categories = KHolidays::allHolidayCategories();
    QCOMPARE(categories.size(), 11);

    QVERIFY(isHolidayCategoryValid(QLatin1String("seasonal")));
    QVERIFY(!isHolidayCategoryValid(QLatin1String("birthdays")));
}

void CategoriesTest::testCategoryDescriptions()
{
    const QStringList categories = KHolidays::allHolidayCategories();
    for (const QString &category : categories) {
        QVERIFY(!holidayCategoryDescription(category).isEmpty());
    }
}

#include "moc_testcategories.cpp"
