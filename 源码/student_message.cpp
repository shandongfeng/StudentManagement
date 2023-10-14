#include "student_message.h"


int student_message::SQLCount()
{
    QSqlQuery query(message_db);
    int count=0;
    query.exec("select* from message");
    while(query.next() && ++count);
    query.finish();
    return count;
}

void student_message::derive_SQL_to_model(const QString& studentID)
{
    standardModel->removeColumn(0);
    QSqlQuery query(message_db);
    query.exec("select* from message");
    if(query.next() == false){
        QMessageBox::information(this,"提示","数据库为空，暂时无法导入到model",QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
        query.finish();
        return;
    }
//根据学号查询此人
    query.exec(QString("select* from message where studentID = %1").arg(studentID.toLongLong()));
    if(query.next() == false){
        QMessageBox::information(this,"提示","查无此人,无法导出",QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
        query.finish();
        return;
    }
//导入数据库信息到model
    for(int i=0;i<standardModel->rowCount();i++){
        standardModel->setItem(i,0,new QStandardItem(query.value(i).toString()));
    }
    QMessageBox::information(this,"提示","数据导入成功",QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
    query.finish();
}

void student_message::derive_model_to_SQL(const QString& studentID)
{
    if(standardModel->columnCount()<=0){
        QMessageBox::information(this,"提示","表格为空，无法导出",QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
        return;
    }
    QSqlQuery query(message_db);
//根据学号查询此人
    query.exec(QString("select* from score where studentID = '%1'").arg(studentID.toLongLong()));
    if(query.next() == false){
        QMessageBox::information(this,"提示",",无法导入",QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
        query.finish();
        return;
    }
    query.exec(QString("delete from message where studentID = %1").arg(studentID.toLongLong()));
    query.exec(QString("insert into message(id,name,sex,age,classes,studentID,college,major,grade,bedroom,hometown,phoneNumber) values(%1,'%2','%3',%4,%5,%6,'%7','%8','%9','%10','%11','%12')").arg(standardModel->data(QModelIndex(standardModel->index(0,0))).toInt()).arg(standardModel->data(QModelIndex(standardModel->index(1,0))).toString()).arg(standardModel->data(QModelIndex(standardModel->index(2,0))).toString()).arg(standardModel->data(QModelIndex(standardModel->index(3,0))).toInt()).arg(standardModel->data(QModelIndex(standardModel->index(4,0))).toInt()).arg(standardModel->data(QModelIndex(standardModel->index(5,0))).toLongLong()).arg(standardModel->data(QModelIndex(standardModel->index(6,0))).toString()).arg(standardModel->data(QModelIndex(standardModel->index(7,0))).toString()).arg(standardModel->data(QModelIndex(standardModel->index(8,0))).toString()).arg(standardModel->data(QModelIndex(standardModel->index(9,0))).toString()).arg(standardModel->data(QModelIndex(standardModel->index(10,0))).toString()).arg(standardModel->data(QModelIndex(standardModel->index(11,0))).toString()));
    QMessageBox::information(this,"提示","model成功导入数据库",QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
    query.finish();

}


student_message::student_message(student *parent)
    : student{parent}
{
    QString studentID = student::getStudentID("zhanghao.txt");
    student::iniStandardView(HFieldName,VFieldName);
    student::createSQL(message_db,"student_message","message");
    student::signal_on_model(studentID);
}

student_message::~student_message()
{
    message_db.close();
    qDebug()<<"析构学生信息student_message";
}
