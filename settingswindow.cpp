#include "settingswindow.h"
#include "ui_settingswindow.h"

SettingsWindow::SettingsWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::SettingsWindow){
    ui->setupUi(this);
    this->setWindowTitle("Settings");
    ui->alphabetComboBox->addItems(alphabetNameList);
    connect(ui->alphabetComboBox, &QComboBox::currentIndexChanged, this, &SettingsWindow::AlphabetChanged);
    LoadSettings();
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

void SettingsWindow::LoadSettings(){
    Alphabet* alphabet = PasswordGenerator::GetInstance()->getAlphabet();
    AlphabetName alphabetName = alphabet->getAlphabetName();
    ui->alphabetComboBox->setCurrentIndex(alphabetName);
    if(alphabetName == AlphabetName::Custom){
        OpenCustomAlphabetInputs();
        ui->customAlphabetUpperCaseLettersInput->setText(QString::fromStdString(alphabet->getUpperCaseLetters()));
        ui->customAlphabetLowerCaseLettersInput->setText(QString::fromStdString(alphabet->getLowerCaseLetters()));
        ui->customAlphabetNumbersInput->setText(QString::fromStdString(alphabet->getNumbers()));
        ui->customAlphabetSymbolsInput->setText(QString::fromStdString(alphabet->getSymbols()));
    }else{
        CloseCustomAlphabetInputs();
    }
}

void SettingsWindow::closeEvent(QCloseEvent *event){
    int selectedAlphabet = ui->alphabetComboBox->currentIndex();
    if(selectedAlphabet == AlphabetName::Custom){
        CustomAlphabet customAlphabet;
        customAlphabet.UpperCaseLetters = ui->customAlphabetUpperCaseLettersInput->text().toStdString();
        customAlphabet.LowerCaseLetters = ui->customAlphabetLowerCaseLettersInput->text().toStdString();
        customAlphabet.Numbers = ui->customAlphabetNumbersInput->text().toStdString();
        customAlphabet.Symbols = ui->customAlphabetSymbolsInput->text().toStdString();
        PasswordGenerator::GetInstance()->setAlphabet(new Alphabet(customAlphabet));
    }else{
        PasswordGenerator::GetInstance()->setAlphabet(new Alphabet((AlphabetName)selectedAlphabet));
    }
}

void SettingsWindow::AlphabetChanged(const int& changedIndex){
    if(changedIndex == 0){
        OpenCustomAlphabetInputs();
    }else{
        CloseCustomAlphabetInputs();
    }
}

void SettingsWindow::OpenCustomAlphabetInputs(){
    ui->customAlphabetWidget->setVisible(true);
    this->setFixedHeight(420);
}

void SettingsWindow::CloseCustomAlphabetInputs(){
    ui->customAlphabetWidget->setVisible(false);
    this->setFixedHeight(120);
}
