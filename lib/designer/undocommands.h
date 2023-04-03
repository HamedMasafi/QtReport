#ifndef QREPORTUNDOCOMMANDS_H
#define QREPORTUNDOCOMMANDS_H

#include "qtreportglobal.h"
#include <QUndoCommand>

LEAF_BEGIN_NAMESPACE

class Report;
class DocumentDesigner;
class UndoCommandPrivate;
class DataConnection;
class DataTable;
class Band;
class Parametere;
class WidgetBase;
class Variable;
class UndoCommand : public QUndoCommand
{

private:
    UndoCommandPrivate *d_ptr;
    Q_DECLARE_PRIVATE(UndoCommand)

public:

    UndoCommand();
    UndoCommand(DocumentDesigner *designer, Report *report);

    virtual void undo();
    virtual void redo();

    void setReady();

    DocumentDesigner *designer() const;
    Report *report() const;

    void setDesigner(DocumentDesigner *designer);
    void setReport(Report *report);

    void setOldState(QString oldState);
    void setNewState(QString newState);

    void setOldName(QString oldName);
    void setNewName(QString newName);

};

#define UNDO_COMMAND_DECL(TYPE) \
class TYPE##UndoCommand : public UndoCommand \
{ \
    TYPE *obj; \
public: \
    TYPE##UndoCommand(TYPE *object, DocumentDesigner *designer, Report *report); \
public: \
    void undo() Q_DECL_OVERRIDE; \
    void redo() Q_DECL_OVERRIDE; \
};

UNDO_COMMAND_DECL(DataConnection)
UNDO_COMMAND_DECL(DataTable)
UNDO_COMMAND_DECL(Band)
UNDO_COMMAND_DECL(Parametere)
UNDO_COMMAND_DECL(WidgetBase)
UNDO_COMMAND_DECL(Variable)

LEAF_END_NAMESPACE

#endif // QREPORTUNDOCOMMANDS_H
