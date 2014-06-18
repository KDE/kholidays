/*
    Original version from plan by Thomas Driemeyer <thomas@bitrot.de>

    Adapted for use in KOrganizer by
        Preston Brown <pbrown@kde.org> and
        Reinhold Kainhofer <reinhold@kainhofer.com>

    Portions contributed by
        Peter Littlefield <plittle@sofkin.ca>
        Armin Liebl <liebla@informatik.tu-muenchen.de>
        Efthimios Mavrogeorgiadis <emav@enl.auth.gr>
        Erwin Hugo Achermann <acherman@inf.ethz.ch>

    Major rewrite using Bison C++ skeleton:
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

#include "holidayparserdriverplan_p.h"
#include "holidayscannerplan_p.h"
#include "holidayparserplan.hpp"

#include <sstream>

#include <QFileInfo>

#include <kdebug.h>

#include "holiday_p.h"

#define LAST        99999
#define ANY        -99999
#define BEFORE         -1
#define AFTER           1

using namespace KHolidays;

HolidayParserDriverPlan::HolidayParserDriverPlan( const QString &planFilePath )
                        :HolidayParserDriver( planFilePath ),
                        m_traceParsing( false ),
                        m_traceScanning( false ),
                        m_parseMetadataOnly( false )
{
    QFile holidayFile( filePath() );
    if ( holidayFile.open( QIODevice::ReadOnly ) ) {
        m_scanData = holidayFile.readAll();
        holidayFile.close();
    }
    m_scanner = new HolidayScannerPlan();
    m_scanner->set_debug( m_traceScanning );
    m_parser = new HolidayParserPlan( *this );
    m_parser->set_debug_level( m_traceParsing );
    m_fileToParse = new std::string( filePath().toLocal8Bit().data() );
    parseMetadata();
}

HolidayParserDriverPlan::~HolidayParserDriverPlan()
{
    delete m_parser;
    delete m_scanner;
    delete m_fileToParse;
}

//TODO Figure why it doesn't compile
void HolidayParserDriverPlan::error( const KHolidays::location &errorLocation, const QString &errorMessage )
{
  Q_UNUSED( errorLocation );
  //std::cerr << errorLocation << " : " << errorMessage;  //Doesn't work???
  //kDebug() << errorLocation << " : " << errorMessage;  //Doesn't work???
  kDebug() << errorMessage;
}

void HolidayParserDriverPlan::error( const QString &errorMessage )
{
    kDebug() << errorMessage;
}


void HolidayParserDriverPlan::parse()
{
    // Parse the file using every calendar system in the file
    foreach ( const QString &calendar, m_fileCalendarTypes ) {

        // Cater for events defined in other Calendar Systems where request year could cover 2 or 3 event years
        // Perhaps also parse year before and year after to allow events to span years or shift to other year?
        setParseCalendar( calendar );
        setParseStartEnd();

        // Generate all events for this calendar in the required year(s)
        for ( m_parseYear = m_parseStartYear; m_parseYear <= m_parseEndYear; ++m_parseYear ) {

            m_parseCalendar->setDate( m_parseYearStart, m_parseYear, 1, 1 );
            m_parseYearEaster = easter( m_parseYear );
            m_parseYearPascha = pascha( m_parseYear );

            std::istringstream iss2( std::string( m_scanData.data() ) );
            m_scanner->yyrestart( &iss2 );

            m_parser->parse();
        }

    }
}

void HolidayParserDriverPlan::parseMetadata()
{
    m_parseMetadataOnly = true;
    m_fileCountryCode.clear();
    m_fileLanguageCode.clear();
    m_fileName.clear();
    m_fileDescription.clear();
    m_fileCalendarTypes.clear();
    m_fileCalendarTypes.append( QLatin1String("gregorian") );

    // Default to files internal metadata
    setParseCalendar( QLatin1String("gregorian") );
    m_parseYear = QDate::currentDate().year();
    std::istringstream iss2( std::string( m_scanData.data() ) );
    m_scanner->yyrestart( &iss2 );
    m_parser->parse();
    m_resultList.clear();

    // If not populated, then use filename metadata, this may change later
    // metadata is encoded in filename in form holiday_<region>_<type>_<language>_<name>
    // with region, type and language sub groups separated by -, and with name optional
    QFileInfo file( m_filePath );
    if ( file.exists() ) {
        QStringList metadata = file.fileName().split( QLatin1Char('_') );
        if ( metadata[0] == QLatin1String("holiday") && metadata.count() > 2 ) {
            if ( m_fileCountryCode.isEmpty() ) {
                setFileCountryCode( metadata[1].toUpper() );
            }
            if ( m_fileLanguageCode.isEmpty() ) {
                QStringList language = metadata[2].split( QLatin1Char('-') );
                m_fileLanguageCode = language[0];
                if ( language.count() > 1 ) {
                    setFileLanguageCode( language[0].append( QLatin1Char('_') ).append( language[1].toUpper() ) );
                } else {
                  setFileLanguageCode( language[0] );
                }
            }
            if ( m_fileLanguageCode.isEmpty() && metadata.count() > 3 ) {
                m_fileName = metadata[3];
            }
        }
    }

    m_parseMetadataOnly = false;
}

QString HolidayParserDriverPlan::filePath()
{
    return m_filePath;
}

std::string *HolidayParserDriverPlan::fileToParse() const
{
    return m_fileToParse;
}

/*****************************************
  Calendar and Date convenience routines
******************************************/

