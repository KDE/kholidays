INCLUDES = -I$(top_srcdir)/libkholidays_ng $(all_includes)

check_PROGRAMS = testlunar testseasons testzodiac

METASOURCES = AUTO

testlunar_SOURCES = testlunar.cpp
testlunar_LDFLAGS = $(all_libraries) $(KDE_RPATH)
testlunar_LDADD = ../libkholidays_ng.la

testseasons_SOURCES = testseasons.cpp
testseasons_LDFLAGS = $(all_libraries) $(KDE_RPATH)
testseasons_LDADD = ../libkholidays_ng.la

testzodiac_SOURCES = testzodiac.cpp
testzodiac_LDFLAGS = $(all_libraries) $(KDE_RPATH)
testzodiac_LDADD = ../libkholidays_ng.la

TESTFILES = 

check-local: testlunar
	$(srcdir)/testlunar > RESULT; \
	diff RESULT data/testlunar.answers; \
	rm -f RESULT;

check-local: testseasons
	$(srcdir)/testseasons > RESULT; \
	diff RESULT data/testseasons.answers; \
	rm -f RESULT;

check-local: testzodiac
	$(srcdir)/testzodiac > RESULT; \
	diff RESULT data/testzodiac.answers; \
	rm -f RESULT;
