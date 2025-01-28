#ifndef TASKWIDGET_H
#define TASKWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <QCheckBox>

#include "include/task.h"
#include "include/kanbanboard.h"
#include "include/mainwindow.h"
#include "include/subtask.h"
#include "include/customcheckbox.h"
#include "include/addsubtaskform.h"

namespace Ui {
class TaskWidget;
}

class TaskWidget : public QWidget
{
    Q_OBJECT

public:
    KanbanBoard& board = KanbanBoard::getInstance();

    explicit TaskWidget(QWidget *parent = nullptr, Task* task = nullptr);
    explicit TaskWidget(QWidget *parent = nullptr, Note* note = nullptr);
    ~TaskWidget();
    void adjustWidgetSize();
    int getTaskIndex();
    int getColumnNumber();
    void mousePressEvent(QMouseEvent *event);

private slots:
    void on_deleteButton_clicked();
    void on_editButton_clicked();
    void on_subtaskButton_clicked();

private:
    Ui::TaskWidget *ui;

signals:
    void taskDeleted();
    void taskEdited();
    void subtaskAdded();
    void subtaskDeleted();
};

#endif // TASKWIDGET_H
