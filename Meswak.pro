TEMPLATE =   app
#TARGET =
DEPENDPATH +=   .
INCLUDEPATH +=   .
QT +=   gui \
  opengl
HEADERS +=   Meswak.h \
  GLView.h \
  aboutdialogimpl.h
FORMS +=   Meswak.ui \
  About.ui
SOURCES +=   main.cpp \
  Meswak.cpp \
  GLView.cpp \
  aboutdialogimpl.cpp
RESOURCES +=   Meswak.qrc
win32 {
  RC_FILE +=     Meswak.rc
}
CONFIG +=   release
LIBS += -lGL -lGLU -lglut
