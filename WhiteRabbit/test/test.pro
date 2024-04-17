include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

HEADERS += \
        tst_opcodecase.h \
        tst_whiterabbitcase.h

SOURCES += \
        main.cpp
