#include "include/addnoteform.h"
#include "ui_addnoteform.h"

AddNoteForm::AddNoteForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddNoteForm)
{
    ui->setupUi(this);

    ui->colorChosen->setFrameStyle(QFrame::NoFrame);
    ui->colorChosen->setAttribute(Qt::WA_StyledBackground, true);
    QString styleSheet = "background-color: " + color.name() + "; border-radius: 20px;";
    ui->colorChosen->setStyleSheet(styleSheet);
}

AddNoteForm::~AddNoteForm()
{
    delete ui;
}

void AddNoteForm::updateUI() {
    QString action = this->property("action").toString();

    if (action == "editNote") {
        this->setWindowTitle("Edytuj notatkę");
        ui->addButton->setText("Edytuj");
    }
}

void AddNoteForm::setColor(QColor color) {
    this->color = color;
    this->ui->colorChosen->setStyleSheet("background-color: " + color.name() + ";");
}

void AddNoteForm::setTitleText(QString title) {
    this->ui->txtTitle->setText(title);
}

void AddNoteForm::setDescriptionText(QString description) {
    this->ui->txtDescription->setPlainText(description);
}

void AddNoteForm::on_colorButton_clicked() {
    color = QColorDialog::getColor(color.name(), this, "Wybierz kolor");

    if (color.isValid()) {
        QString styleSheet = "background-color: " + color.name() + "; border-radius: 20px;";
        ui->colorChosen->setStyleSheet(styleSheet);
    }
}

void AddNoteForm::on_addButton_clicked() {
    QString title = ui -> txtTitle -> text();
    QString description = ui -> txtDescription -> toPlainText();
    QString action = this->property("action").toString();
    int noteIndex = this->property("noteIndex").toInt();

    if (title == "" || description == "") {
        ui -> alertBox -> setText("Wypełnij wszystkie pola!");
    } else {
        if (action == "addNote") {
            Note note = Note(title, description, color, board.getCurrentUser());

            board.addNote(note);

            emit noteAdded();
        }

        if (action == "editNote") {
            Note* editedNote = new Note(title, description, color, board.getCurrentUser());

            board.editNote(noteIndex, editedNote);

            emit noteEdited();
        }

        close();
    }
}

void AddNoteForm::on_cancelButton_clicked() {
    close();
}
