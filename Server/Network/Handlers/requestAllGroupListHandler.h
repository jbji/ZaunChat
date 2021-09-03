#pragma once
#include "msghandler.h"

class RequestAllGroupListHandler :public MsgHandler {
    Q_OBJECT
public:
    explicit RequestAllGroupListHandler(QObject* parent = nullptr);
    virtual void parse(Msg& msg, TcpClientSocket* socket = nullptr);
};
