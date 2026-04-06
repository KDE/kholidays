/*
    This file is part of the kholidays library.

    SPDX-FileCopyrightText: Allen Winter <winter@kde.org>
    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef KHOLIDAYS_HOLIDAYCATEGORIES_H
#define KHOLIDAYS_HOLIDAYCATEGORIES_H

#include "kholidays_export.h"

#include <QStringList>

namespace KHolidays
{
/*!
 * \since 6.26.0
 *
 * Returns a list of all legal holiday categories.
 */
[[nodiscard]] KHOLIDAYS_EXPORT QStringList allHolidayCategories();

/*!
 * \since 6.26.0
 *
 * Returns if the specified string is a valid holiday category.
 */
[[nodiscard]] KHOLIDAYS_EXPORT bool isHolidayCategoryValid(const QString &category);

/*!
 * \since 6.26.0
 *
 * Returns the translated string associated with the specified holiday category.
 * An empty QString is returned for an illegal category.
 */
[[nodiscard]] KHOLIDAYS_EXPORT QString translateHolidayCategory(const QString &category);

/*!
 * \since 6.26
 *
 * Returns a string containing a description of the specified category (for use in tooltips, for example).
 * An empty QString is returned for an illegal category.
 */
[[nodiscard]] KHOLIDAYS_EXPORT QString holidayCategoryDescription(const QString &category);

}

#endif
