
include(CheckIncludeFiles)

check_include_files(err.h HAVE_ERR_H)
check_include_files(sys/cdefs.h HAVE_SYS_CDEFS_H)

configure_file(config-kholidays.h.cmake ${KHolidays_BINARY_DIR}/src/config-kholidays.h)

set(kholidays_SRCS
  astroseasons.cpp
  holiday.cpp
  holidayregion.cpp
  holidayregionselector.cpp
  lunarphase.cpp
  sunriseset.cpp
  zodiac.cpp
  parsers/plan2/holidayscannerplan.cpp
  parsers/holidayparserdriver.cpp
  parsers/plan2/holidayparserdriverplan.cpp
  parsers/plan2/holidayparserplan.cpp
)

set(kholidays_UI
  holidayregionselector.ui
)

qt5_wrap_ui(kholidays_SRCS ${kholidays_UI})

add_library(KF5Holidays ${kholidays_SRCS})
generate_export_header(KF5Holidays BASE_NAME kholidays)

add_library(KF5::Holidays ALIAS KF5Holidays)

target_include_directories(KF5Holidays INTERFACE "$<INSTALL_INTERFACE:${KF5_INCLUDE_INSTALL_DIR}/KHolidays>")
target_include_directories(KF5Holidays PUBLIC "$<BUILD_INTERFACE:${KHolidays_SOURCE_DIR}/src;${KHolidays_BINARY_DIR}/src>")
target_include_directories(KF5Holidays PUBLIC "$<BUILD_INTERFACE:${KHolidays_SOURCE_DIR}/src/parsers/plan2>")

target_link_libraries(KF5Holidays
    KF5::ItemViews
    KF5::I18n
    KF5::KDELibs4Support
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
  HolidayRegionSelector
  Holidays
  LunarPhase
  Zodiac

  REQUIRED_HEADERS KHolidays_HEADERS
)

install(TARGETS KF5Holidays EXPORT KF5HolidaysTargets ${KF5_INSTALL_TARGETS_DEFAULT_ARGS})

########### next target ###############

if(QT_QTDESIGNER_FOUND)
  set(kholidayswidgets_PART_SRCS)
  kde4_add_widget_files(kholidayswidgets_PART_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/kholidays.widgets)

  kde4_add_plugin(kholidayswidgets ${kholidayswidgets_PART_SRCS})

  target_link_libraries(kholidayswidgets ${KDE4_KIO_LIBS} kholidays)

  install(TARGETS kholidayswidgets DESTINATION ${PLUGIN_INSTALL_DIR}/plugins/designer)
endif()

########### install files ###############
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/kholidays_export.h
    ${KHolidays_HEADERS}
    ${KHolidays_CamelCase_HEADERS}
    DESTINATION ${KF5_INCLUDE_INSTALL_DIR}/KHolidays
    COMPONENT Devel
)
