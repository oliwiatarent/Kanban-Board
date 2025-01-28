#ifndef REGISTERFORM_H
#define REGISTERFORM_H

#include <QDialog>

#include "include/kanbanboard.h"

namespace Ui {
class RegisterForm;
}

class RegisterForm : public QDialog
{
    Q_OBJECT

public:
    KanbanBoard& board = KanbanBoard::getInstance();
    explicit RegisterForm(QWidget *parent = nullptr);
    ~RegisterForm();

private slots:
    void on_registerButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::RegisterForm *ui;
};

#endif // REGISTERFORM_H
