include(../shared.pri)

TEMPLATE = lib
TARGET = $$REALWORLD2D_PYLIB_TARGET
DESTDIR = $$REALWORLD2D_BINARY_PATH

INCLUDEPATH += /usr/local/include \
    $$REALWORLD2D_SRC_PATH \
    $$REALWORLD2D_3RDSRC_PATH

LIBS += -L$$REALWORLD2D_BINARY_PATH -l$$REALWORLD2D_SRC_TARGET

macx: {
    INCLUDEPATH += \
        /usr/local/Cellar/python/2.7.13/Frameworks/Python.framework/Versions/2.7/include/python2.7
    LIBS += -L/usr/local/lib -lpython
}

HEADERS += \
    scriptengine.h

SOURCES += \
    scriptengine.c \
    capi_timer.c
