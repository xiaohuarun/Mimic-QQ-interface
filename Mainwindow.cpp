#include "Mainwindow.h"
#include "ui_Mainwindow.h"
#include<QMenu>
#include"myapp.h"
#include"databasemagr.h"
#include"QJsonArray"
#include"QJsonObject"
#include"unit.h"
#include"uipage/chatwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    CustomMoveWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);//去掉QT自带的标题框
    //this->setAttribute(Qt::WA_TranslucentBackground);//去掉黑框
    m_btnGroup=new QButtonGroup(this);
    m_btnGroup->addButton(ui->btnFrind,0);
    m_btnGroup->addButton(ui->btnGroup,1);
    m_btnGroup->addButton(ui->btnApplay,3);
    m_btnGroup->addButton(ui->btnConversation,2);
   // connect(m_btnGroup,&QButtonGroup::buttonClicked,this,&MainWindow::SltMainPageChanged);

    connect(m_btnGroup,SIGNAL(buttonClicked(int )),this,SLOT(SltMainPageChanged(int)));
    InitSysTrayIcon();
    //connect(ui->btnWinMin,&QPushButton::clicked,this,&MainWindow::InitSysTrayIcon);
   // connect(ui->btnWinClose,&QPushButton::clicked,this,&MainWindow::InitSysTrayIcon);
    ui->GCStackedWidget->setCurrentIndex(0);//把第一页设置为默认页
    InitQQListMenu();

}
/**
 * @brief MainWindow::InitQQListMenu
 * 添加好友列表菜单
 */
void MainWindow::InitQQListMenu()
{
    //设置菜单
    //设置组菜单
    QMenu *addFriend = new QMenu(this);
    addFriend->addAction(tr("添加好友"));
    addFriend->addAction(tr("刷新"));
    addFriend->addSeparator();
    addFriend->addAction(tr("删除该组"));
    connect(addFriend, SIGNAL(triggered(QAction*)), this, SLOT(onAddFriendMenuDidSelected(QAction*)));
    ui->frindListWidget->setGroupPopMenu(addFriend);//把它放去了frindListWidget
    //connect(addFriend, SIGNAL(triggered(QAction*)), this, SLOT(onAddFriendMenuDidSelected(QAction*)));

    // 设置子菜单
    QMenu *childMenu = new QMenu(this);
    childMenu->addAction(tr("发送即时消息"));
    childMenu->addSeparator();
    childMenu->addAction("移动至黑名单");
    childMenu->addAction("删除联系人");

    QMenu *groupListMenu = new QMenu(tr("移动联系人至"));
    childMenu->addMenu(groupListMenu);

    // childMenu->addAction(tr("创建讨论组"));
    connect(childMenu, SIGNAL(triggered(QAction*)), this, SLOT(onChildPopMenuDidSelected(QAction*)));
    ui->frindListWidget->setChildPopMenu(childMenu);

    //添加默认项
    //好友列表
    QQCell *myFriend = new QQCell;
    myFriend->groupName = QString(tr("我的好友"));
    myFriend->isOpen = false;
    myFriend->type = QQCellType_Group;
    myFriend->name = QString(tr("我的好友"));
    myFriend->subTitle = QString("(0/0)");
    ui->frindListWidget->insertQQCell(myFriend);

    QQCell *blacklist = new QQCell;
    blacklist->groupName = QString(tr("黑名单"));
    blacklist->isOpen = false;
    blacklist->type = QQCellType_Group;
    blacklist->name = QString(tr("黑名单"));
    blacklist->subTitle = QString("(0/0)");
    ui->frindListWidget->insertQQCell(blacklist);

    connect(ui->frindListWidget, SIGNAL(onChildDidDoubleClicked(QQCell*)), this, SLOT(SltFriendsClicked(QQCell*)));

    //组列表
    QMenu *myGroupMenu = new QMenu(this);
    myGroupMenu->addAction(tr("创建讨论组"));
    myGroupMenu->addAction(tr("加入讨论组"));
    myGroupMenu->addAction(tr("删除该组"));
    myGroupMenu->addSeparator();
    connect(myGroupMenu, SIGNAL(triggered(QAction*)), this, SLOT(onGroupPopMenuDidSelected(QAction*)));
    ui->groupListWidget->setGroupPopMenu(myGroupMenu);
    //设置子菜单
    QMenu *groupChildMen = new QMenu(this);
    groupChildMen->addAction(tr("发送即时消息"));
    ui->groupListWidget->setChildPopMenu(groupChildMen);

    //添加默认项
    QQCell *groupCell = new QQCell;
    groupCell->groupName = QString(tr("我的群组"));
    groupCell->isOpen = false;
    groupCell->type = QQCellType_GroupEx;
    groupCell->name = QString(tr("讨论组"));
    groupCell->subTitle = QString("(0/0)");
    ui->groupListWidget->insertQQCell(groupCell);

    connect(ui->groupListWidget, SIGNAL(onChildDidDoubleClicked(QQCell*)), this, SLOT(SltGroupsClicked(QQCell*)));




}

