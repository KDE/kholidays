
include(CheckIncludeFiles)

check_include_files(err.h HAVE_ERR_H)
check_include_files(sys/cdefs.h HAVE_SYS_CDEFS_H)

configure_file(config-kholidays.h.cmake ${KHolidays_BINARY_DIR}/src/config-kholidays.h)

add_library(KF5Holidays)
add_library(KF5::Holidays ALIAS KF5Holidays)

set_target_properties(KF5Holidays PROPERTIES
  VERSION     ${KHOLIDAYS_VERSION}
  SOVERSION   ${KHOLIDAYS_SOVERSION}
  EXPORT_NAME Holidays
)

target_sources(KF5Holidays PRIVATE
    astroseasons.cpp
    astroseasons.h
    holiday.cpp
    holiday.h
    holiday_p.h
    holidayregion.cpp
    holidayregion.h
    lunarphase.cpp
    lunarphase.h
    parsers/holidayparserdriver.cpp
    parsers/holidayparserdriver_p.h
    parsers/plan2/FlexLexer.h
    parsers/plan2/holidayparserdriverplan.cpp
    parsers/plan2/holidayparserdriverplan_p.h
    parsers/plan2/holidayparserplan.cpp
    parsers/plan2/holidayscannerplan.cpp
    parsers/plan2/holidayscannerplan_p.h
    parsers/qcalendarsystem.cpp
    parsers/qcalendarsystem_p.h
    sunriseset.cpp
    sunriseset.h
    util.h
    zodiac.cpp
    zodiac.h

  ../holidays/holidays.qrc
)

ecm_create_qm_loader(KF5Holidays libkholidays5_qt)

ecm_qt_declare_logging_category(KF5Holidays
    HEADER kholidays_debug.h
    IDENTIFIER KHOLIDAYS_LOG
    CATEGORY_NAME kf.holidays
    DESCRIPTION "KHolidays"
    EXPORT KHOLIDAYS
)

generate_export_header(KF5Holidays BASE_NAME KHolidays)

target_include_directories(KF5Holidays INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF5}/KHolidays>")
target_include_directories(KF5Holidays PUBLIC "$<BUILD_INTERFACE:${KHolidays_SOURCE_DIR}/src;${KHolidays_BINARY_DIR}/src>")
target_include_directories(KF5Holidays PUBLIC "$<BUILD_INTERFACE:${KHolidays_SOURCE_DIR}/src/parsers/plan2>")

target_link_libraries(KF5Holidays PUBLIC Qt5::Core)

ecm_generate_headers(KHolidays_CamelCase_HEADERS
  HEADER_NAMES
  AstroSeasons
  Holiday
  HolidayRegion
  LunarPhase
  SunRiseSet
  Zodiac
  PREFIX KHolidays
  REQUIRED_HEADERS KHolidays_HEADERS
)

install(TARGETS KF5Holidays EXPORT KF5HolidaysTargets ${KF5_INSTALL_TARGETS_DEFAULT_ARGS})

########### install files ###############
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/kholidays_export.h
  ${KHolidays_HEADERS}
  DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5}/KHolidays/kholidays
  COMPONENT Devel
)

install(FILES
  ${KHolidays_CamelCase_HEADERS}
  DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5}/KHolidays/KHolidays
  COMPONENT Devel
)

if(BUILD_QCH)
  ecm_add_qch(
    KF5Holidays_QCH
    NAME KHolidays
    BASE_NAME KF5Holidays
    VERSION ${KF_VERSION}
    ORG_DOMAIN org.kde
    SOURCES # using only public headers, to cover only public API
      ${KHolidays_HEADERS}
    MD_MAINPAGE "${CMAKE_SOURCE_DIR}/README.md"
    LINK_QCHS
      Qt5Core_QCH
    INCLUDE_DIRS
      ${CMAKE_CURRENT_BINARY_DIR}
    BLANK_MACROS
      KHOLIDAYS_EXPORT
    TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
    QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
    COMPONENT Devel
  )
endif()

ecm_generate_pri_file(
  BASE_NAME KHolidays
  LIB_NAME KF5Holidays
  DEPS "widgets"
  FILENAME_VAR PRI_FILENAME
  INCLUDE_INSTALL_DIR ${KDE_INSTALL_INCLUDEDIR_KF5}/KHolidays
)

install(FILES ${PRI_FILENAME} DESTINATION ${ECM_MKSPECS_INSTALL_DIR})

add_subdirectory(declarative)

ecm_qt_install_logging_categories(
    EXPORT KHOLIDAYS
    FILE kholidays.categories
    DESTINATION "${KDE_INSTALL_LOGGINGCATEGORIESDIR}"
)
