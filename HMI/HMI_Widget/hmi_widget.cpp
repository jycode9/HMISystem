
#include <QDebug>
#include <QHBoxLayout>
#include <QCoreApplication>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>

#include "HMI_Widget/hmi_button.h"

#include "hmi_widget.h"

HMI_Widget::HMI_Widget(QWidget *parent) : QWidget(parent)
  , HMI_Object(HMI_ObjectType_Widget)
{

    this->setAttribute(Qt::WA_StyledBackground);
    this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
    setObjSize(QSize(400, 300));

    m_objects.push_back(this);
}


void HMI_Widget::createButton(){

    HMI_Button* button = new HMI_Button(this);
    button->show();

    //点击按钮（选中）
    connect(button, &HMI_Button::clicked, this, [=]{
        emit pressedObject(button);
    });

    m_objects.push_back(button);
}

void HMI_Widget::setObjText(const QString& text){
    HMI_Object::setObjText(text);
}


void HMI_Widget::setObjSize(const QSize& size){
    HMI_Object::setObjSize(size);
    this->setFixedSize(size);
}

void HMI_Widget::setObjHeight(const int& value){
    HMI_Object::setObjHeight(value);
    this->setFixedWidth(value);
}

void HMI_Widget::setObjWidth(const int& value){
    HMI_Object::setObjWidth(value);
    this->setFixedHeight(value);
}

void HMI_Widget::setObjPos(const QPoint& pos){
    HMI_Object::setObjPos(pos);
    this->move(pos);
}

void HMI_Widget::saveHMI(){

    QString path = QCoreApplication::applicationDirPath() + "/" + "HMIConfig.json";
    qDebug()<<"[debug] saved file path="<<path;

    //将当前所有控件写入到文件中
    QFile file(path);
    if(file.open(QIODevice::WriteOnly)){
        //json格式
        QJsonObject jsonObject;
        if(convertObjectToJson(jsonObject) == false){
            qDebug()<<"[error] convert object to json fail";
            return;
        }
        QJsonDocument jsonDocument(jsonObject);
        file.write(jsonDocument.toJson());
        file.close();
        qDebug()<<"[debug] file write done";
    }
    else{
        qDebug()<<"[error] open file fail";
    }

}

bool HMI_Widget::convertObjectToJson(QJsonObject& json){
    //m_objects
    for(auto itr: m_objects){
        //以指针（唯一）为key，每一个key包含HMI_Object中的属性
        //type,width,height,pos_x,pos_y,text,other
        qDebug()<<"\n[debug] object ptr="<<itr;
        qDebug()<<"[debug] object type="<<itr->getObjType();
        qDebug()<<"[debug] object size="<<itr->getObjSize();
        qDebug()<<"[debug] object pos="<<itr->getObjPos();

        QJsonObject obj;
        obj["type"] = itr->getObjType();
        obj["height"] = itr->getObjSize().height();
        obj["width"] = itr->getObjSize().width();
        obj["x"] = itr->getObjPos().x();
        obj["y"] = itr->getObjPos().y();
        json.insert(QString::number(reinterpret_cast<quintptr>(itr), 16), obj);

    }

    return true;
}
