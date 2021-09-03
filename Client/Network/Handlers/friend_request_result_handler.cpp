#include "friend_request_result_handler.h"
#include "DataModel/Msg/msgtype.h"
#include "Utilities/utilities.h"

#include "Controller/clientcontroller.h"

FriendRequestResultHandler::FriendRequestResultHandler(QObject *parent) : MsgHandler(parent)
{

}


void FriendRequestResultHandler::parse(Msg & msg){
    Log::GetLogObj()->writeLog("[FriendRequestResultHandler] 正在返回好友请求结果");

    if(msg.getType() == MsgType::REQUEST_ADD_FRIEND_AGREED){
        UserInfo u = UserInfo::fromQByteArray(msg.getContent());
        ClientController::GetClientInstance()->dynamicAppendFriend(u);
        Log::GetLogObj()->writeLog(QString::number(u.getID()) + "现在是你的好友了.");
        //这样只需要缓存头像就行了.
        emit sigAddFriendSuccessful();
    }
    else{
        emit sigAddFriendFailed(msg.getType());
    }

}
