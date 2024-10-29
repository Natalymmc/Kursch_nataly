#ifndef USER_H
#define USER_H

#include <QString>
#include <vector>
#include "Income.h"
#include "Expense.h"

class User {
public:
    User(const QString &name, const QString &surname, int age, const QString &userID);

    QString getName() const;
    QString getSurname() const;
    int getAge() const;
    QString getUserID() const;

    void setName(const QString &name);
    void setSurname(const QString &surname);
    void setAge(int age);

    void addIncome(const Income &income);
    void addExpense(const Expense &expense);

    const std::vector<Income>& getIncomes() const;
    const std::vector<Expense>& getExpenses() const;

private:
    QString name;
    QString surname;
    int age;
    QString userID;
    std::vector<Income> incomes;
    std::vector<Expense> expenses;
};

#endif // USER_H


