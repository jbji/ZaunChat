
#include "RegisterHandler.h"
#include "DataBase/datadb.h"
#include <QtDebug>
#include <QString>

#include "Utilities/log.h"

RegisterHandler::RegisterHandler(QObject *parent) : MsgHandler(parent)
{

}
void RegisterHandler::parse(Msg& msg, TcpClientSocket* socket) {
    Log::GetLogObj()->writeLog("[RegisterHandler] Trying Parse");
    if (msg.getType() != MsgType::REQUEST_REGISTER) {
        Log::GetLogObj()->writeLog("[Register Handler] Register Msg Error.");
		return;
	}
    //把接收到的Msg转换成UserInfo对象
    UserInfo tmp = UserInfo::fromQByteArray(msg.getContent());
    //获得当前最大ID
    DataDB* db = DataDB::GetInstance();
    quint32 MaxIdx = db->selectMaxId();
    Log::GetLogObj()->writeLog("[RegisterHandler] CurrentMaxID:" + QString::number(MaxIdx) );
    //构造新的Msg对象
    tmp = UserInfo(MaxIdx +quint32(1), tmp.getName(), tmp.getPwd());

    Log::GetLogObj()->writeLog("[RegisterHandler] Registering: " + tmp.getName() + " " + tmp.getPwd());

    //注册新的最大ID
    db->registerUserInfo(tmp);

    Log::GetLogObj()->writeLog("[RegisterHandler] ParseDone");

    //把自己加为自己的好友
    db->addFriendship(tmp.getID(), tmp.getID());

    //重新作为Msg发送
    socket->sendMessage(new Msg(MsgType::REGISTER_SUCCESS, tmp.toQByteArray()));
}
