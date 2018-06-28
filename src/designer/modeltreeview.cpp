#include "modeltreeview.h"
#include "report.h"

#include <QtWidgets/QMenu>
#include <QtCore/QDebug>
#include <QtGui/QMouseEvent>

#include "reportmodel.h"

LEAF_BEGIN_NAMESPACE

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
    if (event->button() == Qt::RightButton)
        menu->exec(event->globalPos());

    QTreeView::mousePressEvent(event);
}

void ModelTreeView::currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);
    if (!current.isValid())
        return;
    ReportModel::NodeType type = ReportModel::NodeType(current.data(ReportModel::TypeRole).toInt());
}

LEAF_END_NAMESPACE

