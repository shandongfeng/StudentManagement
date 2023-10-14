#include "signinui.h"
#include "signupui.h"
#include "findui.h"


void signinUi::open_and_create_Sql(QSqlDatabase& db,const QString connectionName,const QString SQLName)
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
//创建数据库
    QSqlQuery query(user_db);
    //避免表重复创建
    query.exec("select * from user");
    if(query.next() == false){
        //设置账号、密码、手机号即可
        query.exec("create table user(zhanghao text,mima text,phone text)");
        qDebug()<<"user_db数据库表已创建";
    }else{
        qDebug()<<"user_db数据库表已存在,无需创建";
        //QMessageBox::information(this,"警告","user_db数据库表已存在,无需创建",QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
    }
    query.finish();
}

void signinUi::iniSigninUi()
{
    this->setWindowFlags(Qt::FramelessWindowHint| Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);  //隐藏窗体
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setGeometry(xStart,yStart,windowWidth,windowHeight);


//系统托盘
    bottom_tray = new QSystemTrayIcon(this);
    bottom_tray->setIcon(QIcon(":/image/tray.jpg"));
    bottom_tray->setToolTip("学生信息管理系统");

    action1 = new QAction(this);
    action1->setText("返回登录界面");
    action2 = new QAction(this);
    action2->setText("退出");

    menu = new QMenu(this);
    menu->addAction(action1);
    menu->addAction(action2);

    bottom_tray->setContextMenu(menu);
    bottom_tray->show();





//上方动态图
    label1 = new QLabel(this);
    label1->setGeometry(0,0,430,130);

    movie = new QMovie(":/image/2.gif");
    label1->setScaledContents(true);
    label1->setMovie(movie);
    movie->start();
    label1->show();



//窗口左上方logo
    label2 = new QLabel(this);
    label2->setGeometry(0,0,61,51);
    label2->setStyleSheet("QLabel{"
                          "border-image: url(:/image/logo.jpg);"
                          "background: transparent;"
                          "}");
//白色背景
    label4 = new QLabel(this);
    label4->setGeometry(0,130,430,330);
    label4->setStyleSheet("QLabel{"
                          "background: transparent;"
                          "border-image: url(:/image/white.jpg);"
                          "}");

//头像
    /*
    label3 = new QLabel(this);
    label3->setGeometry(215-30,130-50,60,60);
    label3->setStyleSheet(
                          "background: transparent;"
                          "border-image: url(:/image/touxiang.jpg);"
                          "border-width: 0px;"
                          "border-radius: 33px;"
                          "border-style: solid;"
                          "border-color: rgb(255,255,255);"
                          );
    */
//最小化
    small = new QToolButton(this);
    small->setGeometry(windowWidth-50,0,20,20);
    //small->setIcon(QIcon(":/image/small.jpg"));
    small->setStyleSheet("QToolButton{"
                    "background: transparent;"
                    "image: url(:/image/small.jpg);"
                    "}");


//关闭
    shut = new QToolButton(this);
    shut->setGeometry(windowWidth-20,0,20,20);
    shut->setIcon(QIcon(":/image/close.jpg"));
    shut->setStyleSheet("QToolButton{"
                    "background: transparent;"
                    "}");



//账号
    combobox1 = new QComboBox(this);
    combobox1->setGeometry(102,160,241,30);
    QSqlQuery query(user_db);
    query.exec("select* from user");
    while(query.next()){
        combobox1->addItem(query.value(0).toString());
    }
    query.finish();
    combobox1->setStyleSheet("QComboBox{"
                             "background: transparent;"
                             "border: none;"
                             "}"

                             "QComboBox::down-arrow{"
                             "image: url(:/image/combobox1.jpg);"
                             "}"

                             "QComboBox QAbstractItemView {"
                             "outline: 0px solid gray;"   /* 选定项的虚框 */
                             "border: 1px solid gray;"   /* 整个下拉窗体的边框 */
                             "color: black;"
                             "background-color: white;"   /* 整个下拉窗体的背景色 */
                             "selection-background-color: blue;"   /* 整个下拉窗体被选中项的背景色 */
                             "padding-left:0px;" /*边距（还有其他方向边距设置方式）*/
                             "}");


    line1 = new QLineEdit(this);
    line1->setGeometry(102,160,221,30);
    line1->setPlaceholderText("请输入学号");
    QAction* a = new QAction(this);
    a->setIcon(QIcon(":/image/user.jpg"));
    line1->addAction(a,QLineEdit::LeadingPosition);
    line1->setStyleSheet("QLineEdit{"
                         "border: none;"
                         "}");

//密码
    combobox2 = new QComboBox(this);
    combobox2->setGeometry(102,200,241,30);
    combobox2->setStyleSheet("QComboBox{"
                             "background: transparent;"
                             "border: none;"
                             "}"

                             "QComboBox::down-arrow {"
                             "background: transparent;"
                             "}");

    line2 = new QLineEdit(this);
    line2->setGeometry(102,200,221,30);
    line2->setPlaceholderText("请输入密码");
    line2->setEchoMode(QLineEdit::Password);
    QAction* b = new QAction(this);
    b->setIcon(QIcon(":/image/lock.jpg"));
    line2->addAction(b,QLineEdit::LeadingPosition);
    line2->setStyleSheet("QLineEdit{"
                         "border: none;"
                         "}");


//自动登录
    checkbox1 = new QCheckBox("自动登录",this);
    checkbox1->setGeometry(102,240,71,18);


//记住密码
    checkbox2 = new QCheckBox("记住密码",this);
    checkbox2->setGeometry(200,240,71,18);

//忘记密码
    backMima = new QPushButton("忘记密码",this);
    backMima->setGeometry(285,240,61,18);
    backMima->setStyleSheet("QPushButton{"
                          "border: none;"
                          "}"

                          "QPushButton::hover{"
                          "color: red"
                          "}");




//登录
    signin = new QPushButton("登录",this);
    signin->setGeometry(102,280,241,30);
    signin->setStyleSheet("QPushButton{"
                          "background-color: rgb(10,192,255);"
                          "color: white;"
                          "}");

//注册账号
    signup = new QPushButton("注册账号",this);
    signup->setGeometry(10,302,51,21);
    signup->setStyleSheet("QPushButton{"
                          "border: none;"
                          "}"

                          "QPushButton::hover{"
                          "color: red"
                          "}");



}

