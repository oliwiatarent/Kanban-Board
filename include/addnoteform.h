#ifndef ADDNOTEFORM_H
#define ADDNOTEFORM_H

#include <QDialog>
#include <QColorDialog>

#include "include/kanbanboard.h"
#include "include/note.h"

namespace Ui {
class AddNoteForm;
}

class AddNoteForm : public QDialog
{
    Q_OBJECT

private:
    QColor color = "#fdff9e";

public:
    KanbanBoard& board = KanbanBoard::getInstance();
    explicit AddNoteForm(QWidget *parent = nullptr);
    ~AddNoteForm();
    void updateUI();
    void setColor(QColor color);
    void setTitleText(QString title);
    void setDescriptionText(QString description);

private slots:
    void on_colorButton_clicked();
    void on_cancelButton_clicked();
    void on_addButton_clicked();

signals:
    void noteAdded();
    void noteEdited();

private:
    Ui::AddNoteForm *ui;
};

#endif // ADDNOTEFORM_H
