# Test apps should be in the bin dir so that add_test can locate them
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR} )

include_directories(
	${CMAKE_SOURCE_DIR}/libkholidays
)

if(KDE4_BUILD_TESTS)

########### next target ###############

set(testlunar_SRCS testlunar.cpp )

kde4_automoc(${testlunar_SRCS})

kde4_add_executable(testlunar NOGUI RUN_UNINSTALLED ${testlunar_SRCS})

target_link_libraries(testlunar ${KDE4_KDECORE_LIBS} kholidays ${QT_QTTEST_LIBRARY})

add_test(kcal-testlunar ${EXECUTABLE_OUTPUT_PATH}/testlunar)

########### next target ###############

set(testseasons_SRCS testseasons.cpp )

kde4_automoc(${testseasons_SRCS})

kde4_add_executable(testseasons NOGUI RUN_UNINSTALLED ${testseasons_SRCS})

target_link_libraries(testseasons ${KDE4_KDECORE_LIBS} kholidays ${QT_QTTEST_LIBRARY})

add_test(kcal-testseasons ${EXECUTABLE_OUTPUT_PATH}/testseasons)

########### next target ###############

set(testzodiac_SRCS testzodiac.cpp )

kde4_automoc(${testzodiac_SRCS})

kde4_add_executable(testzodiac NOGUI RUN_UNINSTALLED ${testzodiac_SRCS})

target_link_libraries(testzodiac ${KDE4_KDECORE_LIBS} kholidays ${QT_QTTEST_LIBRARY})

add_test(kcal-testzodiac ${EXECUTABLE_OUTPUT_PATH}/testzodiac)

########### install files ###############

endif(KDE4_BUILD_TESTS)

