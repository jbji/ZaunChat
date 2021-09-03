#pragma once
#include "msghandler.h"

class RequestAllFriendListHandler :public MsgHandler {
    Q_OBJECT
public:
    explicit RequestAllFriendListHandler(QObject* parent = nullptr);
    virtual void parse(Msg& msg, TcpClientSocket* socket = nullptr);
};
