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
    term = new SerialTerminal(nullptr);
    connect(term, &SerialTerminal::informMainProgram, this, &FPUCalculator::receiveData);
}

FPUCalculator::~FPUCalculator() {
    delete ui;
}

void FPUCalculator::on_addSubBtn_clicked() {
    ui->tabs->setCurrentIndex(0);
}

void FPUCalculator::on_mulDivBtn_clicked() {
    ui->tabs->setCurrentIndex(1);
}

void FPUCalculator::on_powBtn_clicked() {
    ui->tabs->setCurrentIndex(2);
}

void FPUCalculator::on_sqrtBtn_clicked() {
    ui->tabs->setCurrentIndex(3);
}

void FPUCalculator::on_inverseBtn_clicked() {
    ui->tabs->setCurrentIndex(4);
}

void FPUCalculator::on_add1Number_textChanged(const QString &arg1) {
    IEEE32BitConverter *converter = new IEEE32BitConverter();
    qDebug() << arg1.toFloat();
    string converted = converter->convert(arg1.toFloat());
    qDebug() << QString::fromStdString(converted);
    insertIEEENumberToLabels(ui->addSubTab, QString::fromStdString(converted), QString("lbl1_"));
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

QString FPUCalculator::labelsToString(QObject *labels, QString prefix){
    QString str = "";
    for(int i = 1; i <= 32; i++){
        QLabel *bitLabel = labels->findChild<QLabel*>(prefix+QString::number(i));
        str.append(bitLabel->text());
    }
    return str;
}

void FPUCalculator::prepareLineEdits(QWidget *parent) {
    QList<QLineEdit*> lineEdits = parent->findChildren<QLineEdit*>();
    QRegExp floatingNo("^[+-]?([0-9]*[.])?[0-9]+$");
    QRegExpValidator *validator = new QRegExpValidator(floatingNo, this);
    for(int i = 0; i < lineEdits.length(); i++){
        lineEdits[i]->setValidator(validator);
    }
}

void FPUCalculator::on_clearAdd_clicked() {
    ui->add1Number->setText("");
    ui->add2Number->setText("");
    QList<QLabel*> labels1 = ui->add1Bits->findChildren<QLabel*>();
    foreach(QLabel* label, labels1){
        label->setText("");
    }
    QList<QLabel*> labels2 = ui->add2Bits->findChildren<QLabel*>();
    foreach(QLabel* label, labels2){
        label->setText("");
    }
}

void FPUCalculator::on_clearSub_clicked() {
    ui->sub1Number->setText("");
    ui->sub2Number->setText("");
    QList<QLabel*> labels1 = ui->sub1Bits->findChildren<QLabel*>();
    foreach(QLabel* label, labels1){
        label->setText("");
    }
    QList<QLabel*> labels2 = ui->sub2Bits->findChildren<QLabel*>();
    foreach(QLabel* label, labels2){
        label->setText("");
    }
}

void FPUCalculator::on_clearMul_clicked() {
    ui->mul1Number->setText("");
    ui->mul2Number->setText("");
    QRegExp lbl5("lbl5_*");
    lbl5.setPatternSyntax(QRegExp::Wildcard);
    QList<QLabel*> labels1 = ui->mulDivTab->findChildren<QLabel*>(lbl5);
    foreach(QLabel* label, labels1){
        label->setText("");
    }
    QRegExp lbl6("lbl6_*");
    lbl6.setPatternSyntax(QRegExp::Wildcard);
    QList<QLabel*> labels2 = ui->mulDivTab->findChildren<QLabel*>(lbl6);
    foreach(QLabel* label, labels2){
        label->setText("");
    }
}

void FPUCalculator::on_clearDiv_clicked() {
    ui->div1Number->setText("");
    ui->div2Number->setText("");
    QRegExp lbl7("lbl7_*");
    lbl7.setPatternSyntax(QRegExp::Wildcard);
    QList<QLabel*> labels1 = ui->mulDivTab->findChildren<QLabel*>(lbl7);
    foreach(QLabel* label, labels1){
        label->setText("");
    }
    QRegExp lbl8("lbl8_*");
    lbl8.setPatternSyntax(QRegExp::Wildcard);
    QList<QLabel*> labels2 = ui->mulDivTab->findChildren<QLabel*>(lbl8);
    foreach(QLabel* label, labels2){
        label->setText("");
    }
}

void FPUCalculator::on_clearPow2_clicked() {
    ui->pow21Number->setText("");
    QRegExp lbl9("lbl9_*");
    lbl9.setPatternSyntax(QRegExp::Wildcard);
    QList<QLabel*> labels = ui->powerTab->findChildren<QLabel*>(lbl9);
    foreach(QLabel* label, labels){
        label->setText("");
    }
}

void FPUCalculator::on_clearPown_clicked() {
    QRegExp lbl10("lbl10_*");
    lbl10.setPatternSyntax(QRegExp::Wildcard);
    QList<QLabel*> labels = ui->powerTab->findChildren<QLabel*>(lbl10);
    foreach(QLabel* label, labels){
        label->setText("");
    }
}

void FPUCalculator::on_clearSqrt_clicked() {
    ui->sqrt1Number->setText("");
    QRegExp lbl11("lbl11_*");
    lbl11.setPatternSyntax(QRegExp::Wildcard);
    QList<QLabel*> labels = ui->sqrtTab->findChildren<QLabel*>(lbl11);
    foreach(QLabel* label, labels){
        label->setText("");
    }
}

void FPUCalculator::on_clearInverse_clicked() {
    ui->reverse1Number->setText("");
    QRegExp lbl12("lbl12_*");
    lbl12.setPatternSyntax(QRegExp::Wildcard);
    QList<QLabel*> labels = ui->inverseTab->findChildren<QLabel*>(lbl12);
    foreach(QLabel* label, labels){
        label->setText("");
    }
}

void FPUCalculator::on_sendAdd_clicked() {
    QString commandString = "+;";
    QString binary1 = labelsToString(ui->addSubTab, "lbl1_");
    QString binary2 = labelsToString(ui->addSubTab, "lbl2_");
    commandString.append(binary1);
    commandString.append(";");
    commandString.append(binary2);
    commandString.append(";");
    term->openSerialPort();
    term->show();
    qDebug() << "Data sent: " << commandString;
    term->writeData(commandString.toUtf8());
    term->hide();
}

void FPUCalculator::on_sendSub_clicked() {
    QString commandString = "-;";
    QString binary1 = labelsToString(ui->addSubTab, "lbl3_");
    QString binary2 = labelsToString(ui->addSubTab, "lbl4_");
    commandString.append(binary1);
    commandString.append(";");
    commandString.append(binary2);
    commandString.append(";");
    term->openSerialPort();
    term->show();
    qDebug() << "Data sent: " << commandString;
    term->writeData(commandString.toUtf8());
    term->hide();
}

void FPUCalculator::on_sendMul_clicked() {
    QString commandString = "*;";
    QString binary1 = labelsToString(ui->mulDivTab, "lbl5_");
    QString binary2 = labelsToString(ui->mulDivTab, "lbl6_");
    commandString.append(binary1);
    commandString.append(";");
    commandString.append(binary2);
    commandString.append(";");
    term->openSerialPort();
    term->show();
    qDebug() << "Data sent: " << commandString;
    term->writeData(commandString.toUtf8());
    term->hide();
}

void FPUCalculator::on_sendDiv_clicked() {
    QString commandString = "/;";
    QString binary1 = labelsToString(ui->mulDivTab, "lbl7_");
    QString binary2 = labelsToString(ui->mulDivTab, "lbl8_");
    commandString.append(binary1);
    commandString.append(";");
    commandString.append(binary2);
    commandString.append(";");
    term->openSerialPort();
    term->show();
    qDebug() << "Data sent: " << commandString;
    term->writeData(commandString.toUtf8());
    term->hide();
}

void FPUCalculator::on_sendPow2_clicked() {
    QString commandString = "!;";
    QString binary1 = labelsToString(ui->powerTab, "lbl9_");
    commandString.append(binary1);
    commandString.append(";");
    commandString.append("00000000000000000000000000000000");
    commandString.append(";");
    term->openSerialPort();
    term->show();
    qDebug() << "Data sent: " << commandString;
    term->writeData(commandString.toUtf8());
    term->hide();
}

void FPUCalculator::on_sendSqrt_clicked() {
    QString commandString = "s;";
    QString binary1 = labelsToString(ui->sqrtTab, "lbl11_");
    commandString.append(binary1);
    commandString.append(";");
    commandString.append("00000000000000000000000000000000");
    commandString.append(";");
    term->openSerialPort();
    term->show();
    qDebug() << "Data sent: " << commandString;
    term->writeData(commandString.toUtf8());
    term->hide();
}

void FPUCalculator::on_sendInverse_clicked() {
    QString commandString = "i;";
    QString binary1 = labelsToString(ui->inverseTab, "lbl12_");
    commandString.append(binary1);
    commandString.append(";");
    commandString.append("00000000000000000000000000000000");
    commandString.append(";");
    term->openSerialPort();
    term->show();
    qDebug() << "Data sent: " << commandString;
    term->writeData(commandString.toUtf8());
    term->hide();
}

void FPUCalculator::on_settingsBtn_clicked() {
    term->getSettingsDialog()->show();
}

void FPUCalculator::receiveData(const QByteArray &data) {
    QString receivedStr = QString::fromStdString(data.toStdString());
    qDebug () << receivedStr;
    if(receivedStr.length() >= 32){
        fillResult(receivedStr);
    }else {
        QMessageBox::information(this, "Wystąpił błąd", "Nie można przetworzyć danych.\nSprawdź czy:\n1) Urządzenie jest podłączone\n2) Ustawione są odpowiednie parametry połączenia\n3) Wprowadzono poprawne dane", QMessageBox::Ok);
    }
}

void FPUCalculator::fillResult(QString response) {
    for(int i = 1; i <= 32; i++){
        QLabel *bitLabel = ui->resultBits->findChild<QLabel*>("r1_"+QString::number(i));
        bitLabel->setText("");
        bitLabel->setText(response.at(i-1));
    }
}

