#include "teacher.h"

void teacher::iniStandardView(const QStringList &HFieldName, const QStringList &VFieldName)
{
    this->setWindowFlags(Qt::FramelessWindowHint);  //窗口上方栏消失
    this->setGeometry(teacher::xStart,teacher::yStart,teacher::width,teacher::height);
    this->setStyleSheet("background: rgba(255,255,255,100);");

//模型
    standardModel = new QStandardItemModel(this);
//视图
    tableView = new QTableView(this);
    tableView->setGeometry(0,0,teacher::width,teacher::height);
    tableView->setStyleSheet(
                                "QTableView{"
                                "background: transparent;"
                                "border: none;"
                                "font-size: 20px;"
                                "color: black;"

                                "}"

                                "QTableView:hover{"
                                //"background: rgba(255,255,255,100);"
                                "}"

                                "QTableView::item:selected{"
                                "background: rgba(255,255,255,100);"
                                "}"

                                "QHeaderView::section{"
                                "background: rgba(255,255,255,100);"
                                "color: green;"
                                "font-size: 15px;"
                                "}"
                                );
    if(HFieldName.size()>0){
        standardModel->setHorizontalHeaderLabels(HFieldName);
        tableView->horizontalHeader()->setHidden(false);
        tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents); //自适应列宽
        tableView->horizontalHeader()->setMinimumSectionSize(100);      //列宽最小值
    }else{
        tableView->horizontalHeader()->setHidden(true);
    }

    if(VFieldName.size()>0){
        standardModel->setVerticalHeaderLabels(VFieldName);
        tableView->verticalHeader()->setHidden(false);
        tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Interactive);  //自适应行高
        tableView->verticalHeader()->setMinimumSectionSize(30);      //行高最小值
    }else{
        tableView->verticalHeader()->setHidden(true);
    }
//view添加model
    tableView->setModel(standardModel);
}

void teacher::mySort(const int column, const bool order)
{
//无
}

void teacher::createSQL(QSqlDatabase &db,const QString& connectionName,const QString &SQLName)
{
//打开数据库
    if(QSqlDatabase::contains("qt_sql_default_connection"))
        db = QSqlDatabase::database("qt_sql_default_connection");
    else
        db = QSqlDatabase::addDatabase("QSQLITE",connectionName);
    db.setDatabaseName(SQLName+".db");
    if(db.open()){
        qDebug()<<SQLName+"_db数据库已打开";
    }else{
        QMessageBox::information(this,"警告",db.lastError().text(),QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
        return;
    }
}

void teacher::createTwoSQL(QSqlDatabase &db, const QString &connectionName, const QString &SQLName, QSqlDatabase &db2, const QString &connectionName2, const QString &SQLName2)
{
//打开数据库
    if(QSqlDatabase::contains("qt_sql_default_connection")){
        db = QSqlDatabase::database("qt_sql_default_connection");
        db2 = QSqlDatabase::database("qt_sql_default_connection");
    }
    else{
        db = QSqlDatabase::addDatabase("QSQLITE",connectionName);
        db2 = QSqlDatabase::addDatabase("QSQLITE",connectionName2);
    }
    db.setDatabaseName(SQLName+".db");
    db2.setDatabaseName(SQLName2+".db");
    if(db.open() && db2.open()){
        qDebug()<<SQLName+"_db数据库和"+SQLName2+"_db数据库已打开";
    }else{
        QMessageBox::information(this,"警告",db.lastError().text()+"   "+db2.lastError().text(),QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
        return;
    }
}

void teacher::signal_on_model()
{
//view和model发出信号    
    //单击单元格————获取单元格索引
    connect(tableView,&QTableView::clicked,[=](const QModelIndex& index)->void{
        qDebug()<<"单击单元格:"<<index.row()<<"  "<<index.column();
        tableView->setSelectionBehavior(QAbstractItemView::SelectItems);    //设置单个单元格高亮
    });
    //双击单元格——记录单元格被修改之前的数据
    connect(tableView,&QTableView::doubleClicked,[=](const QModelIndex& index)->void{
        cellData.oldString = index.data().toString();
        cellData.oldStringPoint.rx()=index.row();
        cellData.oldStringPoint.ry()=index.column();
        qDebug()<<"双击单元格 "<<index.row()<<"  "<<index.column();
        standardModel->clearItemData(index);
    });
    //单元格数据改变——传递单元格被修改以及修改内容的信号
    connect(standardModel,&QStandardItemModel::dataChanged,[=](const QModelIndex& left,const QModelIndex& right,const QVector<int>& roles)->void{
        if(left==right){
            if(cellData.oldString != standardModel->item(left.row(),left.column())->text() && left.row() == cellData.oldStringPoint.x() && left.column() == cellData.oldStringPoint.y()){
                qDebug()<<"被修改单元格 = 第 "<<left.row()<<"行   "<<standardModel->horizontalHeaderItem(left.column())->text();
            }
        }else{
            qDebug()<<"操作多个单元格";
        }
    });

//右键点击model弹出菜单
    //初始化菜单并添加行为
    menu = new QMenu(this);
    for(int i=0;i<action.size();i++){
        menu->addAction(action[i]);
        action[i]->setObjectName(action[i]->text());
    }
    //识别鼠标右键并弹出菜单
    tableView->setContextMenuPolicy(Qt::CustomContextMenu); //不设置该语句，右键菜单无法弹出
    connect(tableView, &QTableView::customContextMenuRequested,[=]()->void{
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows); //整行被选中高亮
        menu->exec(cursor().pos());//显示菜单栏
    });
//识别菜单行为
    //增加一行
    connect(action[0],&QAction::triggered,[=]()->void{
        int index = tableView->currentIndex().row();
        qDebug()<<"teacher::signal_on_model  "<<index;
        if(index==-1 || index==0){
            standardModel->insertRows(0,1);
        }else{
            standardModel->insertRows(index+1,1);
        }
        qDebug()<<"添加新行成功";
    });
    //删除一行
    connect(action[1],&QAction::triggered,[=]()->void{
        if(standardModel->rowCount()<=0){
            QMessageBox::information(this,"警告","当前model为空,无法删除",QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
            return;
        }
        standardModel->removeRow(tableView->currentIndex().row());
        qDebug()<<"删除成功";
    });
    //导入数据
    connect(action[2],&QAction::triggered,[=]()->void{
        derive_SQL_to_model();
    });
    //导出数据
    connect(action[3],&QAction::triggered,[=]()->void{
        derive_model_to_SQL();
    });

}

teacher::teacher(QWidget *parent)
    : QWidget{parent}
{

}

teacher::~teacher()
{
    QVector<QAction*>().swap(action);
    qDebug()<<"析构教师teacher";
}
