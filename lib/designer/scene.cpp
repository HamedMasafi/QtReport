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

#include <QGraphicsSceneMouseEvent>

#include "scene.h"

LEAF_BEGIN_NAMESPACE

Scene::Scene() : QGraphicsScene()
{
   this->clear();
}

Scene::Scene ( const QRectF& sceneRect, QObject *parent ) : QGraphicsScene ( sceneRect, parent )
{
   this->clear();
}


Scene::Scene ( qreal x, qreal y, qreal width, qreal height, QObject  *parent )
      : QGraphicsScene ( x, y, width, height, parent )
{
   this->clear();
}


Scene::~Scene()
{
}


QRect Scene::documentArea() const
{
    return QRect();
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
   QGraphicsScene::mouseReleaseEvent(mouseEvent);
   emit mouseRelease(mouseEvent);
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseMoveEvent(mouseEvent);
    emit mouseMove(mouseEvent);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mousePressEvent(mouseEvent);
    emit mousePress(mouseEvent);
}

void Scene::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_UNUSED(event);
}

void Scene::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_UNUSED(event);
}

void Scene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_UNUSED(event);

    event->accept();
}

void Scene::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    emit drop(event);
}

LEAF_END_NAMESPACE
