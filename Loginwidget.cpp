#include "LoginWidget.h"
#include "ui_Loginwidget.h"
#include<QFile>
#include<QDebug>
#include"Mainwindow.h"
#include"clineedit.h"
#include<QString>
#include<QPixmap>
#include<QJsonDocument>
#include<clineedit.h>
#include<unit.h>
#include<QJsonObject>
LoginWidget::LoginWidget(QWidget *parent) :
    CustomMoveWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);

    this->setWindowFlag(Qt::FramelessWindowHint);//去掉QT自带的标题框
    this->setAttribute(Qt::WA_TranslucentBackground);//去掉黑框
    QFile file(":/qss/resource/qss/default.css");
    file.open(QIODevice::ReadOnly);
    //this->setStyleSheet("color: #31A66B");
    //设置样式表
    qApp->setStyleSheet(file.readAll());
    file.close();

    ui->labelWinTitle->setText("用户登录");
    ui->lineEditUser->SetIcon(QPixmap(":/resource/common/ic_user.png"));
       ui->lineEditPasswd->SetIcon(QPixmap(":/resource/common/ic_lock.png"));

    m_tcpSocket =new ClientSocket;
   // m_tcpSocket->CheckConnected();
    connect(m_tcpSocket,&ClientSocket::signalMessage,this,&LoginWidget::OnsignalMessage);
     connect(m_tcpSocket,&ClientSocket::signalStatus,this,&LoginWidget::OnsignalStatus);
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::on_btnWinMenu_clicked()
{
    ui->stackedWidget->setStartVal(0);   //翻转的起始值
      ui->stackedWidget->setEndVal(180);     //翻转的结束值
       //动画效果
       ui->stackedWidget->animation(1);
}

void LoginWidget::on_btnCancel_clicked()
{
    ui->stackedWidget->setStartVal(0);   //翻转的起始值
      ui->stackedWidget->setEndVal(-180);     //翻转的结束值
       //动画效果
      ui->stackedWidget->animation(0);
}

void LoginWidget::on_btnLogin_clicked()
{
    m_tcpSocket->CheckConnected();
    QString username=ui->lineEditUser->text();
    auto userpass=ui->lineEditPasswd->text();
    QJsonObject json;
    json.insert("name", username);
    json.insert("passwd", userpass);

    m_tcpSocket->SltSendMessage(17,json);



   // auto w=new MainWindow(this);
   // auto w=new MainWindow;
  //  w->show();
    //  this->hide();
}

void LoginWidget::OnsignalMessage(const quint8 &type, const QJsonValue &dataVal)
{

}

void LoginWidget::OnsignalStatus(const quint8 &state)
{   if(state ==ConnectedHost) ui->labelWinTitle->setText("已经连接上服务器");
    switch (state) {


    case LoginSuccess:
        //用户登录成功
         {
        disconnect(m_tcpSocket, &ClientSocket::signalMessage, this, &LoginWidget::OnsignalMessage);
        disconnect(m_tcpSocket, &ClientSocket::signalStatus, this, &LoginWidget::OnsignalStatus);
        qDebug("用户登录成功");
        auto w=new MainWindow;
           // auto w=new MainWindow;
         w->SetSocket(m_tcpSocket, ui->lineEditUser->text());
            w->show();
            this->hide();}
        break;
    case LoginPasswdError:
        qDebug() << "可是用户未注册" ;//用户文注册
         break;
    case LoginRepeat:  qDebug("可是用户已经登录了阿");                //用户已在线
         break;
    }
}
