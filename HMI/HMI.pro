QT += core gui
QT += serialbus #modbus

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    HMI_Editor/hmi_configwidget.cpp \
    HMI_Editor/hmi_editor.cpp \
    HMI_Editor/hmi_toolbox.cpp \
    HMI_Widget/hmi_button.cpp \
    HMI_Widget/hmi_object.cpp \
    HMI_Widget/hmi_widget.cpp \
    TCP_Widget/tcpconfig_widget.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    HMI_Editor/hmi_configwidget.h \
    HMI_Editor/hmi_editor.h \
    HMI_Editor/hmi_toolbox.h \
    HMI_Widget/hmi_button.h \
    HMI_Widget/hmi_object.h \
    HMI_Widget/hmi_widget.h \
    TCP_Widget/tcpconfig_widget.h \
    mainwindow.h

TRANSLATIONS += \
    HMI_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
