#pragma once
#include "msghandler.h"

class AddGroupHandler :public MsgHandler {
    Q_OBJECT
public:
    explicit AddGroupHandler(QObject* parent = nullptr);
    virtual void parse(Msg& msg, TcpClientSocket* socket = nullptr);
};
