#include "include/edituserform.h"
#include "ui_edituserform.h"

EditUserForm::EditUserForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditUserForm)
{
    ui->setupUi(this);

    updateUI(0);
}

EditUserForm::~EditUserForm()
{
    delete ui;
}

void EditUserForm::updateUI(bool checked) {
    if (checked) {
        ui->newPasswordLabel->show();
        ui->newPasswordRepeatLabel->show();
        ui->newPasswordText->show();
        ui->newPasswordRepeatText->show();
    } else {
        ui->newPasswordLabel->hide();
        ui->newPasswordRepeatLabel->hide();
        ui->newPasswordText->hide();
        ui->newPasswordRepeatText->hide();
    }
}

void EditUserForm::setFirstNameText(QString firstName) {
    ui->firstNameText->setText(firstName);
}

void EditUserForm::setSecondNameText(QString secondName) {
    ui->secondNameText->setText(secondName);
}

void EditUserForm::setUsernameText(QString username) {
    ui->usernameText->setText(username);
}

void EditUserForm::on_cancelButton_clicked()
{
    close();
}


void EditUserForm::on_newPasswordCheckbox_checkStateChanged(const Qt::CheckState &state)
{
    if (state == Qt::Checked) {
        updateUI(1);
    } else {
        updateUI(0);
    }
}


void EditUserForm::on_updateButton_clicked()
{
    QString firstName = ui->firstNameText->text();
    QString secondName = ui->secondNameText->text();
    QString username = ui->usernameText->text();
    QString oldPassword = ui->passwordText->text();
    QString newPassword, repeatPassword;

    bool checked = ui->newPasswordCheckbox->isChecked();
    bool required = firstName == "" || secondName == "" || username == "" || oldPassword == "";

    if (checked) {
        newPassword = ui->newPasswordText->text();
        repeatPassword = ui->newPasswordRepeatText->text();
        required = required || newPassword == "" || repeatPassword == "";
    }

    if (required) {
        ui->alertBox->setText("Wypełnij wszystkie pola!");
        return;
    }

    if (checked) {
        if (oldPassword == board.getCurrentUser()->getPassword()) {
            if (newPassword == repeatPassword) {
                board.getCurrentUser()->setFirstName(firstName);
                board.getCurrentUser()->setSecondName(secondName);
                board.getCurrentUser()->setUsername(username);
                board.getCurrentUser()->setPassword(newPassword);

                emit userEdited();
                close();
            } else {
                ui->alertBox->setText("Hasła nie są takie same!");
            }
        } else {
            ui->alertBox->setText("Hasło jest niepoprawne!");
        }
    } else {
        if (oldPassword == board.getCurrentUser()->getPassword()) {
            board.getCurrentUser()->setFirstName(firstName);
            board.getCurrentUser()->setSecondName(secondName);
            board.getCurrentUser()->setUsername(username);

            emit userEdited();
            close();
        } else {
            ui->alertBox->setText("Hasło jest niepoprawne!");
        }
    }
}
