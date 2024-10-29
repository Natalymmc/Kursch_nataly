#include "MainWindow.h"
#include "DialogAddUser.h"
#include "DialogUpdateUser.h"
#include "DialogAddIncome.h"
#include "DialogAddExpense.h"
#include "DialogStatistics.h"
#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QInputDialog>



MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), financialManager(new FinancialManager()) {
    setupMenu();
    setupButtons();
}

MainWindow::~MainWindow() {
    delete financialManager;
}

void MainWindow::setupMenu() {
    QMenu *fileMenu = menuBar()->addMenu("Файл");
    fileMenu->addAction("Открыть", this, &MainWindow::openUserProfile);
    fileMenu->addAction("Сохранить", this, &MainWindow::saveUserProfile);
    fileMenu->addSeparator();
    fileMenu->addAction("Выход", this, &QWidget::close);

    QMenu *userMenu = menuBar()->addMenu("Пользователь");
    userMenu->addAction("Добавить пользователя", this, &MainWindow::addUser);
    userMenu->addAction("Обновить информацию", this, &MainWindow::updateUser);

    QMenu *financeMenu = menuBar()->addMenu("Финансы");
    financeMenu->addAction("Добавить доход", this, &MainWindow::addIncome);
    financeMenu->addAction("Добавить расход", this, &MainWindow::addExpense);
    financeMenu->addAction("Просмотр статистики", this, &MainWindow::showStatistics);

    fileMenu->addAction("Отменить последнее действие", this, &MainWindow::undoLastAction);
}

void MainWindow::setupButtons() {
    // Можно добавить кнопки на главном окне для быстрого доступа к основным функциям
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    QPushButton *addUserButton = new QPushButton("Добавить пользователя", this);
    QPushButton *updateUserButton = new QPushButton("Обновить пользователя", this);
    QPushButton *addIncomeButton = new QPushButton("Добавить доход", this);
    QPushButton *addExpenseButton = new QPushButton("Добавить расход", this);
    QPushButton *viewStatsButton = new QPushButton("Просмотр статистики", this);
    QPushButton *undoButton = new QPushButton("Отменить последнее действие", this);

    layout->addWidget(addUserButton);
    layout->addWidget(updateUserButton);
    layout->addWidget(addIncomeButton);
    layout->addWidget(addExpenseButton);
    layout->addWidget(viewStatsButton);
    layout->addWidget(undoButton);

    setCentralWidget(centralWidget);

    // Соединяем кнопки с соответствующими слотами
    connect(addUserButton, &QPushButton::clicked, this, &MainWindow::addUser);
    connect(updateUserButton, &QPushButton::clicked, this, &MainWindow::updateUser);
    connect(addIncomeButton, &QPushButton::clicked, this, &MainWindow::addIncome);
    connect(addExpenseButton, &QPushButton::clicked, this, &MainWindow::addExpense);
    connect(viewStatsButton, &QPushButton::clicked, this, &MainWindow::showStatistics);
    connect(undoButton, &QPushButton::clicked, this, &MainWindow::undoLastAction);
}

void MainWindow::openUserProfile() {
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть профиль пользователя", "", "Data Files (*.dat)");
    if (!fileName.isEmpty() && financialManager->loadFromFile(fileName)) {
        QMessageBox::information(this, "Открыть", "Профиль пользователя загружен.");
    } else {
        QMessageBox::warning(this, "Ошибка", "Не удалось загрузить профиль.");
    }
}

void MainWindow::saveUserProfile() {
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить профиль пользователя", "", "Data Files (*.dat)");
    if (!fileName.isEmpty() && financialManager->saveToFile(fileName)) {
        QMessageBox::information(this, "Сохранение", "Данные сохранены.");
    } else {
        QMessageBox::warning(this, "Ошибка", "Не удалось сохранить данные.");
    }
}

void MainWindow::addUser() {
    DialogAddUser dialog(financialManager, this);
    if (dialog.exec() == QDialog::Accepted) {
        QMessageBox::information(this, "Добавление", "Пользователь успешно добавлен.");
    }
}

void MainWindow::updateUser() {
    DialogUpdateUser dialog(financialManager, this);
    if (dialog.exec() == QDialog::Accepted) {
        QMessageBox::information(this, "Обновление", "Информация о пользователе успешно обновлена.");
    }
}

void MainWindow::addIncome() {
    QString userID = QInputDialog::getText(this, "Добавить доход", "Введите ID пользователя:");
    User* user = financialManager->findUserByID(userID);

    if (user) {
        DialogAddIncome dialog(financialManager, userID, this);
        dialog.exec();
    } else {
        QMessageBox::warning(this, "Ошибка", "Пользователь с таким ID не найден.");
    }
}

void MainWindow::addExpense() {
    QString userID = QInputDialog::getText(this, "Добавить расход", "Введите ID пользователя:");
    User* user = financialManager->findUserByID(userID);

    if (user) {
        DialogAddExpense dialog(financialManager, userID, this);
        dialog.exec();
    } else {
        QMessageBox::warning(this, "Ошибка", "Пользователь с таким ID не найден.");
    }
}

void MainWindow::showStatistics() {
    DialogStatistics dialog(financialManager, this);
    dialog.exec();
}

void MainWindow::undoLastAction() {
    financialManager->undoLastAction();
    QMessageBox::information(this, "Отмена", "Последнее действие отменено.");
}

