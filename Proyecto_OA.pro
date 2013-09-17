#-------------------------------------------------
#
# Project created by QtCreator 2013-09-14T16:55:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Proyecto_OA
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    adtfile.cpp \
    adtfilerecord.cpp \
    field.cpp \
    fileheader.cpp \
    newfieldwindow.cpp \
    modifyfieldwindow.cpp \
    record.cpp \
    object.cpp \
    primaryindex.cpp

HEADERS  += mainwindow.h \
    adtfile.h \
    adtfilerecord.h \
    field.h \
    fileheader.h \
    newfieldwindow.h \
    modifyfieldwindow.h \
    record.h \
    object.h \
    primaryindex.h

FORMS    += mainwindow.ui \
    newfieldwindow.ui \
    modifyfieldwindow.ui
