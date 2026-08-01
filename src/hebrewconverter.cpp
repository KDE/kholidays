/*
  SPDX-FileCopyrightText: 2003 Jonathan Singer <jsinger@leeta.net>
  SPDX-FileCopyrightText: 2007 Loïc Corbasson <loic.corbasson@gmail.com>
  Calendar routines from Hebrew Calendar by Frank Yellin.

  Copyright (c) 2002-2003 Hans Petter Bieker <bieker@kde.org>
  SPDX-FileCopyrightText: 2007, 2009, 2010 John Layt <john@layt.net>
  Calendar conversion routines based on Hdate v6, by Amos Shapir 1978 (rev. 1985, 1992)

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "hebrewconverter.h"

using namespace KHolidays;

// NOLINTBEGIN(readability-isolate-declaration)
HebrewDate::HebrewDate(const HebrewDateResult &d)
    : mYear(d.year)
    , mMonth(d.month)
    , mDay(d.day)
    , mDayOfWeek(d.day_of_week)
    , mHebrewMonthLength(d.hebrew_month_length)
    , mSecularMonthLength(d.secular_month_length)
    , mOnHebrewLeapYear(d.hebrew_leap_year_p)
    , mOnSecularLeapYear(d.secular_leap_year_p)
    , mKvia(d.kvia)
    , mHebrewDayNumber(d.hebrew_day_number)
{
}

HebrewDate::~HebrewDate()
{
}

HebrewDate HebrewDate::fromSecular(int year, int month, int day)
{
    HebrewDateResult result;
    HebrewConverter::secularToHebrewConversion(year, month, day, &result);
    return HebrewDate(result);
}

HebrewDate HebrewDate::fromHebrew(int year, int month, int day)
{
    HebrewDateResult result;
    HebrewConverter::hebrewToSecularConversion(year, month, day, &result);
    return HebrewDate(result);
}

int HebrewDate::year() const
{
    return mYear;
}

int HebrewDate::month() const
{
    return mMonth;
}

int HebrewDate::day() const
{
    return mDay;
}

int HebrewDate::dayOfWeek() const
{
    return mDayOfWeek;
}

int HebrewDate::hebrewMonthLength() const
{
    return mHebrewMonthLength;
}

int HebrewDate::secularMonthLength() const
{
    return mSecularMonthLength;
}

bool HebrewDate::isOnHebrewLeapYear() const
{
    return mOnHebrewLeapYear;
}

bool HebrewDate::isOnSecularLeapYear() const
{
    return mOnSecularLeapYear;
}

int HebrewDate::kvia() const
{
    return mKvia;
}

int HebrewDate::hebrewDayNumber() const
{
    return mHebrewDayNumber;
}

////////////////////////////////////////////////////////////////////////////////

long HebrewConverter::absolute_from_gregorian(int year, int month, int day)
{
    int xyear, day_number;

    xyear = year - 1;
    day_number = day + 31 * (month - 1);
    if (month > 2) {
        day_number -= (23 + (4 * month)) / 10;
        if (gregorian_leap_year_p(year)) {
            day_number++;
        }
    }
    return day_number /* the day number within the current year */
        + 365L * xyear /* days in prior years */
        + (xyear / 4) /* Julian leap years */
        + (-(xyear / 100)) /* deduct century years */
        + (xyear / 400); /* add Gregorian leap years */
}

/* Given a Hebrew date, calculate the number of days since January 0, 0001,
   Gregorian */
long HebrewConverter::absolute_from_hebrew(int year, int month, int day)
{
    long sum = day + hebrew_elapsed_days(year) - 1373429L;
    int i;

    if (month < 7) {
        const int months = hebrew_months_in_year(year);
        for (i = 7; i <= months; ++i) {
            sum += hebrew_month_length(year, i);
        }
        for (i = 1; i < month; ++i) {
            sum += hebrew_month_length(year, i);
        }
    } else {
        for (i = 7; i < month; ++i) {
            sum += hebrew_month_length(year, i);
        }
    }
    return sum;
}

