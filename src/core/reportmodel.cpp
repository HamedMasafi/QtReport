#include "report.h"
#include "reportmodel.h"
#include "core/parametere.h"
#include "core/dataconnection.h"
#include "core/datatable.h"
#include "widgets/band.h"
#include "core/variable.h"

#include <QRandomGenerator>
#include <QCoreApplication>
#include <QIcon>
#include <QRegularExpression>
#include <QtCore/QDebug>
#include <QtCore/QMetaEnum>

LEAF_BEGIN_NAMESPACE

QMetaEnum ReportModel::variablesEnum;

ReportModel::ReportModel(Report *parent) : QAbstractItemModel(parent), _report(parent)
{
    rootItem = new Node(Root);
    rootConnectionsItem = new Node(DataConnectionsRoot);
    rootParameteresItem = new Node(ParameteresRoot);
    rootBandsItem = new Node(WidgetsRoot);
    rootGlobalsItem = new Node(VariablesRoot);

    rootItem->addChild(rootConnectionsItem);
    rootItem->addChild(rootParameteresItem);
    rootItem->addChild(rootBandsItem);
    rootItem->addChild(rootGlobalsItem);
    variablesEnum = QMetaEnum::fromType<Variable::Type>();
    for (int i = 0; i < variablesEnum.keyCount(); ++i) {
        addVariable(new Variable(Variable::Type(i)));
    }
}

void ReportModel::addParametere(Parametere *p)
{
    beginInsertRows(createIndex(rootParameteresItem->row, 0, rootParameteresItem),
                    parameteres.count(),
                    parameteres.count());
    parameteres.append(p);
    rootParameteresItem->addChild(new Node(p));
    endInsertRows();
}

void ReportModel::removeParametere(Parametere *p)
{
    beginRemoveRows(createIndex(rootParameteresItem->row, 0, rootParameteresItem),
                    parameteres.count(),
                    parameteres.count());
    parameteres.removeOne(p);
    rootParameteresItem->remove(p);
    rootParameteresItem->reorder();
    endRemoveRows();
}

void ReportModel::addDataConnection(DataConnection *c)
{
    beginInsertRows(createIndex(rootConnectionsItem->row, 0, rootConnectionsItem),
                    connections.count(),
                    connections.count());
    connections.append(c);
    rootConnectionsItem->addChild(new Node(c));
    endInsertRows();
}

void ReportModel::removeDataConnection(DataConnection *c)
{
    beginRemoveRows(createIndex(rootConnectionsItem->row, 0, rootConnectionsItem),
                    connections.count(),
                    connections.count());
    connections.removeOne(c);
    rootConnectionsItem->remove(c);
    rootConnectionsItem->reorder();
    endRemoveRows();
}

void ReportModel::addVariable(Variable *gv)
{
    beginInsertRows(createIndex(rootGlobalsItem->row, 0, rootGlobalsItem),
                    globalVariables.count(),
                    globalVariables.count());
    globalVariables.append(gv);
    rootGlobalsItem->addChild(new Node(gv));
    endInsertRows();
}

void ReportModel::removeVariable(Variable *gv)
{

}


void ReportModel::addDataTable(DataConnection *c, DataTable *t)
{
    for (int i = 0; i < connections.count(); ++i) {
        if (connections.at(i)->objectName() == c->objectName()) {
            Node *n = rootConnectionsItem->childs.at(i);
            beginInsertRows(createIndex(n->row,
                                        0,
                                        n),
                            n->childs.count(),
                            n->childs.count());
//            bands.append(b);
            n->addChild(new Node(t));
            endInsertRows();
        }
    }
}

void ReportModel::addDataTable(QString connectionName, DataTable *dt)
{
    for (int i = 0; i < connections.count(); ++i) {
        if (connections.at(i)->objectName() == connectionName) {
            Node *n = rootConnectionsItem->childs.at(i);
            beginInsertRows(createIndex(n->row,
                                        0,
                                        n),
                            n->childs.count(),
                            n->childs.count());
            n->addChild(new Node(dt));
            endInsertRows();
        }
    }
}

void ReportModel::addDataTable(DataTable *dt)
{
    addDataTable(dt->connectionName(), dt);
}

void ReportModel::removeDataTable(DataTable *dt)
{

}

void ReportModel::addBand(Band *b)
{
    beginInsertRows(createIndex(rootBandsItem->row, 0, rootBandsItem),
                    bands.count(),
                    bands.count());
    bands.append(b);
    rootBandsItem->addChild(new Node(b));
    endInsertRows();
}

