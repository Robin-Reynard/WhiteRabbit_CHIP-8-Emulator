include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt
INCLUDEPATH += "../../src"


HEADERS += \
        tst_opcodecase.h \
        tst_whiterabbitcase.h \
        ../../src/opcode.h

SOURCES += \
        main.cpp \
        ../../src/opcode.cpp

