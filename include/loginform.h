#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QDialog>

#include "include/kanbanboard.h"
#include "include/registerform.h"

namespace Ui {
class LoginForm;
}

class LoginForm : public QDialog
{
    Q_OBJECT

public:
    KanbanBoard& board = KanbanBoard::getInstance();
    explicit LoginForm(QWidget *parent = nullptr);
    ~LoginForm();
    void updateForm();

private slots:
    void on_loginButton_clicked();
    void on_registerButton_clicked();

signals:
    void loginSuccessful();

private:
    Ui::LoginForm *ui;
};

#endif // LOGINFORM_H
