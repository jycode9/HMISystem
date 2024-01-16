


#include <QGridLayout>
#include <QDebug>


#include "HMI_Widget/hmi_object.h"

#include "HMI_ConfigWidget.h"

HMI_ConfigWidget::HMI_ConfigWidget(QWidget *parent) : QWidget(parent)
{
    loadWidget();
}



void HMI_ConfigWidget::setShowObject(HMI_Object* object){
    m_object = nullptr;
    if(object == nullptr){
        qDebug()<<"[error] HMI object is nullptr";
        return;
    }
    m_object = object;
    //加载控件的信息
    reloadWidget();

}


void HMI_ConfigWidget::reloadWidget(){
    //获取控件尺寸，设置尺寸
    m_hengthEdit->setText(QString::number(m_object->getObjSize().height()));
    m_widthEdit->setText(QString::number(m_object->getObjSize().width()));


}

void HMI_ConfigWidget::changeObjectHeight(const QString& value){
    if(m_object == nullptr){
        qDebug()<<"[error] m_object is nullptr";
        return;
    }
    m_object->setObjHeight(value.toInt());
}

void HMI_ConfigWidget::changeObjectWidth(const QString& value){
    if(m_object == nullptr){
        qDebug()<<"[error] m_object is nullptr";
        return;
    }
    m_object->setObjWidth(value.toInt());
}


void HMI_ConfigWidget::loadWidget(){


    m_hengthEdit = new QLineEdit(this);
    m_widthEdit = new QLineEdit(this);

    connect(m_hengthEdit, &QLineEdit::textChanged, this, &HMI_ConfigWidget::changeObjectHeight);
    connect(m_widthEdit, &QLineEdit::textChanged, this, &HMI_ConfigWidget::changeObjectWidth);


    QGridLayout* layout = new QGridLayout(this);

    m_nameLabel = new QLabel(this);
    layout->addWidget(m_nameLabel, 0, 0);

    QLabel* length = new QLabel(this);
    length->setText(tr("Length"));
    layout->addWidget(length, 1, 0);
    layout->addWidget(m_hengthEdit, 1, 1);


    QLabel* width = new QLabel(this);
    width->setText(tr("Width"));
    layout->addWidget(width, 2, 0);
    layout->addWidget(m_widthEdit, 2, 1);


}



