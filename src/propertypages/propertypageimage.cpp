#include <QFileDialog>

#include "designer/documentdesigner.h"
#include "propertypages/propertypageimage.h"
#include <QImage>

LEAF_BEGIN_NAMESPACE

PropertyPageImage::PropertyPageImage(QWidget *parent) :
      PropertyPageBase(parent)
{
    setupUi(this);
    _title = tr( "Image" );
}

void PropertyPageImage::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi(this);
        break;
    default:
        break;
    }
}


void PropertyPageImage::load()
{
   pixmap = _designer->widgetProperty("image").value<QPixmap>();
   label->setPixmap( pixmap.scaled( label->size(), Qt::KeepAspectRatio ) );

   checkBoxScale->setChecked( _designer->widgetProperty("scaleImage").toBool() );
   checkBoxAcceptRatio->setEnabled( _designer->widgetProperty("scaleImage").toBool() );
   checkBoxAcceptRatio->setChecked( _designer->widgetProperty("acceptRatio").toBool() );
}

void PropertyPageImage::save()
{
   _designer->setWidgetProperty("image", pixmap );
   _designer->setWidgetProperty("scaleImage", checkBoxScale->isChecked() );
   _designer->setWidgetProperty("acceptRatio", checkBoxAcceptRatio->isChecked() );
}


void PropertyPageImage::on_pushButtonBrowse_clicked()
{
   QFileDialog *dialog = new QFileDialog(this);

   dialog->setNameFilter( "Al files(*.*)" );

   QString filePath = dialog->getOpenFileName();

   pixmap.load( filePath );

   label->setPixmap( pixmap.scaled( label->size(), Qt::KeepAspectRatio ) );
}

void PropertyPageImage::on_pushButtonClear_clicked()
{
   pixmap = QPixmap();
   label->setPixmap( pixmap );
}

void PropertyPageImage::on_checkBoxScale_clicked()
{
 //   checkBoxAcceptRatio->setEnabled( checkBoxScale->isChecked() );
}

void PropertyPageImage::resizeEvent ( QResizeEvent * )
{
   if( !label->pixmap()->isNull() )
      label->setPixmap( pixmap.scaled( label->size(), Qt::KeepAspectRatio ) );
}

LEAF_END_NAMESPACE
