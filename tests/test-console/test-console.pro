include(../../shared.pri)

TEMPLATE = app
DESTDIR = $$REALWORLD2D_BINARY_PATH

INCLUDEPATH += $$REALWORLD2D_SRC_PATH \
    $$REALWORLD2D_PYLIB_PATH \
    /usr/local/include

LIBS += -L$$REALWORLD2D_BINARY_PATH -l$$REALWORLD2D_SRC_TARGET -l$$REALWORLD2D_PYLIB_TARGET \
    -L/usr/local/lib -lSDL -lSDL_image -lSDL_ttf

macx: {
    INCLUDEPATH += \
        /usr/local/Cellar/python/2.7.13/Frameworks/Python.framework/Versions/2.7/include/python2.7
    LIBS += -L/usr/local/lib -lpython
}

CONFIG += console

SOURCES += \
    main.c


