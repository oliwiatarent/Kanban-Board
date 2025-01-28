#ifndef EDITUSERFORM_H
#define EDITUSERFORM_H

#include <QDialog>

#include "include/kanbanboard.h"

namespace Ui {
class EditUserForm;
}

class EditUserForm : public QDialog
{
    Q_OBJECT

public:
    KanbanBoard& board = KanbanBoard::getInstance();
    explicit EditUserForm(QWidget *parent = nullptr);
    ~EditUserForm();
    void updateUI(bool checked);
    void setFirstNameText(QString firstName);
    void setSecondNameText(QString secondName);
    void setUsernameText(QString username);

private slots:
    void on_cancelButton_clicked();
    void on_newPasswordCheckbox_checkStateChanged(const Qt::CheckState &arg1);
    void on_updateButton_clicked();

signals:
    void userEdited();

private:
    Ui::EditUserForm *ui;
};

#endif // EDITUSERFORM_H
