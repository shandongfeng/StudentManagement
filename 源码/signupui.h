#ifndef SIGNUPUi_H
#define SIGNUPUi_H

#include <QWidget>
#include <QApplication>
#include <QScreen>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QMovie>
//数据库
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>


class signupUi : public QWidget
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
    QLabel* mima;
    QLabel* mimaAgain;
    QLabel* phone;

    QLineEdit* zhanghaoInput;
    QLineEdit* mimaInput;
    QLineEdit* mimaAgainInput;
    QLineEdit* phoneInput;

    QPushButton* signup;
    QPushButton* back;

//函数实现
    void openSql(QSqlDatabase& db,const QString connectionName,const QString SQLName);
    void iniSignupUi();
    bool derive_data_to_sql();
//信号与槽
    void deskSignal();  //控件信号与槽

public:
    explicit signupUi(QWidget *parent = nullptr);
    ~signupUi();
signals:

};

#endif // SIGNUPUI_H