/**
 * @brief MainWindow::onAddFriendMenuDidSelected
 * 添加好友
 * @param action
 */
void MainWindow::onAddFriendMenuDidSelected(QAction *action)
{   qDebug("执行到这");
    if (!action->text().compare(tr("添加好友")))
    {
        QString text = CInputDialog::GetInputText(this, "hua");//创建出来一个弹窗

        if (!text.isEmpty()) {
            // 首先判断该用户是否已经是我的好友了
            if (DataBaseMagr::Instance()->isMyFriend(MyApp::m_nId, text)) {
                CMessageBox::Infomation(this, "该用户已经是你的好友了！");
                return;
          }

            // 构建 Json 对象
            QJsonObject json;
            json.insert("id", m_tcpSocket->GetUserId());
            json.insert("name", text);

            m_tcpSocket->SltSendMessage(AddFriend, json);
        }
    }
    else if (!action->text().compare(tr("刷新")))
    {
        // 上线的时候获取当前好友的状态
        QJsonArray friendArr = DataBaseMagr::Instance()->GetMyFriend(MyApp::m_nId);

        // 组织Jsonarror
        m_tcpSocket->SltSendMessage(RefreshFriends, friendArr);
    }
    else if (!action->text().compare(tr("删除该组")))
    {
        qDebug() << "delete group";
    }
}

void MainWindow::onGroupPopMenuDidSelected(QAction *action)
{
    if (!action->text().compare(tr("创建讨论组")))
    {
        QString text = CInputDialog::GetInputText(this, "我的朋友们");
        if (!text.isEmpty()) {

            // 构建 Json 对象
            QJsonObject json;
            json.insert("id", m_tcpSocket->GetUserId());
            json.insert("name", text);

            m_tcpSocket->SltSendMessage(CreateGroup, json);
        }
    }
    else if (!action->text().compare(tr("加入讨论组")))
    {
        QString text = CInputDialog::GetInputText(this, "我的朋友们");
        if (!text.isEmpty()) {
            // 首先判断是否已经添加该群组了
          //  if (DataBaseMagr::Instance()->isInGroup(text)) {
          //      CMessageBox::Infomation(this, "你已经添加该群组了！");
         //       return;
     // }

            // 构建 Json 对象
            QJsonObject json;
            json.insert("id", MyApp::m_nId);
            json.insert("name", text);

            m_tcpSocket->SltSendMessage(AddGroup, json);
        }
    }
    else if (!action->text().compare(tr("删除该组")))
    {
        qDebug() << "delete group";
    }
}


void MainWindow::PraseAddFriendReply(const QJsonValue dataVal)
{
    if(dataVal.isObject()){
        QJsonObject dataJson =dataVal.toObject();
        int id =dataJson.value("id").toInt();
         QString name =dataJson.value("name").toString();
         int status =dataJson.value("status").toInt();

        QString head =dataJson.value("head").toString();

    QQCell *cell =new QQCell;
    cell->groupName =QString("我的好友");
   // cell->iconPath=QString(":/resource/head/%1").arg(head);
    cell->iconPath =  QString(":/resource/head/%1").arg(head);
    cell->type=QQCellType_Child;
    cell->name=name;
    cell->subTitle=QString("当前用户状态：%1").arg(OnLine==status ?QString("在线") : QString("离线"));
    cell->id=id;
    cell->status= status;
    ui->frindListWidget->insertQQCell(cell);
    }
}