/* Given an absolute date, calculate the gregorian date  */
void HebrewConverter::gregorian_from_absolute(long date, int *yearp, int *monthp, int *dayp)
{
    int year, month, day;

    for (year = date / 366; date >= absolute_from_gregorian(year + 1, 1, 1); ++year) { }

    for (month = 1; (month <= 11) && (date >= absolute_from_gregorian(year, 1 + month, 1)); ++month) { }

    day = 1 + date - absolute_from_gregorian(year, month, 1);
    *yearp = year;
    *monthp = month;
    *dayp = day;
}

/* Given an absolute date, calculate the Hebrew date */
void HebrewConverter::hebrew_from_absolute(long date, int *yearp, int *monthp, int *dayp)
{
    int year, month, day, gyear, gmonth, gday, months;

    gregorian_from_absolute(date, &gyear, &gmonth, &gday);
    year = gyear + 3760;
    while (date >= absolute_from_hebrew(1 + year, 7, 1)) {
        year++;
    }
    months = hebrew_months_in_year(year);
    for (month = 7; date > absolute_from_hebrew(year, month, hebrew_month_length(year, month)); month = 1 + (month % months)) { }
    day = 1 + date - absolute_from_hebrew(year, month, 1);
    *yearp = year;
    *monthp = month;
    *dayp = day;
}

/* Number of months in a Hebrew year */
int HebrewConverter::hebrew_months_in_year(int year)
{
    if (hebrew_leap_year_p(year)) {
        return 13;
    } else {
        return 12;
    }
}

/* Number of days in a Hebrew month */
int HebrewConverter::hebrew_month_length(int year, int month)
{
    switch (month) {
    case Tishrei:
    case Shvat:
    case Nissan:
    case Sivan:
    case Ab:
        return 30;

    case Tevet:
    case Iyar:
    case Tamuz:
    case Elul:
    case AdarII:
        return 29;

    case Cheshvan:
        // 29 days, unless it's a long year.
        if ((hebrew_year_length(year) % 10) == 5) {
            return 30;
        } else {
            return 29;
        }

    case Kislev:
        // 30 days, unless it's a short year.
        if ((hebrew_year_length(year) % 10) == 3) {
            return 29;
        } else {
            return 30;
        }

    case Adar:
        // Adar (non-leap year) has 29 days. Adar I has 30 days.
        if (hebrew_leap_year_p(year)) {
            return 30;
        } else {
            return 29;
        }

    default:
        return 0;
    }
}

/* Number of days in a Julian or gregorian month */
int HebrewConverter::secular_month_length(int year, int month /*, bool julianp */)
{
    switch (month) {
    case January:
    case March:
    case May:
    case July:
    case August:
    case October:
    case December:
        return 31;

    case April:
    case June:
    case September:
    case November:
        return 30;

    case February:
        if (gregorian_leap_year_p(year)) {
            return 29;
        } else {
            return 28;
        }

    default:
        return 0;
    }
}

/* Is it a leap year in the gregorian calendar */
bool HebrewConverter::gregorian_leap_year_p(int year)
{
    if ((year % 4) != 0) {
        return 0;
    }
    if ((year % 400) == 0) {
        return 1;
    }
    if ((year % 100) == 0) {
        return 0;
    }
    return 1;
}

/* Is it a leap year in the Jewish Calendar */
bool HebrewConverter::hebrew_leap_year_p(int year)
{
    switch (year % 19) {
    case 0:
    case 3:
    case 6:
    case 8:
    case 11:
    case 14:
    case 17:
        return 1;
    default:
        return 0;
    }
}

/* Return the number of days from 1 Tishrei 0001 to the beginning of the given
   year. Since this routine gets called frequently with the same year arguments,
   we cache the most recent values. */
#define MEMORY 5
long HebrewConverter::hebrew_elapsed_days(int year)
{
    static int saved_year[MEMORY] = {-1, -1, -1, -1, -1};
    static long saved_value[MEMORY];
    int i;

    for (i = 0; i < MEMORY; ++i) {
        if (year == saved_year[i]) {
            return saved_value[i];
        }
    }
    for (i = 0; i < MEMORY - 1; ++i) {
        saved_year[i] = saved_year[1 + i];
        saved_value[i] = saved_value[1 + i];
    }
    saved_year[MEMORY - 1] = year;
    saved_value[MEMORY - 1] = hebrew_elapsed_days2(year);
    return saved_value[MEMORY - 1];
}

