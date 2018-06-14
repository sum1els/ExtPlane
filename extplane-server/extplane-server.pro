TEMPLATE = lib
CONFIG += staticlib c++11

# Needed for windows mxe build (hope this doesn't break anything..)
DESTDIR = $$PWD

QT       += core network
QT       -= gui

CONFIG += warn_off

INCLUDEPATH += $$PWD/../util/

SOURCES += tcpserver.cpp \
    tcpclient.cpp \
    datarefprovider.cpp \
    datarefs/dataref.cpp \
    datarefs/floatdataref.cpp \
    datarefs/floatarraydataref.cpp \
    datarefs/intdataref.cpp \
    datarefs/doubledataref.cpp \
    datarefs/intarraydataref.cpp \
    datarefs/datadataref.cpp

HEADERS += \
    tcpserver.h \
    tcpclient.h \
    datarefprovider.h \
    datarefs/dataref.h \
    datarefs/floatdataref.h \
    datarefs/floatarraydataref.h \
    datarefs/intdataref.h \
    datarefs/doubledataref.h \
    datarefs/intarraydataref.h \
    datarefs/datadataref.h \
    ../util/console.h

QMAKE_CLEAN += extplane.xpl
