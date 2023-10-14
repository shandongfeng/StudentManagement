#ifndef FINDUI_H
#define FINDUI_H

#include <QWidget>
#include <QApplication>
#include <QScreen>
#include <QMessageBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMovie>
//数据库
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class findUi : public QWidget
{
    Q_OBJECT
//窗体属性
    const int windowWidth=600;
    const int windowHeight=600;
    const int xStart=QGuiApplication::primaryScreen ()->availableGeometry().width()/2-windowWidth/2;
    const int yStart=QGuiApplication::primaryScreen ()->availableGeometry().height()/2-windowHeight/2;
//外部文件
    QSqlDatabase user_db;
//控件
    QLabel* background;
    QMovie* movie;
    QLabel* zhanghao;
    QLabel* phone;
    QLabel* mima;
    QLabel* mimaAgain;


    QLineEdit* zhanghaoInput;
    QLineEdit* phoneInput;
    QLineEdit* mimaInput;
    QLineEdit* mimaAgainInput;


    QPushButton* signup;
    QPushButton* back;

//方法实现
    void openSql(QSqlDatabase& db,const QString connectionName,const QString SQLName);     //打开数据库
    void iniFindUi();   //初始化找回密码界面
    bool derive_data_to_sql();      //新信息导入到数据库
//信号与槽
    void deskSignal();  //控件信号与槽
public:
    explicit findUi(QWidget *parent = nullptr);
    ~findUi();
signals:

};

#endif // FINDUI_H
