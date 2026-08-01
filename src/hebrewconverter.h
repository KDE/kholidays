/*
  SPDX-FileCopyrightText: 2003 Jonathan Singer <jsinger@leeta.net>
  SPDX-FileCopyrightText: 2007 Loïc Corbasson <loic.corbasson@gmail.com>
  Calendar routines from Hebrew Calendar by Frank Yellin.

  Copyright (c) 2002-2003 Carlos Moro <cfmoro@correo.uniovi.es>
  Copyright (c) 2002-2003 Hans Petter Bieker <bieker@kde.org>
  SPDX-FileCopyrightText: 2007, 2009, 2010 John Layt <john@layt.net>
  Calendar conversion routines based on Hdate v6, by Amos Shapir 1978 (rev. 1985, 1992)

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "kholidays_export.h"

#include <QDate>

namespace KHolidays
{
class h_date
{
public:
    int hd_day;
    int hd_mon;
    int hd_year;
    int hd_dw;
    int hd_flg;
};

struct KHOLIDAYS_EXPORT HebrewDateResult {
    int year;
    int month;
    int day;
    int day_of_week;

    int hebrew_month_length, secular_month_length;
    bool hebrew_leap_year_p, secular_leap_year_p;
    int kvia;
    int hebrew_day_number;
};

/**
  This class converts dates between the Hebrew and Gregorian (secular)
  calendars.

  @author Loïc Corbasson
 */
class KHOLIDAYS_EXPORT HebrewDate
{
public:
    explicit HebrewDate(const HebrewDateResult &);
    ~HebrewDate();

    static HebrewDate fromSecular(int year, int month, int day);
    static HebrewDate fromHebrew(int year, int month, int day);

    [[nodiscard]] int year() const;
    [[nodiscard]] int month() const;
    [[nodiscard]] int day() const;
    [[nodiscard]] int dayOfWeek() const;

    [[nodiscard]] int hebrewMonthLength() const;
    [[nodiscard]] int secularMonthLength() const;
    [[nodiscard]] bool isOnHebrewLeapYear() const;
    [[nodiscard]] bool isOnSecularLeapYear() const;
    [[nodiscard]] int kvia() const;
    [[nodiscard]] int hebrewDayNumber() const;

private:
    int mYear, mMonth, mDay, mDayOfWeek;
    int mHebrewMonthLength, mSecularMonthLength;
    bool mOnHebrewLeapYear, mOnSecularLeapYear;
    int mKvia, mHebrewDayNumber;
};

/**
  This class is used internally to convert dates between the Hebrew and
  Gregorian (secular) calendars.

  Calendar routines from Hebrew Calendar by Frank Yellin.

  For more information, see “The Comprehensive Hebrew Calendar” by Arthur Spier
  and “Calendrical Calculations” by E. M. Reingold and Nachum Dershowitz,
  or the documentation of Remind by Roaring Penguin Software Inc.

  @author Jonathan Singer
*/
class KHOLIDAYS_EXPORT HebrewConverter
{
    friend class HebrewDate;

public:
    enum HebrewMonths { // NOLINT(readability-enum-initial-value)
        Nissan = 1,
        Iyar,
        Sivan,
        Tamuz,
        Ab,
        Elul,
        Tishrei,
        Cheshvan,
        Kislev,
        Tevet,
        Shvat,
        Adar,
        AdarII,
        AdarI = 12,
    };

    enum SecularMonths {
        January = 1,
        February,
        March,
        April,
        May,
        June,
        July,
        August,
        September,
        October,
        November,
        December,
    };

    static int short_kislev(int year);
    static int long_cheshvan(int year);
    static class h_date *qdateToHebrew(const QDate &date);
    static class h_date *gregorianToHebrew(int y, int m, int d);
    static class h_date *hebrewToGregorian(int y, int m, int d);

private:
    static bool hebrew_leap_year_p(int year);
    static bool gregorian_leap_year_p(int year);

    static long absolute_from_gregorian(int year, int month, int day);
    static long absolute_from_hebrew(int year, int month, int day);

    static void gregorian_from_absolute(long date, int *yearp, int *monthp, int *dayp);
    static void hebrew_from_absolute(long date, int *yearp, int *monthp, int *dayp);

    static int hebrew_months_in_year(int year);
    static int hebrew_month_length(int year, int month);
    static int secular_month_length(int year, int month);

    static long hebrew_elapsed_days(int year);
    static long hebrew_elapsed_days2(int year);
    static int hebrew_year_length(int year);

    static void finish_up(long absolute, int hyear, int hmonth, int syear, int smonth, struct HebrewDateResult *result);

    static void secularToHebrewConversion(int year, int month, int day, struct HebrewDateResult *result);
    static void hebrewToSecularConversion(int year, int month, int day, struct HebrewDateResult *result);
};
}
