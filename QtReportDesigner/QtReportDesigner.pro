SOURCES += main.cpp
TEMPLATE = app

QT += sql xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

INCLUDEPATH += ../QtReport

LIBS +=  ../QtReport/libQtReport.a

#
TARGETDEPS += ../QtReport/libQtReport.a



RC_FILE = myapp.rc
