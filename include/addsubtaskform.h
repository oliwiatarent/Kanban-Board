#ifndef ADDSUBTASKFORM_H
#define ADDSUBTASKFORM_H

#include <QDialog>

#include "include/kanbanboard.h"
#include "include/subtask.h"

namespace Ui {
class AddSubtaskForm;
}

class AddSubtaskForm : public QDialog
{
    Q_OBJECT

public:
    KanbanBoard& board = KanbanBoard::getInstance();
    explicit AddSubtaskForm(QWidget *parent = nullptr);
    ~AddSubtaskForm();
    void updateUI();
    void setDescriptionText(QString description);

private slots:
    void on_cancelButton_clicked();
    void on_addButton_clicked();

signals:
    void subtaskAdded();

private:
    Ui::AddSubtaskForm *ui;
};

#endif // ADDSUBTASKFORM_H
