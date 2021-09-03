#include"group_msg_handler.h"
#include"DataModel/chatmessage.h"
#include"DataBase/datadb.h"
#include"servercontroller.h"
#include"Utilities/utilities.h"

GroupMsgHandler::GroupMsgHandler(QObject* parent) :MsgHandler(parent) {

}

void GroupMsgHandler::parse(Msg& msg, TcpClientSocket* socket) {
	Log::GetLogObj()->writeLog("[GroupMsgHandler] Trying Parse");
	ChatMessage chatmsg = ChatMessage::fromQByteArray(msg.getContent());
	quint32 groupId = chatmsg.getReceiver();
	quint32 senderId = chatmsg.getSender();
	DataDB* db = DataDB::GetInstance();
	QList<quint32> list = db->selectAllGroupMember(groupId);

	/*--------------------------------
	database group message reserved
	----------------------------------*/

	for (auto& member : list) {
        Log::GetLogObj()->writeLog("[GroupMsgHandler] "+ QString::number(member));
		if (member == senderId) continue;
		if (ServerController::GetClient(member) == nullptr) continue;
		ServerController::GetClient(member)->sendMessage(&msg);
		Log::GetLogObj()->writeLog("[GroupMsgHandler] "+ QString::number(member)+" groupMsg sent");
	}
	Log::GetLogObj()->writeLog("[GroupMsgHandler] Parse down");
}
