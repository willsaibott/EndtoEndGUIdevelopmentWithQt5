QT += testlib network xml
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase c++14
CONFIG -= app_bundle

TEMPLATE = app

HEADERS += \
  source/models/client_tests.h \
  source/controllers/master_controller_tests.h \
  source/data/datetime_decorator_tests.h \
  source/data/enumerator_decorator_tests.h \
  source/data/integer_decorator_tests.h \
  source/data/string_decorator_tests.h \
  source/test_suite.h

SOURCES +=  \
  source/controllers/master_controller_tests.cpp \
  source/data/datetime_decorator_tests.cpp \
  source/data/enumerator_decorator_tests.cpp \
  source/data/integer_decorator_tests.cpp \
  source/data/string_decorator_tests.cpp \
  source/main.cpp \
  source/models/client_tests.cpp \
  source/test_suite.cpp

INCLUDEPATH += source \
               ../lib/source

include(../qmake-target-platform.pri)
include(../qmake-destination-path.pri)

DISTFILES += \
  ../qmake-destination-path.pri

DESTDIR     = $$PWD/../binaries/$$DESTINATION_PATH
OBJECTS_DIR = $$PWD/build/$$DESTINATION_PATH/.obj
MOC_DIR     = $$PWD/build/$$DESTINATION_PATH/.moc
RCC_DIR     = $$PWD/build/$$DESTINATION_PATH/.qrc
UI_DIR      = $$PWD/build/$$DESTINATION_PATH/.ui
!build_pass:message(test output dir: $${DESTDIR})

LIBS += -L$$DESTDIR -lcm

