#include <QApplication>

#include "undocommands.h"
#include "documentdesigner.h"

LEAF_BEGIN_NAMESPACE

class LReportUndoCommandPrivate
{
    LReportUndoCommand *q_ptr;
    Q_DECLARE_PUBLIC(LReportUndoCommand)

public:
    LReportUndoCommandPrivate(LReportUndoCommand *parent) :
        q_ptr(parent),
        designer(0),
        report(0),
        isReady(false)
    {

    }

    QString oldXML, newXML;
    QString oldName, newName;
    bool changeName;
    LReportDocumentDesigner *designer;
    LReport *report;
    bool isReady;
};

LReportUndoCommand::LReportUndoCommand() :
    d_ptr(new LReportUndoCommandPrivate(this)),
    QUndoCommand()
{

}

LReportUndoCommand::LReportUndoCommand(LReportDocumentDesigner *designer, LReport *report) :
    d_ptr(new LReportUndoCommandPrivate(this))
{
    Q_D(LReportUndoCommand);
    d->report = report;
    d->designer = designer;
}

void LReportUndoCommand::setReady()
{
    Q_D(LReportUndoCommand);
    d->isReady = true;
}

void LReportUndoCommand::undo()
{
    Q_D(const LReportUndoCommand);

    if(!d->isReady) return;

    d->designer->applyXml(d->newXML, d->oldXML);
}

void LReportUndoCommand::redo()
{
    Q_D(const LReportUndoCommand);

    if(!d->isReady) return;

    d->designer->applyXml(d->oldXML, d->newXML);
}

LReportDocumentDesigner *LReportUndoCommand::designer() const
{
    Q_D(const LReportUndoCommand);
    return d->designer;
}

LReport *LReportUndoCommand::report() const
{
    Q_D(const LReportUndoCommand);
    return d->report;
}

void LReportUndoCommand::setDesigner(LReportDocumentDesigner *designer)
{
    Q_D(LReportUndoCommand);
    d->designer = designer;
}

void LReportUndoCommand::setReport(LReport *report)
{
    Q_D(LReportUndoCommand);
    d->report = report;
}

void LReportUndoCommand::setOldState(QString oldState)
{
    Q_D(LReportUndoCommand);
    d->oldXML = oldState;
}

void LReportUndoCommand::setNewState(QString newState)
{
    Q_D(LReportUndoCommand);
    d->newXML = newState;
}

void LReportUndoCommand::setOldName(QString oldName)
{
    Q_D(LReportUndoCommand);
    d->oldName = oldName;
}

void LReportUndoCommand::setNewName(QString newName)
{
    Q_D(LReportUndoCommand);
    d->newName = newName;
}

LEAF_END_NAMESPACE
