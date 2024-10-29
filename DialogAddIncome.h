#ifndef DIALOGADDINCOME_H
#define DIALOGADDINCOME_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include "FinancialManager.h"

class DialogAddIncome : public QDialog {
    Q_OBJECT

public:
    DialogAddIncome(FinancialManager *financialManager, const QString &userID, QWidget *parent = nullptr)
        : QDialog(parent), financialManager(financialManager), userID(userID) {
        setWindowTitle("Добавить доход");

        amountEdit = new QLineEdit(this);
        dateEdit = new QLineEdit(this);
        sourceEdit = new QLineEdit(this); // Новое поле для source


        QPushButton *addButton = new QPushButton("Добавить", this);
        connect(addButton, &QPushButton::clicked, this, &DialogAddIncome::onAddIncome);

        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(amountEdit);
        layout->addWidget(dateEdit);
        layout->addWidget(sourceEdit); // Добавляем в layout
        layout->addWidget(addButton);
    }

private slots:
    void onAddIncome() {
        double amount = amountEdit->text().toDouble();
        QString date = dateEdit->text();
        QString source = sourceEdit->text(); // Получаем значение source


        // Предполагается, что FinancialManager имеет метод для добавления дохода
        if (financialManager->addIncome(userID, amount, date, source)) {
            accept();
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось добавить доход.");
        }
    }

private:
    FinancialManager *financialManager;
    QString userID;
    QLineEdit *amountEdit;
    QLineEdit *dateEdit;
    QLineEdit *sourceEdit; // Поле для ввода source
};

#endif // DIALOGADDINCOME_H

