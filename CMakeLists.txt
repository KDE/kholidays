cmake_minimum_required(VERSION 3.5)

set(KF_VERSION "5.82.0")
project(KHolidays VERSION ${KF_VERSION})

find_package(ECM 5.82.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})
set(CMAKE_AUTORCC ON)

include(GenerateExportHeader)
include(ECMGenerateHeaders)
include(CMakePackageConfigHelpers)
include(ECMSetupVersion)
include(ECMPoQmTools)
include(FeatureSummary)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)
include(ECMCoverageOption)
include(ECMQtDeclareLoggingCategory)
include(ECMAddQch)
include(ECMGeneratePriFile)
include(KDEGitCommitHooks)

set(KHOLIDAYS_LIB_VERSION ${KF_VERSION})

ecm_setup_version(PROJECT VARIABLE_PREFIX KHOLIDAYS
                        VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/kholidays_version.h"
                        PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF5HolidaysConfigVersion.cmake"
                        SOVERSION 5
)

option(BUILD_QCH "Build API documentation in QCH format (for e.g. Qt Assistant, Qt Creator & KDevelop)" OFF)
add_feature_info(QCH ${BUILD_QCH} "API documentation in QCH format (for e.g. Qt Assistant, Qt Creator & KDevelop)")

########### Find packages ###########
set(REQUIRED_QT_VERSION 5.15.0)
find_package(Qt5 ${REQUIRED_QT_VERSION} CONFIG REQUIRED Core Qml)

remove_definitions(-DQT_NO_CAST_FROM_ASCII -DQT_NO_CAST_TO_ASCII)

########### Targets ###########
add_definitions(-DQT_NO_FOREACH)
add_definitions(-DQT_DISABLE_DEPRECATED_BEFORE=0x050f00)
add_subdirectory(src)

if(BUILD_TESTING)
  add_subdirectory(autotests)
endif()

ecm_install_po_files_as_qm(po)

########### CMake Config Files ###########
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF5Holidays")

if(BUILD_QCH)
  ecm_install_qch_export(
    TARGETS KF5Holidays_QCH
    FILE KF5HolidaysQchTargets.cmake
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
  )
  set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KF5HolidaysQchTargets.cmake\")")
endif()

configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/KF5HolidaysConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/KF5HolidaysConfig.cmake"
  INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR}
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
kde_configure_git_pre_commit_hook(CHECKS CLANG_FORMAT)
