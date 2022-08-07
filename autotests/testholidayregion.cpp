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
            qDebug().nospace() << "Date = " << holiday.observedStartDate().toString(Qt::ISODate) << " Duration = " << holiday.duration()
                               << " Name = " << holiday.name().leftJustified(20, /*QChar fill=*/QLatin1Char(' '), /*bool truncate=*/false)
                               << " Category = " << holiday.categoryList();
        }
    } else {
        qDebug() << "No holidays";
    }
}

void HolidayRegionTest::parseRegionCalendarYear(const KHolidays::HolidayRegion &region, int year, const QString &calendarType)
{
    qDebug() << "Parsing region = " << region.regionCode() << " year = " << year << " calendar = " << calendarType;
#if KHOLIDAYS_BUILD_DEPRECATED_SINCE(5, 95)
    printHolidays(region.holidays(year));
#else
    printHolidays(region.rawHolidaysWithAstroSeasons(year));
#endif
    qDebug() << "";
}

void HolidayRegionTest::parseRegionDateRange(const KHolidays::HolidayRegion &region, const QDate &startDate, const QDate &endDate)
{
    qDebug() << "Parsing regionCode = " << region.regionCode() << " start date = " << startDate.toString(Qt::ISODate)
             << " end date = " << endDate.toString(Qt::ISODate);
#if KHOLIDAYS_BUILD_DEPRECATED_SINCE(5, 95)
    printHolidays(region.holidays(startDate, endDate));
#else
    printHolidays(region.rawHolidaysWithAstroSeasons(startDate, endDate));
#endif
    qDebug() << "";
}

void HolidayRegionTest::parseRawRegionDateRange(const KHolidays::HolidayRegion &region, const QDate &startDate, const QDate &endDate)
{
    qDebug() << "Parsing regionCode = " << region.regionCode() << " start date = " << startDate.toString(Qt::ISODate)
             << " end date = " << endDate.toString(Qt::ISODate);
    printHolidays(region.rawHolidaysWithAstroSeasons(startDate, endDate));
    qDebug() << "";
}

void HolidayRegionTest::parseRegionDate(const KHolidays::HolidayRegion &region, const QDate &date)
{
    qDebug() << "Parsing regionCode = " << region.regionCode() << " date = " << date.toString(Qt::ISODate);
#if KHOLIDAYS_BUILD_DEPRECATED_SINCE(5, 95)
    printHolidays(region.holidays(date));
#else
    printHolidays(region.rawHolidaysWithAstroSeasons(date));
#endif
    qDebug() << "";
}

void HolidayRegionTest::parseRegionDateRangeCategory(const KHolidays::HolidayRegion &region,
                                                     const QDate &startDate,
                                                     const QDate &endDate,
                                                     const QString &category)
{
    qDebug() << "Parsing regionCode = " << region.regionCode() << " start date = " << startDate.toString(Qt::ISODate)
             << " end date = " << endDate.toString(Qt::ISODate) << " category = " << category;
    printHolidays(region.rawHolidays(startDate, endDate, category));
    qDebug() << "";
}

void HolidayRegionTest::testLoadFileCalendarSystems()
{
    KHolidays::HolidayRegion region(QFileInfo(KDESRCDIR "/holiday_calendar_systems"));
    printMetadata(region);
    parseRegionDateRangeCategory(region, QDate(2020, 7, 1), QDate(2021, 6, 30), "seasonal");
    parseRegionDateRangeCategory(region, QDate(2020, 1, 1), QDate(2022, 12, 31), "seasonal");
    parseRegionDateRangeCategory(region, QDate(2020, 1, 1), QDate(2020, 12, 31), "public");
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
    parseRegionCalendarYear(region, 2020, QStringLiteral("gregorian"));
    parseRegionCalendarYear(region, 2020);
    parseRegionCalendarYear(region, 2021);
    parseRegionCalendarYear(region, 2022);
    parseRegionCalendarYear(region, 2023);
    parseRegionCalendarYear(region, 2024);
    parseRegionCalendarYear(region, 2025);
    qDebug() << "";
}

void HolidayRegionTest::testGb()
{
    KHolidays::HolidayRegion region(QStringLiteral("gb-eaw_en-gb"));
    printMetadata(region);
    parseRegionDateRange(region, QDate(2020, 7, 1), QDate(2021, 6, 30));
    parseRegionDateRange(region, QDate(2020, 1, 1), QDate(2022, 12, 31));
    parseRegionDateRange(region, QDate(2020, 1, 1), QDate(2020, 12, 31));
    parseRegionDate(region, QDate(2020, 1, 1));
    parseRegionCalendarYear(region, 2020);
    parseRegionCalendarYear(region, 2021);
    parseRegionCalendarYear(region, 2022);
    parseRegionCalendarYear(region, 2023);
    parseRegionCalendarYear(region, 2024);
    parseRegionCalendarYear(region, 2025);
}

