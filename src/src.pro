TEMPLATE = lib


QT += sql \
      xml

TARGET = QtReport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TRANSLATIONS = ../translations/qtreport_en.ts \
               ../translations/qtreport_fa.ts

CONFIG += staticlib

HEADERS +=  widgets/widgetbase.h \
            QtReport \
            widgets/widget.h \
            propertypages/propertypagebase.h \
            propertypages/propertydialog.h \
            report.h \
            propertypages/propertypagetext.h \
            propertypages/propertypagelinetype.h \
            propertypages/propertypagepage.h \
            propertypages/propertypagerectangle.h \
            propertypages/propertypagefont.h \
            propertypages/propertypagerichtext.h \
            databaseinfodialog.h \
            databasetablesdialog.h \
            datatable.h \
            designerwindow.h \
            designeraboutdialog.h \
            parameteredialog.h \
            designerfactory.h \
            propertypages/propertypageimage.h \
            propertypages/propertypagepos.h \
            undocommands.h \
            propertypages/propertypagebarcode.h \
            propertypages/propertypagewidget.h \
            propertypages/propertypageformat.h \
            widgets/textbox.h \
            widgets/image.h \
            event.h \
            widgets/horizontalline.h \
            widgets/linebase.h \
            documentview.h \
            documentdesigner.h \
            docpage.h \
            colorpicker.h \
            displaybase.h \
            ruler.h \
            qtreportglobal.h \
            widgets/verticalline.h \
            widgets/rectanglebase.h \
            widgets/panel.h \
            scene.h \
            propertypages/sectiondataproperties.h \
            propertypages/sectionsproperties.h \
            treemanager.h \
            xmlseriazble.h \
            parametere.h \
            querybuilderdialog.h \
            typehelper.h \
            propertypages/propertypagealign.h \
    widgets/band.h \
    dataconnection.h \
    datatabledialog.h \
    propertypages/propertyband.h \
    propertypages/propertysort.h \
    propertypages/propertyfilter.h \
    widgetresizer_p.h \
    newconnectionwizard.h

SOURCES +=  widgets/widgetbase.cpp \
            widgetresizer.cpp \
            widgets/widget.cpp \
            propertypages/propertypagebase.cpp \
            propertypages/propertydialog.cpp \
            report.cpp \
            propertypages/propertypagetext.cpp \
            propertypages/propertypagelinetype.cpp \
            propertypages/propertypagepage.cpp \
            propertypages/propertypagerectangle.cpp \
            propertypages/propertypagefont.cpp \
            propertypages/propertypagerichtext.cpp \
            databaseinfodialog.cpp \
            databasetablesdialog.cpp \
            datatable.cpp \
            designerwindow.cpp \
            designeraboutdialog.cpp \
            parameteredialog.cpp \
            designerfactory.cpp \
            propertypages/propertypageimage.cpp \
            propertypages/propertypagepos.cpp \
            undocommands.cpp \
            propertypages/propertypagebarcode.cpp \
            propertypages/propertypagewidget.cpp \
            propertypages/propertypageformat.cpp \
            widgets/textbox.cpp \
            widgets/image.cpp \
            widgets/linebase.cpp \
            widgets/horizontalline.cpp \
            documentview.cpp \
            documentdesigner.cpp \
            docpage.cpp \
            colorpicker.cpp \
            displaybase.cpp \
            ruler.cpp \
            widgets/verticalline.cpp \
            widgets/rectanglebase.cpp \
            widgets/panel.cpp \
            scene.cpp \
            propertypages/sectiondataproperties.cpp \
            propertypages/sectionsproperties.cpp \
            treemanager.cpp \
            xmlseriazble.cpp \
            parametere.cpp \
            querybuilderdialog.cpp \
            typehelper.cpp \
            propertypages/propertypagealign.cpp \
    widgets/band.cpp \
    dataconnection.cpp \
    datatabledialog.cpp \
    propertypages/propertyband.cpp \
    propertypages/propertysort.cpp \
    propertypages/propertyfilter.cpp \
    newconnectionwizard.cpp

FORMS += \
    propertypages/propertypagetext.ui \
    propertypages/propertypagepage.ui \
    propertypages/propertypagerectangle.ui \
    propertypages/propertypagefont.ui \
    propertypages/propertypagerichtext.ui \
    databaseinfodialog.ui \
    databasetablesdialog.ui \
    designerwindow.ui \
    designeraboutdialog.ui \
    parameteredialog.ui \
    propertypages/propertypageimage.ui \
    propertypages/propertypagepos.ui \
    propertypages/propertypagebarcode.ui \
    propertypages/propertypagewidget.ui \
    propertypages/propertypageformat.ui \
    propertypages/sectiondataproperties.ui \
    propertypages/sectionsproperties.ui \
    querybuilderdialog.ui \
    propertypages/propertypagealign.ui \
    datatabledialog.ui \
    propertypages/propertyband.ui \
    propertypages/propertysort.ui \
    propertypages/propertyfilter.ui \
    newconnectionwizard.ui

OTHER_FILES += \
    main.dox

RESOURCES += \
    resources.qrc \
    win_resource.qrc \
    linux_resource.qrc \
    mac_resource.qrc
