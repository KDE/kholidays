/*
  This file is part of the kholidays library.

  Copyright (c) 2005-2007 Allen Winter <winter@kde.org>

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

#ifndef KHOLIDAYS_ZODIAC_H
#define KHOLIDAYS_ZODIAC_H

/**
   Represents and manages the Zodiac calendar.
   The Tropical and Sidereal Zodiacs are supported.

   A very good description of the Zodiac calendars can be read at the
   Wikipedia,
     http://en.wikipedia.org/wiki/Zodiac

   Disclaimer: I am by no means a Zodiac expert.  I put together this software
   based on some quick scanning of documents I found on the WWW.  Feel free
   to contact me about this code if you have improvements.

   Sign         Symbol               Birthdates
                          Tropical              Sidereal
   Aries        ram       Mar 21 - Apr 19       Apr 14 - May 14
   Taurus       bull      Apr 20 - May 20       May 15 - Jun 14
   Gemini       twins     May 21 - Jun 20       Jun 15 - Jul 16
   Cancer       crab      Jun 21 - Jul 22       Jul 17 - Aug 16
   Leo          lion      Jul 23 - Aug 22       Aug 17 - Sep 16
   Virgo        virgin    Aug 23 - Sep 22       Sep 17 - Oct 17
   Libra        scale     Sep 23 - Oct 22       Oct 18 - Nov 16
   Scorpio      scorpion  Oct 23 - Nov 21       Nov 17 - Dec 15
   Sagittarius  archer    Nov 22 - Dec 21       Dec 16 - Jan 14
   Capricorn    goat      Dec 22 - Jan 19       Jan 15 - Feb 12
   Aquarius     water     Jan 20 - Feb 18       Feb 13 - Mar 14
   Pisces       fish      Feb 19 - Mar 20       Mar 15 - Apr 13

*/

#include "kholidays_export.h"

#include <QtCore/QSharedDataPointer>

class QDate;
class QString;

namespace KHolidays {

class ZodiacPrivate;

class KHOLIDAYS_EXPORT Zodiac
{
  public:
    enum ZodiacType {
      Tropical,
      Sidereal
    };

    enum ZodiacSigns {
      Aries,
      Taurus,
      Gemini,
      Cancer,
      Leo,
      Virgo,
      Libra,
      Scorpio,
      Sagittarius,
      Capricorn,
      Aquarius,
      Pisces,
      None
    };

    Zodiac( ZodiacType type );
    Zodiac( const Zodiac &other );
    ~Zodiac();

    Zodiac &operator=( const Zodiac &other );

    /**
       Return the Zodiac sign for the specified Gregorian date.
       The enum 'None' is returned if one of the supported signs
       does not occur on the date.

       @param date compute the Zodiac sign for the specified Gregorian date.
    */
    ZodiacSigns signAtDate( const QDate &date ) const;

    /**
       Return the Zodiac sign as a text string for the specified date.
       A null string is returned if one of the supported Zodiac signs does
       not occur on the date.

       @param date compute the Zodiac sign for the specified Gregorian date.
    */
    QString signNameAtDate( const QDate &date ) const;

    /**
       Return the string representation of Zodiac sign.

       @param sign Zodiac sign.
    */
    static QString signName( ZodiacSigns sign );

    /**
       Convert the Zodiac sign to a Zodiac symbol.
    */
    static QString signSymbol( ZodiacSigns sign );

  private:
    QSharedDataPointer<ZodiacPrivate> d;
};

}

#endif

