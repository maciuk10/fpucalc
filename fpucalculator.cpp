#include "fpucalculator.h"
#include "fpucalculator.h"
#include "ui_fpucalculator.h"

FPUCalculator::FPUCalculator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FPUCalculator) {
    ui->setupUi(this);
    ui->tabs->tabBar()->hide();
    ui->tabs->setAttribute(Qt::WA_TranslucentBackground);
    ui->tabs->setCurrentIndex(0);
    prepareLineEdits(ui->tabs);
}

FPUCalculator::~FPUCalculator() {
    delete ui;
}

void FPUCalculator::on_pushButton_clicked() {
    ui->tabs->setCurrentIndex(0);
}

void FPUCalculator::on_pushButton_2_clicked() {
    ui->tabs->setCurrentIndex(1);
}

void FPUCalculator::on_pushButton_3_clicked() {
    ui->tabs->setCurrentIndex(2);
}

void FPUCalculator::on_pushButton_4_clicked() {
    ui->tabs->setCurrentIndex(3);
}

void FPUCalculator::on_pushButton_5_clicked() {
    ui->tabs->setCurrentIndex(4);
}

void FPUCalculator::on_add1Number_textChanged(const QString &arg1) {
    IEEE32BitConverter *converter = new IEEE32BitConverter();
    qDebug() << arg1.toFloat();
    string converted = converter->convert(arg1.toFloat());
    qDebug() << QString::fromStdString(converted);
    insertIEEENumberToLabels(ui->add1Bits, QString::fromStdString(converted), QString("lbl"));
}

void FPUCalculator::on_add2Number_textChanged(const QString &arg1) {
    IEEE32BitConverter *converter = new IEEE32BitConverter();
    qDebug() << arg1.toFloat();
    string converted = converter->convert(arg1.toFloat());
    qDebug() << QString::fromStdString(converted);
    insertIEEENumberToLabels(ui->addSubTab, QString::fromStdString(converted), QString("lbl2_"));
}

void FPUCalculator::on_sub1Number_textChanged(const QString &arg1) {
    IEEE32BitConverter *converter = new IEEE32BitConverter();
    qDebug() << arg1.toFloat();
    string converted = converter->convert(arg1.toFloat());
    qDebug() << QString::fromStdString(converted);
    insertIEEENumberToLabels(ui->addSubTab, QString::fromStdString(converted), QString("lbl3_"));
}

void FPUCalculator::on_sub2Number_textChanged(const QString &arg1) {
    IEEE32BitConverter *converter = new IEEE32BitConverter();
    string converted = converter->convert(arg1.toFloat());
    insertIEEENumberToLabels(ui->addSubTab, QString::fromStdString(converted), QString("lbl4_"));
}

void FPUCalculator::on_mul1Number_textChanged(const QString &arg1) {
    IEEE32BitConverter *converter = new IEEE32BitConverter();
    string converted = converter->convert(arg1.toFloat());
    insertIEEENumberToLabels(ui->mulDivTab, QString::fromStdString(converted), QString("lbl5_"));
}

void FPUCalculator::on_mul2Number_textChanged(const QString &arg1) {
    IEEE32BitConverter *converter = new IEEE32BitConverter();
    string converted = converter->convert(arg1.toFloat());
    insertIEEENumberToLabels(ui->mulDivTab, QString::fromStdString(converted), QString("lbl6_"));
}

void FPUCalculator::on_div1Number_textChanged(const QString &arg1) {
    IEEE32BitConverter *converter = new IEEE32BitConverter();
    string converted = converter->convert(arg1.toFloat());
    insertIEEENumberToLabels(ui->mulDivTab, QString::fromStdString(converted), QString("lbl7_"));
}

void FPUCalculator::on_div2Number_textChanged(const QString &arg1) {
    IEEE32BitConverter *converter = new IEEE32BitConverter();
    string converted = converter->convert(arg1.toFloat());
    insertIEEENumberToLabels(ui->mulDivTab, QString::fromStdString(converted), QString("lbl8_"));
}

void FPUCalculator::on_pow21Number_textChanged(const QString &arg1) {
    IEEE32BitConverter *converter = new IEEE32BitConverter();
    string converted = converter->convert(arg1.toFloat());
    insertIEEENumberToLabels(ui->powerTab, QString::fromStdString(converted), QString("lbl9_"));
}

void FPUCalculator::on_pown1Number_textChanged(const QString &arg1) {
    IEEE32BitConverter *converter = new IEEE32BitConverter();
    string converted = converter->convert(arg1.toFloat());
    insertIEEENumberToLabels(ui->powerTab, QString::fromStdString(converted), QString("lbl10_"));
}


void FPUCalculator::on_sqrt1Number_textChanged(const QString &arg1) {
    IEEE32BitConverter *converter = new IEEE32BitConverter();
    string converted = converter->convert(arg1.toFloat());
    insertIEEENumberToLabels(ui->sqrtTab, QString::fromStdString(converted), QString("lbl11_"));
}

void FPUCalculator::on_reverse1Number_textChanged(const QString &arg1) {
    IEEE32BitConverter *converter = new IEEE32BitConverter();
    string converted = converter->convert(arg1.toFloat());
    insertIEEENumberToLabels(ui->inverseTab, QString::fromStdString(converted), QString("lbl12_"));
}

void FPUCalculator::insertIEEENumberToLabels(QObject *labels, QString number, QString prefix) {
    for(int i = 1; i <= 32; i++){
        QLabel *bitLabel = labels->findChild<QLabel*>(prefix+QString::number(i));
        bitLabel->setAlignment(Qt::AlignCenter);
        if(number.at(i-1) == "0"){
            bitLabel->setStyleSheet("background-color: rgb(224,224,224); color: rgb(0,0,0)");
        }else {
            bitLabel->setStyleSheet("background-color: rgb(30,30,30); color: rgb(255,255,255)");
        }
        bitLabel->setText(number.at(i-1));
    }
}

void FPUCalculator::prepareLineEdits(QWidget *parent) {
    QList<QLineEdit*> lineEdits = parent->findChildren<QLineEdit*>();
    QRegExp floatingNo("^[+-]?([0-9]*[.])?[0-9]+$");
    QRegExpValidator *validator = new QRegExpValidator(floatingNo, this);
    for(int i = 0; i < lineEdits.length(); i++){
        lineEdits[i]->setValidator(validator);
    }
}
