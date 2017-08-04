include(../common.pri)

TARGET = libogg

INCLUDEPATH += $$PWD/include

SOURCES += \
    src/bitwise.c \
    src/framing.c

HEADERS += \
    include/ogg/ogg.h \
    include/ogg/os_types.h
