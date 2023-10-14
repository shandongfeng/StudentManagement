#include "totalui.h"

#include "signinui.h"

QString totalUi::fileRead(const QString fileAddr)
{
    file = new QFile(fileAddr,this);
    if(file->open(QIODevice::ReadOnly)==false){
        QMessageBox::information(this,"提示","文件无法打开",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
    }
    QString line = file->readLine();      //整行读取
    qDebug()<<"文件里的内容是 = "<<line;
    file->close();
    return line;
}

void totalUi::iniTotalUi()
{
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowTitle("学生信息管理界面");
    this->setGeometry(xStart,yStart,windowWidth,windowHeight);
//整个窗体背景
    total = new QLabel(this);
    total->setGeometry(0,0,windowWidth,windowHeight);
    total->setStyleSheet("border-image: url(:/image/total.jpg);");
//上方标题
    title = new QLabel("学生信息管理系统",this);
    title->setGeometry(400,0,500,50);
    title->setAlignment(Qt::AlignHCenter);
    title->setStyleSheet("QLabel{"
                         "font-size: 40px;"
                         "color: black;"
                         "background:transparent;"
                         "}"

                         "QLabel:hover{"
                         "color: white;"
                         "}"
                         );
//用户身份识别        
    userStatus = new QLabel(this);
    userStatus->setGeometry(20,80,100,30);
    userStatus->setStyleSheet("QLabel{"
                              "font-size: 25px;"
                              "}"

                              "QLabel:hover{"
                              "color: pink;"
                              "}"
                              );


    userName = new QLabel(this);
    userName->setGeometry(150,80,150,30);
    userName->setStyleSheet("QLabel{"
                              "font-size: 25px;"
                              "}"

                            "QLabel:hover{"
                            "color: pink;"
                            "}"
                            );

//搜索框
    search = new QLabel(this);
    search->setGeometry(200,70,1100,50);
    search->setStyleSheet(
                         "QLabel{"
                         "background: transparent;"
                         "}"

                         "QLabel:hover{"

                         "}"
                         );

    searchLine = new QLineEdit(this);
    searchLine->setGeometry(400,70,500,50);
    searchLine->setStyleSheet(
                            "QLineEdit{"
                            "font-size: 30px;"
                            "color: black;"
                            "background: rgba(255,255,255,100);"
                            "border: none;"
                            "}"

                            "QLineEdit:hover{"
                            "background: rgba(255,255,255,100);"
                            "}"
                            );

//刷新
    refresh = new QPushButton("刷新",this);
    refresh->setGeometry(0,700,100,30);
    refresh->setStyleSheet(
                        "QPushButton{"
                        "background: transparent;"
                        "text-align: left;"
                        "font-size: 30px;"
                        "color: green;"
                        "}"

                        "QPushButton:hover{"
                        "color: rgb(0,255,255);"
                        "}"

                        );
//退出
    back = new QPushButton("退出",this);
    back->setGeometry(0,750,100,30);
    back->setStyleSheet(
                        "QPushButton{"
                        "background: transparent;"
                        "text-align: left;"
                        "font-size: 30px;"
                        "color: green;"
                        "}"

                        "QPushButton:hover{"
                        "color: white;"
                        "}"

                        );

}

void totalUi::setUserMessage(const QString& userMessage)
{
    if(userMessage>="20210000"){
        userStatus->setText("学生");
    }else{
        userStatus->setText("教师");
    }
    userName->setText(userMessage);
}

void totalUi::setRightView(const QString& userMessage)
{
    widget = new QStackedWidget(this);
    widget->setGeometry(200,150,1100,650);
//教师修改学生信息
    if(userMessage<="20210000"){
        message1 = new teacher_message();
        widget->addWidget(message1);
        score1 = new teacher_score();
        widget->addWidget(score1);
        courseTable1 = new teacher_courseTable();
        widget->addWidget(courseTable1);
    }
    else{
        message2 = new student_message();
        widget->addWidget(message2);
        score2 = new student_score();
        widget->addWidget(score2);
        courseTable2 = new student_courseTable();
        widget->addWidget(courseTable2);

    }
    widget->hide();
}

void totalUi::setLeftView()
{
//添加视图
    treeWidget = new QTreeWidget(this);
    treeWidget->setGeometry(0,150,200,500);
    treeWidget->setColumnCount(1);
    treeWidget->setHeaderHidden(true);
    treeWidget->setStyleSheet("QTreeWidget{"
                              "background: transparent;"
                              "border: none;"
                              "color: rgb(105,105,105);"
                              "font-size: 20px;"
                              "}"

                              "QTreeWidget:hover{"
                              "background: rgba(255,255,255,100);"
                              "}"
                              );
//建立父目录并保存目录地址
    for(int i=0;i<fName.size();i++){
        QTreeWidgetItem* fItem = new QTreeWidgetItem(treeWidget);
        fItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);//先不设置可编辑Qt::ItemIsEditable
        fItem->setText(0,fName[i]);
        father.push_back(fItem);
    }
//建立第一个父目录下的子目录
    for(int i=0;i<sName1.size();i++){
        QTreeWidgetItem* sItem = new QTreeWidgetItem();
        sItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        sItem->setText(0,sName1[i]);
        father[0]->addChild(sItem);
        son1.push_back(sItem);
    }
//建立第一个父目录下两个子目录的子目录
    for(int i=0;i<gName111.size();i++){
        QTreeWidgetItem* gItem1 = new QTreeWidgetItem();
        gItem1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        gItem1->setText(0,gName111[i]);
        son1[0]->addChild(gItem1);
        grandson11.push_back(gItem1);
    }
    for(int j=0;j<gName111.size();j++){
        QTreeWidgetItem* gItem2 = new QTreeWidgetItem();
        gItem2->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        gItem2->setText(0,gName112[j]);
        son1[1]->addChild(gItem2);
        grandson12.push_back(gItem2);
    }
}

