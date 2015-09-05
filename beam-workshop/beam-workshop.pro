#-------------------------------------------------
#
# Project created by QtCreator 2013-02-12T20:33:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = beam-workshop
TEMPLATE = app

include (../libzoom/libzoom.pri)

INCLUDEPATH += ../libzoom

SOURCES += main.cpp\
    mainwindow.cpp \
    processing/imagemanager.cpp \
    processing/processsettings.cpp \
    processing/beamimage.cpp \
    aboutdialog.cpp

HEADERS  += mainwindow.h \
    processing/imagemanager.h \
    processing/processsettings.h \
    processing/beamimage.h \
    aboutdialog.h

FORMS    += mainwindow.ui \
    aboutdialog.ui
