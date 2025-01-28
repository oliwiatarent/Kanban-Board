#ifndef CUSTOMCHECKBOX_H
#define CUSTOMCHECKBOX_H

#include <QWidget>

#include "include/kanbanboard.h"
#include "include/subtask.h"

namespace Ui {
class CustomCheckbox;
}

class CustomCheckbox : public QWidget
{
    Q_OBJECT

public:
    KanbanBoard& board = KanbanBoard::getInstance();
    Ui::CustomCheckbox *ui;
    explicit CustomCheckbox(QWidget *parent = nullptr);
    ~CustomCheckbox();
    void setDescription(QString description);
    void setProperties(bool done);
    void changeLabelHeight();

private slots:
    void on_checkBox_checkStateChanged(const Qt::CheckState &arg1);
    void on_deleteButton_clicked();

private:

signals:
    void subtaskDeleted();

};

#endif // CUSTOMCHECKBOX_H
