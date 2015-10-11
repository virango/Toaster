#-------------------------------------------------
#
# Project created by QtCreator 2015-05-01T08:29:05
#
#-------------------------------------------------

QT       -= core gui
TARGET = RtMidi
TEMPLATE = lib
CONFIG += staticlib debug_and_release

CONFIG(debug, debug|release) {
    DESTDIR = $$OUT_PWD/debug
} else {
    DESTDIR = $$OUT_PWD/release
}

win32:DEFINES += __WINDOWS_MM__
unix:DEFINES += __UNIX_JACK__ \
                __LINUX_ALSA__

SOURCES += RtMidi.cpp
HEADERS += RtMidi.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
