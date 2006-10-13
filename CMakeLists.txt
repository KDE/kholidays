
add_subdirectory( holidays ) 

configure_file (config-libkholidays.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config-libkholidays.h )

########### next target ###############

set(kholidays_LIB_SRCS 
   kholidays.cpp 
   scanholiday.c 
   parseholiday.h 
   parseholiday.c 
   lunarphase.cpp )

kde4_automoc(kholidays ${kholidays_LIB_SRCS})

kde4_add_library(kholidays SHARED ${kholidays_LIB_SRCS})

target_link_libraries(kholidays  ${KDE4_KIO_LIBS} )

set_target_properties(kholidays PROPERTIES VERSION 1.0.0 SOVERSION 1 )
install(TARGETS kholidays  DESTINATION ${LIB_INSTALL_DIR})


########### install files ###############





#original Makefile.am contents follow:

#SUBDIRS=holidays
#
#METASOURCES = AUTO
#
#INCLUDES = -I$(top_srcdir) $(all_includes)
#
#lib_LTLIBRARIES = libkholidays.la
#
#libkholidays_la_LDFLAGS = $(all_libraries) -no-undefined -version-info 1:0:0
#libkholidays_la_LIBADD = $(LIB_KIO)
#libkholidays_la_SOURCES = kholidays.cpp scanholiday.c parseholiday.h parseholiday.c lunarphase.cpp
#
##the lex/flex and yacc/bison files are in CVS and NOT generated
##we do this to eliminate the need for those programs
##parseholiday.c:
##	$(YACC) -p ${KDE4_KCAL_LIBS} -d -o parseholiday.c parseholiday.y
##
##parseholiday.h:
##	$(YACC) -p ${KDE4_KCAL_LIBS} -d -o parseholiday.c parseholiday.y
##
##scanholiday.c: parseholiday.h
##	$(LEX) -Pkcal -B -oscanholiday.c scanholiday.lex
##
##clean:
##	-rm -f scanholiday.c parseholiday.h parseholiday.c
#
#messages: rc.cpp
#	$(XGETTEXT) *.cpp -o $(podir)/libkholidays.pot
#
#include $(top_srcdir)/admin/Doxyfile.am
