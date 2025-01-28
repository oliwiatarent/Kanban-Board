#ifndef COLNAMEEDITFORM_H
#define COLNAMEEDITFORM_H

#include <QDialog>

#include "include/kanbanboard.h"

namespace Ui {
class ColNameEditForm;
}

class ColNameEditForm : public QDialog
{
    Q_OBJECT

public:
    explicit ColNameEditForm(QWidget *parent = nullptr);
    ~ColNameEditForm();
    KanbanBoard& board = KanbanBoard::getInstance();
    void changeTitleText(QString title);

private slots:
    void on_editButton_clicked();
    void on_cancelButton_clicked();

signals:
    void nameEdited();

private:
    Ui::ColNameEditForm *ui;
};

#endif // COLNAMEEDITFORM_H
