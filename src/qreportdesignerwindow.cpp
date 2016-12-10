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


#include <QSettings>

#include "qreportdesignerwindow.h"
#include "qreportdesignerfactory.h"


/*
void QReportDesignerWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi(this);
        break;
    default:
        break;
    }
}
*/

QReportDesignerWindow::QReportDesignerWindow ( QWidget *parent )
    : QMainWindow ( parent )
{
    Q_INIT_RESOURCE( resources );

    factory = new QReportDesignerFactory( this );
    QSettings set( "QtReport2" );

    this->setWindowIcon(QIcon(":/designer/qtreport_32"));
    this->restoreState( set.value( "MainWindowState" ).toByteArray() );

    this->setWindowTitle("QtReport 0.1 (beta)- preview 4");
}

QReportDesignerWindow::~QReportDesignerWindow ()
{
    QSettings set( "QtReport2" );
    set.setValue( "MainWindowState", this->saveState() );
}
