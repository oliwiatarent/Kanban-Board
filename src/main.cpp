#include "include/mainwindow.h"
#include "include/loginform.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginForm *loginWindow = new LoginForm();
    MainWindow *mainWindow = new MainWindow();
    mainWindow->loginForm = loginWindow;

    QObject::connect(loginWindow, &LoginForm::loginSuccessful, mainWindow, &MainWindow::onLoginSuccessful);

    loginWindow->show();

    return a.exec();
}
