#include <QApplication>

#include "qreportundocommands.h"
#include "qreportdocumentdesigner.h"

class QReportUndoCommandPrivate
{
    QReportUndoCommand *q_ptr;
    Q_DECLARE_PUBLIC(QReportUndoCommand)

public:
    QReportUndoCommandPrivate(QReportUndoCommand *parent) :
        q_ptr(parent),
        designer(0),
        report(0),
        isReady(false)
    {

    }

    QString oldXML, newXML;
    QString oldName, newName;
    bool changeName;
    QReportDocumentDesigner *designer;
    QReport *report;
    bool isReady;
};

QReportUndoCommand::QReportUndoCommand() :
    d_ptr(new QReportUndoCommandPrivate(this)),
    QUndoCommand()
{

}

QReportUndoCommand::QReportUndoCommand(QReportDocumentDesigner *designer, QReport *report) :
    d_ptr(new QReportUndoCommandPrivate(this))
{
    Q_D(QReportUndoCommand);
    d->report = report;
    d->designer = designer;
}

void QReportUndoCommand::setReady()
{
    Q_D(QReportUndoCommand);
    d->isReady = true;
}

void QReportUndoCommand::undo()
{
    Q_D(const QReportUndoCommand);

    if(!d->isReady) return;

    d->designer->applyXml(d->newXML, d->oldXML);
}

void QReportUndoCommand::redo()
{
    Q_D(const QReportUndoCommand);

    if(!d->isReady) return;

    d->designer->applyXml(d->oldXML, d->newXML);
}

QReportDocumentDesigner *QReportUndoCommand::designer() const
{
    Q_D(const QReportUndoCommand);
    return d->designer;
}

QReport *QReportUndoCommand::report() const
{
    Q_D(const QReportUndoCommand);
    return d->report;
}

void QReportUndoCommand::setDesigner(QReportDocumentDesigner *designer)
{
    Q_D(QReportUndoCommand);
    d->designer = designer;
}

void QReportUndoCommand::setReport(QReport *report)
{
    Q_D(QReportUndoCommand);
    d->report = report;
}

void QReportUndoCommand::setOldState(QString oldState)
{
    Q_D(QReportUndoCommand);
    d->oldXML = oldState;
}

void QReportUndoCommand::setNewState(QString newState)
{
    Q_D(QReportUndoCommand);
    d->newXML = newState;
}

void QReportUndoCommand::setOldName(QString oldName)
{
    Q_D(QReportUndoCommand);
    d->oldName = oldName;
}

void QReportUndoCommand::setNewName(QString newName)
{
    Q_D(QReportUndoCommand);
    d->newName = newName;
}

