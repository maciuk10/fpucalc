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
