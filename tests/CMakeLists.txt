
if(KDE4_BUILD_TESTS)

include_directories(
	${CMAKE_SOURCE_DIR}/libkholidays_ng
	${CMAKE_SOURCE_DIR}/libkholidays_ng/tests
	
)


########### next target ###############

set(testlunar_SRCS testlunar.cpp )

kde4_automoc(testlunar ${testlunar_SRCS})

kde4_add_executable(testlunar RUN_UNINSTALLED ${testlunar_SRCS})

target_link_libraries(testlunar kholidays_ng ${KDE4_KDECORE_LIBS} )

########### next target ###############

set(testseason_SRCS testseasons.cpp )

kde4_automoc(testseason ${testseason_SRCS})

kde4_add_executable(testseason RUN_UNINSTALLED ${testseason_SRCS})

target_link_libraries(testseason kholidays_ng ${KDE4_KDECORE_LIBS} )

########### next target ###############

set(testzodiac_SRCS testzodiac.cpp )

kde4_automoc(testzodiac ${testzodiac_SRCS})

kde4_add_executable(testzodiac RUN_UNINSTALLED ${testzodiac_SRCS})

target_link_libraries(testzodiac kholidays_ng ${KDE4_KDECORE_LIBS} )

########### install files ###############

endif(KDE4_BUILD_TESTS)

