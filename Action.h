#ifndef ACTION_H
#define ACTION_H

#include "ActionType.h"
#include "Income.h"
#include "Expense.h"
#include <QString>

struct Action {
    ActionType type;          // Тип действия
    QString userID;           // Идентификатор пользователя
    Income incomeData;        // Данные о доходе (если действие — добавление дохода)
    Expense expenseData;      // Данные о расходе (если действие — добавление расхода)

    Action(ActionType t, const QString &id, const Income &inc = {}, const Expense &exp = {})
        : type(t), userID(id), incomeData(inc), expenseData(exp) {}
};

#endif // ACTION_H

