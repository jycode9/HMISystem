#ifndef HMI_TOOLBOX_H
#define HMI_TOOLBOX_H

#include <QWidget>

//左侧的工具箱，插入各种控件
class HMI_ToolBox : public QWidget
{
    Q_OBJECT
public:
    explicit HMI_ToolBox(QWidget *parent = nullptr);

signals:
    void createButton();
    void saveHMI();

private:
    void loadWidget();
};

#endif // HMI_TOOLBOX_H
