#ifndef RPROPERTYDIALOG_H
#define RPROPERTYDIALOG_H

#include <QDialog>

class QReportWidgetBase;
class QReportPropertyPageBase;
class QVBoxLayout;
class QTabWidget;
class QWidget;
class QWidget;
class QDialogButtonBox;
class QAbstractButton;
class QReportPropertyDialog : public QDialog
{
   Q_OBJECT
public:
   QReportPropertyDialog(QWidget *parent = 0);
   QReportPropertyDialog( QReportWidgetBase  *reportWidget, QWidget *parent = 0);
   void retranslateUi(QDialog *);

   void addTab(QReportPropertyPageBase*);

   int exec();

private:
   QVBoxLayout *verticalLayout;
   QTabWidget *tabWidget;
   QDialogButtonBox *buttonBox;

   void initTabs();
   QReportWidgetBase *_widget;


   QList<QReportPropertyPageBase*> properties;


public slots:
   void on_buttonBox_accepted();
   void on_buttonBox_clicked(QAbstractButton * button);
};

#endif // RPROPERTYDIALOG_H
