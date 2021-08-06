#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    MainWindow mainWindow;
    mainWindow.setWindowTitle("Password Strength Meter");
    mainWindow.show();
    return application.exec();
}
