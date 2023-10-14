#ifndef STUDENT_H
#define STUDENT_H

#include <QWidget>
#include <QMessageBox>
#include <synchapi.h>   //延时
#include <QList>
#include <QMenu>
#include <QFile>
//standard view/model
#include <QTableView>
#include <QStandardItemModel>
#include <QHeaderView>
//数据库
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>


class student : public QWidget
{
    Q_OBJECT
protected:
//模型属性
    const int xStart=200;
    const int yStart=150;
    const int width=1100;
    const int height=650;
//文件
    QFile* file;
    QString getStudentID(const QString fileAddr); //打开文件并获取学号
//view/model
    QTableView* tableView;   //右下方显示信息视图
    QStandardItemModel* standardModel;  //右下方显示信息模型
    QVector<QAction*> action = {new QAction("导入数据"),new QAction("导出数据")};
    QMenu* menu;

//视图
    void iniStandardView(const QStringList& HFieldName,const QStringList& VFieldName); //初始化学生视图
    struct{
        QString oldString;
        QPoint oldStringPoint;
    }cellData;

//数据库
    void createSQL(QSqlDatabase& db,const QString& connectionName,const QString& SQLName);  //创建数据库并打开
    virtual int SQLCount()=0;
    virtual void derive_SQL_to_model(const QString& studentID)=0;    //导入数据库数据到model
    virtual void derive_model_to_SQL(const QString& studentID)=0; //导入model数据到数据库
//view/model信号与槽
    void signal_on_model(const QString& studentID); //处理在model上进行的鼠标事件

public:
    explicit student(QWidget *parent = nullptr);
    ~student();
signals:

};

#endif // STUDENT_H
