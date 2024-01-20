
#include <QLayout>
#include <QDebug>
#include <QCoreApplication>
#include <QPushButton>
#include <QToolButton>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>

#include "HMI_Widget/hmi_object.h"
#include "HMI_Editor/hmi_editor.h"
#include "HMI_Widget/hmi_button.h"
#include "HMI_Widget/hmi_widget.h"

#include "TCP_Widget/tcpconfig_widget.h"

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    //if(loadWidget() == false) return;


    TCPConfig_Widget* tcpWidget = new TCPConfig_Widget();
    tcpWidget->show();



}

MainWindow::~MainWindow()
{
}

bool MainWindow::loadWidget(){

    if(this->centralWidget() == nullptr){
        qDebug()<<"[warn] centralWidget is nullptr, create new widget";
        //创建一个新的中心界面
        QWidget* widget = new QWidget(this);
        this->setCentralWidget(widget);
    }
    //如果中心界面仍然不存在，报错返回，退出程序
    if(this->centralWidget() == nullptr){
        qDebug()<<"[error] centralWidget is nullptr, assert program";
        return false;
    }

    m_centralWidget = this->centralWidget();

    //m_centralWidget->setStyleSheet("border:1px solid red;");
    QHBoxLayout* layout = new QHBoxLayout(m_centralWidget);
    HMI_Editor* editor = new HMI_Editor(m_centralWidget);
    layout->addWidget(editor);

    //加载HMI信息
    QToolButton* button_load = new QToolButton(this);
    button_load->setText("Load");
    layout->addWidget(button_load);
    connect(button_load, &QToolButton::clicked, this, &MainWindow::loadHMI);

}

bool MainWindow::loadHMI(){
    QString path = QCoreApplication::applicationDirPath() + "/" + "HMIConfig.json";
    qDebug()<<"[debug] load HMI file="<<path;
    //加载文件，解析json

    //先创建一个HMI_Widget作为一个基础界面
    HMI_Widget* baseWidget = new HMI_Widget();
    baseWidget->show();

    QFile file(path);
    if(file.open(QIODevice::ReadOnly)){
        //json格式
        QByteArray jsonData = file.readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
        if(!jsonDoc.isNull()){
            if(jsonDoc.isObject()){
                QJsonObject jsonObj = jsonDoc.object();
                QStringList keys = jsonObj.keys();
                for(const QString& key: keys){
                    QJsonValue value = jsonObj.value(key);
                    if(value.isObject()){
                        QJsonObject obj = value.toObject();
                        int height = obj.value("height").toInt();
                        int type = obj.value("type").toInt();
                        int width = obj.value("width").toInt();
                        int x = obj.value("x").toInt();
                        int y = obj.value("y").toInt();

                        if(type == HMI_ObjectType::HMI_ObjectType_Button){
                            HMI_Button* button = new HMI_Button(baseWidget);
                            button->setObjSize(QSize(width, height));
                            button->setObjPos(QPoint(x, y));
                            button->show();
                        }
                        else if(type == HMI_ObjectType::HMI_ObjectType_Widget){
                            baseWidget->setObjSize(QSize(width, height));
                        }
                    }
                }
            }
        }
        file.close();
        qDebug()<<"[debug] file load done";
    }
    else{
        qDebug()<<"[error] open file fail";
        return false;
    }

    return true;
}



