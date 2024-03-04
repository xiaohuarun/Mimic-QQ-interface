#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"customwidget.h"
#include <QMainWindow>
#include<QButtonGroup>
#include <QSystemTrayIcon>
#include"chatstackedwidget.h"
#include"clientsocket.h"
#include"databasemagr.h"
#include<qqcell.h>
#include<QJsonValue>
#include"uipage/chatwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public CustomMoveWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void SetSocket(ClientSocket *tcpSocket, const QString &name);
    void onChildPopMenuDidSelected(QAction *action);
    void onAddFriendMenuDidSelected();
private slots:
    void on_btnWinMin_clicked();
    void SltMainPageChanged(int dex);
    void SltTrayIconMenuClicked(QAction *action);
    void SltTrayIcoClicked(QSystemTrayIcon::ActivationReason reason);
    void SltQuitApp();
    void on_btnWinClose_clicked();
    //QTcpSocket信号要关联的槽函数
    void SltTcpReply(const quint8 &type, const QJsonValue &dataVal);
    void SltTcpStatus(const quint8 &state);
    void SltFriendsClicked(QQCell* qqcell);
    void SltGroupsClicked(QQCell*);
    void onAddFriendMenuDidSelected(QAction *action);
    void onGroupPopMenuDidSelected(QAction *action);
    void SltSendMessage(const quint8 &type, const QJsonValue &json);
    void SltFriendChatWindowClose();
    void PraseAddFriendReply(const QJsonValue dataVal);
    void PraseAddFriendRequistReply(const QJsonValue dataVal);
private:
    Ui::MainWindow *ui;
    // 聊天窗管理
    QList<ChatWindow *> m_chatFriendWindows;
    QList<ChatWindow *> m_chatGroupWindows;
    ClientSocket *m_tcpSocket;
    QButtonGroup *m_btnGroup;
    QSystemTrayIcon *systemTrayIcon;

    void ParseAddGroupReply(const QJsonValue &dataVal);
    void ParseAddGroupRequest(const QJsonValue &dataVal);
    void ParseCreateGroupRepParseAddGroupReplyly(const QJsonValue &dataVal);
    void ParseGetGroupFriendsReply(const QJsonValue &dataVal);
    void ParseRefreshGroupFriendsReply(const QJsonValue &dataVal);
    void ParseGroupMessageReply(const QJsonValue &dataVal);
    void AddMyGroups(const QJsonValue &dataVal);
    void ParseCreateGroupReply(const QJsonValue &dataVal);
     QString GetHeadPixmap(const QString &name) const;

    void InitSysTrayIcon();
    void InitQQListMenu();
};

#endif // MAINWINDOW_H
