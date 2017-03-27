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

#include "qreportband.h"
#include "qreportevent.h"
#include <QDomElement>
#include <QDebug>

LEAF_BEGIN_NAMESPACE

QReportBand::QReportBand(QGraphicsItem *parent):
    QReportPanel(parent),
    _index(0)
{
    this->setResizeDirection(::Bottom);
    this->setIsMovable(false);
    this->setZValue(9);
    //this->setFlags( QGraphicsItem::ItemIsPanel );

    _headerHeight = 25;

    this->setMinimumSize(this->size().width(), _headerHeight);

    setWidgetType(::Band);
}


QReportBand::QReportBand(BandType type, QGraphicsItem *parent):
    QReportPanel(parent),
    _bandType(type)
{
    this->setResizeDirection(::Bottom);
    this->setIsMovable(false);
    this->setZValue(9);

    _headerHeight = 25;
    _index = (int)type;

    this->setMinimumSize(this->size().width(), _headerHeight);

    setWidgetType(::Band);

    qRegisterMetaType<BandType>("BandType");
}


QReportBand::~QReportBand()
{
}


BandType  QReportBand::bandType() const
{
    return _bandType;
}

void QReportBand::setBandType(BandType type)
{
    _bandType = type;
}

qreal QReportBand::bandHeight() const
{
    return size().height() - headerHeight();
}
void QReportBand::setBandHeight(qreal value)
{
    setSize(size().width(), value + headerHeight());
}

void QReportBand::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                        QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    int salt = (int)bandType() + 1;

    QColor c;
    //    QColor c = QColor::fromRgb(
    //                salt  *40,
    //                100 + salt  *30,
    //                180 + salt  *10);

    switch(bandType()){
    case ReportHeader:
        c = Qt::darkBlue;
        break;

    case PageHeader:
        c = Qt::darkGreen;
        break;

    case GroupHeader:
        c = Qt::darkBlue;
        break;

    case Data:
        c = Qt::darkMagenta;
        break;

    case EmptyData:
        c = Qt::blue;
        break;

    case GroupFooter:
        c = Qt::darkYellow;
        break;

    case PageFooter:
        c = Qt::darkRed;
        break;

    case ReportFooter:
        c = Qt::darkCyan;
        break;
    default:
        qDebug() << "fuck";
    }

    QRect headerRect(0,
                     0,
                     this->size().width(),
                     _headerHeight);

    painter->setPen(QPen(c));
    painter->drawRect(this->boundingRect());

    painter->drawLine(0,
                      _headerHeight,
                      this->size().width(),
                      _headerHeight);

    QBrush bg(QColor(240, 240, 240, 128));
    painter->setBrush(bg);
    painter->drawRect(this->boundingRect());

    //draw header
    QLinearGradient linearGrad(QPointF(0, 0),
                               QPointF(0, _headerHeight));
    linearGrad.setColorAt(0, Qt::white);
    linearGrad.setColorAt(1, c.lighter(300));

    QBrush brush(linearGrad);
    painter->setBrush(brush);
    painter->drawRect(headerRect);

    painter->setPen(Qt::black);
    headerRect.setLeft(15);
    painter->drawText(headerRect,
                      header(),
                      Qt::AlignLeft | Qt::AlignVCenter);

}

QString QReportBand::typeString() const
{
    QString ret;
    switch (_bandType) {
    case PageHeader:
        ret = tr("Page Header");
        break;

    case ReportHeader:
        ret = tr("Report Header");
        break;

    case GroupHeader:
        ret = tr("Group Header");
        break;

    case Data:
        ret = tr("Data");
        break;

    case EmptyData:
        ret = tr("Empty Data");
        break;

    case GroupFooter:
        ret = tr("Group Footer");
        break;

    case ReportFooter:
        ret = tr("Report Footer");
        break;

    case PageFooter:
        ret = tr("Page Footer");
        break;

    default:
        ret = "";
    }//switch

    return ret;
}

QString QReportBand::header() const
{
    if(objectName() == "")
        return typeString();
    else
        return typeString() + " - " + objectName();
}

//qreal QSectionBand::top() const
//{
//   return pos.x();
//}

void QReportBand::setTop(qreal value)
{
    this->setPos(this->pos().x(), value);
    reorderChilds();
}

qreal QReportBand::headerHeight() const
{
    return _headerHeight;
}
void QReportBand::setHeaderHeight(qreal headerHeight)
{
    _headerHeight = headerHeight;
    this->setMinimumSize(this->size().width(), _headerHeight);
}

/*!
  *Set height for report widget
 * \see void setSize ( QSizeF size )
 */
void QReportBand::setHeight(int height)
{
    setSize(size().width(), height + headerHeight());
}

/*!
 * \see void setSize ( QSizeF size )
 */
void QReportBand::setSize(int width, int height)
{
    QSize newSize(width, height + headerHeight());
    QReportWidgetBase::setSize(newSize);
}


void QReportBand::saveDom(QDomElement *dom)
{
    QReportXMLSeriazble::saveDom(dom);

    dom->setAttribute("bandType", (int)bandType());
    dom->setAttribute("bandHeight", (int)bandHeight());
}

void QReportBand::loadDom(QDomElement *dom)
{
    QReportWidgetBase::loadDom(dom);

    int nBuffer =  dom->attribute("bandHeight").toInt();
    setBandHeight(nBuffer);

    nBuffer =  dom->attribute("bandType").toInt();
    setBandType((BandType)nBuffer);
}


void QReportBand::addWidget(QReportWidgetBase *widget, QPointF pt)
{
    if (!_childs.contains(widget))
        _childs.append(widget);

    QPointF tmpPos = pt;
    tmpPos.setY(pt.y() + _headerHeight);
    widget->setPos(this->mapToScene(tmpPos));
}

void QReportBand::setIndex(int index)
{
    _index = index;
}

int QReportBand::index() const
{
    return _index;
}

LEAF_END_NAMESPACE
