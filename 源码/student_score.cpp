#include "student_score.h"


int student_score::SQLCount()
{
    QSqlQuery query(score_db);
    int count=0;
    query.exec("select* from score");
    while(query.next() && ++count);
    query.finish();
    return count;
}

void student_score::derive_SQL_to_model(const QString& studentID)
{
    standardModel->removeColumn(0);
    QSqlQuery query(score_db);
    query.exec("select* from score");
    if(query.next() == false){
        QMessageBox::information(this,"提示","数据库为空，暂时无法导入到model",QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
        query.finish();
        return;
    }
//根据学号查询此人
    query.exec(QString("select* from score where studentID = '%1'").arg(studentID));
    if(query.next() == false){
        QMessageBox::information(this,"提示","数据库无此人信息",QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
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

void student_score::derive_model_to_SQL(const QString& studentID)
{    
    if(standardModel->columnCount()<=0){
        QMessageBox::information(this,"提示","表格为空，无法导出",QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
        return;
    }
    QSqlQuery query(score_db);
    query.exec(QString("select* from score where studentID = '%1'").arg(studentID));
    if(query.next() == false){
        QMessageBox::information(this,"提示","查无此人,无法导出",QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
        query.finish();
        return;
    }

    query.exec(QString("delete from score where studentID = '%1'").arg(studentID));
    query.exec(QString("insert into score(id,name,classes,studentID,subject1,subject2,subject3,subject4,subject5,subject6) values(%1,'%2',%3,'%4',%5,%6,%7,%8,%9,%10)").arg(standardModel->data(QModelIndex(standardModel->index(0,0))).toInt()).arg(standardModel->data(QModelIndex(standardModel->index(1,0))).toString()).arg(standardModel->data(QModelIndex(standardModel->index(2,0))).toInt()).arg(standardModel->data(QModelIndex(standardModel->index(3,0))).toString()).arg(standardModel->data(QModelIndex(standardModel->index(4,0))).toFloat()).arg(standardModel->data(QModelIndex(standardModel->index(5,0))).toFloat()).arg(standardModel->data(QModelIndex(standardModel->index(6,0))).toFloat()).arg(standardModel->data(QModelIndex(standardModel->index(7,0))).toFloat()).arg(standardModel->data(QModelIndex(standardModel->index(8,0))).toFloat()).arg(standardModel->data(QModelIndex(standardModel->index(9,0))).toFloat()));
    QMessageBox::information(this,"提示","model成功导入数据库",QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
    query.finish();
}


student_score::student_score(student *parent)
    : student{parent}
{
    QString studentID = student::getStudentID("zhanghao.txt");
    iniStandardView(HFieldName,VFieldName);
    student::createSQL(score_db,"two","score");
    student::signal_on_model(studentID);
}

student_score::~student_score()
{
    score_db.close();
    qDebug()<<"析构学生信息student_score";
}
