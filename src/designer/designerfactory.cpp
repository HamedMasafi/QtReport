/***************************************************************************
 *   QtReport                                                              *
 *   Qt Report Builder Soultion                                            *
 *                                                                         *
 *   Copyright (C) 2010 by Hamed Masafi                                    *
 *   Hamed.Masafi@GMail.COM                                                *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#include <QtCore/QVariant>
#include <QtCore/QMetaObject>
#include <QtCore/QMetaProperty>
#include <QtCore/QDebug>
#include <QtCore/QMetaType>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QDockWidget>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <QFontComboBox>
#include <QClipboard>
#include <QMessageBox>
#include <QPageSetupDialog>
#include <QFileDialog>
#include <QUndoView>
#include <QUndoStack>

#include "newconnectionwizard.h"
#include "designerfactory.h"
#include "widgets/band.h"
#include "designerfactory.h"
#include "documentdesigner.h"
#include "databaseinfodialog.h"
#include "databasetablesdialog.h"
#include "core/report.h"
#include "designeraboutdialog.h"
#include "documentview.h"
#include "colorpicker.h"
#include "parameteredialog.h"
#include "propertypages/sectionsproperties.h"
#include "treemanager.h"
#include "documentdesigner.h"
#include "treemanager.h"

LEAF_BEGIN_NAMESPACE

LReportDesignerFactory::LReportDesignerFactory(QMainWindow *window) :
    mainWindow(window)
{
    _report = new LReport();

    _designer = new LReportDocumentDesigner(mainWindow, _report);
    _designer->setObjectName(QString::fromUtf8("doc"));

    initWidgets();
    initActions();
    initToolbars();
    initActionGroups();
    initDockWidgets();
    initStatusBar();
    initMenubar();

    centralwidget = new QWidget(mainWindow);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    verticalLayout = new QVBoxLayout(centralwidget);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    mainWindow->setCentralWidget(centralwidget);

    connect(_designer,  SIGNAL(activeWidgetChanged()), this, SLOT(doc_activeWidgetChanged()));
    connect(_designer,  SIGNAL(dataDirectoryModified()), this, SLOT(doc_dataDirectoryModified()));
    connect(_designer,  SIGNAL(widgetContextMenuEvent()), this, SLOT(doc_widgetContextMenuEvent()));

    verticalLayout->addWidget(_designer);


    retranslateUi();
    QMetaObject::connectSlotsByName(this);

    connect(actionCopy,        SIGNAL(triggered()), _designer,  SLOT(doCopy()));
    connect(actionCut,         SIGNAL(triggered()), _designer,  SLOT(doCut()));
    connect(actionPaste,       SIGNAL(triggered()), _designer,  SLOT(doPaste()));
    connect(actionDelete,      SIGNAL(triggered()), _designer,  SLOT(doDelete()));
    connect(actionSelect_All,  SIGNAL(triggered()), _designer,  SLOT(selectAll()));

    connect(actionAlignToGrid, SIGNAL(triggered()), _designer,  SLOT(alignToGridWidgets()));
    connect(actionSameSize,    SIGNAL(triggered()), _designer,  SLOT(setSameSize()));
    connect(actionSameHeight,  SIGNAL(triggered()), _designer,  SLOT(setSameHeight()));
    connect(actionSameWidth,   SIGNAL(triggered()), _designer,  SLOT(setSameWidth()));

    connect(QApplication::clipboard(), SIGNAL(dataChanged()), this, SLOT(clipboard_dataChanged()));
}


void LReportDesignerFactory::initActions()
{
    actionZoom25 = new QAction(this);
    actionZoom25->setObjectName(QString::fromUtf8("actionZoom25"));
    actionZoom25->setCheckable(true);

    actionZoom50 = new QAction(this);
    actionZoom50->setObjectName(QString::fromUtf8("actionZoom50"));
    actionZoom50->setCheckable(true);

    actionZoom75 = new QAction(this);
    actionZoom75->setObjectName(QString::fromUtf8("actionZoom75"));
    actionZoom75->setCheckable(true);

    actionZoom100 = new QAction(this);
    actionZoom100->setObjectName(QString::fromUtf8("actionZoom100"));
    actionZoom100->setCheckable(true);

    actionZoom200 = new QAction(this);
    actionZoom200->setObjectName(QString::fromUtf8("actionZoom200"));
    actionZoom200->setCheckable(true);

    actionZoom400 = new QAction(this);
    actionZoom400->setObjectName(QString::fromUtf8("actionZoom400"));
    actionZoom400->setCheckable(true);

    actionNew = new QAction(this);
    actionNew->setObjectName(QString::fromUtf8("actionNew"));
    QIcon icon;
    icon.addFile(QString::fromUtf8(":/designer/new_document"), QSize(), QIcon::Normal, QIcon::Off);
    actionNew->setIcon(icon);

    actionSave = new QAction(this);
    actionSave->setObjectName(QString::fromUtf8("actionSave"));
    QIcon icon1;
    icon1.addFile(QString::fromUtf8(":/designer/save"), QSize(), QIcon::Normal, QIcon::Off);
    actionSave->setIcon(icon1);
    actionSave_As = new QAction(this);
    actionSave_As->setObjectName(QString::fromUtf8("actionSave_As"));
    QIcon icon2;
    icon2.addFile(QString::fromUtf8(":/designer/save_as"), QSize(), QIcon::Normal, QIcon::Off);
    actionSave_As->setIcon(icon2);
    actionPrint_Setup = new QAction(this);
    actionPrint_Setup->setObjectName(QString::fromUtf8("actionPrint_Setup"));
    QIcon icon3;
    icon3.addFile(QString::fromUtf8(":/designer/page_setup"), QSize(), QIcon::Normal, QIcon::Off);
    actionPrint_Setup->setIcon(icon3);
    actionPrint_preview = new QAction(this);
    actionPrint_preview->setObjectName(QString::fromUtf8("actionPrint_preview"));
    QIcon icon4;
    icon4.addFile(QString::fromUtf8(":/designer/document_preview"), QSize(), QIcon::Normal, QIcon::Off);
    actionPrint_preview->setIcon(icon4);
    actionPrint = new QAction(this);
    actionPrint->setObjectName(QString::fromUtf8("actionPrint"));
    QIcon icon5;
    icon5.addFile(QString::fromUtf8(":/designer/print"), QSize(), QIcon::Normal, QIcon::Off);
    actionPrint->setIcon(icon5);
    actionExit = new QAction(this);
    actionExit->setObjectName(QString::fromUtf8("actionExit"));
    QIcon icon6;
    icon6.addFile(QString::fromUtf8(":/designer/exit"), QSize(), QIcon::Normal, QIcon::Off);
    actionExit->setIcon(icon6);
    actionAbout = new QAction(this);
    actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
    QIcon icon7;
    icon7.addFile(QString::fromUtf8(":/designer/information"), QSize(), QIcon::Normal, QIcon::Off);
    actionAbout->setIcon(icon7);
    actionHelp = new QAction(this);
    actionHelp->setObjectName(QString::fromUtf8("actionHelp"));

    actionInsertTextbox = new QAction(this);
    actionInsertTextbox->setObjectName(QString::fromUtf8("actionInsertTextbox"));
    actionInsertTextbox->setIcon(QIcon(":/designer/textbox"));
    actionInsertTextbox->setData("LReportTextBox");

    actionInsertImage = new QAction(this);
    actionInsertImage->setObjectName(QString::fromUtf8("actionInsertImage"));
    actionInsertImage->setIcon(QIcon(":/designer/image"));
    actionInsertImage->setData("LReportImage");

    actionInsertVerticalLine = new QAction(this);
    actionInsertVerticalLine->setObjectName(QString::fromUtf8("actionInsertVerticalLine"));
    actionInsertVerticalLine->setIcon(QIcon(":/designer/vline"));
    actionInsertVerticalLine->setData("LReportVerticalLine");

    actionInsertHorizontalLine = new QAction(this);
    actionInsertHorizontalLine->setObjectName(QString::fromUtf8("actionInsertHorizontalLine"));
    actionInsertHorizontalLine->setIcon(QIcon(":/designer/hline"));
    actionInsertHorizontalLine->setData("LReportHorizontalLine");

    actionInsertPageHeader = new QAction(this);
    actionInsertPageHeader->setObjectName(QString::fromUtf8("actionInsertPageHeader"));
    actionInsertPageHeader->setIcon(QIcon(":/designer/section_page_header"));
    actionInsertPageHeader->setData(PageHeader);

    actionInsertReportHeader = new QAction(this);
    actionInsertReportHeader->setObjectName(QString::fromUtf8("actionInsertReportHeader"));
    actionInsertReportHeader->setIcon(QIcon(":/designer/section_report_header"));
    actionInsertReportHeader->setData(ReportHeader);

    actionInsertGroupHeader = new QAction(this);
    actionInsertGroupHeader->setObjectName(QString::fromUtf8("actionInsertGroupHeader"));
    actionInsertGroupHeader->setIcon(QIcon(":/designer/section_group_header"));
    actionInsertGroupHeader->setData(GroupHeader);

    actionInsertData = new QAction(this);
    actionInsertData->setObjectName(QString::fromUtf8("actionInsertData"));
    actionInsertData->setIcon(QIcon(":/designer/section_data"));
    actionInsertData->setData(Data);

    actionInsertGroupFooter = new QAction(this);
    actionInsertGroupFooter->setObjectName(QString::fromUtf8("actionInsertGroupFooter"));
    actionInsertGroupFooter->setIcon(QIcon(":/designer/section_group_footer"));
    actionInsertGroupFooter->setData(GroupFooter);

    actionInsertReportFooter = new QAction(this);
    actionInsertReportFooter->setObjectName(QString::fromUtf8("actionInsertReportFooter"));
    actionInsertReportFooter->setIcon(QIcon(":/designer/section_report_footer"));
    actionInsertReportFooter->setData(ReportFooter);

    actionInsertPageFooter = new QAction(this);
    actionInsertPageFooter->setObjectName(QString::fromUtf8("actionInsertPageFooter"));
    actionInsertPageFooter->setIcon(QIcon(":/designer/section_page_footer"));
    actionInsertPageFooter->setData(PageFooter);

    actionInsertRectangle = new QAction(this);
    actionInsertRectangle->setObjectName(QString::fromUtf8("actionInsertRectangle"));
    actionInsertRectangle->setIcon(QIcon(":/designer/rectangle"));
    actionInsertRectangle->setData("LReportRectangle");

    actionAlignToGridOption = new QAction(this);
    actionAlignToGridOption->setObjectName(QString::fromUtf8("actionAlignToGridOption"));
    actionAlignToGridOption->setCheckable(true);
    actionAlignToGridOption->setChecked(true);
    actionAlignToGridOption->setIcon(QIcon(":/designer/grid_snap"));

    actionAlignToGrid = new QAction(this);
    actionAlignToGrid->setObjectName(QString::fromUtf8("actionAlignToGrid"));
    actionAlignToGrid->setIcon(QIcon(":/designer/align-to-grid"));

    actionShowRulers = new QAction(this);
    actionShowRulers->setObjectName(QString::fromUtf8("actionShowRulers"));
    actionShowRulers->setCheckable(true);
    actionShowRulers->setChecked(true);
    QIcon icon19;
    icon19.addFile(QString::fromUtf8(":/designer/ruler"), QSize(), QIcon::Normal, QIcon::Off);
    actionShowRulers->setIcon(icon19);
    actionGridNone = new QAction(this);
    actionGridNone->setObjectName(QString::fromUtf8("actionGridNone"));
    actionGridNone->setCheckable(true);
    actionGridDots = new QAction(this);
    actionGridDots->setObjectName(QString::fromUtf8("actionGridDots"));
    actionGridDots->setCheckable(true);
    QIcon icon20;
    icon20.addFile(QString::fromUtf8(":/designer/grid_dots"), QSize(), QIcon::Normal, QIcon::Off);
    actionGridDots->setIcon(icon20);
    actionGridLines = new QAction(this);
    actionGridLines->setObjectName(QString::fromUtf8("actionGridLines"));
    actionGridLines->setCheckable(true);
    QIcon icon21;
    icon21.addFile(QString::fromUtf8(":/designer/grid_lines"), QSize(), QIcon::Normal, QIcon::Off);
    actionGridLines->setIcon(icon21);
    actionAbout_Qt = new QAction(this);
    actionAbout_Qt->setObjectName(QString::fromUtf8("actionAbout_Qt"));
    actionBold = new QAction(this);
    actionBold->setObjectName(QString::fromUtf8("actionBold"));
    actionBold->setCheckable(true);
    actionBold->setEnabled(false);
    QIcon icon22;
    icon22.addFile(QString::fromUtf8(":/designer/bold"), QSize(), QIcon::Normal, QIcon::Off);
    actionBold->setIcon(icon22);
    actionItalic = new QAction(this);
    actionItalic->setObjectName(QString::fromUtf8("actionItalic"));
    actionItalic->setCheckable(true);
    actionItalic->setEnabled(false);
    QIcon icon23;
    icon23.addFile(QString::fromUtf8(":/designer/italic"), QSize(), QIcon::Normal, QIcon::Off);
    actionItalic->setIcon(icon23);
    actionUnderline = new QAction(this);
    actionUnderline->setObjectName(QString::fromUtf8("actionUnderline"));
    actionUnderline->setCheckable(true);
    actionUnderline->setEnabled(false);
    QIcon icon24;
    icon24.addFile(QString::fromUtf8(":/designer/underline"), QSize(), QIcon::Normal, QIcon::Off);
    actionUnderline->setIcon(icon24);

    actionUndo = _designer->createUndoAction(this);///new QAction(this);
    actionUndo->setObjectName(QString::fromUtf8("actionUndo"));
    actionUndo->setIcon(QIcon(":/designer/undo"));

    actionRedo = _designer->createRedoAction(this);//new QAction(this);
    actionRedo->setObjectName(QString::fromUtf8("actionRedo"));
    actionRedo->setIcon(QIcon(":/designer/redo"));

    actionCut = new QAction(this);
    actionCut->setObjectName(QString::fromUtf8("actionCut"));
    actionCut->setIcon(QIcon(":/designer/cut"));
    actionCut->setEnabled(false);

    actionCopy = new QAction(this);
    actionCopy->setObjectName(QString::fromUtf8("actionCopy"));
    actionCopy->setIcon(QIcon(":/designer/copy"));
    actionCopy->setEnabled(false);

    actionPaste = new QAction(this);
    actionPaste->setObjectName(QString::fromUtf8("actionPaste"));
    actionPaste->setIcon(QIcon(":/designer/paste"));
    actionPaste->setEnabled(false);

    actionSelect_All = new QAction(this);
    actionSelect_All->setObjectName(QString::fromUtf8("actionSelect_All"));
    QIcon icon30;
    icon30.addFile(QString::fromUtf8(":/designer/select_all"), QSize(), QIcon::Normal, QIcon::Off);
    actionSelect_All->setIcon(icon30);

    actionDelete = new QAction(this);
    actionDelete->setObjectName(QString::fromUtf8("actionDelete"));
    actionDelete->setIcon(QIcon(":/designer/delete"));
    actionDelete->setEnabled(false);

    actionOpen = new QAction(this);
    actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
    QIcon icon32;
    icon32.addFile(QString::fromUtf8(":/designer/open"), QSize(), QIcon::Normal, QIcon::Off);
    actionOpen->setIcon(icon32);
    actionAlignLeft = new QAction(this);
    actionAlignLeft->setObjectName(QString::fromUtf8("actionAlignLeft"));
    actionAlignLeft->setCheckable(true);
    actionAlignLeft->setEnabled(false);
    QIcon icon33;
    icon33.addFile(QString::fromUtf8(":/designer/align-left"), QSize(), QIcon::Normal, QIcon::Off);
    actionAlignLeft->setIcon(icon33);
    actionAlignRight = new QAction(this);
    actionAlignRight->setObjectName(QString::fromUtf8("actionAlignRight"));
    actionAlignRight->setCheckable(true);
    actionAlignRight->setEnabled(false);
    QIcon icon34;
    icon34.addFile(QString::fromUtf8(":/designer/align-right"), QSize(), QIcon::Normal, QIcon::Off);
    actionAlignRight->setIcon(icon34);
    actionAlignCenter = new QAction(this);
    actionAlignCenter->setObjectName(QString::fromUtf8("actionAlignCenter"));
    actionAlignCenter->setCheckable(true);
    actionAlignCenter->setEnabled(false);
    QIcon icon35;
    icon35.addFile(QString::fromUtf8(":/designer/align-center"), QSize(), QIcon::Normal, QIcon::Off);
    actionAlignCenter->setIcon(icon35);
    actionAlignJustify = new QAction(this);
    actionAlignJustify->setObjectName(QString::fromUtf8("actionAlignJustify"));
    actionAlignJustify->setCheckable(true);
    actionAlignJustify->setEnabled(false);
    actionAlignJustify->setIcon(QIcon(":/designer/align-justify"));

    actionAlignTop = new QAction(this);
    actionAlignTop->setObjectName(QString::fromUtf8("actionAlignTop"));
    actionAlignTop->setIcon(QIcon(":/designer/align-top"));
    actionAlignTop->setEnabled(false);
    actionAlignTop->setCheckable(true);

    actionAlignMiddle = new QAction(this);
    actionAlignMiddle->setObjectName(QString::fromUtf8("actionAlignMiddle"));
    actionAlignMiddle->setIcon(QIcon(":/designer/align-middle"));
    actionAlignMiddle->setEnabled(false);
    actionAlignMiddle->setCheckable(true);

    actionAlignBottom = new QAction(this);
    actionAlignBottom->setObjectName(QString::fromUtf8("actionAlignBottom"));
    actionAlignBottom->setIcon(QIcon(":/designer/align-bottom"));
    actionAlignBottom->setEnabled(false);
    actionAlignBottom->setCheckable(true);

    actionProperties = new QAction(this);
    actionProperties->setObjectName(QString::fromUtf8("actionProperties"));
    QIcon icon37;
    icon37.addFile(QString::fromUtf8(":/designer/properties"), QSize(), QIcon::Normal, QIcon::Off);
    actionProperties->setIcon(icon37);
    actionProperties->setEnabled(false);

    actionSetDatabase = new QAction(this);
    actionSetDatabase->setObjectName(QString::fromUtf8("actionSetDatabase"));
    actionSetDatabase->setIcon(QIcon(":/designer/database"));

    actionSetDataSource = new QAction(this);
    actionSetDataSource->setObjectName(QString::fromUtf8("actionSetDataSource"));
    actionSetDataSource->setIcon(QIcon(":/designer/table-edit"));

    actionSendToBack = new QAction(this);
    actionSendToBack->setObjectName(QString::fromUtf8("actionSendToBack"));
    actionSendToBack->setIcon(QIcon(":/designer/send-to-back"));
    actionSendToBack->setEnabled(false);

    actionBringToFront = new QAction(this);
    actionBringToFront->setObjectName(QString::fromUtf8("actionBringToFront"));
    actionBringToFront->setIcon(QIcon(":/designer/bring-to-front"));
    actionBringToFront->setEnabled(false);

    actionSectionsProperties = new QAction(this);
    actionSectionsProperties->setObjectName("actionSectionsProperties");

    actionGroupAlignLeft = new QAction(this);
    actionGroupAlignLeft->setObjectName(QString::fromUtf8("actionGroupAlignLeft"));
    actionGroupAlignLeft->setIcon(QIcon(":/designer/shape-align-left"));
    actionGroupAlignLeft->setEnabled(false);

    actionGroupAlignRight = new QAction(this);
    actionGroupAlignRight->setObjectName(QString::fromUtf8("actionGroupAlignRight"));
    actionGroupAlignRight->setIcon(QIcon(":/designer/shape-align-right"));
    actionGroupAlignRight->setEnabled(false);

    actionGroupAlignBottom = new QAction(this);
    actionGroupAlignBottom->setObjectName(QString::fromUtf8("actionGroupAlignBottom"));
    actionGroupAlignBottom->setIcon(QIcon(":/designer/shape-align-bottom"));
    actionGroupAlignBottom->setEnabled(false);

    actionGroupAlignTop = new QAction(this);
    actionGroupAlignTop->setObjectName(QString::fromUtf8("actionGroupAlignTop"));
    actionGroupAlignTop->setIcon(QIcon(":/designer/shape-align-top"));
    actionGroupAlignTop->setEnabled(false);

    actionGroupAlignMiddle = new QAction(this);
    actionGroupAlignMiddle->setObjectName(QString::fromUtf8("actionGroupAlignMiddle"));
    actionGroupAlignMiddle->setIcon(QIcon(":/designer/shape-align-middle"));
    actionGroupAlignMiddle->setEnabled(false);

    actionGroupAlignCenter = new QAction(this);
    actionGroupAlignCenter->setObjectName(QString::fromUtf8("actionGroupAlignCenter"));
    actionGroupAlignCenter->setIcon(QIcon(":/designer/shape-align-center"));
    actionGroupAlignCenter->setEnabled(false);

    actionPointerTool = new QAction(this);
    actionPointerTool->setObjectName(QString::fromUtf8("actionPointerTool"));
    actionPointerTool->setIcon(QIcon(":/designer/pointer-tool"));
    actionPointerTool->setCheckable(true);

    actionHandTool = new QAction(this);
    actionHandTool->setObjectName(QString::fromUtf8("actionHandTool"));
    actionHandTool->setIcon(QIcon(":/designer/hand-tool"));
    actionHandTool->setCheckable(true);

    actionSelectTool = new QAction(this);
    actionSelectTool->setObjectName(QString::fromUtf8("actionSelectTool"));
    actionSelectTool->setIcon(QIcon(":/designer/select-tool"));
    actionSelectTool->setCheckable(true);

    actionAddParametere = new QAction(this);
    actionAddParametere->setObjectName(QString::fromUtf8("actionAddParametere"));
    actionAddParametere->setIcon(QIcon(":/designer/form-add"));


    actionSameLeft = new QAction(this);
    actionSameLeft->setObjectName(QString::fromUtf8("actionSameLeft"));
    actionSameLeft->setIcon(QIcon(":/designer/all-align-left"));
    actionSameLeft->setEnabled(false);

    actionSameTop = new QAction(this);
    actionSameTop->setObjectName(QString::fromUtf8("actionSameTop"));
    actionSameTop->setIcon(QIcon(":/designer/all-align-top"));
    actionSameTop->setEnabled(false);

    actionSameRight = new QAction(this);
    actionSameRight->setObjectName(QString::fromUtf8("actionSameRight"));
    actionSameRight->setIcon(QIcon(":/designer/all-align-right"));
    actionSameRight->setEnabled(false);

    actionSameBottom = new QAction(this);
    actionSameBottom->setObjectName(QString::fromUtf8("actionSameBottom"));
    actionSameBottom->setIcon(QIcon(":/designer/all-align-bottom"));
    actionSameBottom->setEnabled(false);

    actionSameSize = new QAction(this);
    actionSameSize->setObjectName(QString::fromUtf8("actionSameSize"));
    actionSameSize->setIcon(QIcon(":/designer/same-size"));
    actionSameSize->setEnabled(false);

    actionSameWidth = new QAction(this);
    actionSameWidth->setObjectName(QString::fromUtf8("actionSameWidth"));
    actionSameWidth->setIcon(QIcon(":/designer/same-size-width"));
    actionSameWidth->setEnabled(false);

    actionSameHeight = new QAction(this);
    actionSameHeight->setObjectName(QString::fromUtf8("actionSameHeight"));
    actionSameHeight->setIcon(QIcon(":/designer/same-size-height"));
    actionSameHeight->setEnabled(false);


    connect(actionAlignLeft,    SIGNAL(triggered()), this, SLOT(actionAlign_triggered()));
    connect(actionAlignCenter,  SIGNAL(triggered()), this, SLOT(actionAlign_triggered()));
    connect(actionAlignRight,   SIGNAL(triggered()), this, SLOT(actionAlign_triggered()));
    connect(actionAlignTop,     SIGNAL(triggered()), this, SLOT(actionAlign_triggered()));
    connect(actionAlignMiddle,  SIGNAL(triggered()), this, SLOT(actionAlign_triggered()));
    connect(actionAlignBottom,  SIGNAL(triggered()), this, SLOT(actionAlign_triggered()));
    connect(actionAlignJustify, SIGNAL(triggered()), this, SLOT(actionAlign_triggered()));

    connect(actionInsertTextbox,        SIGNAL(triggered()), this, SLOT(actionInsertWidget_triggered()));
    connect(actionInsertImage,          SIGNAL(triggered()), this, SLOT(actionInsertWidget_triggered()));
    connect(actionInsertVerticalLine,   SIGNAL(triggered()), this, SLOT(actionInsertWidget_triggered()));
    connect(actionInsertHorizontalLine, SIGNAL(triggered()), this, SLOT(actionInsertWidget_triggered()));
    connect(actionInsertRectangle,      SIGNAL(triggered()), this, SLOT(actionInsertWidget_triggered()));

    connect(actionInsertReportHeader, SIGNAL(triggered()), this, SLOT(actionInsertBand_triggered()));
    connect(actionInsertPageHeader,   SIGNAL(triggered()), this, SLOT(actionInsertBand_triggered()));
    connect(actionInsertGroupHeader,  SIGNAL(triggered()), this, SLOT(actionInsertBand_triggered()));
    connect(actionInsertData,         SIGNAL(triggered()), this, SLOT(actionInsertBand_triggered()));
    connect(actionInsertGroupFooter,  SIGNAL(triggered()), this, SLOT(actionInsertBand_triggered()));
    connect(actionInsertPageFooter,   SIGNAL(triggered()), this, SLOT(actionInsertBand_triggered()));
    connect(actionInsertReportFooter, SIGNAL(triggered()), this, SLOT(actionInsertBand_triggered()));
}

void LReportDesignerFactory::initActionGroups()
{
    QActionGroup *groupAlign = new QActionGroup(mainWindow);
    groupAlign->addAction(actionAlignRight);
    groupAlign->addAction(actionAlignCenter);
    groupAlign->addAction(actionAlignLeft);
    groupAlign->addAction(actionAlignJustify);
    actionAlignLeft->setChecked(true);

    QActionGroup *groupAlignV = new QActionGroup(mainWindow);
    groupAlignV->addAction(actionAlignTop);
    groupAlignV->addAction(actionAlignMiddle);
    groupAlignV->addAction(actionAlignBottom);
    actionAlignTop->setChecked(true);

    QActionGroup *groupGrid = new QActionGroup(mainWindow);
    groupGrid->addAction(actionGridNone);
    groupGrid->addAction(actionGridDots);
    groupGrid->addAction(actionGridLines);
    actionGridDots->setChecked(true);

    groupZoom = new QActionGroup(mainWindow);
    groupZoom->addAction(actionZoom25);
    groupZoom->addAction(actionZoom50);
    groupZoom->addAction(actionZoom75);
    groupZoom->addAction(actionZoom100);
    groupZoom->addAction(actionZoom200);
    groupZoom->addAction(actionZoom400);
    actionZoom100->setChecked(true);

    QActionGroup *groupTool = new QActionGroup(mainWindow);
    //groupTool->addAction( actionPointerTool );
    groupTool->addAction(actionSelectTool);
    groupTool->addAction(actionHandTool);
    actionSelectTool->setChecked(true);
}

void LReportDesignerFactory::initMenubar()
{
    menubar = new QMenuBar(mainWindow);
    menubar->setObjectName(QString::fromUtf8("menubar"));

    menubar->setGeometry(QRect(0, 0, 371, 21));
    menuHelp = new QMenu(menubar);
    menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
    menuInsert = new QMenu(menubar);
    menuInsert->setObjectName(QString::fromUtf8("menuInsert"));
    menuEdit = new QMenu(menubar);
    menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
    menuFile = new QMenu(menubar);
    menuFile->setObjectName(QString::fromUtf8("menuFile"));
    menuFormat = new QMenu(menubar);
    menuFormat->setObjectName(QString::fromUtf8("menuFormat"));
    menuView = new QMenu(menubar);
    menuView->setObjectName(QString::fromUtf8("menuView"));
    menuZoom = new QMenu(menuView);
    menuZoom->setObjectName(QString::fromUtf8("menuZoom"));
    menuGrid = new QMenu(menuView);
    menuGrid->setObjectName(QString::fromUtf8("menuGrid"));
    menuReport = new QMenu(menubar);
    menuReport->setObjectName(QString::fromUtf8("menuReport"));

    // menubar
    menubar->addAction(menuFile->menuAction());
    menubar->addAction(menuEdit->menuAction());
    menubar->addAction(menuView->menuAction());
    menubar->addAction(menuFormat->menuAction());
    menubar->addAction(menuReport->menuAction());
    menubar->addAction(menuInsert->menuAction());
    menubar->addAction(menuHelp->menuAction());

    menuHelp->addAction(actionHelp);
    menuHelp->addAction(actionAbout);
    menuHelp->addAction(actionAbout_Qt);

    //menuInsert->addAction(actionPointerTool);
    menuInsert->addAction(actionSelectTool);
    menuInsert->addAction(actionHandTool);
    menuInsert->addSeparator();
    menuInsert->addAction(actionInsertTextbox);
    menuInsert->addAction(actionInsertImage);
    menuInsert->addAction(actionInsertVerticalLine);
    menuInsert->addAction(actionInsertHorizontalLine);
    menuInsert->addAction(actionInsertRectangle);
    menuInsert->addSeparator();
    menuInsert->addAction(actionInsertReportHeader);
    menuInsert->addAction(actionInsertPageHeader);
    menuInsert->addAction(actionInsertGroupHeader);
    menuInsert->addAction(actionInsertData);
    menuInsert->addAction(actionInsertGroupFooter);
    menuInsert->addAction(actionInsertPageFooter);
    menuInsert->addAction(actionInsertReportFooter);

    menuEdit->addAction(actionUndo);
    menuEdit->addAction(actionRedo);
    menuEdit->addSeparator();
    menuEdit->addAction(actionCut);
    menuEdit->addAction(actionCopy);
    menuEdit->addAction(actionPaste);
    menuEdit->addSeparator();
    menuEdit->addAction(actionSelect_All);
    menuEdit->addAction(actionDelete);

    menuFile->addAction(actionNew);
    menuFile->addAction(actionOpen);
    menuFile->addAction(actionSave);
    menuFile->addAction(actionSave_As);
    menuFile->addSeparator();
    menuFile->addAction(actionPrint_Setup);
    menuFile->addAction(actionPrint);
    menuFile->addAction(actionPrint_preview);
    menuFile->addSeparator();
    menuFile->addAction(actionExit);

    menuAlign = new QMenu(menuFormat);
    menuAlign->addAction(actionAlignToGrid);
    menuAlign->addSeparator();
    menuAlign->addAction(actionSameSize);
    menuAlign->addAction(actionSameWidth);
    menuAlign->addAction(actionSameHeight);
    menuAlign->addSeparator();
    menuAlign->addAction(actionSameLeft);
    menuAlign->addAction(actionSameTop);
    menuAlign->addAction(actionSameRight);
    menuAlign->addAction(actionSameBottom);

    menuFormat->addMenu(menuAlign);
    menuFormat->addSeparator();
    menuFormat->addAction(actionBold);
    menuFormat->addAction(actionItalic);
    menuFormat->addAction(actionUnderline);
    menuFormat->addSeparator();
    menuFormat->addAction(actionAlignLeft);
    menuFormat->addAction(actionAlignCenter);
    menuFormat->addAction(actionAlignRight);
    menuFormat->addAction(actionAlignJustify);
    menuFormat->addAction(actionAlignTop);
    menuFormat->addAction(actionAlignMiddle);
    menuFormat->addAction(actionAlignBottom);
    menuFormat->addSeparator();
    menuFormat->addAction(actionSendToBack);
    menuFormat->addAction(actionBringToFront);
    menuFormat->addSeparator();
    menuFormat->addAction(actionProperties);

    //Report
    menuReport->addMenu(treeWidgetFields->createContextMenu());
    menuReport->addSeparator();
    menuReport->addAction(actionSectionsProperties);
    menuReport->addSeparator();
    menuReport->addAction(actionSetDatabase);
    menuReport->addAction(actionSetDataSource);
    menuReport->addSeparator();
    menuReport->addAction(actionAddParametere);

    // View
    QList<QAction*> menuToolbars = mainWindow->createPopupMenu()->actions();

    for (int i =  0; i < menuToolbars.count(); i ++)
        menuView->addAction(menuToolbars[i]);

    menuView->addSeparator();
    menuView->addAction(menuZoom->menuAction());
    menuView->addAction(menuGrid->menuAction());
    menuView->addAction(actionAlignToGridOption);
    menuView->addAction(actionShowRulers);

    menuZoom->addAction(actionZoom25);
    menuZoom->addAction(actionZoom50);
    menuZoom->addAction(actionZoom75);
    menuZoom->addAction(actionZoom100);
    menuZoom->addAction(actionZoom200);
    menuZoom->addAction(actionZoom400);
    menuGrid->addAction(actionGridNone);
    menuGrid->addAction(actionGridDots);
    menuGrid->addAction(actionGridLines);

    mainWindow->setMenuBar(menubar);
}

void LReportDesignerFactory::initToolbars()
{
    toolBarStandard = new QToolBar("Standard", mainWindow);
    toolBarStandard->setObjectName("standardToolBar");

    toolBarFormating = new QToolBar("Formating", mainWindow);
    toolBarFormating->setObjectName("formatingToolBar");

    toolBarToolbox = new QToolBar("Toolbox", mainWindow);
    toolBarToolbox->setObjectName("toolboxToolbar");

    toolBarDesign = new QToolBar("Design", mainWindow);
    toolBarDesign->setObjectName("toolBarDesign");

    //toolBarToolbox->addAction(actionPointerTool);
    toolBarToolbox->addAction(actionSelectTool);
    toolBarToolbox->addAction(actionHandTool);
    toolBarToolbox->addSeparator();
    toolBarToolbox->addAction(actionInsertTextbox);
    toolBarToolbox->addAction(actionInsertImage);
    toolBarToolbox->addAction(actionInsertVerticalLine);
    toolBarToolbox->addAction(actionInsertHorizontalLine);
    toolBarToolbox->addAction(actionInsertRectangle);
    toolBarToolbox->addSeparator();
    toolBarToolbox->addAction(actionInsertReportHeader);
    toolBarToolbox->addAction(actionInsertPageHeader);
    toolBarToolbox->addAction(actionInsertGroupHeader);
    toolBarToolbox->addAction(actionInsertData);
    toolBarToolbox->addAction(actionInsertGroupFooter);
    toolBarToolbox->addAction(actionInsertPageFooter);
    toolBarToolbox->addAction(actionInsertReportFooter);

    toolBarStandard->addAction(actionNew);
    toolBarStandard->addAction(actionOpen);
    toolBarStandard->addAction(actionSave);
    toolBarStandard->addAction(actionPrint);
    toolBarStandard->addAction(actionPrint_Setup);
    toolBarStandard->addAction(actionPrint_preview);
    toolBarStandard->addSeparator();
    toolBarStandard->addAction(actionCut);
    toolBarStandard->addAction(actionCopy);
    toolBarStandard->addAction(actionPaste);
    toolBarStandard->addAction(actionSelect_All);
    toolBarStandard->addAction(actionDelete);
    toolBarStandard->addSeparator();
    toolBarStandard->addAction(actionUndo);
    toolBarStandard->addAction(actionRedo);
    toolBarStandard->addSeparator();
    toolBarStandard->addAction(actionAlignToGridOption);


    actionFontName = toolBarFormating->addWidget(fontComboBox);
    actionFontName->setEnabled(false);
    //actionForeColor = toolBarFormating->addWidget( p );
    //actionForeColor->setEnabled(false);

    actionFontSize = toolBarFormating->addWidget(comboboxFontSize);
    actionFontSize->setEnabled(false);


    toolBarFormating->addAction(actionBold);
    toolBarFormating->addAction(actionItalic);
    toolBarFormating->addAction(actionUnderline);
    toolBarFormating->addSeparator();
    toolBarFormating->addAction(actionAlignLeft);
    toolBarFormating->addAction(actionAlignCenter);
    toolBarFormating->addAction(actionAlignRight);
    toolBarFormating->addAction(actionAlignJustify);
    toolBarFormating->addAction(actionAlignTop);
    toolBarFormating->addAction(actionAlignMiddle);
    toolBarFormating->addAction(actionAlignBottom);
    toolBarFormating->addSeparator();
    toolBarFormating->addAction(actionSendToBack);
    toolBarFormating->addAction(actionBringToFront);
    toolBarFormating->addSeparator();
    toolBarFormating->addAction(actionProperties);


    toolBarDesign->addAction(actionAlignToGrid);
    toolBarDesign->addSeparator();
    toolBarDesign->addAction(actionSameSize);
    toolBarDesign->addAction(actionSameWidth);
    toolBarDesign->addAction(actionSameHeight);
    toolBarDesign->addSeparator();
    toolBarDesign->addAction(actionSameLeft);
    toolBarDesign->addAction(actionSameTop);
    toolBarDesign->addAction(actionSameRight);
    toolBarDesign->addAction(actionSameBottom);


    mainWindow->addToolBar(toolBarStandard);
    mainWindow->addToolBar(toolBarDesign);
    mainWindow->addToolBarBreak();
    mainWindow->addToolBar(toolBarFormating);

    mainWindow->addToolBar(Qt::LeftToolBarArea, toolBarToolbox);

}

void LReportDesignerFactory::initDockWidgets()
{
    // Report items
    reportItemsDock = new QDockWidget(mainWindow);
    reportItemsDock->setObjectName("reportItemsDock");
    reportItemsDock->setWindowTitle("Report items");
    treeWidgetFields = new LReportTreeManager(mainWindow, _designer, _report);
    treeWidgetFields->setObjectName("treeWidgetFields");

    reportItemsDock->setWidget(treeWidgetFields);
    mainWindow->addDockWidget(Qt::RightDockWidgetArea, reportItemsDock);

    //
    undoViewDock = new QDockWidget(mainWindow);
    undoViewDock->setObjectName("undoViewDock");
    undoViewDock->setWindowTitle("Undo view");

    undoView = new QUndoView(_designer->undoStack(), mainWindow);
    undoView->setEmptyLabel(tr("<New document>"));

    undoViewDock->setWidget(undoView);
    mainWindow->addDockWidget(Qt::RightDockWidgetArea, undoViewDock);

}

void LReportDesignerFactory::initStatusBar()
{
    statusbar = new QStatusBar(mainWindow);
    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    mainWindow->setStatusBar(statusbar);
    QSlider *sliderZoom = new QSlider(mainWindow);
    sliderZoom->setObjectName("sliderZoom");
    sliderZoom->setMaximumWidth(150);
    sliderZoom->setValue(100);
    sliderZoom->setMinimum(0);
    sliderZoom->setMaximum(200);
    sliderZoom->setOrientation(Qt::Horizontal);
    statusbar->addPermanentWidget(sliderZoom);
    connect(sliderZoom, SIGNAL(valueChanged(int)), this, SLOT(sliderZoom_valueChanged(int)));
}

void LReportDesignerFactory::initWidgets()
{
    fontComboBox = new QFontComboBox(mainWindow);
    fontComboBox->setObjectName("fontComboBox");
    connect(fontComboBox, SIGNAL(currentIndexChanged(QString)),
            this,         SLOT(fontComboBox_currentIndexChanged(QString)));

    //p = new QColorPickerTool( mainWindow );



    comboboxFontSize = new QComboBox(mainWindow);
    comboboxFontSize->setObjectName("comboboxFontSize");
    comboboxFontSize->addItems(QStringList() << "8" << "10" << "11" << "12" << "14"
                               << "16" << "18" << "20" << "24" << "26" << "28"
                               << "36" << "48" << "72");
    connect(comboboxFontSize, SIGNAL(currentIndexChanged(QString)),
            this,             SLOT(comboboxFontSize_currentIndexChanged(QString)));


}


void LReportDesignerFactory::retranslateUi()
{
    actionNew->setShortcut(tr("Ctrl+N"));
    actionSave->setShortcut(tr("Ctrl+S"));
    actionPrint->setShortcut(tr("Ctrl+P"));
    actionHelp->setShortcut(tr("F1"));
    actionItalic->setShortcut(tr("Ctrl+I"));
    actionCopy->setShortcut(tr("Ctrl+C"));
    actionCut->setShortcut(tr("Ctrl+X"));
    actionRedo->setShortcut(tr("Ctrl+Shift+Z"));
    actionUndo->setShortcut(tr("Ctrl+Z"));
    actionUnderline->setShortcut(tr("Ctrl+U"));
    actionBold->setShortcut(tr("Ctrl+B"));
    actionOpen->setShortcut(tr("Ctrl+O"));
    actionDelete->setShortcut(tr("Del"));
    actionSelect_All->setShortcut(tr("Ctrl+A"));
    actionPaste->setShortcut(tr("Ctrl+V"));
    actionSectionsProperties->setShortcut(tr("Ctrl+Alt+S"));

    mainWindow->setWindowTitle(tr("QtReport"));


    actionZoom25->setText(tr("25%"));
    actionZoom50->setText(tr("50%"));
    actionZoom75->setText(tr("75%"));
    actionZoom100->setText(tr("100%"));
    actionZoom200->setText(tr("200%"));
    actionZoom400->setText(tr("400%"));
    actionNew->setText(tr("New"));
    actionSave->setText(tr("Save"));
    actionSave_As->setText(tr("Save As..."));
    actionPrint_Setup->setText(tr("Print Setup"));
    actionPrint_preview->setText(tr("Print preview"));
    actionPrint->setText(tr("Print..."));
    actionExit->setText(tr("Exit"));
    actionAbout->setText(tr("About..."));
    actionHelp->setText(tr("Help"));
    actionInsertTextbox->setText(tr("Textbox"));
    actionInsertImage->setText(tr("Image"));
    actionInsertVerticalLine->setText(tr("Vertical Line"));
    actionInsertHorizontalLine->setText(tr("Horizontal Line"));
    actionInsertPageHeader->setText(tr("Page header"));
    actionInsertReportHeader->setText(tr("Report header"));
    actionInsertGroupHeader->setText(tr("Group header"));
    actionInsertData->setText(tr("Data"));
    actionInsertGroupFooter->setText(tr("Group footer"));
    actionInsertReportFooter->setText(tr("Report footer"));
    actionInsertPageFooter->setText(tr("Page footer"));
    actionInsertRectangle->setText(tr("Rectangle"));
    actionAlignToGridOption->setText(tr("Align to grid"));
    actionAlignToGrid->setText(tr("Adjust size by grid"));
    actionShowRulers->setText(tr("Rulers"));
    actionGridNone->setText(tr("None"));
    actionGridDots->setText(tr("Dots"));
    actionGridLines->setText(tr("Lines"));
    actionAbout_Qt->setText(tr("About Qt..."));
    actionBold->setText(tr("Bold"));
    actionItalic->setText(tr("Italic"));
    actionUnderline->setText(tr("Underline"));
    actionUndo->setText(tr("Undo"));
    actionRedo->setText(tr("Redo"));
    actionCut->setText(tr("Cut"));
    actionCopy->setText(tr("Copy"));
    actionPaste->setText(tr("Paste"));
    actionSelect_All->setText(tr("Select All"));
    actionDelete->setText(tr("Delete"));
    actionOpen->setText(tr("Open"));
    actionAlignLeft->setText(tr("Align left"));
    actionAlignRight->setText(tr("Align right"));
    actionAlignCenter->setText(tr("Align center"));
    actionAlignTop->setText(tr("Align top"));
    actionAlignMiddle->setText(tr("Align middle"));
    actionAlignBottom->setText(tr("Align bottom"));
    actionAlignJustify->setText(tr("Align justify"));
    actionProperties->setText(tr("Properties"));
    actionSetDatabase->setText(tr("Set database"));
    actionSetDataSource->setText(tr("Select tables"));
    actionSendToBack->setText(tr("Send to back"));
    actionBringToFront->setText(tr("Bring to front"));
    actionAddParametere->setText(tr("Add parametere"));

    actionSectionsProperties->setText(tr("Section settings"));

    actionSameLeft->setText(tr("Align left"));
    actionSameTop->setText(tr("Align top"));
    actionSameRight->setText(tr("Align right"));
    actionSameBottom->setText(tr("Align bottom"));
    actionSameSize->setText(tr("Make same size"));
    actionSameWidth->setText(tr("Make same width"));
    actionSameHeight->setText(tr("Make same height"));

    actionPointerTool->setText(tr("Pointer"));
    actionHandTool->setText(tr("Hand tool"));
    actionSelectTool->setText(tr("Select tool"));

    menuHelp->setTitle(tr("Help"));
    menuInsert->setTitle(tr("Toolbox"));
    menuEdit->setTitle(tr("Edit"));
    menuFile->setTitle(tr("File"));
    menuFormat->setTitle(tr("Format"));
    menuView->setTitle(tr("View"));
    menuZoom->setTitle(tr("Zoom"));
    menuGrid->setTitle(tr("Grid"));
    menuReport->setTitle(tr("Report"));
    menuAlign->setTitle(tr("Align"));

    toolBarStandard->setWindowTitle(tr("Standard"));
    toolBarToolbox->setWindowTitle(tr("Toolbox"));
    toolBarFormating->setWindowTitle(tr("Formating"));
}







void LReportDesignerFactory::actionInsertWidget_triggered()
{
   _designer->addContent(dynamic_cast<QAction*>(sender())->data().toString());
}

void LReportDesignerFactory::actionInsertBand_triggered()
{
   BandType type = (BandType)dynamic_cast<QAction*>(sender())->data().toInt();
   LReportBand *band = new LReportBand(type);
   band->setBandHeight(50);
   _designer->addBand(band);
}

void LReportDesignerFactory::doc_widgetContextMenuEvent()
{
    QMenu menu;


    menu.addAction(actionCut);
    menu.addAction(actionCopy);
    menu.addAction(actionPaste);
    menu.addAction(actionDelete);
    menu.addAction(actionSelect_All);
    menu.addSeparator();
    menu.addAction(actionSendToBack);
    menu.addAction(actionBringToFront);

    if (currentWidgetAtions.count() != 0) {
        menu.addSeparator();
        foreach(QAction  *action, currentWidgetAtions)
        menu.addAction(action);
    }//if

    menu.addSeparator();
    menu.addAction(actionProperties);

    menu.exec(QCursor::pos());
}

// Actions events

void LReportDesignerFactory::on_actionZoom50_triggered()
{
    _designer->setZoom(50);
}

void LReportDesignerFactory::on_actionZoom400_triggered()
{
    _designer->setZoom(400);
}

void LReportDesignerFactory::on_actionZoom25_triggered()
{
    _designer->setZoom(25);
}

void LReportDesignerFactory::on_actionZoom75_triggered()
{
    _designer->setZoom(75);
}

void LReportDesignerFactory::on_actionZoom100_triggered()
{
    _designer->setZoom(100);
}

void LReportDesignerFactory::on_actionZoom200_triggered()
{
    _designer->setZoom(200);
}

void LReportDesignerFactory::on_actionAbout_triggered()
{
    LReportDesignerAboutDialog about(mainWindow);
    about.exec();
}

void LReportDesignerFactory::on_actionSave_triggered()
{
    if(_report->filePath().isEmpty())
        on_actionSave_As_triggered();
    else
        _report->save();
}

void LReportDesignerFactory::on_actionPrint_Setup_triggered()
{
    /* QPageSetupDialog *dialog = new QPageSetupDialog( mainWindow );

     if( dialog->exec() )
     {

        //doc->setM
     }//if
  */
    _designer->showPageSetup();
}

