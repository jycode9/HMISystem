#ifndef HMI_EDITOR_H
#define HMI_EDITOR_H

#include <QWidget>

//HMI编辑界面
class HMI_Editor : public QWidget
{
    Q_OBJECT
public:
    explicit HMI_Editor(QWidget *parent = nullptr);

signals:


private:
    void loadWidget();

};

#endif // HMI_EDITOR_H
