#include "clientcontroller.h"

#include "DataModel/Msg/msg.h"
#include "Utilities/utilities.h"


void ClientController::sendChatMessage(quint32 receiver, QString content){
    ChatMessage chat_msg(getMyInfo().getID(), receiver, content);
    sendChatMessage(chat_msg);
}


void ClientController::sendChatMessage(ChatMessage & chat_msg){
    Log::GetLogObj()->writeLog("[SendChatMessage 正在发送] "+chat_msg.getContent());
    GetSocket()->sendMessage(
                    new Msg(MsgType::MSG_PLAIN_TEXT, chat_msg.toQByteArray())
                );
}

//slot: 初始化聊天消息映射, 同时获取好友列表
//这是一个槽函数, 在接收到登录成功的signal的时候才调用

QList<ChatMessage> * ClientController::getChatMsg(quint32 id) {
    if(chatMsgMap.contains(id)){
        return chatMsgMap[id];
    }
    return nullptr;
}

void ClientController::requestOfflineMsg() {
    ClientController* cc = ClientController::GetClientInstance();
    GetSocket()->sendMessage(new Msg(MsgType::REQUEST_OFFLINE_MSG, QString::number(cc->getMyInfo().getID()).toUtf8()));
    Log::GetLogObj()->writeLog("[SendOfflineMsgRequest] Sent.");
}

void ClientController::requestAllFriendListUserInfo() {
    Log().GetLogObj()->writeLog("[requestAllFriendListUserInfo] work right!");
    for (auto& x : friendList) {
        if (x.getName() == "" || x.getAvatarName() == "") {
            qDebug()<<x.getID();
            requestUserInfoByID(x.getID());
        }
    }
}


void ClientController::sendWindowShake(quint32 receiver){
    GetSocket()->sendMessage(new Msg(MsgType::MSG_WINDOW_SHAKE,
                                     ChatMessage(getMyInfo().getID(), receiver, "窗口抖动").toQByteArray()
                                     ));
}
