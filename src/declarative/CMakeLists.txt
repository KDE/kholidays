ecm_add_qml_module(kholidaysdeclarativeplugin URI "org.kde.kholidays")

target_sources(kholidaysdeclarativeplugin PRIVATE
  kholidaysdeclarativeplugin.cpp
  holidayregionsmodel.cpp
  kholidaysdeclarativeplugin.h
  holidayregionsmodel.h
)

target_link_libraries(kholidaysdeclarativeplugin
  Qt${QT_MAJOR_VERSION}::Qml
  Qt${QT_MAJOR_VERSION}::Core
  KF6Holidays
)

ecm_finalize_qml_module(kholidaysdeclarativeplugin DESTINATION ${KDE_INSTALL_QMLDIR})