/* Called by hebrew_elapsed_days to make the calculations if the result is not
   in the cache */
long HebrewConverter::hebrew_elapsed_days2(int year)
{
    const long prev_year = year - 1;
    const long months_elapsed = 235L * (prev_year / 19) + /* months in complete cycles so far */
        12L * (prev_year % 19) + /* regular months in this cycle */
        (((prev_year % 19) * 7 + 1) / 19);
    /* leap months in this cycle */
    const long parts_elapsed = 5604 + 13753 * months_elapsed;
    const long day = 1 + 29 * months_elapsed + parts_elapsed / 25920;
    const long parts = parts_elapsed % 25920;
    const int weekday = day % 7;
    const long alt_day = ((parts >= 19440) || (weekday == 2 && (parts >= 9924) && !hebrew_leap_year_p(year))
                          || (weekday == 1 && (parts >= 16789) && hebrew_leap_year_p(prev_year)))
        ? day + 1
        : day;

    switch (alt_day % 7) {
    case 0:
    case 3:
    case 5:
        return 1 + alt_day;
    default:
        return alt_day;
    }
}

/* Number of days in the given Hebrew year */
int HebrewConverter::hebrew_year_length(int year)
{
    return hebrew_elapsed_days(1 + year) - hebrew_elapsed_days(year);
}

/* Fill in the HebrewDateResult structure based on the given secular date */
void HebrewConverter::secularToHebrewConversion(int syear, int smonth, int sday, struct HebrewDateResult *result)
{
    int hyear, hmonth, hday;
    long absolute;

    absolute = absolute_from_gregorian(syear, smonth, sday);

    hebrew_from_absolute(absolute, &hyear, &hmonth, &hday);

    result->year = hyear;
    result->month = hmonth;
    result->day = hday;
    finish_up(absolute, hyear, hmonth, syear, smonth, result);
}

/* Fill in the HebrewDateResult structure based on the given Hebrew date */
void HebrewConverter::hebrewToSecularConversion(int hyear, int hmonth, int hday, struct HebrewDateResult *result)
{
    int syear, smonth, sday;
    long absolute;

    absolute = absolute_from_hebrew(hyear, hmonth, hday);
    gregorian_from_absolute(absolute, &syear, &smonth, &sday);
    result->year = hyear;
    result->month = hmonth;
    result->day = hday;
    finish_up(absolute, hyear, hmonth, syear, smonth, result);
}

/* This is common code for filling up the HebrewDateResult structure */
void HebrewConverter::finish_up(long absolute, int hyear, int hmonth, int syear, int smonth, struct HebrewDateResult *result)
{
    result->hebrew_month_length = hebrew_month_length(hyear, hmonth);
    result->secular_month_length = secular_month_length(syear, smonth);
    result->hebrew_leap_year_p = hebrew_leap_year_p(hyear);
    result->secular_leap_year_p = gregorian_leap_year_p(syear);
    result->kvia = (hebrew_year_length(hyear) % 10) - 3;
    // absolute is -1 on 1/1/0001 Julian
    result->day_of_week = (7 + absolute) % 7;
    result->hebrew_day_number = absolute - absolute_from_hebrew(hyear, 7, 1) + 1;
}

/* constants, in 1/18th of minute */
static const int HOUR = 1080;
static const int DAY = 24 * HOUR;
static const int WEEK = 7 * DAY;
#define M(h, p) ((h) * HOUR + (p))
#define MONTH (DAY + M(12, 793))

static int hebrewDaysElapsed(int y)
{
    int m, nm, dw, s, l;

    l = y * 7 + 1; // no. of leap months
    m = y * 12 + l / 19; // total no. of months
    l %= 19;
    nm = m * MONTH + M(1 + 6, 779); // molad new year 3744 (16BC) + 6 hours
    s = m * 28 + nm / DAY - 2;

    nm %= WEEK;
    dw = nm / DAY;
    nm %= DAY;

    // special cases of Molad Zaken
    if ((l < 12 && dw == 3 && nm >= M(9 + 6, 204)) || (l < 7 && dw == 2 && nm >= M(15 + 6, 589))) {
        s++, dw++;
    }

    /* ADU */
    if (dw == 1 || dw == 4 || dw == 6) {
        s++;
    }
    return s;
}

