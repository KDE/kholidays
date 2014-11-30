/*
  This file is part of the kholidays library.

  Copyright (c) 2001 Cornelius Schumacher <schumacher@kde.org>
  Copyright (c) 2004 Allen Winter <winter@kde.org>
  Copyright (c) 2008 David Jarvie <djarvie@kde.org>
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

#include "holiday.h"
#include "holiday_p.h"

#include <QtCore/QDateTime>
#include <QtCore/QFile>
#include <QtCore/QSharedData>

using namespace KHolidays;

Holiday::Holiday()
  : d( new HolidayPrivate )
{
}

Holiday::Holiday( const Holiday &other )
  : d( other.d )
{
}

Holiday::~Holiday()
{
}

Holiday &Holiday::operator=( const Holiday &other )
{
  if ( &other != this ) {
    d = other.d;
  }

  return *this;
}

bool Holiday::operator<( const Holiday &rhs ) const
{
  return d->mObservedDate < rhs.d->mObservedDate;
}

bool Holiday::operator>( const Holiday &rhs ) const
{
  return d->mObservedDate > rhs.d->mObservedDate;
}

QDate Holiday::observedStartDate() const
{
  return d->mObservedDate;
}

QDate Holiday::observedEndDate() const
{
  return d->mObservedDate.addDays( d->mDuration - 1 );
}

int Holiday::duration() const
{
  return d->mDuration;
}

QString Holiday::name() const
{
  return d->mName;
}

QString Holiday::description() const
{
  return d->mDescription;
}

Holiday::DayType Holiday::dayType() const
{
  return d->mDayType;
}
