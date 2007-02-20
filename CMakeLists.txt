
add_subdirectory( holidays )

check_include_files(malloc.h HAVE_MALLOC_H)
check_include_files(err.h HAVE_ERR_H)
configure_file (config-libkholidays.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config-libkholidays.h )

########### next target ###############

set(kholidays_LIB_SRCS 
   kholidays.cpp 
   scanholiday.c 
   parseholiday.h 
   parseholiday.c 
   lunarphase.cpp )

kde4_automoc(${kholidays_LIB_SRCS})

kde4_add_library(kholidays SHARED ${kholidays_LIB_SRCS})

target_link_libraries(kholidays  ${KDE4_KIO_LIBS} )

set_target_properties(kholidays PROPERTIES VERSION ${GENERIC_LIB_VERSION} SOVERSION ${GENERIC_LIB_SOVERSION} )
install(TARGETS kholidays  DESTINATION ${LIB_INSTALL_DIR})
