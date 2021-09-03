#pragma once
#include"msghandler.h"

class FriendshipHandler :public MsgHandler {
    Q_OBJECT
public:
    explicit FriendshipHandler(QObject* parent = nullptr);
    virtual void parse(Msg& msg, TcpClientSocket* socket = nullptr);
};
