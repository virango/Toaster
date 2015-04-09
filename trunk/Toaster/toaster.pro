#-------------------------------------------------
#
# Project created by QtCreator 2015-02-06T21:11:31
#
#-------------------------------------------------

QT       += core gui

LIBS += -lrtmidi -lqpotplug

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = toaster
TEMPLATE = app


SOURCES += main.cpp\
        ToasterWindow.cpp \
    SysExBase.cpp \
    Midi.cpp \
    SysExMsgDispatcher.cpp \
    StompMidi.cpp \
    MainFrame.cpp \
    Stomp.cpp \
    AmpMidi.cpp \
    RigMidi.cpp \
    EqMidi.cpp \
    InputMidi.cpp \
    CabMidi.cpp \
    DelayMidi.cpp \
    ReverbMidi.cpp \
    GlobalMidi.cpp \
    Amp.cpp \
    Cab.cpp \
    Delay.cpp \
    Eq.cpp \
    Global.cpp \
    Input.cpp \
    Rig.cpp \
    Reverb.cpp

HEADERS  += ToasterWindow.h \
    SysExBase.h \
    Midi.h \
    SysExMsgDispatcher.h \
    StompMidi.h \
    MainFrame.h \
    Stomp.h \
    AmpMidi.h \
    RigMidi.h \
    EqMidi.h \
    InputMidi.h \
    CabMidi.h \
    DelayMidi.h \
    ReverbMidi.h \
    GlobalMidi.h \
    Amp.h \
    Cab.h \
    Delay.h \
    Eq.h \
    Global.h \
    Input.h \
    Rig.h \
    Reverb.h

FORMS    += \
    ToasterWindow.ui \
    MainFrame.ui

RESOURCES += \
    resources.qrc


#include ( /usr/local/qwt-6.1.2/features/qwt.prf )

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-ToasterWidgets-Desktop_5_4-Debug/release/ -lqtoasterwidgetsplugin
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-ToasterWidgets-Desktop_5_4-Debug/debug/ -lqtoasterwidgetsplugin
else:unix: LIBS += -L$$PWD/../build-ToasterWidgets-Desktop_5_4-Debug/ -lqtoasterwidgetsplugin

INCLUDEPATH += $$PWD/../ToasterWidgets
DEPENDPATH += $$PWD/../ToasterWidgets
