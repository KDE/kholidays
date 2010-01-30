/*
    This file is part of the kholidays library.

    Copyright 2010 John Layt <john@layt.net>

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

#ifndef KHOLIDAYS_HOLIDAYPARSERDRIVERPLANOLD_P_H
#define KHOLIDAYS_HOLIDAYPARSERDRIVERPLANOLD_P_H

#include "../holidayparserdriver_p.h"

namespace KHolidays {

/**
 * HolidayParserDriverPlanOld implementation class
 *
 * Implements the standard driver interface for parsing Plan holiday files as
 * used from KDE 4.0 to KDE SC 4.4.  Mostly kept for reference and parallel
 * testing.
 *
 * @internal Private, for internal use only
 */
class HolidayParserDriverPlanOld : public HolidayParserDriver
{
public:

    /**
     * Constructor of old Plan file parser driver
     *
     * @param filePath full path to holiday file
     */
    HolidayParserDriverPlanOld( const QString &planFilename );

    /**
     * Destructor.
     */
    ~HolidayParserDriverPlanOld();

    /**
     * Standard error message handling
     *
     * @param errorMessage error message to log
     */
    void error( const QString &errorMessage );

protected:
    /**
     * Actually parse the file, old plan format implementation
     */
    void parse();

    /**
     * Parse the file for metadata only and populate the metadata variables
     */
    void parseMetadata();
};

}

#endif // KHOLIDAYS_HOLIDAYPARSERDRIVERPLANOLD_P_H
