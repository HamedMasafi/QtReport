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

#ifndef QREPORTSCENE_H
#define QREPORTSCENE_H

#include "qtreportglobal.h"
#include <QGraphicsScene>

LEAF_BEGIN_NAMESPACE

class Scene : public QGraphicsScene
{
        Q_OBJECT

    public:

        Scene();

        Scene(const QRectF& sceneRect, QObject *parent);

        Scene(qreal x, qreal y, qreal width, qreal height, QObject *parent = 0);

        QRect documentArea() const;

        ~Scene();

    protected:
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
        void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
        void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);

        void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
        void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
        void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
        void dropEvent(QGraphicsSceneDragDropEvent *event);

    signals:
        void mouseRelease(QGraphicsSceneMouseEvent *mouseEvent);
        void mouseMove(QGraphicsSceneMouseEvent *mouseEvent);
        void mousePress(QGraphicsSceneMouseEvent *mouseEvent);
        void drop(QGraphicsSceneDragDropEvent *event);
};

LEAF_END_NAMESPACE

#endif
