#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class HMI_Object;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private:
    bool loadWidget();
    QWidget* m_centralWidget = nullptr;

    bool loadHMI();

};
#endif // MAINWINDOW_H
