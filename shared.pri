# global variable defines
REALWORLD2D_BINARY_PATH = $$PWD/examples
REALWORLD2D_3RDSRC_PATH = $$PWD/3rdparty
REALWORLD2D_SRC_PATH = $$PWD/src-realworld2d
REALWORLD2D_PYLIB_PATH = $$PWD/src-realworld2d-pylib

REALWORLD2D_SRC_TARGET = realworld2d
REALWORLD2D_PYLIB_TARGET = realworld2dpy

CONFIG -= qt

contains(TEMPLATE,lib) {
   CONFIG(debug, debug|release) {
      unix:TARGET = $$member(TARGET, 0)_debug
      else:TARGET = $$member(TARGET, 0)d
   }
}
