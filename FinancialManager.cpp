#include "FinancialManager.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

bool FinancialManager::addUser(const QString &name, const QString &surname, int age, const QString &userID) {
    // Проверяем, существует ли уже пользователь с таким ID
    for (const auto &user : users) {
        if (user.getUserID() == userID) {
            return false; // Пользователь с таким ID уже существует
        }
    }
    // Если ID уникален, создаем нового пользователя и добавляем его в список
    users.emplace_back(name, surname, age, userID);
    return true;
}

bool FinancialManager::updateUser(const QString &userID, const QString &name, const QString &surname, int age) {
    User* user = findUserByID(userID);
    if (user) {
        user->setName(name);
        user->setSurname(surname);
        user->setAge(age);
        return true; // Успешно обновлено
    }
    return false; // Пользователь не найден
}

QString FinancialManager::getStatistics() const {
    QString stats;
    for (const User &user : users) {
        stats += QString("ID: %1, Name: %2 %3, Age: %4\n")
        .arg(user.getUserID())
            .arg(user.getName())
            .arg(user.getSurname())
            .arg(user.getAge());

        double totalIncome = 0.0;
        double totalExpense = 0.0;

        for (const Income &income : user.getIncomes()) {
            totalIncome += income.getAmount();
        }

        for (const Expense &expense : user.getExpenses()) {
            totalExpense += expense.getAmount();
        }

        stats += QString("Total Income: %1, Total Expense: %2, Remaining Funds: %3\n\n")
                     .arg(totalIncome)
                     .arg(totalExpense)
                     .arg(totalIncome - totalExpense);
    }
    return stats.isEmpty() ? QString("Нет данных для отображения.") : stats;
}

bool FinancialManager::addIncome(const QString &userID, double amount, const QString &date, const QString &source) {
    for (auto &user : users) {
        if (user.getUserID() == userID) {
            Income income(amount, date, source);
            user.addIncome(income);
            return true;
        }
    }
    return false; // Пользователь с указанным ID не найден
}

#include "FinancialManager.h"

bool FinancialManager::addExpense(const QString &userID, double amount, const QString &date, const QString &category) {
    for (auto &user : users) {
        if (user.getUserID() == userID) {
            Expense expense(amount, date, category);
            user.addExpense(expense);
            return true;
        }
    }
    return false; // Пользователь с указанным ID не найден
}


User* FinancialManager::findUserByID(const QString &userID) {
    auto it = std::find_if(users.begin(), users.end(), [&userID](const User &user) {
        return user.getUserID() == userID;
    });
    return it != users.end() ? &(*it) : nullptr; // Вернуть указатель на найденного пользователя или nullptr
}

bool FinancialManager::loadFromFile(const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Ошибка", "Не удалось открыть файл для чтения.");
        return false;
    }

    QTextStream in(&file);
    users.clear();  // Очищаем текущий список пользователей

    while (!in.atEnd()) {
        QString name = in.readLine();
        QString surname = in.readLine();
        int age = in.readLine().toInt();
        QString userID = in.readLine();

        User user(name, surname, age, userID);

        // Загрузка доходов пользователя
        int incomeCount = in.readLine().toInt();
        for (int i = 0; i < incomeCount; ++i) {
            double amount = in.readLine().toDouble();
            QString date = in.readLine();
            QString source = in.readLine();
            user.addIncome(Income(amount, date, source));
        }

        // Загрузка расходов пользователя
        int expenseCount = in.readLine().toInt();
        for (int i = 0; i < expenseCount; ++i) {
            double amount = in.readLine().toDouble();
            QString date = in.readLine();
            QString category = in.readLine();
            user.addExpense(Expense(amount, date, category));
        }

        users.push_back(user);  // Добавляем пользователя в список
    }

    file.close();
    return true;
}

bool FinancialManager::saveToFile(const QString &fileName) const {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Ошибка", "Не удалось открыть файл для записи.");
        return false;
    }

    QTextStream out(&file);

    for (const auto &user : users) {
        out << user.getName() << "\n"
            << user.getSurname() << "\n"
            << user.getAge() << "\n"
            << user.getUserID() << "\n";

        // Сохранение доходов пользователя
        const auto &incomes = user.getIncomes();
        out << incomes.size() << "\n";
        for (const auto &income : incomes) {
            out << income.getAmount() << "\n"
                << income.getDate() << "\n"
                << income.getSource() << "\n";
        }

        // Сохранение расходов пользователя
        const auto &expenses = user.getExpenses();
        out << expenses.size() << "\n";
        for (const auto &expense : expenses) {
            out << expense.getAmount() << "\n"
                << expense.getDate() << "\n"
                << expense.getCategory() << "\n";
        }
    }

    file.close();
    return true;
}

double FinancialManager::getTotalIncome() const {
    double totalIncome = 0.0;
    for (const auto &user : users) {
        for (const auto &income : user.getIncomes()) {
            totalIncome += income.getAmount();
        }
    }
    return totalIncome;
}

double FinancialManager::getTotalExpense() const {
    double totalExpense = 0.0;
    for (const auto &user : users) {
        for (const auto &expense : user.getExpenses()) {
            totalExpense += expense.getAmount();
        }
    }
    return totalExpense;
}

void FinancialManager::undoLastAction() {
    if (actionHistory.empty()) {
        QMessageBox::information(nullptr, "Отмена", "Нет действий для отмены.");
        return;
    }

    Action lastAction = actionHistory.top();
    actionHistory.pop();

    switch (lastAction.type) {
    case ActionType::AddUser:
        // Удаляем последнего добавленного пользователя
        if (!users.empty() && users.back().getUserID() == lastAction.userID) {
            users.pop_back();
        }
        break;

    case ActionType::AddIncome: {
        // Отменяем добавление дохода
        User* user = findUserByID(lastAction.userID);
        if (user) {
            auto &incomes = const_cast<std::vector<Income>&>(user->getIncomes()); // Приведение к неконстантной ссылке
            if (!incomes.empty() && incomes.back().getAmount() == lastAction.incomeData.getAmount()) {
                incomes.pop_back();
            }
        }
        break;
    }

    case ActionType::AddExpense: {
        // Отменяем добавление расхода
        User* user = findUserByID(lastAction.userID);
        if (user) {
            auto &expenses = const_cast<std::vector<Expense>&>(user->getExpenses()); // Приведение к неконстантной ссылке
            if (!expenses.empty() && expenses.back().getAmount() == lastAction.expenseData.getAmount()) {
                expenses.pop_back();
            }
        }
        break;
    }
    }
}
