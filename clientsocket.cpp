#include "clientsocket.h"
#include "databasemagr.h"

#include <QFile>
#include <QDebug>
#include <QHostAddress>
#include <QDataStream>
#include <QApplication>
#include <QJsonObject>
#include <QJsonDocument>
#include<unit.h>
#include"myapp.h"

//#define SERVER_IP "127.0.0.1"
//#define SERVER_PORT 60100

ClientSocket::ClientSocket(QObject *parent) :
    QObject(parent)
{
    m_nId = -1;

    m_tcpSocket = new QTcpSocket(this);
    //text_simple connected and writed
    connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(SltReadyRead()));//读数据
    connect(m_tcpSocket, SIGNAL(connected()), this, SLOT(SltConnected()));//告诉已经连接上服务器
    connect(m_tcpSocket, SIGNAL(disconnected()), this, SLOT(SltDisconnected()));//告诉断开服务器
}

ClientSocket::~ClientSocket()
{
}

/**
 * @brief ClientSocket::GetUserId
 * 获取当前用户id
 * @return
 */
int ClientSocket::GetUserId() const
{
    return  m_nId;
}

/**
 * @brief ClientSocket::SetUserId
 * 设置当前socket的用户id
 * @param id
 */
void ClientSocket::SetUserId(const int &id)
{
    m_nId = id;
}

void ClientSocket::CheckConnected()
{   qDebug("1111准备开始连接");
    if (m_tcpSocket->state() != QTcpSocket::ConnectedState)
    {
        m_tcpSocket->connectToHost(MyApp::m_strHostAddr, MyApp::m_nMsgPort);
       qDebug("22222准备开始连接");
    }
}

/**
 * @brief ClientSocket::ColseConnected
 * 主动断开连接
 */
void ClientSocket::ColseConnected()
{
    if (m_tcpSocket->isOpen()) {
        m_tcpSocket->abort();
    }
}

/**
 * @brief ClientSocket::ConnectToHost
 * 链接服务器接口
 * @param host
 * @param port
 */
void ClientSocket::ConnectToHost(const QString &host, const int &port)
{
    if (m_tcpSocket->isOpen()) m_tcpSocket->abort();
    m_tcpSocket->connectToHost(host, port);
}

/**
 * @brief ClientSocket::ConnectToHost
 * 链接服务器接口
 * @param host
 * @param port
 */
void ClientSocket::ConnectToHost(const QHostAddress &host, const int &port)
{
    if (m_tcpSocket->isOpen()) {
        m_tcpSocket->abort();
    }
    m_tcpSocket->connectToHost(host, port);
}

/**
 * @brief ClientSocket::SltSendMessage
 * tcp socket消息管理
 * @param type
 * @param dataVal
 */
void ClientSocket::SltSendMessage(const quint8 &type, const QJsonValue &dataVal)
{
    // 连接服务器
    if (!m_tcpSocket->isOpen()) {
        m_tcpSocket->connectToHost(MyApp::m_strHostAddr, MyApp::m_nMsgPort);
        m_tcpSocket->waitForConnected(1000);
    }
    // 超时1s后还是连接不上，直接返回
    if (!m_tcpSocket->isOpen()) {
        return;
    }

    // 构建 Json 对象
    QJsonObject json;
    json.insert("type", type);
    json.insert("from", m_nId);
    json.insert("data", dataVal);

    // 构建 Json 文档
    QJsonDocument document;
    document.setObject(json);
    qDebug("发送给服务器");

    qDebug() << "m_tcpSocket->write:" << document.toJson(QJsonDocument::Compact);
    m_tcpSocket->write(document.toJson(QJsonDocument::Compact));
}

/**
 * @brief ClientSocket::SltDisconnected
 */
void ClientSocket::SltDisconnected()
{
    qDebug() << "has disconnecetd";
    m_tcpSocket->abort();
}

/**
 * @brief ClientSocket::SltConnected
 */
void ClientSocket::SltConnected()
{
    qDebug() << "已经连接上服务器has connecetd";
    emit signalStatus(0x01);
}


/**
 * @brief ClientSocket::SltReadyRead
 * 服务器消息处理
 */
void ClientSocket::SltReadyRead()
{   //qDebug() << "这一步"能到达;    //读取socket数据
    QByteArray byRead = m_tcpSocket->readAll();
    QJsonParseError jsonError;
    //转换为JSON文档
    QJsonDocument document = QJsonDocument::fromJson(byRead, &jsonError);
    //解析未发生错误
    if (!document.isNull() && (jsonError.error == QJsonParseError::NoError)) {
        //json文档对象
        if (document.isObject()) {
            //转化为对象
            QJsonObject jsonObj = document.object();
            QJsonValue dataVal = jsonObj.value("data");
            int nFrom = jsonObj.value("from").toInt();
            int nType = jsonObj.value("type").toInt();
            switch(nType){
            case Register:

                  qDebug() << "0x10" ;//注册
                break;
            case Login:             //登录
                paresLongin(dataVal);

            case AddFriend:
                emit signalMessage(AddFriend,dataVal);
                break;
            case AddFriendRequist:
                emit signalMessage(AddFriendRequist,dataVal);
            }

        }
    }
}
//用户登录
void ClientSocket::paresLongin(const QJsonValue &dataVal)
{
        //qDebug() << "text184" ;
        QJsonObject dataObj = dataVal.toObject();
        int id = dataObj.value("id").toInt();
        int code = dataObj.value("code").toInt(); //及时通讯文档
        QString msg = dataObj.value("msg").toString();
        qDebug() << "code的值"<<code;
        qDebug() << "msg的值" <<msg;
        if (code ==-2) {
            qDebug() << "用户以在线:" ;
             emit signalStatus(LoginRepeat);
         // m_nId = id;
        } else if (code ==-1){
            qDebug() << "用户未注册" ;
            emit signalStatus(LoginPasswdError);
    }
        else if (code == 0 && msg =="ok") {
            m_nId=id;
            MyApp::m_nId=id;
               qDebug() << "登录成功" ;
               emit signalStatus(LoginSuccess);
        }

}
