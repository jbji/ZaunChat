#pragma once
#include "msghandler.h"

class RegisterGroupHandler :public MsgHandler {
    Q_OBJECT
public:
    explicit RegisterGroupHandler(QObject* parent = nullptr);
    virtual void parse(Msg& msg, TcpClientSocket* socket = nullptr);
};
