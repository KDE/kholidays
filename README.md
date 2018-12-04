# KHolidays #

Dates for holidays and other special events

## Introduction

This library provides a C++ API that determines holiday and other
special events for a geographical region.

## Testing New Holiday Files

put the new file in place under holidays/plan2
edit the holidays/holidays.qrc file accordingly
% cd <builddir>
% make install && QT_LOGGING_RULES="*.debug=true" ./bin/testholidayregion  >& foo.txt
look for lines containing "syntax error" in foo.txt.
fix any such syntax errors and then you can commit


