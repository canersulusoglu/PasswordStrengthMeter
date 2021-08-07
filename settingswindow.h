#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QMainWindow>
#include "passwordgenerator.h"

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget *parent = nullptr);
    ~SettingsWindow();

private:
    Ui::SettingsWindow *ui;
    void LoadSettings();
    void AlphabetChanged(const int& changedIndex);
    void OpenCustomAlphabetInputs();
    void CloseCustomAlphabetInputs();

protected:
    void closeEvent(QCloseEvent *event);
};

#endif // SETTINGSWINDOW_H
