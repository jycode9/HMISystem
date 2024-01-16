#ifndef HMI_CONFIGWIDGET_H
#define HMI_CONFIGWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>

class HMI_Object;

//右侧的控件配置界面
class HMI_ConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HMI_ConfigWidget(QWidget *parent = nullptr);

    //设定显示的控件
    void setShowObject(HMI_Object* object);

signals:


private:
    //控件的尺寸
    void loadWidget();
    void reloadWidget();

    QLabel* m_nameLabel = nullptr;
    QLineEdit* m_hengthEdit = nullptr;
    QLineEdit* m_widthEdit = nullptr;


private:
    HMI_Object* m_object = nullptr;
    //修改object尺寸
    void changeObjectHeight(const QString& value);
    void changeObjectWidth(const QString& value);

};

#endif // HMI_CONFIGWIDGET_H
