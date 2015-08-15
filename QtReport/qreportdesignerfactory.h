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


#ifndef QREPORTDESIGNERFACTORY_H
#define QREPORTDESIGNERFACTORY_H

#include <QObject>
#include <QMainWindow>

class QAction;
class QToolBar;
class QMenu;
class QMenuBar;
class QStatusBar;
class QTreeWidget;
class QDockWidget;
class QVBoxLayout;
class QReportDocumentDesigner;
class QReport;
class QTreeWidgetItem;
class QComboBox;
class QFontComboBox;
class QColorPicker;
class QColorPickerTool;
class QReportTreeManager;
class QUndoView;
class QActionGroup;
class QReportDesignerFactory : public QObject
{
    Q_OBJECT

public:
    QReportDesignerFactory(QMainWindow *window);

    void initWindow( QMainWindow * );

private:
   QMainWindow *mainWindow;

   void initActions();
   void initToolbars();
   void initMenubar();
   void initActionGroups();
   void initDockWidgets();
   void initStatusBar();
   void initWidgets();
   void retranslateUi();

   void updateActions();

   //Actions:
   QAction *actionZoom25;
   QAction *actionZoom50;
   QAction *actionZoom75;
   QAction *actionZoom100;
   QAction *actionZoom200;
   QAction *actionZoom400;
   QAction *actionNew;
   QAction *actionSave;
   QAction *actionSave_As;
   QAction *actionPrint_Setup;
   QAction *actionPrint_preview;
   QAction *actionPrint;
   QAction *actionExit;
   QAction *actionAbout;
   QAction *actionHelp;
   QAction *actionInsertTextbox;
   QAction *actionInsertImage;
   QAction *actionInsertVerticalLine;
   QAction *actionInsertHorizontalLine;
   QAction *actionInsertPageHeader;
   QAction *actionInsertReportHeader;
   QAction *actionInsertGroupHeader;
   QAction *actionInsertData;
   QAction *actionInsertGroupFooter;
   QAction *actionInsertReportFooter;
   QAction *actionInsertPageFooter;
   QAction *actionInsertRectangle;
   QAction *actionAlignToGridOption;
   QAction *actionAlignToGrid;
   QAction *actionShowRulers;
   QAction *actionGridNone;
   QAction *actionGridDots;
   QAction *actionGridLines;
   QAction *actionAbout_Qt;
   QAction *actionBold;
   QAction *actionItalic;
   QAction *actionUnderline;
   QAction *actionUndo;
   QAction *actionRedo;
   QAction *actionCut;
   QAction *actionCopy;
   QAction *actionPaste;
   QAction *actionSelect_All;
   QAction *actionDelete;
   QAction *actionOpen;
   QAction *actionAlignLeft;
   QAction *actionAlignRight;
   QAction *actionAlignCenter;
   QAction *actionAlignJustify;
   QAction *actionAlignTop;
   QAction *actionAlignMiddle;
   QAction *actionAlignBottom;
   QAction *actionProperties;
   QAction *actionFontName;
   QAction *actionForeColor;
   QAction *actionSetDatabase;
   QAction *actionSetDataSource;
   QAction *actionSendToBack;
   QAction *actionBringToFront;
   QAction *actionGroupAlignLeft;
   QAction *actionGroupAlignRight;
   QAction *actionGroupAlignBottom;
   QAction *actionGroupAlignTop;
   QAction *actionGroupAlignMiddle;
   QAction *actionGroupAlignCenter;
   QAction *actionPointerTool;
   QAction *actionHandTool;
   QAction *actionSelectTool;
   QAction *actionAddParametere;
   QAction *actionFontSize;
   QAction *actionSameTop;
   QAction *actionSameLeft;
   QAction *actionSameRight;
   QAction *actionSameBottom;
   QAction *actionSameSize;
   QAction *actionSameWidth;
   QAction *actionSameHeight;
   QAction *actionSectionsProperties;


   QWidget *centralwidget;
   QMenuBar *menubar;
   QMenu *menuHelp;
   QMenu *menuInsert;
   QMenu *menuEdit;
   QMenu *menuFile;
   QMenu *menuFormat;
   QMenu *menuView;
   QMenu *menuZoom;
   QMenu *menuGrid;
   QMenu *menuReport;
   QMenu *menuAlign;
   QStatusBar *statusbar;

   QDockWidget *reportItemsDock;
   //QWidget *reportItemWidget;
   QVBoxLayout *verticalLayout;

   QDockWidget *undoViewDock;
   QWidget *undoViewWidget;
   QVBoxLayout *undoViewLayout;

   QUndoView *undoView;
   QReportTreeManager *treeWidgetFields;

   QToolBar *toolBarToolbox;
   QToolBar *toolBarStandard;
   QToolBar *toolBarFormating;
   QToolBar *toolBarDesign;

   QComboBox *comboboxFontSize;
   QFontComboBox *fontComboBox;
   QColorPickerTool *p;


   QReportDocumentDesigner *_designer;
   QReport *_report;

   QList<QAction*> currentWidgetAtions;

   QActionGroup *groupZoom;

private slots:
   void clipboard_dataChanged();

   void doc_activeWidgetChanged();
   void doc_dataDirectoryModified();
   void doc_widgetContextMenuEvent();

   void actionInsertWidget_triggered();
   void actionInsertBand_triggered();
   void on_actionProperties_triggered();
   void on_actionOpen_triggered();
   void on_actionCopy_triggered();
   void on_actionNew_triggered();
   void on_actionExit_triggered();
   void on_actionShowRulers_triggered();
   void on_actionAlignToGridOption_triggered();
   void on_actionAbout_Qt_triggered();
   void on_actionGridNone_triggered();
   void on_actionGridLines_triggered();
   void on_actionGridDots_triggered();
   void on_actionPrint_Setup_triggered();
   void on_actionSave_triggered();
   void on_actionSave_As_triggered();
   void on_actionAbout_triggered();
   void on_actionZoom200_triggered();
   void on_actionZoom100_triggered();
   void on_actionZoom75_triggered();
   void on_actionZoom25_triggered();
   void on_actionZoom400_triggered();
   void on_actionZoom50_triggered();
   void on_actionSetDatabase_triggered();
   void on_actionSetDataSource_triggered();
   void on_actionSendToBack_triggered();
   void on_actionBringToFront_triggered();
   void on_actionPointerTool_triggered();
   void on_actionHandTool_triggered();
   void on_actionSelectTool_triggered();
   void on_actionAddParametere_triggered();
   void on_actionBold_triggered();
   void on_actionItalic_triggered();
   void on_actionUnderline_triggered();
   void on_actionSameLeft_triggered();
   void on_actionSameTop_triggered();
   void on_actionSameRight_triggered();
   void on_actionSameBottom_triggered();
   void on_actionSectionsProperties_triggered();
   void actionAlign_triggered();

   void sliderZoom_valueChanged(int);

   void comboboxFontSize_currentIndexChanged ( const QString & text );
   void fontComboBox_currentIndexChanged ( const QString & text );

signals:
   void save(QString fileName);
   void load(QString fileName);
};

#endif // QREPORTDESIGNERFACTORY_H
