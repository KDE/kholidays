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

#ifndef HOLIDAYREGIONSDECLARATIVEMODEL_H
#define HOLIDAYREGIONSDECLARATIVEMODEL_H

#include <QObject>
#include <QAbstractListModel>

class HolidayRegionsDeclarativeModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        RegionRole = Qt::UserRole + 1,
        NameRole,
        DescriptionRole
    };
    explicit HolidayRegionsDeclarativeModel(QObject *parent = nullptr);
    virtual ~HolidayRegionsDeclarativeModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    class Private;
    Private *const d;
};

#endif
