#-------------------------------------------------
#
# Project created by QtCreator 2020-04-23T14:53:14
#
#-------------------------------------------------
QT       += sql
QT       -= gui
TEMPLATE = lib

TARGET = cm

CONFIG += c++14


DEFINES += LIB_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        source/controllers/command_controller.cpp \
        source/controllers/idatabase_controller.cpp \
        source/controllers/master_controller.cpp \
        source/controllers/navigation_controller.cpp \
        source/data/data_decorator.cpp \
        source/data/datetime_decorator.cpp \
        source/data/entity.cpp \
        source/data/enumerator_decorator.cpp \
        source/data/integer_decorator.cpp \
        source/data/string_decorator.cpp \
        source/framework/command.cpp \
        source/models/address.cpp \
        source/models/appointment.cpp \
        source/models/client.cpp \
        source/models/contact.cpp

HEADERS += \
        source/controllers/command_controller.h \
        source/controllers/idatabase_controller.h \
        source/controllers/master_controller.h \
        source/controllers/navigation_controller.h \
        source/data/data_decorator.h \
        source/data/datetime_decorator.h \
        source/data/entity.h \
        source/data/entity_collection.h \
        source/data/enumerator_decorator.h \
        source/data/integer_decorator.h \
        source/data/string_decorator.h \
        source/models/address.h \
        source/models/appointment.h \
        source/models/client.h \
        source/framework/command.h \
        source/lib_global.h \
        source/models/contact.h

INCLUDEPATH += source

unix {
    target.path = /usr/lib
    INSTALLS += target
}

!build_pass:message(lib project dir: $${PWD} )

include(../qmake-target-platform.pri)
include(../qmake-destination-path.pri)

DESTDIR     = $$PWD/../binaries/$$DESTINATION_PATH
OBJECTS_DIR = $$PWD/../build/$$DESTINATION_PATH/.obj
MOC_DIR     = $$PWD/../build/$$DESTINATION_PATH/.moc
RCC_DIR     = $$PWD/../build/$$DESTINATION_PATH/.qrc
UI_DIR      = $$PWD/../build/$$DESTINATION_PATH/.ui
!build_pass:message(lib output dir: $${DESTDIR})
