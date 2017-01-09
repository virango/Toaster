#-------------------------------------------------
#
# Project created by QtCreator 2015-05-01T08:29:05
#
#-------------------------------------------------

QT       -= core gui
TARGET = RtMidi
TEMPLATE = lib
CONFIG += staticlib debug_and_release
unix:QMAKE_CXXFLAGS += -std=c++11
macx:QMAKE_CXXFLAGS += -stdlib=libc++

CONFIG(debug, debug|release) {
    DESTDIR = $$OUT_PWD/debug
} else {
    DESTDIR = $$OUT_PWD/release
}

win32:DEFINES += __WINDOWS_MM__
unix:!macx:DEFINES += __UNIX_JACK__ \
                      __LINUX_ALSA__
macx:DEFINES += __MACOSX_CORE__

SOURCES += RtMidi.cpp
HEADERS += RtMidi.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
