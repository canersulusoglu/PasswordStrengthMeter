#include "mainwindow.h"

QColor redColor = QColor::fromRgbF(255, 0, 0, 0.5);
QColor greenColor = QColor::fromRgbF(0, 255, 0, 0.5);
QColor blueColor = QColor::fromRgbF(0, 0, 255, 0.5);
QColor yellowColor = QColor::fromRgbF(255, 255, 0, 0.5);

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    this->setWindowTitle("Password Strength Meter");
    connect(ui->randomPasswordButton, &QPushButton::clicked, this, &MainWindow::RandomPasswordButtonClicked);
    connect(ui->passwordInput, &QLineEdit::textChanged, this, &MainWindow::PasswordInputTextChanged);
    connect(ui->passwordLengthSlider, &QSlider::valueChanged, this, &MainWindow::RandomPasswordLengthChanged);
    connect(ui->actionSettings, &QAction::triggered, this, &MainWindow::OpenSettingsWindow);
    ui->passwordLengthText->setText(QString::fromStdString(to_string(ui->passwordLengthSlider->value())));
    DrawTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QTableWidgetItem* MainWindow::TableItem(string name){
    QTableWidgetItem *item = new QTableWidgetItem(QString::fromStdString(name));
    item->setTextAlignment(Qt::AlignHCenter);
    item->setFlags(item->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsSelectable);
    return item;
}

void MainWindow::setAdditionsTableItemValue(int row, int column, int value){
    QTableWidget* AdditionsTable = ui->passwordStrengthAdditionsTable;
    AdditionsTable->setItem(row, column, TableItem(to_string(value)));
}

void MainWindow::setDeductionsTableItemValue(int row, int column, int value){
    QTableWidget* DeductionsTable = ui->passwordStrengthDeductionsTable;
    DeductionsTable->setItem(row, column, TableItem(to_string(value)));
}

