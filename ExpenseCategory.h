#ifndef EXPENSECATEGORY_H
#define EXPENSECATEGORY_H

#include "FinancialCategory.h"

class ExpenseCategory : public FinancialCategory {
public:
    ExpenseCategory(const QString &name, double amount = 0.0);

    void increaseExpense(double amount); // Увеличение расходов
    QString categoryType() const;        // Тип категории (расход)
};

// Подкатегории для расходов
class MandatoryExpenseCategory : public ExpenseCategory {
public:
    MandatoryExpenseCategory(const QString &name = "Обязательные расходы", double amount = 0.0)
        : ExpenseCategory(name, amount) {}
};

class BasicExpenseCategory : public ExpenseCategory {
public:
    BasicExpenseCategory(const QString &name = "Основные расходы", double amount = 0.0)
        : ExpenseCategory(name, amount) {}
};

// Определения методов класса
ExpenseCategory::ExpenseCategory(const QString &name, double amount)
    : FinancialCategory(name, amount) {}

void ExpenseCategory::increaseExpense(double amount) {
    addAmount(amount); // Используем метод из базового класса
}

QString ExpenseCategory::categoryType() const {
    return "Expense"; // Возвращает строку, указывающую на тип категории
}

#endif // EXPENSECATEGORY_H


