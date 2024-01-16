
#include <QDebug>
#include <QMouseEvent>

#include "hmi_button.h"

HMI_Button::HMI_Button(QWidget *parent) : QPushButton(parent)
  , HMI_Object(HMI_ObjectType_Button)
{

    this->resize(50, 50);
    setObjSize(this->size());

    connectSignal();
}

void HMI_Button::mousePressEvent(QMouseEvent *event){
    QPushButton::mousePressEvent(event);
    //qDebug()<<"[debug] mousePressEvent";

    //修改为实时检测
    if(mouseOnBorder(event->pos())){
        qDebug()<<"**********obBorder";
        m_mouseOnBorder = true;
        QCursor cursor(Qt::SizeFDiagCursor);
        setCursor(cursor);
        //区分修改尺寸的模式
        ///if(event->pos())
        return;
    }

    QCursor cursor(Qt::SizeAllCursor);
    setCursor(cursor);

    m_mouseIsPressed = true;
    m_offsetPos = event->globalPos() - this->mapToGlobal(this->pos());
}

void HMI_Button::mouseReleaseEvent(QMouseEvent *event){
    QPushButton::mouseReleaseEvent(event);
    //qDebug()<<"[debug] mouseReleaseEvent";
    m_mouseIsPressed = false;
    m_mouseOnBorder = false;

    QCursor cursor(Qt::ArrowCursor);
    setCursor(cursor);
}

void HMI_Button::mouseMoveEvent(QMouseEvent *event){
    QPushButton::mouseMoveEvent(event);
    if(m_mouseOnBorder){
        //计算修改尺寸的方向，在resize的时候近修改固定方向的边框
        //区分8种模式。4个角、4条边
        int newWidth = event->x();
        int newHeight = event->y();
        this->resize(newWidth, newHeight);
    }
    else if(m_mouseIsPressed){
        //如果鼠标为按下状态，获取鼠标移动的方向与距离
        //控件位置与鼠标位置之间要有偏移，需要计算偏移值，然后累加新的鼠标位置
        m_pos = this->mapFromGlobal(event->globalPos() - m_offsetPos);
        //qDebug()<<"[debug] curPos="<<m_pos;
        setObjPos(m_pos);
        m_offsetPos = event->globalPos() - this->mapToGlobal(this->pos());
    }
}

bool HMI_Button::setPressedEvent(std::function<void()> func){
    //解绑信号，重新绑定
    disconnect(this, &HMI_Button::pressed, this, nullptr);
    m_pressedFunc = func;
    connect(this, &HMI_Button::pressed, this, [=]{
        if(m_pressedFunc != nullptr) m_pressedFunc();
    });
    return true;
}

bool HMI_Button::setReleasedEvent(std::function<void()> func){
    disconnect(this, &HMI_Button::pressed, this, nullptr);
    m_releasedFunc = func;
    connect(this, &HMI_Button::released, this, [=]{
        if(m_releasedFunc != nullptr) m_releasedFunc();
    });
    return true;
}

void HMI_Button::connectSignal(){



}

//鼠标进入按钮事件
void HMI_Button::enterEvent(QEvent *event){
    QPushButton::enterEvent(event);
    //qDebug()<<"*********enterEvent";

}

//鼠标移出按钮事件
void HMI_Button::leaveEvent(QEvent *event){
    QPushButton::leaveEvent(event);
    //qDebug()<<"*********leaveEvent";
}

bool HMI_Button::mouseOnBorder(const QPoint& pos)
{
    //检测三种矩形：原始、外扩1像素、内缩1像素
    QRect rect1 = contentsRect();
    QRect rect2 = contentsRect().adjusted(0, 0, 1, 1);
    QRect rect3 = contentsRect().adjusted(0, 0, -1, -1);
    if(!rect1.contains(pos, true) || !rect2.contains(pos, true) || !rect3.contains(pos, true)) return true;
    return false;
}

void HMI_Button::setObjText(const QString& text){
    HMI_Object::setObjText(text);
    this->setText(text);
}


void HMI_Button::setObjSize(const QSize& size){
    HMI_Object::setObjSize(size);
    this->setFixedSize(size);
}

void HMI_Button::setObjHeight(const int& value){
    HMI_Object::setObjHeight(value);
    this->setFixedHeight(value);
}

void HMI_Button::setObjWidth(const int& value){
    HMI_Object::setObjWidth(value);
    this->setFixedWidth(value);
}

void HMI_Button::setObjPos(const QPoint& pos){
    HMI_Object::setObjPos(pos);
    this->move(pos);
}
