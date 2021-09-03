#include"group_chat_message.h"

GroupChatMessage::GroupChatMessage(const ChatMessage& _chatmsg, const UserInfo& _userinfo) :
chatmsg(0, 0, "") {
	chatmsg = _chatmsg;
	userinfo = _userinfo;
}

ChatMessage& GroupChatMessage::getChatMessage() {
	return chatmsg;
}

UserInfo& GroupChatMessage::getUserInfo() {
	return userinfo;
}
