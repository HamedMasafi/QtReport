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

#ifndef QREPORTXMLSERIAZBLE_H
#define QREPORTXMLSERIAZBLE_H

#include "qtreportglobal.h"

#include <QtCore/QObject>

#define XML_ROOT_TAG            "ReportDocument"
#define COPY_XML_ROOT           "CopyContent"
#define XML_NODE_REPORT         "Report"
#define XML_NODE_WIDGET         "Widget"
#define XML_NODE_WIDGETS        XML_NODE_WIDGET "s"
#define XML_NODE_BAND           "Band"
#define XML_NODE_BANDS          XML_NODE_BAND "s"
#define XML_NODE_CONNECTION     "Connection"
#define XML_NODE_CONNECTIONS    XML_NODE_CONNECTION "s"
#define XML_NODE_PARAMETER      "Parameter"
#define XML_NODE_PARAMETERS     XML_NODE_PARAMETER "s"
#define XML_NODE_DATATABLE      "DataTable"
#define XML_NODE_DATATABLES     XML_NODE_DATATABLE "s"

class QDomElement;

LEAF_BEGIN_NAMESPACE

class SeriazbleObject : public QObject
{
    Q_OBJECT

public:

    SeriazbleObject(QObject *parent = 0);

    virtual void saveDom(QDomElement *dom);
    virtual void loadDom(QDomElement *dom);

    void copyTo(SeriazbleObject *other);
};

LEAF_END_NAMESPACE

#endif // QREPORTXMLSERIAZBLE_H
