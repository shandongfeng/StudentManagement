#include "coursetable.h"

void courseTable::iniStandardView(const QStringList &HFieldName, const QStringList &VFieldName)
{
    this->setWindowFlags(Qt::FramelessWindowHint);  //窗口上方栏消失
    this->setGeometry(xStart,yStart,width,height);
    this->setStyleSheet("background: rgba(255,255,255,100);");

//模型
    standardModel = new QStandardItemModel(this);
//视图
    tableView = new QTableView(this);
    tableView->setGeometry(0,0,width,height);
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
    standardModel->setHorizontalHeaderLabels(HFieldName);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //列宽自填充表格

    standardModel->setVerticalHeaderLabels(VFieldName);
    tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);  //行高自填充表格
//view添加model
    tableView->setModel(standardModel);

}

void courseTable::createSQL(QSqlDatabase &db,const QString& connectionName,const QString &SQLName)
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

void courseTable::createTable()
{
//创建数据库
    QSqlQuery query(courseTable_db);
    //避免表重复创建
    query.exec("select * from courseTable");
    if(query.next() == false){
        //周一到周日课程表信息
        query.exec("create table courseTable(monday text,tuesday text,wednesday text,thursday text,friday text,saturday text,sunday text)");
        qDebug()<<"courseTable.db数据库表已创建";
    }else{
        qDebug()<<"courseTable.db数据库表已存在,无需创建";
        return;
    }
    query.finish();
}

void courseTable::signal_on_model()
{
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
    //导入数据
    connect(action[0],&QAction::triggered,[=]()->void{
        derive_SQL_to_model();
    });
    //导出数据
    connect(action[1],&QAction::triggered,[=]()->void{
        derive_model_to_SQL();
    });
}


courseTable::courseTable(QWidget *parent)
    : QWidget{parent}
{

}

courseTable::~courseTable()
{    
    QVector<QAction*>().swap(action);
    qDebug()<<"析构课程表courseTable";
}
