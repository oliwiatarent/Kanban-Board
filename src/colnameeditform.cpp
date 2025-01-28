#include "include/colnameeditform.h"
#include "ui_colnameeditform.h"

ColNameEditForm::ColNameEditForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ColNameEditForm)
{
    ui->setupUi(this);
}

ColNameEditForm::~ColNameEditForm()
{
    delete ui;
}

void ColNameEditForm::changeTitleText(QString title) {
    this->ui->titleLine->setText(title);
}

void ColNameEditForm::on_editButton_clicked()
{
    QString title = ui->titleLine->text();

    if (title != "") {
        int columnNumber = this->property("columnNumber").toInt();
        Column* column = board.getColumn(columnNumber);
        column->setName(title);
        emit nameEdited();
    }

    close();
}

void ColNameEditForm::on_cancelButton_clicked()
{
    close();
}