void MainWindow::DrawTable(){
    QTableWidget* AdditionsTable = ui->passwordStrengthAdditionsTable;
    QTableWidget* DeductionsTable = ui->passwordStrengthDeductionsTable;

    AdditionsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    AdditionsTable->horizontalHeader()->setStyleSheet("QHeaderView{ font-weight: bold; font-size: 14px; }");
    QTimer::singleShot(10, this, [=]() {
        AdditionsTable->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    });
    AdditionsTable->setColumnCount(5);
    AdditionsTable->setRowCount(7);
    QStringList AdditionsTableHeaderItems { "Addition Name", "Type", "Rate","Count", "Score(+)"};
    AdditionsTable->setHorizontalHeaderLabels(AdditionsTableHeaderItems);
    AdditionsTable->setItem(0, 0, TableItem("Number of characters"));
    AdditionsTable->setItem(0, 1, TableItem("Flat"));
    AdditionsTable->setItem(0, 2, TableItem("+(n*4)"));
    AdditionsTable->setItem(0, 3, TableItem("0"));
    AdditionsTable->setItem(0, 4, TableItem("0"));
    AdditionsTable->setItem(1, 0, TableItem("Uppercase letters"));
    AdditionsTable->setItem(1, 1, TableItem("Cond/Incr"));
    AdditionsTable->setItem(1, 2, TableItem("+((len-n)*2)"));
    AdditionsTable->setItem(1, 3, TableItem("0"));
    AdditionsTable->setItem(1, 4, TableItem("0"));
    AdditionsTable->setItem(2, 0, TableItem("Lowercase letters"));
    AdditionsTable->setItem(2, 1, TableItem("Cond/Incr"));
    AdditionsTable->setItem(2, 2, TableItem("+((len-n)*2)"));
    AdditionsTable->setItem(2, 3, TableItem("0"));
    AdditionsTable->setItem(2, 4, TableItem("0"));
    AdditionsTable->setItem(3, 0, TableItem("Numbers"));
    AdditionsTable->setItem(3, 1, TableItem("Cond"));
    AdditionsTable->setItem(3, 2, TableItem("+(n*4)"));
    AdditionsTable->setItem(3, 3, TableItem("0"));
    AdditionsTable->setItem(3, 4, TableItem("0"));
    AdditionsTable->setItem(4, 0, TableItem("Symbols"));
    AdditionsTable->setItem(4, 1, TableItem("Flat"));
    AdditionsTable->setItem(4, 2, TableItem("+(n*6)"));
    AdditionsTable->setItem(4, 3, TableItem("0"));
    AdditionsTable->setItem(4, 4, TableItem("0"));
    AdditionsTable->setItem(5, 0, TableItem("Middle numbers or symbols"));
    AdditionsTable->setItem(5, 1, TableItem("Flat"));
    AdditionsTable->setItem(5, 2, TableItem("+(n*2)"));
    AdditionsTable->setItem(5, 3, TableItem("0"));
    AdditionsTable->setItem(5, 4, TableItem("0"));
    AdditionsTable->setItem(6, 0, TableItem("Minimum requirements"));
    AdditionsTable->setItem(6, 1, TableItem("Flat"));
    AdditionsTable->setItem(6, 2, TableItem("+(n*2)"));
    AdditionsTable->setItem(6, 3, TableItem("0"));
    AdditionsTable->setItem(6, 4, TableItem("0"));

    DeductionsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    DeductionsTable->horizontalHeader()->setStyleSheet("QHeaderView{ font-weight: bold; font-size: 14px; }");
    QTimer::singleShot(10, this, [=]() {
        DeductionsTable->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    });
    DeductionsTable->setColumnCount(5);
    DeductionsTable->setRowCount(9);
    QStringList DeductionsTableHeaderItems { "Deduction Name", "Type", "Rate","Count", "Score(-)"};
    DeductionsTable->setHorizontalHeaderLabels(DeductionsTableHeaderItems);
    DeductionsTable->setItem(0, 0, TableItem("Letters only"));
    DeductionsTable->setItem(0, 1, TableItem("Flat"));
    DeductionsTable->setItem(0, 2, TableItem("-n"));
    DeductionsTable->setItem(0, 3, TableItem("0"));
    DeductionsTable->setItem(0, 4, TableItem("0"));
    DeductionsTable->setItem(1, 0, TableItem("Numbers only"));
    DeductionsTable->setItem(1, 1, TableItem("Flat"));
    DeductionsTable->setItem(1, 2, TableItem("-n"));
    DeductionsTable->setItem(1, 3, TableItem("0"));
    DeductionsTable->setItem(1, 4, TableItem("0"));
    DeductionsTable->setItem(2, 0, TableItem("Repeat Characters"));
    DeductionsTable->setItem(2, 1, TableItem("Comp"));
    DeductionsTable->setItem(2, 2, TableItem("-n*(n-1)"));
    DeductionsTable->setItem(2, 3, TableItem("0"));
    DeductionsTable->setItem(2, 4, TableItem("0"));
    DeductionsTable->setItem(3, 0, TableItem("Consecutive uppercase letters"));
    DeductionsTable->setItem(3, 1, TableItem("Flat"));
    DeductionsTable->setItem(3, 2, TableItem("-(n*2)"));
    DeductionsTable->setItem(3, 3, TableItem("0"));
    DeductionsTable->setItem(3, 4, TableItem("0"));
    DeductionsTable->setItem(4, 0, TableItem("Consecutive lowercase letters"));
    DeductionsTable->setItem(4, 1, TableItem("Flat"));
    DeductionsTable->setItem(4, 2, TableItem("-(n*2)"));
    DeductionsTable->setItem(4, 3, TableItem("0"));
    DeductionsTable->setItem(4, 4, TableItem("0"));
    DeductionsTable->setItem(5, 0, TableItem("Consecutive numbers"));
    DeductionsTable->setItem(5, 1, TableItem("Flat"));
    DeductionsTable->setItem(5, 2, TableItem("-(n*2)"));
    DeductionsTable->setItem(5, 3, TableItem("0"));
    DeductionsTable->setItem(5, 4, TableItem("0"));
    DeductionsTable->setItem(6, 0, TableItem("Sequential letters (3+)"));
    DeductionsTable->setItem(6, 1, TableItem("Flat"));
    DeductionsTable->setItem(6, 2, TableItem("-(n*3)"));
    DeductionsTable->setItem(6, 3, TableItem("0"));
    DeductionsTable->setItem(6, 4, TableItem("0"));
    DeductionsTable->setItem(7, 0, TableItem("Sequential numbers (3+)"));
    DeductionsTable->setItem(7, 1, TableItem("Flat"));
    DeductionsTable->setItem(7, 2, TableItem("-(n*3)"));
    DeductionsTable->setItem(7, 3, TableItem("0"));
    DeductionsTable->setItem(7, 4, TableItem("0"));
    DeductionsTable->setItem(8, 0, TableItem("Sequential symbols (3+)"));
    DeductionsTable->setItem(8, 1, TableItem("Flat"));
    DeductionsTable->setItem(8, 2, TableItem("-(n*3)"));
    DeductionsTable->setItem(8, 3, TableItem("0"));
    DeductionsTable->setItem(8, 4, TableItem("0"));

    for(int i = 0; i < AdditionsTable->rowCount(); i++){
        setRowBackgrounColor(AdditionsTable,i, redColor);
    }
    for(int i = 0; i < DeductionsTable->rowCount(); i++){
        setRowBackgrounColor(DeductionsTable,i, greenColor);
    }
}

