QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase c++14
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  \
  source/models/client_tests.cpp

INCLUDEPATH += source
