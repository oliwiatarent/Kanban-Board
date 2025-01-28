#include "include/addsubtaskform.h"
#include "ui_addsubtaskform.h"

AddSubtaskForm::AddSubtaskForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddSubtaskForm)
{
    ui->setupUi(this);
}

AddSubtaskForm::~AddSubtaskForm()
{
    delete ui;
}

void AddSubtaskForm::updateUI()
{
    QString action = this->property("action").toString();

    if (action == "editTask") {
        this->setWindowTitle("Edytuj zadanie");
        ui->addButton->setText("Edytuj");
    }
}

void AddSubtaskForm::setDescriptionText(QString description)
{
    this->ui->txtDescription->setPlainText(description);
}

void AddSubtaskForm::on_addButton_clicked()
{
    QString description = ui -> txtDescription -> toPlainText();
    QString priority = ui -> priorityBox -> currentText();
    QString action = this->property("action").toString();

    int taskIndex = this->property("subtaskIndex").toInt();
    int columnNumber = this->property("columnNumber").toInt();

    if (description == "") {
        ui -> alertBox -> setText("Wypełnij wszystkie pola!");
    } else {
        if (action == "addSubtask") {
            Subtask* subtask = new Subtask(description, priority);

            board.addSubtask(taskIndex, columnNumber, subtask);

            emit subtaskAdded();
        }

        close();
    }
}

void AddSubtaskForm::on_cancelButton_clicked() {
    close();
}

