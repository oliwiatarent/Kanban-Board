#include "include/customcheckbox.h"
#include "ui_customcheckbox.h"

CustomCheckbox::CustomCheckbox(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CustomCheckbox)
{
    ui->setupUi(this);
}

CustomCheckbox::~CustomCheckbox()
{
    delete ui;
}

void CustomCheckbox::setDescription(QString description) {
    this->ui->subtaskLabel->setText(description);
}

void CustomCheckbox::setProperties(bool done) {
    if (done){
        ui->checkBox->setCheckState(Qt::Checked);
        this->ui->subtaskLabel->setStyleSheet("text-decoration: line-through;");
    }
    else {
        ui->checkBox->setCheckState(Qt::Unchecked);
        this->ui->subtaskLabel->setStyleSheet("text-decoration: none;");
    }
}

void CustomCheckbox::changeLabelHeight() {
    int height = this->ui->subtaskLabel->sizeHint().height();
    this->ui->subtaskLabel->setMinimumHeight(this->ui->subtaskLabel->sizeHint().height());
    this->setMinimumHeight(height);
}

void CustomCheckbox::on_checkBox_checkStateChanged(const Qt::CheckState &done) {
    int subtaskIndex = this->property("subtaskIndex").toInt();
    int columnNumber = this->property("columnNumber").toInt();
    int taskIndex = this->property("taskIndex").toInt();

    Subtask* subtask = board.getSubtask(taskIndex, columnNumber, subtaskIndex);
    if (done == Qt::Checked) {
        subtask->setDone(true);
        ui->subtaskLabel->setStyleSheet("text-decoration: line-through;");
    } else {
        subtask->setDone(false);
        ui->subtaskLabel->setStyleSheet("text-decoration: none;");
    }
}


void CustomCheckbox::on_deleteButton_clicked() {
    int subtaskIndex = this->property("subtaskIndex").toInt();
    int columnNumber = this->property("columnNumber").toInt();
    int taskIndex = this->property("taskIndex").toInt();

    board.deleteSubtask(taskIndex, columnNumber, subtaskIndex);

    emit subtaskDeleted();
}

