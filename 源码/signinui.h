#ifndef SIGNINUI_H
#define SIGNINUI_H

#include <QWidget>

#include <QAction>
#include <QApplication>
#include <QComboBox>
#include <QCheckBox>
#include <QDebug>
#include <QFont>
#include <QFile>
#include <QFileInfo>
#include <QIcon>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QMouseEvent>
#include <QMenu>
#include <QMovie>
#include <QPushButton>
#include <QPoint>
#include <QScreen>
#include <QSystemTrayIcon>
#include <QToolButton>
#include <synchapi.h>
#include <QTime>
//数据库
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
//自定义类
#include "jumpui.h"

class signinUi : public QWidget
{
    Q_OBJECT

//窗体属性
    const int windowWidth=430;
    const int windowHeight=330;
    const int xStart=QGuiApplication::primaryScreen ()->availableGeometry().width()/2-windowWidth/2;//窗体左上角坐标
    const int yStart=QGuiApplication::primaryScreen ()->availableGeometry().height()/2-windowHeight/2;
//外部文件
    QSqlDatabase user_db;
    QFile* file;    //写入账号信息的文件
    jumpUi* jump;   //跳转界面

//窗体控件
    QSystemTrayIcon* bottom_tray;   //系统托盘
    QMenu* menu;
    QAction* action1;
    QAction* action2;

    QLabel* label1;     //窗体上半部分背景
    QMovie* movie;  //设置动态gif

    QLabel* label2; //窗体左上角logo
    QLabel* label3; //头像
    QLabel* label4; //下半部分背景

    QToolButton* small; //最小化
    QToolButton* shut;  //关闭

    QLineEdit* line1;       //账号登录
    QComboBox* combobox1;       //editline控件后面放个combobox（主要是为了下拉控件）

    QLineEdit* line2;   //密码登录
    QComboBox* combobox2;

    QCheckBox* checkbox1;   //自动登录
    QCheckBox* checkbox2;   //记住密码
    QPushButton* backMima;  //忘记密码

    QPushButton* signup;    //注册
    QPushButton* signin;    //登录


//函数实现
    void open_and_create_Sql(QSqlDatabase& db,const QString connectionName,const QString SQLName);     //打开并创建数据库
    void iniSigninUi();     //初始化登录界面
    void fileWrite(const QString fileAddr);   //将输入的账号保存到txt中
//自定义信号与槽
    void deskSignal();  //控件信号与槽
//重写mouseEvent
    bool isClicked = false;
    QPoint point;
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

public:
    signinUi(QWidget *parent = nullptr);
    ~signinUi();
};
#endif // SIGNINUI_H