// Adjust month numbering for Hebrew civil calendar leap month
int HolidayParserDriverPlan::adjustedMonthNumber( int month )
{
    if ( m_eventCalendarType != QLatin1String("hebrew") ||              // Only adjust Hebrew months
         m_parseCalendar->calendarType() != QLatin1String("hebrew") ||
         !m_parseCalendar->isLeapYear( m_parseYear ) ||  // Only adjust in leap year
         month < 6 ) {                                   // Only adjust from Adar onwards
        return month;
    }

    if ( month == 13 ) { // Adar I
        return 6;
    }

    if ( month == 14 ) { // Adar II
      return 7;
    }

    return month + 1; // Inserting Adar I moves other months up by 1
}

bool HolidayParserDriverPlan::isLeapYear( int year )
{
    return m_parseCalendar->isLeapYear( year );
}

int HolidayParserDriverPlan::parseYear()
{
    return m_parseYear;
}

int HolidayParserDriverPlan::monthsInYear( int year )
{
    QDate tempDate;
    m_parseCalendar->setDate( tempDate, year, 1, 1 );
    return m_parseCalendar->monthsInYear( tempDate );
}

int HolidayParserDriverPlan::daysInMonth( int year, int month )
{
    QDate tempDate;
    m_parseCalendar->setDate( tempDate, year, month, 1 );
    return m_parseCalendar->daysInMonth( tempDate );
}

int HolidayParserDriverPlan::julianDay( int year, int month, int day )
{
    QDate tempDate;
    m_parseCalendar->setDate( tempDate, year, month, day );
    return tempDate.toJulianDay();
}

void HolidayParserDriverPlan::julianDayToDate( int jd, int *year, int *month, int *day )
{
    QDate tempDate = QDate::fromJulianDay( jd );

    if ( year ) {
        *year = m_parseCalendar->year( tempDate );
    }
    if ( month ) {
        *month = m_parseCalendar->month( tempDate );
    }
    if ( day ) {
        *day = m_parseCalendar->day( tempDate );
    }
}

QDate HolidayParserDriverPlan::easter( int year )
{
    if ( m_parseCalendar->calendarType() != QLatin1String("gregorian") ) {
        return QDate();
    }

    // Algorithm taken from Tondering
    // http://www.tondering.dk/claus/cal/node3.html#SECTION003137000000000000000
    int g = year % 19;
    int c = year / 100;
    int h = ( c - ( c / 4 ) - ( ( ( 8 * c ) + 13 ) / 25 ) + ( 19 * g ) + 15 ) % 30;
    int i = h - ( ( h / 28 ) * ( 1 - ( ( 29 / ( h + 1 ) ) * ( ( 21 - g ) / 11 ) ) ) );
    int j = ( year + ( year / 4 ) + i + 2 - c + ( c / 4 ) ) % 7;
    int l = i - j;
    int month = 3 + ( ( l + 40 ) / 44 );
    int day = l + 28 - ( 31 * ( month / 4 ) );

    return QDate::fromJulianDay( julianDay( year, month, day ) );
}