void MainWindow::onChildPopMenuDidSelected(QAction *action)
{
    QQCell *cell = ui->frindListWidget->GetRightClickedCell();
    if (NULL == cell) return;

    if (!action->text().compare(tr("发送即时消息")))
    {
        qDebug() << "send message" << cell->name;
        // 打开对话框
     //   SltFriendsClicked(cell);
    }
    else if (!action->text().compare(tr("移动至黑名单")))
    {
        qDebug() << "balck friend list" << cell->name;
    }
    else if (!action->text().compare(tr("删除联系人")))
    {
        qDebug() << "delete my friend" << cell->name;
        ui->frindListWidget->removeQQCell(cell);
        // 更新数据库
      //  bool bOk = DataBaseMagr::Instance()->DeleteMyFriend(cell->id, MyApp::m_nId);
    //    CMessageBox::Infomation(this, bOk ? tr("用户删除成功！") : tr("用户删除失败！"));
    }
}




//void InitQQListMenu();

//// 右键菜单
//void onAddFriendMenuDidSelected(QAction *action);
//void onGroupPopMenuDidSelected(QAction *action);
//void onChildPopMenuDidSelected(QAction *action);

//// 好友列表点击
//void SltFriendsClicked(QQCell *cell);
//// 群组列表点击
//void SltGroupsClicked(QQCell *cell);




MainWindow::~MainWindow()
{
    delete ui;
    InitSysTrayIcon();
}

void MainWindow::on_btnWinMin_clicked()
{
    this->hide();
}

void MainWindow::SltMainPageChanged(int index)
{
    static int m_index =0;
    if(index==m_index){return;}
    ui->GCStackedWidget->setLength(ui->GCStackedWidget->width(),index>m_index ? ChatStackedWidget::LeftToRight : ChatStackedWidget::RightToLeft);
    ui->GCStackedWidget->start(index);
    m_index=index;
}
/**
 * @brief MainWindow::InitSysTrayIcon
 * 托盘菜单
 */
void MainWindow::InitSysTrayIcon()
{
    systemTrayIcon = new QSystemTrayIcon(this);
    systemTrayIcon->setIcon(QIcon(":/resource/background/app.png"));

    QMenu *m_trayMenu = new QMenu(this);
    m_trayMenu->addAction("我在线上");
    m_trayMenu->addAction("离线");
    m_trayMenu->addSeparator();
    m_trayMenu->addAction("显示主面板");
    m_trayMenu->addSeparator();
    m_trayMenu->addAction("退出");

    systemTrayIcon->setContextMenu(m_trayMenu);
    systemTrayIcon->show();

    connect(systemTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this, SLOT(SltTrayIcoClicked(QSystemTrayIcon::ActivationReason)));
    connect(m_trayMenu, SIGNAL(triggered(QAction*)), this, SLOT(SltTrayIconMenuClicked(QAction*)));
}
// 托盘菜单
void MainWindow::SltTrayIconMenuClicked(QAction *action)
{
    if ("退出" == action->text()) {
        this->hide();
        QTimer::singleShot(100, this, SLOT(SltQuitApp()));
    }
    else if ("显示主面板" == action->text()) {
        this->show();
    }
    else if (!QString::compare("我在线上", action->text()))
    {
        m_tcpSocket->CheckConnected();
    }
    else if (!QString::compare("离线", action->text()))
    {
        m_tcpSocket->ColseConnected();
    }
}
/**
 * @brief MainWindow::SltTrayIcoClicke
 * 托盘菜单
 * @param reason
 */
void MainWindow::SltTrayIcoClicked(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
        case QSystemTrayIcon::DoubleClick:
        {
            if (!this->isVisible()) {
                this->show();
            }
        }
        break;
    default:
        break;
    }
}
void MainWindow::SltQuitApp()
{
    delete ui;
    qApp->quit();
}

