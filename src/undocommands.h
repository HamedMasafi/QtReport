#ifndef QREPORTUNDOCOMMANDS_H
#define QREPORTUNDOCOMMANDS_H

#include "qtreportglobal.h"
#include <QUndoCommand>

LEAF_BEGIN_NAMESPACE

class LReport;
class LReportDocumentDesigner;
class LReportUndoCommandPrivate;
class LReportUndoCommand : public QUndoCommand
{

private:
    LReportUndoCommandPrivate *d_ptr;
    Q_DECLARE_PRIVATE(LReportUndoCommand)

public:

    LReportUndoCommand();
    LReportUndoCommand(LReportDocumentDesigner *designer, LReport *report);

    virtual void undo();
    virtual void redo();

    void setReady();

    LReportDocumentDesigner *designer() const;
    LReport *report() const;

    void setDesigner(LReportDocumentDesigner *designer);
    void setReport(LReport *report);

    void setOldState(QString oldState);
    void setNewState(QString newState);

    void setOldName(QString oldName);
    void setNewName(QString newName);

};

LEAF_END_NAMESPACE

#endif // QREPORTUNDOCOMMANDS_H
