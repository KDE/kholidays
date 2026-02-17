add_library(KF6Holidays)
add_library(KF6::Holidays ALIAS KF6Holidays)

set_target_properties(
  KF6Holidays
  PROPERTIES
    VERSION
      ${KHOLIDAYS_VERSION}
    SOVERSION
      ${KHOLIDAYS_SOVERSION}
    EXPORT_NAME
      Holidays
)

target_sources(
  KF6Holidays
  PRIVATE
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
    parsers/plan2/holidayscannerplan_p.h
    parsers/qcalendarsystem.cpp
    parsers/qcalendarsystem_p.h
    sunevents_p.h
    sunevents.cpp
    sunevents.h
    sunriseset.cpp
    sunriseset.h
    zodiac.cpp
    zodiac.h
    ../holidays/holidays.qrc
)
bison_target(
    KF6HolidaysParser
    parsers/plan2/holidayparserplan.ypp
    ${CMAKE_CURRENT_BINARY_DIR}/holidayparserplan.cpp
)
flex_target(
    KF6HolidaysLexer
    parsers/plan2/holidayscannerplan.lpp
    ${CMAKE_CURRENT_BINARY_DIR}/holidayscannerplan.cpp
    COMPILE_FLAGS "-i -B"
)
add_flex_bison_dependency(
  KF6HolidaysLexer
  KF6HolidaysParser
)
target_sources(
    KF6Holidays
    PRIVATE
    ${BISON_KF6HolidaysParser_OUTPUTS}
    ${FLEX_KF6HolidaysLexer_OUTPUTS}
)

ecm_create_qm_loader(KF6Holidays libkholidays6_qt)

ecm_qt_declare_logging_category(KF6Holidays
    HEADER kholidays_debug.h
    IDENTIFIER KHOLIDAYS_LOG
    CATEGORY_NAME kf.holidays
    DESCRIPTION "KHolidays"
    EXPORT KHOLIDAYS
)

ecm_generate_export_header(KF6Holidays
    VERSION  ${KF_VERSION}
    USE_VERSION_HEADER
    BASE_NAME KHolidays
    GROUP_BASE_NAME KF
    DEPRECATED_BASE_VERSION 0
    DEPRECATION_VERSIONS 6.15
    EXCLUDE_DEPRECATED_BEFORE_AND_AT ${EXCLUDE_DEPRECATED_BEFORE_AND_AT}
)

target_include_directories(KF6Holidays INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF}/KHolidays>")
target_include_directories(KF6Holidays PUBLIC "$<BUILD_INTERFACE:${KHolidays_SOURCE_DIR}/src/parsers/plan2>")
target_include_directories(KF6Holidays PRIVATE "${CMAKE_BINARY_DIR}/src")

target_link_libraries(KF6Holidays PUBLIC Qt6::Core)

ecm_generate_headers(KHolidays_CamelCase_HEADERS
  HEADER_NAMES
  AstroSeasons
  Holiday
  HolidayRegion
  LunarPhase
  SunEvents
  SunRiseSet
  Zodiac
  PREFIX KHolidays
  REQUIRED_HEADERS KHolidays_HEADERS
)

install(TARGETS KF6Holidays EXPORT KF6HolidaysTargets ${KF_INSTALL_TARGETS_DEFAULT_ARGS})

########### install files ###############
install(
  FILES
    ${CMAKE_CURRENT_BINARY_DIR}/kholidays_export.h
    ${KHolidays_HEADERS}
  DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/KHolidays/kholidays
  COMPONENT Devel
)

install(
  FILES
    ${KHolidays_CamelCase_HEADERS}
  DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/KHolidays/KHolidays
  COMPONENT Devel
)

add_subdirectory(declarative)

ecm_generate_qdoc(KF6Holidays kholidays.qdocconf)

ecm_qt_install_logging_categories(
    EXPORT KHOLIDAYS
    FILE kholidays.categories
    DESTINATION "${KDE_INSTALL_LOGGINGCATEGORIESDIR}"
)