class h_date *HebrewConverter::hebrewToGregorian(int y, int m, int d)
{
    static class h_date h;
    int s;

    y -= 3744;
    s = hebrewDaysElapsed(y);
    d += s;
    s = hebrewDaysElapsed(y + 1) - s; /* length of year */

    if (s > 365 && m > 6) {
        --m;
        d += 30;
    }
    d += (59 * (m - 1) + 1) / 2; /* regular months */
    /* special cases */
    if (s % 10 > 4 && m > 2) { /* long Heshvan */
        d++;
    }
    if (s % 10 < 4 && m > 3) { /* short Kislev */
        d--;
    }
    // ### HPB: Broken in leap years
    // if (s > 365 && m > 6)  /* leap year */
    //  d += 30;
    d -= 6002;

    y = (d + 36525) * 4 / 146097 - 1;
    d -= y / 4 * 146097 + (y % 4) * 36524;
    y *= 100;

    /* compute year */
    s = (d + 366) * 4 / 1461 - 1;
    d -= s / 4 * 1461 + (s % 4) * 365;
    y += s;
    /* compute month */
    m = (d + 245) * 12 / 367 - 7;
    d -= m * 367 / 12 - 30;
    if (++m >= 12) {
        m -= 12;
        y++;
    }
    h.hd_day = d;
    h.hd_mon = m;
    h.hd_year = y;
    return (&h);
}

int HebrewConverter::long_cheshvan(int year)
{
    QDate first, last;
    const class h_date *gd;

    gd = hebrewToGregorian(year, 1, 1);
    first.setDate(gd->hd_year, gd->hd_mon + 1, gd->hd_day + 1);

    gd = hebrewToGregorian(year + 1, 1, 1);
    last.setDate(gd->hd_year, gd->hd_mon + 1, gd->hd_day + 1);

    return (first.daysTo(last) % 10 == 5);
}

int HebrewConverter::short_kislev(int year)
{
    QDate first, last;
    const class h_date *gd;

    gd = hebrewToGregorian(year, 1, 1);
    first.setDate(gd->hd_year, gd->hd_mon + 1, gd->hd_day + 1);

    gd = hebrewToGregorian(year + 1, 1, 1);
    last.setDate(gd->hd_year, gd->hd_mon + 1, gd->hd_day + 1);

    return (first.daysTo(last) % 10 == 3);
}

class h_date *HebrewConverter::gregorianToHebrew(int y, int m, int d)
{
    static class h_date h;
    int s;

    if ((m -= 2) <= 0) {
        m += 12;
        y--;
    }
    /* no. of days, Julian calendar */
    d += 365 * y + y / 4 + 367 * m / 12 + 5968;
    /* Gregorian calendar */
    d -= y / 100 - y / 400 - 2;
    h.hd_dw = (d + 1) % 7;

    /* compute the year */
    y += 16;
    s = hebrewDaysElapsed(y);
    m = hebrewDaysElapsed(y + 1);
    while (d >= m) { /* computed year was underestimated */
        s = m;
        y++;
        m = hebrewDaysElapsed(y + 1);
    }
    d -= s;
    s = m - s; /* size of current year */
    y += 3744;

    h.hd_flg = s % 10 - 4;

    /* compute day and month */
    if (d >= s - 236) { /* last 8 months are regular */
        d -= s - 236;
        m = d * 2 / 59;
        d -= (m * 59 + 1) / 2;
        m += 4;
        if (s > 365 && m <= 5) { /* Adar of Meuberet */
            m += 8;
        }
    } else {
        /* first 4 months have 117-119 days */
        s = 114 + s % 10;
        m = d * 4 / s;
        d -= (m * s + 3) / 4;
    }

    h.hd_day = d;
    h.hd_mon = m;
    h.hd_year = y;
    return (&h);
}

class h_date *HebrewConverter::qdateToHebrew(const QDate &date)
{
    class h_date *sd;

    sd = gregorianToHebrew(date.year(), date.month(), date.day());
    ++sd->hd_mon;
    ++sd->hd_day;

    return sd;
}
// NOLINTEND(readability-isolate-declaration)
