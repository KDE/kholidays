/*
    This file is part of libkholidays.
    Copyright (c) 2005-2006 Allen Winter <winter@kde.org>

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

#include <kglobal.h>
#include <klocale.h>
#include <kdebug.h>

#include "zodiac.h"

using namespace LibKHolidays;

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
      return( i18n( "Aries" ) );
      break;
  case Taurus:
      return( i18n( "Taurus" ) );
      break;
  case Gemini:
      return( i18n( "Gemini" ) );
      break;
  case Cancer:
      return( i18n( "Cancer" ) );
      break;
  case Leo:
      return( i18n( "Leo" ) );
      break;
  case Virgo:
      return( i18n( "Virgo" ) );
      break;
  case Libra:
      return( i18n( "Libra" ) );
      break;
  case Scorpio:
      return( i18n( "Scorpio" ) );
      break;
  case Sagittarius:
      return( i18n( "Sagittarius" ) );
      break;
  case Capricorn:
      return( i18n( "Capricorn" ) );
      break;
  case Aquarius:
      return( i18n( "Aquarius" ) );
      break;
  case Pisces:
      return( i18n( "Pisces" ) );
      break;
  default:
  case None:
      return( QString::null );
      break;
  }
}

Zodiac::ZodiacSigns Zodiac::sign( const QDate &date ) const
{
    QDate startdate, enddate;

    switch( mType ) {
    case Tropical:
        startdate = QDate( date.year(), 1, 1 );
        enddate = QDate( date.year(), 1, 19 );
        if ( date >= startdate && date <= enddate )return( Capricorn );

        startdate = enddate.addDays( 1 );
        enddate = startdate.addDays( 29 );
        if ( date >= startdate && date <= enddate )return( Aquarius );

        startdate = enddate.addDays( 1 );
        enddate = QDate( date.year(), 3, 20 );
        if ( date >= startdate && date <= enddate )return( Pisces );

        startdate = enddate.addDays( 1 );  // March 21
        enddate = startdate.addDays( 29 );
        if ( date >= startdate && date <= enddate )return( Aries );

        startdate = enddate.addDays( 1 );
        enddate = startdate.addDays( 30 );
        if ( date >= startdate && date <= enddate )return( Taurus );

        startdate = enddate.addDays( 1 );
        enddate = startdate.addDays( 30 );
        if ( date >= startdate && date <= enddate )return( Gemini );

        startdate = enddate.addDays( 1 );
        enddate = startdate.addDays( 31 );
        if ( date >= startdate && date <= enddate )return( Cancer );

        startdate = enddate.addDays( 1 );
        enddate = startdate.addDays( 30 );
        if ( date >= startdate && date <= enddate )return( Leo );

        startdate = enddate.addDays( 1 );
        enddate = startdate.addDays( 30 );
        if ( date >= startdate && date <= enddate )return( Virgo );

        startdate = enddate.addDays( 1 );
        enddate = startdate.addDays( 29 );
        if ( date >= startdate && date <= enddate )return( Libra );

        startdate = enddate.addDays( 1 );
        enddate = startdate.addDays( 29 );
        if ( date >= startdate && date <= enddate )return( Scorpio );

        startdate = enddate.addDays( 1 );
        enddate = startdate.addDays( 29 );
        if ( date >= startdate && date <= enddate )return( Sagittarius );

        return( Capricorn );
        break;

    case Sidereal:
        startdate = QDate( date.year(), 1, 1 );
        enddate = QDate( date.year(), 1, 14 );
        if ( date >= startdate && date <= enddate )return( Sagittarius );

        startdate = enddate.addDays( 1 );
        enddate = startdate.addDays( 28 );
        if ( date >= startdate && date <= enddate )return( Capricorn );

        startdate = enddate.addDays( 1 );
        enddate = QDate( date.year(), 3, 14 );
        if ( date >= startdate && date <= enddate )return( Aquarius );

        startdate = enddate.addDays( 1 );
        enddate = QDate( date.year(), 4, 13 );
        if ( date >= startdate && date <= enddate )return( Pisces );

        startdate = QDate( date.year(), 4, 14 );  // April 14
        enddate = startdate.addDays( 30 );
        if ( date >= startdate && date <= enddate )return( Aries );

        startdate = enddate.addDays( 1 );
        enddate = startdate.addDays( 30 );
        if ( date >= startdate && date <= enddate )return( Taurus );

        startdate = enddate.addDays( 1 );
        enddate = startdate.addDays( 31 );
        if ( date >= startdate && date <= enddate )return( Gemini );

        startdate = enddate.addDays( 1 );
        enddate = startdate.addDays( 30 );
        if ( date >= startdate && date <= enddate )return( Cancer );

        startdate = enddate.addDays( 1 );
        enddate = startdate.addDays( 30 );
        if ( date >= startdate && date <= enddate )return( Leo );

        startdate = enddate.addDays( 1 );
        enddate = startdate.addDays( 30 );
        if ( date >= startdate && date <= enddate )return( Virgo );

        startdate = enddate.addDays( 1 );
        enddate = startdate.addDays( 29 );
        if ( date >= startdate && date <= enddate )return( Libra );

        startdate = enddate.addDays( 1 );
        enddate = startdate.addDays( 28 );
        if ( date >= startdate && date <= enddate )return( Scorpio );

        return( Sagittarius );
        break;
    }
    return( None );
}

QString Zodiac::signSymbol( Zodiac::ZodiacSigns sign )
{
    switch( sign ) {
  case Aries:
      return( i18n( "ram" ) );
      break;
  case Taurus:
      return( i18n( "bull" ) );
      break;
  case Gemini:
      return( i18n( "twins" ) );
      break;
  case Cancer:
      return( i18n( "crab" ) );
      break;
  case Leo:
      return( i18n( "lion" ) );
      break;
  case Virgo:
      return( i18n( "virgin" ) );
      break;
  case Libra:
      return( i18n( "scales" ) );
      break;
  case Scorpio:
      return( i18n( "scorpion" ) );
      break;
  case Sagittarius:
      return( i18n( "archer" ) );
      break;
  case Capricorn:
      return( i18n( "goat" ) );
      break;
  case Aquarius:
      return( i18n( "water" ) );
      break;
  case Pisces:
      return( i18n( "fish" ) );
      break;
  default:
  case None:
      return( QString::null );
      break;
  }
}
