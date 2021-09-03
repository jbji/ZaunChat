#include "clientcontroller.h"


//添加好友的请求 以及反馈
void ClientController::requestAddFriend(quint32 receiver,QString verifyMsg){//发送好友请求
    ChatMessage msg = ChatMessage(getMyInfo().getID(),receiver,verifyMsg);
    GetSocket()->sendMessage(new Msg(MsgType::REQUEST_ADD_FRIEND,msg.toQByteArray()));
}

void ClientController::agreeFriendRequest(quint32 sender,quint32 receiver,QString s){
    ChatMessage msg=ChatMessage(sender,receiver,s);
    Log::GetLogObj()->writeLog("[client add friend receiver]: agree.");
    GetSocket()->sendMessage(new Msg(MsgType::REQUEST_ADD_FRIEND_AGREED,msg.toQByteArray()));
}

void ClientController::declineFriendRequest(quint32 sender,quint32 receiver,QString s){
    ChatMessage msg=ChatMessage(sender,receiver,s);
    Log::GetLogObj()->writeLog("[client add friend receiver]: decline.");
    GetSocket()->sendMessage(new Msg(MsgType::REQUEST_ADD_FRIEND_DECLINED,msg.toQByteArray()));
}

//在好友接受了请求之后, 将Friend Append到里面.
//将好友添加到现存的数据结构中
void ClientController::dynamicAppendFriend(UserInfo _friend) {
    //将好友添加到好友列表中
    friendList.append(_friend);
    //为好友新建消息List
    chatMsgMap[_friend.getID()] = new QList<ChatMessage>;
}

//发送好友列表获取的请求
void ClientController::requestFriendList(UserInfo info) {
    GetSocket()->sendMessage(new Msg(MsgType::REQUEST_ALL_FRIEND_LIST, QString::number(info.getID()).toUtf8() ));
    Log::GetLogObj()->writeLog("[SendFriendListRequest] Sent.");
}

QList<UserInfo> * ClientController::getFriendList() {
    return &friendList;
}
