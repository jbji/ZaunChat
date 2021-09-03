#ifndef DATADB_H
#define DATADB_H
#include <QSqlDatabase>
#include "DataModel/chatmessage.h"
#include "DataModel/datamodel.h"

class DataDB
{
public:
    explicit DataDB();
    ~DataDB();
    //登录功能数据库
    bool selectUserByIdAndPwd(const quint32 id, const QString pwd);//存在返回true，不存在返回false
    UserInfo selectUserInfoById(const quint32 id);//存在返回true，不存在返回false
    //查询当前全部用户的数据库操作--静态sql
    QList<QByteArray> selectAllFriendsUserInfo(quint32 UserId);
    //注册
    void registerUserInfo(const UserInfo& user);//一个用户结构题
    //添加好友
    void addFriendship(quint32 Id1,quint32 Id2);//两个好友的Id
    //删除好友
    void deleteFriendship(quint32 Id1,quint32 Id2);//两个好友的Id
    //判断好友关系是否存在
    bool friendshipExist(quint32 Id1,quint32 Id2);
    //添加聊天信息
    void addMsg(quint32 Id1,quint32 Id2,QString Msg,QString Date);//发送者的Id，接收者的Id，聊天信息，标准日期xxxx-xx-xx xx:xx:xx使用库获取日期
    //获取最大的Id值
    quint32 selectMaxId();
    //单例设计模式--应对数据库的对象的内存使用
    static DataDB* GetInstance();
    //邱睿桥给我她的struct之后，我写一个QList返回她需要的结构列表

    //处理离线消息
    //添加离线消息
    void addOfflineMsg(ChatMessage &msg);
    //获取离线消息
    QList<ChatMessage> getOfflineMsg(quint32 ID);
    //删除离线消息
    void dropOfflineMsg(quint32 ID);

    //群组操作
    //添加群聊关系
    void addGroupship(quint32 UserID,quint32 GroupID,quint32 UserPermission = 0);
    void registerGroupInfo(const GroupInfo& Group);
    quint32 selectMaxGroupId();
    GroupInfo selectGroupInfoByID(quint32);
    // Id1用户ID,Id2群聊ID,返回Id1是否在Id2中
    bool groupshipExist(quint32 Id1, quint32 Id2);
    QList<QByteArray> selectAllGroupInfo(quint32 ID);
    QList<quint32> selectAllGroupMember(quint32 ID);

    //修改用户名和头像
    void updUsername(quint32 ID,QString Username);
    void updAvatar(quint32 ID,QString Avatar);
private:
    QSqlDatabase sqldb;
    static DataDB* db;
};

#endif // DATADB_H