QDate HolidayParserDriverPlan::pascha( int year )
{
    if ( m_parseCalendar->calendarType() == QLatin1String("gregorian") ||
         m_parseCalendar->calendarType() == QLatin1String("julian") ) {
        // Algorithm taken from Tondering
        // http://www.tondering.dk/claus/cal/node3.html#SECTION003137000000000000000
        // Gives Orthodox Easter in the Julian Calendar, need to convert afterwards to Gregorian if needed
        int g = year % 19;
        int i = ( ( 19 * g ) + 15 ) % 30;
        int j = ( year + ( year / 4 ) + i ) % 7;
        int l = i - j;
        int month = 3 + ( ( l + 40 ) / 44 );
        int day = l + 28 - ( 31 * ( month / 4 ) );

        if ( m_parseCalendar->calendarType() == QLatin1String("julian") ) {
            return QDate::fromJulianDay( julianDay( year, month, day ) );
        }

        if ( m_parseCalendar->calendarType() == QLatin1String("gregorian") ) {
            setParseCalendar( QLatin1String("julian") );
            int paschaJd = julianDay( year, month, day );
            setParseCalendar( QLatin1String("gregorian") );
            return QDate::fromJulianDay( paschaJd );
        }
    }

    return QDate();
}


/*************************
 * Calculate jd routines *
 *************************/

// Return the jd of an existing event, assumes unique names and correct order in file
int HolidayParserDriverPlan::julianDayFromEventName( const QString &eventName )
{
    foreach ( const KHolidays::Holiday &thisHoliday, m_resultList ) {
        if ( thisHoliday.text() == eventName ) {
            return thisHoliday.date().toJulianDay();
        }
    }
    return -1;
}

// Return jd of Easter if Gregorian
int HolidayParserDriverPlan::julianDayFromEaster( void )
{
    if ( m_eventCalendarType == QLatin1String("gregorian") ) {
        return m_parseYearEaster.toJulianDay();
    } else {
        error( QLatin1String("Can only use Easter in Gregorian event rule") );
        return -1;
    }
}

// Return jd of Orthodox Easter if Gregorian or Julian
int HolidayParserDriverPlan::julianDayFromPascha( void )
{
    if ( m_eventCalendarType == QLatin1String("gregorian") || m_eventCalendarType == QLatin1String("julian") ) {
        return m_parseYearPascha.toJulianDay();
    } else {
        error( QLatin1String("Can only use Easter in Gregorian or Julian event rule") );
        return -1;
    }
}

// Return jd of weekday from a month/day in parse year
int HolidayParserDriverPlan::julianDayFromMonthDay( int month, int day ) {
    return julianDay( m_parseYear, month, day );
}

// Return jd of weekday relative to a Julian Day number
int HolidayParserDriverPlan::julianDayFromRelativeWeekday( int occurrence, int weekday, int jd )
{
    if ( occurrence == ANY ) {  /* Should never get this, convert to AFTER instead */
        occurrence = AFTER;
    }

    int thisWeekday = m_parseCalendar->dayOfWeek( QDate::fromJulianDay( jd ) );

    /* AFTER actually means on or after */
    /* BEFORE actually means on or before */
    if ( occurrence > 0 ) {
        occurrence = occurrence - 1;
    } else if ( occurrence < 0 && weekday == thisWeekday ) {
        occurrence = occurrence + 1;
    }

    if ( weekday < thisWeekday ) {
        occurrence = occurrence + 1;
    }

    return jd + weekday - thisWeekday + ( occurrence * 7 );
}

// Return jd of weekday occurence in a given month and day in the parse year
int HolidayParserDriverPlan::julianDayFromWeekdayInMonth( int occurrence, int weekday, int month )
{
    if ( occurrence == LAST ) {  // Is weekday on or before last day of month
        return julianDayFromRelativeWeekday( BEFORE, weekday, julianDay( m_parseYear, month, daysInMonth( m_parseYear, month ) ) );
    } else {  // Is nth weekday on or after first day of month
        return julianDayFromRelativeWeekday( occurrence, weekday, julianDay( m_parseYear, month, 1 ) );
    }
}


