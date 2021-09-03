#include <QtDebug>
#include <QString>
#include "DataBase/datadb.h"
#include "Network/Handlers/LogoutHandler.h"

#include "servercontroller.h"

#include "DataModel/datamodel.h"
#include "Utilities/utilities.h"

LogoutHandler::LogoutHandler(QObject *parent) : MsgHandler(parent)
{

}
void LogoutHandler::parse(Msg& msg, TcpClientSocket* socket){
    Log::GetLogObj()->writeLog("[LogoutHandler] Trying Parse");
    if (msg.getType() != MsgType::REQUEST_LOGOUT) {
        Log::GetLogObj()->writeLog("Logout msg error");
        return;
    }
    UserInfo tmp = UserInfo::fromQByteArray(msg.getContent());
    if(ServerController::GetClient(tmp.getID()) == nullptr){
        socket->sendMessage(new Msg(MsgType::LOGOUT_ERROR,""));
    }
    ServerController::getServerInstance()->deleteClient(tmp.getID());
    socket->sendMessage(new Msg(MsgType::LOGOUT_SUCCESS,""));
    Log::GetLogObj()->writeLog("[LogoutHandler] Sent");
}
