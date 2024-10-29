#ifndef FINANCIALMANAGER_H
#define FINANCIALMANAGER_H

#include <vector>
#include <stack>
#include <QString>
#include "User.h"

// Перечисление для типов действий
enum class ActionType {
    AddUser,
    AddIncome,
    AddExpense,
};
// Класс для представления действия
class Action {
public:
    Action(ActionType type, const QString &userID, const Income &income = Income(), const Expense &expense = Expense())
        : type(type), userID(userID), incomeData(income), expenseData(expense) {}

    ActionType type;
    QString userID;
    Income incomeData;  // Данные дохода (при необходимости)
    Expense expenseData; // Данные расхода (при необходимости)
};


class FinancialManager {
public:
    bool addUser(const QString &name, const QString &surname, int age, const QString &userID);
    bool updateUser(const QString &userID, const QString &name, const QString &surname, int age);
    bool addIncome(const QString &userID, double amount, const QString &date, const QString &source);
    bool addExpense(const QString &userID, double amount, const QString &date, const QString &category);

    User* findUserByID(const QString &userID);
    bool loadFromFile(const QString &fileName);
    bool saveToFile(const QString &fileName) const;

    double getTotalIncome() const;
    double getTotalExpense() const;
    QString getStatistics() const;

    void undoLastAction();  // Отмена последнего действия

private:

    std::vector<User> users;
    std::stack<Action> actionHistory; // Стек для истории действий
};

#endif // FINANCIALMANAGER_H
