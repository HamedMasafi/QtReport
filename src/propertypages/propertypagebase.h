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

#ifndef RPROPERTYPAGEBASE_H
#define RPROPERTYPAGEBASE_H

#include "widgets/widgetbase.h"
#include "designer/documentdesigner.h"
#include <QWidget>

class QSpinBox;

LEAF_BEGIN_NAMESPACE

class DocumentDesigner;
class PropertyPageBase : public QWidget
{
    Q_OBJECT
public:
   PropertyPageBase(QWidget *parent = 0);


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

   DocumentDesigner *designer() const;
   void setDesigner(DocumentDesigner *designer);

protected:
   bool _isChanged;

   DocumentDesigner *_designer;

};

LEAF_END_NAMESPACE

#endif
