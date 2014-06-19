/*
    This file is part of the kholidays library.

    Copyright 2010 John Layt <john@layt.net>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#ifndef TESTHOLIDAYREGION_H
#define TESTHOLIDAYREGION_H

#include <QtCore/QObject>

#include "holidays.h"

class QString;
class QDate;

class HolidayRegionTest : public QObject
{
Q_OBJECT
private Q_SLOTS:
    void testLoadFile();
    void testGb();
    void testIran();
    void testIsrael();
    void testRegions();
    void testLocations();
    void testDefaultRegions();

private:
    void printMetadata( const KHolidays::HolidayRegion &region );
    void printHolidays( KHolidays::Holiday::List holidays );
    void parseRegionCalendarYear( const KHolidays::HolidayRegion &region, int year,
                                  const QString &calendarType = "gregorian",
                                  KHolidays::Holiday::MultidayMode multidayMode = KHolidays::Holiday::MultidayHolidaysAsMultipleEvents );
    void parseRegionDateRange( const KHolidays::HolidayRegion &region, const QDate &startDate, const QDate &endDate,
                               KHolidays::Holiday::MultidayMode multidayMode = KHolidays::Holiday::MultidayHolidaysAsMultipleEvents );
    void parseRegionDate( const KHolidays::HolidayRegion &region, const QDate &date,
                          KHolidays::Holiday::MultidayMode multidayMode = KHolidays::Holiday::MultidayHolidaysAsMultipleEvents );
};

#endif // TESTHOLIDAYREGION_H
