#ifndef TOTALUI_H
#define TOTALUI_H

#include <QMainWindow>
#include <QApplication>
#include <QScreen>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include <QList>
#include <QStackedWidget>
#include <QFile>
//view/model
#include <QTreeWidgetItem>
//引用自定义类
#include "teacher_message.h"
#include "teacher_score.h"
#include "teacher_coursetable.h"
#include "student_message.h"
#include "student_score.h"
#include "student_coursetable.h"



class totalUi : public QMainWindow
{
    Q_OBJECT
//窗口属性
    const int windowWidth=1300;
    const int windowHeight=800;
    const int xStart=QGuiApplication::primaryScreen ()->availableGeometry().width()/2-windowWidth/2;
    const int yStart=QGuiApplication::primaryScreen ()->availableGeometry().height()/2-windowHeight/2;
//窗体及标题
    QLabel* total;  //全图背景
    QLabel* title;  //标题（学生信息管理系统）背景
//用户识别区域
    QFile* file;
    QLabel* userStatus; //用户身份
    QLabel* userName;   //用户名
//搜索区域
    QLabel* search; //搜索label
    QLineEdit* searchLine;  //搜索框
//左边的功能模块栏
    QTreeWidget* treeWidget;
    QList<QTreeWidgetItem*> father;
    QList<QTreeWidgetItem*> son1;
    QList<QTreeWidgetItem*> grandson11;
    QList<QTreeWidgetItem*> grandson12;
    QStringList fName={"信息管理","其他"};
    QStringList sName1={"教师模块","学生模块"};
    QStringList gName111={"修改信息","修改成绩","修改课程表"};
    QStringList gName112={"查询信息","查询成绩","查询课程表"};

    QPushButton* refresh;   //刷新按钮
    QPushButton* back;  //退出按钮
//右下方表格视图
    QStackedWidget* widget;
    teacher* message1;
    teacher* score1;
    courseTable* courseTable1;
    student* message2;
    student* score2;
    courseTable* courseTable2;
//函数实现
    QString fileRead(const QString fileAddr);    //读取txt文件内容
    void iniTotalUi();  //初始化总界面 
    void setUserMessage(const QString& userMessage);  //将所有用户账号导入到账号combobox中
    void setRightView(const QString& userMessage);    //设置最后右下方的信息显示视图
    void setLeftView(); //设置左边combobox视图
//信号与槽
    void handle_left_signal();  //处理左边功能栏的信号
//外部类获取本类信息



public:
    explicit totalUi(QWidget *parent = nullptr);
    ~totalUi();
signals:

};

#endif // TOTALUI_H
