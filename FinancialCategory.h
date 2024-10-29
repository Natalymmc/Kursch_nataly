#ifndef FINANCIALCATEGORY_H
#define FINANCIALCATEGORY_H

#include <QString>

class FinancialCategory {
public:
    FinancialCategory(const QString &name, double amount = 0.0);

    QString getName() const;
    double getAmount() const;
    void setAmount(double amount);
    void addAmount(double amount);

protected:
    QString name;
    double amount;
};

// Определения методов класса
FinancialCategory::FinancialCategory(const QString &name, double amount)
    : name(name), amount(amount) {}

QString FinancialCategory::getName() const {
    return name;
}

double FinancialCategory::getAmount() const {
    return amount;
}

void FinancialCategory::setAmount(double amount) {
    this->amount = amount;
}

void FinancialCategory::addAmount(double amount) {
    this->amount += amount;
}

#endif // FINANCIALCATEGORY_H


