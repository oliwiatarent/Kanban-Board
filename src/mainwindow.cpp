#include "include/mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString buttonNames[] = {"editToDo", "editDoing", "editDone", "editNotes"};
    for (int i = 0; i < 4; i++) {
        QPushButton* button = this->findChild<QPushButton*>(buttonNames[i]);
        connect(button, &QPushButton::clicked, this, &MainWindow::editColumnName);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateUserLabel() {
    User* user = board.getCurrentUser();
    QString userText = user->getFirstName() + " " + user->getSecondName() + " (" + user->getUsername() + ")";
    ui->userLabel->setText("<b>Zalogowano jako:</b> " + userText);
    ui->userLabel->setStyleSheet("font-size: 16px;");
}

void MainWindow::onLoginSuccessful() {
    updateUserLabel();
    this->show();
    this->refreshColumnNames();
    this->refreshColumns();
    this->refreshNotes();
    loginForm->hide();
}

void MainWindow::refreshColumnNames()
{
    QString columnLabels[] = {"labelToDo", "labelDoing", "labelDone", "labelNotes"};

    for (int i = 0; i < 4; i++) {
        QLabel* label = this->findChild<QLabel*>(columnLabels[i]);
        Column* column = board.getColumn(i);
        QString name = column->getName();

        label->setText(name);
    }
}

void MainWindow::clearLayout(QVBoxLayout* layout)
{
    while (QLayoutItem* item = layout->takeAt(0)) {
        if (QWidget* widget = item->widget()) {
            widget->deleteLater();
        }
        delete item;
    }

    layout->update();
}

void MainWindow::refreshColumns()
{
    QString columnWidgets[] = {"widgetsToDo", "widgetsDoing", "widgetsDone"};
    for (int i = 0; i < 3; i++) {
        QString widgetName = columnWidgets[i];
        QWidget* columnWidget = this->findChild<QWidget*>(widgetName);

        columnWidget->setAcceptDrops(true);

        QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(columnWidget->layout());
        if (!layout) {
            layout = new QVBoxLayout(columnWidget);
            columnWidget->setLayout(layout);
        }

        clearLayout(layout);
        layout->setAlignment(Qt::AlignTop);

        Column* column = board.getColumn(i);

        for (int j = 0; j < column->getNumberOfTasks(); j++) {
            Task* task = column->getTask(j);
            task->setId(j);

            TaskWidget* newTask = new TaskWidget(columnWidget, task);
            layout->addWidget(newTask);

            connect(newTask, &TaskWidget::taskDeleted, this, &MainWindow::refreshColumns);
            connect(newTask, &TaskWidget::taskEdited, this, &MainWindow::refreshColumns);
            connect(newTask, &TaskWidget::subtaskAdded, this, &MainWindow::refreshColumns);
            connect(newTask, &TaskWidget::subtaskDeleted, this, &MainWindow::refreshColumns);
        }
    }
}

void MainWindow::refreshNotes() {
    QWidget* columnWidget = this->findChild<QWidget*>("widgetsNotes");

    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(columnWidget->layout());
    if (!layout) {
        layout = new QVBoxLayout(columnWidget);
        columnWidget->setLayout(layout);
    }

    clearLayout(layout);
    layout->setAlignment(Qt::AlignTop);

    Column* column = board.getColumn(3);

    for (int i = 0; i < column->getNumberOfNotes(); i++) {
        Note* note = column->getNote(i);
        note->setId(i);

        NoteWidget* newNote = new NoteWidget(columnWidget, note);
        layout->addWidget(newNote);

        connect(newNote, &NoteWidget::noteDeleted, this, &MainWindow::refreshNotes);
        connect(newNote, &NoteWidget::noteEdited, this, &MainWindow::refreshNotes);
    }
}

void MainWindow::editColumnName() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    int columnNumber = button->property("columnNumber").toInt();

    ColNameEditForm* form = new ColNameEditForm();
    form->setProperty("columnNumber", columnNumber);
    form->changeTitleText(board.getColumn(columnNumber)->getName());
    form->show();

    connect(form, &ColNameEditForm::nameEdited, this, &MainWindow::refreshColumnNames);
}

void MainWindow::on_addTaskButton_clicked()
{
    AddForm* newForm = new AddForm();
    newForm->setProperty("action", "addTask");
    newForm->updateUI();
    newForm->show();

    connect(newForm, &AddForm::taskAdded, this, &MainWindow::refreshColumns);
}

void MainWindow::on_addNoteButton_clicked()
{
    AddNoteForm* newForm = new AddNoteForm();

    newForm->setProperty("action", "addNote");
    newForm->updateUI();
    newForm->show();

    connect(newForm, &AddNoteForm::noteAdded, this, &MainWindow::refreshNotes);
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("taskwidget")) {
        QPoint pos = event->position().toPoint();
        QWidget* targetColumn = this->childAt(pos);

        while (targetColumn &&
               (targetColumn != ui->widgetsToDo &&
                targetColumn != ui->widgetsDoing &&
                targetColumn != ui->widgetsDone)) {
            targetColumn = qobject_cast<QWidget*>(targetColumn->parent());
        }

        if (targetColumn &&
            (targetColumn == ui->widgetsToDo ||
             targetColumn == ui->widgetsDoing ||
             targetColumn == ui->widgetsDone)) {
            event->acceptProposedAction();
        } else {
            event->ignore();
        }
    }
}

void MainWindow::dropEvent(QDropEvent* event)
{
    // Pozycja, na ktorej opuszczono zadanie
    QPoint pos = event->position().toPoint();
    // Znalezienie widgetu, który znajduje sie na tej pozycji
    QWidget* targetColumn = this->childAt(pos);
    // Znalezienie kolumny zrodlowej
    QWidget* sourceColumn = qobject_cast<QWidget*>(event->source()->parent());

    // Znalezeienie kolumny, do ktorej przeniesiono zadanie
    while (targetColumn &&
        (targetColumn != ui->widgetsToDo &&
         targetColumn != ui->widgetsDoing &&
         targetColumn != ui->widgetsDone)) {
        targetColumn = qobject_cast<QWidget*>(targetColumn->parent());
    }

    int taskIndex = event->mimeData()->data("taskwidget").toInt();
    int targetIndex = targetColumn->property("columnNumber").toInt();
    int sourceIndex = sourceColumn->property("columnNumber").toInt();

    board.moveTask(sourceIndex, taskIndex, targetIndex);

    event->acceptProposedAction();

    refreshColumns();
}


void MainWindow::on_logOutButton_clicked()
{
    board.setCurrentUser(nullptr);
    loginForm->show();
    loginForm->updateForm();
    this->hide();
}


void MainWindow::on_editUserButton_clicked()
{
    EditUserForm* newForm = new EditUserForm(this);
    newForm->setFirstNameText(board.getCurrentUser()->getFirstName());
    newForm->setSecondNameText(board.getCurrentUser()->getSecondName());
    newForm->setUsernameText(board.getCurrentUser()->getUsername());
    newForm->show();

    connect(newForm, &EditUserForm::userEdited, this, &MainWindow::refreshColumns);
    connect(newForm, &EditUserForm::userEdited, this, &MainWindow::refreshNotes);
    connect(newForm, &EditUserForm::userEdited, this, &MainWindow::updateUserLabel);
}