void MainWindow::on_btnWinClose_clicked()
{
    this->hide();
}

void MainWindow::SltTcpReply(const quint8 &type, const QJsonValue &dataVal)
{
    //qDebug() << "dataVal:" << dataVal;
    qDebug()<<"type是什么"<<type;
    switch (type) {
        case AddFriend: //服务器返回 主动添加好友的用户 消息
        {
            PraseAddFriendReply(dataVal);
        }
            break;
        case AddFriendRequist: //服务器通知被添加的好友
        {
            //{"head":"2_head_64.png","id":2,"msg":"附加消息： 你好！","name":"milo"}
            PraseAddFriendRequistReply(dataVal);
        }
            break;
        case AddGroup:
        {
            ParseAddGroupReply(dataVal);
        }
            break;
        case AddGroupRequist:
        {
            ParseAddGroupRequest(dataVal);
        }
            break;
        case CreateGroup:
        {
            ParseCreateGroupReply(dataVal);
        }
            break;
        case GetMyGroups:
        {
            ParseGetGroupFriendsReply(dataVal);
        }
            break;
        case RefreshGroups:
        {
            ParseRefreshGroupFriendsReply(dataVal);
        }
            break;
        case SendGroupMsg:
        {
            ParseGroupMessageReply(dataVal);
        }
        break;
    }
}

void MainWindow::ParseCreateGroupReply(const QJsonValue &dataVal)
{   qDebug("创建一个全");
    if (dataVal.isObject()) {
        QJsonObject dataObj = dataVal.toObject();

        int nId = dataObj.value("id").toInt();
        // 未查询到该用户
        if (-1 == nId) {
            CMessageBox::Infomation(this, "该群组已经添加!");
            return;
        }

        QQCell *cell = new QQCell;
        cell->groupName = QString(tr("我的群组"));
        cell->iconPath  = GetHeadPixmap(dataObj.value("head").toString());
        cell->type      = QQCellType_Child;
        cell->name      = dataObj.value("name").toString();
        cell->subTitle  = QString("我的群，我做主...");
        cell->id        = nId;
        cell->status    = OnLine;

        ui->groupListWidget->insertQQCell(cell);

        // 更新至数据库
        DataBaseMagr::Instance()->AddGroup(cell->id, MyApp::m_nId, cell->name);
    }
}
void MainWindow::PraseAddFriendRequistReply(const QJsonValue dataVal){

    if (dataVal.isObject()) {
        QJsonObject dataJson = dataVal.toObject();
        int id = dataJson.value("id").toInt();
        QString name = dataJson.value("name").toString();
        QString head = dataJson.value("head").toString();
        QString msg = dataJson.value("msg").toString();

        qDebug("通知好友");
        if (!DataBaseMagr::Instance()->isMyFriend(MyApp::m_nId, name)) {
            QQCell *cell = new QQCell;
            cell->groupName = QString("我的好友");
            cell->iconPath =  QString(":/resource/head/%1").arg(head);
            cell->type = QQCellType_Child;
            cell->name = name;
            cell->subTitle = QString("当前用户状态: 在线");
            cell->id = id;
            cell->status = OnLine;

            ui->frindListWidget->insertQQCell(cell);

            qDebug() << "MyApp::m_nId:"<<MyApp::m_nId <<" 添加好友, 好友id:" << id;

            //更新数据库
            DataBaseMagr::Instance()->AddFriend(cell->id, MyApp::m_nId, name);
        }

    }



    }








void MainWindow::AddMyGroups(const QJsonValue &dataVal)
{
    // data 的 value 是数组
    if (dataVal.isArray()) {
        QJsonArray array = dataVal.toArray();
        int nSize = array.size();
        for (int i = 0; i < nSize; ++i) {
            QJsonObject jsonObj = array.at(i).toObject();

            QQCell *cell = new QQCell;
            cell->groupName = QString(tr("我的群组"));
            cell->iconPath  = ":/resource/head/1.bmp";
            cell->type      = QQCellType_Child;
            cell->name      = jsonObj.value("name").toString();
            cell->subTitle  = QString("我的群，我做主...");
            cell->id        = jsonObj.value("id").toInt();;
            cell->SetStatus(OnLine);

            ui->groupListWidget->insertQQCell(cell);
        }
    }
}

