include(../shared.pri)

TEMPLATE = lib

PRECOMPILED_HEADER += precompiled.h

HEADERS += \
    realworld2d.h \
    globaldefs.h \
    precompiled.h \
    _global_config.h \
    _global_constants.h \
    _global_macros.h \
    _global_memory.h \
    _global_types.h \
    point2d.h

SOURCES += \
    point2d.c

