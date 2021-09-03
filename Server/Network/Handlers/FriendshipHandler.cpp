#include "FriendshipHandler.h"
#include "DataBase/datadb.h"
#include "servercontroller.h"
#include <QtDebug>
#include <QString>

#include "Utilities/log.h"

FriendshipHandler::FriendshipHandler(QObject *parent) : MsgHandler(parent)
{

}
void FriendshipHandler::parse(Msg& msg, TcpClientSocket* socket) {
    Log::GetLogObj()->writeLog("[Friendship Handler] Trying Parse");
    if (msg.getType() != MsgType::REQUEST_ADD_FRIEND) {
        Log::GetLogObj()->writeLog("[Friendship Handler] Register Msg Error.");
        return;
    }
    //获取现在的信息
    ChatMessage nowMsg = ChatMessage::fromQByteArray(msg.getContent());
    Log::GetLogObj()->writeLog("[Friendship Handler]" + QString::number(nowMsg.getSender()));
    DataDB *db = DataDB::GetInstance();
    if(db->selectUserInfoById(nowMsg.getReceiver()).getID()==0x0000){
        Log::GetLogObj()->writeLog("[Friendship Handler] NO_THIS_USER");
        socket -> sendMessage(new Msg(MsgType::REQUEST_ADD_FRIEND_ERROR_FRIEND_NOT_EXIST,""));
        return;
    }
    else if(db->friendshipExist(nowMsg.getSender(),nowMsg.getReceiver())){
        Log::GetLogObj()->writeLog("[Friendship Handler] FRIENDSHIP_EXIST");
        socket -> sendMessage(new Msg(MsgType::REQUEST_ADD_FRIEND_ERROR_FRIENDSHIP_EXIST,""));
        return;
    }
    TcpClientSocket* Friend = ServerController::GetClient(nowMsg.getReceiver());
    if(Friend == nullptr){
        Log::GetLogObj()->writeLog("[Friendship Handler] FRIEND_OFFLINE");
        socket -> sendMessage(new Msg(MsgType::REQUEST_ADD_FRIEND_ERROR_FRIEND_OFFLINE,""));
        return;
    }
    UserInfo user = db->selectUserInfoById(nowMsg.getSender());
    Friend -> sendMessage(new Msg(MsgType::REQUEST_ADD_FRIEND,user.toQByteArray()));
    Log::GetLogObj()->writeLog("[Friendship Handler] ParseDone");
}