void MainWindow::RandomPasswordButtonClicked(){
    QLineEdit* passwordInput = ui->passwordInput;
    int passwordLength = ui->passwordLengthSlider->value();
    string RandomPassword = PasswordGenerator::GetInstance()->GenerateRandomPassword(passwordLength);
    passwordInput->setText(QString::fromStdString(RandomPassword));
}

void MainWindow::PasswordInputTextChanged(const QString& changedValue){
    PasswordStrengthValues strengthValues = PasswordGenerator::GetInstance()->calculatePasswordStrength(changedValue.toStdString());
    placeStrengthValuesToTables(strengthValues);
    int passwordTotalScore = PasswordGenerator::GetInstance()->getPasswordScore(strengthValues);
    setPasswordStrengthDisplay(passwordTotalScore);
}

void MainWindow::RandomPasswordLengthChanged(const int& changedValue){
    ui->passwordLengthText->setText(QString::fromStdString(to_string(changedValue)));
}

void MainWindow::placeStrengthValuesToTables(PasswordStrengthValues strengthValues){
    QTableWidget* AdditionsTable = ui->passwordStrengthAdditionsTable;
    QTableWidget* DeductionsTable = ui->passwordStrengthDeductionsTable;

    AdditionsTable->setItem(0, 3, TableItem(to_string(strengthValues.numberOfCharacters.Count)));
    AdditionsTable->setItem(0, 4, TableItem(to_string(strengthValues.numberOfCharacters.Score)));
    AdditionsTable->setItem(1, 3, TableItem(to_string(strengthValues.upperCaseLetters.Count)));
    AdditionsTable->setItem(1, 4, TableItem(to_string(strengthValues.upperCaseLetters.Score)));
    AdditionsTable->setItem(2, 3, TableItem(to_string(strengthValues.lowerCaseLetters.Count)));
    AdditionsTable->setItem(2, 4, TableItem(to_string(strengthValues.lowerCaseLetters.Score)));
    AdditionsTable->setItem(3, 3, TableItem(to_string(strengthValues.numbers.Count)));
    AdditionsTable->setItem(3, 4, TableItem(to_string(strengthValues.numbers.Score)));
    AdditionsTable->setItem(4, 3, TableItem(to_string(strengthValues.symbols.Count)));
    AdditionsTable->setItem(4, 4, TableItem(to_string(strengthValues.symbols.Score)));
    AdditionsTable->setItem(5, 3, TableItem(to_string(strengthValues.middleNumbersOrSymbols.Count)));
    AdditionsTable->setItem(5, 4, TableItem(to_string(strengthValues.middleNumbersOrSymbols.Score)));
    AdditionsTable->setItem(6, 3, TableItem(to_string(strengthValues.minimumRequirements.Count)));
    AdditionsTable->setItem(6, 4, TableItem(to_string(strengthValues.minimumRequirements.Score)));

    DeductionsTable->setItem(0, 3, TableItem(to_string(strengthValues.lettersOnly.Count)));
    DeductionsTable->setItem(0, 4, TableItem(to_string(strengthValues.lettersOnly.Score)));
    DeductionsTable->setItem(1, 3, TableItem(to_string(strengthValues.numbersOnly.Count)));
    DeductionsTable->setItem(1, 4, TableItem(to_string(strengthValues.numbersOnly.Score)));
    DeductionsTable->setItem(2, 3, TableItem(to_string(strengthValues.repeatCharacters.Count)));
    DeductionsTable->setItem(2, 4, TableItem(to_string(strengthValues.repeatCharacters.Score)));
    DeductionsTable->setItem(3, 3, TableItem(to_string(strengthValues.consecutiveUppercaseLetters.Count)));
    DeductionsTable->setItem(3, 4, TableItem(to_string(strengthValues.consecutiveUppercaseLetters.Score)));
    DeductionsTable->setItem(4, 3, TableItem(to_string(strengthValues.consecutiveLowercaseLetters.Count)));
    DeductionsTable->setItem(4, 4, TableItem(to_string(strengthValues.consecutiveLowercaseLetters.Score)));
    DeductionsTable->setItem(5, 3, TableItem(to_string(strengthValues.consecutiveNumbers.Count)));
    DeductionsTable->setItem(5, 4, TableItem(to_string(strengthValues.consecutiveNumbers.Score)));
    DeductionsTable->setItem(6, 3, TableItem(to_string(strengthValues.sequentialLetters.Count)));
    DeductionsTable->setItem(6, 4, TableItem(to_string(strengthValues.sequentialLetters.Score)));
    DeductionsTable->setItem(7, 3, TableItem(to_string(strengthValues.sequentialNumbers.Count)));
    DeductionsTable->setItem(7, 4, TableItem(to_string(strengthValues.sequentialNumbers.Score)));
    DeductionsTable->setItem(8, 3, TableItem(to_string(strengthValues.sequentialSymbols.Count)));
    DeductionsTable->setItem(8, 4, TableItem(to_string(strengthValues.sequentialSymbols.Score)));

    placeTableBackgroundColor(strengthValues);
}

