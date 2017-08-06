include(../shared.pri)

TEMPLATE = lib
TARGET = $$REALWORLD2D_SRC_TARGET
DESTDIR = $$REALWORLD2D_BINARY_PATH

PRECOMPILED_HEADER += precompiled.h

INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib -lSDL2

HEADERS += \
    realworld2d.h \
    globaldefs.h \
    precompiled.h \
    _global_config.h \
    _global_constants.h \
    _global_macros.h \
    _global_memory.h \
    _global_types.h \
    timer.h \
    hashtable.h \
    event.h \
    rect.h \
    graphics.h

SOURCES += \
    timer.c \
    hashtable.c \
    event.c \
    rect.c

