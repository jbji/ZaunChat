
#include "registerGroupHandler.h"
#include "DataBase/datadb.h"
#include "DataModel/groupinfo.h"
#include <QtDebug>
#include <QString>

#include "Utilities/log.h"

RegisterGroupHandler::RegisterGroupHandler(QObject *parent) : MsgHandler(parent)
{

}
void RegisterGroupHandler::parse(Msg& msg, TcpClientSocket* socket) {
    Log::GetLogObj()->writeLog("[RegisterGroupHandler] Trying Parse");
    if (msg.getType() != MsgType::REQUEST_REGISTER_GROUP) {
        Log::GetLogObj()->writeLog("[RegisterGroupHandler] Register Msg Error.");
        return;
    }
    //把接收到的Msg转换成UserInfo对象
    UserInfo tmp = UserInfo::fromQByteArray(msg.getContent());
    //获得当前最大群组ID
    DataDB* db = DataDB::GetInstance();
    quint32 MaxIdx = db->selectMaxGroupId();
    Log::GetLogObj()->writeLog("[RegisterGroupHandler] CurrentMaxID:" + QString::number(MaxIdx) );
    //构造新的Msg对象
    GroupInfo tmp1 = GroupInfo(MaxIdx +quint32(1),tmp.getName());

    Log::GetLogObj()->writeLog("[RegisterGroupHandler] Registering: " + tmp.getName());

    //注册新的最大ID
    db->registerGroupInfo(tmp1);

    Log::GetLogObj()->writeLog("[RegisterGroupHandler] ParseDone");

    //把自己加到自己的群关系中
    db->addGroupship(tmp.getID(), tmp1.getID(),3);

    //重新作为Msg发送
    socket->sendMessage(new Msg(MsgType::REGISTER_GROUP_SUCCESS, tmp1.toQByteArray()));
}
