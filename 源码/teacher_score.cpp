#include "teacher_score.h"


void teacher_score::createTable()
{
//创建数据库
    QSqlQuery query(score_db);
    //避免表重复创建
    query.exec("select * from score");
    if(query.next() == false){
        //"序号","姓名","班级","学号","人工智能","嵌入式","Linux","网络编程","C++高级编程","Python"
        query.exec("create table score(id INTEGER PRIMARY KEY AUTOINCREMENT,name varchar(20),classes int,studentID varchar(15),subject1 float,subject2 float,subject3 float,subject4 float,subject5 float,subject6 float)");
        qDebug()<<"score_db数据库表已创建";
    }else{
        qDebug()<<"score_db数据库表已存在,无需创建";
        return;
    }
    query.finish();
}

int teacher_score::SQLCount()
{
    QSqlQuery query(score_db);
    int count=0;
    query.exec("select* from score");
    while(query.next() && ++count);
    query.finish();
    return count;
}

void teacher_score::derive_SQL_to_model()
{
    standardModel->removeRows(0,standardModel->rowCount());
    QSqlQuery query2(message_db_tmp);
    query2.exec("select* from message");
    if(query2.next() == false){
        QMessageBox::information(this,"提示","数据库为空，暂时无法导入到model",QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
        return;
    }
    int count =0;
    do{
        standardModel->setItem(count,0,new QStandardItem(query2.value(0).toString()));
        standardModel->setItem(count,1,new QStandardItem(query2.value(1).toString()));
        standardModel->setItem(count,2,new QStandardItem(query2.value(4).toString()));
        standardModel->setItem(count,3,new QStandardItem(query2.value(5).toString()));
    }while(query2.next() && ++count);

    QSqlQuery query(score_db);
    query.exec("select* from score");    

//导入数据库信息到model
    for(int i=0;i<SQLCount() && query.next();i++){
        for(int k=4;k<HFieldName.size();k++){
            standardModel->setItem(i,k,new QStandardItem(query.value(k).toString()));
        }
    }
    QMessageBox::information(this,"提示","数据导入成功",QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
    query.finish();
    query2.finish();
}

void teacher_score::derive_model_to_SQL()
{
    if(standardModel->rowCount()<=0){
        QMessageBox::information(this,"提示","表格为空，无法导出",QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
        return;
    }
    QSqlQuery query(score_db);
    query.exec("delete from score");
    for(int i=0;i<standardModel->rowCount();i++){
        query.exec(QString("insert into score(id,name,classes,studentID,subject1,subject2,subject3,subject4,subject5,subject6) values(%1,'%2',%3,'%4',%5,%6,%7,%8,%9,%10)").arg(standardModel->data(QModelIndex(standardModel->index(i,0))).toInt()).arg(standardModel->data(QModelIndex(standardModel->index(i,1))).toString()).arg(standardModel->data(QModelIndex(standardModel->index(i,2))).toInt()).arg(standardModel->data(QModelIndex(standardModel->index(i,3))).toString()).arg(standardModel->data(QModelIndex(standardModel->index(i,4))).toFloat()).arg(standardModel->data(QModelIndex(standardModel->index(i,5))).toFloat()).arg(standardModel->data(QModelIndex(standardModel->index(i,6))).toFloat()).arg(standardModel->data(QModelIndex(standardModel->index(i,7))).toFloat()).arg(standardModel->data(QModelIndex(standardModel->index(i,8))).toFloat()).arg(standardModel->data(QModelIndex(standardModel->index(i,9))).toFloat()));
    }
    QMessageBox::information(this,"提示","model成功导入数据库",QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
    query.finish();
}

void teacher_score::mySort(const int column, const bool order)
{
    if(standardModel->rowCount()<=0){
        QMessageBox::information(this,"警告","当前model为空,无法排序",QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
        return;
    }
    int rowCount=standardModel->rowCount(); //tableView总行数
    int colCount=HFieldName.size();  //tableView总列数
//提前记录tableview所有数据
    qDebug()<<rowCount<<"  "<<colCount;
    QVector<QVector<QString>> list(rowCount,QVector<QString>(colCount));
    for(int i=0;i<rowCount;i++){
        for(int j=0;j<colCount;j++){
            if(standardModel->item(i,j) != nullptr){
                list[i][j] = (standardModel->item(i,j)->text());
            }
        }
    }
//获取指定列数据
    QVector<QPair<float,int>> list2;
    for(int i=0;i<rowCount;i++){
        if(standardModel->item(i,column) != nullptr){
            list2.push_back({standardModel->item(i,column)->text().toFloat(),i});
        }
    }

//排序
    if(order == true){
        sort(list2.begin(),list2.end(),std::greater<QPair<float,int>>());
    }else{
        sort(list2.begin(),list2.end(),std::less<QPair<float,int>>());
    }

//将排完序的新数据导入到model
    for(int i=0;i<rowCount;i++){
        for(int j=0;j<colCount;j++){
            if(standardModel->item(i,j) != nullptr){
                standardModel->item(i,j)->setText(list[list2[i].second][j]);
            }
        }
    }
}

void teacher_score::modelSort()
{
//双击表头排序
    connect(tableView->horizontalHeader(),&QHeaderView::sectionDoubleClicked,[=](int colIndex)->void{
        qDebug()<<"双击排序";
        if(sortFactor==0){//降序
            sortFactor=1;
        }else{  //升序
            sortFactor=0;
        }
        if(colIndex == 1 || colIndex==3){
            tableView->sortByColumn(colIndex,Qt::SortOrder(sortFactor));    //字符串排序
        }else{
            mySort(colIndex,sortFactor);  //浮点数排序
        }

    });
}


teacher_score::teacher_score(teacher *parent)
    : teacher{parent}
{
    teacher::iniStandardView(HFieldName,VFieldName);
    teacher::createTwoSQL(score_db,"second","score",message_db_tmp,"second2","message");
    teacher_score::createTable();
    teacher::signal_on_model();
    teacher_score::modelSort();
}

teacher_score::~teacher_score()
{
    score_db.close();
    qDebug()<<"析构教师成绩teacher_score";
}
