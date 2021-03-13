/*
    This file is part of the kholidays library.

    SPDX-FileCopyrightText: 2015 Martin Klapetek <mklapetek@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef HOLIDAYREGIONSMODEL_H
#define HOLIDAYREGIONSMODEL_H

#include <QObject>
#include <QAbstractListModel>

class HolidayRegionsDeclarativeModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        RegionRole = Qt::UserRole + 1,
        NameRole,
        DescriptionRole,
    };
    explicit HolidayRegionsDeclarativeModel(QObject *parent = nullptr);
    ~HolidayRegionsDeclarativeModel() override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    class Private;
    Private *const d;
};

#endif
