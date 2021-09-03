
#include "requestUserInfoHandler.h"
#include "DataBase/datadb.h"
#include <QtDebug>
#include <QString>

#include "Utilities/log.h"

RequsetUserInfoHandler::RequsetUserInfoHandler(QObject *parent) : MsgHandler(parent)
{

}
void RequsetUserInfoHandler::parse(Msg& msg, TcpClientSocket* socket) {
    Log::GetLogObj()->writeLog("[RequsetUserInfo] Trying Parse");
    if (msg.getType() != MsgType::REQUEST_USERINFO) {
        Log::GetLogObj()->writeLog("[RequsetUserInfo] Error.");
        return;
    }
    quint32 ID = msg.getContent().toUInt();//获取ID信息
    UserInfo tmp = DataDB::GetInstance()->selectUserInfoById(ID);//通过ID获取信息
    socket->sendMessage(new Msg(MsgType::USERINFO,tmp.toQByteArray()));
}
