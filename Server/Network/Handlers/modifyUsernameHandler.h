#pragma once
#include "msghandler.h"

class ModifyUsernameHandler :public MsgHandler {
    Q_OBJECT
public:
    explicit ModifyUsernameHandler(QObject* parent = nullptr);
    virtual void parse(Msg& msg, TcpClientSocket* socket = nullptr);
};