void LReportDesignerFactory::on_actionPrint_triggered()
{
    _report->print();
}

void LReportDesignerFactory::on_actionGridDots_triggered()
{
    _designer->setGridType(DotGrid);
}

void LReportDesignerFactory::on_actionGridLines_triggered()
{
    _designer->setGridType(LinesGrid);
}

void LReportDesignerFactory::on_actionGridNone_triggered()
{
    _designer->setGridType(NoGrid);
}

void LReportDesignerFactory::on_actionAbout_Qt_triggered()
{
    qApp->aboutQt();
}

void LReportDesignerFactory::on_actionAlignToGridOption_triggered()
{
    _designer->setAlignToGrid(actionAlignToGridOption->isChecked());
}

void LReportDesignerFactory::on_actionShowRulers_triggered()
{
    _designer->setShowRulers(actionShowRulers->isChecked());
}

void LReportDesignerFactory::on_actionExit_triggered()
{
    qApp->quit();
}

void LReportDesignerFactory::on_actionNew_triggered()
{
    /*
    LReportDatabaseInfoDialog *dialog = new LReportDatabaseInfoDialog(_report);
    dialog->exec();
    LReportDatabaseTablesDialog *tablesDialog = new LReportDatabaseTablesDialog(_report);
    tablesDialog->exec();

    for (int i = 0; i < nodeDataSource->childCount(); i++)
        nodeDataSource->removeChild(nodeDataSource->child(i));

    for (int i = 0; i < _report->tables().count(); i++) {
        QTreeWidgetItem *item = new QTreeWidgetItem;
        item->setText(0, _report->tables().at(i)->name());
        item->setIcon(0, QIcon(":/designer/table"));
        nodeDataSource->addChild(item);

        for (int j = 0; j < _report->tables().at(i)->fields().count(); j++) {
            QTreeWidgetItem *itemChild = new QTreeWidgetItem;
            itemChild->setText(0, _report->tables().at(i)->fields().at(j).name());
            itemChild->setIcon(0, QIcon(":/designer/field"));
            item->addChild(itemChild);
        }//for
    }
    */
    _designer->clear();
}

