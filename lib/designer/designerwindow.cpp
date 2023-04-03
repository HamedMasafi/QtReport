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

#include "designerwindow.h"
#include "designerfactory.h"

static void init_resources() {
    Q_INIT_RESOURCE( resources );
}

LEAF_BEGIN_NAMESPACE

/*
void DesignerWindow::changeEvent(QEvent *e)
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

DesignerWindow::DesignerWindow ( QWidget *parent )
    : QMainWindow ( parent )
{
    init_resources();

    factory = new DesignerFactory( this );
    QSettings set( "QtReport2" );

    this->setWindowIcon(QIcon(":/designer/qtreport_32"));
    this->restoreState( set.value( "MainWindowState" ).toByteArray() );

    this->setWindowTitle("QtReport 0.1 (beta)- preview 4");
}

DesignerWindow::~DesignerWindow ()
{
    QSettings set( "QtReport2" );
    set.setValue( "MainWindowState", this->saveState() );
}

LEAF_END_NAMESPACE
