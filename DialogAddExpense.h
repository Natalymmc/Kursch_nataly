#ifndef DIALOGADDEXPENSE_H
#define DIALOGADDEXPENSE_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include "FinancialManager.h"

class DialogAddExpense : public QDialog {
    Q_OBJECT

public:
    DialogAddExpense(FinancialManager *financialManager, const QString &userID, QWidget *parent = nullptr)
        : QDialog(parent), financialManager(financialManager), userID(userID) {
        setWindowTitle("Добавить расход");

        amountEdit = new QLineEdit(this);
        dateEdit = new QLineEdit(this);
        categoryEdit = new QLineEdit(this);

        QPushButton *addButton = new QPushButton("Добавить", this);
        connect(addButton, &QPushButton::clicked, this, &DialogAddExpense::onAddExpense);

        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(amountEdit);
        layout->addWidget(dateEdit);
        layout->addWidget(categoryEdit);
        layout->addWidget(addButton);
    }

private slots:
    void onAddExpense() {
        double amount = amountEdit->text().toDouble();
        QString date = dateEdit->text();
        QString category = categoryEdit->text();

        // Предполагается, что FinancialManager имеет метод для добавления расхода
        if (financialManager->addExpense(userID, amount, date, category)) {
            accept();
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось добавить расход.");
        }
    }

private:
    FinancialManager *financialManager;
    QString userID;
    QLineEdit *amountEdit;
    QLineEdit *dateEdit;
    QLineEdit *categoryEdit;
};

#endif // DIALOGADDEXPENSE_H

