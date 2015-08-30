
include(CheckIncludeFiles)

check_include_files(err.h HAVE_ERR_H)
check_include_files(sys/cdefs.h HAVE_SYS_CDEFS_H)

configure_file(config-kholidays.h.cmake ${KHolidays_BINARY_DIR}/src/config-kholidays.h)

set(kholidays_SRCS
  astroseasons.cpp
  holiday.cpp
  holidayregion.cpp
  lunarphase.cpp
  sunriseset.cpp
  zodiac.cpp
  parsers/holidayparserdriver.cpp
  parsers/qcalendarsystem.cpp
  parsers/plan2/holidayscannerplan.cpp
  parsers/plan2/holidayparserdriverplan.cpp
  parsers/plan2/holidayparserplan.cpp
)

add_library(KF5Holidays ${kholidays_SRCS})
generate_export_header(KF5Holidays BASE_NAME kholidays)

add_library(KF5::Holidays ALIAS KF5Holidays)

target_include_directories(KF5Holidays INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF5}/KHolidays>")
target_include_directories(KF5Holidays PUBLIC "$<BUILD_INTERFACE:${KHolidays_SOURCE_DIR}/src;${KHolidays_BINARY_DIR}/src>")
target_include_directories(KF5Holidays PUBLIC "$<BUILD_INTERFACE:${KHolidays_SOURCE_DIR}/src/parsers/plan2>")

target_link_libraries(KF5Holidays
PUBLIC
    Qt5::Test
)

set_target_properties(KF5Holidays PROPERTIES
    VERSION ${KHOLIDAYS_VERSION_STRING}
    SOVERSION ${KHOLIDAYS_SOVERSION}
    EXPORT_NAME Holidays
)

ecm_generate_headers(KHolidays_CamelCase_HEADERS
  HEADER_NAMES
  AstroSeasons
  Holiday
  HolidayRegion
  LunarPhase
  Zodiac
  PREFIX KHolidays
  REQUIRED_HEADERS KHolidays_HEADERS
)

install(TARGETS KF5Holidays EXPORT KF5HolidaysTargets ${KF5_INSTALL_TARGETS_DEFAULT_ARGS})

########### install files ###############
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/kholidays_export.h
    ${KHolidays_HEADERS}
    ${KHolidays_CamelCase_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5}/KHolidays/kholidays
    COMPONENT Devel
)

install(FILES
    ${KHolidays_CamelCase_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5}/KHolidays/KHolidays
    COMPONENT Devel
)

ecm_generate_pri_file(BASE_NAME KHolidays LIB_NAME KF5KHolidays DEPS "widgets" FILENAME_VAR PRI_FILENAME  INCLUDE_INSTALL_DIR ${KDE_INSTALL_INCLUDEDIR_KF5}/KHolidays)

install(FILES ${PRI_FILENAME} DESTINATION ${ECM_MKSPECS_INSTALL_DIR})
