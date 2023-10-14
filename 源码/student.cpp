#include "student.h"

QString student::getStudentID(const QString fileAddr)
{
    file = new QFile(fileAddr,this);
    if(file->open(QIODevice::ReadOnly)==false){ //只读
        QMessageBox::information(this,"提示","文件无法打开",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
    }
    QString line = file->readLine();      //整行读取
    qDebug()<<"getStudentID 文件里的内容是 = "<<line;
    file->close();
    return line;
}

void student::iniStandardView(const QStringList& HFieldName,const QStringList& VFieldName)
{
    this->setWindowFlags(Qt::FramelessWindowHint);  //窗口上方栏消失
    this->setGeometry(student::xStart,student::yStart,student::width,student::height);
    this->setStyleSheet("background: rgba(255,255,255,100);");

//模型
    standardModel = new QStandardItemModel(this);
    standardModel->setVerticalHeaderLabels(HFieldName);

//视图
    tableView = new QTableView(this);
    tableView->setGeometry(0,0,student::width,student::height);
    tableView->horizontalHeader()->setHidden(true);
    tableView->setStyleSheet(
                                "QTableView{"
                                "background: transparent;"
                                "border: none;"
                                "color: pink;"
                                "font-size: 20px"
                                "}"

                                "QTableView:hover{"
                                "background: rgba(255,255,255,100);"
                                "}"

                                "QHeaderView::section{"
                                "background: rgba(255,255,255,100);"
                                "color: green;"
                                "font-size: 20px;"
                                "}"

                                "QTableView::item:selected{"
                                "background: rgba(255,255,255,100);"
                                "}"
                                );

    if(HFieldName.size()>0){
        standardModel->setHorizontalHeaderLabels(HFieldName);
        tableView->horizontalHeader()->setHidden(false);
        tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }else{
        tableView->horizontalHeader()->setHidden(true);
        tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }

    if(VFieldName.size()>0){
        standardModel->setVerticalHeaderLabels(VFieldName);
        tableView->verticalHeader()->setHidden(false);
        tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }else{
        tableView->verticalHeader()->setHidden(true);
    }


    tableView->setModel(standardModel);
}

void student::createSQL(QSqlDatabase &db, const QString &connectionName, const QString &SQLName)
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

void student::signal_on_model(const QString& studentID)
{
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
        derive_SQL_to_model(studentID);
    });
    //导出数据
    connect(action[1],&QAction::triggered,[=]()->void{
        derive_model_to_SQL(studentID);
    });
}


student::student(QWidget *parent)
    : QWidget{parent}
{
}

student::~student()
{
    QVector<QAction*>().swap(action);
    qDebug()<<"析构学生student";
}