/****************************************************
 * Set parsed event variables convenience functions *
 ****************************************************/

void  HolidayParserDriverPlan::setFileCountryCode( const QString &countryCode )
{
    m_fileCountryCode = countryCode;
}

void  HolidayParserDriverPlan::setFileLanguageCode( const QString &languageCode )
{
    m_fileLanguageCode = languageCode;
}

void  HolidayParserDriverPlan::setFileName( const QString &name )
{
    m_fileName = name;
}

void  HolidayParserDriverPlan::setFileDescription( const QString &description )
{
    m_fileDescription = description;
}

void  HolidayParserDriverPlan::setEventName( const QString &eventName )
{
    // Assume if setting an event name then is start of new event line, so clear categories
    m_eventCategories.clear();
    m_eventName = eventName;
}

void  HolidayParserDriverPlan::setEventCategory( const QString &category )
{
    m_eventCategories.append( category );
}

void  HolidayParserDriverPlan::setEventCalendarType( const QString &calendarType )
{
    m_eventCalendarType = calendarType;
    if ( m_parseMetadataOnly && !m_fileCalendarTypes.contains( calendarType ) ) {
        m_fileCalendarTypes.append( calendarType );
    }
}

void  HolidayParserDriverPlan::setEventDate( int eventYear, int eventMonth, int eventDay )
{
    m_eventYear = eventYear;
    m_eventMonth = eventMonth;
    m_eventDay = eventDay;
}

void  HolidayParserDriverPlan::setEventDate( int jd )
{
    julianDayToDate( jd, &m_eventYear, &m_eventMonth, &m_eventDay );
}

/********************************************
 * Set event date from event rules routines *
 ********************************************/

/*
 * Set event by weekday (Monday..Sunday). The rule expression is
 * "every <occurrence> <weekday> of <month> plus <offset> days length <duration> days".
 * Occurrence and month can be ANY or LAST, offset and duration are optional.
 */

void HolidayParserDriverPlan::setFromWeekdayInMonth( int occurrence, int weekday, int month, int offset, int duration )
{
    // Don't set if only parsing metadata or calendar for event rule is not the current parse calendar
    if ( m_parseMetadataOnly || m_eventCalendarType != m_parseCalendar->calendarType() ) {
        return;
    }

    int startMonth, endMonth;
    if ( month == LAST ) {
        startMonth = monthsInYear( m_parseYear );
        endMonth = startMonth;
    } else if ( month == ANY ) {
        startMonth = 1;
        endMonth = monthsInYear( m_parseYear );
    } else {
        startMonth = month;
        endMonth = month;
    }

    // Generate all events in the required event month(s)
    for ( int thisMonth = startMonth; thisMonth <= endMonth; ++thisMonth ) {

        if ( m_parseCalendar->isValid( m_parseYear, thisMonth, 1 ) ) {
            int startOccurrence, endOccurrence;
            if ( occurrence == ANY ) {  // Generate 1st through 5th weekdays, assumes no month with > 35 days
                startOccurrence = 1;
                endOccurrence = 5;
            } else {  // Generate just nth or LAST weekday
                startOccurrence = occurrence;
                endOccurrence = occurrence;
            }

            int jdMonthStart = julianDay( m_parseYear, thisMonth, 1 );
            int jdMonthEnd = julianDay( m_parseYear, thisMonth, daysInMonth( m_parseYear, thisMonth ) );

            // Generate each required occurrence of weekday in month, check occurrence actually falls in month
            for ( int thisOccurrence = startOccurrence; thisOccurrence <= endOccurrence; ++thisOccurrence ) {
                int thisJd = julianDayFromWeekdayInMonth( thisOccurrence, weekday, thisMonth );
                if ( thisJd >= jdMonthStart && thisJd <= jdMonthEnd ) {
                    setEvent( thisJd + offset, 0, duration );
                }
            }
        }

    }
}

/*
 * Set event by weekday (Monday..Sunday) relative to a date. The expression is
 * "<weekday> <occurrence> <date> plus <offset> days length <duration> days".
 * Occurrence, month and day can be ANY or LAST, year can be ANY, offset and duration are optional.
 */

