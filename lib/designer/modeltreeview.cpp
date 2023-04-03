#include "modeltreeview.h"
#include "core/report.h"

#include <QtWidgets/QMenu>
#include <QtCore/QDebug>
#include <QtGui/QMouseEvent>
#include <QDrag>
#include <QApplication>
#include <QMimeData>

#include "core/reportmodel.h"

LEAF_BEGIN_NAMESPACE

ModelTreeView::ModelTreeView(QWidget *parent) : QTreeView(parent)
{
    setHeaderHidden(true);
    setEnableDrag(true);

    menu = new QMenu(this);

    QAction *actionNewConnection = new QAction(tr("New"), this);
    actionNewConnection->setObjectName("actionNewConnection");
    actionNewConnection->setIcon(QIcon(":/designer/add"));

    QAction *actionEditConnection= new QAction(tr("Edit"), this);
    actionEditConnection->setObjectName("actionEditConnection");
    actionEditConnection->setIcon(QIcon(":/designer/edit"));

    QAction *actionDeleteConnection= new QAction(tr("Delete"), this);
    actionDeleteConnection->setObjectName("actionDeleteConnection");
    actionDeleteConnection->setIcon(QIcon(":/designer/delete"));

    menu->addAction(actionNewConnection);
    menu->addAction(actionEditConnection);
    menu->addAction(actionDeleteConnection);
}

ModelTreeView::ModelTreeView(Report *report, QWidget *parent)
    : QTreeView(parent), _report(report)
{
    setModel(_report->model());
    setHeaderHidden(true);

    menu = new QMenu(this);

    QAction *actionNewConnection = new QAction(tr("New"), this);
    actionNewConnection->setObjectName("actionNewConnection");
    actionNewConnection->setIcon(QIcon(":/designer/add"));

    QAction *actionEditConnection= new QAction(tr("Edit"), this);
    actionEditConnection->setObjectName("actionEditConnection");
    actionEditConnection->setIcon(QIcon(":/designer/edit"));

    QAction *actionDeleteConnection= new QAction(tr("Delete"), this);
    actionDeleteConnection->setObjectName("actionDeleteConnection");
    actionDeleteConnection->setIcon(QIcon(":/designer/delete"));

    menu->addAction(actionNewConnection);
    menu->addAction(actionEditConnection);
    menu->addAction(actionDeleteConnection);
}

void ModelTreeView::mousePressEvent(QMouseEvent *event)
{
    QTreeView::mousePressEvent(event);
    qApp->processEvents();

    if (event->button() == Qt::RightButton)
        menu->exec(event->globalPos());
    else if (event->button() == Qt::LeftButton) {
        ReportModel::NodeType type = ReportModel::NodeType(
                    currentIndex().data(ReportModel::TypeRole).toInt());

        if (m_enableDrag &&
                (type == ReportModel::ParametereItem
                 || type == ReportModel::VariableItem)) {
            QMimeData *mimeData = new QMimeData();
            mimeData->setText(QString("{%1}").arg(currentIndex()
                                                  .data(Qt::DisplayRole)
                                                  .toString()));

            QDrag *drag = new QDrag(this);
            drag->setMimeData(mimeData);

            drag->exec(Qt::CopyAction);
        }
    }
}

void ModelTreeView::currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);
    if (!current.isValid())
        return;
}



bool ModelTreeView::enableDrag() const
{
    return m_enableDrag;
}

void ModelTreeView::setEnableDrag(bool enableDrag)
{
    m_enableDrag = enableDrag;
}

LEAF_END_NAMESPACE

