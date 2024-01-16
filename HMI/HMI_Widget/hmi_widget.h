#ifndef HMI_WIDGET_H
#define HMI_WIDGET_H

#include <QWidget>

#include "HMI_Widget/hmi_object.h"

//基础界面
class HMI_Widget : public QWidget, public HMI_Object
{
    Q_OBJECT
public:
    explicit HMI_Widget(QWidget *parent = nullptr);

    //创建控件
    void createButton();
    //删除控件


    virtual void setObjText(const QString& text) override;
    virtual void setObjSize(const QSize& size) override;
    virtual void setObjHeight(const int& value) override;
    virtual void setObjWidth(const int& value) override;
    virtual void setObjPos(const QPoint& pos) override;

    void saveHMI();

signals:
    //选中了控件
    void pressedObject(HMI_Object* object);


private:
    //保存的控件
    QVector<HMI_Object*> m_objects;
    //序列化控件转为Json
    bool convertObjectToJson(QJsonObject& json);

};

#endif // HMI_WIDGET_H
