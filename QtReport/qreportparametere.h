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

#ifndef QREPORTPARAMETERE_H
#define QREPORTPARAMETERE_H


#include <QVariant>

class QString;

#include "qreportxmlseriazble.h"
#include "qtreportglobal.h"

class QReportParametere : public QReportXMLSeriazble
{
    Q_OBJECT

    Q_PROPERTY(int type READ type WRITE setType USER true)
    Q_PROPERTY(QVariant value READ value WRITE setValue USER true)
    Q_PROPERTY(QVariant defaultValue READ defaultValue WRITE setDefaultValue USER true)

    R_PROPERTY(QVariant, value, value, setValue, _value)
    R_PROPERTY(int, type, type, setType, _type)
    R_PROPERTY(QVariant, defaultValue, defaultValue, setDefaultValue, _defaultValue)


    public:
        QReportParametere(QString name = "",
                          QVariant value = QVariant(),
                          QVariant::Type type = QVariant::String);
};

#endif // QREPORTPARAMETERE_H
