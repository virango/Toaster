CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(qtoasterwidgetsplugin)
TEMPLATE    = lib
QT         += core gui widgets designer

CONFIG(debug, debug|release) {
    DESTDIR = $$OUT_PWD/debug
} else {
    DESTDIR = $$OUT_PWD/release
}


DEFINES += TOASTERWIDGETS_LIB

HEADERS     = \
#    qbigdialplugin.h \
#    qsmalldialplugin.h \
    qmulticolorledplugin.h \
#    qsmallknobplugin.h \
    qchickenheaddialplugin.h \
    qtoasterwidgets.h \
    qtoasterdialplugin.h \
    qtoasterenumdialplugin.h \
    qtoasterbuttonplugin.h \
    qtoasterlcdplugin.h \
    ../Toaster/Commons.h \
    ToasterWidgetsLib.h \
    CtxMenuProvider.h
SOURCES     = \
#    qbigdialplugin.cpp \
#    qsmalldialplugin.cpp \
    qmulticolorledplugin.cpp \
#   qsmallknobplugin.cpp \
    qchickenheaddialplugin.cpp \
    qtoasterwidgets.cpp \
    qtoasterdialplugin.cpp \
    qtoasterenumdialplugin.cpp \
    qtoasterbuttonplugin.cpp \
    qtoasterlcdplugin.cpp
RESOURCES   = icons.qrc \
    skins.qrc \
    fonts.qrc
LIBS        += -L. 

INCLUDEPATH += $$PWD/../Shared

#greaterThan(QT_MAJOR_VERSION, 4) {
#    QT += designer
#} else {
#    CONFIG += designer
#}

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

#include(qbigdial.pri)
include(qtoasterbutton.pri)
include(qtoasterdial.pri)
include(qtoasterenumdial.pri)
include(qmulticolorled.pri)
include(qtoasterlcd.pri)
#include(qsmalldial.pri)
include(qchickenheaddial.pri)
#include(qsmallknob.pri)

DISTFILES +=
