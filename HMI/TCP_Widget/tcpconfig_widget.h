#ifndef TCPCONFIG_WIDGET_H
#define TCPCONFIG_WIDGET_H

#include <QWidget>
#include <QModbusDevice>

class QModbusTcpClient;
class QModbusDevice;

class TCPConfig_Widget : public QWidget
{
    Q_OBJECT
public:
    explicit TCPConfig_Widget(QWidget *parent = nullptr);

    inline QModbusDevice::State getTCPState(){return m_state;};

signals:


private:
    void loadWidget();
    int connectTCP(const QString& addr, const QString& port);
    void disconnectTCP();

    QModbusTcpClient *m_client = nullptr;
    QModbusDevice::State m_state = QModbusDevice::State::UnconnectedState;
};

#endif // TCPCONFIG_WIDGET_H
