CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(qtoasterwidgetsplugin)
TEMPLATE    = lib

HEADERS     = qlcddisplayplugin.h qbigdialplugin.h qsmalldialplugin.h qmulticolorledplugin.h qsmallknobplugin.h qchickenheaddialplugin.h qtoasterwidgets.h \
    qtoasterdialplugin.h \
    qtoasterbuttonplugin.h
SOURCES     = qlcddisplayplugin.cpp qbigdialplugin.cpp qsmalldialplugin.cpp qmulticolorledplugin.cpp qsmallknobplugin.cpp qchickenheaddialplugin.cpp qtoasterwidgets.cpp \
    qtoasterdialplugin.cpp \
    qtoasterbuttonplugin.cpp
RESOURCES   = icons.qrc \
    skins.qrc
LIBS        += -L. 

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += designer
} else {
    CONFIG += designer
}

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(qbigdial.pri)
include(qtoasterbutton.pri)
include(qtoasterdial.pri)
include(qmulticolorled.pri)
include(qlcddisplay.pri)
include(qsmalldial.pri)
include(qchickenheaddial.pri)
include(qsmallknob.pri)

DISTFILES +=
