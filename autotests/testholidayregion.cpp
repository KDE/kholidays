/*
    This file is part of the kholidays library.

    SPDX-FileCopyrightText: 2010 John Layt <john@layt.net>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "testholidayregion.h"

#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QString>
#include <QTest>

QTEST_MAIN(HolidayRegionTest)

void HolidayRegionTest::printMetadata(const KHolidays::HolidayRegion &region)
{
    if (region.isValid()) {
        qDebug() << "This regionCode = " << region.regionCode();
        qDebug() << "Is valid? = " << region.isValid();
        qDebug() << "Country code = " << region.countryCode();
        qDebug() << "Language code = " << region.languageCode();
        qDebug() << "Name = " << region.name();
        qDebug() << "Description = " << region.description();
    } else {
        qDebug() << "Not Valid!";
    }
    qDebug() << "";
}

void HolidayRegionTest::printHolidays(const KHolidays::Holiday::List &holidays)
{
    if (!holidays.isEmpty()) {
        for (const KHolidays::Holiday &holiday : holidays) {
            qDebug() << "Date = " << holiday.observedStartDate().toString(Qt::ISODate) << " Duration = " << holiday.duration() << " Name = " << holiday.name();
        }
    } else {
        qDebug() << "No holidays";
    }
}

void HolidayRegionTest::parseRegionCalendarYear(const KHolidays::HolidayRegion &region, int year, const QString &calendarType)
{
    qDebug() << "Parsing region = " << region.regionCode() << " year = " << year << " calendar = " << calendarType;
    printHolidays(region.holidays(year));
    qDebug() << "";
}

void HolidayRegionTest::parseRegionDateRange(const KHolidays::HolidayRegion &region, const QDate &startDate, const QDate &endDate)
{
    qDebug() << "Parsing regionCode = " << region.regionCode() << " start date = " << startDate.toString(Qt::ISODate)
             << " end date = " << endDate.toString(Qt::ISODate);
    printHolidays(region.holidays(startDate, endDate));
    qDebug() << "";
}

void HolidayRegionTest::parseRegionDate(const KHolidays::HolidayRegion &region, const QDate &date)
{
    qDebug() << "Parsing regionCode = " << region.regionCode() << " date = " << date.toString(Qt::ISODate);
    printHolidays(region.holidays(date));
    qDebug() << "";
}

void HolidayRegionTest::testLoadFileCalendarSystems()
{
    KHolidays::HolidayRegion region(QFileInfo(KDESRCDIR "/holiday_calendar_systems"));
    printMetadata(region);
    parseRegionCalendarYear(region, 2020, QStringLiteral("gregorian"));
    parseRegionCalendarYear(region, 2020);
    parseRegionCalendarYear(region, 2021);
    parseRegionCalendarYear(region, 2022);
    parseRegionCalendarYear(region, 2023);
    parseRegionCalendarYear(region, 2024);
    parseRegionCalendarYear(region, 2025);
    qDebug() << "";
}

void HolidayRegionTest::testLoadFile()
{
    KHolidays::HolidayRegion region(QFileInfo(KDESRCDIR "/holiday_gb-eaw_en-gb_Test"));
    printMetadata(region);
    parseRegionCalendarYear(region, 2010, QStringLiteral("gregorian"));
    parseRegionCalendarYear(region, 2010);
    parseRegionCalendarYear(region, 2011);
    parseRegionCalendarYear(region, 2012);
    parseRegionCalendarYear(region, 2013);
    parseRegionCalendarYear(region, 2014);
    parseRegionCalendarYear(region, 2015);
    qDebug() << "";
}

void HolidayRegionTest::testGb()
{
    KHolidays::HolidayRegion region(QStringLiteral("gb-eaw_en-gb"));
    printMetadata(region);
    parseRegionDateRange(region, QDate(2010, 7, 1), QDate(2011, 6, 30));
    parseRegionDateRange(region, QDate(2010, 1, 1), QDate(2012, 12, 31));
    parseRegionDateRange(region, QDate(2010, 1, 1), QDate(2010, 12, 31));
    parseRegionDate(region, QDate(2010, 1, 1));
    parseRegionCalendarYear(region, 2010);
    parseRegionCalendarYear(region, 2011);
    parseRegionCalendarYear(region, 2012);
    parseRegionCalendarYear(region, 2013);
    parseRegionCalendarYear(region, 2014);
    parseRegionCalendarYear(region, 2015);
}

void HolidayRegionTest::testIran()
{
    KHolidays::HolidayRegion region(QStringLiteral("ir_en-us"));
    printMetadata(region);
    parseRegionCalendarYear(region, 2010);
    parseRegionCalendarYear(region, 2011);
    parseRegionCalendarYear(region, 2012);
    parseRegionCalendarYear(region, 2013);
    parseRegionCalendarYear(region, 2014);
    parseRegionCalendarYear(region, 2015);
}

void HolidayRegionTest::testIsrael()
{
    KHolidays::HolidayRegion region(QStringLiteral("il_en-us"));
    printMetadata(region);
    parseRegionCalendarYear(region, 2010);
    parseRegionCalendarYear(region, 2011);
    parseRegionCalendarYear(region, 2012);
    parseRegionCalendarYear(region, 2013);
    parseRegionCalendarYear(region, 2014);
    parseRegionCalendarYear(region, 2015);
}

void HolidayRegionTest::testRegions()
{
    qDebug() << "Available region codes:";
    const QStringList regionCodes = KHolidays::HolidayRegion::regionCodes();
    for (const QString &regionCode : regionCodes) {
        KHolidays::HolidayRegion testRegion(regionCode);
        qDebug() << regionCode << " = " << testRegion.name();
    }
    qDebug() << "";

    qDebug() << "This years holidays:";
    for (const QString &regionCode : regionCodes) {
        KHolidays::HolidayRegion testRegion(regionCode);
        printMetadata(testRegion);
        parseRegionCalendarYear(testRegion, QDate::currentDate().year());
        qDebug() << "";
    }
    qDebug() << "";
}

void HolidayRegionTest::testDefaultRegions()
{
    QCOMPARE(KHolidays::HolidayRegion::defaultRegionCode("be", "nl"), QString("be_nl"));
    QCOMPARE(KHolidays::HolidayRegion::defaultRegionCode("be", "fr"), QString("be_fr"));
    QCOMPARE(KHolidays::HolidayRegion::defaultRegionCode("be", "xx"), QString("be_fr"));
    QCOMPARE(KHolidays::HolidayRegion::defaultRegionCode("xx", "fr_BE"), QString("be_fr"));
    QCOMPARE(KHolidays::HolidayRegion::defaultRegionCode("xx", "xx"), QString());
    QCOMPARE(KHolidays::HolidayRegion::defaultRegionCode("au", "en_GB"), QString("au-act_en-gb"));
    QCOMPARE(KHolidays::HolidayRegion::defaultRegionCode("au-VIC", "en_GB"), QString("au-vic_en-gb"));
    QCOMPARE(KHolidays::HolidayRegion::defaultRegionCode("DE-BE"), QLatin1String("de-be_de"));
    QCOMPARE(KHolidays::HolidayRegion::defaultRegionCode("DE"), QLatin1String("de_de"));
    QCOMPARE(KHolidays::HolidayRegion::defaultRegionCode("AT-9"), QLatin1String("at_de"));
    QCOMPARE(KHolidays::HolidayRegion::defaultRegionCode("US-CA"), QLatin1String("us_en-us"));
}
