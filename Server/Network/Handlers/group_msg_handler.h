#pragma once
#include"msghandler.h"
class GroupMsgHandler :public MsgHandler {
    Q_OBJECT
public:
    explicit GroupMsgHandler(QObject* parent = nullptr);
    virtual void parse(Msg& msg, TcpClientSocket* socket = nullptr);
};