void LReportDesignerFactory::on_actionCopy_triggered()
{
    //RReportWidgetBase *w = doc->activeWidget();
    //QClipboard::setUserData
}


void LReportDesignerFactory::updateActions()
{
    if (_designer->hasWidgetProperty("font")) {
        QFont font = _designer->widgetProperty("font").value<QFont>();

        actionBold->setChecked(font.bold());
        actionItalic->setChecked(font.italic());
        actionUnderline->setChecked(font.underline());
    }//
    if (_designer->hasWidgetProperty("align")) {
        Qt::Alignment align = (Qt::Alignment)_designer->widgetProperty("align").value<int>();

        actionAlignLeft   ->setChecked(align & Qt::AlignLeft);
        actionAlignCenter ->setChecked(align & Qt::AlignHCenter);
        actionAlignRight  ->setChecked(align & Qt::AlignRight);
        actionAlignJustify->setChecked(align & Qt::AlignJustify);

        actionAlignTop    ->setChecked(align & Qt::AlignTop);
        actionAlignMiddle ->setChecked(align & Qt::AlignVCenter);
        actionAlignBottom ->setChecked(align & Qt::AlignBottom);
    }
}

void LReportDesignerFactory::doc_activeWidgetChanged()
{
    int count = _designer->selectedWidgets().count();
    actionCut->setEnabled(count);
    actionCopy->setEnabled(count);
    actionDelete->setEnabled(count);

    actionSameSize->setEnabled(count > 1);
    actionSameWidth->setEnabled(count > 1);
    actionSameHeight->setEnabled(count > 1);
    actionSameLeft->setEnabled(count > 1);
    actionSameTop->setEnabled(count > 1);
    actionSameRight->setEnabled(count > 1);
    actionSameBottom->setEnabled(count > 1);

    actionAlignRight     ->setEnabled(_designer->hasWidgetProperty("align"));
    actionAlignLeft      ->setEnabled(_designer->hasWidgetProperty("align"));
    actionAlignCenter    ->setEnabled(_designer->hasWidgetProperty("align"));
    actionAlignJustify   ->setEnabled(_designer->hasWidgetProperty("align"));
    actionAlignTop       ->setEnabled(_designer->hasWidgetProperty("align"));
    actionAlignMiddle    ->setEnabled(_designer->hasWidgetProperty("align"));
    actionAlignBottom    ->setEnabled(_designer->hasWidgetProperty("align"));

    actionFontName       ->setEnabled(_designer->hasWidgetProperty("font"));
    //actionForeColor      ->setEnabled( doc->hasWidgetProperty( "backColor" ) );
    actionBold           ->setEnabled(_designer->hasWidgetProperty("font"));
    actionItalic         ->setEnabled(_designer->hasWidgetProperty("font"));
    actionUnderline      ->setEnabled(_designer->hasWidgetProperty("font"));
    actionFontSize       ->setEnabled(_designer->hasWidgetProperty("font"));

    actionProperties     ->setEnabled(true);
    actionSendToBack     ->setEnabled(true);
    actionBringToFront   ->setEnabled(true);

    currentWidgetAtions.clear();

    updateActions();


    if (_designer->hasWidgetProperty("align")) {
        currentWidgetAtions.append(actionAlignRight);
        currentWidgetAtions.append(actionAlignLeft);
        currentWidgetAtions.append(actionAlignCenter);
        currentWidgetAtions.append(actionAlignJustify);
        currentWidgetAtions.append(actionAlignTop);
        currentWidgetAtions.append(actionAlignMiddle);
        currentWidgetAtions.append(actionAlignBottom);
    }//if

    if (_designer->hasWidgetProperty("font")) {
        //currentWidgetAtions.append( actionFontName );
        //currentWidgetAtions.append( actionForeColor );
        currentWidgetAtions.append(actionBold);
        currentWidgetAtions.append(actionItalic);
        currentWidgetAtions.append(actionUnderline);
    }//if


    actionProperties->setEnabled(true);
}

