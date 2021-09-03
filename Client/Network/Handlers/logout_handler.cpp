#include "logout_handler.h"

#include <QDebug>

#include "Utilities/log.h"


LogoutHandler::LogoutHandler(QObject *parent) : MsgHandler(parent)
{
}

void LogoutHandler::parse(Msg & msg){
    MsgType loginStatus = msg.getType();

    if(loginStatus == MsgType::LOGOUT_SUCCESS){
        UserInfo myInfo = UserInfo::fromQByteArray(msg.getContent());
        emit sigLogoutSuccessful(myInfo);
        Log::GetLogObj()->writeLog("[ClientLogoutHandler] 下线成功");

    }else{
        emit sigLogoutFailed();
        Log::GetLogObj()->writeLog("[ClientLogoutHandler] 下线失败");
    }
}
