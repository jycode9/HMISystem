

#include <QModbusTcpClient>
#include <QModbusDataUnit>
#include <QModbusTcpServer>

#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QDebug>

#include "tcpconfig_widget.h"


TCPConfig_Widget::TCPConfig_Widget(QWidget *parent) : QWidget(parent)
{
    m_client = new QModbusTcpClient(this);





    loadWidget();

}



void TCPConfig_Widget::loadWidget(){

    QGridLayout* layout = new QGridLayout(this);
    //
    QLabel* addrLabel = new QLabel(this);
    QLabel* portLabel = new QLabel(this);
    QLineEdit* addrEdit = new QLineEdit(this);
    QLineEdit* portEdit = new QLineEdit(this);
    addrEdit->setText("127.0.0.1");
    portEdit->setText("502");
    //
    layout->addWidget(addrLabel, 0, 0);
    layout->addWidget(addrEdit, 0, 1, 1, 2);
    //
    layout->addWidget(portLabel, 1, 0);
    layout->addWidget(portEdit, 1, 1, 1, 2);
    //
    addrLabel->setText("Address");
    portLabel->setText("Port");
    addrLabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    portLabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    //
    QPushButton* connectButton = new QPushButton(this);
    connectButton->setText("Connect");
    layout->addWidget(connectButton, 2, 1);



    connect(connectButton, &QPushButton::clicked, this, [=]{

        //根据当前文字判断连接或断开
        if(connectButton->text().compare("Connect")==0){
            QString addr = addrEdit->text();
            QString port = portEdit->text();
            //connect
            connectTCP(addr, port);
        }
        else{
            disconnectTCP();

        }


    });


    connect(m_client, &QModbusTcpClient::stateChanged, this, [=](QModbusDevice::State state){
        qDebug()<<"*******connect state changed="<<m_client->state();

        if(state == QModbusDevice::UnconnectedState){
            connectButton->setEnabled(true);
            connectButton->setText("Connect");
        }
        else if(state == QModbusDevice::ConnectingState){
            connectButton->setEnabled(false);
            connectButton->setText("Connecting");
        }
        else if(state == QModbusDevice::ConnectedState){
            connectButton->setEnabled(true);
            connectButton->setText("Disconnect");
        }
        else if(state == QModbusDevice::ClosingState){
            connectButton->setEnabled(false);
            connectButton->setText("Closing");
        }
        else{
            //error
            connectButton->setEnabled(true);
            connectButton->setText("Connect");
        }

        m_state = state;

    });

}

int TCPConfig_Widget::connectTCP(const QString& addr, const QString& port){


    qDebug()<<"*******addr="<<addr;
    qDebug()<<"*******port="<<port;

    m_client->setConnectionParameter(QModbusDevice::NetworkPortParameter, port); // 设置端口号
    m_client->setConnectionParameter(QModbusDevice::NetworkAddressParameter, addr); // 设置下位机的IP地址

    if (!m_client->connectDevice()) {
        qDebug()<<"********connect fail";
        return -1;
    }
    qDebug()<<"*******connect suc";

    return 0;

}


void TCPConfig_Widget::disconnectTCP(){
    m_client->disconnectDevice();

}







