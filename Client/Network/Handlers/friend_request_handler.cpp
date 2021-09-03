#include "friend_request_handler.h"
#include "DataModel/Msg/msgtype.h"
#include "Utilities/utilities.h"

FriendRequestHandler::FriendRequestHandler(QObject *parent) : MsgHandler(parent)
{

}

void FriendRequestHandler::parse(Msg & msg){
    Log::GetLogObj()->writeLog("[FriendRequestHandler] 接收到添加好友的请求");
    UserInfo nowMst =  UserInfo::fromQByteArray(msg.getContent());
    emit readyShowFriendRequest(nowMst);
}
