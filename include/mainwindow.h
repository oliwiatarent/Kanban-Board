#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "include/addform.h"
#include "include/addnoteform.h"
#include "include/taskwidget.h"
#include "include/notewidget.h"
#include "include/kanbanboard.h"
#include "include/colnameeditform.h"
#include "include/loginform.h"
#include "include/user.h"
#include "include/edituserform.h"

#include <QMainWindow>
#include <QVBoxLayout>
#include <QDrag>
#include <QMimeData>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    LoginForm *loginForm;
    KanbanBoard& board = KanbanBoard::getInstance();
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void updateUserLabel();
    void onLoginSuccessful();
    void refreshColumnNames();
    void refreshColumns();
    void refreshNotes();
    void editColumnName();
    void dragEnterEvent(QDragEnterEvent* event);
    void dropEvent(QDropEvent* event);

private slots:
    void clearLayout(QVBoxLayout* layout);
    void on_addTaskButton_clicked();
    void on_addNoteButton_clicked();
    void on_logOutButton_clicked();
    void on_editUserButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
