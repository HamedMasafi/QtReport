#ifndef REVENT_H
#define REVENT_H


class QSizeF;
class QPointF;
#include <QEvent>


class QReportResizeEvent : public QEvent
{
public:
   QReportResizeEvent( const QSizeF &size, const QSizeF &oldSize ): QEvent( Resize )
    {
       m_size = size;
       m_oldSize = oldSize;
    }

   QDOC_PROPERTY( QSizeF size READ size WRITE setSize )

    inline const QSizeF &size() const{ return m_size; }
    inline const QSizeF &oldSize() const{ return m_oldSize; }
    inline void setOldSize( QSizeF oldSize ){ m_oldSize = oldSize; }
    inline void setSize( QSizeF size ){ m_size = size;}

protected:
    QSizeF m_size,
          m_oldSize;
    friend class QApplication;
    friend class QCoreApplication;
};


class QReportMoveEvent : public QEvent
{
public:
   QReportMoveEvent( const QPointF &point, const QPointF &oldPoint ): QEvent( Resize )
    {
       m_point = point;
       m_oldPoint = oldPoint;
    }

   QDOC_PROPERTY( QPointF size READ size WRITE setSize )

    inline const QPointF &point() const{ return m_point; }
    inline const QPointF &oldSize() const{ return m_oldPoint; }
    inline void setOldPoint( QPointF oldPoint ){ m_oldPoint = oldPoint; }
    inline void setPoint( QPointF point ){ m_point = point;}

protected:
    QPointF m_point,
           m_oldPoint;
    friend class QApplication;
    friend class QCoreApplication;
};

#endif // REVENT_H
