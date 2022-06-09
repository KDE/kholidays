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

ecm_generate_export_header(KF5Holidays 
    VERSION  ${KF_VERSION}
    BASE_NAME KHolidays
    GROUP_BASE_NAME KF
    DEPRECATED_BASE_VERSION 0
    DEPRECATION_VERSIONS 5.95
    EXCLUDE_DEPRECATED_BEFORE_AND_AT ${EXCLUDE_DEPRECATED_BEFORE_AND_AT}
)

target_include_directories(KF5Holidays INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF}/KHolidays>")
target_include_directories(KF5Holidays PUBLIC "$<BUILD_INTERFACE:${KHolidays_SOURCE_DIR}/src;${KHolidays_BINARY_DIR}/src>")
target_include_directories(KF5Holidays PUBLIC "$<BUILD_INTERFACE:${KHolidays_SOURCE_DIR}/src/parsers/plan2>")

target_link_libraries(KF5Holidays PUBLIC Qt${QT_MAJOR_VERSION}::Core)

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
  DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/KHolidays/kholidays
  COMPONENT Devel
)

install(FILES
  ${KHolidays_CamelCase_HEADERS}
  DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/KHolidays/KHolidays
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
      Qt${QT_MAJOR_VERSION}Core_QCH
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
  INCLUDE_INSTALL_DIR ${KDE_INSTALL_INCLUDEDIR_KF}/KHolidays
)

install(FILES ${PRI_FILENAME} DESTINATION ${ECM_MKSPECS_INSTALL_DIR})

add_subdirectory(declarative)

ecm_qt_install_logging_categories(
    EXPORT KHOLIDAYS
    FILE kholidays.categories
    DESTINATION "${KDE_INSTALL_LOGGINGCATEGORIESDIR}"
)
