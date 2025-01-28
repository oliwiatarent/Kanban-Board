#include "include/notewidget.h"
#include "ui_notewidget.h"

NoteWidget::NoteWidget(QWidget *parent, Note *note)
    : QWidget(parent)
    , ui(new Ui::NoteWidget)
{
    ui->setupUi(this);
    ui->noteTitle->setText(note->getTitle());
    ui->noteDescription->setText(note->getDescription());
    ui->userLabel->setText("<b>Dodano przez:</b><br>" + note->getOwner()->getFirstName() + " " + note->getOwner()->getSecondName());

    this->setProperty("index", note->getId());

    QColor noteColor = note->getColor();
    QString styleSheet = "border-radius: 20px; background-color: " + noteColor.name() + ";";

    QFrame* backgroundFrame = new QFrame(this);
    backgroundFrame->setStyleSheet(styleSheet);
    backgroundFrame->lower();

    ui->noteDescription->setWordWrap(true);
    ui->noteDescription->adjustSize();

    ui->noteTitle->setWordWrap(true);
    ui->noteTitle->adjustSize();

    adjustWidgetSize();
}

NoteWidget::~NoteWidget()
{
    delete ui;
}

void NoteWidget::adjustWidgetSize()
{
    int titleHeight = ui->noteTitle->sizeHint().height();
    int descriptionHeight = ui->noteDescription->sizeHint().height() + 20;
    int buttonHeight = ui->editButton->size().height();
    int margins = 40;

    int totalHeight = titleHeight + descriptionHeight + buttonHeight + margins;

    int currentWidgetSize = this->size().height();
    int defaultTitleHeight = ui->noteTitle->minimumHeight();

    QFrame* backgroundFrame = findChild<QFrame*>();

    if (totalHeight > currentWidgetSize) {
        this->setMinimumHeight(totalHeight);
        this->adjustSize();

        if (backgroundFrame)
            backgroundFrame->setGeometry(0, 0, this->width(), totalHeight);

        ui->editButton->move(ui->editButton->pos().x(), ui->editButton->pos().y() + ((descriptionHeight + titleHeight) - currentWidgetSize + margins + buttonHeight + 3));
        ui->deleteButton->move(ui->deleteButton->pos().x(), ui->deleteButton->pos().y() + ((descriptionHeight + titleHeight) - currentWidgetSize + margins + buttonHeight + 3));
        ui->userLabel->move(ui->userLabel->pos().x(), ui->userLabel->pos().y() + ((descriptionHeight + titleHeight) - currentWidgetSize + margins + buttonHeight + 3));

        if (defaultTitleHeight < titleHeight) {
            ui->noteDescription->move(ui->noteDescription->pos().x(), ui->noteDescription->pos().y() + (titleHeight - defaultTitleHeight));
        }
    } else {
        if (backgroundFrame)
            backgroundFrame->setGeometry(0, 0, this->width(), this->height());
    }
}

int NoteWidget::getNoteIndex()
{
    return this->property("index").toInt();
}

void NoteWidget::on_deleteButton_clicked()
{
    int noteIndex = getNoteIndex();

    board.deleteNote(noteIndex);

    emit noteDeleted();
}

void NoteWidget::on_editButton_clicked()
{
    AddNoteForm* newForm = new AddNoteForm();

    int noteIndex = getNoteIndex();

    Column* notesColumn = board.getColumn(3);
    Note* note = notesColumn->getNote(noteIndex);

    newForm->setProperty("action", "editNote");
    newForm->setProperty("noteIndex", noteIndex);
    newForm->setTitleText(note->getTitle());
    newForm->setDescriptionText(note->getDescription());
    newForm->setColor(note->getColor());
    newForm->updateUI();
    newForm->show();

    connect(newForm, &AddNoteForm::noteEdited, this, &NoteWidget::noteEdited);
}
