#pragma once
#include "msghandler.h"

#include "DataModel/datamodel.h"

class GroupMsgHandler : public MsgHandler {
	Q_OBJECT
public:
	explicit GroupMsgHandler(QObject* parent = nullptr);
	void parse(Msg& msg);
signals:
	void groupMsgReceiveSuccess(GroupChatMessage groupchatmsg);
};
