#------------------------------------------------------------------
#
# Project created by QtCreator 2017-03-17T17:57:23
# Author: Suayder Milhomem Costa
#
#Compile information: This aplication use c++11 version to compile
#                     and also use opencv
#
#------------------------------------------------------------------

CONFIG += c++11 -O3
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Weightless_Neural_Network
TEMPLATE = app

#INTEGRAÇÃO COM O OPENCV

INCLUDEPATH += /usr/local/include/opencv \
                /usr/local/include/opencv2

LIBS += -L/usr/local/lib
LIBS += -lopencv_core
LIBS += -lopencv_imgcodecs
LIBS += -lopencv_highgui
LIBS += -lopencv_imgproc
LIBS += -lopencv_highgui
LIBS += -lopencv_ml
LIBS += -lopencv_objdetect
LIBS += -lopencv_contrib
LIBS += -lopencv_legacy
LIBS += -lopencv_flann

SOURCES += main.cpp\
        mainwindow.cpp \
    ram.cpp \
    conversion.cpp \
    eventmouseclass.cpp \
    descriptor.cpp \
    mapping.cpp \
    binary_tree_tostorage.cpp \
    originimagemanipulation.cpp \
    inputrectanglesize.cpp \
    tracker.cpp

HEADERS  += mainwindow.h \
    ram.h \
    conversion.h \
    eventmouseclass.h \
    descriptor.h \
    mapping.h \
    binary_tree_tostorage.h \
    originimagemanipulation.h \
    inputrectanglesize.h \
    tracker.h

FORMS    += mainwindow.ui \
    inputrectanglesize.ui