void MainWindow::placeTableBackgroundColor(PasswordStrengthValues strengthValues){
    QTableWidget* AdditionsTable = ui->passwordStrengthAdditionsTable;
    QTableWidget* DeductionsTable = ui->passwordStrengthDeductionsTable;

    if(strengthValues.numberOfCharacters.Score > 32){
        setRowBackgrounColor(AdditionsTable, 0, blueColor);
    }
    else if(strengthValues.numberOfCharacters.Score > 30){
        setRowBackgrounColor(AdditionsTable, 0, greenColor);
    }
    else{
        setRowBackgrounColor(AdditionsTable, 0, redColor);
    }

    if(strengthValues.upperCaseLetters.Count > 1){
        setRowBackgrounColor(AdditionsTable, 1, blueColor);
    }
    else if(strengthValues.numberOfCharacters.Score > 0){
        setRowBackgrounColor(AdditionsTable, 1, greenColor);
    }
    else{
        setRowBackgrounColor(AdditionsTable, 1, redColor);
    }

    if(strengthValues.lowerCaseLetters.Count > 1){
        setRowBackgrounColor(AdditionsTable, 2, blueColor);
    }
    else if(strengthValues.numberOfCharacters.Score > 0){
        setRowBackgrounColor(AdditionsTable, 2, greenColor);
    }
    else{
        setRowBackgrounColor(AdditionsTable, 2, redColor);
    }

    if(strengthValues.numbers.Count > 1){
        setRowBackgrounColor(AdditionsTable, 3, blueColor);
    }
    else if(strengthValues.numberOfCharacters.Score > 0){
        setRowBackgrounColor(AdditionsTable, 3, greenColor);
    }
    else{
        setRowBackgrounColor(AdditionsTable, 3, redColor);
    }

    if(strengthValues.symbols.Count > 1){
        setRowBackgrounColor(AdditionsTable, 4, blueColor);
    }
    else if(strengthValues.numberOfCharacters.Score > 0){
        setRowBackgrounColor(AdditionsTable, 4, greenColor);
    }
    else{
        setRowBackgrounColor(AdditionsTable, 4, redColor);
    }

    if(strengthValues.middleNumbersOrSymbols.Count > 1){
        setRowBackgrounColor(AdditionsTable, 5, blueColor);
    }
    else if(strengthValues.numberOfCharacters.Score > 0){
        setRowBackgrounColor(AdditionsTable, 5, greenColor);
    }
    else{
        setRowBackgrounColor(AdditionsTable, 5, redColor);
    }

    if(strengthValues.minimumRequirements.Score > 8){
        setRowBackgrounColor(AdditionsTable, 6, blueColor);
    }
    else if(strengthValues.minimumRequirements.Score == 8){
        setRowBackgrounColor(AdditionsTable, 6, greenColor);
    }
    else{
        setRowBackgrounColor(AdditionsTable, 6, redColor);
    }

    if(strengthValues.lettersOnly.Score < 0){
        setRowBackgrounColor(DeductionsTable, 0, yellowColor);
    }
    else{
        setRowBackgrounColor(DeductionsTable, 0, greenColor);
    }

    if(strengthValues.numbersOnly.Score < 0){
        setRowBackgrounColor(DeductionsTable, 1, yellowColor);
    }
    else{
        setRowBackgrounColor(DeductionsTable, 1, greenColor);
    }

    if(strengthValues.repeatCharacters.Score < 0){
        setRowBackgrounColor(DeductionsTable, 2, yellowColor);
    }
    else{
        setRowBackgrounColor(DeductionsTable, 2, greenColor);
    }

    if(strengthValues.consecutiveUppercaseLetters.Score < 0){
        setRowBackgrounColor(DeductionsTable, 3, yellowColor);
    }
    else{
        setRowBackgrounColor(DeductionsTable, 3, greenColor);
    }

    if(strengthValues.consecutiveLowercaseLetters.Score < 0){
        setRowBackgrounColor(DeductionsTable, 4, yellowColor);
    }
    else{
        setRowBackgrounColor(DeductionsTable, 4, greenColor);
    }

    if(strengthValues.consecutiveNumbers.Score < 0){
        setRowBackgrounColor(DeductionsTable, 5, yellowColor);
    }
    else{
        setRowBackgrounColor(DeductionsTable, 5, greenColor);
    }

    if(strengthValues.sequentialLetters.Score < 0){
        setRowBackgrounColor(DeductionsTable, 6, yellowColor);
    }
    else{
        setRowBackgrounColor(DeductionsTable, 6, greenColor);
    }

    if(strengthValues.sequentialNumbers.Score < 0){
        setRowBackgrounColor(DeductionsTable, 7, yellowColor);
    }
    else{
        setRowBackgrounColor(DeductionsTable, 7, greenColor);
    }

    if(strengthValues.sequentialSymbols.Score < 0){
        setRowBackgrounColor(DeductionsTable, 8, yellowColor);
    }
    else{
        setRowBackgrounColor(DeductionsTable, 8, greenColor);
    }
}

