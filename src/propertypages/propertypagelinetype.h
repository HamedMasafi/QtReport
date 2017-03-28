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


#ifndef RPROPERTYPAGELINETYPE_H
#define RPROPERTYPAGELINETYPE_H

class QGridLayout;
class QGridLayout;
class QSpinBox;
class QLabel;
class QTextBrowser;
class QPushButton;
class QComboBox;
class QSpacerItem;

#include "propertypages/propertypagebase.h"

LEAF_BEGIN_NAMESPACE

class QColorPicker;

class LReportPropertyPageLineType : public LReportPropertyPageBase
{
   Q_OBJECT

public:
    LReportPropertyPageLineType(QWidget *parent = 0);


    void load();
    void save();


 public slots:
    void on_pushButtonSelectColor_clicked();

private:
   QGridLayout *gridLayout_2;
   QGridLayout *gridLayout;
   QLabel *labelLineWidth;
   QSpinBox *spinBoxWidth;
   QLabel *labelColor;
   QTextBrowser *textBrowserColorBox;
   QPushButton *pushButtonSelectColor;
   QLabel *labelType;
   QComboBox *comboBoxType;
   QSpacerItem *horizontalSpacer;
   QSpacerItem *verticalSpacer;
   QColorPicker *picker;
};

LEAF_END_NAMESPACE

#endif // RPROPERTYPAGELINETYPE_H
