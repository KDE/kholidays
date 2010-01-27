project(kholidays)

add_definitions(-DKDE_DEFAULT_DEBUG_AREA=5350)

add_subdirectory(holidays)
add_subdirectory(tests)

check_include_files(err.h HAVE_ERR_H)
check_include_files(sys/cdefs.h HAVE_SYS_CDEFS_H)
configure_file(config-kholidays.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config-kholidays.h)

########### next target ###############

set(kholidays_LIB_SRCS
  astroseasons.cpp
  holiday.cpp
  holidayregion.cpp
  lunarphase.cpp
  zodiac.cpp
  parsers/holidayparserdriver.cpp
  parsers/plan1/holidayparserdriverplanold.cpp
  parsers/plan1/scanholiday.c
  parsers/plan1/parseholiday.c
)

kde4_add_library(kholidays SHARED ${kholidays_LIB_SRCS})

target_link_libraries(kholidays ${KDE4_KIO_LIBS})

set_target_properties(kholidays PROPERTIES VERSION ${GENERIC_LIB_VERSION} SOVERSION ${GENERIC_LIB_SOVERSION})
install(TARGETS kholidays EXPORT kdepimlibsLibraryTargets ${INSTALL_TARGETS_DEFAULT_ARGS})

########### install files ###############

install(FILES kholidays_export.h astroseasons.h holiday.h holidayregion.h holidays.h lunarphase.h zodiac.h DESTINATION ${INCLUDE_INSTALL_DIR}/kholidays COMPONENT Devel)
