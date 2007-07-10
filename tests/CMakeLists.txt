include_directories(
	${CMAKE_SOURCE_DIR}/libkholidays
)

########### next target ###############

set(testlunar_SRCS testlunar.cpp )


kde4_add_unit_test(testlunar TESTNAME kcal-testlunar ${testlunar_SRCS})

target_link_libraries(testlunar ${KDE4_KDECORE_LIBS} kholidays ${QT_QTTEST_LIBRARY})

########### next target ###############

set(testseasons_SRCS testseasons.cpp )


kde4_add_unit_test(testseasons TESTNAME kcal-testseasons ${testseasons_SRCS})

target_link_libraries(testseasons ${KDE4_KDECORE_LIBS} kholidays ${QT_QTTEST_LIBRARY})

########### next target ###############

set(testzodiac_SRCS testzodiac.cpp )


kde4_add_unit_test(testzodiac TESTNAME kcal-testzodiac ${testzodiac_SRCS})

target_link_libraries(testzodiac ${KDE4_KDECORE_LIBS} kholidays ${QT_QTTEST_LIBRARY})