void MainWindow::setPasswordStrengthDisplay(int score){
    QProgressBar* strengthBar = ui->passwordStrengthPercentage;
    QLabel* strengthScoreText = ui->passwordStrengthScoreText;
    QLabel* strengthText = ui->passwordStrengthText;

    strengthScoreText->setText(QString::fromStdString(to_string(score)));
    if(score > 100){
        strengthBar->setValue(100);
    }
    else if(score < 0){
        strengthBar->setValue(0);
    }
    else{
        strengthBar->setValue(score);
    }

    if(score <= 25){
        strengthText->setText(QString::fromStdString("Weak"));
    }else if(score > 25 && score <= 50){
        strengthText->setText(QString::fromStdString("Average"));
    }else if(score > 50 && score <= 75){
        strengthText->setText(QString::fromStdString("Strong"));
    }else{
        strengthText->setText(QString::fromStdString("Very Strong"));
    }
}

void MainWindow::setRowBackgrounColor(QTableWidget* table, int row, QColor color){
    for (int i = 0; i < table->columnCount(); i++) {
        table->item(row, i)->setBackground(color);
    }
}

void MainWindow::OpenSettingsWindow(){
    SettingsWindow* settingsWindow = new SettingsWindow(this);
    settingsWindow->setWindowModality(Qt::ApplicationModal);
    settingsWindow->show();
}
