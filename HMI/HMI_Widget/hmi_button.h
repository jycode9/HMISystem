#ifndef HMI_BUTTON_H
#define HMI_BUTTON_H



#include <QPushButton>

#include <functional>

#include "HMI_Widget/hmi_object.h"

//HMI控件——按钮
class HMI_Button : public QPushButton, public HMI_Object
{
    Q_OBJECT
public:
    explicit HMI_Button(QWidget *parent);

    inline QPoint getPos(){return m_pos;};
    //设置按钮响应事件
    bool setPressedEvent(std::function<void()> func);
    bool setReleasedEvent(std::function<void()> func);

    virtual void setObjText(const QString& text) override;
    virtual void setObjSize(const QSize& size) override;
    virtual void setObjHeight(const int& value) override;
    virtual void setObjWidth(const int& value) override;
    virtual void setObjPos(const QPoint& pos) override;

    //设置模式（编辑模式-可拖动、release模式-不可拖动）

signals:


    //***************控件拖拽、尺寸修改***************
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
private:
    bool m_mouseIsPressed = false;
    QPoint m_offsetPos = QPoint(0, 0); //鼠标位置与控件原点的偏移量
    QPoint m_pos = QPoint(0, 0);    //控件最后的位置
    bool mouseOnBorder(const QPoint& pos);
    bool m_mouseOnBorder = false;
    //4个角
    bool m_mouseOnBorder_LeftTop = false;
    bool m_mouseOnBorder_RightTop = false;
    bool m_mouseOnBorder_LeftBottom = false;
    bool m_mouseOnBorder_RightBottom = false;
    //4条边
    bool m_mouseOnBorder_Top = false;
    bool m_mouseOnBorder_Right = false;
    bool m_mouseOnBorder_Bottom = false;
    bool m_mouseOnBorder_Left = false;

    //***************自定义按钮事件***************
private:
    void connectSignal();
    std::function<void()> m_pressedFunc;
    std::function<void()> m_releasedFunc;




};

#endif // HMI_BUTTON_H