void HolidayRegionTest::testIran()
{
    KHolidays::HolidayRegion region(QStringLiteral("ir_en-us"));
    printMetadata(region);
    parseRegionCalendarYear(region, 2020);
    parseRegionCalendarYear(region, 2021);
    parseRegionCalendarYear(region, 2022);
    parseRegionCalendarYear(region, 2023);
    parseRegionCalendarYear(region, 2024);
    parseRegionCalendarYear(region, 2025);
}

void HolidayRegionTest::testIsrael()
{
    KHolidays::HolidayRegion region(QStringLiteral("il_en-us"));
    printMetadata(region);
    parseRegionCalendarYear(region, 2020);
    parseRegionCalendarYear(region, 2021);
    parseRegionCalendarYear(region, 2022);
    parseRegionCalendarYear(region, 2023);
    parseRegionCalendarYear(region, 2024);
    parseRegionCalendarYear(region, 2025);
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

void HolidayRegionTest::testSolistaleInHolidays()
{
    KHolidays::HolidayRegion region(QFileInfo(KDESRCDIR "/holiday_solstice_in_holidays"));

    auto holidays = region.rawHolidaysWithAstroSeasons(QDate(2020, 7, 1), QDate(2021, 6, 30));
    QCOMPARE(holidays.size(), 5);
    QCOMPARE(holidays.first().observedStartDate(), QDate(2020, 9, 22));
    QCOMPARE(holidays.first().name(), QLatin1String("September Equinox"));

    holidays = region.rawHolidays(QDate(2020, 7, 1), QDate(2021, 6, 30));
    QCOMPARE(holidays.size(), 1);
    QCOMPARE(holidays.first().observedStartDate(), QDate(2021, 1, 1));
    QCOMPARE(holidays.first().name(), QLatin1String("New Years"));

    holidays = region.rawHolidays(QDate(2020, 7, 1), QDate(2021, 6, 30), QLatin1String("public"));
    QCOMPARE(holidays.size(), 1);
    QCOMPARE(holidays.first().observedStartDate(), QDate(2021, 1, 1));
    QCOMPARE(holidays.first().name(), QLatin1String("New Years"));

    holidays = region.rawHolidays(QDate(2020, 7, 1), QDate(2021, 6, 30), QLatin1String("seasonal"));
    QCOMPARE(holidays.size(), 4);
    QCOMPARE(holidays.first().observedStartDate(), QDate(2020, 9, 22));
    QCOMPARE(holidays.first().name(), QLatin1String("September Equinox"));

    holidays = region.rawHolidaysWithAstroSeasons(2020);
    QCOMPARE(holidays.size(), 5);
    QCOMPARE(holidays.first().observedStartDate(), QDate(2020, 1, 1));
    QCOMPARE(holidays.first().name(), QLatin1String("New Years"));
    QCOMPARE(holidays.last().observedStartDate(), QDate(2020, 12, 21));
    QCOMPARE(holidays.last().name(), QLatin1String("December Solstice"));

    holidays = region.rawHolidaysWithAstroSeasons(QDate(2021, 3, 20));
    QCOMPARE(holidays.size(), 1);
    QCOMPARE(holidays.first().observedStartDate(), QDate(2021, 3, 20));
    QCOMPARE(holidays.first().name(), QLatin1String("March Equinox"));
}

void HolidayRegionTest::testLoadFileCalendarSystemsForPlasma()
{
    KHolidays::HolidayRegion region(QFileInfo(KDESRCDIR "/holiday_calendar_systems"));
    printMetadata(region);
    parseRawRegionDateRange(region, QDate(2020, 7, 1), QDate(2021, 6, 30));
    parseRawRegionDateRange(region, QDate(2020, 1, 1), QDate(2020, 12, 31));
    parseRawRegionDateRange(region, QDate(2020, 11, 1), QDate(2021, 1, 2));
    parseRawRegionDateRange(region, QDate(2020, 12, 25), QDate(2021, 7, 2));
    parseRawRegionDateRange(region, QDate(2020, 12, 25), QDate(2022, 1, 2));
}
