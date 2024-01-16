#ifndef HMI_OBJECT_H
#define HMI_OBJECT_H

#include <QPoint>
#include <QSize>
#include <QString>

#include <functional>

enum HMI_ObjectType{

    HMI_ObjectType_None,    //无效，略过
    HMI_ObjectType_Widget,  //主界面
    HMI_ObjectType_Button,  //按钮
    HMI_ObjectType_Lamp,    //状态灯
};

//HMI控件的基类。保存控件的类型和信息
class HMI_Object
{
public:
    explicit HMI_Object(const HMI_ObjectType& type);

    virtual void setObjText(const QString& text) = 0;
    virtual void setObjSize(const QSize& size) = 0;
    virtual void setObjHeight(const int& value) = 0;
    virtual void setObjWidth(const int& value) = 0;
    virtual void setObjPos(const QPoint& pos) = 0;

    inline QSize getObjSize(){return m_size;};
    inline HMI_ObjectType getObjType(){return m_type;};
    inline QString getObjText(){return m_text;};
    inline QPoint getObjPos(){return m_pos;};


private:
    HMI_ObjectType m_type = HMI_ObjectType::HMI_ObjectType_None;
    QString m_text = "";
    QPoint m_pos = QPoint(0, 0);
    QSize m_size = QSize(0, 0);

    //针对不同的控件类型，有特定的信号与槽函数
    std::function<void()> m_pressedFunc;
    std::function<void()> m_releasedFunc;

};

#endif // HMI_OBJECT_H
