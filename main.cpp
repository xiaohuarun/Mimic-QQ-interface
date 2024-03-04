#include "Mainwindow.h"
#include <QApplication>
#include"LoginWidget.h"
int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    //MainWindow w;
//    LoginWidget l;
//    l.show();
//   //w.show();
    QApplication a(argc, argv);

    DataBaseMagr::Instance()->OpenUserDb("user.db");
    DataBaseMagr::Instance()->OpenMessage("msg.db");
    LoginWidget w;
    //myHelper::FormInCenter(&w);
    w.show();

    return a.exec();
}
