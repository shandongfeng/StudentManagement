#include "jumpui.h"
#include "signinui.h"



void jumpUi::iniJumpUi()
{
    this->setWindowFlags(Qt::FramelessWindowHint| Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);  //隐藏窗体
    setAttribute(Qt::WA_DeleteOnClose);
    this->setGeometry(xStart,yStart,windowWidth,windowHeight);

    background = new QLabel(this);
    background->setGeometry(0,0,windowWidth,windowHeight);
    movie = new QMovie(":/image/jump.gif");
    background->setScaledContents(true);

    background->setMovie(movie);
    movie->start();
    background->show();

    back = new QPushButton("返回",this);
    back->setGeometry(165,280,100,30);

    signal_on_jumpUi();
}

void jumpUi::signal_on_jumpUi()
{
    connect(back,&QPushButton::clicked,[=]()->void{
        this->close();
        signinUi* signin = new signinUi();
        signin->show();
    });
}


jumpUi::jumpUi(QWidget *parent)
    : QWidget{parent}
{  
    iniJumpUi();
    time = new QTimer(this);
    time->setSingleShot(true);
    time->start(3000);
    connect(time, &QTimer::timeout, this, [=](){
        this->close();
        totalUi* total = new totalUi();
        total->show();
    });

}

jumpUi::~jumpUi()
{
    qDebug()<<"析构跳转界面jumpUi";
}
