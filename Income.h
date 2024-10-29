#ifndef INCOME_H
#define INCOME_H

#include <QString>

// Класс для представления дохода
class Income {
public:
    Income() : amount(0), date(""), source("") {} // Конструктор по умолчанию
    Income(double amount, const QString &date, const QString &source)
        : amount(amount), date(date), source(source) {}

    double getAmount() const { return amount; }
    QString getDate() const { return date; }
    QString getSource() const { return source; }

private:
    double amount;
    QString date;
    QString source;
};

#endif // INCOME_H

