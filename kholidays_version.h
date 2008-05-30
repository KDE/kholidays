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

#ifndef KHOLIDAYS_KHOLIDAYS_VERSION_H
#define KHOLIDAYS_KHOLIDAYS_VERSION_H

#define LIBKHOLIDAYS_VERSION_STRING "1.3.90"
#define LIBKHOLIDAYS_VERSION_MAJOR 1
#define LIBKHOLIDAYS_VERSION_MINOR 3
#define LIBKHOLIDAYS_VERSION_RELEASE 90

#define LIBKHOLIDAYS_VERSION KDE_MAKE_VERSION( LIBKHOLIDAYS_VERSION_MAJOR, \
                                               LIBKHOLIDAYS_VERSION_MINOR, \
                                               LIBKHOLIDAYS_VERSION_RELEASE )

#define LIBKHOLIDAYS_IS_VERSION( a, b, c ) \
  ( LIBKHOLIDAYS_VERSION >= KDE_MAKE_VERSION( a, b, c ) )

#endif
