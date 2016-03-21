/*
  This file is part of the kholidays library.

  Copyright (c) 2015 Martin Klapetek <mklapetek@kde.org>

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Library General Public
  License as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Library General Public License for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; see the file COPYING.LIB.  If not, write to the
  Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
  Boston, MA 02110-1301, USA.
*/

#include "holidayregionsmodel.h"

#include "../holidayregion.h"

class HolidayRegionsDeclarativeModel::Private
{
public:
    QStringList regionCodes;
};

HolidayRegionsDeclarativeModel::HolidayRegionsDeclarativeModel(QObject *parent)
    : QAbstractListModel(parent),
      d(new Private())
{
    d->regionCodes = KHolidays::HolidayRegion::regionCodes();
    // Make sure we don't add the same regions twice
    // This can happen if two copies of the data exists
    // in the system and both are read by KHolidays
    d->regionCodes.removeDuplicates();
}

HolidayRegionsDeclarativeModel::~HolidayRegionsDeclarativeModel()
{
    delete d;
}

int HolidayRegionsDeclarativeModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return d->regionCodes.size();
}

QVariant HolidayRegionsDeclarativeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    const QString regionCode = d->regionCodes.at(index.row());

    switch (role) {
    case HolidayRegionsDeclarativeModel::RegionRole:
        return regionCode;
    case HolidayRegionsDeclarativeModel::NameRole:
        return KHolidays::HolidayRegion::name(regionCode);
    case HolidayRegionsDeclarativeModel::DescriptionRole:
        return KHolidays::HolidayRegion::description(regionCode);
    }

    return QVariant();
}

QHash<int, QByteArray> HolidayRegionsDeclarativeModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles.insert(HolidayRegionsDeclarativeModel::RegionRole, QByteArrayLiteral("region"));
    roles.insert(HolidayRegionsDeclarativeModel::NameRole, QByteArrayLiteral("name"));
    roles.insert(HolidayRegionsDeclarativeModel::DescriptionRole, QByteArrayLiteral("description"));

    return roles;
}
