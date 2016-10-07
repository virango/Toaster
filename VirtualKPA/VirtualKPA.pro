#-------------------------------------------------
#
# Project created by QtCreator 2016-07-13T19:18:59
#
#-------------------------------------------------

CONFIG   += debug_and_release
QT       -= gui

TARGET = VirtualKPA
TEMPLATE = lib

DEFINES += VIRTUALKPA_LIBRARY

CONFIG(debug, debug|release) {
    DESTDIR = $$OUT_PWD/debug
} else {
    DESTDIR = $$OUT_PWD/release
}

INCLUDEPATH += $$PWD/../Shared

SOURCES += VirtualKPA.cpp \
    VirtualRig.cpp \
    VirtualModule.cpp \
    VirtualParam.cpp \
    VirtualStringParam.cpp \
    VirtualSingleParam.cpp \
    VirtualMultiParam.cpp \
    VirtualBlobParam.cpp \
    VirtualExtendedParam.cpp \
    VirtualUnknownParam.cpp

HEADERS += VirtualKPA.h\
        virtualkpa_global.h \
    VirtualRig.h \
    VirtualModule.h \
    VirtualParam.h \
    VirtualStringParam.h \
    VirtualSingleParam.h \
    VirtualMultiParam.h \
    VirtualBlobParam.h \
    VirtualExtendedParam.h \
    VirtualUnknownParam.h \
    ../Shared/Utils.h \
    ../Shared/SysExBase.h \
    ../Shared/MidiConsumer.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
