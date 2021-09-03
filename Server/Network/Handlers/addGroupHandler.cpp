#include "addGroupHandler.h"
#include"DataBase/datadb.h"
#include"servercontroller.h"

#include "Utilities/log.h"

AddGroupHandler::AddGroupHandler(QObject* parent) : MsgHandler(parent)
{

}
void AddGroupHandler::parse(Msg& msg, TcpClientSocket* socket) {
    Log::GetLogObj()->writeLog("[AddGroup Handler] Trying Parse");
    if (msg.getType() != MsgType::REQUEST_ADD_GROUP) {
        Log::GetLogObj()->writeLog("[AddGroup Handler] Chat Msg error!");
        return;
    }
    DataDB * db = DataDB::GetInstance();
    ChatMessage tmp = ChatMessage::fromQByteArray(msg.getContent());
    if(db->selectGroupInfoByID(tmp.getReceiver()).getID() == 0x0000){
        Log::GetLogObj()->writeLog("[AddGroup Handler] NO_THIS_GROUP");
        socket -> sendMessage(new Msg(MsgType::ADD_GROUP_ERROR_GROUP_NOT_EXIST,""));
        return;
    }
    else if(db->groupshipExist(tmp.getSender(),tmp.getReceiver())){
        Log::GetLogObj()->writeLog("[AddGroup Handler] GROUPSHIP_EXIST");
        socket -> sendMessage(new Msg(MsgType::ADD_GROUP_ERROR_GROUPSHIP_EXIST,""));
        return;
    }
    db->addGroupship(tmp.getSender(),tmp.getReceiver());
    GroupInfo ans = db->selectGroupInfoByID(tmp.getReceiver());
    Log::GetLogObj()->writeLog("[AddGroup Handler] GroupName:" + ans.getName());
    socket->sendMessage(new Msg(MsgType::ADD_GROUP_SUCCESS,ans.toQByteArray()));
    Log::GetLogObj()->writeLog("[AddGroup Handler] Parse Successful.");
}
