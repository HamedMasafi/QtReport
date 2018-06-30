#ifndef REPORTMODEL_H
#define REPORTMODEL_H

#include "qtreportglobal.h"

#include <QAbstractItemModel>
#include <QMetaEnum>

LEAF_BEGIN_NAMESPACE

class Parametere;
class DataConnection;
class DataField;
class DataTable;
class Band;
class WidgetBase;
class Report;
class Variable;
class ReportModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    ReportModel(Report *parent = Q_NULLPTR);
    enum NodeType {
        Root,

        DataConnectionsRoot,
        DataConnectionItem,

        ParameteresRoot,
        ParametereItem,

        VariablesRoot,
        VariableItem,

        DataTableItem,
        FieldItem,

        WidgetsRoot,
        BandItem,
        WidgetBaseItem
    };
    enum Role {
        TextRole = Qt::DisplayRole,
        IconRole = Qt::DecorationRole,
        TypeRole = Qt::UserRole + 1,
        DataRole
    };
    struct Node {
        Node *parent;
        QList<Node*> childs;
        QObject *data;
        NodeType type;
        int row;

        Node (NodeType type) {
            this->type = type;
            data = nullptr;
        }

        Node (Parametere *p);
        Node (DataTable *dt);
        Node (DataConnection *c);
        Node (Band *b);
        Node (WidgetBase *w);
        Node (Variable *w);

        void addChild(Node *node) {
            node->row = childs.count();
            childs.append(node);
            node->parent = this;
        }
        void remove(QObject *o) {
            for (int i = 0; i < childs.count(); ++i) {
                if (childs.at(i)->data == o) {
                    childs.removeAt(i);
                    return;
                }
            }
        }
        Node *findChild(QObject *obj) {
            foreach (Node *n, childs)
                if (n->data == obj)
                    return n;
            return nullptr;
        }
        void reorder() {
            for (int i = 0; i < childs.count(); ++i)
                childs[i]->row = i;
        }

        template<class T>
        T *get() {
            return static_cast<T*>(data);
        }

        QString title() const;
        QString iconPath() const;
    };

public:
    void addParametere(Parametere *p);
    void removeParametere(Parametere *p);

    void addDataConnection(DataConnection *c);
    void removeDataConnection(DataConnection *c);

    void addVariable(Variable *gv);
    void removeVariable(Variable *gv);

    void addDataTable(DataConnection *c, DataTable *dt);
    void addDataTable(QString connectionName, DataTable *dt);
    void addDataTable(DataTable *dt);
    void removeDataTable(DataTable *dt);

    void addBand(Band *b);
    void removeBand(Band *b);

    void addWidgetBase(WidgetBase *w);
    void addWidgetBase(Band *b, WidgetBase *w);
    void removeWidgetBase(WidgetBase *w);

    QModelIndex index(int row, int column, const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex &child) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

private:
    Report *_report;
    Node *rootItem;
    Node *rootConnectionsItem;
    Node *rootBandsItem;
    Node *rootParameteresItem;
    Node *rootGlobalsItem;

    QList<Parametere*> parameteres;
    QList<Variable*> globalVariables;
    QList<DataConnection*> connections;
    QList<DataTable*> dataTables;
    QList<Band*> bands;

    static QMetaEnum variablesEnum;
};

LEAF_END_NAMESPACE

#endif // REPORTMODEL_H
