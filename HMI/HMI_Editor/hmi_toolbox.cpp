
#include <QGridLayout>
#include <QToolButton>

#include "hmi_toolbox.h"


HMI_ToolBox::HMI_ToolBox(QWidget *parent) : QWidget(parent)
{
    loadWidget();
}


void HMI_ToolBox::loadWidget(){

    QGridLayout* layout = new QGridLayout(this);

    //创建button控件
    QToolButton* button = new QToolButton(this);
    button->setText("Button");
    layout->addWidget(button, 0, 0);
    connect(button, &QToolButton::clicked, this, &HMI_ToolBox::createButton);

    //保存HMI信息
    QToolButton* button_save = new QToolButton(this);
    button_save->setText("Save");
    layout->addWidget(button_save, 1, 0);
    connect(button_save, &QToolButton::clicked, this, &HMI_ToolBox::saveHMI);

}