void LReportDesignerFactory::doc_dataDirectoryModified()
{
    qDebug() << "doc_dataDirectoryModified";
    treeWidgetFields->initTreeItems();
}

void LReportDesignerFactory::on_actionSave_As_triggered()
{
    QString filePath =
        QFileDialog::getSaveFileName(mainWindow,
                                     tr("Save File"),
                                     QDir::homePath(),
                                     tr("QtReport files(*.qtr);;All files(*)"));
    _report->save(filePath);
}

void LReportDesignerFactory::on_actionOpen_triggered()
{
    QString filePath =
        QFileDialog::getOpenFileName(mainWindow,
                                     tr("Save File"),
                                     QDir::homePath(),
                                     tr("QtReport files(*.qtr);;All files(*)"));

    _designer->clear();
    _report->load(filePath);
    _designer->loadReport();
    treeWidgetFields->initTreeItems();
}

void LReportDesignerFactory::on_actionProperties_triggered()
{
    _designer->showWidgetProperties();
}

void LReportDesignerFactory::on_actionSetDatabase_triggered()
{
    LReportDatabaseInfoDialog *dialog = new LReportDatabaseInfoDialog(_report);
    dialog->exec();
    delete dialog;
}

void LReportDesignerFactory::on_actionSetDataSource_triggered()
{
    NewConnectionWizard wizard(_designer);
    wizard.exec();
    /*TODO
    LReportDatabaseTablesDialog *tablesDialog = new LReportDatabaseTablesDialog(_report);
    tablesDialog->exec();

    for (int i = 0; i < nodeDataSource->childCount(); i++)
        nodeDataSource->removeChild(nodeDataSource->child(i));

    for (int i = 0; i < _report->tables().count(); i++) {
        QTreeWidgetItem *item = new QTreeWidgetItem;
        item->setText(0, _report->tables().at(i)->name());
        item->setIcon(0, QIcon(":/designer/table"));
        nodeDataSource->addChild(item);

        for (int j = 0; j < _report->tables().at(i)->fields().count(); j++) {
            QTreeWidgetItem *itemChild = new QTreeWidgetItem;
            itemChild->setText(0, _report->tables().at(i)->fields().at(j).name());
            itemChild->setIcon(0, QIcon(":/designer/field"));
            item->addChild(itemChild);
        }//for
    }

    delete tablesDialog;
    */
}