void HolidayParserDriverPlan::setFromRelativeWeekday( int occurrence, int weekday, int offset, int duration )
{
    // Don't set if only parsing metadata or calendar for event rule is not the current parse calendar
    if ( m_parseMetadataOnly || m_eventCalendarType != m_parseCalendar->calendarType() ) {
        return;
    }

    int thisYear;
    if ( m_eventYear == ANY ) {  // Generate the parse year
        thisYear = m_parseYear;
    } else {  // Generate a specific event year
        thisYear = m_eventYear;
    }

    int startMonth, endMonth;
    if ( m_eventMonth == LAST ) {  // Generate just the last month
        startMonth = monthsInYear( thisYear );
        endMonth = startMonth;
    } else if ( m_eventMonth == ANY ) {  // Generate every month
        startMonth = 1;
        endMonth = monthsInYear( thisYear );
    } else {  // Generate just the specific event month
        startMonth = m_eventMonth;
        endMonth = m_eventMonth;
    }

    // Generate all events in the required month(s)
    int thisMonth;
    for ( thisMonth = startMonth; thisMonth <= endMonth; ++thisMonth ) {

        int startDay, endDay;
        if ( m_eventDay == LAST ) {  // Generate just the last day in the month
            startDay = daysInMonth( thisYear, thisMonth );
            endDay = startDay;
        } else if ( m_eventDay == ANY ) {  // Generate every day in the month
            startDay = 1;
            endDay = daysInMonth( thisYear, thisMonth );
        } else {  // Generate just the specific event day
            startDay = m_eventDay;
            endDay = m_eventDay;
        }

        // Generate all events on the required day(s)
        for ( int thisDay = startDay; thisDay <= endDay; ++thisDay ) {
            if ( m_parseCalendar->isValid( thisYear, thisMonth, thisDay ) ) {
                int relativeJd = julianDayFromRelativeWeekday( occurrence, weekday, julianDay( thisYear, thisMonth, thisDay ) );
                setEvent( relativeJd + offset, 0, duration );
            }
        }

    }
}

// TODO Figure out how this works :-)
int HolidayParserDriverPlan::conditionalOffset( int year, int month, int day, int condition )
{
    /** The encoding of the condition is:
          8 lower bits: conditions to shift (bit-register, bit 1=mon, ..., bit 7=sun)
          8 higher bits: weekday to shift to (bit-register, bit 1=mon, ..., bit 7=sun)
    */

    int offset = 0;

    QDate tempDate;
    m_parseCalendar->setDate( tempDate, year, month, day );
    int weekday = m_parseCalendar->dayOfWeek( tempDate );

    if ( condition & ( 1 << weekday ) ) {
        /* condition matches -> higher 8 bits contain the possible days to shift to */
        int to = ( condition >> 8 );
        while ( !( to & ( 1 << ( ( weekday + offset ) % 7 ) ) ) && ( offset < 8 ) ) {
            ++offset;
        }
    }

    if ( offset >= 8 ) {
        offset = 0;
    }

    return offset;
}

/*
 * Set event by date. The expression is
 * "<date> plus <offset> days shift <condition> length <duration> days".
 * Occurrence, month and day can be ANY or LAST, year can be ANY, offset and duration are optional.
 */

