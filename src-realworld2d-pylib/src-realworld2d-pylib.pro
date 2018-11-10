include(../shared.pri)

TEMPLATE = lib
TARGET = $$REALWORLD2D_PYLIB_TARGET
DESTDIR = $$REALWORLD2D_BINARY_PATH

INCLUDEPATH += /usr/local/include \
    $$REALWORLD2D_SRC_PATH \
    $$REALWORLD2D_3RDSRC_PATH

LIBS += -L$$REALWORLD2D_BINARY_PATH -l$$REALWORLD2D_SRC_TARGET \
    -L/usr/local/lib -lSDL -lSDL_image -lSDL_ttf

macx: {
    INCLUDEPATH += \
        /usr/local/Cellar/python/2.7.13/Frameworks/Python.framework/Versions/2.7/include/python2.7
    LIBS += -L/usr/local/lib -lpython
}

HEADERS += \
    scriptengine.h \
    graphicsutils.h

SOURCES += \
    scriptengine.c \
    capi_timer.c \
    capi_display.c \
    capi_assets.c \
    capi_gameevent.c \
    graphicsutils.c \
    capi_cahce.c
