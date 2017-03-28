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

#include "typehelper.h"

LReportTypeHelper::LReportTypeHelper()
{
}

QString LReportTypeHelper::typeToString(QVariant::Type type)
{
    switch(type){
    case QVariant::Int:
        return "Int";
        break;

    case QVariant::Double:
        return "Double";
        break;

    case QVariant::Bool:
        return "Bool";
        break;

    case QVariant::Char:
        return "Char";
        break;

    case QVariant::Pixmap:
        return "Pixmap";
        break;

    default:
        return "String";
        break;

    }//switch

}

QVariant::Type LReportTypeHelper::stringToType(QString type)
{
    type = type.toLower();

    if(type == "int")      return QVariant::Int;
    if(type == "double")   return QVariant::Double;
    if(type == "bool")     return QVariant::Bool;
    if(type == "char")     return QVariant::Char;
    if(type == "pixmap")   return QVariant::Pixmap;

    return QVariant::String;
}

