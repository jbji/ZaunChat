#include "handlerreg.h"

QMap<MsgType, MsgHandler* > HandlerReg::handler_regs;
HandlerReg* HandlerReg::regObj = nullptr;

HandlerReg::HandlerReg(QObject* parent)
	:QObject(parent)
{
	initialize();
}


HandlerReg* HandlerReg::GetRegObj() {
	if (!regObj) {
		regObj = new HandlerReg();
	}
	return regObj;
}

MsgHandler* HandlerReg::getHandler(MsgType type) {
	if (handler_regs.contains(type)) {
		return handler_regs[type];
	}
	return nullptr;
}

void HandlerReg::regHandler(MsgType type, MsgHandler* msg_handler) {
	if (!handler_regs.contains(type)) {
		handler_regs[type] = msg_handler;
	}
	else {
		handler_regs[MsgType::UNDEFINED] = msg_handler;
	}
}



void HandlerReg::initialize() {
	//指定父对象, 原则上应该不会泄漏, qt应该会回收掉才对

	MsgHandler* msghandler = new ChatMsgHandler(this);
	regHandler(MsgType::MSG_PLAIN_TEXT, msghandler);
	regHandler(MsgType::MSG_PIC, msghandler);
	regHandler(MsgType::MSG_EMOTION, msghandler);
	regHandler(MsgType::MSG_FILE, msghandler);
    regHandler(MsgType::MSG_WINDOW_SHAKE, msghandler);

	MsgHandler* loginhandler = new LoginHandler(this);
	regHandler(MsgType::LOGIN_SUCCESS, loginhandler);
	regHandler(MsgType::LOGIN_ERROR, loginhandler);

	MsgHandler* reghandler = new RegisterHandler(this);
	regHandler(MsgType::REGISTER_SUCCESS, reghandler);
	regHandler(MsgType::REGISTER_ERROR, reghandler);

	//加好友
	regHandler(MsgType::REQUEST_ADD_FRIEND, new FriendRequestHandler(this));

	MsgHandler* friendAddResult = new FriendRequestResultHandler(this);
	regHandler(MsgType::REQUEST_ADD_FRIEND_AGREED, friendAddResult);
	regHandler(MsgType::REQUEST_ADD_FRIEND_DECLINED, friendAddResult);
	regHandler(MsgType::REQUEST_ADD_FRIEND_ERROR_FRIEND_OFFLINE, friendAddResult);
	regHandler(MsgType::REQUEST_ADD_FRIEND_ERROR, friendAddResult);
	regHandler(MsgType::REQUEST_ADD_FRIEND_ERROR_FRIEND_NOT_EXIST, friendAddResult);
	regHandler(MsgType::REQUEST_ADD_FRIEND_ERROR_FRIENDSHIP_EXIST, friendAddResult);
	//获得好友列表
	MsgHandler* friendListHandler = new FriendListHandler(this);
	regHandler(MsgType::ALL_FRIEND_LIST, friendListHandler);

	MsgHandler* logouthandler = new LogoutHandler(this);
	regHandler(MsgType::LOGOUT_SUCCESS, logouthandler);
	regHandler(MsgType::LOGOUT_ERROR, logouthandler);

	MsgHandler* userinfoHandler = new UserInfoHandler(this);
	regHandler(MsgType::USERINFO, userinfoHandler);

	MsgHandler* registerGroupHandler = new RegisterGroupHandler(this);
	regHandler(MsgType::REGISTER_GROUP_SUCCESS, registerGroupHandler);
	regHandler(MsgType::REGISTER_GROUP_ERROR, registerGroupHandler);

	MsgHandler* modifyUserNameResultHandler = new ModifyUserNameResultHandler(this);
	regHandler(MsgType::MODIFY_USERNAME_SUCCESS, modifyUserNameResultHandler);
	regHandler(MsgType::MODIFY_USERNAME_ERROR, modifyUserNameResultHandler);

	MsgHandler* addGroupResultHandler = new AddGroupResultHandler(this);
	regHandler(MsgType::ADD_GROUP_SUCCESS, addGroupResultHandler);
	regHandler(MsgType::ADD_GROUP_ERROR, addGroupResultHandler);
	regHandler(MsgType::ADD_GROUP_ERROR_GROUP_NOT_EXIST, addGroupResultHandler);
	regHandler(MsgType::ADD_GROUP_ERROR_GROUPSHIP_EXIST, addGroupResultHandler);
	MsgHandler* groupListHandler = new GroupListHandler(this);
	regHandler(MsgType::ALL_GROUP_LIST, groupListHandler);

	MsgHandler* groupMsgHandler = new GroupMsgHandler(this);
	regHandler(MsgType::GROUP_MSG_PLAIN_TEXT, groupMsgHandler);
}
