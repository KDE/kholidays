/*
    This file is part of libkholidays.
    Copyright (c) 2004 Allen Winter <winter@kde.org>

    Copyright (c) 1989, 1993
    The Regents of the University of California.  All rights reserved.

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

#include <kglobal.h>
#include <klocale.h>
#include <kdebug.h>

#include "lunarphase.h"

using namespace KHolidays;

LunarPhase::LunarPhase( Hemisphere hemisphere )
{
  mHemisphere = hemisphere;
}

LunarPhase::~LunarPhase()
{
}

void LunarPhase::setHemisphere( Hemisphere hemisphere )
{
  mHemisphere = hemisphere;
}

LunarPhase::Hemisphere LunarPhase::hemisphere() const
{
  return( mHemisphere );
}

QString LunarPhase::hemisphereStr() const
{
  return hemisphereName( mHemisphere );
}

QString LunarPhase::hemisphereName( LunarPhase::Hemisphere hemisphere )
{
  switch( hemisphere ) {
  case Northern:
  default:
    return( i18n( "Northern" ) );
    break;
  case Southern:
    return( i18n( "Southern" ) );
    break;
  }
}

QString LunarPhase::phaseStr( const QDate &date ) const
{
  return phaseName( phase( date ) );
}

QString LunarPhase::phaseName( LunarPhase::Phase phase )
{
  switch ( phase ) {
  case New:
    return( i18n( "New Moon" ) );
    break;
  case Full:
    return( i18n( "Full Moon" ) );
    break;
  case FirstQ:
    return( i18n( "First Quarter Moon" ) );
    break;
  case LastQ:
    return( i18n( "Last Quarter Moon" ) );
    break;
  default:
  case None:
    return( QString::null );
    break;
  }
}

LunarPhase::Phase LunarPhase::phase( const QDate &date ) const
{
  Phase retPhase = None;

  // compute percent-full for the middle of today and yesterday.
  QTime noontime( 12, 0, 0 );
  QDateTime today( date, noontime );
  double todayPer = percentFull( today.toTime_t() );
  QDateTime yesterday( date.addDays(-1), noontime );
  double yesterdayPer = percentFull( yesterday.toTime_t() );

  if ( ( todayPer < 0.50 ) && ( yesterdayPer > 0.50 ) ) {
     retPhase = New;
  } else if ( ( todayPer > 99.50 ) && ( yesterdayPer < 99.50 ) ) {
      retPhase = Full;
  } else {
    // compute percent-full for the start of today.
    QTime sqt( 0, 0, 0 );
    QDateTime start( date, sqt );
    double startPer = percentFull( start.toTime_t() );
    // compute percent-full for the end of today.
    QTime eqt( 23, 59, 59 );
    QDateTime end( date, eqt );
    double endPer = percentFull( end.toTime_t() );

    if ( ( startPer <= 50 ) && ( endPer > 50 ) ) {
      if ( mHemisphere == Northern ) {
        retPhase = FirstQ;
      } else {
        retPhase = LastQ;
      }
    }
    if ( ( endPer <= 50 ) && ( startPer > 50 ) ) {
      if ( mHemisphere == Northern ) {
        retPhase = LastQ;
      } else {
        retPhase = FirstQ;
      }
    }
    // Note: if you want to support crescent and gibbous phases then please
    //  read the source for the original BSD 'pom' program.
  }
  return( retPhase );
}

/*
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software posted to USENET.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/cdefs.h>

/*
 * Phase of the Moon.  Calculates the current phase of the moon.
 * Based on routines from `Practical Astronomy with Your Calculator',
 * by Duffett-Smith.  Comments give the section from the book that
 * particular piece of code was adapted from.
 *
 * -- Keith E. Brandt  VIII 1984
 *
 * Updated to the Third Edition of Duffett-Smith's book, Paul Janzen, IX 1998
 *
 */


#include <ctype.h>
#include <err.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#ifndef PI
#define	PI	  3.14159265358979323846
#endif

/*
 * The EPOCH in the third edition of the book is 1990 Jan 0.0 TDT.
 * In this program, we do not bother to correct for the differences
 * between UTC (as shown by the UNIX clock) and TDT.  (TDT = TAI + 32.184s;
 * TAI-UTC = 32s in Jan 1999.)
 */
#define EPOCH_MINUS_1970        (20 * 365 + 5 - 1) /* 20 years, 5 leaps, back 1 day to Jan 0 */
#define EPSILONg  279.403303    /* solar ecliptic long at EPOCH */
#define RHOg      282.768422    /* solar ecliptic long of perigee at EPOCH */
#define ECCEN     0.016713      /* solar orbit eccentricity */
#define lzero     318.351648    /* lunar mean long at EPOCH */
#define Pzero     36.340410     /* lunar mean long of perigee at EPOCH */
#define Nzero     318.510107    /* lunar mean long of node at EPOCH */

/*
 * percentFull --
 *	return phase of the moon as a percentage of full
 */
double LunarPhase::percentFull( uint tmpt ) const
{
  double N, Msol, Ec, LambdaSol, l, Mm, Ev, Ac, A3, Mmprime;
  double A4, lprime, V, ldprime, D, Nm;

  double days;
  days = ( tmpt - EPOCH_MINUS_1970 * 86400 ) / 86400.0;

  N = 360 * days / 365.242191;                                  /* sec 46 #3 */
  adj360(&N);
  Msol = N + EPSILONg - RHOg;                                   /* sec 46 #4 */
  adj360(&Msol);
  Ec = 360 / PI * ECCEN * sin(degreesToRadians(Msol));          /* sec 46 #5 */
  LambdaSol = N + Ec + EPSILONg;                                /* sec 46 #6 */
  adj360(&LambdaSol);
  l = 13.1763966 * days + lzero;                                /* sec 65 #4 */
  adj360(&l);
  Mm = l - (0.1114041 * days) - Pzero;                          /* sec 65 #5 */
  adj360(&Mm);
  Nm = Nzero - (0.0529539 * days);                              /* sec 65 #6 */
  adj360(&Nm);
  Ev = 1.2739 * sin(degreesToRadians(2*(l - LambdaSol) - Mm));  /* sec 65 #7 */
  Ac = 0.1858 * sin(degreesToRadians(Msol));                    /* sec 65 #8 */
  A3 = 0.37 * sin(degreesToRadians(Msol));
  Mmprime = Mm + Ev - Ac - A3;                                  /* sec 65 #9 */
  Ec = 6.2886 * sin(degreesToRadians(Mmprime));                 /* sec 65 #10 */
  A4 = 0.214 * sin(degreesToRadians(2 * Mmprime));              /* sec 65 #11 */
  lprime = l + Ev + Ec - Ac + A4;                               /* sec 65 #12 */
  V = 0.6583 * sin(degreesToRadians(2 * (lprime - LambdaSol))); /* sec 65 #13 */
  ldprime = lprime + V;                                         /* sec 65 #14 */
  D = ldprime - LambdaSol;                                      /* sec 67 #2 */
  return(50.0 * (1 - cos(degreesToRadians(D))));                /* sec 67 #3 */
}

/*
 * degreesToRadians --
 *	convert degrees to radians
 */
double LunarPhase::degreesToRadians( double degree ) const
{
  return( degree * PI / 180 );
}

/*
 * adj360 --
 *	adjust value so 0 <= degree <= 360
 */
void LunarPhase::adj360( double *degree ) const
{
  for( ;; )
    if( *degree < 0 )
      *degree += 360;
    else if( *degree > 360 )
      *degree -= 360;
    else
      break;
}
