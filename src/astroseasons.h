/*
    This file is part of the kholidays library.

    SPDX-FileCopyrightText: 2004, 2006-2007 Allen Winter <winter@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef KHOLIDAYS_ASTROSEASONS_H
#define KHOLIDAYS_ASTROSEASONS_H

#include "kholidays_export.h"

class QDate;
class QString;

namespace KHolidays
{
/*!
  \class KHolidays::AstroSeasons
  \inheaderfile KHolidays/AstroSeasons
  \inmodule KHolidays

  \brief Represents and manages the Astronomical Seasons (solstices and equinoxes).

  For the purposes of this class, we sometimes use the shorthand of "Season"
  where we really mean "Astronomical Season".

  An Astronomical Season can be one of the following:
  \list
  \li June solstice
  \li December solstice
  \li March equinox
  \li September equinox
  \endlist

  A very good description of the astronomical seasons can be read at the
  Wikipedia,
     https://en.wikipedia.org/wiki/Seasons

  Note that this class represents the "Astronomical Seasons" and not
  the traditional "Seasons" which vary widely by culture.
*/
class KHOLIDAYS_EXPORT AstroSeasons // krazy:exclude=dpointer
{
public:
    /*!
     * \value JuneSolstice
     * \value DecemberSolstice
     * \value MarchEquinox
     * \value SeptemberEquinox
     * \value None
     */
    enum Season {
        JuneSolstice,
        DecemberSolstice,
        MarchEquinox,
        SeptemberEquinox,
        None,
    };

    /*!
     * Return the Gregorian date on which the season occurs in given year.
     *
     * \a season Season to return a date for
     *
     * \a year Year for which to return the date
     *
     * \since 5.50
     */
    static QDate seasonDate(Season season, int year);

    /*!
       Return the season for the specified Gregorian date.
       The enum 'None' is returned if one of the supported seasons
       does not occur on the date.

       \a date compute the season for the specified Gregorian date.
    */
    static Season seasonAtDate(const QDate &date);

    /*!
       Return the season as a text string for the specified date.
       A null string is returned if one of the supported seasons does
       not occur on the date.

       \a date compute the season for the specified Gregorian date.
    */
    static QString seasonNameAtDate(const QDate &date);

    /*!
       Return the string representation of season.

       \a season astronomical season.
    */
    static QString seasonName(Season season);
};

}

#endif
