#ifndef ADDFORM_H
#define ADDFORM_H

#include <QDialog>
#include <QDebug>
#include <QString>

#include "include/kanbanboard.h"

namespace Ui {
class AddForm;
}

class AddForm : public QDialog
{
    Q_OBJECT

public:
    KanbanBoard& board = KanbanBoard::getInstance();
    explicit AddForm(QWidget *parent = nullptr);
    ~AddForm();
    void setTitleText(QString title);
    void setDescriptionText(QString description);
    void setPriorityOption(QString priority);
    void updateUI();

private slots:
    void on_cancelButton_clicked();
    void on_addButton_clicked();

private:
    Ui::AddForm *ui;

signals:
    void taskAdded();
    void taskEdited();
};

#endif // ADDFORM_H
