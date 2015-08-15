#ifndef RPROPERTYPAGEBASE_H
#define RPROPERTYPAGEBASE_H


#include "qreportwidgetbase.h"
#include "qreportdocumentdesigner.h"
#include <QWidget>


class QSpinBox;

class Q_DECL_HIDDEN QReportPropertyPageBase : public QWidget
{
    Q_OBJECT
public:
   QReportPropertyPageBase(QWidget *parent = 0);


   bool isChanged() const;
   int index() const;
   QString title() const;


    /*!
      *
    */
   virtual void load() = 0;
   virtual void save() = 0;

   void loadData(QString propertyName, QSpinBox *spin);

   void saveData(QString propertyName, QSpinBox *spin);

   int     _index;
   QString _title;

   QReportDocumentDesigner designer() const;
   void setDesigner(QReportDocumentDesigner *designer);

protected:
   bool _isChanged;

   QReportDocumentDesigner *_designer;

};

#endif
