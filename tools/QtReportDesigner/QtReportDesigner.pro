SOURCES += main.cpp
TEMPLATE = app

QT += sql xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

INCLUDEPATH += ../../src

LIBS +=  ../../src/libQtReport.a

#
TARGETDEPS += ../../src/libQtReport.a



RC_FILE = myapp.rc
