#include "serialterminal.h"
#include "ui_serialterminal.h"
#include "settingsdialog.h"

#include <QLabel>
#include <QMessageBox>

SerialTerminal::SerialTerminal(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::SerialTerminal),
    m_status(new QLabel),
    m_settings(new SettingsDialog),
    m_serial(new QSerialPort(this))
{
    m_ui->setupUi(this);
    m_ui->actionConnect->setEnabled(true);
    m_ui->actionDisconnect->setEnabled(false);
    m_ui->actionQuit->setEnabled(true);
    m_ui->actionConfigure->setEnabled(true);
    initActionsConnections();
    connect(m_serial, &QSerialPort::errorOccurred, this, &SerialTerminal::handleError);
    connect(m_serial, &QSerialPort::readyRead, this, &SerialTerminal::readData);
}

SerialTerminal::~SerialTerminal()
{
    delete m_settings;
}

void SerialTerminal::openSerialPort() {
    const SettingsDialog::Settings p = m_settings->settings();
    m_serial->setPortName(p.name);
    m_serial->setBaudRate(p.baudRate);
    m_serial->setDataBits(p.dataBits);
    m_serial->setParity(p.parity);
    m_serial->setStopBits(p.stopBits);
    m_serial->setFlowControl(p.flowControl);
    if (m_serial->open(QIODevice::ReadWrite)) {
        showStatusMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                          .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                          .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));
    } else {
        QMessageBox::critical(nullptr, tr("Error"), m_serial->errorString());
        showStatusMessage(tr("Open error"));
    }
}

void SerialTerminal::informHelper(const QByteArray &data) {
    closeSerialPort();
    emit informMainProgram(data);
}

SettingsDialog *SerialTerminal::getSettingsDialog() {
    return m_settings;
}

void SerialTerminal::closeSerialPort() {
    if (m_serial->isOpen())
        m_serial->close();
    showStatusMessage(tr("Disconnected"));
}

void SerialTerminal::readData(){
    const QByteArray data = m_serial->readAll();
    received = data;
    informHelper(received);
}

void SerialTerminal::writeData(const QByteArray &data){
    m_serial->write(data);
}

void SerialTerminal::handleError(QSerialPort::SerialPortError error){
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(nullptr, tr("Critical Error"), m_serial->errorString());
        closeSerialPort();
    }
}

void SerialTerminal::showStatusMessage(const QString &message)
{
    m_status->setText(message);
}

void SerialTerminal::initActionsConnections() {
    connect(m_ui->actionConnect, &QAction::triggered, this, &SerialTerminal::openSerialPort);
    connect(m_ui->actionDisconnect, &QAction::triggered, this, &SerialTerminal::closeSerialPort);
    connect(m_ui->actionQuit, &QAction::triggered, this, &SerialTerminal::close);
    connect(m_ui->actionConfigure, &QAction::triggered, m_settings, &SettingsDialog::show);
    connect(m_ui->actionAboutQt, &QAction::triggered, qApp, &QApplication::aboutQt);
}