void totalUi::handle_left_signal()
{
    connect(treeWidget,&QTreeWidget::itemClicked,[=](QTreeWidgetItem *item)->void{
        int widgetIndex=100;    //表示要显示的子窗口的索引,初始值为大值，方便下方if判断显示哪个窗口
    //点击哪个窗口之后就显示哪个窗口
        if(userStatus->text() == "教师"){
            if(item == grandson11[0]){
                widgetIndex=0;
            }else if(item == grandson11[1]){
                widgetIndex=1;
            }else if(item == grandson11[2]){
                widgetIndex=2;
            }
        }
        else{
            if(item == grandson12[0]){
                widgetIndex=0;
            }else if(item == grandson12[1]){
                widgetIndex=1;
            }else if(item == grandson12[2]){
                widgetIndex=2;
            }
        }

    //点击窗口显示窗口，如果widget窗口数量小于点击索引，就清空桌面
        if(widgetIndex == 100){
            widget->hide();
        }else{
            widget->setCurrentIndex(widgetIndex);
            widget->show();
        }
    });
//点击刷新
    connect(refresh,&QPushButton::clicked,[=]()->void{
        for(int i=0;i<father.size();i++){
            father[i]->setExpanded(false);
        }
        widget->hide();
        QMessageBox::information(this,"提示","界面刷新",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
    });
//点击退出
    connect(back,&QPushButton::clicked,[=]()->void{
        signinUi* signin = new signinUi();
        signin->show();
        this->close();
    });
}

totalUi::totalUi(QWidget *parent)
    : QMainWindow{parent}
{
    QString clientName = fileRead("zhanghao.txt");
    iniTotalUi();   //初始化主界面    
    setUserMessage(clientName);
    setRightView(clientName); //显示信息的右下方view/model
    setLeftView();      //左边视图
    handle_left_signal();   //处理左边视图的信号
}

totalUi::~totalUi()
{
    QList<QTreeWidgetItem*>().swap(father);
    QList<QTreeWidgetItem*>().swap(son1);
    QList<QTreeWidgetItem*>().swap(grandson11);
    QList<QTreeWidgetItem*>().swap(grandson12);
    qDebug()<<"析构总窗口totalUi";
}
