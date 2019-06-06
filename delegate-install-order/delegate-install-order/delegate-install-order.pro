TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    manifestlist.cpp \
    dependency.cpp

HEADERS += \
    manifestlist.h \
    dependency.h
