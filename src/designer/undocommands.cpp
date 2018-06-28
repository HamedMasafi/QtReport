#include <QApplication>

#include "report.h"
#include "reportmodel.h"
#include "undocommands.h"
#include "designer/documentdesigner.h"
#include "dataconnection.h"
#include "datatable.h"
#include "widgets/band.h"
#include "parametere.h"
#include "widgets/widgetbase.h"
#include "variable.h"

LEAF_BEGIN_NAMESPACE

class UndoCommandPrivate
{
    UndoCommand *q_ptr;
    Q_DECLARE_PUBLIC(UndoCommand)

public:
    UndoCommandPrivate(UndoCommand *parent) :
        q_ptr(parent),
        designer(nullptr),
        report(nullptr),
        isReady(false)
    {

    }

    QString oldXML, newXML;
    QString oldName, newName;
    bool changeName;
    DocumentDesigner *designer;
    Report *report;
    bool isReady;
};

UndoCommand::UndoCommand() :
    QUndoCommand(),
    d_ptr(new UndoCommandPrivate(this))
{

}

UndoCommand::UndoCommand(DocumentDesigner *designer, Report *report) :
    d_ptr(new UndoCommandPrivate(this))
{
    Q_D(UndoCommand);
    d->report = report;
    d->designer = designer;
}

void UndoCommand::setReady()
{
    Q_D(UndoCommand);
    d->isReady = true;
}

void UndoCommand::undo()
{
    Q_D(const UndoCommand);

    if(!d->isReady) return;

    d->designer->applyXml(d->newXML, d->oldXML);
}

void UndoCommand::redo()
{
    Q_D(const UndoCommand);

    if(!d->isReady) return;

    d->designer->applyXml(d->oldXML, d->newXML);
}

DocumentDesigner *UndoCommand::designer() const
{
    Q_D(const UndoCommand);
    return d->designer;
}

Report *UndoCommand::report() const
{
    Q_D(const UndoCommand);
    return d->report;
}

void UndoCommand::setDesigner(DocumentDesigner *designer)
{
    Q_D(UndoCommand);
    d->designer = designer;
}

void UndoCommand::setReport(Report *report)
{
    Q_D(UndoCommand);
    d->report = report;
}

void UndoCommand::setOldState(QString oldState)
{
    Q_D(UndoCommand);
    d->oldXML = oldState;
}

void UndoCommand::setNewState(QString newState)
{
    Q_D(UndoCommand);
    d->newXML = newState;
}

void UndoCommand::setOldName(QString oldName)
{
    Q_D(UndoCommand);
    d->oldName = oldName;
}

void UndoCommand::setNewName(QString newName)
{
    Q_D(UndoCommand);
    d->newName = newName;
}

#define UNDO_COMMAND_IMPL(TYPE) \
TYPE##UndoCommand::TYPE##UndoCommand(TYPE *object, DocumentDesigner *designer, Report *report) \
    : UndoCommand(designer, report), obj(object) \
{ } \
void TYPE##UndoCommand::undo() \
{ \
    report()->model()->remove##TYPE(obj); \
} \
void TYPE##UndoCommand::redo() \
{ \
    report()->model()->add##TYPE(obj); \
}
UNDO_COMMAND_IMPL(DataConnection)
UNDO_COMMAND_IMPL(DataTable)
UNDO_COMMAND_IMPL(Band)
UNDO_COMMAND_IMPL(Parametere)
UNDO_COMMAND_IMPL(WidgetBase)
UNDO_COMMAND_IMPL(Variable)


LEAF_END_NAMESPACE
