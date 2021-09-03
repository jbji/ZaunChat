#pragma once
#include"chatmessage.h"
#include"userinfo.h"

class GroupChatMessage {
public:
	explicit GroupChatMessage(const ChatMessage& _chatmsg, const UserInfo& _userinfo);
	ChatMessage& getChatMessage();
	UserInfo& getUserInfo();
private:
	ChatMessage chatmsg;
	UserInfo userinfo;
};