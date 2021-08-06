#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QMessageBox>
#include "ui_mainwindow.h"
#include <string>
#include "alphabet.h"
#include "passwordgenerator.h"
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    PasswordGenerator* passwordGenerator;
    Ui::MainWindow *ui;
    QTableWidgetItem* TableItem(string name);
    void setAdditionsTableItemValue(int row, int column, int value);
    void setDeductionsTableItemValue(int row, int column, int value);
    void DrawTable();
    void RandomPasswordButtonClicked();
    void PasswordInputTextChanged(const QString& changedValue);
    void RandomPasswordLengthChanged(const int& changedValue);
    void placeStrengthValuesToTables(PasswordStrengthValues strengthValues);
    void placeTableBackgroundColor(PasswordStrengthValues strengthValues);
    void setPasswordStrengthDisplay(int score);
    void setRowBackgrounColor(QTableWidget* table,int row, QColor color);
};
#endif // MAINWINDOW_H
