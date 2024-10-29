#ifndef EXPENSE_H
#define EXPENSE_H

#include <QString>

class Expense {
public:
    // Конструктор по умолчанию
    Expense() : amount(0.0), date(""), category("") {}

    Expense(double amount, const QString &date, const QString &category)
        : amount(amount), date(date), category(category) {}

    double getAmount() const { return amount; }
    QString getDate() const { return date; }
    QString getCategory() const { return category; }

private:
    double amount;
    QString date;
    QString category;
};

#endif // EXPENSE_H


