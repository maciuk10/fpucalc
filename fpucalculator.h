#ifndef FPUCALCULATOR_H
#define FPUCALCULATOR_H

#include <QMainWindow>
#include <QTabBar>
#include <QSignalMapper>
#include <QList>
#include <QDebug>
#include <QGroupBox>
#include <QRegExp>
#include <QRegExpValidator>
#include <QBitArray>
#include "ieee32bitconverter.h"


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
    void on_add1Number_textChanged(const QString &arg1);
    void insertIEEENumberToLabels(QObject *labels, QString number, QString prefix);
    void prepareLineEdits(QWidget *parent);

    void on_add2Number_textChanged(const QString &arg1);
    void on_sub1Number_textChanged(const QString &arg1);
    void on_sub2Number_textChanged(const QString &arg1);

    void on_mul1Number_textChanged(const QString &arg1);

    void on_mul2Number_textChanged(const QString &arg1);

    void on_div1Number_textChanged(const QString &arg1);

    void on_div2Number_textChanged(const QString &arg1);

    void on_pow21Number_textChanged(const QString &arg1);

    void on_pown1Number_textChanged(const QString &arg1);

    void on_sqrt1Number_textChanged(const QString &arg1);

    void on_reverse1Number_textChanged(const QString &arg1);

private:
    Ui::FPUCalculator *ui;
};

#endif // FPUCALCULATOR_H
