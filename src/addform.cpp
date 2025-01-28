#include "include/addform.h"
#include "ui_addform.h"

using namespace std;

AddForm::AddForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddForm)
{
    ui->setupUi(this);
}

AddForm::~AddForm()
{
    delete ui;
}

void AddForm::updateUI()
{
    QString action = this->property("action").toString();

    if (action == "editTask") {
        this->setWindowTitle("Edytuj zadanie");
        ui->addButton->setText("Edytuj");
    }
}

void AddForm::setTitleText(QString title)
{
    this->ui->txtTitle->setText(title);
}

void AddForm::setDescriptionText(QString description)
{
    this->ui->txtDescription->setPlainText(description);
}

void AddForm::setPriorityOption(QString priority)
{
    this->ui->priorityBox->setCurrentText(priority);
}

void AddForm::on_addButton_clicked()
{
    QString title = ui -> txtTitle -> text();
    QString description = ui -> txtDescription -> toPlainText();
    QString priority = ui -> priorityBox -> currentText();
    QString action = this->property("action").toString();

    int taskIndex = this->property("taskIndex").toInt();
    int columnNumber = this->property("columnNumber").toInt();

    if (title == "" || description == "") {
        ui->alertBox->setText("Wypełnij wszystkie pola!");
    } else {
        if (action == "addTask") {
            Task task(title, description, priority, board.getCurrentUser());
            board.addTaskToColumn(0, task);

            emit taskAdded();
        }

        if (action == "editTask") {
            Task* editedTask = new Task(title, description, priority, board.getCurrentUser());

            board.editTaskFromColumn(columnNumber, taskIndex, editedTask);

            emit taskEdited();
        }

        close();
    }
}

void AddForm::on_cancelButton_clicked()
{
    close();
}
