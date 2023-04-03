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

#ifndef QRTEPORT_GLOBAL
#define QRTEPORT_GLOBAL

#include <QFlags>

#define LEAF_NAMESPACE Leaf

#ifdef LEAF_COMPILE_STATIC
#   define LEAF_EXPORT
#else
#   define LEAF_EXPORT Q_DECL_EXPORT
#endif

#ifdef LEAF_NAMESPACE
#   define LEAF_BEGIN_NAMESPACE     namespace LEAF_NAMESPACE{
#   define LEAF_END_NAMESPACE       }
#   define LEAF_WRAP_NAMESPACE(x)   LEAF_NAMESPACE::x
#else
#   define LEAF_BEGIN_NAMESPACE
#   define LEAF_END_NAMESPACE
#   define LEAF_WRAP_NAMESPACE(x)   x
#endif


#define REGISTER_PROPERTY_PAGE(name) Q_CLASSINFO("prop_" #name, "true")

//LEAF_BEGIN_NAMESPACE

enum WidgetType
{
    BandWidget,
    WidgetWidget,
    PageWidget
};
//Q_DECLARE_FLAGS(WidgetType, WidgetTypeFlag)
//Q_DECLARE_OPERATORS_FOR_FLAGS(WidgetType)

enum ResizeDirectionFlag
{
    Top = 1,
    Left = 2,
    Right = 4,
    Bottom = 8
};
Q_DECLARE_FLAGS(ResizeDirection, ResizeDirectionFlag)
Q_DECLARE_OPERATORS_FOR_FLAGS(ResizeDirection)

enum Unit
{
    Centimeters,
    Milimeters,
    Inch,
    Pixel
};
//Q_DECLARE_FLAGS(Unit, UnitFlag)
//Q_DECLARE_OPERATORS_FOR_FLAGS(Unit)

enum BandType
{
    ReportHeader,
    PageHeader,
    GroupHeader,
    Data,
    EmptyData,
    GroupFooter,
    PageFooter,
    ReportFooter
};
//Q_DECLARE_FLAGS(BandType, BandTypeFlag)
//Q_DECLARE_OPERATORS_FOR_FLAGS(BandType)

enum GridType
{
    NoGrid,
    DotGrid,
    LinesGrid
};
//Q_DECLARE_FLAGS(GridType, GridTypeFlag)
//Q_DECLARE_OPERATORS_FOR_FLAGS(GridType)

enum MouseTool
{
    Pointer,
    Hand
};
//Q_DECLARE_FLAGS(MouseTool, MouseToolFlag)
//Q_DECLARE_OPERATORS_FOR_FLAGS(MouseTool)


//LEAF_END_NAMESPACE

#endif
