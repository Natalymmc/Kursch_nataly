#ifndef INCOMECATEGORY_H
#define INCOMECATEGORY_H

#include "FinancialCategory.h"

class IncomeCategory : public FinancialCategory {
public:
    IncomeCategory(const QString &name, double amount = 0.0);

    void increaseIncome(double amount); // Увеличение дохода
    QString categoryType() const;       // Тип категории (доход)
};

// Подкатегории для доходов
class MainIncomeCategory : public IncomeCategory {
public:
    MainIncomeCategory(const QString &name = "Основной доход", double amount = 0.0)
        : IncomeCategory(name, amount) {}
};

class AdditionalIncomeCategory : public IncomeCategory {
public:
    AdditionalIncomeCategory(const QString &name = "Дополнительный доход", double amount = 0.0)
        : IncomeCategory(name, amount) {}
};


// Определения методов класса
IncomeCategory::IncomeCategory(const QString &name, double amount)
    : FinancialCategory(name, amount) {}

void IncomeCategory::increaseIncome(double amount) {
    addAmount(amount); // Используем метод из базового класса
}

QString IncomeCategory::categoryType() const {
    return "Income"; // Возвращает строку, указывающую на тип категории
}

#endif // INCOMECATEGORY_H
