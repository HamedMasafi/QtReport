TEMPLATE = lib


QT += sql \
      xml

TARGET = QtReport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TRANSLATIONS = ../translations/qtreport_en.ts \
               ../translations/qtreport_fa.ts

CONFIG += staticlib

HEADERS +=  qreportwidgetbase.h \
            QtReport \
            qreportwidget.h \
            propertypages/qreportpropertypagebase.h \
            propertypages/qreportpropertydialog.h \
            qreport.h \
            propertypages/qreportpropertypagetext.h \
            propertypages/qreportpropertypagelinetype.h \
            propertypages/qreportpropertypagepage.h \
            propertypages/qreportpropertypagerectangle.h \
            propertypages/qreportpropertypagefont.h \
            propertypages/qreportpropertypagerichtext.h \
            qreportdatabaseinfodialog.h \
            qreportdatabasetablesdialog.h \
            qreportdatatable.h \
            qreportdesignerwindow.h \
            qreportdesigneraboutdialog.h \
            qreportparameteredialog.h \
            qreportdesignerfactory.h \
            propertypages/qreportpropertypageimage.h \
            propertypages/qreportpropertypagepos.h \
            qreportundocommands.h \
            propertypages/qreportpropertypagebarcode.h \
            propertypages/qreportpropertypagewidget.h \
            propertypages/qreportpropertypageformat.h \
            qreporttextbox.h \
            qreportimage.h \
            qreportevent.h \
            qreporthorizontalline.h \
            qreportlinebase.h \
            qreportdocumentview.h \
            qreportdocumentdesigner.h \
            qreportdocpage.h \
            qreportcolorpicker.h \
            qreportdisplaybase.h \
            qreportruler.h \
            qtreportglobal.h \
            qreportverticalline.h \
            qreportrectanglebase.h \
            qreportpanel.h \
            qreportscene.h \
            qreportsectiondataproperties.h \
            qreportsectionsproperties.h \
            qreporttreemanager.h \
            qreportxmlseriazble.h \
            qreportparametere.h \
            qreportquerybuilderdialog.h \
            qreporttypehelper.h \
            propertypages/qreportpropertypagealign.h \
    qreportband.h \
    qreportdataconnection.h \
    qreportdatatabledialog.h \
    propertypages/qreportpropertyband.h \
    propertypages/qreportpropertysort.h \
    propertypages/qreportpropertyfilter.h \
    qreportwidgetresizer_p.h

SOURCES +=  qreportwidgetbase.cpp \
            qreportwidgetresizer.cpp \
            qreportwidget.cpp \
            propertypages/qreportpropertypagebase.cpp \
            propertypages/qreportpropertydialog.cpp \
            qreport.cpp \
            propertypages/qreportpropertypagetext.cpp \
            propertypages/qreportpropertypagelinetype.cpp \
            propertypages/qreportpropertypagepage.cpp \
            propertypages/qreportpropertypagerectangle.cpp \
            propertypages/qreportpropertypagefont.cpp \
            propertypages/qreportpropertypagerichtext.cpp \
            qreportdatabaseinfodialog.cpp \
            qreportdatabasetablesdialog.cpp \
            qreportdatatable.cpp \
            qreportdesignerwindow.cpp \
            qreportdesigneraboutdialog.cpp \
            qreportparameteredialog.cpp \
            qreportdesignerfactory.cpp \
            propertypages/qreportpropertypageimage.cpp \
            propertypages/qreportpropertypagepos.cpp \
            qreportundocommands.cpp \
            propertypages/qreportpropertypagebarcode.cpp \
            propertypages/qreportpropertypagewidget.cpp \
            propertypages/qreportpropertypageformat.cpp \
            qreporttextbox.cpp \
            qreportimage.cpp \
            qreportlinebase.cpp \
            qreporthorizontalline.cpp \
            qreportdocumentview.cpp \
            qreportdocumentdesigner.cpp \
            qreportdocpage.cpp \
            qreportcolorpicker.cpp \
            qreportdisplaybase.cpp \
            qreportruler.cpp \
            qreportverticalline.cpp \
            qreportrectanglebase.cpp \
            qreportpanel.cpp \
            qreportscene.cpp \
            qreportsectiondataproperties.cpp \
            qreportsectionsproperties.cpp \
            qreporttreemanager.cpp \
            qreportxmlseriazble.cpp \
            qreportparametere.cpp \
            qreportquerybuilderdialog.cpp \
            qreporttypehelper.cpp \
            propertypages/qreportpropertypagealign.cpp \
    qreportband.cpp \
    qreportdataconnection.cpp \
    qreportdatatabledialog.cpp \
    propertypages/qreportpropertyband.cpp \
    propertypages/qreportpropertysort.cpp \
    propertypages/qreportpropertyfilter.cpp

FORMS += \
    propertypages/qreportpropertypagetext.ui \
    propertypages/qreportpropertypagepage.ui \
    propertypages/qreportpropertypagerectangle.ui \
    propertypages/qreportpropertypagefont.ui \
    propertypages/qreportpropertypagerichtext.ui \
    qreportdatabaseinfodialog.ui \
    qreportdatabasetablesdialog.ui \
    qreportdesignerwindow.ui \
    qreportdesigneraboutdialog.ui \
    qreportparameteredialog.ui \
    propertypages/qreportpropertypageimage.ui \
    propertypages/qreportpropertypagepos.ui \
    propertypages/qreportpropertypagebarcode.ui \
    propertypages/qreportpropertypagewidget.ui \
    propertypages/qreportpropertypageformat.ui \
    qreportsectiondataproperties.ui \
    qreportsectionsproperties.ui \
    qreportquerybuilderdialog.ui \
    propertypages/qreportpropertypagealign.ui \
    qreportdatatabledialog.ui \
    propertypages/qreportpropertyband.ui \
    propertypages/qreportpropertysort.ui \
    propertypages/qreportpropertyfilter.ui

OTHER_FILES += \
    main.dox

RESOURCES += \
    resources.qrc \
    win_resource.qrc \
    linux_resource.qrc \
    mac_resource.qrc
