add_library(kholidaysdeclarativeplugin SHARED kholidaysdeclarativeplugin.cpp
                                              holidayregionsmodel.cpp)

target_link_libraries(kholidaysdeclarativeplugin Qt5::Qml
                                                 Qt5::Core
                                                 KF5Holidays
)

install(TARGETS kholidaysdeclarativeplugin DESTINATION ${KDE_INSTALL_QMLDIR}/org/kde/kholidays)
install(FILES qmldir DESTINATION ${KDE_INSTALL_QMLDIR}/org/kde/kholidays)
