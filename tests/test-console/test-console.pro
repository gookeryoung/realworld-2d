include(../../shared.pri)

TEMPLATE = app
DESTDIR = $$REALWORLD2D_BINARY_PATH

INCLUDEPATH += $$REALWORLD2D_SRC_PATH \
    $$REALWORLD2D_PYLIB_PATH

LIBS += -L$$REALWORLD2D_BINARY_PATH -l$$REALWORLD2D_PYLIB_TARGET

CONFIG += console

SOURCES += \
    main.c

