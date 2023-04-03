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

class WidgetBase;
class PropertyPageBase;
class PropertyDialog : public QDialog
{
   Q_OBJECT
public:
   PropertyDialog(QWidget *parent = 0);
   PropertyDialog( WidgetBase  *reportWidget, QWidget *parent = 0);
   void retranslateUi(QDialog *);

   void addTab(PropertyPageBase*);

   int exec();

private:
   QVBoxLayout *verticalLayout;
   QTabWidget *tabWidget;
   QDialogButtonBox *buttonBox;

   void initTabs();
   WidgetBase *_widget;


   QList<PropertyPageBase*> properties;


public slots:
   void on_buttonBox_accepted();
   void on_buttonBox_clicked(QAbstractButton * button);
};

LEAF_END_NAMESPACE

#endif // RPROPERTYDIALOG_H
