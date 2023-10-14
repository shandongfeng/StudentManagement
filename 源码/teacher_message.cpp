#include "teacher_message.h"

void teacher_message::createTable()
{
//创建数据库
    QSqlQuery query(message_db);
    //避免表重复创建
    query.exec("select * from message");
    if(query.next() == false){
        //"序号"<<"姓名"<<"性别"<<"年龄"<<"班级"<<"学号"<<"学院"<<"专业"<<"年级"<<"寝室"<<"籍贯"<<"联系方式";
        query.exec("create table message(id INTEGER PRIMARY KEY AUTOINCREMENT,name varchar(20),sex varchar(5),age int,classes int,studentID long long int,college varchar(30),major varchar(30),grade varchar(10),bedroom varchar(20),hometown varchar(70),phoneNumber varchar(30))");
        qDebug()<<"message.db数据库表已创建";
    }else{
        qDebug()<<"message.db数据库表已存在,无需创建";
        return;
    }
    query.finish();
}

int teacher_message::SQLCount()
{
    QSqlQuery query(message_db);
    int count=0;
    query.exec("select* from message");
    while(query.next() && ++count);
    query.finish();
    return count;
}

void teacher_message::derive_SQL_to_model()
{
    standardModel->removeRows(0,standardModel->rowCount());
    QSqlQuery query(message_db);
    query.exec("select* from message");
    if(query.next() == false){
        QMessageBox::information(this,"提示","数据库为空，暂时无法导入到model",QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
        query.finish();
        return;
    }
//导入数据库信息到model
    for(int i=0;i<SQLCount();i++,query.next()){
        for(int j=0;j<HFieldName.size();j++){
            standardModel->setItem(i,j,new QStandardItem(query.value(j).toString()));
        }
    }
    QMessageBox::information(this,"提示","数据导入成功",QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
    query.finish();
}

void teacher_message::derive_model_to_SQL()
{
    if(standardModel->rowCount()<=0){
        QMessageBox::information(this,"提示","表格为空，无法导出",QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
        return;
    }
    QSqlQuery query(message_db);
    query.exec("delete from message");
    for(int i=0;i<standardModel->rowCount();i++){
        query.exec(QString("insert into message(id,name,sex,age,classes,studentID,college,major,grade,bedroom,hometown,phoneNumber) values(%1,'%2','%3',%4,%5,%6,'%7','%8','%9','%10','%11','%12')").arg(standardModel->data(QModelIndex(standardModel->index(i,0))).toInt()).arg(standardModel->data(QModelIndex(standardModel->index(i,1))).toString()).arg(standardModel->data(QModelIndex(standardModel->index(i,2))).toString()).arg(standardModel->data(QModelIndex(standardModel->index(i,3))).toInt()).arg(standardModel->data(QModelIndex(standardModel->index(i,4))).toInt()).arg(standardModel->data(QModelIndex(standardModel->index(i,5))).toLongLong()).arg(standardModel->data(QModelIndex(standardModel->index(i,6))).toString()).arg(standardModel->data(QModelIndex(standardModel->index(i,7))).toString()).arg(standardModel->data(QModelIndex(standardModel->index(i,8))).toString()).arg(standardModel->data(QModelIndex(standardModel->index(i,9))).toString()).arg(standardModel->data(QModelIndex(standardModel->index(i,10))).toString()).arg(standardModel->data(QModelIndex(standardModel->index(i,11))).toString()));
    }
    QMessageBox::information(this,"提示","model成功导入数据库",QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
    query.finish();

}

void teacher_message::mySort(const int column,const bool order)
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
                list[i][j] = standardModel->item(i,j)->text();
            }
        }
    }
    qDebug()<<1;
//获取指定列数据
    QVector<QPair<int,int>> list2;
    for(int i=0;i<rowCount;i++){
        if(standardModel->item(i,column) != nullptr){
            list2.push_back({standardModel->item(i,column)->text().toInt(),i});
        }else{
            list2.push_back({-1,i});
        }
    }
    qDebug()<<2;
//排序
    if(order == true){
        sort(list2.begin(),list2.end(),std::greater<QPair<int,int>>());
    }else{
        sort(list2.begin(),list2.end(),std::less<QPair<int,int>>());
    }
    qDebug()<<3;
//将排完序的新数据导入到model
    for(int i=0;i<rowCount;i++){
        for(int j=0;j<colCount;j++){
            if(standardModel->item(i,j) != nullptr){
                standardModel->item(i,j)->setText(list[list2[i].second][j]);
            }else{
                standardModel->setItem(i,j,new QStandardItem(list[list2[i].second][j]));
            }
        }
    }
}

void teacher_message::modelSort()
{
//双击表头排序
    connect(tableView->horizontalHeader(),&QHeaderView::sectionDoubleClicked,[=](int colIndex)->void{
        qDebug()<<"双击排序";
        if(sortFactor==0){//降序
            sortFactor=1;
        }else{  //升序
            sortFactor=0;
        }
        if(colIndex == 0 || colIndex==3 || colIndex==4 || colIndex==5){
            mySort(colIndex,sortFactor);  //整型排序
        }else{
            tableView->sortByColumn(colIndex,Qt::SortOrder(sortFactor));    //字符串排序
        }

    });
}


teacher_message::teacher_message(teacher *parent)
    : teacher{parent}
{
    teacher::iniStandardView(HFieldName,VFieldName);
    teacher::createSQL(message_db,"first","message");
    teacher_message::createTable();
    teacher::signal_on_model();
    teacher_message::modelSort();
}

teacher_message::~teacher_message()
{
    message_db.close();
    qDebug()<<"析构教师信息teacher_message";
}
