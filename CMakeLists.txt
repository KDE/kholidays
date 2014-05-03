cmake_minimum_required(VERSION 2.8.12)

project(KHolidays)

# ECM setup
find_package(ECM 0.0.12 CONFIG REQUIRED)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(GenerateExportHeader)
include(ECMGenerateHeaders)
include(ECMGeneratePriFile)
include(ECMPackageConfigHelpers)
include(ECMSetupVersion)
include(FeatureSummary)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDEFrameworkCompilerSettings)


# FIXME: Do we want the same versions in kdepimlibs and kf5?
set(KF5_VERSION "4.98.0")

ecm_setup_version(${KF5_VERSION} VARIABLE_PREFIX KHOLIDAYS
                        VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/kholidays_version.h"
                        PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF5HolidaysConfigVersion.cmake"
                        SOVERSION 5
)

########### Find packages ###########
find_package(KF5ItemViews ${KF5_VERSION} CONFIG REQUIRED)
find_package(KF5KDELibs4Support ${KF5_VERSION} CONFIG REQUIRED)

find_package(Qt5Designer NO_MODULE)
set_package_properties(Qt5Designer PROPERTIES
   PURPOSE "Required to build the Qt Designer plugins"
   TYPE OPTIONAL
)


########### Targets ###########
add_subdirectory(src)
add_subdirectory(autotests)
add_subdirectory(holidays)

########### CMake Config Files ###########
set(CMAKECONFIG_INSTALL_DIR "${CMAKECONFIG_INSTALL_PREFIX}/KF5Holidays")

ecm_configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/KF5HolidaysConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/KF5HolidaysConfig.cmake"
  INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/KF5HolidaysConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/KF5HolidaysConfigVersion.cmake"
  DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
  COMPONENT Devel
)

install(EXPORT KF5HolidaysTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}" FILE KF5HolidaysTargets.cmake NAMESPACE KF5::)

install(FILES
   ${CMAKE_CURRENT_BINARY_DIR}/kholidays_version.h
  DESTINATION ${KF5_INCLUDE_INSTALL_DIR} COMPONENT Devel
)

if ("${CMAKE_BINARY_DIR}" STREQUAL "${KHolidays_BINARY_DIR}")
  feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
endif()
