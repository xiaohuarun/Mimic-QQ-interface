#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H
#include"customwidget.h"
#include <QWidget>
#include"Mainwindow.h"
#include"clineedit.h"
#include"clientsocket.h"
namespace Ui {
class LoginWidget;
}

class LoginWidget : public CustomMoveWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();
private slots:
    void on_btnWinMenu_clicked();
    void on_btnCancel_clicked();
    void on_btnLogin_clicked();
    void OnsignalMessage(const quint8 &type, const QJsonValue &dataVal);
    void OnsignalStatus(const quint8 &state);
private:
    Ui::LoginWidget *ui;
    ClientSocket *m_tcpSocket;
};

#endif // LOGINWIDGET_H
