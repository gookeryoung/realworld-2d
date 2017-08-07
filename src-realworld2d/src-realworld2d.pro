include(../shared.pri)

TEMPLATE = lib
TARGET = $$REALWORLD2D_SRC_TARGET
DESTDIR = $$REALWORLD2D_BINARY_PATH

PRECOMPILED_HEADER += precompiled.h

INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib -lSDL -lSDL_image -lSDL_ttf

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
    graphics.h \
    animation.h \
    charactermotion.h \
    screen.h \
    surface.h \
    palette.h \
    sprite.h \
    gamemap.h \
    gamemapground.h \
    stringutils.h \
    graphicssystem.h \
    font.h \
    character.h

SOURCES += \
    timer.c \
    hashtable.c \
    event.c \
    rect.c \
    animation.c \
    charactermotion.c \
    screen.c \
    surface.c \
    palette.c \
    sprite.c \
    gamemap.c \
    gamemapground.c \
    stringutils.c \
    graphicssystem.c \
    font.c \
    character.c