void LReportDesignerFactory::on_actionSendToBack_triggered()
{
    _designer->sendToBack();
}

void LReportDesignerFactory::on_actionBringToFront_triggered()
{
    _designer->bringToFront();
}

void LReportDesignerFactory::on_actionPointerTool_triggered()
{
    //TODO: _document moved to Private class
    //    _designer->_document->setDragMode(QGraphicsView::NoDrag);
}

void LReportDesignerFactory::on_actionHandTool_triggered()
{
    //TODO: _document moved to Private class
    //    _designer->_document->setDragMode(QGraphicsView::ScrollHandDrag);
    _designer->setMouseTool(Hand);
}

void LReportDesignerFactory::on_actionSelectTool_triggered()
{
    //TODO: _document moved to Private class
    //    _designer->_document->setDragMode(QGraphicsView::RubberBandDrag);
    _designer->setMouseTool(Pointer);
}

void LReportDesignerFactory::on_actionAddParametere_triggered()
{
    /*
    LReportParametereDialog *dialog = new LReportParametereDialog(mainWindow);
    dialog->exec();

    if (dialog->result() == QDialog::Accepted) {
        _report->addParametere(dialog->name(), dialog->defaultValue());

        for (int i = 0; i < nodeParameters->childCount(); i++)
            nodeParameters->removeChild(nodeParameters->child(i));

        for (int i = 0; i < _report->parameters().count(); i++) {
            QTreeWidgetItem *item = new QTreeWidgetItem;
            item->setText(0, _report->parameters().at(i).name());
            //item->setIcon( 0, QIcon(":/designer/table") );
            nodeParameters->addChild(item);
        }//for
    }//if
    */
}

