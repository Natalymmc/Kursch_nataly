#ifndef DIALOGSTATISTICS_H
#define DIALOGSTATISTICS_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include "FinancialManager.h"

class DialogStatistics : public QDialog {
    Q_OBJECT

public:
    DialogStatistics(FinancialManager *financialManager, QWidget *parent = nullptr)
        : QDialog(parent), financialManager(financialManager) {
        setWindowTitle("Статистика");

        QVBoxLayout *layout = new QVBoxLayout(this);

        QLabel *statisticsLabel = new QLabel("Статистика пользователя:", this);
        layout->addWidget(statisticsLabel);

        QPushButton *viewButton = new QPushButton("Показать статистику", this);
        connect(viewButton, &QPushButton::clicked, this, &DialogStatistics::onViewStatistics);
        layout->addWidget(viewButton);

        setLayout(layout);
    }

private slots:
    void onViewStatistics() {
        QString statistics = financialManager->getStatistics(); // Предполагается, что есть метод для получения статистики
        if (!statistics.isEmpty()) {
            QMessageBox::information(this, "Статистика", statistics);
        } else {
            QMessageBox::warning(this, "Ошибка", "Нет данных для отображения статистики.");
        }
    }

private:
    FinancialManager *financialManager;
};

#endif // DIALOGSTATISTICS_H

