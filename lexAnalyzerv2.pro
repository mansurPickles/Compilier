TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    token.cpp

HEADERS += \
    constvalues.h \
    lexanalyzer.h \
    reader.h \
    token.h
