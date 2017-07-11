TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    OpenseesModelGenerator.cpp \
    Steel.cpp \
    Steel02.cpp \
    ReinforcingSteel.cpp \
    Concrete.cpp \
    Concrete01.cpp \
    Concrete02.cpp

HEADERS += \
    OpenseesModelGenerator.h \
    Steel.h \
    Steel02.h \
    ReinforcingSteel.h \
    Concrete.h \
    Concrete01.h \
    Concrete02.h
