#ifndef COURSETABLE_H
#define COURSETABLE_H

#include <QWidget>
#include <QMessageBox>
#include <synchapi.h>   //延时
#include <QList>
#include <QMenu>
#include <QAction>
#include <QVector>
#include <QPlainTextEdit>
//standard view/model
#include <QTableView>
#include <QStandardItemModel>
#include <QHeaderView>
//数据库
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class courseTable : public QWidget
{
    Q_OBJECT
protected:
//view属性
    const int xStart=200;
    const int yStart=150;
    const int width=1100;
    const int height=650;

//view/model
    QTableView* tableView;   //右下方显示信息视图
    QStandardItemModel* standardModel;  //右下方显示信息模型
    QVector<QAction*> action = {new QAction("导入数据"),new QAction("导出数据")};
    QMenu* menu;



//视图
    void iniStandardView(const QStringList& HFieldName,const QStringList& VFieldName); //初始化教师视图
    struct{
        QString oldString;
        QPoint oldStringPoint;
    }cellData;
//数据库
    QSqlDatabase courseTable_db;
    void createSQL(QSqlDatabase& db,const QString& connectionName,const QString& SQLName);   //创建数据库
    void createTable(); //创建数据表
    virtual int SQLCount()=0;    //获取数据库有多少行
    virtual void derive_SQL_to_model()=0;    //导入数据库数据到model
    virtual void derive_model_to_SQL()=0; //导入model数据到数据库
//view/model信号与槽
    void signal_on_model(); //处理在model上进行的鼠标事件
public:
    explicit courseTable(QWidget *parent = nullptr);
    ~courseTable();
signals:

};

#endif // COURSETABLE_H
