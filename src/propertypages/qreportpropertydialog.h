#ifndef RPROPERTYDIALOG_H
#define RPROPERTYDIALOG_H

#include "qtreportglobal.h"
#include <QDialog>

class QVBoxLayout;
class QTabWidget;
class QWidget;
class QWidget;
class QDialogButtonBox;
class QAbstractButton;

LEAF_BEGIN_NAMESPACE

class LReportWidgetBase;
class LReportPropertyPageBase;
class LReportPropertyDialog : public QDialog
{
   Q_OBJECT
public:
   LReportPropertyDialog(QWidget *parent = 0);
   LReportPropertyDialog( LReportWidgetBase  *reportWidget, QWidget *parent = 0);
   void retranslateUi(QDialog *);

   void addTab(LReportPropertyPageBase*);

   int exec();

private:
   QVBoxLayout *verticalLayout;
   QTabWidget *tabWidget;
   QDialogButtonBox *buttonBox;

   void initTabs();
   LReportWidgetBase *_widget;


   QList<LReportPropertyPageBase*> properties;


public slots:
   void on_buttonBox_accepted();
   void on_buttonBox_clicked(QAbstractButton * button);
};

LEAF_END_NAMESPACE

#endif // RPROPERTYDIALOG_H
