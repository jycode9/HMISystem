#include "hmi_object.h"

HMI_Object::HMI_Object(const HMI_ObjectType& type):
    m_type(type)
{

}

void HMI_Object::setObjText(const QString& text){
    m_text = text;

}

void HMI_Object::setObjPos(const QPoint& pos){
    m_pos = pos;

}

void HMI_Object::setObjSize(const QSize& size){
    m_size = size;
}

void HMI_Object::setObjHeight(const int& value){
    m_size.setHeight(value);
}


void HMI_Object::setObjWidth(const int& value){
    m_size.setWidth(value);
}
