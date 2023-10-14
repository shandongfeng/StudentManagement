#include "student_coursetable.h"


int student_courseTable::SQLCount()
{
    QSqlQuery query(courseTable_db);
    int count=0;
    query.exec("select* from courseTable");
    while(query.next() && ++count);
    query.finish();
    return count;
}

void student_courseTable::derive_SQL_to_model()
{
//清除单元格
    for(int i=0;i<VFieldName.size();i++){
        for(int j=0;j<HFieldName.size();j++){
            standardModel->clearItemData(standardModel->index(i,j));
        }
    }
    QSqlQuery query(courseTable_db);
    query.exec("select* from courseTable");
    if(query.next() == false){
        QMessageBox::information(this,"提示","数据库为空，暂时无法导入到model",QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
        return;
    }
//导入数据库信息到model
    for(int i=0;i<SQLCount();i++,query.next()){
        for(int j=0;j<HFieldName.size();j++){
            standardModel->setItem(i,j,new QStandardItem(query.value(j).toString().replace("\\n","\n")));
        }
    }
    QMessageBox::information(this,"提示","数据导入成功",QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
    query.finish();
}

void student_courseTable::derive_model_to_SQL()
{
    QMessageBox::information(this,"提示","学生无法修改课程表",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
//想导入就取消下面的注释
    /*if(standardModel->rowCount()<=0){
        QMessageBox::information(this,"提示","表格为空，无法导出",QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
        return;
    }
    QSqlQuery query(courseTable_db);
    query.exec("delete from courseTable");
    for(int i=0;i<standardModel->rowCount();i++){
        query.exec(QString("insert into courseTable(monday,tuesday,wednesday,thursday,friday,saturday,sunday) values('%1','%2','%3','%4','%5','%6','%7')").arg(standardModel->data(QModelIndex(standardModel->index(i,0))).toString()).arg(standardModel->data(QModelIndex(standardModel->index(i,1))).toString()).arg(standardModel->data(QModelIndex(standardModel->index(i,2))).toString()).arg(standardModel->data(QModelIndex(standardModel->index(i,3))).toString()).arg(standardModel->data(QModelIndex(standardModel->index(i,4))).toString()).arg(standardModel->data(QModelIndex(standardModel->index(i,5))).toString()).arg(standardModel->data(QModelIndex(standardModel->index(i,6))).toString()));
    }
    QMessageBox::information(this,"提示","model成功导出数据库",QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
    query.finish();
    */
}



student_courseTable::student_courseTable(courseTable *parent)
    : courseTable{parent}
{
    courseTable::iniStandardView(HFieldName,VFieldName);
    courseTable::createSQL(courseTable_db,"three","courseTable");
    courseTable::signal_on_model();
}

student_courseTable::~student_courseTable()
{
    qDebug()<<"析构学生课程表student_courseTable";
}
