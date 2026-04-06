/*
    This file is part of the kholidays library.

    SPDX-FileCopyrightText: Allen Winter <winter@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef TESTCATEGORIES_H
#define TESTCATEGORIES_H

#include <QObject>

class CategoriesTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void testCategories();
    void testCategoryDescriptions();
};

#endif