void ReportModel::removeBand(Band *b)
{
    beginRemoveRows(createIndex(rootBandsItem->row, 0, rootBandsItem),
                    connections.count(),
                    connections.count());
    bands.removeOne(b);
    rootBandsItem->remove(b);
    rootBandsItem->reorder();
    endRemoveRows();
}

void ReportModel::addWidgetBase(WidgetBase *w)
{

}

void ReportModel::addWidgetBase(Band *b, WidgetBase *w)
{
    for (int i = 0; i < bands.count(); ++i) {
        Band *band = bands.at(i);
        if (band->objectName() == b->objectName()) {
            Node *n = rootBandsItem->childs.at(i);
            beginInsertRows(createIndex(n->row,
                                        0,
                                        n),
                            n->childs.count(),
                            n->childs.count());
//            bands.append(b);
            n->addChild(new Node(w));
            endInsertRows();
        }
    }
}

void ReportModel::removeWidgetBase(WidgetBase *w)
{

}

QModelIndex ReportModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    Node *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<Node*>(parent.internalPointer());

    Node *childItem = parentItem->childs.at(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex ReportModel::parent(const QModelIndex &child) const
{
    if (!child.isValid())
        return QModelIndex();

    Node *childItem = static_cast<Node*>(child.internalPointer());
    Node *parentItem = childItem->parent;

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row, 0, parentItem);
}

int ReportModel::rowCount(const QModelIndex &parent) const
{
    Node *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<Node*>(parent.internalPointer());

    return parentItem->childs.count();
}

int ReportModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant ReportModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    Node *d = static_cast<Node*>(index.internalPointer());

    switch (role) {
    case Qt::DisplayRole:
        return d->title();

    case Qt::DecorationRole:
        return QIcon(d->iconPath());

    case TypeRole:
        return d->type;

    default:
        return QVariant();
    }
}

#define NODE_CTOR(TYPE) \
    ReportModel::Node::Node(TYPE *arg) { \
    this->type = TYPE##Item; \
    this->data = arg; \
    }

NODE_CTOR(Parametere)
NODE_CTOR(DataTable)
NODE_CTOR(DataConnection)
NODE_CTOR(Band)
NODE_CTOR(WidgetBase)
NODE_CTOR(Variable)

QString ReportModel::Node::title() const {
    switch (type) {
    case Root:
        return QCoreApplication::translate("Leaf::ReportModel::Node", "Root");

    case DataConnectionsRoot:
        return QCoreApplication::translate("Leaf::ReportModel::Node", "Data Connections");

    case DataConnectionItem:
        return qobject_cast<DataConnection*>(data)->objectName();

    case ParameteresRoot:
        return QCoreApplication::translate("Leaf::ReportModel::Node", "Parameteres");

    case ParametereItem:
        return qobject_cast<Parametere*>(data)->objectName();

    case VariableItem: {
        QString name = ReportModel::variablesEnum.valueToKey(qobject_cast<Variable*>(data)->type());
        name = name
                .replace(QRegularExpression("([A-Z])"), " \\1")
                .trimmed();
        return name;
    }
    case VariablesRoot:
        return QCoreApplication::translate("Leaf::ReportModel::Node", "Global variables");

    case DataTableItem:
        return qobject_cast<DataTable*>(data)->objectName();

    case FieldItem:
        return qobject_cast<DataField*>(data)->objectName();

    case WidgetsRoot:
        return QCoreApplication::translate("Leaf::ReportModel::Node", "Widgets");

    case BandItem:
        return qobject_cast<Band*>(data)->objectName();

    case WidgetBaseItem:
        return qobject_cast<WidgetBase*>(data)->objectName();
    }
    return "";
}

QString ReportModel::Node::iconPath() const
{
    switch (type) {
    case Root:
        return "";

    case DataConnectionsRoot:
        return ":/designer/database";

    case DataConnectionItem:
        return ":/designer/database";

    case ParameteresRoot:
        return "";

    case ParametereItem:
        return ":/designer/properties";

    case DataTableItem:
        return ":/designer/table";

    case FieldItem:
        return ":/designer/field";

    case WidgetsRoot:
        return "";

    case BandItem: {
        auto band = qobject_cast<Band*>(data);
        switch (band->bandType()){
        case ReportHeader: return ":/designer/section_report_header";
        case PageHeader: return ":/designer/section_page_header";
        case GroupHeader: return ":/designer/section_group_header";
        case Data: return ":/designer/section_data";
        case EmptyData: return ":/designer/section_data";
        case GroupFooter: return ":/designer/section_group_footer";
        case PageFooter: return ":/designer/section_page_footer";
        case ReportFooter: return ":/designer/section_report_footer";
        }
        return ":/designer/section_data";
    }

    case WidgetBaseItem:
        return "";
    }
    return "";
}

LEAF_END_NAMESPACE
