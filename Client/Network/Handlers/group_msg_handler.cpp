#include"group_msg_handler.h"
#include"Utilities/utilities.h"
#include"DataModel/group_chat_message.h"
#include"Controller/clientcontroller.h"

GroupMsgHandler::GroupMsgHandler(QObject* parent) : MsgHandler(parent) {

}

void GroupMsgHandler::parse(Msg& msg) {
	Log::GetLogObj()->writeLog("[GroupMsgHandler] Tring Parse");
	if (msg.getType() != MsgType::GROUP_MSG_PLAIN_TEXT) {
		Log::GetLogObj()->writeLog("[GroupMsgHandler] MsgType Error");
		return;
	}
	ChatMessage chatmsg = ChatMessage::fromQByteArray(msg.getContent());
	ClientController* cc = ClientController::GetClientInstance();
	QMap<quint32, QList<GroupChatMessage>*>* chatMsgMapGroup = cc->getChatMsgMapGroup();
	QList<GroupChatMessage>* list = (*chatMsgMapGroup)[chatmsg.getReceiver()];
	quint32 senderId = chatmsg.getSender();
	QMap<quint32, UserInfo>& idtouserinfomap = cc->getIdToUserInfoMap();
	if (!idtouserinfomap.contains(senderId)) {
		//request UserInfo by senderId
		cc->requestUserInfoByID(senderId);
	}
	GroupChatMessage groupchatmsg = GroupChatMessage(chatmsg, idtouserinfomap[senderId]);
	list->append(groupchatmsg);
	emit groupMsgReceiveSuccess(groupchatmsg);
}
