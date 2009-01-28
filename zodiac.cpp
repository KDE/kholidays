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

#include "zodiac.h"
#include <QDateTime>
#include <KLocale>

using namespace KHolidays;

Zodiac::Zodiac( ZodiacType type )
{
  mType = type;
}

Zodiac::~Zodiac()
{
}

QString Zodiac::signStr( const QDate &date ) const
{
  return signName( sign( date ) );
}

QString Zodiac::signName( Zodiac::ZodiacSigns sign )
{
  switch ( sign ) {
  case Aries:
    return i18n( "Aries" );
  case Taurus:
    return i18n( "Taurus" );
  case Gemini:
    return i18n( "Gemini" );
  case Cancer:
    return i18n( "Cancer" );
  case Leo:
    return i18n( "Leo" );
  case Virgo:
    return i18n( "Virgo" );
  case Libra:
    return i18n( "Libra" );
  case Scorpio:
    return i18n( "Scorpio" );
  case Sagittarius:
    return i18n( "Sagittarius" );
  case Capricorn:
    return i18n( "Capricorn" );
  case Aquarius:
    return i18n( "Aquarius" );
  case Pisces:
    return i18n( "Pisces" );
  default:
  case None:
    return QString();
  }
}

Zodiac::ZodiacSigns Zodiac::sign( const QDate &date ) const
{
    QDate startdate, enddate;

    switch( mType ) {
    case Tropical:
        startdate = QDate( date.year(), 1, 1 );
        enddate = QDate( date.year(), 1, 19 );
        if ( date >= startdate && date <= enddate ) {
          return Capricorn;
        }

        startdate = enddate.addDays( 1 );
        enddate = startdate.addDays( 29 );
        if ( date >= startdate && date <= enddate ) {
          return Aquarius;
        }

        startdate = enddate.addDays( 1 );
        enddate = QDate( date.year(), 3, 20 );
        if ( date >= startdate && date <= enddate ) {
          return Pisces;
        }

        startdate = enddate.addDays( 1 );  // March 21
        enddate = startdate.addDays( 29 );
        if ( date >= startdate && date <= enddate ) {
          return Aries;
        }

        startdate = enddate.addDays( 1 );
        enddate = startdate.addDays( 30 );
        if ( date >= startdate && date <= enddate ) {
          return Taurus;
        }

        startdate = enddate.addDays( 1 );
        enddate = startdate.addDays( 30 );
        if ( date >= startdate && date <= enddate ) {
          return Gemini;
        }

        startdate = enddate.addDays( 1 );
        enddate = startdate.addDays( 31 );
        if ( date >= startdate && date <= enddate ) {
          return Cancer;
        }

        startdate = enddate.addDays( 1 );
        enddate = startdate.addDays( 30 );
        if ( date >= startdate && date <= enddate ) {
          return Leo;
        }

        startdate = enddate.addDays( 1 );
        enddate = startdate.addDays( 30 );
        if ( date >= startdate && date <= enddate ) {
          return Virgo;
        }

        startdate = enddate.addDays( 1 );
        enddate = startdate.addDays( 29 );
        if ( date >= startdate && date <= enddate ) {
          return Libra;
        }

        startdate = enddate.addDays( 1 );
        enddate = startdate.addDays( 29 );
        if ( date >= startdate && date <= enddate ) {
          return Scorpio;
        }

        startdate = enddate.addDays( 1 );
        enddate = startdate.addDays( 29 );
        if ( date >= startdate && date <= enddate ) {
          return Sagittarius;
        }

        return Capricorn;
        break;

    case Sidereal:
        startdate = QDate( date.year(), 1, 1 );
        enddate = QDate( date.year(), 1, 14 );
        if ( date >= startdate && date <= enddate ) {
          return Sagittarius;
        }

        startdate = enddate.addDays( 1 );
        enddate = startdate.addDays( 28 );
        if ( date >= startdate && date <= enddate ) {
          return Capricorn;
        }

        startdate = enddate.addDays( 1 );
        enddate = QDate( date.year(), 3, 14 );
        if ( date >= startdate && date <= enddate ) {
          return Aquarius;
        }

        startdate = enddate.addDays( 1 );
        enddate = QDate( date.year(), 4, 13 );
        if ( date >= startdate && date <= enddate ) {
          return Pisces;
        }

        startdate = QDate( date.year(), 4, 14 );  // April 14
        enddate = startdate.addDays( 30 );
        if ( date >= startdate && date <= enddate ) {
          return Aries;
        }

        startdate = enddate.addDays( 1 );
        enddate = startdate.addDays( 30 );
        if ( date >= startdate && date <= enddate ) {
          return Taurus;
        }

        startdate = enddate.addDays( 1 );
        enddate = startdate.addDays( 31 );
        if ( date >= startdate && date <= enddate ) {
          return Gemini;
        }

        startdate = enddate.addDays( 1 );
        enddate = startdate.addDays( 30 );
        if ( date >= startdate && date <= enddate ) {
          return Cancer;
        }

        startdate = enddate.addDays( 1 );
        enddate = startdate.addDays( 30 );
        if ( date >= startdate && date <= enddate ) {
          return Leo;
        }

        startdate = enddate.addDays( 1 );
        enddate = startdate.addDays( 30 );
        if ( date >= startdate && date <= enddate ) {
          return Virgo;
        }

        startdate = enddate.addDays( 1 );
        enddate = startdate.addDays( 29 );
        if ( date >= startdate && date <= enddate ) {
          return Libra;
        }

        startdate = enddate.addDays( 1 );
        enddate = startdate.addDays( 28 );
        if ( date >= startdate && date <= enddate ) {
          return Scorpio;
        }

        return Sagittarius;
        break;
    }
    return None;
}

QString Zodiac::signSymbol( Zodiac::ZodiacSigns sign )
{
  switch( sign ) {
  case Aries:
    return i18n( "ram" );
  case Taurus:
    return i18n( "bull" );
  case Gemini:
    return i18n( "twins" );
  case Cancer:
    return i18n( "crab" );
  case Leo:
    return i18n( "lion" );
  case Virgo:
    return i18n( "virgin" );
  case Libra:
    return i18n( "scales" );
  case Scorpio:
    return i18n( "scorpion" );
  case Sagittarius:
    return i18n( "archer" );
  case Capricorn:
    return i18n( "goat" );
  case Aquarius:
    return i18n( "water" );
  case Pisces:
    return i18n( "fish" );
  default:
  case None:
    return QString();
  }
}
