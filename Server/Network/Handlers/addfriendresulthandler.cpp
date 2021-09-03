#include "addfriendresulthandler.h"


AddFriendResultHandler::AddFriendResultHandler(QObject* parent) : MsgHandler(parent)
{

}

void AddFriendResultHandler::parse(Msg &msg, TcpClientSocket *socket)
{
    Log::GetLogObj()->writeLog("[AddFriendResult Handler] Trying Parse");
    MsgType addFriendResultType = msg.getType();
    if(addFriendResultType != MsgType::REQUEST_ADD_FRIEND_AGREED
            && addFriendResultType != MsgType::REQUEST_ADD_FRIEND_DECLINED){
        Log::GetLogObj()->writeLog("[AddFriendResult Handler] AddFriendResult Error.");
        return;
    }

    ChatMessage nowMsg = ChatMessage::fromQByteArray(msg.getContent());
    TcpClientSocket * receiverSocket = ServerController::GetClient(nowMsg.getSender());
    if(addFriendResultType == MsgType::REQUEST_ADD_FRIEND_AGREED){
        DataDB *db = DataDB::GetInstance();
        db->addFriendship(nowMsg.getSender(), nowMsg.getReceiver());
        db->addFriendship(nowMsg.getReceiver(),nowMsg.getSender());
        UserInfo info = db->selectUserInfoById(nowMsg.getReceiver());
        //如果是同意了 那么返回的东西变成一个发送请求的人的UserInfo
        receiverSocket->sendMessage(new Msg(addFriendResultType, info.toQByteArray()));
        return;
    }
    if(receiverSocket == nullptr){
        Log::GetLogObj()->writeLog("[AddFriendResult Handler] FRIEND_OFFLINE");
        socket -> sendMessage(new Msg(MsgType::REQUEST_ADD_FRIEND_ERROR_FRIEND_OFFLINE,""));
        return;
    }
    Log::GetLogObj()->writeLog("[AddFriendResult Handler] test");
    receiverSocket->sendMessage(new Msg(addFriendResultType, msg.getContent()));
}
