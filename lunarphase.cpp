/*
  This file is part of the kholidays library.

  Copyright (c) 2004,2007 Allen Winter <winter@kde.org>

  Copyright (c) 1989, 1993  //krazy:exclude=copyright
  The Regents of the University of California.  All rights reserved.

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

#include "lunarphase.h"
#include <config-kholidays.h>

#include <KDebug>
#include <KGlobal>
#include <KLocale>

#include <QDateTime>

using namespace LibKHolidays;

LunarPhase::LunarPhase()
{
}

LunarPhase::~LunarPhase()
{
}

QString LunarPhase::phaseStr( const QDate &date ) const
{
  return phaseName( phase( date ) );
}

QString LunarPhase::phaseName( LunarPhase::Phase phase )
{
  switch ( phase ) {
  case NewMoon:
    return( i18n( "New Moon" ) );
  case FullMoon:
    return( i18n( "Full Moon" ) );
  case FirstQuarter:
    return( i18n( "First Quarter Moon" ) );
  case LastQuarter:
    return( i18n( "Last Quarter Moon" ) );
  default:
  case None:
    return QString();
  }
}

LunarPhase::Phase LunarPhase::phase( const QDate &date ) const
{
  Phase retPhase = None;

  // compute percent-full for the middle of today and yesterday.
  QTime anytime( 0, 0, 0 );
  QDateTime today( date, anytime, Qt::UTC );
  double todayPer = percentFull( today.toTime_t() ) + 0.5;

  if ( static_cast<int>( todayPer ) == 100 ) {
    retPhase = FullMoon;
    //kDebug() << date << " todayPer: " << todayPer << " " << phaseName( retPhase );
  } else if ( static_cast<int>( todayPer ) == 0 ) {
    retPhase = NewMoon;
    //kDebug() << date << " todayPer: " << todayPer << " " << phaseName( retPhase );
  } else {
    QDateTime tomorrow( date.addDays( 1 ), anytime, Qt::UTC );
    double tomorrowPer = percentFull( tomorrow.toTime_t() );

    if ( static_cast<int>( todayPer ) == 50 ) {
      retPhase = ( tomorrowPer > todayPer ) ? FirstQuarter : LastQuarter;
      //kDebug() << date
      //         << " tomorrowPer: " << tomorrowPer
      //         << " " << phaseName( retPhase );
    } else {
      //kDebug() << date
      //         << " todayPer: " << todayPer
      //         << " tomorrowPer: " << tomorrowPer
      //         << " " << phaseName( None );
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

#ifdef HAVE_SYS_CDEFS_H
#include <sys/cdefs.h>
#endif

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
#ifdef HAVE_ERR_H
#include <err.h>
#endif
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

  N = 360 * days / 365.242191;                                 /* sec 46 #3 */
  adj360( &N );
  Msol = N + EPSILONg - RHOg;                                  /* sec 46 #4 */
  adj360( &Msol );
  Ec = 360 / PI * ECCEN * sinl( degreesToRadians( Msol ) );    /* sec 46 #5 */
  LambdaSol = N + Ec + EPSILONg;                               /* sec 46 #6 */
  adj360( &LambdaSol );
  l = 13.1763966 * days + lzero;                               /* sec 65 #4 */
  adj360( &l );
  Mm = l - ( 0.1114041 * days ) - Pzero;                       /* sec 65 #5 */
  adj360( &Mm );
  Nm = Nzero - ( 0.0529539 * days );                           /* sec 65 #6 */
  adj360( &Nm );
  Ev = 1.2739 * sinl( degreesToRadians( 2 * ( l - LambdaSol ) - Mm ) ); /* sec 65 #7 */
  Ac = 0.1858 * sinl( degreesToRadians( Msol ) );              /* sec 65 #8 */
  A3 = 0.37 * sinl( degreesToRadians( Msol ) );
  Mmprime = Mm + Ev - Ac - A3;                                 /* sec 65 #9 */
  Ec = 6.2886 * sinl( degreesToRadians( Mmprime ) );           /* sec 65 #10 */
  A4 = 0.214 * sinl( degreesToRadians( 2 * Mmprime ) );        /* sec 65 #11 */
  lprime = l + Ev + Ec - Ac + A4;                              /* sec 65 #12 */
  V = 0.6583 * sinl( degreesToRadians( 2 * ( lprime - LambdaSol ) ) );/* sec 65 #13 */
  ldprime = lprime + V;                                        /* sec 65 #14 */
  D = ldprime - LambdaSol;                                     /* sec 67 #2 */
  D = 50.0 * ( 1 - cosl( degreesToRadians( D ) ) );            /* sec 67 #3 */
  return D;
}

/*
 * degreesToRadians --
 *	convert degrees to radians
 */
double LunarPhase::degreesToRadians( double degree ) const
{
  return ( degree * PI ) / 180.00;
}

/*
 * adj360 --
 *	adjust value so 0 <= degree <= 360
 */
void LunarPhase::adj360( double *degree ) const
{
  for ( ;; ) {
    if ( *degree < 0 ) {
      *degree += 360;
    } else if ( *degree > 360 ) {
      *degree -= 360;
    } else {
      break;
    }
  }
}
