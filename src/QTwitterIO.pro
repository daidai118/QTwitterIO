QT  += network
LIBS += -lcrypto
INCLUDEPATH += $$PWD
include(./o2/src/src.pri)
# Input
HEADERS += $$PWD/TwitterIO.hpp $$PWD/config.hpp
SOURCES += $$PWD/TwitterIO.cpp $$PWD/config.cpp
