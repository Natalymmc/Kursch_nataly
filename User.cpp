#include "User.h"

User::User(const QString &name, const QString &surname, int age, const QString &userID)
    : name(name), surname(surname), age(age), userID(userID) {}

QString User::getName() const { return name; }
QString User::getSurname() const { return surname; }
int User::getAge() const { return age; }
QString User::getUserID() const { return userID; }

void User::setName(const QString &name) { this->name = name; }
void User::setSurname(const QString &surname) { this->surname = surname; }
void User::setAge(int age) { this->age = age; }

void User::addIncome(const Income &income) {
    incomes.push_back(income);
}

void User::addExpense(const Expense &expense) {
    expenses.push_back(expense);
}

const std::vector<Income>& User::getIncomes() const { return incomes; }
const std::vector<Expense>& User::getExpenses() const { return expenses; }
