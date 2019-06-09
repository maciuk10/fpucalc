#ifndef SERIALTERMINAL_H
#define SERIALTERMINAL_H

#include <QMainWindow>
#include <QSerialPort>

QT_BEGIN_NAMESPACE

class QLabel;

namespace Ui {
class SerialTerminal;
}


QT_END_NAMESPACE

class SettingsDialog;

class SerialTerminal : public QMainWindow
{
    Q_OBJECT
signals:
    void informMainProgram(const QByteArray &data);
public:
    explicit SerialTerminal(QWidget *parent = nullptr);
    ~SerialTerminal();
    void openSerialPort();
    void informHelper(const QByteArray &data);
    SettingsDialog* getSettingsDialog();

public slots:
    void writeData(const QByteArray &data);

private slots:
    void closeSerialPort();
    void readData();
    void handleError(QSerialPort::SerialPortError error);

private:
    void showStatusMessage(const QString &message);
    void initActionsConnections();

    Ui::SerialTerminal *m_ui = nullptr;
    QLabel *m_status = nullptr;
    SettingsDialog *m_settings = nullptr;
    QSerialPort *m_serial = nullptr;
    QByteArray received;
};

#endif // SERIALTERMINAL_H
