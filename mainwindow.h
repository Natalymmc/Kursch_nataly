#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "FinancialManager.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openUserProfile();      // Открыть профиль пользователя из файла
    void saveUserProfile();      // Сохранить профиль пользователя в файл
    void addUser();              // Добавить пользователя
    void updateUser();           // Обновить информацию о пользователе
    void addIncome();            // Добавить доход
    void addExpense();           // Добавить расход
    void showStatistics();       // Просмотр статистики
    void undoLastAction();       // Отменить последнее действие

private:
    FinancialManager *financialManager;
    void setupMenu();            // Настройка меню
    void setupButtons();         // Настройка кнопок на главном окне (если нужны дополнительные)
};

#endif // MAINWINDOW_H
