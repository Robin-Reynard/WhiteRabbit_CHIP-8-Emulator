QT += network widgets
requires(qtConfig(combobox))

HEADERS       = client.h \
    ../WhiteRabbit/src/server.h
SOURCES       = client.cpp \
                main.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/network/fortuneclient
INSTALLS += target
