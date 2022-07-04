TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        crypto/crypto.cpp \
        crypto/help.cpp \
        crypto/sha256.cpp \
        crypto/timer.cpp \
        main.cpp

HEADERS += \
    crypto/crypto.h \
    crypto/help.h \
    crypto/passwd-utils.hpp \
    crypto/random.hpp \
    crypto/sha256.h \
    crypto/timer.h \
    threadpool.hpp

QMAKE_CXXFLAGS += -std=c++17
QMAKE_CXXFLAGS_RELEASE += -O3
