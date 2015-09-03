cmake_minimum_required(VERSION 2.8.12)

project(KHolidays)

# ECM setup
find_package(ECM 5.12.0 CONFIG REQUIRED)
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


set(KF5_VERSION "5.12.0")
set(KHOLIDAYS_LIB_VERSION "4.80.0")

ecm_setup_version(${KHOLIDAYS_LIB_VERSION} VARIABLE_PREFIX KHOLIDAYS
                        VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/kholidays_version.h"
                        PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF5HolidaysConfigVersion.cmake"
                        SOVERSION 5
)

########### Find packages ###########
set(REQUIRED_QT_VERSION 5.3.0)
find_package(Qt5 ${REQUIRED_QT_VERSION} CONFIG REQUIRED Test)

remove_definitions(-DQT_NO_CAST_FROM_ASCII -DQT_NO_CAST_TO_ASCII)

########### Targets ###########
add_subdirectory(src)

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()

add_subdirectory(holidays)

########### CMake Config Files ###########
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF5Holidays")

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
  DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5} COMPONENT Devel
)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
