#include "userinfo_handler.h"

#include <QDebug>

#include "Utilities/log.h"

UserInfoHandler::UserInfoHandler(QObject *parent) : MsgHandler(parent)
{
}

void UserInfoHandler::parse(Msg & msg){
    Log::GetLogObj()->writeLog("["+QString::number(UserInfo::fromQByteArray(msg.getContent()).getID())+"]");
    emit readyShowUserInfo(UserInfo::fromQByteArray(msg.getContent()));
    emit readyRefreshFriendList();
}
