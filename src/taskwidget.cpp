#include "include/taskwidget.h"
#include "ui_taskwidget.h"


TaskWidget::TaskWidget(QWidget *parent, Task* task)
    : QWidget(parent)
    , ui(new Ui::TaskWidget)
{
    ui->setupUi(this);
    ui->taskTitle->setText(task->getTitle());
    ui->taskDescription->setText(task->getDescription());
    ui->userLabel->setText("<b>Dodano przez:</b><br>" + task->getOwner()->getFirstName() + " " + task->getOwner()->getSecondName());

    for (int i = 0; i < task->getNumberOfSubtasks(); i++) {
        Subtask* subtask = task->getSubtask(i);
        subtask->setId(i);

        CustomCheckbox* checkbox = new CustomCheckbox(this);

        ui->subtasksLayout->addWidget(checkbox);

        checkbox->setProperty("subtaskIndex", i);
        checkbox->setProperty("taskIndex", task->getId());
        checkbox->setProperty("columnNumber", getColumnNumber());

        QString priority = subtask->getPriority();
        QString color;
        if (priority == "Wysoki") {
            color = "red";
        } else if (priority == "Średni") {
            color = "orange";
        } else {
            color = "green";
        }

        checkbox->setProperties(subtask->getDone());
        checkbox->setDescription(subtask->getDescription() + "<br><b>Priorytet: <span style=\"color: " + color + ";\"> " + priority + "</span></b>");
        checkbox->changeLabelHeight();

        connect(checkbox, &CustomCheckbox::subtaskDeleted, this, &TaskWidget::subtaskDeleted);
    }

    this->setProperty("index", task->getId());

    QString styleSheet = "border-radius: 20px;";

    QString priority = task->getPriority();
    if (priority == "Niski") {
        styleSheet += "background-color: rgb(204, 245, 196);";
    } else if (priority == "Średni") {
        styleSheet += "background-color: rgb(250, 241, 180);";
    } else {
        styleSheet += "background-color: rgb(245, 196, 196);";
    }

    QFrame* backgroundFrame = new QFrame(this);
    backgroundFrame->setStyleSheet(styleSheet);
    backgroundFrame->lower();

    ui->taskDescription->setWordWrap(true);
    ui->taskDescription->adjustSize();

    ui->taskTitle->setWordWrap(true);
    ui->taskTitle->adjustSize();

    ui->subtasksContainer->setLayout(ui->subtasksLayout);
    ui->subtasksContainer->layout()->invalidate(); // Wymuś ponowne przeliczenie układu
    ui->subtasksContainer->adjustSize();

    adjustWidgetSize();
}

TaskWidget::~TaskWidget()
{
    delete ui;
}

void TaskWidget::adjustWidgetSize()
{
    int titleHeight = ui->taskTitle->sizeHint().height();
    int descriptionHeight = ui->taskDescription->sizeHint().height();
    int buttonHeight = ui->editButton->size().height() + 10;
    int subtasksHeight = ui->subtasksLayout->sizeHint().height() + 20;
    int margins = 40;

    if (subtasksHeight == 0) subtasksHeight = 31;

    int totalHeight = titleHeight + descriptionHeight + buttonHeight + subtasksHeight + margins;

    int currentWidgetSize = this->size().height();
    int defaultTitleHeight = ui->taskTitle->minimumHeight();
    int defaultDescriptionHeight = ui->taskDescription->minimumHeight();

    QFrame* backgroundFrame = findChild<QFrame*>();

    if (totalHeight > currentWidgetSize) {
        this->setMinimumHeight(totalHeight);
        this->adjustSize();

        if (backgroundFrame)
            backgroundFrame->setGeometry(0, 0, this->width(), totalHeight);

        ui->editButton->move(ui->editButton->pos().x(), ui->editButton->pos().y() + ((descriptionHeight + titleHeight + subtasksHeight) - currentWidgetSize + margins + buttonHeight + 3));
        ui->deleteButton->move(ui->deleteButton->pos().x(), ui->deleteButton->pos().y() + ((descriptionHeight + titleHeight + subtasksHeight) - currentWidgetSize + margins + buttonHeight + 3));
        ui->subtaskButton->move(ui->subtaskButton->pos().x(), ui->subtaskButton->pos().y() + ((descriptionHeight + titleHeight + subtasksHeight) - currentWidgetSize + margins + buttonHeight + 3));
        ui->userLabel->move(ui->userLabel->pos().x(), ui->userLabel->pos().y() + ((descriptionHeight + titleHeight + subtasksHeight) - currentWidgetSize + margins + buttonHeight + 3));

        if (defaultTitleHeight < titleHeight) {
            ui->taskDescription->move(ui->taskDescription->pos().x(), ui->taskDescription->pos().y() + (titleHeight - defaultTitleHeight));
        }

        ui->subtasksContainer->move(ui->subtasksContainer->pos().x(), ui->subtasksContainer->pos().y() + ((titleHeight + descriptionHeight) - (defaultDescriptionHeight + defaultTitleHeight)));

    } else {
        if (backgroundFrame)
            backgroundFrame->setGeometry(0, 0, this->width(), this->height());
    }
}

int TaskWidget::getTaskIndex()
{
    return this->property("index").toInt();
}

int TaskWidget::getColumnNumber()
{
    QWidget* parent = this->parentWidget();
    return parent->property("columnNumber").toInt();
}

void TaskWidget::on_deleteButton_clicked()
{
    int taskIndex = getTaskIndex();
    int columnNumber = getColumnNumber();

    board.deleteTaskFromColumn(columnNumber, taskIndex);

    emit taskDeleted();
}

void TaskWidget::on_editButton_clicked()
{
    AddForm* newForm = new AddForm();

    int taskIndex = getTaskIndex();
    int columnNumber = getColumnNumber();

    Column* currentColumn = board.getColumn(columnNumber);
    Task* task = currentColumn->getTask(taskIndex);

    newForm->setProperty("action", "editTask");
    newForm->setTitleText(task->getTitle());
    newForm->setDescriptionText(task->getDescription());
    newForm->setPriorityOption(task->getPriority());
    newForm->setProperty("taskIndex", taskIndex);
    newForm->setProperty("columnNumber", columnNumber);
    newForm->updateUI();
    newForm->show();

    connect(newForm, &AddForm::taskEdited, this, &TaskWidget::taskEdited);
}

void TaskWidget::on_subtaskButton_clicked()
{
    AddSubtaskForm* newForm = new AddSubtaskForm();

    int subtaskIndex = getTaskIndex();
    int columnNumber = getColumnNumber();

    newForm->setProperty("action", "addSubtask");
    newForm->setProperty("subtaskIndex", subtaskIndex);
    newForm->setProperty("columnNumber", columnNumber);
    newForm->updateUI();
    newForm->show();

    connect(newForm, &AddSubtaskForm::subtaskAdded, this, &TaskWidget::subtaskAdded);
}


void TaskWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        QDrag *drag = new QDrag(this);
        QMimeData *mimeData = new QMimeData;

        mimeData->setData("taskwidget", QByteArray::number(this->property("index").toInt()));

        drag->setMimeData(mimeData);
        drag->exec(Qt::MoveAction);
    }
}