void MainWindow::SetSocket(ClientSocket *tcpSocket, const QString &name)
{
    if (tcpSocket != NULL) {
        m_tcpSocket = tcpSocket;

        connect(m_tcpSocket, &ClientSocket::signalMessage, this, &MainWindow::SltTcpReply);
        connect(m_tcpSocket, &ClientSocket::signalStatus, this, &MainWindow::SltTcpStatus);
         AddMyGroups(DataBaseMagr::Instance()->GetMyGroup(MyApp::m_nId));
    }
}
void MainWindow::SltTcpStatus(const quint8 &state)
{
}

void MainWindow::SltFriendsClicked(QQCell *cell)
{
    qDebug("看看聊天窗口是否实现");
    ChatWindow *chatwindow =new ChatWindow();
    connect(chatwindow,&ChatWindow::signalSendMessage,m_tcpSocket,&ClientSocket::SltSendMessage);
    connect(chatwindow,&ChatWindow::signalClose,this,&MainWindow::SltFriendChatWindowClose);
    //设置窗口的属性
    chatwindow->SetCell(cell);
    chatwindow->show();
}

//群组点击
void MainWindow::SltGroupsClicked(QQCell *cell)
{
    // 构建 Json 对象
    QJsonObject json;
    json.insert("id", cell->id);
    json.insert("name", cell->name);

    m_tcpSocket->SltSendMessage(GetMyGroups, json);

    // 判断与该用户是否有聊天窗口，如果有弹出窗口
    foreach (ChatWindow *window, m_chatGroupWindows) {
        if (window->GetUserId() == cell->id) {
            window->show();
            return;
        }
    }

    // 没有检索到聊天窗口，直接弹出新窗口
    ChatWindow *chatWindow = new ChatWindow();
    connect(chatWindow, SIGNAL(signalSendMessage(quint8,QJsonValue)), m_tcpSocket, SLOT(SltSendMessage(quint8,QJsonValue)));
    connect(chatWindow, SIGNAL(signalClose()), this, SLOT(SltGroupChatWindowClose()));

    chatWindow->SetCell(cell, 1);
    chatWindow->show();

    // 添加到当前聊天框
    m_chatGroupWindows.append(chatWindow);
}
void MainWindow::SltSendMessage(const quint8 &type, const QJsonValue &json)
{

}
void MainWindow::SltFriendChatWindowClose()
{
    ChatWindow *chatWindow = (ChatWindow*)sender();
    disconnect(chatWindow, SIGNAL(signalSendMessage(quint8,QJsonValue)), m_tcpSocket, SLOT(SltSendMessage(quint8,QJsonValue)));
    disconnect(chatWindow, SIGNAL(signalClose()), this, SLOT(SltFriendChatWindowClose()));

    if (!this->isVisible() && m_chatFriendWindows.size() == 1)
    {
        this->show();
    }

    // 删除聊天窗口
    m_chatFriendWindows.removeOne(chatWindow);

}
QString MainWindow::GetHeadPixmap(const QString &name) const
{
    if (QFile::exists(MyApp::m_strHeadPath + name)) {
        return MyApp::m_strHeadPath + name;
    }

    return ":/resource/head/1.bmp";
}

/**
 * @brief MainWindow::ParseAddGroupReply
 * @param dataVal
 */
