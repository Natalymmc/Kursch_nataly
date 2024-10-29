#ifndef DIALOGADDUSER_H
#define DIALOGADDUSER_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include "FinancialManager.h"

class DialogAddUser : public QDialog {
    Q_OBJECT

public:
    DialogAddUser(FinancialManager *financialManager, QWidget *parent = nullptr)
        : QDialog(parent), financialManager(financialManager) {
        setWindowTitle("Добавить пользователя");

        nameEdit = new QLineEdit(this);
        surnameEdit = new QLineEdit(this);
        ageEdit = new QLineEdit(this);
        userIDEdit = new QLineEdit(this);

        QPushButton *addButton = new QPushButton("Добавить", this);
        connect(addButton, &QPushButton::clicked, this, &DialogAddUser::onAddUser);

        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(nameEdit);
        layout->addWidget(surnameEdit);
        layout->addWidget(ageEdit);
        layout->addWidget(userIDEdit);
        layout->addWidget(addButton);
    }

private slots:
    void onAddUser() {
        QString name = nameEdit->text();
        QString surname = surnameEdit->text();
        int age = ageEdit->text().toInt();
        QString userID = userIDEdit->text();

        // Предполагается, что FinancialManager имеет метод для добавления пользователя
        if (financialManager->addUser(name, surname, age, userID)) {
            accept();
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось добавить пользователя.");
        }
    }

private:
    FinancialManager *financialManager;
    QLineEdit *nameEdit;
    QLineEdit *surnameEdit;
    QLineEdit *ageEdit;
    QLineEdit *userIDEdit;
};

#endif // DIALOGADDUSER_H
