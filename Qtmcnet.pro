#-------------------------------------------------
#
# Project created by QtCreator 2012-07-30T22:40:21
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = Qtmcnet
TEMPLATE = lib
CONFIG += staticlib

DEFINES += QTMCNET_LIBRARY

SOURCES += \
    QMcParser.cpp

HEADERS +=\
    QMcParser.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE28C46D1
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = Qtmcnet.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
