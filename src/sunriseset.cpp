/*
  This file is part of the kholidays library.

  Adapted from the Javascript found at http://www.esrl.noaa.gov/gmd/grad/solcalc
  which is in the public domain.

  Copyright (c) 2012 Allen Winter <winter@kde.org>

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

#include "sunriseset.h"
#include <cmath>
static const double PI = 3.14159265358979323846;
static const double MaxLat = 89.99;
static const double MaxLong = 179.99;

using namespace KHolidays;
using namespace SunRiseSet;

static double degToRad( double degree )
{
  return ( degree * PI ) / 180.00;
}

static double radToDeg( double rad )
{
  return ( rad * 180.0 ) / PI;
}

//convert Julian Day to centuries since J2000.0.
static double calcTimeJulianCent( int jday )
{
  return ( double( jday ) - 2451545.0 ) / 36525.0;
}

//calculate the mean obliquity of the ecliptic (in degrees)
static double calcMeanObliquityOfEcliptic( double t )
{
  double seconds = 21.448 - t * ( 46.8150 + t * ( 0.00059 - t * 0.001813 ) );
  double e0 = 23.0 + ( 26.0 + ( seconds / 60.0 ) ) / 60.0;
  return e0;  // in degrees
}

//calculate the corrected obliquity of the ecliptic (in degrees)
static double calcObliquityCorrection( double t )
{
  double e0 = calcMeanObliquityOfEcliptic( t );
  double omega = 125.04 - 1934.136 * t;
  double e = e0 + 0.00256 * cos( degToRad( omega ) );
  return e;  // in degrees
}

//calculate the Geometric Mean Longitude of the Sun (in degrees)
static double calcGeomMeanLongSun( double t )
{
  double L0 = 280.46646 + t * ( 36000.76983 + 0.0003032 * t );
  while ( L0 > 360.0 ) {
    L0 -= 360.0;
  }
  while ( L0 < 0.0 ) {
    L0 += 360.0;
  }
  return L0;  // in degrees
}

//calculate the Geometric Mean Anomaly of the Sun (in degrees)
static double calcGeomMeanAnomalySun( double t )
{
  double M = 357.52911 + t * ( 35999.05029 - 0.0001537 * t );
  return M;  // in degrees
}

//calculate the equation of center for the sun (in degrees)
static double calcSunEqOfCenter( double t )
{
  double m = calcGeomMeanAnomalySun( t );
  double mrad = degToRad( m );
  double sinm = sin( mrad );
  double sin2m = sin( mrad + mrad );
  double sin3m = sin( mrad + mrad + mrad );
  double C = sinm * ( 1.914602 - t * ( 0.004817 + 0.000014 * t ) ) +
             sin2m * ( 0.019993 - 0.000101 * t ) + sin3m * 0.000289;
  return C;  // in degrees
}

//calculate the true longitude of the sun (in degrees)
static double calcSunTrueLong( double t )
{
  double l0 = calcGeomMeanLongSun( t );
  double c = calcSunEqOfCenter( t );
  double O = l0 + c;
  return O;  // in degrees
}

//calculate the apparent longitude of the sun (in degrees)
static double calcSunApparentLong( double t )
{
  double o = calcSunTrueLong( t );
  double omega = 125.04 - 1934.136 * t;
  double lambda = o - 0.00569 - 0.00478 * sin( degToRad( omega ) );
  return lambda;  // in degrees
}

//calculate the declination of the sun (in degrees)
static double calcSunDeclination( double t )
{
  double e = calcObliquityCorrection( t );
  double lambda = calcSunApparentLong( t );

  double sint = sin( degToRad( e ) ) * sin( degToRad( lambda ) );
  double theta = radToDeg( asin( sint ) );
  return theta; // in degrees
}

//calculate the eccentricity of earth's orbit (unitless)
static double calcEccentricityEarthOrbit( double t )
{
  double e = 0.016708634 - t * ( 0.000042037 + 0.0000001267 * t );
  return e;  // unitless
}

//calculate the difference between true solar time and mean solar time
//(output: equation of time in minutes of time)
static double calcEquationOfTime( double t )
{
  double epsilon = calcObliquityCorrection( t );
  double l0 = calcGeomMeanLongSun( t );
  double e = calcEccentricityEarthOrbit( t );
  double m = calcGeomMeanAnomalySun( t );

  double y = tan( degToRad( epsilon ) / 2.0 );
  y *= y;

  double sin2l0 = sin( 2.0 * degToRad( l0 ) );
  double sinm  = sin( degToRad( m ) );
  double cos2l0 = cos( 2.0 * degToRad( l0 ) );
  double sin4l0 = sin( 4.0 * degToRad( l0 ) );
  double sin2m  = sin( 2.0 * degToRad( m ) );

  double Etime = y * sin2l0 - 2.0 * e * sinm + 4.0 * e *
                 y * sinm * cos2l0 - 0.5 *
                 y * y * sin4l0 - 1.25 * e * e * sin2m;
  return radToDeg( Etime ) * 4.0; // in minutes of time
}

//calculate the hour angle of the sun at sunrise for the latitude (in radians)
static double calcHourAngleSunrise( double latitude, double solarDec )
{
  double latRad = degToRad( latitude );
  double sdRad = degToRad( solarDec );
  double HAarg = ( cos( degToRad( 90.833 ) ) /
                 ( cos( latRad ) * cos( sdRad ) ) - tan( latRad ) * tan( sdRad ) );
  double HA = acos( HAarg );
  return HA; // in radians (for sunset, use -HA)
}

QTime KHolidays::SunRiseSet::utcSunrise( const QDate &date, double latitude, double longitude )
{
  latitude = qMax( qMin( MaxLat, latitude ), -MaxLat );
  longitude = qMax( qMin( MaxLong, longitude ), -MaxLong );

  double t = calcTimeJulianCent( date.toJulianDay() );
  double eqTime = calcEquationOfTime( t );
  double solarDec = calcSunDeclination( t );
  double hourAngle = calcHourAngleSunrise( latitude, solarDec );
  double delta = longitude + radToDeg( hourAngle );
  QTime timeUTC;
  timeUTC = timeUTC.addSecs( ( 720 - ( 4.0 * delta ) - eqTime ) * 60 );
  return QTime( timeUTC.hour(),
                timeUTC.second() > 29 ? timeUTC.minute() + 1 : timeUTC.minute(),
                0 );
}

QTime KHolidays::SunRiseSet::utcSunset( const QDate &date, double latitude, double longitude )
{
  latitude = qMax( qMin( MaxLat, latitude ), -MaxLat );
  longitude = qMax( qMin( MaxLong, longitude ), -MaxLong );

  double t = calcTimeJulianCent( date.toJulianDay() );
  double eqTime = calcEquationOfTime( t );
  double solarDec = calcSunDeclination( t );
  double hourAngle = -calcHourAngleSunrise( latitude, solarDec );
  double delta = longitude + radToDeg( hourAngle );
  QTime timeUTC;
  timeUTC = timeUTC.addSecs( ( 720 - ( 4.0 * delta ) - eqTime ) * 60 );
  return QTime( timeUTC.hour(),
                timeUTC.second() > 29 ? timeUTC.minute() + 1 : timeUTC.minute(),
                0 );
}