void LReportDesignerFactory::on_actionBold_triggered()
{
    QFont font = _designer->widgetProperty("font").value<QFont>();
    font.setBold(actionBold->isChecked());
    _designer->setWidgetProperty("font", font);
    _designer->updateWidgets();
}

void LReportDesignerFactory::on_actionItalic_triggered()
{
    QFont font = _designer->widgetProperty("font").value<QFont>();
    font.setItalic(actionItalic->isChecked());
    _designer->setWidgetProperty("font", font);
    _designer->updateWidgets();
}

void LReportDesignerFactory::on_actionUnderline_triggered()
{
    QFont font = _designer->widgetProperty("font").value<QFont>();
    font.setUnderline(actionUnderline->isChecked());
    _designer->setWidgetProperty("font", font);
    _designer->updateWidgets();
}

void LReportDesignerFactory::on_actionSameLeft_triggered()
{
    _designer->setAlign(Left);
}

void LReportDesignerFactory::on_actionSameTop_triggered()
{
    _designer->setAlign(Top);
}

void LReportDesignerFactory::on_actionSameRight_triggered()
{
    _designer->setAlign(Right);
}

void LReportDesignerFactory::on_actionSameBottom_triggered()
{
    _designer->setAlign(Bottom);
}

void LReportDesignerFactory::on_actionSectionsProperties_triggered()
{
    LReportSectionsProperties prop(mainWindow, _designer, _report);
    prop.exec();
}

