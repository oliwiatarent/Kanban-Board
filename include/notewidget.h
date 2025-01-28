#ifndef NOTEWIDGET_H
#define NOTEWIDGET_H

#include <QWidget>

#include "include/note.h"
#include "include/kanbanboard.h"
#include "include/addnoteform.h"

namespace Ui {
class NoteWidget;
}

class NoteWidget : public QWidget
{
    Q_OBJECT

public:
    KanbanBoard& board = KanbanBoard::getInstance();

    explicit NoteWidget(QWidget *parent = nullptr, Note *note = nullptr);
    ~NoteWidget();
    void adjustWidgetSize();
    int getNoteIndex();
    int getColumnNumber();

private slots:
    void on_deleteButton_clicked();
    void on_editButton_clicked();

private:
    Ui::NoteWidget *ui;

signals:
    void noteDeleted();
    void noteEdited();
};

#endif // NOTEWIDGET_H
