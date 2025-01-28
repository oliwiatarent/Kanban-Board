#include "include/loginform.h"
#include "ui_loginform.h"
#include "include/mainwindow.h"

LoginForm::LoginForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginForm)
{
    ui->setupUi(this);
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::updateForm() {
    ui->nameText->setText("");
    ui->passwordText->setText("");
    ui->alertBox->setText("");
}

void LoginForm::on_loginButton_clicked()
{
    QString username = ui->nameText->text();
    QString password = ui->passwordText->text();

    if (username == "" || password == "") {
        ui->alertBox->setText("Nieprawidłowe dane logowania!");
    } else {
        if (board.authorizeUser(username, password)) {
            board.setCurrentUser(board.getUser(username));
            emit loginSuccessful();
        } else {
            ui->alertBox->setText("Nieprawidłowe dane logowania!");
        }
    }
}


void LoginForm::on_registerButton_clicked()
{
    RegisterForm *registerForm = new RegisterForm(this);
    registerForm->show();
}

