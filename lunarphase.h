/*
    This file is part of libkholidays.
    Copyright (c) 2004 Allen Winter <winter@kde.org>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation; either version 2 of the
    License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    In addition, as a special exception, the copyright holders give
    permission to link the code of this program with any edition of
    the Qt library by Trolltech AS, Norway (or with modified versions
    of Qt that use the same license as Qt), and distribute linked
    combinations including the two.  You must obey the GNU General
    Public License in all respects for all of the code used other than
    Qt.  If you modify this file, you may extend this exception to
    your version of the file, but you are not obligated to do so.  If
    you do not wish to do so, delete this exception statement from
    your version.
*/

#ifndef KHOLIDAYS_LUNARPHASE_H
#define KHOLIDAYS_LUNARPHASE_H

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

   In the southern hemisphere the order of the phases is reversed.
   So, to be accurate we need to know the hemisphere.

   Note that crescent and gibbous phases are not currently supported.
*/

#include <qstring.h>
#include <qdatetime.h>

#include <time.h>

namespace KHolidays {

class LunarPhase
{
  public:
    enum Phase { New,  FirstQ, LastQ, Full, None };
    enum Hemisphere { Northern,  Southern };

    LunarPhase( Hemisphere hemisphere = Northern );
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
      Set the hemisphere.

      @param hemisphere Hemisphere
   */
    void setHemisphere( Hemisphere hemisphere = Northern );

    /**
       Return the hemisphere.
    */
    Hemisphere hemisphere() const;

    /**
       Return hemisphere as a clear text string.
    */
    QString hemisphereStr() const;

    /**
       Return the string representation of hemisphere.
    */
    static QString hemisphereName( Hemisphere hemisphere );

    /**
       Return the string representation of phase.

       @parm phase the lunar phase.
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

    Hemisphere mHemisphere;
};

}

#endif


