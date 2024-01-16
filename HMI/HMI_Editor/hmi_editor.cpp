
#include <QHBoxLayout>

#include "HMI_Editor/hmi_toolbox.h"
#include "HMI_Widget/hmi_widget.h"
#include "HMI_Editor/HMI_ConfigWidget.h"

#include "hmi_editor.h"

HMI_Editor::HMI_Editor(QWidget *parent) : QWidget(parent)
{
    loadWidget();

    this->setAttribute(Qt::WA_StyledBackground);
    this->setStyleSheet("border: 1px solid red;");
}



void HMI_Editor::loadWidget(){

    HMI_ToolBox* toolBox = new HMI_ToolBox(this);
    HMI_Widget* widget = new HMI_Widget(this);
    HMI_ConfigWidget* configWidget = new HMI_ConfigWidget(this);


    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setMargin(10);

    layout->addWidget(toolBox);
    layout->addWidget(widget);
    layout->addWidget(configWidget);


    connect(toolBox, &HMI_ToolBox::createButton, widget, &HMI_Widget::createButton);
    connect(widget, &HMI_Widget::pressedObject, this, [=](HMI_Object* object){
        configWidget->setShowObject(object);
    });

    //将HMI_Widget中的所有控件保存
    connect(toolBox, &HMI_ToolBox::saveHMI, widget, &HMI_Widget::saveHMI);

}

