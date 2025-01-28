#include "include/registerform.h"
#include "ui_registerform.h"

RegisterForm::RegisterForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterForm)
{
    ui->setupUi(this);
}

RegisterForm::~RegisterForm()
{
    delete ui;
}

void RegisterForm::on_registerButton_clicked()
{
    QString firstName = ui->firstNameText->text();
    QString secondName = ui->secondNameText->text();
    QString username = ui->usernameText->text();
    QString password = ui->passwordText->text();
    QString repeatPassword = ui->repeatPasswordText->text();

    if (firstName == "" || secondName == "" || username == "" || password == "" || repeatPassword == "") {
        ui -> alertBox -> setText("Wypełnij wszystkie pola!");
    } else {
        if (password != repeatPassword){
            ui -> alertBox -> setText("Hasła nie są takie same!");
        } else {
            if (board.getUser(username) != nullptr) {
                ui -> alertBox -> setText("Użytkownik już istnieje!");
                return;
            }

            User newUser = User(firstName, secondName, username, password);
            board.addUser(newUser);

            close();
        }
    }
}


void RegisterForm::on_cancelButton_clicked()
{
    close();
}

