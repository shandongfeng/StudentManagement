#include "signinui.h"
#include "totalui.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*a.connect( &a,
               SIGNAL(lastWindowClosed()),
               &a,
               SLOT(quit()));*/
    signinUi* w = new signinUi;
    w->show();
//    totalUi* ui = new totalUi();
//    ui->show();

    return a.exec();
}
