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
#include <QMessageBox>
#include "ieee32bitconverter.h"
#include "serialterminal.h"
#include "settingsdialog.h"


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
    void on_addSubBtn_clicked();
    void on_mulDivBtn_clicked();
    void on_powBtn_clicked();
    void on_sqrtBtn_clicked();
    void on_inverseBtn_clicked();
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
    void on_clearAdd_clicked();
    void on_clearSub_clicked();
    void on_clearMul_clicked();
    void on_clearDiv_clicked();
    void on_clearPow2_clicked();
    void on_clearPown_clicked();
    void on_clearSqrt_clicked();
    void on_clearInverse_clicked();
    void on_sendAdd_clicked();
    void on_settingsBtn_clicked();
    void receiveData(const QByteArray &data);
    QString labelsToString(QObject *labels, QString prefix);
    void fillResult(QString response);

    void on_sendSub_clicked();

    void on_sendMul_clicked();

    void on_sendDiv_clicked();

    void on_sendPow2_clicked();

    void on_sendSqrt_clicked();

    void on_sendInverse_clicked();

private:
    Ui::FPUCalculator *ui;
    QByteArray receivedResult;
    SerialTerminal *term;
};

#endif // FPUCALCULATOR_H
