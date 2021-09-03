#include "login_handler.h"

#include <QDebug>

#include "Utilities/log.h"


LoginHandler::LoginHandler(QObject *parent) : MsgHandler(parent)
{
}

void LoginHandler::parse(Msg & msg){
    MsgType loginStatus = msg.getType();

    if(loginStatus == MsgType::LOGIN_SUCCESS){
        myInfo = UserInfo::fromQByteArray(msg.getContent());
        Log::GetLogObj()->writeLog("[ClientLoginHandler] 登录成功");
        emit sigLoginSuccessful(myInfo);
    }else{
        Log::GetLogObj()->writeLog("[ClientLoginHandler] 登录失败");
        emit sigLoginFailed();
    }
}

UserInfo& LoginHandler::getMyInfo(){
    return myInfo;
}
