#ifndef JUMPUI_H
#define JUMPUI_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QApplication>
#include <QScreen>
#include <QTimer>
#include <QMovie>
//自定义类
#include "totalui.h"

class jumpUi : public QWidget
{
    Q_OBJECT
//窗体属性
    const int windowWidth=430;
    const int windowHeight=330;
    const int xStart=QGuiApplication::primaryScreen ()->availableGeometry().width()/2-windowWidth/2;//窗体左上角坐标
    const int yStart=QGuiApplication::primaryScreen ()->availableGeometry().height()/2-windowHeight/2;

    QLabel* background;
    QPushButton* back;
    QTimer* time;
    QMovie* movie;

    void iniJumpUi();
//自定义信号与槽
    void signal_on_jumpUi();



public:
    explicit jumpUi(QWidget *parent = nullptr);
    ~jumpUi();
signals:

};

#endif // JUMPUI_H
