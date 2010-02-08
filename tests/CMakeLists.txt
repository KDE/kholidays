set( EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR} )

include_directories(
	${CMAKE_SOURCE_DIR}/kholidays
)

########### next target ###############

set(testlunar_SRCS testlunar.cpp )


kde4_add_unit_test(testlunar TESTNAME kholidays-testlunar ${testlunar_SRCS})

target_link_libraries(testlunar ${KDE4_KDECORE_LIBS} kholidays ${QT_QTTEST_LIBRARY} ${QT_QTGUI_LIBRARY})

########### next target ###############

set(testseasons_SRCS testseasons.cpp )


kde4_add_unit_test(testseasons TESTNAME kholidays-testseasons ${testseasons_SRCS})

target_link_libraries(testseasons ${KDE4_KDECORE_LIBS} kholidays ${QT_QTTEST_LIBRARY} ${QT_QTGUI_LIBRARY})

########### next target ###############

set(testzodiac_SRCS testzodiac.cpp )


kde4_add_unit_test(testzodiac TESTNAME kholidays-testzodiac ${testzodiac_SRCS})

target_link_libraries(testzodiac ${KDE4_KDECORE_LIBS} kholidays ${QT_QTTEST_LIBRARY})

########### next target ###############

set(testholidayregion_SRCS testholidayregion.cpp )

kde4_add_unit_test(testholidayregion TESTNAME kholidays-testholidayregion ${testholidayregion_SRCS})

target_link_libraries(testholidayregion ${KDE4_KDECORE_LIBS} ${QT_QTGUI_LIBRARY} kholidays ${QT_QTTEST_LIBRARY})

########### next target ###############

#set( EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/tests/ )

set(testparseholiday_SRCS
    testparseholiday.cpp
    ../parsers/holidayparserdriver.cpp
    ../parsers/plan1/holidayparserdriverplanold.cpp
    ../parsers/plan2/holidayparserplan.cpp
    ../parsers/plan2/holidayscannerplan.cpp
    ../parsers/plan2/holidayparserdriverplan.cpp)

kde4_add_unit_test(testparseholiday TESTNAME kholidays-testparseholiday ${testparseholiday_SRCS})

target_link_libraries(testparseholiday ${KDE4_KDECORE_LIBS} kholidays ${QT_QTTEST_LIBRARY} ${QT_QTGUI_LIBRARY})

########### next target ###############

#set(testholiday_SRCS testholiday.cpp )


#kde4_add_unit_test(testholiday TESTNAME kcal-testholiday ${testholiday_SRCS})

#target_link_libraries(testholiday ${KDE4_KDECORE_LIBS} kholidays ${QT_QTTEST_LIBRARY})

########### next target ###############

#set(testus_SRCS testus.cpp )


#kde4_add_unit_test(testus TESTNAME kcal-testus ${testus_SRCS})

#target_link_libraries(testus ${KDE4_KDECORE_LIBS} kholidays ${QT_QTTEST_LIBRARY})
