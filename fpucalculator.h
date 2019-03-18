#ifndef FPUCALCULATOR_H
#define FPUCALCULATOR_H

#include <QMainWindow>
#include <QTabBar>

namespace Ui {
class FPUCalculator;
}

class FPUCalculator : public QMainWindow
{
    Q_OBJECT

public:
    explicit FPUCalculator(QWidget *parent = nullptr);
    ~FPUCalculator();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();

private:
    Ui::FPUCalculator *ui;
};

#endif // FPUCALCULATOR_H
