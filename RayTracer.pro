#-------------------------------------------------
#
# Project created by QtCreator 2017-10-25T11:43:48
#
#-------------------------------------------------

lessThan(QT_MAJOR_VERSION, 5): error("Requires Qt5- run with Qt5's qmake (/usr/lib/x86_64-linux-gnu/qt5/bin/qmake).")

QT       += core gui widgets

TARGET = RayTracer
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++17

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        src/intersection.cpp \
        src/light.cpp \
        src/main.cpp \
        src/material.cpp \
        src/ray.cpp \
        src/sphere.cpp \
        src/transformations.cpp \
        src/tuple.cpp \
        src/window.cpp \
        src/canvas.cpp \
        src/world.cpp

HEADERS += \
    src/intersection.h \
    src/light.h \
    src/material.h \
    src/point.h \
    src/ray.h \
    src/sphere.h \
    src/transformations.h \
    src/tuple.h \
    src/vector.h \
    src/window.h \
    src/canvas.h \
    src/world.h

FORMS += \
    src/window.ui

CONFIG += conan_basic_setup
 include(./build/conanbuildinfo.pri)