void HolidayParserDriverPlan::setFromDate( int offset, int condition, int duration )
{
    // Don't set if only parsing metadata or calendar for event rule is not the current parse calendar
    if ( m_parseMetadataOnly || m_eventCalendarType != m_parseCalendar->calendarType() ) {
        return;
    }

    int thisYear;
    if ( m_eventYear == ANY ) {  // Generate the parse year
        thisYear = m_parseYear;
    } else {  // Generate a specific event year
        thisYear = m_eventYear;
    }

    int startMonth, endMonth;
    if ( m_eventMonth == LAST ) {  // Generate just the last month
        startMonth = monthsInYear( thisYear );
        endMonth = startMonth;
    } else if ( m_eventMonth == ANY ) {  // Generate every month
        startMonth = 1;
        endMonth = monthsInYear( thisYear );
    } else {  // Generate just the specific event month
        startMonth = m_eventMonth;
        endMonth = m_eventMonth;
    }

    // Generate all events in the required month(s)
    for ( int thisMonth = startMonth; thisMonth <= endMonth; ++thisMonth ) {

        int startDay, endDay;
        if ( m_eventDay == LAST ) {  // Generate just the last day in the month
            startDay = daysInMonth( thisYear, thisMonth );
            endDay = startDay;
        } else if ( m_eventDay == ANY ) {  // Generate every day in the month
            startDay = 1;
            endDay = daysInMonth( thisYear, thisMonth );
        } else {  // Generate just the specific event day
            startDay = m_eventDay;
            endDay = m_eventDay;
        }

        // Generate all events on the required day(s)
        for ( int thisDay = startDay; thisDay <= endDay; ++thisDay ) {

            if ( m_parseCalendar->isValid( thisYear, thisMonth, thisDay ) ) {
                setEvent( julianDay( thisYear, thisMonth, thisDay ) + offset,
                          conditionalOffset( thisYear, thisMonth, thisDay, condition ), duration );
            }

        }

    }
}

/*
 * Set event relative to Easter. The expression is
 * "EASTER plus <offset> days length <duration> days".
 * Offset and duration are optional.
 */

void HolidayParserDriverPlan::setFromEaster( int offset, int duration )
{
    // Don't set if only parsing metadata or calendar for event rule is not the current parse calendar
    if ( m_parseMetadataOnly || m_eventCalendarType != m_parseCalendar->calendarType() ) {
        return;
    }

    if ( m_eventCalendarType == QLatin1String("gregorian") ) {
        setEvent( m_parseYearEaster.toJulianDay() + offset, 0, duration );
    } else {
        error( QLatin1String("Can only use Easter in Gregorian event rule") );
    }
}

/*
 * Set event relative to Pascha. The expression is
 * "PASCHA plus <offset> days length <duration> days".
 * Offset and duration are optional.
 */

void HolidayParserDriverPlan::setFromPascha( int offset, int duration )
{
    // Don't set if only parsing metadata or calendar for event rule is not the current parse calendar
    if ( m_parseMetadataOnly || m_eventCalendarType != m_parseCalendar->calendarType() ) {
        return;
    }

    if ( m_eventCalendarType == QLatin1String("gregorian") || m_eventCalendarType == QLatin1String("julian") ) {
        setEvent( m_parseYearPascha.toJulianDay(), offset, duration );
    } else {
        error( QLatin1String("Can only use Pascha in Julian and Gregorian event rule") );
    }
}

// Set the event if it falls inside the requested date range
void HolidayParserDriverPlan::setEvent( int jd, int observeOffset, int duration )
{
    // Don't set if only parsing metadata or calendar for event rule is not the current parse calendar
    if ( m_parseMetadataOnly || m_eventCalendarType != m_parseCalendar->calendarType() ) {
        return;
    }

    // Date the holiday will be observed on
    int observeJd = jd + observeOffset;

    if ( m_multidayMode == Holiday::MultidayHolidaysAsSingleEvents ) {
        addHoliday( QDate::fromJulianDay( observeJd ), duration );
    } else { // KHolidays::MultidayHolidaysAsMultipleEvents
        // Create backwards compatible holidays, one incidence per day
        for ( int dd = 0; dd < duration; ++dd ) {
            addHoliday( QDate::fromJulianDay( observeJd + dd ), 1 );
        }
    }
}

void  HolidayParserDriverPlan::addHoliday( const QDate &observedDate, int duration )
{
    // Only set if event falls in requested date range, i.e. either starts or ends during range
    if ( m_parseCalendar->isValid( observedDate ) &&
         observedDate <= m_requestEnd &&
         observedDate.addDays( duration - 1 ) >= m_requestStart ) {
        KHolidays::Holiday holiday;
        holiday.d->mObservedDate = observedDate;
        holiday.d->mDuration = duration;
        holiday.d->mText = m_eventName;
        holiday.d->mShortText = m_eventName;
        if ( m_eventCategories.contains( "public" ) ) {
            holiday.d->mDayType = KHolidays::Holiday::NonWorkday;
        } else {
            holiday.d->mDayType = KHolidays::Holiday::Workday;
        }
        m_resultList.append( holiday );
    }
}