void MainWindow::ParseAddGroupReply(const QJsonValue &dataVal)
{
    if (dataVal.isObject()) {
        QJsonObject jsonObj = dataVal.toObject();
        int nId = jsonObj.value("id").toInt();
        if (-1 == nId) {
            CMessageBox::Infomation(this, "未找到该群组!");
            return;
        }

        QQCell *cell = new QQCell;
        cell->groupName = QString(tr("我的群组"));
        cell->iconPath  = GetHeadPixmap(jsonObj.value("head").toString());
        cell->type      = QQCellType_Child;
        cell->name      = jsonObj.value("name").toString();
        cell->subTitle  = QString("我的群，我做主...");
        cell->id        = nId;
        cell->status    = OnLine;

        ui->groupListWidget->insertQQCell(cell);

        // 更新至数据库
        DataBaseMagr::Instance()->AddGroup(nId, MyApp::m_nId, cell->name);
    }
}

void MainWindow::ParseAddGroupRequest(const QJsonValue &dataVal)
{
    if (!dataVal.isObject()) return;
}
/**
 * @brief MainWindow::ParseGroupFriendsReply
 * @param dataVal
 */
void MainWindow::ParseGetGroupFriendsReply(const QJsonValue &dataVal)
{
    // data 的 value 是数组
    if (dataVal.isArray()) {
        QJsonArray array = dataVal.toArray();
        int nGroupId = array.at(0).toInt();

        // 将数据更新至界面
        // 判断与该用户是否有聊天窗口，如果有弹出窗口
        foreach (ChatWindow *window, m_chatGroupWindows) {
            if (window->GetUserId() == nGroupId) {
                window->UpdateUserStatus(dataVal);
                window->show();
                return;
            }
        }
    }
}


/**
 * @brief MainWindow::ParseRefreshGroupFriendsReply
 * 刷新组
 * @param dataVal
 */
void MainWindow::ParseRefreshGroupFriendsReply(const QJsonValue &dataVal)
{
    // data 的 value 是数组
    if (dataVal.isArray()) {
        QJsonArray array = dataVal.toArray();
        int nSize = array.size();
        for (int i = 0; i < nSize; ++i) {
            //            QJsonObject jsonObj = array.at(i).toObject();
            //            int nId = jsonObj.value("id").toInt();
            //            int nStatus = jsonObj.value("status").toInt();

            //            QList<QQCell *> friends = ui->groupListWidget->getCells();
            //            foreach (QQCell *cell, friends.at(0)->childs) {
            //                if (cell->id == nId) {
            //                    cell->SetSubtitle(QString("当前用户状态：%1 ").arg(OnLine == nStatus ? tr("在线") : tr("离线")));
            //                }
            //            }

            //            ui->groupListWidget->upload();
        }
    }
}


/**
 * @brief MainWindow::ParseGroupMessageReply
 * 处理群组ID
 * @param dataVal
 */
void MainWindow::ParseGroupMessageReply(const QJsonValue &dataVal)
{
    // 消息格式为object对象
    if (dataVal.isObject()) {
        QJsonObject dataObj = dataVal.toObject();
        int nId = dataObj.value("group").toInt();

        // 如果收到消息时有聊天窗口存在，直接添加到聊天记录，并弹出窗口
        foreach (ChatWindow *window, m_chatGroupWindows) {
            if (window->GetUserId() == nId) {
                window->AddMessage(dataVal);
                window->show();
                return;
            }
        }

        // 没有检索到聊天窗口，直接弹出新窗口
        QList<QQCell *> groups = ui->groupListWidget->getCells();
        foreach (QQCell *cell, groups.at(0)->childs) {
            // 有列表的才创建
            if (cell->id == nId) {
                ChatWindow *chatWindow = new ChatWindow();
                connect(chatWindow, SIGNAL(signalSendMessage(quint8,QJsonValue)), m_tcpSocket, SLOT(SltSendMessage(quint8,QJsonValue)));
                connect(chatWindow, SIGNAL(signalClose()), this, SLOT(SltGroupChatWindowClose()));

                // 构建 Json 对象
                QJsonObject json;
                json.insert("id", cell->id);
                json.insert("name", cell->name);

                //获取最新用户状态
                m_tcpSocket->SltSendMessage(GetMyGroups, json);


                chatWindow->SetCell(cell, 1);
                chatWindow->AddMessage(dataVal);
                chatWindow->show();
                // 添加到当前聊天框
                m_chatGroupWindows.append(chatWindow);
                return;
            }
        }
    }
}
