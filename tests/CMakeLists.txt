set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})

include_directories(${CMAKE_SOURCE_DIR}/kholidays)

########### next target ###############

set(testlunar_SRCS testlunar.cpp)

kde4_add_unit_test(testlunar TESTNAME kholidays-testlunar ${testlunar_SRCS})

target_link_libraries(testlunar
  kholidays
  ${KDE4_KDECORE_LIBS}
  ${QT_QTGUI_LIBRARY}
  ${QT_QTTEST_LIBRARY}
)

########### next target ###############

set(testseasons_SRCS testseasons.cpp)

kde4_add_unit_test(testseasons TESTNAME kholidays-testseasons ${testseasons_SRCS})

target_link_libraries(testseasons
  kholidays
  ${KDE4_KDECORE_LIBS}
  ${QT_QTGUI_LIBRARY}
  ${QT_QTTEST_LIBRARY}
)

########### next target ###############

set(testsunriseset_SRCS testsunriseset.cpp)

kde4_add_unit_test(testsunriseset TESTNAME kholidays-testsunriseset ${testsunriseset_SRCS})

target_link_libraries(testsunriseset
  kholidays
  ${KDE4_KDECORE_LIBS}
  ${QT_QTGUI_LIBRARY}
  ${QT_QTTEST_LIBRARY}
)

########### next target ###############

set(testzodiac_SRCS testzodiac.cpp)

kde4_add_unit_test(testzodiac TESTNAME kholidays-testzodiac ${testzodiac_SRCS})

target_link_libraries(testzodiac
  kholidays
  ${KDE4_KDECORE_LIBS}
  ${QT_QTTEST_LIBRARY}
)

########### next target ###############

set(testholidayregion_SRCS testholidayregion.cpp)

kde4_add_unit_test(testholidayregion TESTNAME kholidays-testholidayregion ${testholidayregion_SRCS})

target_link_libraries(testholidayregion
  kholidays
  ${KDE4_KDECORE_LIBS}
  ${QT_QTGUI_LIBRARY}
  ${QT_QTTEST_LIBRARY}
)
