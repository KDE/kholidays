project(kholidays)

add_definitions(-DKDE_DEFAULT_DEBUG_AREA=5350)

add_subdirectory(holidays)
add_subdirectory(tests)

check_include_files(err.h HAVE_ERR_H)
check_include_files(sys/cdefs.h HAVE_SYS_CDEFS_H)
configure_file(config-kholidays.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config-kholidays.h)

########### next target ###############

set(kholidays_LIB_SRCS 
  kholidays.cpp 
  scanholiday.c 
  parseholiday.h 
  parseholiday.c 
  astroseasons.cpp
  lunarphase.cpp
  zodiac.cpp
)

kde4_add_library(kholidays SHARED ${kholidays_LIB_SRCS})

target_link_libraries(kholidays ${KDE4_KIO_LIBS})

set_target_properties(kholidays PROPERTIES VERSION ${GENERIC_LIB_VERSION} SOVERSION ${GENERIC_LIB_SOVERSION})
install(TARGETS kholidays EXPORT kdepimlibsLibraryTargets ${INSTALL_TARGETS_DEFAULT_ARGS})

########### install files ###############

install( FILES kimap_export.h rfccodecs.h DESTINATION ${INCLUDE_INSTALL_DIR}/kimap  COMPONENT Devel)
~

