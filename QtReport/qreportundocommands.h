#ifndef QREPORTUNDOCOMMANDS_H
#define QREPORTUNDOCOMMANDS_H

#include <QUndoCommand>


class QReport;
class QReportDocumentDesigner;
class QReportUndoCommandPrivate;
class QReportUndoCommand : public QUndoCommand
{

private:
    QReportUndoCommandPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QReportUndoCommand)

public:

    QReportUndoCommand();
    QReportUndoCommand(QReportDocumentDesigner *designer, QReport *report);

    virtual void undo();
    virtual void redo();

    void setReady();

    QReportDocumentDesigner *designer() const;
    QReport *report() const;

    void setDesigner(QReportDocumentDesigner *designer);
    void setReport(QReport *report);

    void setOldState(QString oldState);
    void setNewState(QString newState);

    void setOldName(QString oldName);
    void setNewName(QString newName);

};

#endif // QREPORTUNDOCOMMANDS_H
