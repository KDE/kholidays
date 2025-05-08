/*
    SPDX-FileCopyrightText: 2012 Allen Winter <winter@kde.org>
    SPDX-FileCopyrightText: 2025 Vlad Zahorodnii <vlad.zahorodnii@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "testsunevents.h"
#include "sunevents.h"

#include <QTest>

QTEST_MAIN(SunEventsTest)

using namespace KHolidays;

struct Sample {
    QDate date;
    int firstHour;
    int lastHour;
    QTimeZone timeZone;
    qreal latitude;
    qreal longitude;
    QDateTime astronomicalDawn;
    QDateTime nauticalDawn;
    QDateTime civilDawn;
    QDateTime sunrise;
    QDateTime noon;
    QDateTime sunset;
    QDateTime civilDusk;
    QDateTime nauticalDusk;
    QDateTime astronomicalDusk;
    qreal tolerance = 5 * 60;
};

void SunEventsTest::pole()
{
    for (qreal latitude : {-90, 90}) {
        const SunEvents transit(QDateTime::currentDateTime(), latitude, 0);

        QVERIFY(!transit.astronomicalDawn().isValid());
        QVERIFY(!transit.nauticalDawn().isValid());
        QVERIFY(!transit.civilDawn().isValid());
        QVERIFY(!transit.sunrise().isValid());
        QVERIFY(transit.solarNoon().isValid());
        QVERIFY(!transit.sunset().isValid());
        QVERIFY(!transit.civilDusk().isValid());
        QVERIFY(!transit.nauticalDusk().isValid());
        QVERIFY(!transit.astronomicalDusk().isValid());
    }
}

static QTimeZone makeTimeZone(int hours, int minutes = 0)
{
    return QTimeZone::fromSecondsAheadOfUtc(hours * 60 * 60 + minutes * 60);
}

void SunEventsTest::transitTime_data()
{
    QTest::addColumn<Sample>("sample");

    QTest::addRow("Adelaide on 4/30/25") << Sample{
        .date = QDate(2025, 4, 30),
        .firstHour = 1,
        .lastHour = 24,
        .timeZone = makeTimeZone(9, 30),
        .latitude = -34.9275,
        .longitude = 138.6,
        .astronomicalDawn = QDateTime(QDate(2025, 4, 30), QTime(5, 25), makeTimeZone(9, 30)),
        .nauticalDawn = QDateTime(QDate(2025, 4, 30), QTime(5, 55), makeTimeZone(9, 30)),
        .civilDawn = QDateTime(QDate(2025, 4, 30), QTime(6, 24), makeTimeZone(9, 30)),
        .sunrise = QDateTime(QDate(2025, 4, 30), QTime(6, 51), makeTimeZone(9, 30)),
        .noon = QDateTime(QDate(2025, 4, 30), QTime(12, 12), makeTimeZone(9, 30)),
        .sunset = QDateTime(QDate(2025, 4, 30), QTime(17, 34), makeTimeZone(9, 30)),
        .civilDusk = QDateTime(QDate(2025, 4, 30), QTime(18, 0), makeTimeZone(9, 30)),
        .nauticalDusk = QDateTime(QDate(2025, 4, 30), QTime(18, 30), makeTimeZone(9, 30)),
        .astronomicalDusk = QDateTime(QDate(2025, 4, 30), QTime(19, 0), makeTimeZone(9, 30)),
    };

    QTest::addRow("Wellington on 4/30/25") << Sample{
        .date = QDate(2025, 4, 30),
        .firstHour = 1,
        .lastHour = 24,
        .timeZone = makeTimeZone(12, 0),
        .latitude = -41.3,
        .longitude = 174.783333,
        .astronomicalDawn = QDateTime(QDate(2025, 4, 30), QTime(5, 33), makeTimeZone(12, 0)),
        .nauticalDawn = QDateTime(QDate(2025, 4, 30), QTime(6, 5), makeTimeZone(12, 0)),
        .civilDawn = QDateTime(QDate(2025, 4, 30), QTime(6, 38), makeTimeZone(12, 0)),
        .sunrise = QDateTime(QDate(2025, 4, 30), QTime(7, 7), makeTimeZone(12, 0)),
        .noon = QDateTime(QDate(2025, 4, 30), QTime(12, 18), makeTimeZone(12, 0)),
        .sunset = QDateTime(QDate(2025, 4, 30), QTime(17, 29), makeTimeZone(12, 0)),
        .civilDusk = QDateTime(QDate(2025, 4, 30), QTime(17, 57), makeTimeZone(12, 0)),
        .nauticalDusk = QDateTime(QDate(2025, 4, 30), QTime(18, 30), makeTimeZone(12, 0)),
        .astronomicalDusk = QDateTime(QDate(2025, 4, 30), QTime(19, 2), makeTimeZone(12, 0)),
    };

    QTest::addRow("Kyiv on 4/30/25") << Sample{
        .date = QDate(2025, 4, 30),
        .firstHour = 1,
        .lastHour = 24,
        .timeZone = makeTimeZone(3, 0),
        .latitude = 50.45,
        .longitude = 30.523333,
        .astronomicalDawn = QDateTime(QDate(2025, 4, 30), QTime(3, 12), makeTimeZone(3, 0)),
        .nauticalDawn = QDateTime(QDate(2025, 4, 30), QTime(4, 9), makeTimeZone(3, 0)),
        .civilDawn = QDateTime(QDate(2025, 4, 30), QTime(4, 57), makeTimeZone(3, 0)),
        .sunrise = QDateTime(QDate(2025, 4, 30), QTime(5, 34), makeTimeZone(3, 0)),
        .noon = QDateTime(QDate(2025, 4, 30), QTime(12, 55), makeTimeZone(3, 0)),
        .sunset = QDateTime(QDate(2025, 4, 30), QTime(20, 16), makeTimeZone(3, 0)),
        .civilDusk = QDateTime(QDate(2025, 4, 30), QTime(20, 53), makeTimeZone(3, 0)),
        .nauticalDusk = QDateTime(QDate(2025, 4, 30), QTime(21, 40), makeTimeZone(3, 0)),
        .astronomicalDusk = QDateTime(QDate(2025, 4, 30), QTime(22, 37), makeTimeZone(3, 0)),
    };

    QTest::addRow("London on 4/30/25") << Sample{
        .date = QDate(2025, 4, 30),
        .firstHour = 2,
        .lastHour = 25,
        .timeZone = makeTimeZone(1, 0),
        .latitude = 51.507222,
        .longitude = -0.1275,
        .astronomicalDawn = QDateTime(QDate(2025, 4, 30), QTime(3, 5), makeTimeZone(1, 0)),
        .nauticalDawn = QDateTime(QDate(2025, 4, 30), QTime(4, 5), makeTimeZone(1, 0)),
        .civilDawn = QDateTime(QDate(2025, 4, 30), QTime(4, 55), makeTimeZone(1, 0)),
        .sunrise = QDateTime(QDate(2025, 4, 30), QTime(5, 33), makeTimeZone(1, 0)),
        .noon = QDateTime(QDate(2025, 4, 30), QTime(12, 57), makeTimeZone(1, 0)),
        .sunset = QDateTime(QDate(2025, 4, 30), QTime(20, 22), makeTimeZone(1, 0)),
        .civilDusk = QDateTime(QDate(2025, 4, 30), QTime(21, 0), makeTimeZone(1, 0)),
        .nauticalDusk = QDateTime(QDate(2025, 4, 30), QTime(21, 49), makeTimeZone(1, 0)),
        .astronomicalDusk = QDateTime(QDate(2025, 4, 30), QTime(22, 50), makeTimeZone(1, 0)),
    };

    QTest::addRow("Oulu on 4/30/25") << Sample{
        .date = QDate(2025, 4, 30),
        .firstHour = 2,
        .lastHour = 25,
        .timeZone = makeTimeZone(3, 0),
        .latitude = 65.014167,
        .longitude = 25.471944,
        .astronomicalDawn = QDateTime(),
        .nauticalDawn = QDateTime(),
        .civilDawn = QDateTime(QDate(2025, 4, 30), QTime(3, 31), makeTimeZone(3, 0)),
        .sunrise = QDateTime(QDate(2025, 4, 30), QTime(4, 45), makeTimeZone(3, 0)),
        .noon = QDateTime(QDate(2025, 4, 30), QTime(13, 15), makeTimeZone(3, 0)),
        .sunset = QDateTime(QDate(2025, 4, 30), QTime(21, 44), makeTimeZone(3, 0)),
        .civilDusk = QDateTime(QDate(2025, 4, 30), QTime(22, 58), makeTimeZone(3, 0)),
        .nauticalDusk = QDateTime(),
        .astronomicalDusk = QDateTime(),
        .tolerance = 10 * 60,
    };

    QTest::addRow("Denver on 4/30/25") << Sample{
        .date = QDate(2025, 4, 30),
        .firstHour = 1,
        .lastHour = 24,
        .timeZone = makeTimeZone(-6, 0),
        .latitude = 39.7392,
        .longitude = -104.9849,
        .astronomicalDawn = QDateTime(QDate(2025, 4, 30), QTime(4, 18), makeTimeZone(-6, 0)),
        .nauticalDawn = QDateTime(QDate(2025, 4, 30), QTime(4, 56), makeTimeZone(-6, 0)),
        .civilDawn = QDateTime(QDate(2025, 4, 30), QTime(5, 31), makeTimeZone(-6, 0)),
        .sunrise = QDateTime(QDate(2025, 4, 30), QTime(6, 0), makeTimeZone(-6, 0)),
        .noon = QDateTime(QDate(2025, 4, 30), QTime(12, 57), makeTimeZone(-6, 0)),
        .sunset = QDateTime(QDate(2025, 4, 30), QTime(19, 53), makeTimeZone(-6, 0)),
        .civilDusk = QDateTime(QDate(2025, 4, 30), QTime(20, 22), makeTimeZone(-6, 0)),
        .nauticalDusk = QDateTime(QDate(2025, 4, 30), QTime(20, 57), makeTimeZone(-6, 0)),
        .astronomicalDusk = QDateTime(QDate(2025, 4, 30), QTime(21, 36), makeTimeZone(-6, 0)),
    };

    QTest::addRow("San Francisco on 4/30/25") << Sample{
        .date = QDate(2025, 4, 30),
        .firstHour = 2,
        .lastHour = 25,
        .timeZone = makeTimeZone(-7, 0),
        .latitude = 37.783333,
        .longitude = -122.416667,
        .astronomicalDawn = QDateTime(QDate(2025, 4, 30), QTime(4, 35), makeTimeZone(-7, 0)),
        .nauticalDawn = QDateTime(QDate(2025, 4, 30), QTime(5, 11), makeTimeZone(-7, 0)),
        .civilDawn = QDateTime(QDate(2025, 4, 30), QTime(5, 46), makeTimeZone(-7, 0)),
        .sunrise = QDateTime(QDate(2025, 4, 30), QTime(6, 14), makeTimeZone(-7, 0)),
        .noon = QDateTime(QDate(2025, 4, 30), QTime(13, 6), makeTimeZone(-7, 0)),
        .sunset = QDateTime(QDate(2025, 4, 30), QTime(19, 59), makeTimeZone(-7, 0)),
        .civilDusk = QDateTime(QDate(2025, 4, 30), QTime(20, 27), makeTimeZone(-7, 0)),
        .nauticalDusk = QDateTime(QDate(2025, 4, 30), QTime(21, 1), makeTimeZone(-7, 0)),
        .astronomicalDusk = QDateTime(QDate(2025, 4, 30), QTime(21, 38), makeTimeZone(-7, 0)),
    };

    QTest::addRow("New York on 4/30/25") << Sample{
        .date = QDate(2025, 4, 30),
        .firstHour = 1,
        .lastHour = 24,
        .timeZone = makeTimeZone(-4, 0),
        .latitude = 40.712778,
        .longitude = -74.006111,
        .astronomicalDawn = QDateTime(QDate(2025, 4, 30), QTime(4, 10), makeTimeZone(-4, 0)),
        .nauticalDawn = QDateTime(QDate(2025, 4, 30), QTime(4, 49), makeTimeZone(-4, 0)),
        .civilDawn = QDateTime(QDate(2025, 4, 30), QTime(5, 25), makeTimeZone(-4, 0)),
        .sunrise = QDateTime(QDate(2025, 4, 30), QTime(5, 55), makeTimeZone(-4, 0)),
        .noon = QDateTime(QDate(2025, 4, 30), QTime(12, 53), makeTimeZone(-4, 0)),
        .sunset = QDateTime(QDate(2025, 4, 30), QTime(19, 51), makeTimeZone(-4, 0)),
        .civilDusk = QDateTime(QDate(2025, 4, 30), QTime(20, 20), makeTimeZone(-4, 0)),
        .nauticalDusk = QDateTime(QDate(2025, 4, 30), QTime(20, 57), makeTimeZone(-4, 0)),
        .astronomicalDusk = QDateTime(QDate(2025, 4, 30), QTime(21, 36), makeTimeZone(-4, 0)),
    };

    QTest::addRow("Tokyo on 4/30/25") << Sample{
        .date = QDate(2025, 4, 30),
        .firstHour = 0,
        .lastHour = 23,
        .timeZone = makeTimeZone(9, 0),
        .latitude = 35.689722,
        .longitude = 139.692222,
        .astronomicalDawn = QDateTime(QDate(2025, 4, 30), QTime(3, 15), makeTimeZone(9, 0)),
        .nauticalDawn = QDateTime(QDate(2025, 4, 30), QTime(3, 50), makeTimeZone(9, 0)),
        .civilDawn = QDateTime(QDate(2025, 4, 30), QTime(4, 23), makeTimeZone(9, 0)),
        .sunrise = QDateTime(QDate(2025, 4, 30), QTime(4, 50), makeTimeZone(9, 0)),
        .noon = QDateTime(QDate(2025, 4, 30), QTime(11, 38), makeTimeZone(9, 0)),
        .sunset = QDateTime(QDate(2025, 4, 30), QTime(18, 26), makeTimeZone(9, 0)),
        .civilDusk = QDateTime(QDate(2025, 4, 30), QTime(18, 53), makeTimeZone(9, 0)),
        .nauticalDusk = QDateTime(QDate(2025, 4, 30), QTime(19, 26), makeTimeZone(9, 0)),
        .astronomicalDusk = QDateTime(QDate(2025, 4, 30), QTime(20, 1), makeTimeZone(9, 0)),
    };

    QTest::addRow("Beijing on 4/30/25") << Sample{
        .date = QDate(2025, 4, 30),
        .firstHour = 1,
        .lastHour = 24,
        .timeZone = makeTimeZone(8, 0),
        .latitude = 39.906667,
        .longitude = 116.3975,
        .astronomicalDawn = QDateTime(QDate(2025, 4, 30), QTime(3, 32), makeTimeZone(8, 0)),
        .nauticalDawn = QDateTime(QDate(2025, 4, 30), QTime(4, 11), makeTimeZone(8, 0)),
        .civilDawn = QDateTime(QDate(2025, 4, 30), QTime(4, 46), makeTimeZone(8, 0)),
        .sunrise = QDateTime(QDate(2025, 4, 30), QTime(5, 15), makeTimeZone(8, 0)),
        .noon = QDateTime(QDate(2025, 4, 30), QTime(12, 11), makeTimeZone(8, 0)),
        .sunset = QDateTime(QDate(2025, 4, 30), QTime(19, 7), makeTimeZone(8, 0)),
        .civilDusk = QDateTime(QDate(2025, 4, 30), QTime(19, 36), makeTimeZone(8, 0)),
        .nauticalDusk = QDateTime(QDate(2025, 4, 30), QTime(20, 12), makeTimeZone(8, 0)),
        .astronomicalDusk = QDateTime(QDate(2025, 4, 30), QTime(20, 50), makeTimeZone(8, 0)),
    };

    QTest::addRow("Cape Town on 4/30/25") << Sample{
        .date = QDate(2025, 4, 30),
        .firstHour = 1,
        .lastHour = 24,
        .timeZone = makeTimeZone(2, 0),
        .latitude = -33.925278,
        .longitude = 18.423889,
        .astronomicalDawn = QDateTime(QDate(2025, 4, 30), QTime(5, 55), makeTimeZone(2, 0)),
        .nauticalDawn = QDateTime(QDate(2025, 4, 30), QTime(6, 25), makeTimeZone(2, 0)),
        .civilDawn = QDateTime(QDate(2025, 4, 30), QTime(6, 54), makeTimeZone(2, 0)),
        .sunrise = QDateTime(QDate(2025, 4, 30), QTime(7, 20), makeTimeZone(2, 0)),
        .noon = QDateTime(QDate(2025, 4, 30), QTime(12, 43), makeTimeZone(2, 0)),
        .sunset = QDateTime(QDate(2025, 4, 30), QTime(18, 6), makeTimeZone(2, 0)),
        .civilDusk = QDateTime(QDate(2025, 4, 30), QTime(18, 32), makeTimeZone(2, 0)),
        .nauticalDusk = QDateTime(QDate(2025, 4, 30), QTime(19, 1), makeTimeZone(2, 0)),
        .astronomicalDusk = QDateTime(QDate(2025, 4, 30), QTime(19, 31), makeTimeZone(2, 0)),
    };

    QTest::addRow("Sao Paulo on 4/30/25") << Sample{
        .date = QDate(2025, 4, 30),
        .firstHour = 1,
        .lastHour = 24,
        .timeZone = makeTimeZone(-3, 0),
        .latitude = -23.55,
        .longitude = -46.633333,
        .astronomicalDawn = QDateTime(QDate(2025, 4, 30), QTime(5, 9), makeTimeZone(-3, 0)),
        .nauticalDawn = QDateTime(QDate(2025, 4, 30), QTime(5, 36), makeTimeZone(-3, 0)),
        .civilDawn = QDateTime(QDate(2025, 4, 30), QTime(6, 3), makeTimeZone(-3, 0)),
        .sunrise = QDateTime(QDate(2025, 4, 30), QTime(6, 26), makeTimeZone(-3, 0)),
        .noon = QDateTime(QDate(2025, 4, 30), QTime(12, 3), makeTimeZone(-3, 0)),
        .sunset = QDateTime(QDate(2025, 4, 30), QTime(17, 40), makeTimeZone(-3, 0)),
        .civilDusk = QDateTime(QDate(2025, 4, 30), QTime(18, 4), makeTimeZone(-3, 0)),
        .nauticalDusk = QDateTime(QDate(2025, 4, 30), QTime(18, 30), makeTimeZone(-3, 0)),
        .astronomicalDusk = QDateTime(QDate(2025, 4, 30), QTime(18, 57), makeTimeZone(-3, 0)),
    };
}

static bool verifyTransitPoint(const QDateTime &now, const QDateTime &actual, const QDateTime &expected, int tolerance)
{
    const int difference = std::abs(actual.secsTo(expected));
    if (difference > tolerance) {
        qDebug() << now << actual << expected << tolerance;
        return false;
    }
    return true;
}

void SunEventsTest::transitTime()
{
    QFETCH(Sample, sample);

    for (int cycle = -1; cycle <= 1; ++cycle) {
        for (int hour = sample.firstHour; hour <= sample.lastHour; ++hour) {
            const QDateTime dateTime = QDateTime(sample.date, QTime(0, 0), sample.timeZone).addDays(cycle).addSecs(hour * 60 * 60);

            const SunEvents transit(dateTime, sample.latitude, sample.longitude);

            QVERIFY(verifyTransitPoint(dateTime, transit.astronomicalDawn(), sample.astronomicalDawn.addDays(cycle), sample.tolerance));
            QVERIFY(verifyTransitPoint(dateTime, transit.nauticalDawn(), sample.nauticalDawn.addDays(cycle), sample.tolerance));
            QVERIFY(verifyTransitPoint(dateTime, transit.civilDawn(), sample.civilDawn.addDays(cycle), sample.tolerance));
            QVERIFY(verifyTransitPoint(dateTime, transit.sunrise(), sample.sunrise.addDays(cycle), sample.tolerance));
            QVERIFY(verifyTransitPoint(dateTime, transit.solarNoon(), sample.noon.addDays(cycle), sample.tolerance));
            QVERIFY(verifyTransitPoint(dateTime, transit.sunset(), sample.sunset.addDays(cycle), sample.tolerance));
            QVERIFY(verifyTransitPoint(dateTime, transit.civilDusk(), sample.civilDusk.addDays(cycle), sample.tolerance));
            QVERIFY(verifyTransitPoint(dateTime, transit.nauticalDusk(), sample.nauticalDusk.addDays(cycle), sample.tolerance));
            QVERIFY(verifyTransitPoint(dateTime, transit.astronomicalDusk(), sample.astronomicalDusk.addDays(cycle), sample.tolerance));
        }
    }
}

static bool verifyPolarDayRange(QDate begin, QDate end, double latitude, bool expected)
{
    for (QDate date = begin; date <= end; date = date.addDays(1)) {
        const QDateTime dateTime(date, QTime(12, 0), QTimeZone::utc());
        const SunEvents transit(dateTime, latitude, 0.0);
        if (transit.isPolarDay() != expected) {
            qDebug() << date << latitude << transit.isPolarDay() << expected;
            return false;
        }
        if (expected && transit.sunrise().isValid() && transit.sunset().isValid()) {
            qDebug() << date << latitude << transit.sunrise() << transit.sunset();
            return false;
        }
    }
    return true;
}

static bool verifyPolarTwilightRange(QDate begin, QDate end, double latitude, bool expected)
{
    for (QDate date = begin; date <= end; date = date.addDays(1)) {
        const QDateTime dateTime(date, QTime(12, 0), QTimeZone::utc());
        const SunEvents transit(dateTime, latitude, 0.0);
        if (transit.isPolarTwilight() != expected) {
            qDebug() << date << latitude << transit.isPolarTwilight() << expected;
            return false;
        }
    }
    return true;
}

static bool verifyPolarNightRange(QDate begin, QDate end, double latitude, bool expected)
{
    for (QDate date = begin; date <= end; date = date.addDays(1)) {
        const QDateTime dateTime(date, QTime(12, 0), QTimeZone::utc());
        const SunEvents transit(dateTime, latitude, 0.0);
        if (transit.isPolarNight() != expected) {
            qDebug() << date << latitude << transit.isPolarNight() << expected;
            return false;
        }
        if (expected && transit.sunrise().isValid() && transit.sunset().isValid()) {
            qDebug() << date << latitude << transit.sunrise() << transit.sunset();
            return false;
        }
    }
    return true;
}

void SunEventsTest::polarDayNight()
{
    // polar circle (north): polar day from 6th June to 6th July, no polar night
    QVERIFY(verifyPolarDayRange(QDate(2022, 1, 1), QDate(2022, 6, 5), 66.5, false));
    QVERIFY(verifyPolarDayRange(QDate(2022, 6, 6), QDate(2022, 7, 5), 66.5, true));
    QVERIFY(verifyPolarDayRange(QDate(2022, 7, 6), QDate(2022, 12, 31), 66.5, false));
    QVERIFY(verifyPolarNightRange(QDate(2022, 1, 1), QDate(2022, 12, 31), 66.5, false));

    // polar circle (south): same in reverse
    QVERIFY(verifyPolarDayRange(QDate(2021, 1, 6), QDate(2021, 12, 7), -66.5, false));
    QVERIFY(verifyPolarDayRange(QDate(2021, 12, 8), QDate(2022, 1, 4), -66.5, true));
    QVERIFY(verifyPolarDayRange(QDate(2022, 1, 5), QDate(2022, 12, 7), -66.5, false));
    QVERIFY(verifyPolarNightRange(QDate(2022, 1, 1), QDate(2022, 12, 31), -66.5, false));

    // 68°: polar twilight from Dec 9 to Jan 2, no polar night
    QVERIFY(verifyPolarTwilightRange(QDate(2021, 1, 3), QDate(2021, 12, 8), 68.0, false));
    QVERIFY(verifyPolarTwilightRange(QDate(2021, 12, 9), QDate(2022, 1, 2), 68.0, true));
    QVERIFY(verifyPolarTwilightRange(QDate(2022, 1, 3), QDate(2022, 12, 8), 68.0, false));
    QVERIFY(verifyPolarNightRange(QDate(2022, 1, 1), QDate(2022, 12, 31), 68.0, false));

    // -68°: polar twilight from June 8 to July 3, no polar night
    QVERIFY(verifyPolarTwilightRange(QDate(2021, 1, 1), QDate(2021, 6, 7), -68.0, false));
    QVERIFY(verifyPolarTwilightRange(QDate(2021, 6, 8), QDate(2021, 7, 3), -68.0, true));
    QVERIFY(verifyPolarTwilightRange(QDate(2021, 7, 4), QDate(2021, 12, 31), -68.0, false));
    QVERIFY(verifyPolarNightRange(QDate(2022, 1, 1), QDate(2022, 12, 31), -68.0, false));

    // 78.5°: polar night from Nov 11 to Jan 30
    QVERIFY(verifyPolarNightRange(QDate(2021, 1, 31), QDate(2021, 11, 10), 78.5, false));
    QVERIFY(verifyPolarNightRange(QDate(2021, 11, 11), QDate(2022, 1, 30), 78.5, true));
    QVERIFY(verifyPolarNightRange(QDate(2022, 1, 31), QDate(2022, 11, 10), 78.5, false));

    // -78.5°: polar night from May 10 to Aug 2
    QVERIFY(verifyPolarNightRange(QDate(2022, 1, 1), QDate(2022, 5, 9), -78.5, false));
    QVERIFY(verifyPolarNightRange(QDate(2022, 5, 10), QDate(2022, 8, 2), -78.5, true));
    QVERIFY(verifyPolarNightRange(QDate(2022, 8, 3), QDate(2022, 12, 31), -78.5, false));
}

#include "moc_testsunevents.cpp"
