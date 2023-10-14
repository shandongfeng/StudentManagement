#include "signupui.h"
#include "signinui.h"

void signupUi::openSql(QSqlDatabase& db,const QString connectionName,const QString SQLName)
{
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

void signupUi::iniSignupUi()
{
    setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowTitle("注册账号");
    this->setGeometry(xStart,yStart,windowWidth,windowHeight);
//背景
    background = new QLabel(this);
    background->setGeometry(0,0,windowWidth,windowHeight);
    movie = new QMovie(this);
    movie->setFileName(":/image/signup.gif");
    background->setScaledContents(true);
    background->setMovie(movie);
    movie->start();
    background->show();

//输入账号
    zhanghao = new QLabel("请输入账号:",this);
    zhanghao->setGeometry(100,100,150,30);

    zhanghaoInput = new QLineEdit(this);
    zhanghaoInput->setGeometry(200,100,250,30);

//输入密码
    mima = new QLabel("请输入密码:",this);
    mima->setGeometry(100,200,150,30);

    mimaInput = new QLineEdit(this);
    mimaInput->setGeometry(200,200,250,30);
    mimaInput->setEchoMode(QLineEdit::Password);

//再次确认密码
    mimaAgain = new QLabel("请再次输入密码:",this);
    mimaAgain->setGeometry(100,300,150,30);

    mimaAgainInput = new QLineEdit(this);
    mimaAgainInput->setGeometry(200,300,250,30);
    mimaAgainInput->setEchoMode(QLineEdit::Password);

//手机号
    phone = new QLabel("请输入手机号:",this);
    phone->setGeometry(100,400,150,30);

    phoneInput = new QLineEdit(this);
    phoneInput->setGeometry(200,400,250,30);

//注册
    signup = new QPushButton("注册",this);
    signup->setGeometry(100,500,100,30);

//登录
    back = new QPushButton("返回",this);
    back->setGeometry(350,500,100,30);

}

bool signupUi::derive_data_to_sql()
{
    QString s1=zhanghaoInput->text(),s2=mimaInput->text(),s3=mimaAgainInput->text(),s4=phoneInput->text();
//输入不能为空
    if(s1==nullptr || s2==nullptr ||  s3==nullptr ||  s4==nullptr){
        QMessageBox::information(this,"警告","输入不能为空",QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
        return false;
    }
//两次密码输入要一致
    if(s2 != s3){
        QMessageBox::information(this,"警告","两次密码输入不一致，请重新输入",QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
        return false;
    }
    qDebug()<<"账号 = "<<s1<<" 密码 = "<<s2<<" 二次密码 = "<<s3<<" 手机号 = "<<s4;

    QSqlQuery query(user_db);
//一个账号只能注册一次
    query.exec(QString("select* from user where zhanghao = '%1'").arg(s1));
    if(query.next() == true){
        QMessageBox::information(this,"警告","该账号已注册,请重新注册",QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
        return false;
    }
//一个手机号注册一个账号
    query.exec(QString("select* from user where phone = '%1'").arg(s4));
    if(query.next() == true){
        QMessageBox::information(this,"警告","该手机号已注册,请输入新手机号",QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
        return false;
    }
//将注册信息导入到数据库
    query.exec(QString("insert into user(zhanghao,mima,phone) values('%1','%2','%3')").arg(s1).arg(s2).arg(s4));
    QMessageBox::information(this,"提示","注册成功",QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);

    query.finish();
    return true;
}

void signupUi::deskSignal()
{
    connect(signup,&QPushButton::clicked,[=]()->void{
        if(derive_data_to_sql()==true){//新用户信息成功导入到数据库
            this->close();
            signinUi* ui = new signinUi();
            ui->show();
        }
    });
    connect(back,&QPushButton::clicked,[=]()->void{
        this->close();
        signinUi* ui = new signinUi();
        ui->show();
    });
}

signupUi::signupUi(QWidget *parent)
    : QWidget{parent}
{
    openSql(user_db,"signup","user");  //打开数据库无需创建
    iniSignupUi();   //初始化注册界面
    deskSignal();   //桌面信号触发
}


signupUi::~signupUi(){
    user_db.close();
    qDebug()<<"注册界面被析构signupUi";
}
