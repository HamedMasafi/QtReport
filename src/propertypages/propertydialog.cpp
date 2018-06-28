
#include <QVBoxLayout>
#include <QTabWidget>
#include <QDialogButtonBox>
#include <QTabWidget>
#include <QLabel>
#include <QDebug>
#include <QPushButton>

#include "propertydialog.h"
#include "propertypages/propertypagebase.h"
#include "propertypages/propertypagebase.h"
#include "propertypages/propertypagetext.h"
#include "widgets/widgetbase.h"

LEAF_BEGIN_NAMESPACE

PropertyDialog::PropertyDialog(QWidget *parent): QDialog( parent )
{
   resize(355, 284);
   verticalLayout = new QVBoxLayout( this );
   verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
   tabWidget = new QTabWidget( this );
   tabWidget->setObjectName(QString::fromUtf8("tabWidget"));

   verticalLayout->addWidget(tabWidget);

   buttonBox = new QDialogButtonBox( this );
   buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
   buttonBox->setOrientation(Qt::Horizontal);
   buttonBox->setStandardButtons(QDialogButtonBox::Cancel
                                 | QDialogButtonBox::Ok
                                 /*| QDialogButtonBox::Apply*/);

   verticalLayout->addWidget(buttonBox);

   retranslateUi( this );
   QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

   QMetaObject::connectSlotsByName( this );
}

PropertyDialog::PropertyDialog( WidgetBase *reportWidget, QWidget *parent ) :
    QDialog( parent ),
    _widget( reportWidget )
{
   resize(355, 284);
   verticalLayout = new QVBoxLayout( this );
   verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
   tabWidget = new QTabWidget( this );
   tabWidget->setObjectName(QString::fromUtf8("tabWidget"));

   verticalLayout->addWidget(tabWidget);

   buttonBox = new QDialogButtonBox( this );
   buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
   buttonBox->setOrientation(Qt::Horizontal);
   buttonBox->setStandardButtons(QDialogButtonBox::Cancel
                                 | QDialogButtonBox::Ok );

   verticalLayout->addWidget(buttonBox);


   retranslateUi( this );
   //QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
   QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

   //initTabs();

   QMetaObject::connectSlotsByName( this );
} // setupUi

void PropertyDialog::retranslateUi(QDialog *)
{
   setWindowTitle( tr("Property page") );
   buttonBox->button(QDialogButtonBox::Cancel)->setText( tr("Cancel") );
   buttonBox->button(QDialogButtonBox::Ok)->setText( tr("OK") );
}

int PropertyDialog::exec()
{
   if( tabWidget->count() == 0)
   {
      QLabel *nothing = new QLabel(this);
      nothing->setText( tr("This widget has no property to change!") );
      nothing->setAlignment( Qt::AlignCenter );
      tabWidget->addTab( nothing, tr("Properties") );
   }

   return QDialog::exec();
}

void PropertyDialog::initTabs()
{
   //TODO init properties in new way
   /*properties = _widget->getPropertiesPages();

   for( int i = 0; i < properties.count(); i++ )
      addTab( properties.at( i ) );

   if( tabWidget->count() == 0)
   {
      QLabel *nothing = new QLabel(this);
      nothing->setText( tr("This widget has no property to change!") );
      nothing->setAlignment( Qt::AlignHCenter | Qt::AlignVCenter );
      tabWidget->addTab( nothing, "Properties" );
   }*/
}

void PropertyDialog::addTab(PropertyPageBase *page)
{
   tabWidget->addTab( page, page->title() );

   page->load();
}


void PropertyDialog::on_buttonBox_accepted()
{
   for( int i = 0; i < properties.count(); i++ )
      properties.at( i )->save();

   this->accept();
}

void PropertyDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    qDebug()<<buttonBox->buttonRole(button);
   if(buttonBox->buttonRole(button) == QDialogButtonBox::ApplyRole)
       for( int i = 0; i < properties.count(); i++ )
          properties.at( i )->save();
}

LEAF_END_NAMESPACE
