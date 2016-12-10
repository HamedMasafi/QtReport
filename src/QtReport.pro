TEMPLATE = lib


QT += sql \
      xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TRANSLATIONS = ../translations/qtreport_en.ts \
               ../translations/qtreport_fa.ts

CONFIG += staticlib

HEADERS +=  qreportwidgetbase.h \
            QtReport \
            qreportwidgetresizer.h \
            qreportwidget.h \
            qreportpropertypagebase.h \
            qreportpropertydialog.h \
            qreport.h \
            qreportpropertypagetext.h \
            qreportpropertypagelinetype.h \
            qreportpropertypagepage.h \
            qreportpropertypagerectangle.h \
            qreportpropertypagefont.h \
            qreportpropertypagerichtext.h \
            qreportdatabaseinfodialog.h \
            qreportdatabasetablesdialog.h \
            qreportdatatable.h \
            qreportdesignerwindow.h \
            qreportdesigneraboutdialog.h \
            qreportparameteredialog.h \
            qreportdesignerfactory.h \
            qreportpropertypageimage.h \
            qreportpropertypagepos.h \
            qreportundocommands.h \
            qreportpropertypagebarcode.h \
            qreportpropertypagewidget.h \
            qreportpropertypageformat.h \
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
            qreportpropertypagealign.h \
    qreportband.h \
    qreportdataconnection.h \
    qreportdatatabledialog.h \
    qreportpropertyband.h \
    qreportpropertysort.h \
    qreportpropertyfilter.h

SOURCES +=  qreportwidgetbase.cpp \
            qreportwidgetresizer.cpp \
            qreportwidget.cpp \
            qreportpropertypagebase.cpp \
            qreportpropertydialog.cpp \
            qreport.cpp \
            qreportpropertypagetext.cpp \
            qreportpropertypagelinetype.cpp \
            qreportpropertypagepage.cpp \
            qreportpropertypagerectangle.cpp \
            qreportpropertypagefont.cpp \
            qreportpropertypagerichtext.cpp \
            qreportdatabaseinfodialog.cpp \
            qreportdatabasetablesdialog.cpp \
            qreportdatatable.cpp \
            qreportdesignerwindow.cpp \
            qreportdesigneraboutdialog.cpp \
            qreportparameteredialog.cpp \
            qreportdesignerfactory.cpp \
            qreportpropertypageimage.cpp \
            qreportpropertypagepos.cpp \
            qreportundocommands.cpp \
            qreportpropertypagebarcode.cpp \
            qreportpropertypagewidget.cpp \
            qreportpropertypageformat.cpp \
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
            qreportpropertypagealign.cpp \
    qreportband.cpp \
    qreportdataconnection.cpp \
    qreportdatatabledialog.cpp \
    qreportpropertyband.cpp \
    qreportpropertysort.cpp \
    qreportpropertyfilter.cpp

FORMS += \
    qreportpropertypagetext.ui \
    qreportpropertypagepage.ui \
    qreportpropertypagerectangle.ui \
    qreportpropertypagefont.ui \
    qreportpropertypagerichtext.ui \
    qreportdatabaseinfodialog.ui \
    qreportdatabasetablesdialog.ui \
    qreportdesignerwindow.ui \
    qreportdesigneraboutdialog.ui \
    qreportparameteredialog.ui \
    qreportpropertypageimage.ui \
    qreportpropertypagepos.ui \
    qreportpropertypagebarcode.ui \
    qreportpropertypagewidget.ui \
    qreportpropertypageformat.ui \
    qreportsectiondataproperties.ui \
    qreportsectionsproperties.ui \
    qreportquerybuilderdialog.ui \
    qreportpropertypagealign.ui \
    qreportdatatabledialog.ui \
    qreportpropertyband.ui \
    qreportpropertysort.ui \
    qreportpropertyfilter.ui

OTHER_FILES += \
    main.dox

RESOURCES += \
    resources.qrc \
    win_resource.qrc \
    linux_resource.qrc \
    mac_resource.qrc