void signinUi::fileWrite(const QString fileAddr)
{
    if (!QFile::exists(fileAddr)){
        qDebug()<<111;
    }

    file = new QFile(fileAddr,this);

    if(file->open(QIODevice::ReadWrite | QIODevice::Truncate)==false){  //读写+每次打开文件都对其初始化
        QMessageBox::information(this,"提示","文件无法打开",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
    }
    QString s =line1->text();
    file->write(s.toStdString().c_str());   //写入的数据一直在缓冲区
    file->flush();  //清空缓冲区，才能让数据导入到txt
    file->close();
}

void signinUi::deskSignal()
{
//最小化（系统托盘图标）
    connect(action1,&QAction::triggered,[=]()->void{
        this->show();
    });
//关闭（系统托盘图标）
    connect(action2,&QAction::triggered,[=]()->void{
        this->close();
    });


//最小化
    connect(small,&QToolButton::clicked,[=]()->void{
        this->hide();
        qDebug()<<"登录窗口最小化";
    });
//关闭
    connect(shut,&QToolButton::clicked,this,[=]()->void{
        this->close();
        qDebug()<<"登录窗口关闭";
    });


//combobox下拉框的指定数据输出到lineEdit中
    connect(combobox1,static_cast<void (QComboBox::*)(int index)>(&QComboBox::activated),[=](int index)->void{
        line1->setText(combobox1->itemText(index));
    });

//注册账号
    connect(signup,&QPushButton::clicked,[=]()->void{
        this->close();
        signupUi* ui = new signupUi();
        ui->show();
    });
//忘记密码
    connect(backMima,&QPushButton::clicked,[=]()->void{
        this->close();
        findUi* ui = new findUi();
        ui->show();
    });
//登录
    connect(signin,&QPushButton::clicked,[=]()->void{
        QString s1=line1->text(),s2=line2->text();
        if(s1==nullptr || s2==nullptr){
            QMessageBox::information(this,"警告","账号或密码不能为空",QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
            return;
        }
        QSqlQuery query(user_db);
        qDebug()<<"登录账号 = "<<s1<<"  登录密码 = "<<s2;
        query.exec(QString("select* from user where zhanghao = '%1' and mima = '%2'").arg(line1->text()).arg(line2->text()));
        if(query.next() == false){
            QMessageBox::information(this,"警告","账号或密码输入错误,请重新输入",QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
            return;
        }
        query.finish();
//记录此时登录的用户
        fileWrite("zhanghao.txt");    //保存账号信息到txt，为了在total判断访客身份
//跳转到信息管理界面
        jump = new jumpUi();
        jump->show();
        this->close();
    });
//自动登录
    connect(checkbox1,static_cast<void (QCheckBox::*)(int index)>(&QCheckBox::stateChanged),[=](int index)->void{
        qDebug()<<"checkbox1 = "<<index;
    });
//记住密码
    connect(checkbox2,&QCheckBox::stateChanged,[=](int index)->void{
        qDebug()<<"checkbox2 = "<<index;
    });

}

signinUi::signinUi(QWidget *parent)
    : QWidget(parent)
{       
    open_and_create_Sql(user_db,"signin","user");  //打开并创建数据库
    iniSigninUi();  //初始化登录界面
    deskSignal();   //界面信号与槽    
}

signinUi::~signinUi()
{
    user_db.close();

    qDebug()<<"析构登录界面signinUi";
}
//鼠标事件
void signinUi::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        isClicked = true;
        point = event->globalPos();
    }
}

void signinUi::mouseMoveEvent(QMouseEvent *event)
{
    if(isClicked){
        move(x()+(event->globalPos().x()-point.x()),y()+(event->globalPos().y()-point.y()));
        point = event->globalPos();
    }
}

void signinUi::mouseReleaseEvent(QMouseEvent *event)
{
    move(x()+event->globalPos().x()-point.x(),y()+event->globalPos().y()-point.y());
    isClicked = false;
}

