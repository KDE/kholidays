include(ECMMarkAsTest)

find_package(Qt5Test CONFIG REQUIRED)

########### next target ###############

set(testlunar_SRCS testlunar.cpp)

add_executable(testlunar ${testlunar_SRCS})
add_test(NAME testlunar COMMAND testlunar)
ecm_mark_as_test(testlunar)
target_link_libraries(testlunar KF5Holidays Qt5::Test)

########### next target ###############

set(testseasons_SRCS testseasons.cpp)

add_executable(testseasons ${testseasons_SRCS})
add_test(NAME testseasons COMMAND testseasons)
ecm_mark_as_test(testseasons)
target_link_libraries(testseasons KF5Holidays Qt5::Test)

########### next target ###############

set(testsunriseset_SRCS testsunriseset.cpp)

add_executable(testsunriseset ${testsunriseset_SRCS})
add_test(NAME testsunriseset COMMAND testsunriseset)
ecm_mark_as_test(testsunriseset)
target_link_libraries(testsunriseset KF5Holidays Qt5::Test)

########### next target ###############

set(testzodiac_SRCS testzodiac.cpp)

add_executable(testzodiac ${testzodiac_SRCS})
add_test(NAME testzodiac COMMAND testzodiac)
ecm_mark_as_test(testzodiac)
target_link_libraries(testzodiac KF5Holidays Qt5::Test)

########### next target ###############

set(testholidayregion_SRCS testholidayregion.cpp)

add_executable(testholidayregion ${testholidayregion_SRCS})
add_test(NAME testholidayregion COMMAND testholidayregion)
set_target_properties(testholidayregion PROPERTIES COMPILE_FLAGS -DKDESRCDIR="\\"${CMAKE_CURRENT_SOURCE_DIR}/\\"")

ecm_mark_as_test(testholidayregion)
target_link_libraries(testholidayregion KF5Holidays Qt5::Test)
