#-------------------------------------------------
#
# Project created by QtCreator 2011-08-16T22:08:50
#
#-------------------------------------------------

QT       += core gui

TARGET = Calourada
TEMPLATE = app


DEPENDPATH += .;C:\qextserialport\
INCLUDEPATH += .;C:\qextserialport\

SOURCES += main.cpp\
        principal.cpp

HEADERS  += principal.h \
    Protocol.h

FORMS    += principal.ui

LIBS += -LC:\qextserialport\build\ -lqextserialport

RESOURCES += \
    imagens.qrc
