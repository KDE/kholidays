SUBDIRS=holidays

METASOURCES = AUTO

INCLUDES = -I$(top_srcdir) $(all_includes)

lib_LTLIBRARIES = libkholidays.la

libkholidays_la_LDFLAGS = $(all_libraries) -no-undefined -version-info 1:0:0
libkholidays_la_LIBADD = $(LIB_KIO)
libkholidays_la_SOURCES = holidays.cpp scanholiday.c parseholiday.h parseholiday.c

parseholiday.c: $(top_srcdir)/libkholidays/parseholiday.y
	$(YACC) -p kcal -d -o parseholiday.c $(top_srcdir)/libkholidays/parseholiday.y

parseholiday.h: $(top_srcdir)/libkholidays/parseholiday.y
	$(YACC) -p kcal -d -o parseholiday.c $(top_srcdir)/libkholidays/parseholiday.y

scanholiday.c: parseholiday.h $(top_srcdir)/libkholidays/scanholiday.lex
	$(LEX) -Pkcal -B -oscanholiday.c $(top_srcdir)/libkholidays/scanholiday.lex

clean:
	-rm -f scanholiday.c parseholiday.h parseholiday.c