void LReportDesignerFactory::comboboxFontSize_currentIndexChanged(const QString& text)
{
    bool ok;
    int size = text.toInt(&ok);
    if (ok) {
        QFont font = _designer->widgetProperty("font").value<QFont>();
        font.setPointSize(size);
        _designer->setWidgetProperty("font", font);
        _designer->updateWidgets();
    }//if
}

void LReportDesignerFactory::fontComboBox_currentIndexChanged(const QString& text)
{
    QFont font = _designer->widgetProperty("font").value<QFont>();
    font.setFamily(text);
    _designer->setWidgetProperty("font", font);
    _designer->updateWidgets();
}

void LReportDesignerFactory::actionAlign_triggered()
{
    int align = 0;

    if (actionAlignLeft   ->isChecked()) align |= Qt::AlignLeft;
    if (actionAlignCenter ->isChecked()) align |= Qt::AlignHCenter;
    if (actionAlignRight  ->isChecked()) align |= Qt::AlignRight;
    if (actionAlignTop    ->isChecked()) align |= Qt::AlignTop;
    if (actionAlignMiddle ->isChecked()) align |= Qt::AlignVCenter;
    if (actionAlignBottom ->isChecked()) align |= Qt::AlignBottom;
    if (actionAlignJustify->isChecked()) align |= Qt::AlignJustify;

    _designer->setWidgetProperty("align", align);
    _designer->updateWidgets();
}

void LReportDesignerFactory::sliderZoom_valueChanged(int value)
{
    if(abs(100 - value) < 5){
        qobject_cast<QSlider*>(sender())->setValue(100);
        value = 100;
    }

    int zoomValue;
    if(value < 100)
        zoomValue = (value * 75 / 100) + 25;
    else
        zoomValue = ((value - 100) * 3) + 100;

    _designer->setZoom(zoomValue);
    QString sZoom = QString::number(zoomValue) + "%";

    foreach (QAction *action, groupZoom->actions())
        action->setChecked(action->text() == sZoom);
}

void LReportDesignerFactory::clipboard_dataChanged()
{
    actionPaste->setEnabled(
          QApplication::clipboard()->text().startsWith("<!DOCTYPE ReportDocument>"));
}

LEAF_END_NAMESPACE
