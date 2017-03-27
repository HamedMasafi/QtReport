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


#ifndef RREPORTDESIGNERWINDOW_H
#define RREPORTDESIGNERWINDOW_H

//#include <ui_qreportdesignerwindow.h>
#include "qtreportglobal.h"
#include <QMainWindow>

LEAF_BEGIN_NAMESPACE

class QReportDesignerFactory ;


class QReportDesignerWindow : public QMainWindow//, private Ui::QReportDesignerWindow
{
    Q_OBJECT

public:
    QReportDesignerWindow(QWidget *parent = 0);
    ~QReportDesignerWindow();

private:
   QReportDesignerFactory *factory;
};

LEAF_END_NAMESPACE

#endif // RREPORTDESIGNERWINDOW_H
