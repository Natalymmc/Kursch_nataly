#ifndef DIALOGUPDATEUSER_H
#define DIALOGUPDATEUSER_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include "FinancialManager.h"

class DialogUpdateUser : public QDialog {
    Q_OBJECT

public:
    DialogUpdateUser(FinancialManager *financialManager, QWidget *parent = nullptr)
        : QDialog(parent), financialManager(financialManager) {
        setWindowTitle("Обновить пользователя");

        userIDEdit = new QLineEdit(this);
        nameEdit = new QLineEdit(this);
        surnameEdit = new QLineEdit(this);
        ageEdit = new QLineEdit(this);

        QPushButton *updateButton = new QPushButton("Обновить", this);
        connect(updateButton, &QPushButton::clicked, this, &DialogUpdateUser::onUpdateUser);

        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(userIDEdit);
        layout->addWidget(nameEdit);
        layout->addWidget(surnameEdit);
        layout->addWidget(ageEdit);
        layout->addWidget(updateButton);
    }

private slots:
    void onUpdateUser() {
        QString userID = userIDEdit->text();
        QString name = nameEdit->text();
        QString surname = surnameEdit->text();
        int age = ageEdit->text().toInt();

        // Предполагается, что FinancialManager имеет метод для обновления пользователя
        if (financialManager->updateUser(userID, name, surname, age)) {
            accept();
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось обновить информацию о пользователе.");
        }
    }

private:
    FinancialManager *financialManager;
    QLineEdit *userIDEdit;
    QLineEdit *nameEdit;
    QLineEdit *surnameEdit;
    QLineEdit *ageEdit;
};

#endif // DIALOGUPDATEUSER_H

