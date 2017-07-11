TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    OpenseesModelGenerator.cpp \
    Steel.cpp \
    Steel02.cpp \
    ReinforcingSteel.cpp

HEADERS += \
    OpenseesModelGenerator.h \
    Steel.h \
    Steel02.h \
    ReinforcingSteel.h
