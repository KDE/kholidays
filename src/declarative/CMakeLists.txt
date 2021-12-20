add_library(kholidaysdeclarativeplugin SHARED kholidaysdeclarativeplugin.cpp holidayregionsmodel.cpp kholidaysdeclarativeplugin.h holidayregionsmodel.h)

target_link_libraries(kholidaysdeclarativeplugin
  Qt${QT_MAJOR_VERSION}::Qml
  Qt${QT_MAJOR_VERSION}::Core
  KF5Holidays
)

install(TARGETS kholidaysdeclarativeplugin DESTINATION ${KDE_INSTALL_QMLDIR}/org/kde/kholidays)
install(FILES qmldir DESTINATION ${KDE_INSTALL_QMLDIR}/org/kde/kholidays)
