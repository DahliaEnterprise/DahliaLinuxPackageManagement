TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    manifestlist.cpp \
    dependency.cpp \
    installorderqueue.cpp \
    installorderqueuegenerator.cpp \
    textfile.cpp

HEADERS += \
    manifestlist.h \
    dependency.h \
    installorderqueue.h \
    installorderqueuegenerator.h \
    textfile.h
