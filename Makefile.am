SUBDIRS=holidays

METASOURCES = AUTO

INCLUDES = -I$(top_srcdir) $(all_includes)

lib_LTLIBRARIES = libkholidays.la

libkholidays_la_LDFLAGS = $(all_libraries) -no-undefined -version-info 1:0:0
libkholidays_la_LIBADD = $(LIB_KIO)
libkholidays_la_SOURCES = kholidays.cpp scanholiday.c parseholiday.h parseholiday.c lunarphase.cpp

#the lex/flex and yacc/bison files are in CVS and NOT generated
#we do this to eliminate the need for those programs
#parseholiday.c:
#	$(YACC) -p kcal -d -o parseholiday.c parseholiday.y
#
#parseholiday.h:
#	$(YACC) -p kcal -d -o parseholiday.c parseholiday.y
#
#scanholiday.c: parseholiday.h
#	$(LEX) -Pkcal -B -oscanholiday.c scanholiday.lex
#
#clean:
#	-rm -f scanholiday.c parseholiday.h parseholiday.c

messages: rc.cpp
	$(XGETTEXT) *.cpp -o $(podir)/libkholidays.pot

include ../admin/Doxyfile.am
