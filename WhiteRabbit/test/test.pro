include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt
INCLUDEPATH += "../../src"


HEADERS += \
        MockOpcode.h \
        tst_chip8case.h \
        tst_opcodecase.h \
        tst_whiterabbitcase.h \
        ../../src/opcode.h \
        ../../src/chip8.h

SOURCES += \
        main.cpp \
        ../../src/opcode.cpp \
        ../../src/chip8.cpp


