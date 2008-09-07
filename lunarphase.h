/*
  This file is part of the kholidays library.

  Copyright (c) 2004,2007 Allen Winter <winter@kde.org>

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Library General Public
  License as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Library General Public License for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; see the file COPYING.LIB.  If not, write to the
  Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
  Boston, MA 02110-1301, USA.
*/

#ifndef KHOLIDAYS_LUNARPHASE_H
#define KHOLIDAYS_LUNARPHASE_H

#include "kholidays_export.h"
#include <QString>

class QDate;

namespace LibKHolidays {

/**
  Represents and manages a Lunar Phase

  A Lunar Phase can be one of the following:

   + "new": the moon is not visible; or traditionally: first visible
            crescent of the Moon.  For religious purposes, the new
            month begins when the first crescent moon can be seen.
            Thus, it is impossible to be certain in advance of when
            months will begin; in particular, the exact date on which
            Ramadan will begin is not known in advance. In Saudi Arabia,
            observers are sent up in airplanes if the weather is cloudy
            when the new moon is expected.
   + "first quarter": the right 50% of the moon is visible.
   + "full": the moon is fully visible.
   + "last quarter": the left 50% of the moon is visible.

   A very good description of the lunar phases can be read at the Wikipedia,
     http://en.wikipedia.org/wiki/Lunar_phase

   Note that crescent and gibbous phases are not currently supported.
*/
class KHOLIDAYS_EXPORT LunarPhase
{
  public:
    /**
      Phases of the moon, in traditional English notation. The
      phase @c None is used only as an error indicator, for instance
      in phase().
    */
    enum Phase {
      NewMoon,
      FirstQuarter,
      LastQuarter,
      FullMoon,
      None
    };

    /**
      Constructor.
    */

    LunarPhase();

    /**
      Destructor.
    */
    ~LunarPhase();

    /**
       Return the lunar phase for the specified Gregorian date.
       The enum 'None' is returned if one of the supported phases
       does not occur on the date.

       @param date compute the lunar phase for the specified Gregorian date.
    */
    Phase phase( const QDate &date ) const;

    /**
       Return the lunar phase as a text string for the specified date.
       A null string is returned if one of the supported phases does
       not occur on the date.

       @param date compute the lunar phase for the specified Gregorian date.
    */
    QString phaseStr( const QDate &date ) const;

    /**
       Return the string representation of phase.

       @param phase the lunar phase.
    */
    static QString phaseName( Phase phase );

  private:
    /**
       Return the phase of the moon as a percentage of full

       @param t is the time since the Epoch, measured in seconds.

       @return the percent fullness [0,100] of the moon.
    */
    double percentFull( uint t ) const;

    /**
       Convert degrees to radians.

       @param degree degrees to convert.

       @return degrees in radians.
    */
    double degreesToRadians( double degree ) const;

    /**
       Adjust value so that 0 <= degree <= 360.

       @param degree a pointer to the degree value.
    */
    void adj360( double *degree ) const;
};

}

#endif