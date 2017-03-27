#ifndef RPROPERTYPAGEBASE_H
#define RPROPERTYPAGEBASE_H


#include "widgets/qreportwidgetbase.h"
#include "qreportdocumentdesigner.h"
#include <QWidget>

class QSpinBox;

LEAF_BEGIN_NAMESPACE

class LReportDocumentDesigner;
class LReportPropertyPageBase : public QWidget
{
    Q_OBJECT
public:
   LReportPropertyPageBase(QWidget *parent = 0);


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

   LReportDocumentDesigner *designer() const;
   void setDesigner(LReportDocumentDesigner *designer);

protected:
   bool _isChanged;

   LReportDocumentDesigner *_designer;

};

LEAF_END_NAMESPACE

#endif
