/*
  This file is part of the kholidays library.

  Copyright (c) 2004,2006-2007 Allen Winter <winter@kde.org>

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

#ifndef KHOLIDAYS_ASTROSEASONS_H
#define KHOLIDAYS_ASTROSEASONS_H

/**
  Represents and manages the Astronomical Seasons (solstices and equinoxes).
  For the purposes of this class, we sometimes use the shorthand of "Season"
  where we really mean "Astronomical Season".

  An Astronomical Season can be one of the following:

   - June solstice
   - December solstice
   - March equinox
   - September equinox

   A very good description of the astronomical seasons can be read at the
   Wikipedia,
     http://en.wikipedia.org/wiki/Seasons

   Note that this class represents the "Astronomical Seasons" and not
   the traditional "Seasons" which vary widely by culture.
*/

#include "kholidays_export.h"

class QDate;
class QString;

namespace KHolidays {

class KHOLIDAYS_EXPORT AstroSeasons //krazy:exclude=dpointer
{
  public:

    enum Season {
      JuneSolstice,
      DecemberSolstice,
      MarchEquinox,
      SeptemberEquinox,
      None
    };

    /**
       Return the season for the specified Gregorian date.
       The enum 'None' is returned if one of the supported seasons
       does not occur on the date.

       @param date compute the season for the specified Gregorian date.
    */
    static Season seasonAtDate( const QDate &date );

    /**
       Return the season as a text string for the specified date.
       A null string is returned if one of the supported seasons does
       not occur on the date.

       @param date compute the season for the specified Gregorian date.
    */
    static QString seasonNameAtDate( const QDate &date );

    /**
       Return the string representation of season.

       @param season astronomical season.
    */
    static QString seasonName( Season season );
};

}

#endif

