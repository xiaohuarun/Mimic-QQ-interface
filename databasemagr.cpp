#include "databasemagr.h"

#include <QDebug>
#include<QJsonArray>
DataBaseMagr *DataBaseMagr::self = NULL;

DataBaseMagr::DataBaseMagr(QObject *parent) :
    QObject(parent)
{

}

DataBaseMagr::~DataBaseMagr()
{
    if (userdb.isOpen()) {
        userdb.close();
    }
}

/**
 * @brief DataBaseMagr::OpenDb
 * 打开数据库
 */
bool DataBaseMagr::OpenUserDb(const QString &dataName)
{
    userdb = QSqlDatabase::addDatabase("QSQLITE", "connectionUser");
    userdb.setDatabaseName(dataName);
    if (!userdb.open()) {
        qDebug() << "Open sql failed";
        return false;
    }

    // 添加数据表
    QSqlQuery query(userdb);

    // 创建我的好友表 id为好友id，userid为当前用户id
    query.exec("CREATE TABLE FRIEND (id INT, userId INT, name varchar(50))");

    // 创建群组表 id为群组id，userid为当前用户id
    query.exec("CREATE TABLE MYGROUP (id INT, userId INT, name varchar(50))");

    // 用户数据保存
    query.exec("CREATE TABLE USERINFO (id INT, name varchar(50), passwd varchar(50))");

    return true;
}

bool DataBaseMagr::OpenMessage(const QString &dataName)
{
    msgdb = QSqlDatabase::addDatabase("QSQLITE", "connectionMsg");
    msgdb.setDatabaseName(dataName);
    if (!msgdb.open()) {
        qDebug() << "Open sql failed";
        return false;
    }

    // 添加数据表
    QSqlQuery query(msgdb);
    // 创建历史聊天表
    query.exec("CREATE TABLE MSGINFO (id INT PRIMARY KEY, userId INT, name varchar(20),"
               "head varchar(50), datetime varchar(20), filesize varchar(30),"
               "content varchar(500), type INT, direction INT)");

    return true;
}
bool DataBaseMagr::isMyFriend(const int &id,const QString &name){
    QString strQuery ="SELECT [id] FROM FRIEND";
    strQuery.append(QString("WHERE name=%1").arg(name));
    strQuery.append(QString("AND userID=%1").arg(QString::number(id)));

    QSqlQuery query(strQuery,userdb);

    return query.next();
}
QJsonArray DataBaseMagr::GetMyFriend(const int &userId){
    QJsonArray myFriends;
    QString strQuery = "SELECT [id] FROM FRIEND";
    strQuery.append(QString("WHERE userId=%1;").arg(QString::number(userId)));

    QSqlQuery query(strQuery, userdb);
    while (query.next()) {
        myFriends.append(query.value("id").toInt());
    }

    return myFriends;
}
void DataBaseMagr::AddFriend(const int &friendId, const int &userId, const QString &name)
{
    QString strQuery = "SELECT [id] FROM FRIEND";
    strQuery.append(QString("WHERE id=%1").arg(QString::number(friendId)));
    strQuery.append(QString(" AND userId=").arg(QString::number(userId)));

    QSqlQuery query(strQuery, userdb);
    if (query.next()) {
        //该用户有此好友了，不需要添加
        qDebug() << "好友已存在";
        return;
    }

    query.prepare("INSERT INTO FRIEND(id, userId, name) values (?, ?, ?)");
    query.bindValue(0, friendId);
    query.bindValue(1, userId);
    query.bindValue(2, name);
    query.exec();
}
/**
 * @brief DataBaseMagr::AddHistoryMsg
 * 添加历史记录
 * @param userId
 * @param itemInfo
 */
void DataBaseMagr::AddHistoryMsg(const int &userId, ItemInfo *itemInfo)
{
    // 查询数据库
    QSqlQuery query("SELECT [id] FROM MSGINFO ORDER BY id DESC;", msgdb);
    int nId = 0;
    // 查询最高ID
    if (query.next()) {
        nId = query.value(0).toInt();
    }

    // 根据新ID重新创建用户
    query.prepare("INSERT INTO MSGINFO (id, userId, name, head, datetime, filesize, content, type, direction) "
                  "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?);");

    query.bindValue(0, nId + 1);
    query.bindValue(1, userId);
    query.bindValue(2, itemInfo->GetName());
    query.bindValue(3, itemInfo->GetStrPixmap());
    query.bindValue(4, itemInfo->GetDatetime());
    query.bindValue(5, itemInfo->GetText());
    query.bindValue(6, itemInfo->GetFileSizeString());
    query.bindValue(7, itemInfo->GetOrientation());
    query.bindValue(8, itemInfo->GetMsgType());

    query.exec();
}
/**
 * @brief DataBaseMagr::GetMyGroup
 * 获取我所在的群组
 * @return
 */
QJsonArray DataBaseMagr::GetMyGroup(const int &userId) const
{
    QJsonArray  myGroup;

    QString strQuery = "SELECT [id],[name] FROM MYGROUP ";
    strQuery.append("WHERE userId=");
    strQuery.append(QString::number(userId));

    QSqlQuery query(strQuery, userdb);
    while (query.next()) {
        QJsonObject jsonObj;
        jsonObj.insert("id", query.value(0).toInt());
        jsonObj.insert("name", query.value(1).toString());
        myGroup.append(jsonObj);
    }

    return myGroup;
}

/**
 * @brief DataBaseMagr::AddGroup
 * 添加我的群组
 * @param id
 * @param name
 */
void DataBaseMagr::AddGroup(const int &id, const int &userId, const QString &name)
{
    QString strQuery = "SELECT [id] FROM MYGROUP ";
    strQuery.append("WHERE id=");
    strQuery.append(QString::number(id));
    strQuery.append(" AND userId=");
    strQuery.append(QString::number(userId));

    QSqlQuery query(strQuery, userdb);
    if (query.next()) {
        // 查询到有该用户，不添加
        qDebug() << "yes" << query.value(0).toString();
        return;
    }

    // 根据新ID重新创建用户
    query.prepare("INSERT INTO MYGROUP (id, userId, name) "
                  "VALUES (?, ?, ?);");
    query.bindValue(0, id);
    query.bindValue(1, userId);
    query.bindValue(2, name);

    query.exec();
}

